#include <iostream>
#include <cctype>
#include <opencv2/opencv.hpp>

#include "regex_module/regex_function.h"
#include "text_module/text_processing.h"
#include "tess_module/TesseractEngine.h"
#include <mutex>
#include "MeraDrpRuntimeWrapper.h"
#include <builtin_fp16.h>
#include <fstream>
#include <string>
#include <sys/time.h>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <glob.h>
#include <cmath>

#include <sys/types.h>

#include "define.h"
#include "box.h"

using namespace std;

/*AI Inference for DRPAI*/
/* DRP-AI TVM[*1] Runtime object */

MeraDrpRuntimeWrapper model_inf_runtime;

/*Global Variables*/
static float drpai_output_buf[INF_OUT_SIZE];

unsigned int out;
uint32_t out_size_arr;
std::vector<float> floatarr(1);

static std::mutex mtx;

static int DRPAI_IN_WIDTH;
static int DRPAI_IN_HEIGHT;
static vector<detection> det;

cv::Mat frame_g;
cv::VideoCapture cap;

/**/
static unordered_map<int, date_struct> date_struc_map;

/*Variable for Regex Dict */
static map<boost::regex, string> regex_dict_g;

struct bb
{
    int xmin;
    int ymin;
    int xmax;
    int ymax;
};

cv::Mat processImage(const cv::Mat &inputImg, int resizeHeight, bool gray_rqd)
{
    cv::Mat grayImg, resizedImg, claheThreshImg, filteredImg, thresholdImg;

    // Convert to grayscale
    //

    if (gray_rqd)
    {
        cv::cvtColor(inputImg, grayImg, cv::COLOR_BGR2GRAY);
    }
    else
    {
        grayImg = inputImg;
    }

    if (inputImg.rows < resizeHeight)
    {
        // Resize to specified height while maintaining aspect ratio
        double aspectRatio = (double)inputImg.cols / (double)inputImg.rows;
        int resizeWidth = (int)(resizeHeight * aspectRatio);
        cv::resize(grayImg, resizedImg, cv::Size(resizeWidth, resizeHeight), 0, 0, cv::INTER_CUBIC);
    }
    else
    {
        resizedImg = grayImg;
    }

    // Apply CLAHE (Adaptive Histogram Equalzn)to enhance contrast
    // cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    // clahe->setClipLimit(1);
    // clahe->setTilesGridSize(cv::Size(4, 2));
    // clahe->apply(resizedImg, claheThreshImg);

    // Apply median blur with filter size 3
    // cv::medianBlur(claheThreshImg, filteredImg, 3);

    // Apply adaptive threshold
    // cv::adaptiveThreshold(filteredImg, thresholdImg, 255,
    //                       cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, resizeHeight - 1, 7);

    cv::adaptiveThreshold(grayImg, thresholdImg, 255,
                          cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, resizeHeight - 1, 7);

    return thresholdImg;
}

bb run_model(cv::Mat frame)
{
    bb bound;
    bound.xmin = 487;
    bound.ymin = 357;
    bound.xmax = 604;
    bound.ymax = 374;

    return bound;
}

// std::string date_extract_single_frame(cv::Mat& frame, tesseract::TessBaseAPI &tess_ocr)
std::string date_extract_single_frame(cv::Mat &frame)
{

    mtx.lock();
    // Get the initialized Tesseract engine instance
    TesseractEngine &tesseract = TesseractEngine::getInstance();

    // Use the initialized Tesseract engine for processing
    tesseract::TessBaseAPI &tess_ocr = tesseract.getEngine();

    // Save the current PSM value
    tesseract::PageSegMode savedPSM = tess_ocr.GetPageSegMode();

    // Print the current PSM value
    std::cout << "Current PSM: " << savedPSM << std::endl;

    // Restore the saved PSM value
    tess_ocr.SetPageSegMode(savedPSM);

    // Get the current OCR Engine Mode (OEM) value
    tesseract::OcrEngineMode oem = tess_ocr.oem();

    // Print the OEM value
    std::cout << "Current OEM: " << oem << std::endl;

    printf("Image props : %d %d %d\n", frame.cols, frame.rows, frame.step);
    /* add the image */
    tess_ocr.SetImage(frame.data, frame.cols, frame.rows, 1, frame.step);

    // set resolution in dpi
    int resolution = 330;
    tess_ocr.SetSourceResolution(resolution);

    // Perform OCR and retrieve the recognized text
    char *recognizedText = tess_ocr.GetUTF8Text();

    std::string processedText = trim_white_spc(recognizedText);

    mtx.unlock();
    return processedText;
}

