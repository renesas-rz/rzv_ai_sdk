#include "define.h"
/*DRP-AI TVM[*1] Runtime*/
#include "MeraDrpRuntimeWrapper.h"

/*****************************************
* Global Variables
******************************************/
std::map<std::string, int> input_source_map =
{
    {"USB", 1},
    #ifndef V2N
        {"VIDEO", 2},
    #endif
    {"IMAGE", 3}
};

enum MODE {
    YOLOX = 1,
    UNET,
    CALIBRATION
};
enum MODE mode = YOLOX;

struct GridAndStride
{
    int grid0;
    int grid1;
    int stride;
};

struct Detection {
    cv::Rect_<float> rect;
    int class_id;
    float score;
    cv::Point center;
};

std::vector<Detection> detections;

/*Multithreading*/
static sem_t terminate_req_sem;
static pthread_t inf_thread;
static pthread_t capture_thread;
static pthread_t kbhit_thread;

static std::mutex mtx; 
static std::mutex unet_mtx;
static std::mutex yolox_mtx;

static std::atomic<uint8_t> inference_start (0);
static std::atomic<uint8_t> img_obj_ready   (0);

/*AI Inference for DRPAI*/
/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper runtime_yolox;
MeraDrpRuntimeWrapper runtime_unet;

/*DRP-AI Frequency setting*/
static int32_t drpai_freq;

uint32_t middle_bn_x0 = 800;
uint32_t middle_bn_x1 = 1050;
uint32_t middle_bn_y0 = 800;
uint32_t middle_bn_y1 = 880;

uint32_t topleft_bn_x0 = 200;
uint32_t topleft_bn_x1 = 450;
uint32_t topleft_bn_y0 = 100;
uint32_t topleft_bn_y1 = 180;

uint32_t topright_bn_x0 = 1100;
uint32_t topright_bn_x1 = 1350;
uint32_t topright_bn_y0 = 100;
uint32_t topright_bn_y1 = 180;

uint32_t min_control_bn_x0 = DISP_IMAGE_OUTPUT_WIDTH + 120;
uint32_t min_control_bn_x1 = DISP_IMAGE_OUTPUT_WIDTH + 220;
uint32_t min_control_bn_y0 = DISP_IMAGE_OUTPUT_HEIGHT - 580;
uint32_t min_control_bn_y1 = DISP_IMAGE_OUTPUT_HEIGHT - 500;

uint32_t max_control_bn_x0 = DISP_IMAGE_OUTPUT_WIDTH + 320;
uint32_t max_control_bn_x1 = DISP_IMAGE_OUTPUT_WIDTH + 420;
uint32_t max_control_bn_y0 = DISP_IMAGE_OUTPUT_HEIGHT - 580;
uint32_t max_control_bn_y1 = DISP_IMAGE_OUTPUT_HEIGHT - 500;

static float yolox_pre_time   = 0;
static float yolox_post_time  = 0;
static float yolox_ai_time    = 0;
static float yolox_total_time = 0;

static float unet_pre_time   = 0;
static float unet_post_time  = 0;
static float unet_ai_time    = 0;
static float unet_total_time = 0;

cv::Mat yuyv_image;
cv::Mat input_image;
cv::Mat unet_output_mask;
bool unet_output_ready = false;
std::unordered_map<std::string, std::unordered_map<std::string, std::string>> ini_values;
int32_t page = 1;
std::vector<cv::Point> points;
bool g_image_mode = false;
bool dev_option = false;

float font_size = 0.75;
float font_weight = 2;
float font_thickness = 2;

cv::Point min(-1, -1), max(-1, -1), center(-1, -1), tip(-1, -1);
int max_deviation = DEVIATION_THRESHOLD;
bool high_deviation = false;
double meter_value;
int meter_min; 
int meter_max;


/*****************************************
* Function Name     : float16_to_float32
* Description       : Function by Edge cortex. Cast uint16_t a into float value.
* Arguments         : a = uint16_t number
* Return value      : float = float32 number
******************************************/
float float16_to_float32(uint16_t a)
{
    return __extendXfYf2__<uint16_t, uint16_t, 10, float, uint32_t, 23>(a);
}

/*****************************************
* Function Name : time_difference_msec
* Description   : compute the time differences in ms between two moments
* Arguments     : t0 = start time
*                 t1 = stop time
* Return value  : the time difference in ms
******************************************/
static double time_difference_msec(struct timespec t0, struct timespec t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1000000.0;
}

/*****************************************
 * Function Name     : float_to_string
 * Description       : Convert float to string with precision
 * Arguments         : number = float number to be converted
 *                     precision = int number to set precision
 * Return value      : string = string number
 ******************************************/
std::string float_to_string(float number, int precision = 2)
{
    std::stringstream stream;  
    stream.precision(precision);
    stream << std::fixed << number;  
    return stream.str();
}

/*****************************************
* Function Name : wait_join
* Description   : waits for a fixed amount of time for the thread to exit
* Arguments     : p_join_thread = thread that the function waits for to Exit
*                 join_time = the timeout time for the thread for exiting
* Return value  : 0 if successful
*                 not 0 otherwise
******************************************/
static int8_t wait_join(pthread_t *p_join_thread, uint32_t join_time)
{
    int8_t ret_err;
    struct timespec join_timeout;
    ret_err = clock_gettime(CLOCK_REALTIME, &join_timeout);
    if ( 0 == ret_err )
    {
        join_timeout.tv_sec += join_time;
        ret_err = pthread_timedjoin_np(*p_join_thread, NULL, &join_timeout);
    }
    return ret_err;
}


/*****************************************
* Function Name     : config_read
* Description       : Read configuration from the config.ini file.
******************************************/
void config_read()
{
    /*Open config.ini file*/
    std::ifstream ini_file("config.ini");
    std::string line;
    std::string current_section;
    /*parsing ini file*/
    while (std::getline(ini_file, line))
    {
        auto comment_pos = line.find(";");
        if (comment_pos != std::string::npos)
        {
            line.erase(comment_pos);
        }
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        if (line.empty())
        {
            continue;
        }
        else if (line[0] == '[')
        {
            current_section = line.substr(1, line.size() - 2);
        }
        else
        {
            auto delimiter_pos = line.find("=");
            std::string key = line.substr(0, delimiter_pos);
            std::string value = line.substr(delimiter_pos + 1);
            ini_values[current_section][key] = value;
        }
    }
    return;
}

/*****************************************
* Function Name : get_result
* Description   : Get DRP-AI Output from memory via DRP-AI Driver
* Arguments     : drpai_fd = file descriptor of DRP-AI Driver
*                 output_addr = memory start address of DRP-AI output
*                 output_size = output data size
* Return value  : 0 if succeeded
*                 not 0 otherwise
******************************************/
int8_t get_result(MeraDrpRuntimeWrapper runtime, std::vector<float> &drpai_output_buf)
{
    int8_t ret = 0;
    int32_t i = 0;
    int32_t output_num = 0;
    std::tuple<InOutDataType, void*, int64_t> output_buffer;
    int64_t output_size;
    uint32_t size_count = 0;

    /* Get the number of output of the target model. */
    output_num = runtime.GetNumOutput();
    size_count = 0;
    /*GetOutput loop*/
    for (i = 0; i < output_num; i++)
    {
        /* output_buffer below is tuple, which is { data type, address of output data, number of elements } */
        output_buffer = runtime.GetOutput(i);
        /*Output Data Size = std::get<2>(output_buffer). */
        output_size = std::get<2>(output_buffer);
        drpai_output_buf.resize(output_size);

        /*Output Data Type = std::get<0>(output_buffer)*/
        if (InOutDataType::FLOAT16 == std::get<0>(output_buffer))
        {
            /*Output Data = std::get<1>(output_buffer)*/
            uint16_t* data_ptr = reinterpret_cast<uint16_t*>(std::get<1>(output_buffer));
            for (int j = 0; j < output_size; j++)
            {
                /*FP16 to FP32 conversion*/
                drpai_output_buf[j + size_count]=float16_to_float32(data_ptr[j]);
            }
        }
        else if (InOutDataType::FLOAT32 == std::get<0>(output_buffer))
        {
            /*Output Data = std::get<1>(output_buffer)*/
            float* data_ptr = reinterpret_cast<float*>(std::get<1>(output_buffer));
            for (int j = 0; j < output_size; j++)
            {
                drpai_output_buf[j + size_count]=data_ptr[j];
            }
        }
        else
        {
            fprintf(stderr, "[ERROR] Output data type : not floating point.\n", errno);
            ret = -1;
            break;
        }
        size_count += output_size;
    }
    return ret;
}

/*****************************************
 * Function Name : hwc2chw
 * Description   : This function takes an input image in HWC (height, width, channels)
 *                 format and returns an output image in CHW (channels, height, width) format.
 * Arguments     : image = cv::Mat
 * Return value  : flat_image = cv::Mat
 ******************************************/
