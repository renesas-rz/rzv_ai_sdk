#include <thread>
#include <linux/drpai.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "define.h"
#include "common/box.h"
#include "common/MeraDrpRuntimeWrapper.h"
#include "common/date_chck_module/date_check.h"
#include "common/regex_module/regex_function.h"
#include "common/tess_module/TesseractEngine.h"
#include "common/text_proc_module/TextProc.h"
#include "common/utils/common_utils.h"
#include "common/comm_define.h"
#include "image_processing.h"

/* Brings the entire standard C++ library into the current scope */
using namespace std;

/* AI Inference for DRPAI*/
/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper model_inf_runtime;

/* Connected devises object */

/* Global variables */
unsigned int out;
uint32_t out_size_arr;
std::vector<float> floatarr(1);
static vector<detection> det;
static DateChecker date_checker;
static float drpai_output_buf[INF_OUT_SIZE];

/* Global variables to update time */
static float pre_time           = 0;
static float post_time          = 0;
static float ai_inference_time  = 0;
static float ai_time            = 0;

/* Global frame */
cv::Mat frame_g;
/* Create Display frame */
cv::Mat disp_frame;

/* Creates a global variable "g_cap" of type */ 
/* for capturing camera source */ 
cv::VideoCapture g_cap;

/* flags to detect image mode*/
bool g_image_mode           = false;
/* flag for detecting double click*/
bool doubleClick = false;

bool imageMode = false;
/* To fill the extracted date variable*/
static unordered_map<int, date_struct> date_struc_map;

/*Variable for Regex Dict */
static map<boost::regex, string> regex_dict_g;

/*Remaining Days Shown*/
static bool rem_days_shown = false ;

/* Queue to store captured frames from valid input source */
std::queue<cv::Mat> frame_queue;

/* Map to store input source list */
std::map<std::string, int> input_source_map =
{
    {"IMAGE", 1},
    {"MIPI",  2},
    {"USB",   3}
};

/*****************************************
 * Function Name    : mouse_callback_button_click
 * Description      : Callback function to exit on mouse double click
 * Arguments        : Default opencv formats for callbacks
 * Return value     : -
 *****************************************/
void mouse_callback_button_click(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDBLCLK)
    {
        std::cout << "[INFO] Double Tap !!\n";
        doubleClick = true;
    }
}

/*****************************************
 * Function Name : pre_process
 * Description   : Preprocess the global frame and return the processed local frame
 * Return value  : cv::Mat imageCHW
 ******************************************/
cv::Mat pre_process(void)
{
    /* Temp frame */
    cv::Mat frame;

    /*resize the image to the model input size*/
    cv::Size size(MODEL_IN_H, MODEL_IN_W);
    
    /* collect first frame from queue */
    frame = frame_queue.front();
    frame_g = frame;
    frame_queue.pop();

    /*src , dest, size*/
    cv::resize(frame, frame, size);

    /* Transposed matrix */
    cv ::Mat imageCHW;

    imageCHW = hwc2chw(frame);

    /*convert to FP32*/
    imageCHW.convertTo(imageCHW, CV_32FC3);

    /* divide */
    cv::divide(imageCHW, 255.0, imageCHW);

    /* DRP AI input image should be continuous buffer */
    if (!imageCHW.isContinuous())
        imageCHW = imageCHW.clone();
    /* return CHW frame */
    return imageCHW;
}

/*****************************************
 * Function Name : get_result from the DRP-AI output
 * Description   : Get DRP-AI Output from memory via DRP-AI Driver
 * Return value  : 0 if succeeded
 *                 not 0 otherwise
 ******************************************/