/*****************************************
 * Function Name     : float16_to_float32
 * Description       : Function by Edgecortex. Cast uint16_t a into float value.
 * Arguments         : a = uint16_t number
 * Return value      : float = float32 number
 ******************************************/
float float16_to_float32(uint16_t a)
{
    return __extendXfYf2__<uint16_t, uint16_t, 10, float, uint32_t, 23>(a);
}

// std::string get_inference_on_frame(cv::Mat frame, tesseract::TessBaseAPI &tess_ocr)
std::string get_inference_on_frame(cv::Mat frame)
{
    cv::Mat process_frame;

    /* pre-process  img*/
    // cv::Resize()
    /* get output from runtime */

    /* check the float output */

    /* do float conversion */

    /* post process the output */

    /* load the model */

    /* crop the image */

    /* pre-processing*/

    // cv::imshow("Original", frame);
    // cv::waitKey(5000);

    // process_frame=processImage(frame, 32, false);
    process_frame = frame;
    // cv::imshow("Processed",process_frame);
    // cv::waitKey(5000);

    /* pass the cropped image to tesseract */

    // std::string return_char = date_extract_single_frame(process_frame, tess_ocr);
    std::string return_char = date_extract_single_frame(process_frame);
    return return_char;
}

// void show_result(const std::map<boost::regex, std::string> &regex_dict, std::string processedText)
// {
//     ymd_struct ret_result;
//     if (processedText.length() >= 1)
//     {
//         std::cout << "Text Extracted:'" << processedText << "'" << std::endl;

//         ret_result = get_yymmddd(regex_dict, processedText);

//         if (ret_result.matched)
//         {
//             std::cout << "Matched with format: " << ret_result.format << std::endl;
//             std::cout << "Year: " << ret_result.year;
//             std::cout << " Month: " << ret_result.month;
//             std::cout << " Day: " << ret_result.day << std::endl;
//         }
//         else
//         {
//             std::cout << "No appropriate date-format found for '" << processedText << "'" << std::endl;
//         }
//     }
//     else
//     {
//         std::cout << "No Text Detected" << std::endl;
//     }
// }

// cv::Mat display_bb_on_frame(cv::Mat& frame,bb bound){
//     //cv::rectangle(frame,(),())
// }

/*****************************************
 * Function Name     : load_label_file
 * Description       : Load label list text file and return the label list that contains the label.
 * Arguments         : label_file_name = filename of label list. must be in txt format
 * Return value      : vector<string> list = list contains labels
 *                     empty if error occurred
 ******************************************/
vector<string> load_label_file(string label_file_name)
{
    vector<string> list = {};
    vector<string> empty = {};
    ifstream infile(label_file_name);

    if (!infile.is_open())
    {
        return list;
    }

    string line = "";
    while (getline(infile, line))
    {
        list.push_back(line);
        if (infile.fail())
        {
            return empty;
        }
    }

    return list;
}

/*****************************************
 * Function Name : sigmoid
 * Description   : Helper function for YOLO Post Processing
 * Arguments     : x = input argument for the calculation
 * Return value  : sigmoid result of input x
 ******************************************/
double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

/*****************************************
* Function Name : yolo_index
* Description   : Get the index of the bounding box attributes based on the input offset
* Arguments     : n = output layer number
                  offs = offset to access the bounding box attributes
*                 channel = channel to access each bounding box attribute.
* Return value  : index to access the bounding box attribute.
******************************************/
int32_t yolo_index(uint8_t n, int32_t offs, int32_t channel)
{
    uint8_t num_grid = num_grids[n];
    return offs + channel * num_grid * num_grid;
}