cv::Mat hwc2chw(const cv::Mat &image)
{
    std::vector<cv::Mat> rgb_images;
    cv::split(image, rgb_images);
    cv::Mat m_flat_r = rgb_images[0].reshape(1, 1);
    cv::Mat m_flat_g = rgb_images[1].reshape(1, 1);
    cv::Mat m_flat_b = rgb_images[2].reshape(1, 1);
    cv::Mat matArray[] = {m_flat_r, m_flat_g, m_flat_b};
    cv::Mat flat_image;
    cv::hconcat(matArray, 3, flat_image);
    return flat_image;
}


/*****************************************
* Function Name     : yolox_preprocessing
* Description       : yolox model preprocessing
* Arguments         : input_frame = input mat image
*                     input_tensor_values = preprocessed output
******************************************/
void yolox_preprocessing(const cv::Mat input_frame, std::vector<float> &input_tensor_values, float &r)
{
    input_tensor_values.clear();
    int h = input_frame.rows, w = input_frame.cols;
    r = std::min(YOLOX_MODEL_WIDTH / (float)w, YOLOX_MODEL_HEIGHT / (float)h);
    int new_w = int(w * r), new_h = int(h * r);

    cv::Mat resized;
    cv::resize(input_frame, resized, cv::Size(new_w, new_h));
    cv::Mat padded(cv::Size(YOLOX_MODEL_WIDTH, YOLOX_MODEL_HEIGHT), CV_8UC3, cv::Scalar(114, 114, 114));
    resized.copyTo(padded(cv::Rect(0, 0, new_w, new_h)));

    padded.convertTo(padded, CV_32F);

    std::vector<cv::Mat> channels(3);
    cv::split(padded, channels);
    for (int c = 0; c < 3; ++c) {  
        input_tensor_values.insert(input_tensor_values.end(),
                                   (float*)channels[c].datastart,
                                   (float*)channels[c].dataend);
    }

}

/*****************************************
* Function Name     : generate_grids_and_stride
* Description       : function to generate grids for the given input size to decode yolox bounding box positions  
* Arguments         : target_w = width
*                     target_h = height
*                     strides = grid sizes in vector
*                     grid_strides = variable to store the grid generated
******************************************/
static void generate_grids_and_stride(const int target_w, const int target_h, std::vector<int>& strides, std::vector<GridAndStride>& grid_strides)
{
    for (auto stride : strides)
    {
        int num_grid_w = target_w / stride;
        int num_grid_h = target_h / stride;
        for (int g1 = 0; g1 < num_grid_h; g1++)
        {
            for (int g0 = 0; g0 < num_grid_w; g0++)
            {
                grid_strides.push_back((GridAndStride){g0, g1, stride});
            }
        }
    }
}

/*****************************************
* Function Name     : generate_yolox_proposals
* Description       : function to generate all bounding boxes
* Arguments         : grid_strides = grid generated
*                     feat_ptr = yolox model output array
*                     prob_threshold = cut off threshold
*                     objects = variable to store the objects detected
******************************************/
static void generate_yolox_proposals(std::vector<GridAndStride> grid_strides, const float* feat_ptr, float prob_threshold, std::vector<Detection>& objects)
{
    
    const int num_anchors = grid_strides.size();
    
    for (int anchor_idx = 0; anchor_idx < num_anchors; anchor_idx++)
    {
        const int grid0 = grid_strides[anchor_idx].grid0;
        const int grid1 = grid_strides[anchor_idx].grid1;
        const int stride = grid_strides[anchor_idx].stride;

	    const int basic_pos = anchor_idx * (NUM_CLASS + 5);

        float x_center = (feat_ptr[basic_pos + 0] + grid0) * stride;
        float y_center = (feat_ptr[basic_pos + 1] + grid1) * stride;
        float w = exp(feat_ptr[basic_pos + 2]) * stride;
        float h = exp(feat_ptr[basic_pos + 3]) * stride;
        float x0 = x_center - w * 0.5f;
        float y0 = y_center - h * 0.5f;

        float box_objectness = feat_ptr[basic_pos + 4];
        for (int class_idx = 0; class_idx < NUM_CLASS; class_idx++)
        {
            float box_cls_score = feat_ptr[basic_pos + 5 + class_idx]; 
            float box_prob = box_objectness * box_cls_score;
            if (box_prob > prob_threshold)
            {
                Detection obj;
                obj.rect.x = x0;
                obj.rect.y = y0;
                obj.rect.width = w;
                obj.rect.height = h;
                obj.class_id = class_idx;
                obj.score = box_prob;
                obj.center.x = x_center;
                obj.center.y = y_center;
                objects.push_back(obj);
            }

        }
    }
}

/*****************************************
* Function Name     : qsort_descent_inplace
* Description       : function to sort detected bounding box with specified positions
* Arguments         : faceobjects = vector of objects detected
*                     left = left position
*                     right = right position
******************************************/
static void qsort_descent_inplace(std::vector<Detection>& faceobjects, int left, int right)
{
    int i = left;
    int j = right;
    float p = faceobjects[(left + right) / 2].score;

    while (i <= j)
    {
        while (faceobjects[i].score > p)
            i++;

        while (faceobjects[j].score < p)
            j--;

        if (i <= j)
        {
            // swap
            std::swap(faceobjects[i], faceobjects[j]);

            i++;
            j--;
        }
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            if (left < j) qsort_descent_inplace(faceobjects, left, j);
        }
        #pragma omp section
        {
            if (i < right) qsort_descent_inplace(faceobjects, i, right);
        }
    }
}

/*****************************************
* Function Name     : qsort_descent_inplace
* Description       : function to sort detected bounding box 
* Arguments         : objects = vector of objects detected
******************************************/
static void qsort_descent_inplace(std::vector<Detection>& objects)
{
    if (objects.empty())
        return;

    qsort_descent_inplace(objects, 0, objects.size() - 1);
}

/*****************************************
* Function Name     : intersection_area
* Description       : function to find intersection between 2 bounding box
* Arguments         : a = objects detected
*                   : b = objects detected
******************************************/
static inline float intersection_area(const Detection& a, const Detection& b)
{
    cv::Rect_<float> inter = a.rect & b.rect;
    return inter.area();
}

/*****************************************
* Function Name     : nms_sorted_bboxes
* Description       : function for nms
* Arguments         : faceobjects = vector of objects detected
*                   : picked = objects picked in vector (index only)
*                   : nms_threshold = nms threshold
******************************************/
static void nms_sorted_bboxes(const std::vector<Detection>& faceobjects, std::vector<int>& picked, float nms_threshold)
{
    picked.clear();

    const int n = faceobjects.size();

    std::vector<float> areas(n);
    for (int i = 0; i < n; i++)
    {
        areas[i] = faceobjects[i].rect.area();
    }

    for (int i = 0; i < n; i++)
    {
        const Detection& a = faceobjects[i];

        int keep = 1;
        for (int j = 0; j < (int)picked.size(); j++)
        {
            const Detection& b = faceobjects[picked[j]];

            // intersection over union
            float inter_area = intersection_area(a, b);
            float union_area = areas[i] + areas[picked[j]] - inter_area;
            // float IoU = inter_area / union_area
            if (inter_area / union_area > nms_threshold)
                keep = 0;
        }

        if (keep)
            picked.push_back(i);
    }
}

/*****************************************
* Function Name     : yolox_postprocessing
* Description       : function for yolox postprocessing
* Arguments         : output = yolox inference output buffer 
******************************************/
void yolox_postprocessing(const float* output, float &r)
{
    yolox_mtx.lock();
    detections.clear();
    std::vector<Detection> proposals;
    std::vector<int> strides = {8, 16, 32};
    std::vector<GridAndStride> grid_strides;
    generate_grids_and_stride(YOLOX_MODEL_WIDTH, YOLOX_MODEL_HEIGHT, strides, grid_strides);
    generate_yolox_proposals(grid_strides, output, TH_PROB, proposals);
    qsort_descent_inplace(proposals);

    std::vector<int> picked;
    nms_sorted_bboxes(proposals, picked, TH_NMS);
    int count = picked.size();
    
    detections.resize(count);
    for (int i = 0; i < count; i++)
    {
        detections[i] = proposals[picked[i]];

        // adjust offset to original unpadded
        detections[i].rect.x /= r;
        detections[i].rect.y /= r; 
        detections[i].rect.width /= r;
        detections[i].rect.height /= r;
        detections[i].center.x /= r;
        detections[i].center.y /= r;

    }
    yolox_mtx.unlock();
}

