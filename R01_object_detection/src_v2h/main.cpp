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
* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : main.cpp
* Version      : v3.00
* Description  : RZ/V2H AI SDK Sample Application for Object Detection
***********************************************************************************************************************/

/*****************************************
* Includes
******************************************/
/*DRP-AI TVM[*1] Runtime*/
#include "MeraDrpRuntimeWrapper.h"
/*Pre-processing Runtime Header*/
#include "PreRuntime.h"
/*Definition of Macros & other variables*/
#include "define.h"
/*Image control*/
#include "image.h"
/*Wayland control*/
#include "wayland.h"
/*box drawing*/
#include "box.h"
/*dmabuf for Pre-processing Runtime input data*/
#include "dmabuf.h"
/*Mutual exclusion*/
#include <mutex>

/*****************************************
* Global Variables
******************************************/
/*Multithreading*/
static sem_t terminate_req_sem;
static pthread_t ai_inf_thread;
static pthread_t kbhit_thread;
static pthread_t capture_thread;
static pthread_t img_thread;
static pthread_t hdmi_thread;
static std::mutex mtx;

/*Flags*/
static std::atomic<uint8_t> inference_start (0);
static std::atomic<uint8_t> img_obj_ready   (0);
static std::atomic<uint8_t> hdmi_obj_ready  (0);
/*Global Variables*/
static float drpai_output_buf[INF_OUT_SIZE];

static Image img;
/*Image to be displayed on GUI*/
cv::Mat input_image;
cv::Mat capture_image;
cv::Mat proc_image;
cv::Mat display_image;

/*GStreamer pipeline for camera capture*/
static std::string gstreamer_pipeline = "";

/*AI Inference for DRP-AI*/
/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper runtime;
/* Pre-processing Runtime object */
PreRuntime preruntime;
/*MMNGR buffer for DRP-AI Pre-processing*/
static dma_buffer *drpai_buf;

/*Processing Time*/
static double pre_time = 0;
static double post_time = 0;
static double ai_time = 0;

#ifdef DISP_CAM_FRAME_RATE
static double cap_fps = 0;
static double proc_time_capture = 0;
static uint32_t array_cap_time[30] = {1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000};
#endif /* DISP_CAM_FRAME_RATE */

/*DRP-AI Frequency setting*/
static int32_t drp_max_freq;
static int32_t drpai_freq;

static Wayland wayland;
static std::vector<detection> det;
static std::vector<detection> print_det;

/*****************************************
 * Function Name : query_device_status
 * Description   : function to check USB/MIPI device is connectod.
 * Return value  : media_port, media port that device is connectod. 
 ******************************************/