/*****************************************
* Function Name : yolo_offset
* Description   : Get the offset number to access the bounding box attributes
*                 To get the actual value of bounding box attributes, use yolo_index() after this function.
* Arguments     : n = output layer number [0~2].
                  b = Number to indicate which bounding box in the region [0~4]
*                 y = Number to indicate which region [0~13]
*                 x = Number to indicate which region [0~13]
* Return value  : offset to access the bounding box attributes.
******************************************/
int32_t yolo_offset(uint8_t n, int32_t b, int32_t y, int32_t x)
{

    uint8_t num = num_grids[n];
    uint32_t prev_layer_num = 0;
    int32_t i = 0;

    for (i = 0; i < n; i++)
    {
        prev_layer_num += NUM_BB * (NUM_CLASS + 5) * num_grids[i] * num_grids[i];
    }
    return prev_layer_num + b * (NUM_CLASS + 5) * num * num + y * num + x;
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
int8_t get_result()
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

void start_runtime(float *input)
{
    /*Set Pre-processing output to be inference input. */
    model_inf_runtime.SetInput(0, input);
    model_inf_runtime.Run();

    int ret = get_result();

    if (ret != 0)
    {
        fprintf(stderr, "[Error] Inference Not working !!! ");
    }
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
    mtx.lock();
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
                    /*Fetch Bounding Bbox params and objectness_score [4+1] associated with each BB from the model output*/
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

                    // printf("XYWHC%f %f %f %f %f \n", center_x, center_y, box_w, box_h, objectness);

                    Bbox bb = {center_x, center_y, box_w, box_h};

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
                    // printf("Probability: %0.2f\n", probability);
                    if (probability > TH_PROB)
                    {
                        d = {bb, pred_class, probability};
                        det.push_back(d);
                    }
                }
            }
        }
    }

    // printf(" Size in post: %d \n", det.size());
    /* Non-Maximum Suppression filter */
    filter_boxes_nms(det, det.size(), TH_NMS);
    mtx.unlock();
    return;
}

cv::Mat get_crop_gray(cv::Mat& frame, int32_t x_center, int32_t y_center, int32_t width, int32_t height)
{
    
    /* xmin, ymin extraction and stretching */
    int32_t x_min = x_center - round(width / 2.) - CROP_IMG_STRETCH;
    int32_t y_min = y_center - round(height / 2.) - CROP_IMG_STRETCH;

    width = width + (CROP_IMG_STRETCH)*2; 
    height = height + (CROP_IMG_STRETCH)*2; 

    /* Check the rectangle box is in the image range */
    x_min = x_min < 0 ? 0 : x_min;
    y_min = y_min < 0 ? 0 : y_min;
    width = x_min + width  < (DRPAI_IN_WIDTH ) ? width   : DRPAI_IN_WIDTH ;
    height = y_min + height < (DRPAI_IN_HEIGHT ) ? height : DRPAI_IN_HEIGHT;

    /*Define the region of interest (ROI) using a rectangle */
    cv::Rect roi(x_min, y_min, width, height);

    /*Extract the cropped region from the color image */
    cv::Mat cropped_image = frame(roi);

    /*Convert BGRA image to grayscale */
    cv::Mat grayscale_image;
    cv::cvtColor(cropped_image, grayscale_image, cv::COLOR_BGRA2GRAY);

    return grayscale_image;
}

cv::Mat resize_gray_image(const cv::Mat &input_img, int32_t resize_height)
{
    cv::Mat resized_img;

    // Resize to specified height while maintaining aspect ratio
    if (input_img.rows < resize_height)
    {

        double aspect_ratio = (double)input_img.cols / (double)input_img.rows;
        int resize_width = (int)(resize_height * aspect_ratio);
        cv::resize(input_img, resized_img, cv::Size(resize_width, resize_height), 0, 0, cv::INTER_CUBIC);

        return resized_img;
    }
    else
    {
        return input_img;
    }
}