/*****************************************
* Function Name     : angle_calculation
* Description       : function for angle calculation
* Arguments         : mask = mask generated from unet output
******************************************/
void angle_calculation(cv::Mat mask)
{ 
    // Find contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    if (contours.empty()) {
        std::cerr << "No contours found." << std::endl;
        return;
    }
    std::vector<cv::Point> contour = *std::max_element(contours.begin(), contours.end(),
                                             [](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b) {
                                                 return cv::contourArea(a) < cv::contourArea(b);
                                             });
    
    cv::Point leftmost = *std::min_element(contour.begin(), contour.end(), [](const cv::Point& a, const cv::Point& b) {
        return a.x < b.x;
    });
    cv::Point rightmost = *std::max_element(contour.begin(), contour.end(), [](const cv::Point& a, const cv::Point& b) {
        return a.x < b.x;
    });
    cv::Point topmost = *std::min_element(contour.begin(), contour.end(), [](const cv::Point& a, const cv::Point& b) {
        return a.y < b.y;
    });
    cv::Point bottommost = *std::max_element(contour.begin(), contour.end(), [](const cv::Point& a, const cv::Point& b) {
        return a.y < b.y;
    });

    double dist_leftmost, dist_rightmost, dist_topmost, dist_bottommost;
    dist_leftmost = std::sqrt(std::pow(leftmost.x - center.x, 2) + std::pow(leftmost.y - center.y, 2));
    dist_rightmost = std::sqrt(std::pow(rightmost.x - center.x, 2) + std::pow(rightmost.y - center.y, 2));
    dist_topmost = std::sqrt(std::pow(topmost.x - center.x, 2) + std::pow(topmost.y - center.y, 2));
    dist_bottommost = std::sqrt(std::pow(bottommost.x - center.x, 2) + std::pow(bottommost.y - center.y, 2));

    tip = topmost;
    if (dist_leftmost >= dist_rightmost && dist_leftmost >= dist_topmost && dist_leftmost >= dist_bottommost) tip = leftmost;
    if (dist_rightmost >= dist_leftmost && dist_rightmost >= dist_topmost && dist_rightmost >= dist_bottommost) tip = rightmost;
    if (dist_bottommost >= dist_leftmost && dist_bottommost >= dist_rightmost && dist_bottommost >= dist_topmost) tip = bottommost;

    double distance_tip_min, distance_center_min, distance_center_tip, distance_tip_max, distance_center_max, distance_min_max;
    double angle_min_center_tip, angle_max_center_tip, angle_min_center_max;

    // distance calculations for triangle min-center-tip 
    distance_tip_min = std::sqrt(std::pow(tip.x - min.x, 2) + std::pow(tip.y - min.y, 2));
    distance_center_min = std::sqrt(std::pow(min.x - center.x, 2) + std::pow(min.y - center.y, 2));
    distance_center_tip = std::sqrt(std::pow(tip.x - center.x, 2) + std::pow(tip.y - center.y, 2));
    
    // distance calculations for triangle max-center-tip 
    distance_tip_max = std::sqrt(std::pow(tip.x - max.x, 2) + std::pow(tip.y - max.y, 2));
    distance_center_max = std::sqrt(std::pow(max.x - center.x, 2) + std::pow(max.y - center.y, 2));
    
    // distance calculations for triangle min-center-max 
    distance_min_max = std::sqrt(std::pow(min.x - max.x, 2) + std::pow(min.y - max.y, 2));

    // angle calculations
    angle_min_center_tip = std::acos((std::pow(distance_center_min, 2) + std::pow(distance_center_tip, 2) - std::pow(distance_tip_min, 2)) / (2 * distance_center_tip * distance_center_min));
    angle_max_center_tip = std::acos((std::pow(distance_center_max, 2) + std::pow(distance_center_tip, 2) - std::pow(distance_tip_max, 2)) / (2 * distance_center_tip * distance_center_max));
    angle_min_center_max = std::acos((std::pow(distance_center_min, 2) + std::pow(distance_center_max, 2) - std::pow(distance_min_max, 2)) / (2 * distance_center_max * distance_center_min));
    
    // convert radians to degrees 
    angle_min_center_tip = angle_min_center_tip * (180.0 / M_PI);
    angle_max_center_tip = angle_max_center_tip * (180.0 / M_PI);
    angle_min_center_max = angle_min_center_max * (180.0 / M_PI);
    angle_min_center_max = 360 - angle_min_center_max;

    // when tip is below min
    if (angle_max_center_tip < (angle_min_center_max - 180) && angle_min_center_tip > 3) {
        angle_min_center_tip = 360 - angle_min_center_tip;
    }

    if (dev_option)
    {
        std::cout << "Angle min-center-tip : " << angle_min_center_tip << std::endl;
        std::cout << "Angle min-center-max (inverse) : " << angle_min_center_max << std::endl;
    }
    meter_value = angle_min_center_tip / (angle_min_center_max / (meter_max - meter_min));
    meter_value += meter_min;
}

/*****************************************
* Function Name     : unet_preprocessing
* Description       : function for unet preprocessing 
* Arguments         : input_frame = input imahe
*                     preprocessed_image = output image
******************************************/
void unet_preprocessing(const cv::Mat input_frame, cv::Mat& preprocessed_image)
{
    cv::resize(input_frame, preprocessed_image, cv::Size(UNET_MODEL_WIDTH, UNET_MODEL_HEIGHT));
    cv::cvtColor(preprocessed_image, preprocessed_image, cv::COLOR_BGR2RGB);
    preprocessed_image = hwc2chw(preprocessed_image);
    preprocessed_image.convertTo(preprocessed_image, CV_32FC3, 1.0 / 255.0, 0);
    /*deep copy, if not continuous*/
    if (!preprocessed_image.isContinuous()) preprocessed_image = preprocessed_image.clone();
}

