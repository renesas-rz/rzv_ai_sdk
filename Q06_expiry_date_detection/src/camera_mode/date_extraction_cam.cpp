/*
 * Original Code (C) Copyright Edgecortix, Inc. 2022
 * Modified Code (C) Copyright Renesas Electronics Corporation 2023
 *　
 *  *1 DRP-AI TVM is powered by EdgeCortix MERA(TM) Compiler Framework.
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : main.cpp
 * Version      : v1.00
 * Description  : RZ/V2L AI SDK Sample Application: Expiry Date Extraction
 ***********************************************************************************************************************/

/*****************************************
 * Includes
 ******************************************/
/*DRP-AI TVM[*1] Runtime*/
#include "../common/MeraDrpRuntimeWrapper.h"
/*Pre-processing Runtime Header*/
#include "PreRuntime.h"
/*Definition of Macros & other variables*/
#include "define.h"
/*MIPI camera control*/
#include "camera.h"
/*Image control*/
#include "image.h"
/*Wayland control*/
#include "wayland.h"
/*Common Definitions of Macros*/
#include "../common/comm_define.h"
/*box drawing*/
#include "../common/box.h"
/*Tesseract Extraction*/
#include "../common/tess_module/TesseractEngine.h"
/*Regular Expression Module */
#include "../common/regex_module/regex_function.h"
/* text processing */
#include "../common/text_proc_module/TextProc.h"
/* Date checking module*/
#include "../common/date_chck_module/date_check.h"
/* Common Utils: Yolo, label list file load*/
#include "../common/utils/common_utils.h"

using namespace std;
/*****************************************
 * Global Variables
 ******************************************/
/*Multithreading*/
static sem_t terminate_req_sem;
static pthread_t ai_inf_thread;
static pthread_t kbhit_thread;
static pthread_t capture_thread;
static mutex mtx;

/*Flags*/
static atomic<uint8_t> inference_start(0);
static atomic<uint8_t> img_obj_ready(0);

/*Global Variables*/
static float drpai_output_buf[INF_OUT_SIZE];
static uint32_t capture_address;
static uint64_t udmabuf_address = 0;
static Image img;

/*AI Inference for DRPAI*/
/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper runtime;
/* Pre-processing Runtime object */
PreRuntime preruntime;

static float pre_time = 0;
static float post_time = 0;
static float ai_time = 0;
static Wayland wayland;
static vector<detection> det;

static unordered_map<int, date_struct> date_struc_map;

static DateChecker date_checker;

/*Variable for Regex Dict */
static map<boost::regex, string> regex_dict_g;

/*Remaining Days Shown*/
static bool rem_days_shown = false ;

/*****************************************
 * Function Name : timedifference_msec
 * Description   : compute the time differences in ms between two moments
 * Arguments     : t0 = start time
 *                 t1 = stop time
 * Return value  : the time difference in ms
 ******************************************/