void date_extraction()
{
    mtx.lock();

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

        /*Run the Tesseract Engine*/

        // cv::imshow("cropped image ", crop_img);
        // cv::waitKey(3000);

        /* add the image */
        // printf("Img prop %d %d %d \n", crop_img.cols, crop_img.rows, crop_img.step);

        /* Resize when height < 32 */
        cv::Mat process_img = resize_gray_image(crop_img, MIN_CROP_HEIGHT);

        // cv::imshow("process", process_img);
        // cv::waitKey(2000);

        // Get the initialized Tesseract engine instance
        TesseractEngine &tesseract = TesseractEngine::getInstance();

        // Use the initialized Tesseract engine for processing
        tesseract::TessBaseAPI &tess_ocr_engine = tesseract.getEngine();

        tess_ocr_engine.SetImage(process_img.data, process_img.cols, process_img.rows, 1, process_img.step);
        // printf("Img prop process %d %d %d \n", process_img.cols, process_img.rows, process_img.step);
        // printf("image set\n");

        tess_ocr_engine.SetSourceResolution(TESS_IMG_RESOLUTION);

        /* Perform OCR and retrieve the recognized text */

        char *recognizedText = tess_ocr_engine.GetUTF8Text();

        cout<<"Detected length : "<< strlen(recognizedText)<<endl;

        /*Remove trailing and leading white spaces */
        processed_text = trim_white_spc(recognizedText);
 
        cout<< "Detected String :"<< processed_text << endl;

        /*check for empty string*/
        if (processed_text.length() >= 1)
        {
            result_struc = get_yymmddd(regex_dict_g, processed_text);


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

                /*Store the print result on the map */
                date_struc_map[i] = ret_date_struc;
            }

        }

        /*free up the memory and clear the image from the tesseract*/
        delete[] recognizedText;
        tesseract.clear();
    }

    mtx.unlock();
}

/*****************************************
 * Function Name : draw_bounding_box
 * Description   : Draw bounding box on image.
 * Arguments     : -
 * Return value  : 0 if succeeded
 *               not 0 otherwise
 ******************************************/
void draw_bounding_box(void)
{
    stringstream stream;
    string result_str;
    mtx.lock();
    /* Draw bounding box on RGB image. */
    int32_t i = 0;
    // printf(" Size in func: %d \n", det.size());
    for (i = 0; i < det.size(); i++)
    {
        // printf("Det conf %0.2f and size %d \n", det[i].prob, det.size());
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

        /*Define the region of interest (ROI) using a rectangle */
        cv::Rect roi(x_min, y_min, x_max - x_min, y_max - y_min);

        /*Extract the cropped region from the color image */
        cv::Mat cropped_image = frame_g(roi);

        cv::rectangle(frame_g, topLeft, bottomRight, cv::Scalar(0, 255, 0), 2);
        cv::putText(frame_g, result_str, topLeft, cv::FONT_HERSHEY_SIMPLEX, CHAR_SCALE_SMALL, cv::Scalar(0,255,0),CHAR_THICKNESS-1);
    }
    mtx.unlock();
    return;
}


void write_string_rgb(std::string str, uint32_t x, uint32_t y, float scale, uint32_t color)
{

    uint8_t thickness = CHAR_THICKNESS;
    /*Extract RGB information*/
    uint8_t r = (color >> 16) & 0x0000FF;
    uint8_t g = (color >> 8) & 0x0000FF;
    uint8_t b = color & 0x0000FF;
    
    /*Color must be in BGR order*/
    //cv::putText(bgra_image, str.c_str(), cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, scale, cv::Scalar(b, g, r), thickness);
    cv::putText(frame_g, str, cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, scale, cv::Scalar(b, g, r), thickness);
    return;
}


void print_result()
{
    mtx.lock();

    stringstream stream;
    string str = "";
    int32_t result_cnt = 0;

    uint32_t draw_offset_x = 0;
    uint32_t y= 10;

    string ymd_string = "";
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
        stream << "Class "<< ":" << label_file_map[det[i].c].c_str() << " " << round(det[i].prob * 100) << "%";
        str = stream.str();
        y = LINE_HEIGHT*result_cnt;
        write_string_rgb(str, draw_offset_x, y, CHAR_SCALE_SMALL, WHITE_DATA);
        

        /* If the detected class is date and the index is stored in the formatted string */
        if (det[i].c == 0 && (date_struc_map.find(i) != date_struc_map.end()))
        {
            /* Print YYMMDD separate */

            /*Text at point(x,y) */
            /* point(y)-> */
            // int32_t y = (LINE_HEIGHT * TIME_LINE_NUM) + LINE_HEIGHT_OFFSET + (result_cnt * LINE_HEIGHT);

            cout<<str<<endl;
            for (int ymd = 1; ymd<4; ymd++)
            {
                y += LINE_HEIGHT;
                stream.str("");

                switch (ymd)
                {
                case (1):
                    stream<<"Year: "<< date_struc_map[i].year;
                    break;
                case (2):
                    stream<<"Month: "<< date_struc_map[i].month;
                    break;
                case (3):
                    stream<<"Day: "<< date_struc_map[i].day;
                    break;
                default:
                    break;
                }

                write_string_rgb(stream.str(), draw_offset_x, y, CHAR_SCALE_SMALL, WHITE_DATA);
            }

        }
        
    }

    mtx.unlock();
    return;
}

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