/*****************************************
* Function Name     : unet_postprocessing
* Description       : function for unet postprocessing 
* Arguments         : output = unet inference output buffer 
******************************************/
void unet_postprocessing(float* output)
{
    cv::Mat mask(UNET_MODEL_WIDTH, UNET_MODEL_HEIGHT, CV_32FC1, (void*)output);
    double minVal, maxVal;
    cv::minMaxLoc(mask, &minVal, &maxVal);
    unet_mtx.lock();
    mask.convertTo(unet_output_mask, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
    cv::threshold(unet_output_mask, unet_output_mask, 127, 255, cv::THRESH_BINARY);
    cv::resize(unet_output_mask, unet_output_mask, cv::Size(input_image.cols, input_image.rows));
    angle_calculation(unet_output_mask);
    cv::applyColorMap(unet_output_mask, unet_output_mask, cv::COLORMAP_INFERNO);
    unet_output_ready = true;
    unet_mtx.unlock();
}


/*****************************************
* Function Name : R_Inf_Thread
* Description   : Executes the DRP-AI inference thread
* Arguments     : threadid = thread identification
* Return value  : -
******************************************/
void *R_Inf_Thread(void *threadid)
{
    /*Semaphore Variable*/
    int32_t inf_sem_check = 0;

    /*Variable for checking return value*/
    int8_t ret = 0;
    /*Variable for Performance Measurement*/
    static struct timespec start_time;
    static struct timespec inf_end_time;
    static struct timespec pre_start_time;
    static struct timespec pre_end_time;
    static struct timespec post_start_time;
    static struct timespec post_end_time;

    printf("\n[INFO] Inference Thread Starting\n");

    std::vector<float> drpai_unet_output_buf;
    std::vector<float> drpai_yolox_output_buf;

    std::vector<float> yolox_preprocessed_image;
    cv::Mat unet_preprocessed_image;

    int yolox_if_count = 0;
    int unet_if_count = 0;
    bool yolox_model = true;
    bool unet_model = false;
    float r;

    /*Inference Loop Start*/
    while(1)
    {
        while(1)
        {
            /*Gets the Termination request semaphore value. If different then 1 Termination was requested*/
            /*Checks if sem_getvalue is executed without issue*/
            errno = 0;
            ret = sem_getvalue(&terminate_req_sem, &inf_sem_check);
            if (0 != ret)
            {
                fprintf(stderr, "[ERROR] Failed to get Semaphore Value: errno=%d\n", errno);
                goto err;
            }
            /*Checks the semaphore value*/
            if (1 != inf_sem_check)
            {
                goto ai_inf_end;
            }
            /*Checks if image frame from Capture Thread is ready.*/
            if (inference_start.load())
            {
                break;
            }
            usleep(WAIT_TIME);
        }

        switch (mode)
        {
        case 1:
            yolox_model = true;
            unet_model = false;
            break;
        case 2:
            yolox_model = false;
            unet_model = true;
            unet_if_count++;
            if(unet_if_count > UNET_IF_COUNT)
            {
                mode = CALIBRATION;
                page = 5;
                unet_if_count = 0;
                yolox_model = true;
            }
            break;
        case 3:
            yolox_if_count++;
            if(yolox_if_count > YOLOX_IF_COUNT && !high_deviation)
            {
                mode = UNET;
                page = 4;
                yolox_if_count = 0;
            }
            else if (yolox_if_count > YOLOX_IF_COUNT && high_deviation)
            {
                mode = YOLOX;
                page = 2;
                yolox_if_count = 0;
            }
            else
            {
                yolox_model = true;
                unet_model = true;
            }
            break;
        default:
            break;
        }

        if(yolox_model)
        {
            /*Gets Pre-process starting time*/
            ret = timespec_get(&pre_start_time, TIME_UTC);
            if (0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to get Pre-process Start Time\n");
                goto err;
            }

            yolox_preprocessing(input_image, yolox_preprocessed_image, r);

            ret = timespec_get(&pre_end_time, TIME_UTC);
            if ( 0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to Get Pre-process End Time\n");
                goto err;
            }

            /*Set Pre-processing output to be inference input. */
            runtime_yolox.SetInput(0, yolox_preprocessed_image.data());
            
            /*Pre-process Time Result*/
            yolox_pre_time = (float)((time_difference_msec(pre_start_time, pre_end_time)));

            /*Gets inference starting time*/
            ret = timespec_get(&start_time, TIME_UTC);
            if (0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to get Inference Start Time\n");
                goto err;
            }
            
            runtime_yolox.Run(drpai_freq);

            usleep(WAIT_TIME * 10);

            /*Gets AI Inference End Time*/
            ret = timespec_get(&inf_end_time, TIME_UTC);
            if ( 0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to Get Inference End Time\n");
                goto err;
            }
            /*Inference Time Result*/
            yolox_ai_time = (float)((time_difference_msec(start_time, inf_end_time)));

            /*Gets Post-process starting time*/
            ret = timespec_get(&post_start_time, TIME_UTC);
            if (0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to get Post-process Start Time\n");
                goto err;
            }
            /*Process to read the DRPAI output data.*/
            ret = get_result(runtime_yolox, drpai_yolox_output_buf);
            if (0 != ret)
            {
                fprintf(stderr, "[ERROR] Failed to get result from memory.\n");
                goto err;
            }
            
            yolox_postprocessing(drpai_yolox_output_buf.data(), r);

            /*Gets Post-process End Time*/
            ret = timespec_get(&post_end_time, TIME_UTC);
            if ( 0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to Get Post-process End Time\n");
                goto err;
            }
            /*Post-process Time Result*/
            yolox_post_time = (float)((time_difference_msec(post_start_time, post_end_time)));
            yolox_total_time = yolox_pre_time + yolox_ai_time + yolox_post_time;
        }
        if (unet_model)
        {
            /*Gets Pre-process starting time*/
            ret = timespec_get(&pre_start_time, TIME_UTC);
            if (0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to get Pre-process Start Time\n");
                goto err;
            }

            unet_preprocessing(input_image, unet_preprocessed_image);

            ret = timespec_get(&pre_end_time, TIME_UTC);
            if ( 0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to Get Pre-process End Time\n");
                goto err;
            }

            /*Set Pre-processing output to be inference input. */
            runtime_unet.SetInput(0, unet_preprocessed_image.ptr<float>());
            
            /*Pre-process Time Result*/
            unet_pre_time = (float)((time_difference_msec(pre_start_time, pre_end_time)));

            /*Gets inference starting time*/  
            ret = timespec_get(&start_time, TIME_UTC);
            if (0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to get Inference Start Time\n");
                goto err;
            }
            
            runtime_unet.Run(drpai_freq);

            /*Gets AI Inference End Time*/
            ret = timespec_get(&inf_end_time, TIME_UTC);
            if ( 0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to Get Inference End Time\n");
                goto err;
            }
            /*Inference Time Result*/
            unet_ai_time = (float)((time_difference_msec(start_time, inf_end_time)));

            /*Gets Post-process starting time*/
            ret = timespec_get(&post_start_time, TIME_UTC);
            if (0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to get Post-process Start Time\n");
                goto err;
            }
            /*Process to read the DRPAI output data.*/
            ret = get_result(runtime_unet, drpai_unet_output_buf);
            if (0 != ret)
            {
                fprintf(stderr, "[ERROR] Failed to get result from memory.\n");
                goto err;
            }
            
            unet_postprocessing(drpai_unet_output_buf.data());
            
            /*Gets Post-process End Time*/
            ret = timespec_get(&post_end_time, TIME_UTC);
            if ( 0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to Get Post-process End Time\n");
                goto err;
            }
            /*Post-process Time Result*/
            unet_post_time = (float)((time_difference_msec(post_start_time, post_end_time)));
            unet_total_time = unet_pre_time + unet_ai_time + unet_post_time;
        }
        inference_start.store(0);
    }
    /*End of Inference Loop*/

/*Error Processing*/
err:
    /*Set Termination Request Semaphore to 0*/
    sem_trywait(&terminate_req_sem);
    goto ai_inf_end;
/*AI Thread Termination*/
ai_inf_end:
    /*To terminate the loop in Capture Thread.*/
    printf("[INFO] AI Inference Thread Terminated\n");
    pthread_exit(NULL);
}

/*****************************************
* Function Name : R_Kbhit_Thread
* Description   : Executes the Keyboard hit thread (checks if enter key is hit)
* Arguments     : threadid = thread identification
* Return value  : -
******************************************/
void *R_Kbhit_Thread(void *threadid)
{
    /*Semaphore Variable*/
    int32_t kh_sem_check = 0;
    /*Variable to store the getchar() value*/
    int32_t c = 0;
    /*Variable for checking return value*/
    int8_t ret = 0;

    printf("[INFO] Key Hit Thread Starting\n");

    printf("\n\n************************************************\n");
    printf("* Press ENTER key to quit. *\n");
    printf("************************************************\n");

    /*Set Standard Input to Non Blocking*/
    errno = 0;
    ret = fcntl(0, F_SETFL, O_NONBLOCK);
    if (-1 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to run fctnl(): errno=%d\n", errno);
        goto err;
    }

    while(1)
    {
        /*Gets the Termination request semaphore value. If different then 1 Termination was requested*/
        /*Checks if sem_getvalue is executed without issue*/
        errno = 0;
        ret = sem_getvalue(&terminate_req_sem, &kh_sem_check);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Semaphore Value: errno=%d\n", errno);
            goto err;
        }
        /*Checks the semaphore value*/
        if (1 != kh_sem_check)
        {
            goto key_hit_end;
        }

        c = getchar();
        if (EOF != c)
        {
            /* When key is pressed. */
            printf("[INFO] key Detected. !!!\n");
            goto err;
        }
        else
        {
            /* When nothing is pressed. */
            usleep(WAIT_TIME);
        }
    }

/*Error Processing*/
err:
    /*Set Termination Request Semaphore to 0*/
    sem_trywait(&terminate_req_sem);
    goto key_hit_end;

key_hit_end:
    printf("[INFO] Key Hit Thread Terminated\n");
    pthread_exit(NULL);
}

/*****************************************
* Function Name : R_Capture_Thread
* Description   : Executes the V4L2 capture with Capture thread.
* Arguments     : cap_pipeline = g-streamer pipeline
* Return value  : -
******************************************/
void *R_Capture_Thread(void *cap_pipeline)
{
    std::string &gstream = *(static_cast<std::string*>(cap_pipeline));
    /*Semaphore Variable*/
    int32_t capture_sem_check = 0;
    int8_t ret = 0;
    cv::Mat g_frame;
    cv::Mat raw_frame;
    cv::VideoCapture g_cap;

    printf("[INFO] Capture Thread Starting\n");

    g_cap.open(gstream, cv::CAP_GSTREAMER);
    if (!g_cap.isOpened())
    {
        std::cout << "[ERROR] Error opening video stream or camera !\n"
                  << std::endl;
        goto err;
    }

    g_cap >> g_frame;
    /* Breaking the loop if no video frame is detected */
    if (g_frame.empty())
    {
        std::cout << "[INFO] Video ended or corrupted frame !\n";
        goto capture_end;
    }

    /* Set camera resolution */
    while(1)
    {
        /*Gets the Termination request semaphore value. If different then 1 Termination was requested*/
        /*Checks if sem_getvalue is executed without issue*/
        errno = 0;
        ret = sem_getvalue(&terminate_req_sem, &capture_sem_check);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Semaphore Value: errno=%d\n", errno);
            goto err;
        }
        /*Checks the semaphore value*/
        if (1 != capture_sem_check)
        {
            goto capture_end;
        }
        if(!g_image_mode)
        {
            g_cap >> g_frame;
            /* Breaking the loop if no video frame is detected */
            if (g_frame.empty())
            {
                std::cout << "[INFO] Video ended or corrupted frame !\n";
                goto capture_end;
            }
        } 
        if (!inference_start.load())
        {
            input_image = g_frame.clone();
            inference_start.store(1); /* Flag for AI Inference Thread. */
        }

        if (!img_obj_ready.load())
        {
            yuyv_image = g_frame.clone();
            img_obj_ready.store(1); /* Flag for Main Thread. */
        }
    } /*End of Loop*/

/*Error Processing*/
err:
    sem_trywait(&terminate_req_sem);
    goto capture_end;

capture_end:
    /*To terminate the loop in AI Inference Thread.*/
    inference_start.store(1);

    printf("[INFO] Capture Thread Terminated\n");
    pthread_exit(NULL);
}

/*****************************************
 * Function Name    : create_output_frame
 * Description      : create the output frame with space for displaying inference details
 * Arguments        : cv::Mat frame_g, input frame to be displayed in the background
 * Return value     : cv::Mat background, final display frame to be written to g-streamer pipeline
 *****************************************/