int8_t get_result(void)
{
    int8_t ret = 0;
    int32_t i = 0;
    int32_t output_num = 0;
    std::tuple<InOutDataType, void *, int64_t> output_buffer;
    int64_t output_size;
    uint32_t size_count = 0;

    /* Get the number of output of the target model. */
    output_num = model_inf_runtime.GetNumOutput();
    size_count = 0;
    /*GetOutput loop*/
    for (i = 0; i < output_num; i++)
    {
        /* output_buffer below is tuple, which is { data type, address of output data, number of elements } */
        output_buffer = model_inf_runtime.GetOutput(i);
        /*Output Data Size = std::get<2>(output_buffer). */
        output_size = std::get<2>(output_buffer);

        /*Output Data Type = std::get<0>(output_buffer)*/
        if (InOutDataType::FLOAT16 == std::get<0>(output_buffer))
        {
            /*Output Data = std::get<1>(output_buffer)*/
            uint16_t *data_ptr = reinterpret_cast<uint16_t *>(std::get<1>(output_buffer));
            for (int j = 0; j < output_size; j++)
            {
                /*FP16 to FP32 conversion*/
                drpai_output_buf[j + size_count] = float16_to_float32(data_ptr[j]);
            }
        }
        else if (InOutDataType::FLOAT32 == std::get<0>(output_buffer))
        {
            /*Output Data = std::get<1>(output_buffer)*/
            float *data_ptr = reinterpret_cast<float *>(std::get<1>(output_buffer));
            for (int j = 0; j < output_size; j++)
            {
                drpai_output_buf[j + size_count] = data_ptr[j];
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
 * Function Name : drpai_inference
 * Description   : Run inference of frame on drp-cores
 * Arguments     : cv::Mat frame 
 * Return value  : int ret
 ******************************************/
int drpai_inference(cv::Mat& frame)
{
    /*start inference using drp runtime*/
    model_inf_runtime.SetInput(0, frame.ptr<float>());
    model_inf_runtime.Run();
    /*load inference out on drpai_out_buffer*/
    int ret = get_result();
    return ret;
}

/*****************************************
 * Function Name : R_Post_Proc
 * Description   : Process CPU post-processing for YOLOv3
 * Arguments     : floatarr = drpai output address
 * Return value  : -
 ******************************************/
void R_Post_Proc(float *floatarr)
{
    /* Following variables are required for correct_region_boxes in Darknet implementation*/
    /* Note: This implementation refers to the "darknet detector test" */
    float new_w, new_h;
    float correct_w = 1.;
    float correct_h = 1.;
    if ((float)(MODEL_IN_W / correct_w) < (float)(MODEL_IN_H / correct_h))
    {
        new_w = (float)MODEL_IN_W;
        new_h = correct_h * MODEL_IN_W / correct_w;
    }
    else
    {
        new_w = correct_w * MODEL_IN_H / correct_h;
        new_h = MODEL_IN_H;
    }

    int32_t n = 0;
    int32_t b = 0;
    int32_t y = 0;
    int32_t x = 0;
    int32_t offs = 0;
    int32_t i = 0;
    float tx = 0;
    float ty = 0;
    float tw = 0;
    float th = 0;
    float tc = 0;
    float center_x = 0;
    float center_y = 0;
    float box_w = 0;
    float box_h = 0;
    float objectness = 0;
    uint8_t num_grid = 0;
    uint8_t anchor_offset = 0;
    float classes[NUM_CLASS];
    float max_pred = 0;
    int32_t pred_class = -1;
    float probability = 0;
    detection d;
    /* Clear the detected result list */
    det.clear();

    /*Post Processing Start*/
    for (n = 0; n < NUM_INF_OUT_LAYER; n++)
    {
        num_grid = num_grids[n];
        anchor_offset = 2 * NUM_BB * (NUM_INF_OUT_LAYER - (n + 1));

        for (b = 0; b < NUM_BB; b++)
        {
            for (y = 0; y < num_grid; y++)
            {
                for (x = 0; x < num_grid; x++)
                {
                    offs = yolo_offset(n, b, y, x);
                    /*Fetch Bounding BBox params and objectness_score [4+1] associated with each BB from the model output*/
                    tx = floatarr[offs];
                    ty = floatarr[yolo_index(n, offs, 1)];
                    tw = floatarr[yolo_index(n, offs, 2)];
                    th = floatarr[yolo_index(n, offs, 3)];
                    tc = floatarr[yolo_index(n, offs, 4)];

                    /* Compute the bounding box */
                    /*get_region_box*/
                    center_x = ((float)x + sigmoid(tx)) / (float)num_grid;
                    center_y = ((float)y + sigmoid(ty)) / (float)num_grid;

                    box_w = (float)exp(tw) * anchors[anchor_offset + 2 * b + 0] / (float)MODEL_IN_W;
                    box_h = (float)exp(th) * anchors[anchor_offset + 2 * b + 1] / (float)MODEL_IN_W;
                    /* Adjustment for VGA size */
                    /* correct_region_boxes */
                    center_x = (center_x - (MODEL_IN_W - new_w) / 2. / MODEL_IN_W) / ((float)new_w / MODEL_IN_W);
                    center_y = (center_y - (MODEL_IN_H - new_h) / 2. / MODEL_IN_H) / ((float)new_h / MODEL_IN_H);
                    box_w *= (float)(MODEL_IN_W / new_w);
                    box_h *= (float)(MODEL_IN_H / new_h);

                    /* BB params wrt to actual height and width of input image */
                    center_x = round(center_x * DRPAI_IN_WIDTH);
                    center_y = round(center_y * DRPAI_IN_HEIGHT);
                    box_w = round(box_w * DRPAI_IN_WIDTH);
                    box_h = round(box_h * DRPAI_IN_HEIGHT);

                    objectness = sigmoid(tc);

                    BBox bb = {center_x, center_y, box_w, box_h};

                    /* Get the class prediction associated with each BB  [5: ] */
                    for (i = 0; i < NUM_CLASS; i++)
                    {
                        classes[i] = sigmoid(floatarr[yolo_index(n, offs, 5 + i)]);
                    }

                    max_pred = 0;
                    pred_class = -1;
                    /*Get the predicted class */
                    for (i = 0; i < NUM_CLASS; i++)
                    {
                        if (classes[i] > max_pred)
                        {
                            pred_class = i;
                            max_pred = classes[i];
                        }
                    }

                    /* Store the result into the list if the probability is more than the threshold */
                    probability = max_pred * objectness;
                    if (probability > TH_PROB)
                    {
                        d = {bb, pred_class, probability};
                        det.push_back(d);
                    }
                }
            }
        }
    }
    /* Non-Maximum Suppression filter */
    filter_boxes_nms(det, det.size(), TH_NMS);
    return;
}

/*****************************************
 * Function Name : date_extraction 
 * Description   : Extract date from the image and store the date on the map
 * Arguments     : -
 * Return value  : -
 ******************************************/
void date_extraction(void)
{
    /* clear the previous frames detected date */
    date_struc_map.clear();

    string processed_text;

    ymd_struct result_struc;
    date_struct ret_date_struc;
    /* indx i is the number of objects detected on each frame */
    for (int i = 0; i < det.size(); i++)
    {
        /* skipping overlapped bounding boxes */
        if (det[i].prob == 0)
        {
            continue;
        }
        /* Skipping the bounding boxes for other classes than class 0 [i.e. date]*/
        if (det[i].c != 0)
        {
            continue;
        }

        /* skipping if height or width is zero */
        if (((int)det[i].bbox.h == 0) || ((int)det[i].bbox.w == 0))
        {
            continue;
        }

        /*Get the cropped image */
        cv::Mat crop_img = get_crop_gray(frame_g, (int)det[i].bbox.x, (int)det[i].bbox.y,
                                         (int)det[i].bbox.w, (int)det[i].bbox.h);
        /* Resize when height < 32 */
        cv::Mat process_img = resize_gray_image(crop_img, MIN_CROP_HEIGHT);

        /*Run the Tesseract Engine*/
        /* Get the initialized Tesseract engine instance */
        TesseractEngine &tesseract = TesseractEngine::getInstance();

        /* Use the initialized Tesseract engine for processing */
        tesseract::TessBaseAPI &tess_ocr_engine = tesseract.getEngine();

        tess_ocr_engine.SetImage(process_img.data, process_img.cols, process_img.rows, 1, process_img.step);

        tess_ocr_engine.SetSourceResolution(TESS_IMG_RESOLUTION);

        /* Perform OCR and retrieve the recognized text */

        char *recognizedText = tess_ocr_engine.GetUTF8Text();
        /*Remove trailing and leading white spaces */
        processed_text = trim_white_spc(recognizedText); 
        cout<< "Detected String :"<< processed_text << endl;
        /*check for empty string*/
        if (processed_text.length() >= 1)
        {
            result_struc = get_yymmddd(regex_dict_g,processed_text);
            if (!result_struc.matched)
            {
                stringstream stream;
                stream<< "Detected '"<< processed_text << "' does not match any format !!" ;
                std::string result = stream.str();
                cout<< result<< endl;
            }
            else
            {
                cout << "The string '" << processed_text << "' match the format " << result_struc.format<< endl;
                /*Fill the date structure for printing*/
                ret_date_struc.txt_extr = processed_text;
                ret_date_struc.year = result_struc.year;
                ret_date_struc.month = result_struc.month;
                ret_date_struc.day = result_struc.day;

                cout << "Year : " << result_struc.year << " Month : " << result_struc.month << " Day: " << result_struc.day<<endl;
                
                /* If Remaining day calculation is required*/
                if (rem_days_shown)
                {
                    /* Calculate remaining days */
                    int day_rem = date_checker.calculate_days_left (result_struc.year, result_struc.month, result_struc.day);
                    cout<< "Days Remaining "<< day_rem <<endl;
                    /* store in the structure */
                    ret_date_struc.remaining_days = day_rem ;
                }

                /*Store the print result on the map */
                date_struc_map[i] = ret_date_struc;
            }

        }

        /*free up the memory and clear the image from the tesseract*/
        delete[] recognizedText;
        tesseract.clear();
    }
}

/*****************************************
 * Function Name : draw_bounding_box
 * Description   : Draw bounding box on image.
 * Arguments     : cv::Mat frame
 * Return value  : cv::Mat frame
 ******************************************/
cv::Mat draw_bounding_box(cv::Mat frame)
{
    stringstream stream;
    string result_str;
    /* Draw bounding box on RGB image. */
    int32_t i = 0;
    for (i = 0; i < det.size(); i++)
    {
        /* Skip the overlapped bounding boxes */
        if (det[i].prob == 0)
        {
            continue;
        }

        /* Clear string stream for bounding box labels */
        stream.str("");
        /* Draw the bounding box on the image */
        stream << fixed << setprecision(2) << det[i].prob;
        result_str = label_file_map[det[i].c] + " " + stream.str();

        int32_t x_min = (int)det[i].bbox.x - round((int)det[i].bbox.w / 2.);
        int32_t y_min = (int)det[i].bbox.y - round((int)det[i].bbox.h / 2.);
        int32_t x_max = (int)det[i].bbox.x + round((int)det[i].bbox.w / 2.) - 1;
        int32_t y_max = (int)det[i].bbox.y + round((int)det[i].bbox.h / 2.) - 1;

        /* Check the bounding box is in the image range */
        x_min = x_min < 1 ? 1 : x_min;
        x_max = ((DRPAI_IN_WIDTH - 2) < x_max) ? (DRPAI_IN_WIDTH - 2) : x_max;
        y_min = y_min < 1 ? 1 : y_min;
        y_max = ((DRPAI_IN_HEIGHT - 2) < y_max) ? (DRPAI_IN_HEIGHT - 2) : y_max;

        cv::Point topLeft(x_min, y_min);
        cv::Point bottomRight(x_max, y_max);

        /* Creating bounding box and class labels */
        cv::rectangle(frame, topLeft, bottomRight, CV_BLACK, CHAR_SCALE_LARGE);

        /* Create a rectangle for the background */
        cv::Rect back_rect(x_min, y_min-8, x_max - x_min, 8);
        cv::rectangle(frame, back_rect, CV_BLACK, -1); // -1 thickness fills the rectangle

        cv::putText(frame, result_str, topLeft, CV_FONT, CHAR_SCALE_XS, CV_WHITE, CHAR_THICKNESS);
    }
    return frame;
}

/*****************************************
 * Function Name : print_result
 * Description   : print the result on the frame. 
 * Arguments     : cv::Mat frame
 * Return value  : cv::Mat frame
 ******************************************/
cv::Mat print_result(cv::Mat& frame)
{
    std::string text = "Double Click to exit the Application!!";
    stringstream stream;
    string str = "";
    int32_t result_cnt = 0;

    uint32_t x = IMAGE_OUTPUT_WIDTH + 10;
    uint32_t y = 175;

    string ymd_string = "";

    /* Add total inference AI-time into the output frame */
    cv::putText(frame, "Total AI Time [ms] : " + std::to_string((int)ai_time), cv::Point(x + 10, 55), CV_FONT,
                CHAR_SCALE_LARGE, CV_WHITE, CHAR_THICKNESS_OUT);
    /* Add total inference Infernce-time into the output frame */
    cv::putText(frame,"Infernce : "+ std::to_string((int)ai_inference_time), cv::Point(x+30, 85), CV_FONT, 
                    CHAR_SCALE_SMALLER, CV_WHITE, CHAR_THICKNESS);
    /* Add total inference PreProcess-time into the output frame */
    cv::putText(frame,"PreProcess : "+ std::to_string((int)pre_time), cv::Point(x+30, 110), CV_FONT, 
                    CHAR_SCALE_SMALLER, CV_WHITE, CHAR_THICKNESS);
    /* Add total inference PostProcess-time into the output frame */
    cv::putText(frame,"PostProcess : "+ std::to_string((int)post_time), cv::Point(x+30, 135), CV_FONT, 
                    CHAR_SCALE_SMALLER, CV_WHITE, CHAR_THICKNESS);
    /* For detected classes  */
    for (int i = 0; i < det.size(); i++)
    {
        /* Skip the overlapped bounding boxes */
        if (det[i].prob == 0)
            continue;

        /* Increment count of the detected objects in a frame */
        result_cnt++;

        /* Clear string stream for bounding box labels */
        stream.str("");

        /* Create bounding box label of class */
        label_file_map[det[i].c].erase(std::remove_if(label_file_map[det[i].c].begin(), label_file_map[det[i].c].end(), ::isspace), label_file_map[det[i].c].end());
        stream << "Class : " << label_file_map[det[i].c].c_str() << " " << round(det[i].prob * 100) << "%";
        str = stream.str();
        y = LINE_HEIGHT*result_cnt;

        cv::putText(frame, str, cv::Point(x+30, 175 + i*25), CV_FONT, 
                    CHAR_SCALE_SMALL, CV_WHITE, CHAR_THICKNESS_OUT);
   
        /* If the detected class is date and the index is stored in the formatted string */
        if (det[i].c == 0 && (date_struc_map.find(i) != date_struc_map.end()))
        {   
            cv::Scalar color = CV_WHITE ;
            for (int ymd = 1; ymd<5; ymd++)
            {
                y += LINE_HEIGHT;
                stream.str("");
                switch (ymd)
                {
                    case (1):
                        stream<<"Day : "<< date_struc_map[i].day; 
                    break;
                    case (2):
                        stream<<"Month : "<< date_struc_map[i].month;
                    break;
                    case (3):
                        stream<<"Year : "<< date_struc_map[i].year;
                    break;
                    case (4):
                        /* If Remaining day display is required*/
                        if (rem_days_shown)
                        {
                            if (date_struc_map[i].remaining_days == -1 )
                            {
                                stream<<"Date Expired !!";
                                color = CV_RED;
                            }
                            else 
                            {
                                stream <<"Remaining Days: "<< date_struc_map[i].remaining_days;
                                color = CV_GREEN ;
                            }  
                        }
                    break;
                default:
                    break;
                }
                cv::putText(frame, stream.str(), cv::Point(x+10, 250 + ymd*27), CV_FONT, CHAR_SCALE_SMALL, color, CHAR_THICKNESS_OUT);
            }
        }
    }
    unsigned int winWidth = frame.cols;
    unsigned int winHeight =frame.rows;
    cv::Size text_size = cv::getTextSize(text,cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, 0);
    cv::Point text_pos(winWidth - text_size.width - 10, winHeight - 10);
    cv::putText(frame, text, text_pos, cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_WHITE, 1, cv::LINE_AA);
    return frame;
}

/*****************************************
 * Function Name : date_extraction_on_frame
 * Description   : This function is the main entry point for the date extraction pipeline. 
 *                 It takes an input frame, performs preprocessing, inference, postprocessing, 
 *                 and date extraction.
 * Return value  : int  "0 if succeeded"
 *                      "not 0 otherwise"
 ******************************************/
int date_extraction_on_frame(void)
{   
    /* Preprocess start time */
    auto t5 = std::chrono::high_resolution_clock::now();
    cv::Mat frame = pre_process();
    /* Preprocess end time */
    auto t6 = std::chrono::high_resolution_clock::now();
    pre_time = std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t5).count();
    std::cout << "\n[INFO] Pre-Process Time(ms): " << pre_time << " ms\n";
    int ret = 0;

    /* Inference start time */
    auto t1 = std::chrono::high_resolution_clock::now();

    ret = drpai_inference(frame);

    if (ret != 0)
    {
        fprintf(stderr, "[Error] DRP Inference Not working !!! ");
        return -1;
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    ai_inference_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "\n[INFO] AI-Inference Time(ms): " << ai_inference_time << " ms\n";
   
   /* Do post process to get adequate boxes */
    R_Post_Proc(drpai_output_buf);
    auto t3 = std::chrono::high_resolution_clock::now();
    post_time = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
    std::cout << "[INFO] Post-Process Time(ms): "<< post_time << " ms\n";

    ai_time = pre_time + post_time + ai_inference_time;
    std::cout<<"[INFO] Total AI Time(ms): "<< ai_time <<"ms\n";
    
    /* Extract Date information */
    date_extraction();
    auto t4 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();
    std::cout << "[INFO] Date-Extraction Time(ms): "<< duration << " ms\n";

    return 0;
}

/*****************************************
 * Function Name    : create_output_frame
 * Description      : create the output frame with space for displaying inference details
 * Arguments        : cv::Mat frame_g, input frame to be displayed in the background
 * Return value     : cv::Mat background, final display frame to be written to gstreamer pipeline
 *****************************************/
cv::Mat create_output_frame(cv::Mat frame)
{
    /* Create a black background image of size 1080x720 */
    cv::Mat background(DISP_OUTPUT_HEIGHT, DISP_OUTPUT_WIDTH,CV_8UC3, cv::Scalar(0, 0, 0));
    /* Resize the original image to fit within 960x720 */
    cv::Mat resizedImage;
    cv::resize(frame, resizedImage, cv::Size(IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT));
    /* Copy the resized image to the left side of the background (0 to 960) */
    cv::Rect roi(cv::Rect(0, 0, resizedImage.cols, resizedImage.rows));
    resizedImage.copyTo(background(roi));
    return background;
}

/*****************************************
* Function Name : get_drpai_start_addr
* Description   : Function to get the start address of DRPAImem.
* Arguments     : -
* Return value  : uint32_t = DRPAImem start address in 32-bit.
******************************************/
uint32_t get_drpai_start_addr(void)
{
    int fd  = 0;
    int ret = 0;
    drpai_data_t drpai_data;

    errno = 0;

    fd = open("/dev/drpai0", O_RDWR);
    if (0 > fd )
    {
        LOG(FATAL) << "[ERROR] Failed to open DRP-AI Driver : errno=" << errno;
        return (uint32_t)NULL;
    }

    /* Get DRP-AI Memory Area Address via DRP-AI Driver */
    ret = ioctl(fd , DRPAI_GET_DRPAI_AREA, &drpai_data);
    if (-1 == ret)
    {
        LOG(FATAL) << "[ERROR] Failed to get DRP-AI Memory Area : errno=" << errno ;
        return (uint32_t)NULL;
    }

    return drpai_data.address;
}

/*****************************************
 * Function Name : camera_thread
 * Description   : This function continuously captures frames from the connected camera 
 *                 and adds them to a frame queue. 
 ******************************************/
void camera_thread(void)
{
    /* Camera capture frame */
    cv::Mat frame_c;
    /* frame inter val count to limit frame*/
    unsigned int interval_count = 0; 
    /* Taking an everlasting loop to show the output */
    while (true && doubleClick == false)
    {
        g_cap.read(frame_c);
        interval_count++;
        /* Breaking the loop if no video frame is detected */
        if (frame_c.empty())
        {
            std::cout << "[INFO] Video ended or corrupted frame !\n";
            return;
        }
        else
        {   /* Limit frames */
            if(interval_count == 2)
            {
                /* Resize to fixed height and width*/
                cv::resize(frame_c, frame_c, cv::Size(IMAGE_WIDTH, IMAGE_HEIGHT));
                /* Push captured frame int frame queue */
                if (frame_queue.size()<100)
                    frame_queue.push(frame_c);
                interval_count = 0;
            }
        }
    }
}

/******************************************
 * Function Name : capture_frame
 * Description   : function to open camera or video source with respect to the source pipeline.
 * Arguments     : string cap_pipeline input source pipeline
 * Return value  : int  "0 if succeeded"
 *                      "not 0 otherwise"
 ******************************************/
int capture_frame(std::string cap_pipeline,std::string input_source)
{
    /* Camera capture frame */
    cv::Mat frame_c;
    /* Capture stream of frames from camera using Gstreamer pipeline */
    g_cap.open(cap_pipeline, cv::CAP_GSTREAMER);
    if (!g_cap.isOpened())
    {
        /* This section prompt an error message if no video stream is found */
        std::cout << "[ERROR] Error opening "<< input_source <<" source!!\n"
                  << std::endl;
        return -1;
    }
    else
    {
        if(input_source == "MIPI" || input_source == "USB")
        {
            std::thread camera_start(camera_thread);
            camera_start.detach();
        }
        else
        {
            g_cap.read(frame_c);
            if (frame_c.empty())
            {
                std::cout << "[INFO] Video ended or corrupted frame !\n";
                return -1;
            }
            else
            {
                /* Resize to fixed height and width*/
                cv::resize(frame_c, frame_c, cv::Size(IMAGE_WIDTH, IMAGE_HEIGHT));
                /* Push captured frame int frame queue */
                if (frame_queue.size()<100)
                    frame_queue.push(frame_c);
                return 0;
            }
        }
    }
    return 0;
}

/******************************************
 * Function Name : process_frames
 * Description   : This function processes frames from the frame queue, 
 *                 performs date extraction, draws bounding boxes, 
 *                 and displays the output frame..
 ******************************************/
void process_frames(void)
{
    /* Output frame */
    cv::Mat frame_out; 
    while(true)
    {
        if(frame_queue.empty())
        {
            /* Check for whether a double click has occurred. */
            if(doubleClick == true)
                break;
            continue;
        }
        else
        {
            /* Do date extraction the resized image file */
            int ret = date_extraction_on_frame();
            if (ret != 0)
            {
                fprintf(stderr, "[Error] Inference Not working !!! ");
                return;
            }
            if(!frame_g.empty())
            {
                /* Draw bounding box on the frame */
                frame_out = draw_bounding_box(frame_g);
                disp_frame = create_output_frame(frame_out);
                /* Print result on the frame */
                disp_frame = print_result(disp_frame);
                cv::namedWindow("Date Extraction", cv::WINDOW_NORMAL);
                cv::setWindowProperty("Date Extraction", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
                cv::setMouseCallback("Date Extraction", mouse_callback_button_click);
                cv::imshow("Date Extraction", disp_frame);
                cv::waitKey(10);
            }
        }
        if(imageMode)
            break;
        /* Check for whether a double click has occurred. */
        if(doubleClick == true)
        {
            cv::destroyAllWindows();
            doubleClick = false;
            g_image_mode = false;
            break;
        }
    }
}

/*****************************************
 * Function Name : query_device_status
 * Description   : function to check USB/MIPI device is connectod.
 * Return value  : media_port, media port that device is connectod.
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
            /* return media port*/
            return media_port;
        }
    }
    pclose(pipe);
    /* return media port*/
    return media_port;
}

/*****************************************
 * Function Name : mipi_cam_init
 * Description   : function to open camera or video source with respect to the source pipeline.
 ******************************************/
void mipi_cam_init(void)
{
    int ret = 0;
    std::cout << "[INFO] MIPI CAM Init \n";
    const char *commands[4] =
        {
            "media-ctl -d /dev/media0 -r",
            "media-ctl -d /dev/media0 -V \"\'ov5645 0-003c\':0 [fmt:UYVY8_2X8/640x480 field:none]\"",
            "media-ctl -d /dev/media0 -l \"\'rzg2l_csi2 10830400.csi2\':1 -> \'CRU output\':0 [1]\"",
            "media-ctl -d /dev/media0 -V \"\'rzg2l_csi2 10830400.csi2\':1 [fmt:UYVY8_2X8/640x480 field:none]\""};

    /* media-ctl command */
    for (int i = 0; i < 4; i++)
    {
        std::cout << commands[i] << "\n";
        ret = system(commands[i]);
        std::cout << "system ret = " << ret << "\n";
        if (ret < 0)
        {
            std::cout << "[ERROR]" << __func__ << ": failed media-ctl commands. index = " << i << "\n";
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    bool runtime_status             = false;
    bool errorHandle                = false;
    uint64_t drpaimem_addr_start    = 0;

    /* Gstreamer input pipeline*/
    std::string gstreamer_pipeline;
    std::cout << "Date-Extraction Application Start" << std::endl;
    
    /* Check the input source is valid.*/
    if (argc < 2) 
    {
        errorHandle = true;
    }
    else if(argc == 3 || argc == 4)
    {
        std::string input_source = argv[1];
        if(input_source == "IMAGE" && argc == 4)
        {
            std::string remainDay = argv[3];
            if (remainDay == "-rem")
                rem_days_shown = true;
            else
            {
                errorHandle = true;
            }
            
        }
        else if ((input_source == "MIPI" || input_source == "USB") && argc == 3)
        {
            std::string remainDay = argv[2];
            if (remainDay == "-rem")
                rem_days_shown = true;
            else
            {
                errorHandle = true;
            }
        }
        else if ((input_source == "MIPI" || input_source == "USB") && argc == 4)
        {
            errorHandle = true;
        }
    }
    else if(argc == 2 )
    {
        std::string input_source = argv[1];
        if (input_source == "MIPI" || input_source == "USB");
        else
        {
            errorHandle = true;
        }   
    }
    else
    {
        errorHandle = true;
    }

    if (errorHandle)
    {
        std::cout << "\n[ERROR] Please specify Input Source" << std::endl;
        std::cout << "[INFO] usage: ./date_extraction MIPI|USB|IMAGE [Input_file for IMAGE] -rem[Optional]" << std::endl;
        std::cout << "\n[INFO] End Application\n";
        return -1;
    }

        /* initialize tesseract engine */
        TesseractEngine &tesseract = TesseractEngine::getInstance();
    /* create regex dictionary from regex module functions */
    regex_dict_g = create_regex_dict();
    /* Load Label from label_list file */
    label_file_map = load_label_file(label_list);
    /*Load model_dir structure and its weight to runtime object */
    drpaimem_addr_start = get_drpai_start_addr();
    if (drpaimem_addr_start == (uint64_t)NULL)
    {
        /* Error notifications are output from function get_drpai_start_addr(). */
	    fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address. \n");
        return -1;
    }
    /*Load model */
    runtime_status = model_inf_runtime.LoadModel(model_dir, drpaimem_addr_start + DRPAI_MEM_OFFSET);
    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load model. \n");
        return -1;
    } 
    /* Get the valid input source */
    std::string input_source = argv[1];
    switch (input_source_map[input_source])
    {
        /* Input Source : Image */
        case 1:
        {
            std::cout << "[INFO] Image \n";
            g_image_mode = true;
            /* read input image */
            std::string image_path = argv[2];
            /* gstremer pipeline to read input image source */
            gstreamer_pipeline = "filesrc location=" + image_path + " ! jpegdec ! videoconvert ! appsink";
            int ret = capture_frame(gstreamer_pipeline,input_source);
            imageMode = true;
            if(ret == 0)
                process_frames();
            while (doubleClick == false)
            {
                cv::namedWindow("Date Extraction", cv::WINDOW_NORMAL);
                cv::setWindowProperty("Date Extraction", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
                cv::setMouseCallback("Date Extraction", mouse_callback_button_click);
                cv::imshow("Date Extraction", disp_frame);
                cv::waitKey(10);
            }
        }
        break;
        /* Input Source : MIPI Camera */
        case 2:
        {
            std::cout << "[INFO] MIPI CAMERA \n";
            mipi_cam_init();
            /* check the status of device */
            std::string media_port = query_device_status("CRU");
            /* gstremer pipeline to read input image source */
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
            int ret = capture_frame(gstreamer_pipeline,input_source);
            if(ret == 0)
                process_frames();
        }
        break;
        /* Input Source : USB Camera */
        case 3:
        {
            std::cout << "[INFO] USB CAMERA \n";
            /* check the status of device */
            std::string media_port = query_device_status("usb");
            /* gstremer pipeline to read input image source */
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
            int ret = capture_frame(gstreamer_pipeline,input_source);
            if(ret == 0)
                process_frames();
        }
        break;
        /* default case */
        default:
        {
            std::cout << "[ERROR] Invalid Input source\n";
        }
        break;
    }
    /* End Application */
    std::cout << "\n[INFO] Application End\n";
    return 0;
}