int run_inference()
{   
    cv::Mat frame;
    // float *output;
    auto t1 = std::chrono::high_resolution_clock::now();

    cv::Size size(MODEL_IN_H, MODEL_IN_W);
    /*resize the image to the model input size*/

    /*src , dest, size*/
    cv::resize(frame_g, frame, size);

    cv ::Mat imageCHW;
    // cv::transpose(frame, imageCHW);//
    imageCHW = hwc2chw(frame);
    // cv::flip(imageCHW, imageCHW, 0);

    /*convert to FP32*/
    imageCHW.convertTo(imageCHW, CV_32FC3);

    /* divide */

    // frame/=255.0;
    cv::divide(imageCHW, 255.0, imageCHW);
    // cv::normalize(imageCHW,imageCHW, 0, 1, cv::NORM_MINMAX, CV_32FC3);
    // cv::imshow("out1", frame);
    // cv::waitKey(5000);

    if (!imageCHW.isContinuous())
        imageCHW = imageCHW.clone();

    /*start inference using drp runtime*/
    // output = start_runtime(frame.ptr<float>());
    // cv::imshow("out1", frame);
    // cv::waitKey(5000);
    // start_runtime(frame.ptr<float>());

    // std::cout<< imageCHW<<endl;

    model_inf_runtime.SetInput(0, imageCHW.ptr<float>());
    model_inf_runtime.Run();

    // /*load inference out on drpai_out_buffer*/
    int ret = get_result();

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "\nAI-Inference Time(ms): " << duration << " ms\n";
   
   
    R_Post_Proc(drpai_output_buf);
    auto t3 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
    std::cout << "Post-Process Time(ms): "<< duration << " ms\n";

    date_extraction();
    auto t4 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();
    std::cout << "Date-Extraction Time(ms): "<< duration << " ms\n";

    draw_bounding_box();
    print_result();

    return 0;
}

int main(int argc, char *argv[])
{
    std::cout << "Date-Extraction Application Start" << std::endl;

    // initialize tesseract engine
    TesseractEngine &tesseract = TesseractEngine::getInstance();

    // create regex dictionary from regex module functions
    regex_dict_g = create_regex_dict();

    /*Load Label from label_list file*/
    label_file_map = load_label_file(label_list);

    /*Load the model */
    model_inf_runtime.LoadModel(model_dir);


    cv::Mat image;
    std::cout << "Mode is: " << argv[1] << std::endl;
    std::string inp_mode = argv[1];
    if (inp_mode == "IMAGE")
    {
        std::cout << "image_path: " << argv[2] << std::endl;
        // read frame
        frame_g = cv::imread(argv[2]);

        cv::resize(frame_g, frame_g, cv::Size(640, 480));

        // DRPAI_IN_WIDTH = frame_g.cols;
        // DRPAI_IN_HEIGHT = frame_g.rows;

        DRPAI_IN_WIDTH = 640;
        DRPAI_IN_HEIGHT = 480;

        if (frame_g.empty())
        {
            std::cout << "Failed to load image!" << std::endl;
            return -1;
        }
        else
        {
            // cv::imshow("output", frame_g);
            // cv::waitKey(5000);
            int ret = run_inference();

            if (ret != 0)
            {
                fprintf(stderr, "[Error] Inference Not working !!! ");
                return -1;
            }

            cv::imshow("output", frame_g);
            cv::waitKey(5000);
        }

        // if (image.empty())
        // {
        //     std::cout << "Failed to load image!" << std::endl;
        //     return -1;

        // } else{
        //     cv::Mat grayscale;
        //     cv::cvtColor(image, grayscale, cv::COLOR_BGR2GRAY);
        //     // std::string text_extracted = get_inference_on_frame(grayscale, tess_ocr);
        //     std::string text_extracted = get_inference_on_frame(grayscale);
        //     show_result(regex_dict, text_extracted);
        // }
    }
    else
    {
        std::cout << "No suitable running mode specified" << std::endl;
    }

    return 0;
}