cv::Mat create_output_frame(cv::Mat frame_g)
{
    /* Create a black background image of size 1080x720 */
    cv::Mat background(DISP_OUTPUT_HEIGHT, DISP_OUTPUT_WIDTH, frame_g.type(), BLACK);
    /* Resize the original image to fit within 960x720 */
    cv::Mat resizedImage;
    cv::resize(frame_g, resizedImage, cv::Size(DISP_IMAGE_OUTPUT_WIDTH, DISP_IMAGE_OUTPUT_HEIGHT));
    /* Copy the resized image to the left side of the background (0 to 960) */
    cv::Rect roi(cv::Rect(0, 0, resizedImage.cols, resizedImage.rows));
    resizedImage.copyTo(background(roi));
    return background;
}

/*****************************************
* Function Name : get_drpai_start_addr
* Description   : Get DRP-AI Memory Area Address via DRP-AI Driver
* Arguments     : int drpai_fd
* Return value  : drpai start address 
******************************************/
uint64_t get_drpai_start_addr(int drpai_fd)
{
    int ret = 0;
    drpai_data_t drpai_data;
    errno = 0;
    /* Get DRP-AI Memory Area Address via DRP-AI Driver */
    ret = ioctl(drpai_fd , DRPAI_GET_DRPAI_AREA, &drpai_data);
    if (-1 == ret)
    {
        std::cerr << "[ERROR] Failed to get DRP-AI Memory Area : errno=" << errno ;
        return (uint32_t)NULL;
    }

    return drpai_data.address;
}


/*****************************************
* Function Name : init_drpai
* Description   : Function to initialize DRP-AI.
* Arguments     : drpai_fd: DRP-AI file descriptor
* Return value  : If non-zero, DRP-AI memory start address.
*                 0 is failure.
******************************************/
uint64_t init_drpai(int drpai_fd)
{
    int ret = 0;
    uint64_t drpai_addr = 0;
    /*Get DRP-AI memory start address*/
    drpai_addr = get_drpai_start_addr(drpai_fd);

    if (drpai_addr == 0)
    {
        return 0;
    }

    return drpai_addr;
}

/*****************************************
* Function Name : print_application_info
* Description   : Function to print application info
******************************************/
void print_application_info()
{
    #ifdef V2N 
        printf("AI Application for RZ/V2N\n");
    #elif V2H
        printf("AI Application for RZ/V2H\n");
    #endif
    printf("Model 1 : YoloX | %s\n", yolox_model_dir.c_str());
    printf("Model 2 : Unet | %s\n", unet_model_dir.c_str());
}

/*****************************************
* Function Name : query_device_status
* Description   : function to check USB/MIPI device is connected
* Arguments     : device_type = the type of device
* Return value  : media_port = media port that device is connected
******************************************/
std::string query_device_status(std::string device_type)
{
    std::string media_port = "";
    /* Linux command to be executed */
    const char *command = "v4l2-ctl --list-devices";
    /* Open a pipe to the command and execute it */
    FILE *pipe = popen(command, "r");
    if (!pipe)
    {
        std::cerr << "[ERROR] Unable to open the pipe." << std::endl;
        return media_port;
    }
    /* Read the command output line by line */
    char buffer[128];
    size_t found;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        std::string response = std::string(buffer);
        found = response.find(device_type);
        if (found != std::string::npos)
        {
            fgets(buffer, sizeof(buffer), pipe);
            media_port = std::string(buffer);
            pclose(pipe);
            return media_port;
        }
    }
    pclose(pipe);
    return media_port;
}

/*****************************************
* Function Name : print_usage_info
* Description   : function to print usage info
******************************************/
void print_usage_info()
{
    #ifdef V2N
        std::cout << "[INFO] usage: ./analog_reader USB|IMAGE [File for IMAGE]\n";
    #elif V2H
        std::cout << "[INFO] usage: ./analog_reader USB|IMAGE|VIDEO [File for IMAGE|VIDEO]\n";
    #endif
}

/*****************************************
* Function Name : get_gstreamer_pipeline
* Description   : function to build gstreamer pipeline
* Arguments     : argv = command argument 
*               : gstreamer_pipeline: variable the output should be stored
* Return value  : 0 if success else -1
******************************************/
int8_t get_gstreamer_pipeline(char * argv[], std::string &gstreamer_pipeline)
{
    std::string input_source = argv[1];
    switch (input_source_map[input_source])
    {   
        /* Input Source : USB Camera */
        case 1:
        {
            std::cout << "[INFO] USB CAMERA \n";
            std::string media_port = query_device_status("usb");
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
        }
        break;
        /* Input Source : Video */
        case 2:
        {
            std::cout << "[INFO] Video \n";
            /* read input video */
            std::string video_path = argv[2];
            /* g-streamer pipeline to read input video source */
            gstreamer_pipeline = "filesrc location=" + video_path + " ! decodebin ! videoconvert ! videoscale ! video/x-raw, format=BGR ! appsink";
        }
        break;
        /* Input Source : Image */
        case 3:
        {
            std::cout << "[INFO] Image \n";
            /* read input image */
            std::string image_path = argv[2];
            g_image_mode = true;
            /* Extract the file extension */
            size_t dotPos = image_path.find_last_of('.');
            std::string extension = image_path.substr(dotPos + 1);
            if (dotPos != std::string::npos && (extension == "jpg" || extension == "JPG" || extension == "jpeg" || extension == "JPEG")) 
            {
                gstreamer_pipeline = "filesrc location=" + image_path + " ! jpegdec ! videoconvert ! videoscale ! video/x-raw, format=BGR ! appsink";
            }
            else if (dotPos != std::string::npos && (extension =="png"|| extension =="PNG"))
            {
                gstreamer_pipeline = "filesrc location=" + image_path + " ! pngdec ! videoconvert ! videoscale ! video/x-raw, format=BGR ! appsink";
            }
            else
            {
                std::cout << "[ERROR] Invalid Input source\n";
                std::cout << "\n[ERROR] Please specify Input Source" << std::endl;
                print_usage_info();
                return -1;
            }
        }
        break;
        default:
        {
            std::cout << "[ERROR] Invalid Input source\n";
            print_usage_info();
            return -1;
        }
    }
    return 0;
}

/*****************************************
* Function Name : check_model_output_data_type
* Description   : function to check model precision
* Arguments     : input_data_type = datatype of expected model input
* Return value  : 0 if success else -1
******************************************/
int8_t check_model_output_data_type(InOutDataType input_data_type)
{
    if (InOutDataType::FLOAT32 == input_data_type)
    {
        /*Do nothing*/
    }
    else if (InOutDataType::FLOAT16 == input_data_type)
    {
        fprintf(stderr, "[ERROR] Input data type : FP16.\n");
        /*If your model input data type is FP16, use std::vector<uint16_t> for reading input data. */
        return -1;
    }
    else
    {
        fprintf(stderr, "[ERROR] Input data type : neither FP32 nor FP16.\n");
        return -1;
    }
    return 0;
}

/*****************************************
* Function Name : mouse_callback
* Description   : callback function of mouseclick
* Arguments     : event = opencv mouse events
*                 x = The x-coordinate of the mouse event.
*                 y = The y-coordinate of the mouse event.
*                 f = opencv flags
*                 data = optional parameter
******************************************/
void mouse_callback(int event, int x, int y, int f, void * data)
{
    bool valid_point = true;
    switch (event)
    {
    case cv::EVENT_LBUTTONDOWN:
        // Start Button
        if(page == 1 && x > middle_bn_x0 && x < middle_bn_x1 && y > middle_bn_y0 && y < middle_bn_y1)
        {
            page = 2;
        }
        // Add Points Button
        if(page == 2 && x > topleft_bn_x0 && x < topleft_bn_x1 && y > topleft_bn_y0 && y < topleft_bn_y1)
        {
            page = 3;
        }
        // Continue Button
        if(page == 2 && x > topright_bn_x0 && x < topright_bn_x1 && y > topright_bn_y0 && y < topright_bn_y1)
        {
            mode = UNET;
            page = 4;
        }
        if(page == 2 && x > min_control_bn_x0 && x < min_control_bn_x1 && y > min_control_bn_y0 && y < min_control_bn_y1)
        {
            meter_min += 10;
        }
        if(page == 2 && x > min_control_bn_x0 && x < min_control_bn_x1 && y > (min_control_bn_y0 + 100) && y < (min_control_bn_y1 + 100))
        {
            meter_min += 1;
        }
        if(page == 2 && x > min_control_bn_x0 && x < min_control_bn_x1 && y > (min_control_bn_y0 + 300) && y < (min_control_bn_y1 + 300))
        {
            meter_min -= 1;
        }
        if(page == 2 && x > min_control_bn_x0 && x < min_control_bn_x1 && y > (min_control_bn_y0 + 400) && y < (min_control_bn_y1 + 400))
        {
            meter_min -= 10;
        }
        if(page == 2 && x > max_control_bn_x0 && x < max_control_bn_x1 && y > max_control_bn_y0 && y < max_control_bn_y1)
        {
            meter_max += 10;
        }
        if(page == 2 && x > max_control_bn_x0 && x < max_control_bn_x1 && y > (max_control_bn_y0 + 100) && y < (max_control_bn_y1 + 100))
        {
            meter_max += 1;
        }
        if(page == 2 && x > max_control_bn_x0 && x < max_control_bn_x1 && y > (max_control_bn_y0 + 300) && y < (max_control_bn_y1 + 300))
        {
            meter_max -= 1;
        }
        if(page == 2 && x > max_control_bn_x0 && x < max_control_bn_x1 && y > (max_control_bn_y0 + 400) && y < (max_control_bn_y1 + 400))
        {
            meter_max -= 10;
        }
        // Reset Button
        if(page == 3 && x > topleft_bn_x0 && x < topleft_bn_x1 && y > topleft_bn_y0 && y < topleft_bn_y1)
        {
            points.clear();
            valid_point = false; 
        }
        // Save Button
        if(page == 3 && points.size() == 3 && x > topright_bn_x0 + 200 && x < topright_bn_x1 + 200 && y > topright_bn_y0 && y < topright_bn_y1)
        {
            page = 4;
            mode = UNET;
            double width_ratio = (double)input_image.cols / DISP_OUTPUT_WIDTH;
            double height_ratio = (double)input_image.rows / DISP_OUTPUT_HEIGHT;
            for(auto& p: points)
            {
                p.x *= width_ratio;
                p.y *= height_ratio;
            }
            min = points[0];
            center = points[1];
            max = points[2];
            valid_point = false;
        }
        if(page == 3 && points.size() < 3 && valid_point)
        {
            points.push_back(cv::Point(x, y));
        }
        break;

    case cv::EVENT_LBUTTONDBLCLK:
        if(page == 2 && x > min_control_bn_x0 && x < max_control_bn_x1 && y > min_control_bn_y0 && y < (max_control_bn_y1 + 400)) break;
        sem_trywait(&terminate_req_sem);
        break;

    default:
        break;
    }
}