static double timedifference_msec(struct timespec t0, struct timespec t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1000000.0;
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
    if (0 == ret_err)
    {
        join_timeout.tv_sec += join_time;
        ret_err = pthread_timedjoin_np(*p_join_thread, NULL, &join_timeout);
    }
    return ret_err;
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
    output_num = runtime.GetNumOutput();
    size_count = 0;
    /*GetOutput loop*/
    for (i = 0; i < output_num; i++)
    {
        /* output_buffer below is tuple, which is { data type, address of output data, number of elements } */
        output_buffer = runtime.GetOutput(i);
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
                    tx = floatarr[offs];
                    ty = floatarr[yolo_index(n, offs, 1)];
                    tw = floatarr[yolo_index(n, offs, 2)];
                    th = floatarr[yolo_index(n, offs, 3)];
                    tc = floatarr[yolo_index(n, offs, 4)];
                    /* Compute the bounding BBox */
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

                    /* Getting params with respect to Input image size */
                    center_x = round(center_x * DRPAI_IN_WIDTH);
                    center_y = round(center_y * DRPAI_IN_HEIGHT);
                    box_w = round(box_w * DRPAI_IN_WIDTH);
                    box_h = round(box_h * DRPAI_IN_HEIGHT);

                    objectness = sigmoid(tc);
                    BBox bb = {center_x, center_y, box_w, box_h};
                    /* Get the class prediction */
                    for (i = 0; i < NUM_CLASS; i++)
                    {
                        classes[i] = sigmoid(floatarr[yolo_index(n, offs, 5 + i)]);
                    }
                    max_pred = 0;
                    pred_class = -1;
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
    /* Non-Maximum Suppression filter : det vector will updated*/
    filter_boxes_nms(det, det.size(), TH_NMS);
    mtx.unlock();
    return;
}

/*****************************************
 * Function Name : date_extraction 
 * Description   : Extract date from the image and store the date on the date_struc_map
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

        /*Get the cropped image with date */
        cv::Mat crop_img = img.get_crop_gray((int)det[i].bbox.x, (int)det[i].bbox.y, (int)det[i].bbox.w, (int)det[i].bbox.h);

        /* Resize when height < Min crop height */
        cv::Mat process_img = img.resize_gray_image(crop_img, MIN_CROP_HEIGHT);
        
        /*Run the Tesseract Engine*/
        /* Get the initialized Tesseract engine instance */ 
        TesseractEngine &tesseract = TesseractEngine::getInstance();

        /* Use the initialized Tesseract engine for processing*/ 
        tesseract::TessBaseAPI &tess_ocr_engine = tesseract.getEngine();

        /* set the processed image */
        tess_ocr_engine.SetImage(process_img.data, process_img.cols, process_img.rows, 1, process_img.step);
        /* set resolution of the image */
        tess_ocr_engine.SetSourceResolution(TESS_IMG_RESOLUTION);

        /* Perform OCR and retrieve the recognized text */
        char *recognizedText = tess_ocr_engine.GetUTF8Text();

        /* Remove trailing and leading white spaces */
        processed_text = trim_white_spc(recognizedText);

        cout<<"Extracted text : '"<< processed_text <<"'"<<endl;

        
        /*check for empty string*/
        if (processed_text.length() >= 1)
        {
            result_struc = get_yymmddd(regex_dict_g, processed_text);

            if (!result_struc.matched)
            {
                cout << "The string '" << processed_text << "' does not match any format" << endl; 
            }
            else
            {
                cout << "The string '" << processed_text << "' match the format" << result_struc.format<< endl; 
                cout << "Year: " << result_struc.year << " Month: "<< result_struc.month << "Day: "<< result_struc.day << endl;

                /*Fill the date structure for printing*/
                ret_date_struc.txt_extr = processed_text;
                ret_date_struc.year = result_struc.year;
                ret_date_struc.month = result_struc.month;
                ret_date_struc.day = result_struc.day;

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

        /*free up the memory*/
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

    for (i = 0; i < det.size(); i++)
    {
        /* Skip the overlapped bounding boxes */
        if (det[i].prob == 0)
            continue;

        /* Clear string stream for bounding box labels */
        stream.str("");
        /* Draw the bounding box on the image */
        stream << fixed << setprecision(2) << det[i].prob;
        result_str = label_file_map[det[i].c] + " " + stream.str();
        img.draw_rect((int)det[i].bbox.x, (int)det[i].bbox.y, (int)det[i].bbox.w, (int)det[i].bbox.h, result_str.c_str());
    }
    mtx.unlock();
    return;
}

/*****************************************
 * Function Name : print_result
 * Description   : print the result on display.
 * Arguments     : -
 * Return value  : 0 if succeeded
 *               not 0 otherwise
 ******************************************/
int8_t print_result(Image *img)
{
    mtx.lock();
    int32_t i = 0;
    stringstream stream;
    string str = "";
    int32_t result_cnt = 0;
    uint32_t total_time = ai_time + pre_time + post_time;

    /*point(x, y) to put text*/
    uint32_t draw_offset_x = DRPAI_IN_WIDTH * RESIZE_SCALE + TEXT_WIDTH_OFFSET; // Taking X to black region
    uint32_t y = LINE_HEIGHT * TIME_LINE_NUM + LINE_HEIGHT_OFFSET; // Taking Y to print after Inference time 

    uint32_t print_time = 0;
    string print_str = "";
    
    /* For detected classes  */
    for (i = 0; i < det.size(); i++)
    {
        /* Skip the overlapped bounding boxes */
        if (det[i].prob == 0)
            continue;

        /* Increment count of the detected objects in a frame */
        result_cnt++;

        /* Clear string stream for bounding box labels */
        stream.str("");

        /* Point (y) to print the class */
        y += LINE_HEIGHT ;

        /* Create bounding box label */
        stream << "Class "<< ":" << label_file_map[det[i].c].c_str() << " " << round(det[i].prob * 100) << "%";
        str = stream.str();
        img->write_string_rgb(str, draw_offset_x, y, CHAR_SCALE_SMALL, WHITE_DATA);
        
        /* Print Year, Month, Day separately */
        if (det[i].c == 0 && (date_struc_map.find(i) != date_struc_map.end()))
        {
            uint32_t color = WHITE_DATA;

            for(int ymd = 1; ymd< 5; ymd++)   
            {
                /* Increment y */
                y += LINE_HEIGHT;

                /* Clear the stream */  
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
                    if (rem_days_shown)
                    {
                        if (date_struc_map[i].remaining_days == -1 )
                        {
                            stream<<"Date Expired !!";
                            color = RED_DATA;
                        }
                        else 
                        {
                            stream <<"Remaining Days: "<< date_struc_map[i].remaining_days;
                            color = GREEN_DATA;
                        }
                         
                    }
                    break;
                default:
                    break;
                }

                img->write_string_rgb(stream.str(), draw_offset_x, y, CHAR_SCALE_SMALL, color);
            
            }

        }
        
    }

    /* For printing the time taken */
    for (int i = 0; i < TIME_LINE_NUM; i++)
    {   
        
        switch (i)
        {
        case (TIME_TOTAL_ID):
            print_time = (uint32_t)total_time;
            print_str = "Total AI Time : ";
            break;
        case (TIME_INF_ID):
            print_time = (uint32_t)ai_time;
            print_str = "  Inference   : ";
            break;
        case (TIME_PRE_ID):
            print_time = (uint32_t)pre_time;
            print_str = "  PreProcess : ";
            break;
        case (TIME_POST_ID):
            print_time = (uint32_t)post_time;
            print_str = "  PostProcess: ";
            break;
        default:
            break;
        }
        stream.str("");
        stream << print_str << print_time << "msec";
        str = stream.str();
        img->write_string_rgb(str, draw_offset_x, LINE_HEIGHT * (i + 1), CHAR_SCALE_SMALL, WHITE_DATA);
    }
    mtx.unlock();
    return 0;
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
    /*Variable for getting Inference output data*/
    void *output_ptr;
    uint32_t out_size;

    /*Variable for Pre-processing parameter configuration*/
    s_preproc_param_t in_param;
    /*Inference Variables*/
    fd_set rfds;
    struct timespec tv;
    int8_t inf_status = 0;
    /*Variable for checking return value*/
    int8_t ret = 0;
    /*Variable for Performance Measurement*/
    static struct timespec start_time;
    static struct timespec inf_end_time;
    static struct timespec pre_start_time;
    static struct timespec pre_end_time;
    static struct timespec post_start_time;
    static struct timespec post_end_time;

    printf("Inference Thread Starting\n");
    in_param.pre_in_shape_w = DRPAI_IN_WIDTH;
    in_param.pre_in_shape_h = DRPAI_IN_HEIGHT;

    printf("Inference Loop Starting\n");
    /*Inference Loop Start*/

    while (1)
    {
        while (1)
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

        /* set image address for pre- processing */
        in_param.pre_in_addr = (uintptr_t)capture_address;

        /*Gets Pre-process starting time*/
        ret = timespec_get(&pre_start_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Pre-process Start Time\n");
            goto err;
        }

        /* Do pre processing */
        ret = preruntime.Pre(&in_param, &output_ptr, &out_size);
        if (0 < ret)
        {
            fprintf(stderr, "[ERROR] Failed to run Pre-processing Runtime Pre()\n");
            goto err;
        }

        /*Gets AI Pre-process End Time*/
        ret = timespec_get(&pre_end_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to Get Pre-process End Time\n");
            goto err;
        }

        /*Set Pre-processing output to be inference input. */
        runtime.SetInput(0, (float *)output_ptr);
        /*Pre-process Time Result*/
        pre_time = (float)((timedifference_msec(pre_start_time, pre_end_time)));

        /*Gets inference starting time*/
        ret = timespec_get(&start_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Inference Start Time\n");
            goto err;
        }

        runtime.Run();

        /*Gets AI Inference End Time*/
        ret = timespec_get(&inf_end_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to Get Inference End Time\n");
            goto err;
        }
        /*Inference Time Result*/
        ai_time = (float)((timedifference_msec(start_time, inf_end_time)));

        /*Gets Post-process starting time*/
        ret = timespec_get(&post_start_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Post-process Start Time\n");
            goto err;
        }
        /*Process to read the DRPAI output data.*/
        ret = get_result();
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to get result from memory.\n");
            goto err;
        }

        /*CPU Post-Processing For YOLOv3*/
        R_Post_Proc(drpai_output_buf);

        // printf("Post process completed");

        /*Gets Post-process End Time*/
        ret = timespec_get(&post_end_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to Get Post-process End Time\n");
            goto err;
        }

        /*Post-process Time Result*/
        post_time = (float)((timedifference_msec(post_start_time, post_end_time)));

        // /* Text Extraction and regex*/
        // date_extraction();
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
    printf("AI Inference Thread Terminated\n");
    pthread_exit(NULL);
}

/*****************************************
 * Function Name : R_Capture_Thread
 * Description   : Executes the V4L2 capture with Capture thread.
 * Arguments     : threadid = thread identification
 * Return value  : -
 ******************************************/
void *R_Capture_Thread(void *threadid)
{
    Camera *capture = (Camera *)threadid;
    /*Semaphore Variable*/
    int32_t capture_sem_check = 0;
    /*First Loop Flag*/
    uint32_t capture_addr = 0;
    int8_t ret = 0;
    int32_t counter = 0;
    uint8_t *img_buffer;
    uint8_t *img_buffer0;
    const int32_t th_cnt = INF_FRAME_NUM;
    uint8_t udmabuf_fd0;
    uint8_t capture_stabe_cnt = 8; // Counter to wait for the camera to stabilize

    printf("Capture Thread Starting\n");

    udmabuf_fd0 = open("/dev/udmabuf0", O_RDWR);

    /* Map physical memory udmabuf_fd0 to virtual memory img_buffer0 with r/w access across multiple process*/
    img_buffer0 = (unsigned char *)mmap(NULL, CAM_IMAGE_WIDTH * CAM_IMAGE_HEIGHT * CAM_IMAGE_CHANNEL_YUY2, 
                    PROT_READ | PROT_WRITE, MAP_SHARED, udmabuf_fd0, UDMABUF_INFIMAGE_OFFSET);
    capture_address = (uint32_t)udmabuf_address + UDMABUF_INFIMAGE_OFFSET;

    while (1)
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

        /* Capture MIPI camera image and stop updating the capture buffer */
        capture_addr = (uint32_t)capture->capture_image(udmabuf_address);
        if (capture_addr == 0)
        {
            fprintf(stderr, "[ERROR] Failed to capture image from camera.\n");
            goto err;
        }
        else
        {
            /* Do not process until the camera stabilizes, because the image is unreliable until the camera stabilizes. */
            if (capture_stabe_cnt > 0)
            {
                capture_stabe_cnt--;
            }
            else
            {
                img_buffer = capture->get_img();
                /* If inference flag is 0*/
                if (!inference_start.load())
                {
                    /* Copy captured image to Image object. This will be used in Main Thread. */
                    memcpy(img_buffer0, img_buffer, CAM_IMAGE_WIDTH * CAM_IMAGE_HEIGHT * CAM_IMAGE_CHANNEL_YUY2);
                    inference_start.store(1); /* Flag for AI Inference Thread. */
                }
                /* If Image object needs to be loaded*/
                if (!img_obj_ready.load())
                {
                    img.camera_to_image(img_buffer, capture->get_size());
                    img_obj_ready.store(1); /* Flag for Main Thread. */
                }
            }
        }
        /* IMPORTANT: Place back the image buffer to the capture queue */
        ret = capture->capture_qbuf();
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to enqueue capture buffer.\n");
            goto err;
        }
    } /*End of Loop*/

