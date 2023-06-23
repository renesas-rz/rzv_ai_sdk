#include "define.h"
#include "../common/box.h"
#include "../common/MeraDrpRuntimeWrapper.h"
#include "image_proc/image_processing.h"
#include "../common/date_chck_module/date_check.h"
#include "../common/regex_module/regex_function.h"
#include "../common/tess_module/TesseractEngine.h"
#include "../common/text_proc_module/TextProc.h"
#include "../common/utils/common_utils.h"
#include "../common/comm_define.h"


using namespace std;

/* AI Inference for DRPAI*/
/* DRP-AI TVM[*1] Runtime object */

MeraDrpRuntimeWrapper model_inf_runtime;

/*Global Variables*/
static float drpai_output_buf[INF_OUT_SIZE];

unsigned int out;
uint32_t out_size_arr;
std::vector<float> floatarr(1);


static std::mutex mtx;
static vector<detection> det;

static DateChecker date_checker;
/*Global frame */
cv::Mat frame_g;
cv::VideoCapture cap;

/* To fill the extracted date variable*/
static unordered_map<int, date_struct> date_struc_map;

/*Variable for Regex Dict */
static map<boost::regex, string> regex_dict_g;


/**
 * @brief Preprocess the global frame and return the processed local frame
 * 
 * @return cv::Mat 
 */
cv::Mat pre_process(){
    /* Temp frame */
    cv::Mat frame;

    cv::Size size(MODEL_IN_H, MODEL_IN_W);
    /*resize the image to the model input size*/

    /*src , dest, size*/
    cv::resize(frame_g, frame, size);

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

    return imageCHW;
}

/*****************************************
 * Function Name : get_result from the DRP-AI output
 * Description   : Get DRP-AI Output from memory via DRP-AI Driver
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

/**
 * @brief Run inference of frame on drp-cores
 * 
 * @param frame 
 * @return int 
 */
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

    /* Non-Maximum Suppression filter */
    filter_boxes_nms(det, det.size(), TH_NMS);
    mtx.unlock();
    return;
}

/*****************************************
 * Function Name : date_extraction 
 * Description   : Extract date from the image and store the date on the map
 * Arguments     : -
 * Return value  : -
 ******************************************/
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

        /* Resize when height < 32 */
        cv::Mat process_img = resize_gray_image(crop_img, MIN_CROP_HEIGHT);

        /*Run the Tesseract Engine*/
        // Get the initialized Tesseract engine instance
        TesseractEngine &tesseract = TesseractEngine::getInstance();

        // Use the initialized Tesseract engine for processing
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
                
                /* If Remaining day calculation is required*/
                #ifdef REM_DAY_DISP_OFF
                /* do nothing */
                #else
                /* Calculate remaining days */
                int day_rem = date_checker.calculate_days_left (result_struc.year, result_struc.month, result_struc.day);
                cout<< "Days Remaining "<< day_rem <<endl;
                /* store in the structure */
                ret_date_struc.remaining_days = day_rem ;
                #endif
                

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
        // cv::Rect roi(x_min, y_min, x_max - x_min, y_max - y_min);

        // /*Extract the cropped region from the color image */
        // cv::Mat cropped_image = frame_g(roi);

        /* Creating bounding box and class labels */
        cv::rectangle(frame_g, topLeft, bottomRight, CV_BLACK, CHAR_SCALE_SMALL);

        

        /* Create a rectangle for the background */
        cv::Rect back_rect(x_min, y_min-8, x_max - x_min, 8);
        cv::rectangle(frame_g, back_rect, CV_BLACK, -1); // -1 thickness fills the rectangle

        cv::putText(frame_g, result_str, topLeft, CV_FONT, CHAR_SCALE_XS, CV_WHITE, CHAR_THICKNESS);
    }
    mtx.unlock();
    return;
}


/**
 * @brief print the result on the frame 
 * 
 */