/*****************************************
* Function Name : update_points
* Description   : function to check deviation and update min, center, max
******************************************/
void update_points()
{
    for(Detection det: detections)
    {
        if(det.class_id == 0)
        {
            // Center
            if (center == cv::Point(-1, -1) || mode == YOLOX)
            {
                center = det.center;
            }
            else if(std::sqrt(std::pow(center.x - det.center.x, 2) + std::pow(center.y - det.center.y, 2)) < max_deviation)
            {
                center = det.center;
            }
            else
            {
                high_deviation = true;
            }
        } 
        if(det.class_id == 2)
        {
            // max
            if (max == cv::Point(-1, -1) || mode == YOLOX)
            {
                max = det.center;
            }
            else if(std::sqrt(std::pow(max.x - det.center.x, 2) + std::pow(max.y - det.center.y, 2)) < max_deviation)
            {
                max = det.center;
            }
            else
            {
                high_deviation = true;
            }
        }
        if(det.class_id == 3)
        {
            // min
            if (min == cv::Point(-1, -1) || mode == YOLOX)
            {
                min = det.center;
            }
            else if(std::sqrt(std::pow(min.x - det.center.x, 2) + std::pow(min.y - det.center.y, 2)) < max_deviation)
            {
                min = det.center;
            }
            else
            {
                high_deviation = true;
            }
        }
    }
}

/*****************************************
* Function Name : add_performance_data
* Description   : function to display model performance data
* Arguments     : cv::Mat image = input frame
* Return value  : cv::Mat image = output frame
******************************************/
cv::Mat add_performance_data(cv::Mat image)
{
    int32_t verical_space = 0;
    image = create_output_frame(image);
    switch (mode)
    {
    case 1:
        cv::putText(image, "Total AI Time (ms): " + float_to_string(yolox_ai_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 60), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image,"Yolox Detection:", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 100), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_thickness);
        cv::putText(image, "Preprocess  : " + float_to_string(yolox_pre_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 130), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image, "Inference    : " + float_to_string(yolox_ai_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 160), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image, "Postprocess : " + float_to_string(yolox_post_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 190), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image, "Objects Detected : ", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 250), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        for(Detection det: detections)
        {
            if(det.class_id == 1 || det.class_id == 4) continue;
            cv::putText(image, label_file_map[det.class_id] + " " + float_to_string(det.score * 100) + "%", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 280 + verical_space), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
            verical_space += 30;
        }
        break;
    case 2:
        cv::putText(image, "Total AI Time (ms): " + float_to_string(unet_ai_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 60), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image,"Unet Segmentation:", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 100), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_thickness);
        cv::putText(image, "Preprocess  : " + float_to_string(unet_pre_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 130), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image, "Inference    : " + float_to_string(unet_ai_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 160), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image, "Postprocess : " + float_to_string(unet_post_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 190), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image, "Reading : " + float_to_string(meter_value), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 240), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::cvtColor(image, image,cv::COLOR_BGR2BGRA);
        break;
    case 3:
        cv::putText(image, "Total AI Time (ms): " + float_to_string(yolox_ai_time +  unet_ai_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 60), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image,"Yolox Detection:", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 100), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_thickness);
        cv::putText(image, "Preprocess  : " + float_to_string(yolox_pre_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 130), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image, "Inference    : " + float_to_string(yolox_ai_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 160), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image, "Postprocess : " + float_to_string(yolox_post_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 190), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);

        cv::putText(image,"Unet Segmentation:", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 230), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_thickness);
        cv::putText(image, "Preprocess  : " + float_to_string(unet_pre_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 260), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image, "Inference    : " + float_to_string(unet_ai_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 290), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image, "Postprocess : " + float_to_string(unet_post_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 320), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        cv::putText(image, "Reading : " + float_to_string(meter_value), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 370), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);

        cv::putText(image, "Checking Calibration... ", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 600), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
        break;
    default:
        break;
    }
    return image;
}

/*****************************************
* Function Name : add_unet_output
* Description   : function to display unet output
* Arguments     : cv::Mat image = input frame
* Return value  : cv::Mat image = output frame
******************************************/
cv::Mat add_unet_output(cv::Mat image)
{
    cv::Mat unet_mask;
    if(unet_output_ready)
    {
        unet_mtx.lock();
        if (dev_option)
        {
            cv::circle(image, min, 10, GREEN, -1);
            cv::circle(image, center, 10, YELLOW, -1);
            cv::circle(image, max, 10, RED, -1);
            cv::circle(image, tip, 10, BLUE, -1);
        }
        cv::cvtColor(unet_output_mask, unet_mask, cv::COLOR_RGB2BGR);
        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        if (mode != CALIBRATION)
        {
            cv::resize(image, image, cv::Size(DISP_IMAGE_OUTPUT_WIDTH, DISP_IMAGE_OUTPUT_HEIGHT));
            cv::resize(unet_mask, unet_mask, cv::Size(DISP_IMAGE_OUTPUT_WIDTH, DISP_IMAGE_OUTPUT_HEIGHT));
        }
        cv::addWeighted(image, 1.0, unet_mask, 0.5, 0.0, image);
        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        unet_mtx.unlock();
    }
    return image;
}

/*****************************************
* Function Name : add_yolox_output
* Description   : function to display bounding box from yolox
* Arguments     : cv::Mat image = input frame
* Return value  : cv::Mat image = output frame
******************************************/
cv::Mat add_yolox_output(cv::Mat image)
{
    yolox_mtx.lock();
    update_points();
    for(Detection det: detections)
    {
        if(det.class_id == 1 || det.class_id == 4) continue;
        cv::putText(image, label_file_map[det.class_id] + " " + float_to_string(det.score), cv::Point(det.rect.x, det.rect.y - 20), cv::FONT_HERSHEY_SIMPLEX, font_size, BLUE, font_weight);
        cv::rectangle(image, det.rect, GREEN, 1.5);
    }
    yolox_mtx.unlock();
    return image;
}