/*Error Processing*/
err:
    sem_trywait(&terminate_req_sem);
    goto capture_end;

capture_end:
    munmap(img_buffer0, CAM_IMAGE_WIDTH * CAM_IMAGE_HEIGHT * CAM_IMAGE_CHANNEL_YUY2);
    /*To terminate the loop in AI Inference Thread.*/
    inference_start.store(1);

    printf("Capture Thread Terminated\n");
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

    printf("Key Hit Thread Starting\n");

    printf("************************************************\n");
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

    while (1)
    {
        /*Gets the Termination request semaphore value. If different then 1 Termination was requested*/
        /*Checks if sem_getvalue is executed with
        out issue*/
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
            printf("key Detected.\n");
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
    printf("Key Hit Thread Terminated\n");
    pthread_exit(NULL);
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
    uint8_t img_buf_id;

    printf("Main Loop Starts\n");
    while (1)
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

        /* Check img_obj_ready flag which is set in Capture Thread. if flag is 1*/
        if (img_obj_ready.load())
        {

            /* Text Extraction and regex*/
            date_extraction();

            /* Draw bounding box on image. */
            draw_bounding_box();

            /* Convert YUYV image to BGRA format. */
            img.convert_format();

            /* Scale up the image data. */
            img.convert_size();

            /*displays AI Inference Results on display.*/
            print_result(&img);

            /*Update Wayland*/
            img_buf_id = img.get_buf_id();
            wayland.commit(img_buf_id);

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
    printf("Main Process Terminated\n");
    return main_ret;
}

int32_t main(int32_t argc, char *argv[])
{
    int8_t main_proc = 0;
    int8_t ret = 0;
    int8_t ret_main = 0;
    /*Multithreading Variables*/
    int32_t create_thread_ai = -1;
    int32_t create_thread_key = -1;
    int32_t create_thread_capture = -1;
    int32_t sem_create = -1;
    Camera *capture = NULL;
    InOutDataType input_data_type;

    /*Initialize tesseract engine (using singleton class) */
    TesseractEngine &tesseract = TesseractEngine::getInstance();

    // create regex dictionary from regex module functions
    regex_dict_g = create_regex_dict();

    /* Check number of arguments */
    if (argc>2)
    {
        std::cerr << "Wrong number Arguments are passed \n";
        printf("Usage1: date_extraction_cam -rem \n Usage2 : date_extraction_cam \n");
        return 1;
    } 
    else if (argc == 2 && std::string(argv[1]) == "-rem")
    {
        std::cout<<"[INFO] Remaining Expiry Days will be shown"<<std::endl;
        rem_days_shown = true;
    }
    else if (argc == 1)
    {
        /* do nothing*/
        std::cout<<"[INFO] Remaining Expiry Days will Not be shown"<<std::endl;
    }
    else
    {
        std::cerr << "[ERROR] Wrong Arguments are passed\n";
        printf("Usage1: date_extraction_cam -rem \n Usage2 : date_extraction_cam \n");
        return 1;
    }

    /* Obtain udmabuf memory area starting address */
    int8_t fd = 0;
    char addr[1024];
    int32_t read_ret = 0;
    errno = 0;
    fd = open("/sys/class/u-dma-buf/udmabuf0/phys_addr", O_RDONLY);
    if (0 > fd)
    {
        fprintf(stderr, "[ERROR] Failed to open udmabuf0/phys_addr : errno=%d\n", errno);
        return -1;
    }
    read_ret = read(fd, addr, 1024);
    if (0 > read_ret)
    {
        fprintf(stderr, "[ERROR] Failed to read udmabuf0/phys_addr : errno=%d\n", errno);
        close(fd);
        return -1;
    }
    sscanf(addr, "%lx", &udmabuf_address);
    close(fd);
    /* Filter the bit higher than 32 bit */
    udmabuf_address &= 0xFFFFFFFF;

    printf("RZ/V2L AI SDK Sample Application: Date Extraction \n");
    printf("Model : Tiny Darknet YOLOv3 | %s\n", model_dir.c_str());
    /* Camera type Input*/
    #ifdef INPUT_CORAL
    printf("Input : Coral Camera\n");
    #else
    printf("Input : USB Camera\n");
    #endif

    /*Load Label from label_list file*/
    label_file_map = load_label_file(label_list);
    if (label_file_map.empty())
    {
        fprintf(stderr, "[ERROR] Failed to load label file: %s\n", label_list.c_str());
        ret = -1;
        goto end_main;
    }

    /*Load pre_dir object to DRP-AI */
    ret = preruntime.Load(pre_dir);
    if (0 < ret)
    {
        fprintf(stderr, "[ERROR] Failed to run Pre-processing Runtime Load().\n");
        goto end_main;
    }

    /*Load model_dir structure and its weight to runtime object */
    runtime.LoadModel(model_dir);
    /*Get input data */
    input_data_type = runtime.GetInputDataType(0);
    if (InOutDataType::FLOAT32 == input_data_type)
    {
        /*Do nothing*/
    }
    else if (InOutDataType::FLOAT16 == input_data_type)
    {
        fprintf(stderr, "[ERROR] Input data type : FP16.\n");
        /*If your model input data type is FP16, use std::vector<uint16_t> for reading input data. */
        goto end_main;
    }
    else
    {
        fprintf(stderr, "[ERROR] Input data type : neither FP32 nor FP16.\n");
        goto end_main;
    }

    /* Create Camera Instance */
    capture = new Camera();

    /* Init and Start Camera */
    ret = capture->start_camera();
    if (0 != ret)
    {
        fprintf(stderr, "[ERROR] Failed to initialize Camera.\n");
        delete capture;
        ret_main = ret;
        goto end_main;
    }

    /*Initialize Image object.*/
    ret = img.init(CAM_IMAGE_WIDTH, CAM_IMAGE_HEIGHT, CAM_IMAGE_CHANNEL_YUY2, IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT, IMAGE_CHANNEL_BGRA);
    if (0 != ret)
    {
        fprintf(stderr, "[ERROR] Failed to initialize Image object.\n");
        ret_main = ret;
        goto end_close_camera;
    }

    /* Initialize wayland */
    ret = wayland.init(img.udmabuf_fd, IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT, IMAGE_CHANNEL_BGRA);
    if (0 != ret)
    {
        fprintf(stderr, "[ERROR] Failed to initialize Image for Wayland\n");
        ret_main = -1;
        goto end_close_camera;
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

    /*Create Key Hit Thread*/
    create_thread_key = pthread_create(&kbhit_thread, NULL, R_Kbhit_Thread, NULL);
    if (0 != create_thread_key)
    {
        fprintf(stderr, "[ERROR] Failed to create Key Hit Thread.\n");
        ret_main = -1;
        goto end_threads;
    }

    /*Create Inference Thread*/
    create_thread_ai = pthread_create(&ai_inf_thread, NULL, R_Inf_Thread, NULL);
    if (0 != create_thread_ai)
    {
        sem_trywait(&terminate_req_sem);
        fprintf(stderr, "[ERROR] Failed to create AI Inference Thread.\n");
        ret_main = -1;
        goto end_threads;
    }

    /*Create Capture Thread*/
    create_thread_capture = pthread_create(&capture_thread, NULL, R_Capture_Thread, (void *)capture);
    if (0 != create_thread_capture)
    {
        sem_trywait(&terminate_req_sem);
        fprintf(stderr, "[ERROR] Failed to create Capture Thread.\n");
        ret_main = -1;
        goto end_threads;
    }

    /*Main Processing*/
    main_proc = R_Main_Process();
    if (0 != main_proc)
    {
        fprintf(stderr, "[ERROR] Error during Main Process\n");
        ret_main = -1;
    }
    goto end_threads;

end_threads:
    if (0 == create_thread_capture)
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
        ret = wait_join(&ai_inf_thread, AI_THREAD_TIMEOUT);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to exit AI Inference Thread on time.\n");
            ret_main = -1;
        }
    }
    if (0 == create_thread_key)
    {
        ret = wait_join(&kbhit_thread, KEY_THREAD_TIMEOUT);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to exit Key Hit Thread on time.\n");
            ret_main = -1;
        }
    }

    /*Delete Terminate Request Semaphore.*/
    if (0 == sem_create)
    {
        sem_destroy(&terminate_req_sem);
    }

    /* Exit waylad */
    wayland.exit();
    goto end_close_camera;

end_close_camera:
    /*Close MIPI Camera.*/
    ret = capture->close_camera();
    if (0 != ret)
    {
        fprintf(stderr, "[ERROR] Failed to close Camera.\n");
        ret_main = -1;
    }
    delete capture;
    goto end_main;

end_main:
    printf("Application End\n");
    return ret_main;
}