cv::Mat print_result(cv::Mat& frame)
{
    mtx.lock();

    stringstream stream;
    string str = "";
    int32_t result_cnt = 0;

    uint32_t x = IMAGE_OUTPUT_WIDTH;
    uint32_t y = 2;

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
        stream << "Class: " << label_file_map[det[i].c].c_str() << " " << round(det[i].prob * 100) << "%";
        str = stream.str();
        y = LINE_HEIGHT*result_cnt;

        cv::putText(frame, str, cv::Point(x, y), CV_FONT, 
                    CHAR_SCALE_SMALL, CV_WHITE, CHAR_THICKNESS);
   
        /* If the detected class is date and the index is stored in the formatted string */
        if (det[i].c == 0 && (date_struc_map.find(i) != date_struc_map.end()))
        {   cv::Scalar color = CV_WHITE ; 
            
            for (int ymd = 1; ymd<5; ymd++)
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
                case (4):
                    /* If Remaining day display is required*/
                    #ifdef REM_DAY_DISP_OFF // do nothing
                        break;
                    #else 
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
                        break; 
                    #endif
                default:
                    break;
                }

                cv::putText(frame, stream.str(), cv::Point(x, y), CV_FONT, CHAR_SCALE_SMALL, color, CHAR_THICKNESS);
   
            }

        }
        
    }

    mtx.unlock();
    return frame;
}




/**
 * @brief run inference on global frame, get the 
 * 
 * @return int 
 */
int date_extraction_on_frame()
{   
    cv::Mat frame = pre_process();
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
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "\nAI-Inference Time(ms): " << duration << " ms\n";
   
   /* Do post process to get adequate boxes */
    R_Post_Proc(drpai_output_buf);
    auto t3 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
    std::cout << "Post-Process Time(ms): "<< duration << " ms\n";
    
    /* Extract Date information */
    date_extraction();
    auto t4 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();
    std::cout << "Date-Extraction Time(ms): "<< duration << " ms\n";

    return 0;
}

cv::Mat create_output_frame()
{
    /* Create a black background image of size 1080x720 */
    cv::Mat background(DISP_OUTPUT_HEIGHT, DISP_OUTPUT_WIDTH, frame_g.type(), cv::Scalar(0, 0, 0));

    /* Resize the original image to fit within 960x720 */
    cv::Mat resizedImage;
    cv::resize(frame_g, resizedImage, cv::Size(IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT));

    /* Copy the resized image to the left side of the background (0 to 960) */
    cv::Rect roi(cv::Rect(0, 0, resizedImage.cols, resizedImage.rows));
    resizedImage.copyTo(background(roi));
    
    return background;
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


    std::cout << "Image_path: " << argv[1] << std::endl;
    // read frame
    frame_g = cv::imread(argv[1]);

    /* Resize to fixed height and width*/
    cv::resize(frame_g, frame_g, cv::Size(IMAGE_WIDTH, IMAGE_HEIGHT));
    
    if (frame_g.empty())
    {
        std::cout << "Failed to load image!" << std::endl;
        return -1;
    }
    else
    {
        
        int ret = date_extraction_on_frame();

        if (ret != 0)
        {
            fprintf(stderr, "[Error] Inference Not working !!! ");
            return -1;
        }

        /* Draw bounding box on the frame */
        draw_bounding_box();
        cout<<"bb drawn\n" ; 
        /*  Create Display frame */
        cv::Mat disp_frame ; 
        disp_frame = create_output_frame();
        cout<<"disp drawn\n" ;
        /* Print result on the frame */
        disp_frame = print_result(disp_frame);
        cout<<"res drawn\n" ;
        /* Display the resulting image */
        cv::imshow("Output Image", disp_frame);

        /* If defined for user to hit the key */
        #ifdef USER_KEY_HIT
        int key = 0;

        while (key != 27) // 'ESC' key (ASCII code 27)
        {
            key = cv::waitKey(0);
        }
        
        // User pressed 'ESC' key, close the image window
        cv::destroyAllWindows();

        #else
        cv::waitKey(WAIT_TIME);
        cv::destroyAllWindows();
        #endif

    }
   
    /* Exit the program */
    return 0;
}