/*****************************************
* Function Name : R_Main_Process
* Description   : Runs the main process loop
* Arguments     : -
* Return value  : 0 if succeeded
*                 not 0 otherwise
******************************************/
int8_t R_Main_Process()
{
    /*Main Process Variables*/
    int8_t main_ret = 0;
    /*Semaphore Related*/
    int32_t sem_check = 0;
    /*Variable for checking return value*/
    int8_t ret = 0;
    uint32_t middle_img_test_x = 800;
    uint32_t middle_img_test_y = 100;

    cv::Mat bg_image = cv::imread("background_image.jpg");
    cv::resize(bg_image, bg_image, cv::Size(DISP_OUTPUT_WIDTH, DISP_OUTPUT_HEIGHT));
    cv::Mat output_image;
    output_image = bg_image.clone();
    
    
    cv::namedWindow("Analog Reader", cv::WINDOW_NORMAL);
    cv::setWindowProperty("Analog Reader", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    cv::setMouseCallback("Analog Reader", mouse_callback);
    cv::imshow("Analog Reader", output_image);
    
    printf("\n[INFO] Main Loop Starts\n");
    while(1)
    {
        /*Gets the Termination request semaphore value. If different then 1 Termination was requested*/
        errno = 0;
        ret = sem_getvalue(&terminate_req_sem, &sem_check);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Semaphore Value: errno=%d\n", errno);
            goto err;
        }
        /*Checks the semaphore value*/
        if (1 != sem_check)
        {
            goto main_proc_end;
        }
        /* Check img_obj_ready flag which is set in Capture Thread. */
        if (img_obj_ready.load())
        {
            switch (page)
            {
                case 1:
                    output_image = bg_image.clone();
                    cv::putText(output_image, "Position the camera to face the analog meter. Then press ", cv::Point(middle_img_test_x - 280, middle_img_test_y), cv::FONT_HERSHEY_SIMPLEX, 1, RED, 2);
                    cv::putText(output_image, "the start button to configure.", cv::Point(middle_img_test_x - 100, middle_img_test_y + 50), cv::FONT_HERSHEY_SIMPLEX, 1, RED, 2);
                    cv::rectangle(output_image, cv::Point(middle_bn_x0, middle_bn_y0), cv::Point(middle_bn_x1, middle_bn_y1), WHITE, -1);
                    cv::rectangle(output_image, cv::Point(middle_bn_x0, middle_bn_y0), cv::Point(middle_bn_x1, middle_bn_y1), BLACK, 2);
                    cv::putText(output_image, "Start", cv::Point(middle_bn_x0 + 80, middle_bn_y0 + 50), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                    cv::imshow("Analog Reader", output_image);
                    break;
                case 2:
                    high_deviation = false;
                    output_image = yuyv_image;
                    output_image = add_yolox_output(output_image);
                    output_image = add_performance_data(output_image);
                    cv::putText(output_image, "Press 'Continue' if Min, Max, and Center are detected correctly.", cv::Point(middle_img_test_x - 500, middle_img_test_y - 30), cv::FONT_HERSHEY_SIMPLEX, 1, YELLOW, 2);
                    cv::putText(output_image, "Otherwise, press 'Add Points'.", cv::Point(middle_img_test_x - 280, middle_img_test_y + 20), cv::FONT_HERSHEY_SIMPLEX, 1, YELLOW, 2);
                    cv::rectangle(output_image, cv::Point(topleft_bn_x0, topleft_bn_y0), cv::Point(topleft_bn_x1, topleft_bn_y1), WHITE, -1);
                    cv::rectangle(output_image, cv::Point(topleft_bn_x0, topleft_bn_y0), cv::Point(topleft_bn_x1, topleft_bn_y1), BLACK, 2);
                    cv::putText(output_image, "Add Points", cv::Point(topleft_bn_x0 + 30, topleft_bn_y0 + 50), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                    cv::rectangle(output_image, cv::Point(topright_bn_x0, topright_bn_y0), cv::Point(topright_bn_x1, topright_bn_y1), WHITE, -1);
                    cv::rectangle(output_image, cv::Point(topright_bn_x0, topright_bn_y0), cv::Point(topright_bn_x1, topright_bn_y1), BLACK, 2);
                    cv::putText(output_image, "Continue", cv::Point(topright_bn_x0 + 50, topright_bn_y0 + 50), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);

                    cv::putText(output_image, "Meter Range Control", cv::Point(min_control_bn_x0 - 100, min_control_bn_y0 - 40), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
                    // min control
                    cv::rectangle(output_image, cv::Point(min_control_bn_x0, min_control_bn_y0), cv::Point(min_control_bn_x1, min_control_bn_y1), WHITE, -1);
                    cv::putText(output_image, "+10", cv::Point(min_control_bn_x0 + 10, min_control_bn_y0 + 52), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                    cv::rectangle(output_image, cv::Point(min_control_bn_x0, min_control_bn_y0 + 100), cv::Point(min_control_bn_x1, min_control_bn_y1 + 100), WHITE, -1);
                    cv::putText(output_image, "+1", cv::Point(min_control_bn_x0 + 20, min_control_bn_y0 + 152), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                    cv::rectangle(output_image, cv::Point(min_control_bn_x0, min_control_bn_y0 + 200), cv::Point(min_control_bn_x1, min_control_bn_y1 + 200), WHITE, 2);
                    cv::putText(output_image, "Min:", cv::Point(min_control_bn_x0 - 70, min_control_bn_y0 + 252), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
                    cv::putText(output_image, std::to_string(meter_min), cv::Point(min_control_bn_x0 + 25, min_control_bn_y0 + 252), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
                    cv::rectangle(output_image, cv::Point(min_control_bn_x0, min_control_bn_y0 + 300), cv::Point(min_control_bn_x1, min_control_bn_y1 + 300), WHITE, -1);
                    cv::putText(output_image, "-1", cv::Point(min_control_bn_x0 + 20, min_control_bn_y0 + 352), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                    cv::rectangle(output_image, cv::Point(min_control_bn_x0, min_control_bn_y0 + 400), cv::Point(min_control_bn_x1, min_control_bn_y1 + 400), WHITE, -1);
                    cv::putText(output_image, "-10", cv::Point(min_control_bn_x0 + 10, min_control_bn_y0 + 452), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                    // max control
                    cv::rectangle(output_image, cv::Point(max_control_bn_x0, max_control_bn_y0), cv::Point(max_control_bn_x1, max_control_bn_y1), WHITE, -1);
                    cv::putText(output_image, "+10", cv::Point(max_control_bn_x0 + 10, max_control_bn_y0 + 52), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                    cv::rectangle(output_image, cv::Point(max_control_bn_x0, max_control_bn_y0 + 100), cv::Point(max_control_bn_x1, max_control_bn_y1 + 100), WHITE, -1);
                    cv::putText(output_image, "+1", cv::Point(max_control_bn_x0 + 20, max_control_bn_y0 + 152), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                    cv::rectangle(output_image, cv::Point(max_control_bn_x0, max_control_bn_y0 + 200), cv::Point(max_control_bn_x1, max_control_bn_y1 + 200), WHITE, 2);
                    cv::putText(output_image, "Max:", cv::Point(max_control_bn_x0 - 80, max_control_bn_y0 + 252), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
                    cv::putText(output_image, std::to_string(meter_max), cv::Point(max_control_bn_x0 + 20, max_control_bn_y0 + 252), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
                    cv::rectangle(output_image, cv::Point(max_control_bn_x0, max_control_bn_y0 + 300), cv::Point(max_control_bn_x1, max_control_bn_y1 + 300), WHITE, -1);
                    cv::putText(output_image, "-1", cv::Point(max_control_bn_x0 + 20, max_control_bn_y0 + 352), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                    cv::rectangle(output_image, cv::Point(max_control_bn_x0, max_control_bn_y0 + 400), cv::Point(max_control_bn_x1, max_control_bn_y1 + 400), WHITE, -1);
                    cv::putText(output_image, "-10", cv::Point(max_control_bn_x0 + 10, max_control_bn_y0 + 452), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                    cv::putText(output_image, "Double click to exit!", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, DISP_IMAGE_OUTPUT_HEIGHT - 40), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
                    cv::imshow("Analog Reader", output_image);
                    break;
                case 3:
                    output_image = yuyv_image; 
                    cv::resize(output_image, output_image, cv::Size(DISP_OUTPUT_WIDTH, DISP_OUTPUT_HEIGHT));
                    cv::rectangle(output_image, cv::Point(topleft_bn_x0, topleft_bn_y0), cv::Point(topleft_bn_x1, topleft_bn_y1), WHITE, -1);
                    cv::rectangle(output_image, cv::Point(topleft_bn_x0, topleft_bn_y0), cv::Point(topleft_bn_x1, topleft_bn_y1), BLACK, 2);
                    cv::putText(output_image, "Reset", cv::Point(topleft_bn_x0 + 80, topleft_bn_y0 + 50), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                    switch (points.size())
                    {
                        case 0:
                            cv::putText(output_image, "Click on Min Reading", cv::Point(middle_img_test_x, middle_img_test_y), cv::FONT_HERSHEY_SIMPLEX, 1, RED, 2);
                            break;
                        case 1:
                            cv::circle(output_image, points[0], 10, GREEN, -1);
                            cv::putText(output_image, "Click on Needle Center", cv::Point(middle_img_test_x, middle_img_test_y), cv::FONT_HERSHEY_SIMPLEX, 1, RED, 2);
                            break;
                        case 2:
                            cv::circle(output_image, points[0], 10, GREEN, -1);
                            cv::circle(output_image, points[1], 10, YELLOW, -1);
                            cv::putText(output_image, "Click on Max Reading", cv::Point(middle_img_test_x, middle_img_test_y), cv::FONT_HERSHEY_SIMPLEX, 1, RED, 2);
                            break;
                        case 3:
                            cv::circle(output_image, points[0], 10, GREEN, -1);
                            cv::circle(output_image, points[1], 10, YELLOW, -1);
                            cv::circle(output_image, points[2], 10, RED, -1);
                            cv::putText(output_image, "Click on Save", cv::Point(middle_img_test_x, middle_img_test_y), cv::FONT_HERSHEY_SIMPLEX, 1, RED, 2);
                            cv::rectangle(output_image, cv::Point(topright_bn_x0 + 200, topright_bn_y0), cv::Point(topright_bn_x1 + 200, topright_bn_y1), WHITE, -1);
                            cv::rectangle(output_image, cv::Point(topright_bn_x0 + 200, topright_bn_y0), cv::Point(topright_bn_x1 + 200, topright_bn_y1), BLACK, 2);
                            cv::putText(output_image, "Save", cv::Point(topright_bn_x0 + 280, topright_bn_y0 + 50), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2);
                            break;
                        default:
                            break;
                    }
                    cv::imshow("Analog Reader", output_image);
                    break;
                case 4:
                    output_image = yuyv_image;
                    output_image = add_unet_output(output_image);
                    output_image = add_performance_data(output_image);
                    cv::putText(output_image, "Double click to exit!", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, DISP_IMAGE_OUTPUT_HEIGHT - 40), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
                    cv::imshow("Analog Reader", output_image);
                    break;
                case 5:
                    output_image = yuyv_image;
                    output_image = add_unet_output(output_image);
                    output_image = add_yolox_output(output_image);
                    output_image = add_performance_data(output_image);
                    if (high_deviation) 
                    {
                        cv::putText(output_image, "Warning", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 640), cv::FONT_HERSHEY_SIMPLEX, font_size, RED, font_weight);
                        cv::putText(output_image, "Calibration required", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 680), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
                    }
                    else
                    {
                        cv::putText(output_image, "Calibration not required ", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 640), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
                    }
                    cv::putText(output_image, "Double click to exit!", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, DISP_IMAGE_OUTPUT_HEIGHT - 40), cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
                    cv::imshow("Analog Reader", output_image);
                    break;
                default:
                    break;
            }
            cv::waitKey(1);
            img_obj_ready.store(0);
        }
        /*Wait for 1 TICK.*/
        usleep(WAIT_TIME);
    }

/*Error Processing*/
err:
    sem_trywait(&terminate_req_sem);
    main_ret = 1;
    goto main_proc_end;
/*Main Processing Termination*/
main_proc_end:
    /*To terminate the loop in Capture Thread.*/
    img_obj_ready.store(0);
    printf("[INFO] Main Process Terminated\n");
    return main_ret;
}

/*****************************************
* Function Name : add_performance_data
* Description   : function to display model performance data
* Arguments     : argc = command argument count
*               : argv = command 
* Return value  : 0 if succeeded
*                 -1 otherwise
******************************************/
int8_t check_command_arguments(int32_t argc, char * argv[])
{
    /* Check the input source is valid.*/
    if (argc < 2)
    {
        return -1;
    }
    else
    {
        std::string input_source = argv[1];
        if ((input_source == "USB" || input_source == "MIPI") && argc >= 2)
            return 0;
        else if((input_source == "IMAGE"|| input_source == "VIDEO") && argc >= 3)
            return 0;
        else
            return -1;
    }
    return -1;
}


int32_t main(int32_t argc, char * argv[])
{
    int8_t main_proc = 0;
    int8_t ret_main = 0;
    int8_t ret = 0;

    /*Multithreading Variables*/
    int32_t create_thread_ai = -1;
    int32_t create_thread_key = -1;
    int32_t create_thread_capture = -1;
    int32_t sem_create = -1;

    std::map<std::string, std::string> args;
    bool runtime_status = false;
    std::string gstreamer_pipeline;
    int8_t drpai_fd;
    InOutDataType input_data_type;
    /* Set drpai mem start address */
    uint64_t drpaimem_addr_start = 0;
    
    /*Disable OpenCV Accelerator due to the use of multithreading */
    unsigned long OCA_list[16];
    for(int8_t i = 0; i < 16; i++) OCA_list[i] = 0;
    OCA_Activate(&OCA_list[0]);
    
    ret = check_command_arguments(argc, argv);
    if (0 != ret)
    {
        std::cout << "\n[ERROR] Please specify proper argument/Input Source" << std::endl;
        print_usage_info();
        printf("[INFO] End Application.\n");
        return -1;
    }
    
    ret = get_gstreamer_pipeline(argv, gstreamer_pipeline);
    if (0 != ret)
    {
        ret_main = -1;
        goto end_main;
    }

    /* Parse input arguments */
    for (int8_t i = 1; i < argc; ++i) 
    {
        std::string arg = argv[i];
        size_t pos = arg.find('=');
        if (pos != std::string::npos) 
        {
            std::string key = arg.substr(0, pos);
            std::string value = arg.substr(pos + 1);
            args[key] = value;
        }
    }

    /* DRP-AI Frequency Setting */
    if (args.find("--drpai_freq") != args.end() && std::stoi(args["--drpai_freq"]) <= 127 && std::stoi(args["--drpai_freq"]) > 0)
        drpai_freq = stoi(args["--drpai_freq"]);
    else 
        drpai_freq = DRPAI_FREQ;
    std::cout<<"\n[INFO] DRPAI FREQUENCY : "<<drpai_freq<<"\n";

    print_application_info();

    if (args.find("--dev_mode") != args.end() && args["--dev_mode"]=="true")
        dev_option = true;
        
    if (args.find("--meter_min") != args.end())
        meter_min = stoi(args["--meter_min"]);
    else 
        meter_min = 0;
    
    if (args.find("--meter_max") != args.end() && std::stoi(args["--meter_max"]) > 0)
        meter_max = stoi(args["--meter_max"]);
    else 
        meter_max = 6;

    /* DRP Loading */
    drpai_fd = open("/dev/drpai0", O_RDWR);
    if (0 > drpai_fd)
    {
        std::cerr << "[ERROR] Failed to open DRP-AI Driver : errno=" << errno << std::endl;
        ret_main = -1;
        goto end_main;
    }

    /*Load model_dir structure and its weight to runtime object */
    drpaimem_addr_start = init_drpai(drpai_fd);
   
    if ((uint32_t)NULL == drpaimem_addr_start) 
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address.\n");
        goto end_main;
    }

    runtime_status = runtime_yolox.LoadModel(yolox_model_dir, drpaimem_addr_start + DRPAI_MEM_OFFSET);

    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load yolox model.\n");
        goto end_main;
    }

    runtime_status = runtime_unet.LoadModel(unet_model_dir, drpaimem_addr_start);

    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load unet model.\n");
        goto end_main;
    }

    /*Get input data */
    input_data_type = runtime_yolox.GetInputDataType(0);
    ret = check_model_output_data_type(input_data_type);
    if (0 != ret)
    {
        ret_main = -1;
        goto end_main;
    }

    input_data_type = runtime_unet.GetInputDataType(0);
    ret = check_model_output_data_type(input_data_type);
    if (0 != ret)
    {
        ret_main = -1;
        goto end_main;
    }

    /*Termination Request Semaphore Initialization*/
    /*Initialized value at 1.*/
    sem_create = sem_init(&terminate_req_sem, 0, 1);
    if (0 != sem_create)
    {
        fprintf(stderr, "[ERROR] Failed to Initialize Termination Request Semaphore.\n");
        ret_main = -1;
        goto end_threads;
    }

    /*Create Inference Thread*/
    create_thread_ai = pthread_create(&inf_thread, NULL, R_Inf_Thread, NULL);
    if (0 != create_thread_ai)
    {
        sem_trywait(&terminate_req_sem);
        fprintf(stderr, "[ERROR] Failed to create AI Inference Thread.\n");
        ret_main = -1;
        goto end_threads;
    }

    /* Create Capture Thread */
    create_thread_capture = pthread_create(&capture_thread, NULL, R_Capture_Thread, (void *) &gstreamer_pipeline);
    if (0 != create_thread_capture)
    {
        sem_trywait(&terminate_req_sem);
        fprintf(stderr, "[ERROR] Failed to create Capture Thread.\n");
        ret_main = -1;
        goto end_threads;
    }

    /* Create Key Hit Thread */
    create_thread_key = pthread_create(&kbhit_thread, NULL, R_Kbhit_Thread, NULL);
    if (0 != create_thread_key)
    {
        fprintf(stderr, "[ERROR] Failed to create Key Hit Thread.\n");
        ret_main = -1;
        goto end_threads;
    }

    /* Main Processing */
    main_proc = R_Main_Process();
    if (0 != main_proc)
    {
        fprintf(stderr, "[ERROR] Error during Main Process\n");
        ret_main = -1;
    }
    goto end_threads;

end_threads:
    if(0 == create_thread_capture)
    {
        ret = wait_join(&capture_thread, CAPTURE_TIMEOUT);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to exit Capture Thread on time.\n");
            ret_main = -1;
        }
    }
    if (0 == create_thread_ai)
    {
        ret = wait_join(&inf_thread, AI_THREAD_TIMEOUT);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to exit AI Inference Thread on time.\n");
            ret_main = -1;
        }
    }
    if (0 == create_thread_key)
    {
        ret = wait_join(&kbhit_thread, EXIT_THREAD_TIMEOUT);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to exit Key Hit Thread on time.\n");
            ret_main = -1;
        }
    }

    /* Delete Terminate Request Semaphore */
    if (0 == sem_create)
    {
        sem_destroy(&terminate_req_sem);
    }
    goto end_close_drpai;
end_close_drpai:
    /*Close DRP-AI Driver.*/
    if (0 < drpai_fd)
    {
        errno = 0;
        ret = close(drpai_fd);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to close DRP-AI Driver: errno=%d\n",errno);
            ret_main = -1;
        }
    }
    goto end_main;

end_main:
    printf("[INFO] End Application.\n");
    return ret_main;
}