std::string query_device_status(std::string device_type)
{
    std::string media_port = "";
    /* Linux command to be executed */
    const char* command = "v4l2-ctl --list-devices";
    /* Open a pipe to the command and execute it */ 
    errno = 0;
    FILE* pipe = popen(command, "r");
    if (!pipe) 
    {
        fprintf(stderr, "[ERROR] Unable to open the pipe.\n", errno);
        return media_port;
    }
    /* Read the command output line by line */
    char buffer[128];
    size_t found;
    while (nullptr != fgets(buffer, sizeof(buffer), pipe)) 
    {
        std::string response = std::string(buffer);
        found = response.find(device_type);
        if (std::string::npos != found)
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
* Function Name     : float16_to_float32
* Description       : Function by Edgecortex. Cast uint16_t a into float value.
* Arguments         : a = uint16_t number
* Return value      : float = float32 number
******************************************/
float float16_to_float32(uint16_t a)
{
    return __extendXfYf2__<uint16_t, uint16_t, 10, float, uint32_t, 23>(a);
}

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
    if ( 0 == ret_err )
    {
        join_timeout.tv_sec += join_time;
        ret_err = pthread_timedjoin_np(*p_join_thread, NULL, &join_timeout);
    }
    return ret_err;
}

/*****************************************
* Function Name     : load_label_file
* Description       : Load label list text file and return the label list that contains the label.
* Arguments         : label_file_name = filename of label list. must be in txt format
* Return value      : std::vector<string> list = list contains labels
*                     empty if error occured
******************************************/
std::vector<std::string> load_label_file(std::string label_file_name)
{
    std::vector<std::string> list = {};
    std::vector<std::string> empty = {};
    std::ifstream infile(label_file_name);

    if (!infile.is_open())
    {
        return list;
    }

    std::string line = "";
    while (getline(infile,line))
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
* Function Name : get_result
* Description   : Get DRP-AI Output from memory via DRP-AI Driver
* Arguments     : -
* Return value  : 0 if succeeded
*                 not 0 otherwise
******************************************/
int8_t get_result()
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
    for (i = 0;i<output_num;i++)
    {
        /* output_buffer below is tuple, which is { data type, address of output data, number of elements } */
        output_buffer = runtime.GetOutput(i);
        /*Output Data Size = std::get<2>(output_buffer). */
        output_size = std::get<2>(output_buffer);

        /*Output Data Type = std::get<0>(output_buffer)*/
        if (InOutDataType::FLOAT16 == std::get<0>(output_buffer))
        {
            /*Output Data = std::get<1>(output_buffer)*/
            uint16_t* data_ptr = reinterpret_cast<uint16_t*>(std::get<1>(output_buffer));
            for (int j = 0; j<output_size; j++)
            {
                /*FP16 to FP32 conversion*/
                drpai_output_buf[j + size_count]=float16_to_float32(data_ptr[j]);
            }
        }
        else if (InOutDataType::FLOAT32 == std::get<0>(output_buffer))
        {
            /*Output Data = std::get<1>(output_buffer)*/
            float* data_ptr = reinterpret_cast<float*>(std::get<1>(output_buffer));
            for (int j = 0; j<output_size; j++)
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
* Function Name : sigmoid
* Description   : Helper function for YOLO Post Processing
* Arguments     : x = input argument for the calculation
* Return value  : sigmoid result of input x
******************************************/
double sigmoid(double x)
{
    return 1.0/(1.0 + exp(-x));
}

/*****************************************
* Function Name : softmax
* Description   : Helper function for YOLO Post Processing
* Arguments     : val[] = array to be computed softmax
* Return value  : -
******************************************/
void softmax(float val[NUM_CLASS])
{
    float max_num = -FLT_MAX;
    float sum = 0;
    int32_t i;
    for ( i = 0 ; i<NUM_CLASS ; i++ )
    {
        max_num = std::max(max_num, val[i]);
    }

    for ( i = 0 ; i<NUM_CLASS ; i++ )
    {
        val[i]= (float) exp(val[i] - max_num);
        sum+= val[i];
    }

    for ( i = 0 ; i<NUM_CLASS ; i++ )
    {
        val[i]= val[i]/sum;
    }
    return;
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
    return offs + channel * num_grid *  num_grid;
}

/*****************************************
* Function Name : yolo_offset
* Description   : Get the offset nuber to access the bounding box attributes
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

    for (i = 0 ; i < n; i++)
    {
        prev_layer_num += NUM_BB *(NUM_CLASS + 5)* num_grids[i] * num_grids[i];
    }
    return prev_layer_num + b *(NUM_CLASS + 5)* num * num + y * num + x;
}

/*****************************************
* Function Name : R_Post_Proc
* Description   : Process CPU post-processing for YOLOv3
* Arguments     : floatarr = drpai output address
* Return value  : -
******************************************/
void R_Post_Proc(float* floatarr)
{
    std::vector<detection> det_buff;

    /* Following variables are required for correct_yolo_boxes in Darknet implementation*/
    /* Note: This implementation refers to the "darknet detector test" */
    float new_w, new_h;
    float correct_w = 1.;
    float correct_h = 1.;
    if ((float) (MODEL_IN_W / correct_w) < (float) (MODEL_IN_H/correct_h) )
    {
        new_w = (float) MODEL_IN_W;
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
    /*Post Processing Start*/
    for (n = 0; n < NUM_INF_OUT_LAYER; n++)
    {
        num_grid = num_grids[n];
        anchor_offset = 2 * NUM_BB * (NUM_INF_OUT_LAYER - (n + 1));
        
        for(b = 0; b < NUM_BB; b++)
        {
            for(y = 0; y < num_grid; y++)
            {
                for(x = 0; x < num_grid; x++)
                {
                    offs = yolo_offset(n, b, y, x);
                    tc = floatarr[yolo_index(n, offs, 4)];
                    tx = floatarr[offs];
                    ty = floatarr[yolo_index(n, offs, 1)];
                    tw = floatarr[yolo_index(n, offs, 2)];
                    th = floatarr[yolo_index(n, offs, 3)];
                    /* Compute the bounding box */
                    /*get_yolo_box*/
                    center_x = ((float) x + sigmoid(tx)) / (float) num_grid;
                    center_y = ((float) y + sigmoid(ty)) / (float) num_grid;
                    box_w = (float) exp(tw) * anchors[anchor_offset+2*b+0] / (float) MODEL_IN_W;
                    box_h = (float) exp(th) * anchors[anchor_offset+2*b+1] / (float) MODEL_IN_W;
                    /* Adjustment for VGA size */
                    /* correct_yolo_boxes */
                    center_x = (center_x - (MODEL_IN_W - new_w) / 2. / MODEL_IN_W) / ((float) new_w / MODEL_IN_W);
                    center_y = (center_y - (MODEL_IN_H - new_h) / 2. / MODEL_IN_H) / ((float) new_h / MODEL_IN_H);
                    box_w *= (float) (MODEL_IN_W / new_w);
                    box_h *= (float) (MODEL_IN_H / new_h);
                    center_x = round(center_x * DRPAI_IN_WIDTH);
                    center_y = round(center_y * DRPAI_IN_HEIGHT);
                    box_w = round(box_w * DRPAI_IN_WIDTH);
                    box_h = round(box_h * DRPAI_IN_HEIGHT);
                    objectness = sigmoid(tc);
                    Box bb = {center_x, center_y, box_w, box_h};
                    /* Get the class prediction */
                    for (i = 0; i < NUM_CLASS; i++)
                    {
                        classes[i] = sigmoid(floatarr[yolo_index(n, offs, 5+i)]);
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
                        det_buff.push_back(d);
                    }
                }
            }
        }
    }
    /* Non-Maximum Supression filter */
    filter_boxes_nms(det_buff, det_buff.size(), TH_NMS);

    mtx.lock();
    det.clear();
    copy(det_buff.begin(), det_buff.end(), back_inserter(det));
    mtx.unlock();
    return;
}

/*****************************************
* Function Name : draw_bounding_box
* Description   : Draw bounding box on image. 
*                 Must be called before resizing the display image.
* Arguments     : -
* Return value  : 0 if succeeded
*               not 0 otherwise
******************************************/
void draw_bounding_box(void)
{
    std::vector<detection> det_buff;
    std::stringstream stream;
    std::string result_str;
    int32_t i = 0;
    uint32_t color = GREEN_DATA;
    uint32_t label_color = BLACK_DATA;

    mtx.lock();
    copy(det.begin(), det.end(), back_inserter(det_buff));
    mtx.unlock();

    print_det.clear();
    /* Draw bounding box on RGB image. */
    for (i = 0; i < det_buff.size(); i++)
    {
        /* Skip the overlapped bounding boxes */
        if (det_buff[i].prob == 0) continue;
        print_det.push_back(det_buff[i]);
        /* Clear string stream for bounding box labels */
        stream.str("");
        /* Draw the bounding box on the image */
        stream << std::fixed << std::setprecision(2) << det_buff[i].prob;
        result_str = label_file_map[det_buff[i].c]+ " "+ stream.str();
        img.draw_rect((int)det_buff[i].bbox.x, (int)det_buff[i].bbox.y, 
            (int)det_buff[i].bbox.w, (int)det_buff[i].bbox.h, 
            result_str.c_str(), color, label_color);
    }
    return;
}

/*****************************************
* Function Name : print_result
* Description   : print the result on display.
* Arguments     : -
* Return value  : 0 if succeeded
*               not 0 otherwise
******************************************/
int8_t print_result(Image* img)
{
    std::stringstream stream;
    std::string str = "";
    uint32_t total_time = ai_time + pre_time + post_time;
    uint8_t str_count = 1;
    uint8_t time_width = 5;
    uint8_t time_precision = 1;
    uint8_t result_width = 5;
    uint8_t result_precision = 1;
    uint32_t i = 0;

    /* Draw Total Time Result on BGR image.*/
    stream.str("");
    stream << "Total AI Time [ms]: " << std::setw(time_width)<< std::setfill(' ') << std::fixed << std::setprecision(time_precision) << std::round(total_time * 10) / 10;
    str = stream.str();
    img->write_string_rgb(str, ALIGHN_LEFT, TEXT_START_X + TEXT_WIDTH_OFFSET, LINE_HEIGHT_OFFSET + (LINE_HEIGHT * str_count++), CHAR_SCALE_LARGE, WHITE_DATA);

     /* Draw Inference Time on BGR image.*/
    stream.str("");
    stream << "  Inference : " << std::setw(time_width) << std::fixed << std::setprecision(time_precision) << std::round(ai_time * 10) / 10;
    str = stream.str();
    img->write_string_rgb(str, ALIGHN_LEFT, TEXT_START_X + TEXT_WIDTH_OFFSET, LINE_HEIGHT_OFFSET + (LINE_HEIGHT * str_count++), CHAR_SCALE_SMALL, WHITE_DATA);

    /* Draw PreProcess Time on BGR image.*/
    stream.str("");
    stream << "  PreProcess : " << std::setw(time_width) << std::fixed << std::setprecision(time_precision) << std::round(pre_time * 10) / 10;
    str = stream.str();
    img->write_string_rgb(str, ALIGHN_LEFT, TEXT_START_X + TEXT_WIDTH_OFFSET, LINE_HEIGHT_OFFSET + (LINE_HEIGHT * str_count++), CHAR_SCALE_SMALL, WHITE_DATA);

    /* Draw PostProcess Time on BGR image.*/
    stream.str("");
    stream << "  PostProcess : " << std::setw(time_width) << std::fixed << std::setprecision(time_precision) << std::round(post_time * 10) / 10;
    str = stream.str();
    img->write_string_rgb(str, ALIGHN_LEFT, TEXT_START_X + TEXT_WIDTH_OFFSET, LINE_HEIGHT_OFFSET + (LINE_HEIGHT * str_count++), CHAR_SCALE_SMALL, WHITE_DATA);

    /* Insert empty lines.*/
    str_count++;
#ifdef DISP_CAM_FRAME_RATE
    /* Draw Camera Frame Rate on BGR image.*/
    uint8_t framerate_width = 3;
    stream.str("");
    stream << "Camera Frame Rate [fps]: " << std::setw(framerate_width) << (uint32_t)cap_fps;
    str = stream.str();
    img->write_string_rgb(str, ALIGHN_LEFT, TEXT_START_X + TEXT_WIDTH_OFFSET, LINE_HEIGHT_OFFSET + (LINE_HEIGHT * str_count++), CHAR_SCALE_SMALL, WHITE_DATA);
#endif /* DISP_CAM_FRAME_RATE */
    /* Insert empty lines.*/
    str_count++;

    /* Draw the detected results*/
    for (i = 0; i < print_det.size(); i++)
    {
        stream.str("");
        stream << label_file_map[print_det[i].c].c_str() << " " << std::setw(result_width) << std::fixed << std::setprecision(result_precision) << round(print_det[i].prob*100) << "%";
        str = stream.str();
        img->write_string_rgb(str, ALIGHN_LEFT, TEXT_START_X + TEXT_WIDTH_OFFSET, LINE_HEIGHT_OFFSET + (LINE_HEIGHT * str_count++), CHAR_SCALE_SMALL, WHITE_DATA);
    }

    /* Draw the termination method at the bottom.*/
    stream.str("");
    stream << "To terminate the application,";
    str = stream.str();
    img->write_string_rgb(str, ALIGHN_LEFT, TEXT_START_X + TEXT_WIDTH_OFFSET, 
                            IMAGE_OUTPUT_HEIGHT - LINE_HEIGHT*3, CHAR_SCALE_VERY_SMALL, WHITE_DATA);
    stream.str("");
    stream << "press [Super]+[Tab] and press ENTER key.";
    str = stream.str();
    img->write_string_rgb(str, ALIGHN_LEFT, TEXT_START_X + TEXT_WIDTH_OFFSET, 
                            IMAGE_OUTPUT_HEIGHT - LINE_HEIGHT*2, CHAR_SCALE_VERY_SMALL, WHITE_DATA);
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
    void* output_ptr;
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
    while(1)
    {
        while(1)
        {
            /*Gets the Termination request semaphore value. If different then 1 Termination was requested*/
            /*Checks if sem_getvalue is executed wihtout issue*/
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

        /*Gets Pre-process Start time*/
        ret = timespec_get(&pre_start_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Pre-process Start Time\n");
            goto err;
        }

        in_param.pre_in_addr = (uintptr_t) drpai_buf->phy_addr;

        ret = preruntime.Pre(&in_param, &output_ptr, &out_size);
        if (0 < ret)
        {
            fprintf(stderr, "[ERROR] Failed to run Pre-processing Runtime Pre()\n");
            goto err;
        }
        /*Gets AI Pre-process End Time*/
        ret = timespec_get(&pre_end_time, TIME_UTC);
        if ( 0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to Get Pre-process End Time\n");
            goto err;
        }

        /*Set Pre-processing output to be inference input. */
        runtime.SetInput(0, (float*)output_ptr);

        /*Pre-process Time Result*/
        pre_time = (timedifference_msec(pre_start_time, pre_end_time) * TIME_COEF);

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
        if ( 0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to Get Inference End Time\n");
            goto err;
        }
        /*Inference Time Result*/
        ai_time = (timedifference_msec(start_time, inf_end_time) * TIME_COEF);

        /*Gets Post-process starting time*/
        ret = timespec_get(&post_start_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Post-process Start Time\n");
            goto err;
        }

        inference_start.store(0);

        /*Process to read the DRPAI output data.*/
        ret = get_result();
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to get result from memory.\n");
            goto err;
        }

        /*CPU Post-Processing For YOLOv3*/
        R_Post_Proc(drpai_output_buf);
        
        /*Gets Post-process End Time*/
        ret = timespec_get(&post_end_time, TIME_UTC);
        if ( 0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to Get Post-process End Time\n");
            goto err;
        }
        /*Post-process Time Result*/

        post_time = (timedifference_msec(post_start_time, post_end_time)*TIME_COEF);
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
    std::string &gstream = gstreamer_pipeline;
    printf("[INFO] GStreamer pipeline: %s\n", gstream.c_str());

    /*Semaphore Variable*/
    int32_t capture_sem_check = 0;
    int8_t ret = 0;
    /* Counter to wait for the camera to stabilize */
    uint8_t capture_stabe_cnt = CAPTURE_STABLE_COUNT;

#ifdef DISP_CAM_FRAME_RATE
    int32_t cap_cnt = -1;
    static struct timespec capture_time;
    static struct timespec capture_time_prev = { .tv_sec = 0, .tv_nsec = 0, };
#endif /* DISP_CAM_FRAME_RATE */

    cv::VideoCapture g_cap;
    cv::Mat g_frame;
    cv::Mat padding_frame(CAM_IMAGE_WIDTH - CAM_IMAGE_HEIGHT, CAM_IMAGE_WIDTH, CV_8UC3);

    printf("Capture Thread Starting\n");

    g_cap.open(gstream, cv::CAP_GSTREAMER);
    if (!g_cap.isOpened())
    {
        fprintf(stderr, "[ERROR] Failed to open camera.\n");
        goto err;
    }

    while(1)
    {
        /*Gets the Termination request semaphore value. If different then 1 Termination was requested*/
        /*Checks if sem_getvalue is executed wihtout issue*/
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

        /* Capture camera image and stop updating the capture buffer */

        g_cap.read(g_frame);
#ifdef DISP_CAM_FRAME_RATE
        cap_cnt++;
        ret = timespec_get(&capture_time, TIME_UTC);
        proc_time_capture = (timedifference_msec(capture_time_prev, capture_time) * TIME_COEF);
        capture_time_prev = capture_time;

        int idx = cap_cnt % SIZE_OF_ARRAY(array_cap_time);
        array_cap_time[idx] = (uint32_t)proc_time_capture;
        int arraySum = std::accumulate(array_cap_time, array_cap_time + SIZE_OF_ARRAY(array_cap_time), 0);
        double arrayAvg = 1.0 * arraySum / SIZE_OF_ARRAY(array_cap_time);
        cap_fps = 1.0 / arrayAvg * 1000.0 + 0.5;
#endif /* DISP_CAM_FRAME_RATE */

        /* Breaking the loop if no video frame is detected */
        if (g_frame.empty())
        {
            fprintf(stderr, "[ERROR] Failed to get capture image.\n");
            goto err;
        }
        else
        {
            /* Do not process until the camera stabilizes, because the image is unreliable until the camera stabilizes. */
            if( capture_stabe_cnt > 0 )
            {
                capture_stabe_cnt--;
            }
            else
            {
                if (!inference_start.load())
                {
                    /* Copy captured image to Image object. This will be used in Main Thread. */
                    mtx.lock();
                    /*Image: CAM_IMAGE_WIDTH*CAM_IMAGE_HEIGHT (BGR) */
                    input_image = g_frame.clone();
                    
                    /*Add padding for keeping the aspect ratio: CAM_IMAGE_WIDTH*CAM_IMAGE_WIDTH (BGR) */
                    cv::vconcat(input_image, padding_frame, input_image);
                    
                    /*Copy input data to drpai_buf for DRP-AI Pre-processing Runtime.*/
                    memcpy( drpai_buf->mem, input_image.data, drpai_buf->size);
                    /* Flush buffer */
                    ret = buffer_flush_dmabuf(drpai_buf->idx, drpai_buf->size);
                    if (0 != ret)
                    {
                        goto err;
                    }
                    mtx.unlock();
                    inference_start.store(1); /* Flag for AI Inference Thread. */
                }

                if (!img_obj_ready.load())
                {
                    mtx.lock();
                    capture_image = g_frame.clone();
                    img.set_mat(capture_image);
                    mtx.unlock();
                    img_obj_ready.store(1); /* Flag for Img Thread. */
                }
            }
        }
    } /*End of Loop*/

/*Error Processing*/
err:
    sem_trywait(&terminate_req_sem);
    goto capture_end;

capture_end:
    g_cap.release();
    /*To terminate the loop in AI Inference Thread.*/
    inference_start.store(1);

    printf("Capture Thread Terminated\n");
    pthread_exit(NULL);
}

/*****************************************
* Function Name : R_Img_Thread
* Description   : Executes img proc with img thread
* Arguments     : threadid = thread identification
* Return value  : -
******************************************/
void *R_Img_Thread(void *threadid)
{
    /*Semaphore Variable*/
    int32_t hdmi_sem_check = 0;
    /*Variable for checking return value*/
    int8_t ret = 0;
    
    timespec start_time;
    timespec end_time;

    /*Check the aspect ratio of camera input and display.*/
    bool display_padding = false;
    float camera_ratio = (float) CAM_IMAGE_WIDTH / CAM_IMAGE_HEIGHT;
    float display_ratio = (float) IMAGE_OUTPUT_WIDTH / IMAGE_OUTPUT_HEIGHT;
    if (camera_ratio != display_ratio)
    {
        /*If different, set padding on Wayland display*/
        display_padding = true;
    }

    printf("Image Thread Starting\n");
    while(1)
    {
        /*Gets The Termination Request Semaphore Value, If Different Then 1 Termination Is Requested*/
        /*Checks If sem_getvalue Is Executed Without Issue*/
        errno = 0;
        ret = sem_getvalue(&terminate_req_sem, &hdmi_sem_check);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Semaphore Value: errno=%d\n", errno);
            goto err;
        }
        /*Checks the semaphore value*/
        if (1 != hdmi_sem_check)
        {
            goto hdmi_end;
        }
        /* Check img_obj_ready flag which is set in Capture Thread. */
        if (img_obj_ready.load())
        {
            /* Draw bounding box on image. */
            draw_bounding_box();

            /* Convert output image size. */
            img.convert_size(CAM_IMAGE_WIDTH, DRPAI_OUT_WIDTH, display_padding);

            /*Displays AI Inference Results on display.*/
            print_result(&img);
            
            proc_image = img.get_mat().clone(); 

            if (!hdmi_obj_ready.load())
            {
                hdmi_obj_ready.store(1); /* Flag for Display Thread. */
            }
            img_obj_ready.store(0);
        }
        usleep(WAIT_TIME); //wait 1 tick time
    } /*End Of Loop*/

/*Error Processing*/
err:
    /*Set Termination Request Semaphore To 0*/
    sem_trywait(&terminate_req_sem);
    goto hdmi_end;

hdmi_end:
    /*To terminate the loop in Capture Thread.*/
    img_obj_ready.store(0);
    printf("Img Thread Terminated\n");
    pthread_exit(NULL);
}

/*****************************************
* Function Name : R_Display_Thread
* Description   : Executes the HDMI Display with Display thread
* Arguments     : threadid = thread identification
* Return value  : -
******************************************/
void *R_Display_Thread(void *threadid)
{
    /*Semaphore Variable*/
    int32_t hdmi_sem_check = 0;
    /*Variable for checking return value*/
    int8_t ret = 0;
    /* Initialize waylad */
    ret = wayland.init(IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT, IMAGE_OUTPUT_CHANNEL_BGRA);
    if(0 != ret)
    {
        fprintf(stderr, "[ERROR] Failed to initialize Image for Wayland\n");
        goto err;
    }
    printf("Display Thread Starting\n");
    while(1)
    {
        /*Gets The Termination Request Semaphore Value, If Different Then 1 Termination Is Requested*/
        /*Checks If sem_getvalue Is Executed Without Issue*/
        errno = 0;
        ret = sem_getvalue(&terminate_req_sem, &hdmi_sem_check);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Semaphore Value: errno=%d\n", errno);
            goto err;
        }
        /*Checks the semaphore value*/
        if (1 != hdmi_sem_check)
        {
            goto hdmi_end;
        }
        /* Check hdmi_obj_ready flag which is set in Capture Thread. */
        if (hdmi_obj_ready.load())
        {
            /*Update Wayland*/
            display_image = proc_image;
            cv::cvtColor(display_image, display_image, cv::COLOR_BGR2BGRA);
            wayland.commit(display_image.data, NULL);
            hdmi_obj_ready.store(0);
        }
        usleep(WAIT_TIME); //wait 1 tick timedg
    } /*End Of Loop*/

/*Error Processing*/
err:
    /*Set Termination Request Semaphore To 0*/
    sem_trywait(&terminate_req_sem);
    goto hdmi_end;

hdmi_end:
    /*To terminate the loop in Capture Thread.*/
    hdmi_obj_ready.store(0);
    printf("Display Thread Terminated\n");
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

    while(1)
    {
        /*Gets the Termination request semaphore value. If different then 1 Termination was requested*/
        /*Checks if sem_getvalue is executed wihtout issue*/
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
            printf("[INFO] Key Detected.\n");
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

    printf("Main Loop Starts\n");
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
    printf("Main Process Terminated\n");
    return main_ret;
}

/*****************************************
* Function Name : get_drpai_start_addr
* Description   : Function to get the start address of DRPAImem.
* Arguments     : drpai_fd: DRP-AI file descriptor
* Return value  : If non-zero, DRP-AI memory start address.
*                 0 is failure.
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
        fprintf(stderr, "[ERROR] Failed to get DRP-AI Memory Area : errno=%d\n", errno);
        return 0;
    }

    return drpai_data.address;
}

/*****************************************
* Function Name : set_drpai_freq
* Description   : Function to set the DRP and DRP-AI frequency.
* Arguments     : drpai_fd: DRP-AI file descriptor
* Return value  : 0 if succeeded
*                 not 0 otherwise
******************************************/
int set_drpai_freq(int drpai_fd)
{
    int ret = 0;
    uint32_t data;

    errno = 0;
    data = drp_max_freq;
    ret = ioctl(drpai_fd , DRPAI_SET_DRP_MAX_FREQ, &data);
    if (-1 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to set DRP Max Frequency : errno=%d\n", errno);
        return -1;
    }

    errno = 0;
    data = drpai_freq;
    ret = ioctl(drpai_fd , DRPAI_SET_DRPAI_FREQ, &data);
    if (-1 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to set DRP-AI Frequency : errno=%d\n", errno);
        return -1;
    }
    return 0;
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

    /*Set DRP-AI frequency*/
    ret = set_drpai_freq(drpai_fd);
    if (ret != 0)
    {
        return 0;
    }

    return drpai_addr;
}

int32_t main(int32_t argc, char * argv[])
{
    int8_t main_proc = 0;
    int8_t ret = 0;
    int8_t ret_main = 0;
    /*Multithreading Variables*/
    int32_t create_thread_ai = -1;
    int32_t create_thread_key = -1;
    int32_t create_thread_capture = -1;
    int32_t create_thread_img = -1;
    int32_t create_thread_hdmi = -1;
    int32_t sem_create = -1;

    InOutDataType input_data_type;
    bool runtime_status = false;
    int drpai_fd;

    std::string media_port = query_device_status("usb");
    gstreamer_pipeline = "v4l2src device=" + media_port +" ! video/x-raw, width="+std::to_string(CAM_IMAGE_WIDTH)+", height="+std::to_string(CAM_IMAGE_HEIGHT)+" ,framerate=30/1 ! videoconvert ! appsink -v";

    /*Disable OpenCV Accelerator due to the use of multithreading */
    unsigned long OCA_list[16];
    for (int i=0; i < 16; i++) OCA_list[i] = 0;
    OCA_Activate( &OCA_list[0] );

    printf("RZ/V2H AI SDK Sample Application\n");
    printf("Model : Darknet YOLOv3 | %s\n", model_dir.c_str());
    printf("Input : %s\n", INPUT_CAM_NAME);

    /* DRP-AI Frequency Setting */
    /* Usually, users can use default values. */
    if (2 <= argc)
    {
        drp_max_freq = atoi(argv[1]);
        printf("Argument : <DRP0_max_freq_factor> = %d\n", drp_max_freq);
    }
    else
    {
        drp_max_freq = DRP_MAX_FREQ;
    }
    if (3 <= argc)
    {
        drpai_freq = atoi(argv[2]);
        printf("Argument : <AI-MAC_freq_factor> = %d\n", drpai_freq);
    }
    else
    {
        drpai_freq = DRPAI_FREQ;
    }
    
    uint64_t drpaimem_addr_start = 0;

    /*Load Label from label_list file*/
    label_file_map = load_label_file(label_list);
    if (label_file_map.empty())
    {
        fprintf(stderr,"[ERROR] Failed to load label file: %s\n", label_list.c_str());
        ret_main = -1;
        goto end_main;
    }

    /*DRP-AI Driver initialization*/
    errno = 0;
    drpai_fd = open("/dev/drpai0", O_RDWR);
    if (0 > drpai_fd)
    {
        fprintf(stderr, "[ERROR] Failed to open DRP-AI Driver : errno=%d\n", errno);
        ret_main = -1;
        goto end_main;
    }
    /*Get DRP-AI memory area start address*/
    drpaimem_addr_start = init_drpai(drpai_fd);
    if ((uint64_t)NULL == drpaimem_addr_start) 
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address.\n");
        goto end_close_drpai;
    }

    /*Load pre_dir object to DRP-AI */
    ret = preruntime.Load(pre_dir);
    if (0 < ret)
    {
        fprintf(stderr, "[ERROR] Failed to run Pre-processing Runtime Load().\n");
        ret_main = -1;
        goto end_close_drpai;
    }

    /*Load model_dir for DRP-AI inference */
    runtime_status = runtime.LoadModel(model_dir, drpaimem_addr_start);

    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load model.\n");
        goto end_close_drpai;
    }

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
        goto end_close_drpai;
    }
    else
    {
        fprintf(stderr, "[ERROR] Input data type : neither FP32 nor FP16.\n");
        goto end_close_drpai;
    }

    /*Initialize buffer for DRP-AI Pre-processing Runtime. */
    drpai_buf = (dma_buffer*)malloc(sizeof(dma_buffer));
    ret = buffer_alloc_dmabuf(drpai_buf,CAM_IMAGE_WIDTH*CAM_IMAGE_WIDTH*CAM_IMAGE_CHANNEL_BGR);
    if (-1 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to Allocate DMA buffer for the drpai_buf\n");
        goto end_free_malloc;
    }

    /*Initialize Image object.*/
    ret = img.init(CAM_IMAGE_WIDTH, CAM_IMAGE_HEIGHT, CAM_IMAGE_CHANNEL_BGR, 
                    IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT, IMAGE_OUTPUT_CHANNEL_BGRA);
    if (0 != ret)
    {
        fprintf(stderr, "[ERROR] Failed to initialize Image object.\n");
        ret_main = ret;
        goto end_close_dmabuf;
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
    create_thread_capture = pthread_create(&capture_thread, NULL, R_Capture_Thread, NULL);
    if (0 != create_thread_capture)
    {
        sem_trywait(&terminate_req_sem);
        fprintf(stderr, "[ERROR] Failed to create Capture Thread.\n");
        ret_main = -1;
        goto end_threads;
    }
    /*Create Image Thread*/
    create_thread_img = pthread_create(&img_thread, NULL, R_Img_Thread, NULL);
    if(0 != create_thread_img)
    {
        sem_trywait(&terminate_req_sem);
        fprintf(stderr, "[ERROR] Failed to create Image Thread.\n");
        ret_main = -1;
        goto end_threads;
    }

    /*Create Display Thread*/
    create_thread_hdmi = pthread_create(&hdmi_thread, NULL, R_Display_Thread, NULL);
    if(0 != create_thread_hdmi)
    {
        sem_trywait(&terminate_req_sem);
        fprintf(stderr, "[ERROR] Failed to create Display Thread.\n");
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
    if (0 == create_thread_hdmi)
    {
        ret = wait_join(&hdmi_thread, DISPLAY_THREAD_TIMEOUT);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to exit Display Thread on time.\n");
            ret_main = -1;
        }
    }
    if (0 == create_thread_img)
    {
        ret = wait_join(&img_thread, IMAGE_THREAD_TIMEOUT);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to exit Image Thread on time.\n");
            ret_main = -1;
        }
    }
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

    goto end_close_dmabuf;

end_close_dmabuf:
    buffer_free_dmabuf(drpai_buf);
    goto end_free_malloc;

end_free_malloc:
    free(drpai_buf);
    drpai_buf = NULL;
    
    goto end_close_drpai;

end_close_drpai:
    /*Close DRP-AI Driver.*/
    if (0 < drpai_fd)
    {
        errno = 0;
        ret = close(drpai_fd);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to close DRP-AI Driver: errno=%d\n", errno);
            ret_main = -1;
        }
    }
    goto end_main;

end_main:
    printf("Application End\n");
    return ret_main;
}
