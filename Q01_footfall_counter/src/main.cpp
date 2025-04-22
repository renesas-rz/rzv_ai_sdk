/*
 * Original Code (C) Copyright Edgecortix, Inc. 2022
 * Modified Code (C) Copyright Renesas Electronics Corporation 2024
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

/*****************************************
* Includes
******************************************/
/*DRP-AI TVM[*1] Runtime*/
#include "MeraDrpRuntimeWrapper.h"
/*Definition of Macros & other variables*/
#include "define.h"
/*box drawing*/
#include "box.h"

#include "sort.h"

#include "draw.h"

/*****************************************
* Global Variables
******************************************/
std::map<std::string, int> input_source_map =
{
    {"USB", 1},
    #ifdef V2L
        {"MIPI", 2}
    #endif
};


/*Multithreading*/
static sem_t terminate_req_sem;
static pthread_t ai_inf_thread;
static pthread_t capture_thread;
static pthread_t kbhit_thread;
static std::mutex mtx;

/*Flags*/
static std::atomic<uint8_t> inference_start (0);
static std::atomic<uint8_t> img_obj_ready   (0);

/*Global Variables*/
static float drpai_output_buf[INF_OUT_SIZE];

/*AI Inference for DRPAI*/
/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper runtime;

#ifdef V2H
/*DRP-AI Frequency setting*/
static int32_t drpai_freq;
#endif

static float pre_time   = 0;
static float post_time  = 0;
static float ai_time    = 0;
static float total_time = 0;
static std::vector<detection> det;

cv::Mat yuyv_image;
cv::Mat input_image;
std::unordered_map<std::string, std::unordered_map<std::string, std::string>> ini_values;
std::vector<std::string> detection_object_vector;

static cv::Mat trackerbbox = cv::Mat(0, 6, CV_32F);
static std::vector<bbox_t> bbox;
int pointx1, pointy1, pointx2, pointy2, actual_count = 0;
std::vector<cv::Point> polygon;
static float conf = 0;


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
* Function Name : data_present
* Description   : Checks presence of data.txt file
* Return value  : 1 if file exists
*                 0 otherwise
******************************************/
int data_present()
{
    std::ifstream file("data.txt");
    if (file.good()) 
    {
        return 1;
    }
    return 0;
}

/*****************************************
* Function Name : data_read
* Description   : Retrive Line and polygon data
******************************************/
void data_read()
{
    std::ifstream myfile ("data.txt");
    std::string line, num;
    cv::Point P;

    if (!myfile.is_open())
    {
        std::cout << "Unable to open file";
    }
    while (getline(myfile, line)) {
        if (line.empty())
        {
            continue;
        }
        else
        {
            auto delimiter_pos = line.find(":");
            std::string key = line.substr(0, delimiter_pos);
            std::string value = line.substr(delimiter_pos + 1);
            if(key == "Point 1")
            {
                auto delimiter_pos = value.find(" ");
                pointx1 = std::stoi(value.substr(0, delimiter_pos));
                pointy1 = std::stoi(value.substr(delimiter_pos + 1));
            }
            else if(key == "Point 2")
            {
                auto delimiter_pos = value.find(" ");
                pointx2 = std::stoi(value.substr(0, delimiter_pos));
                pointy2 = std::stoi(value.substr(delimiter_pos + 1));
            }
            else
            {
                auto delimiter_pos = value.find(" ");
                P.x = std::stoi(value.substr(0, delimiter_pos));
                P.y = std::stoi(value.substr(delimiter_pos + 1));
                polygon.push_back(P);
            }
        }
    }
    myfile.close();
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
* Function Name     : load_label_file
* Description       : Load label list text file and return the label list that contains the label.
* Arguments         : label_file_name = filename of label list. must be in txt format
* Return value      : vector<string> list = list contains labels
*                     empty if error occurred
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
* Function Name : R_Post_Proc
* Description   : Process CPU post-processing for YOLOv3
* Arguments     : floatarr = drpai output address
* Return value  : -
******************************************/
void R_Post_Proc(float* floatarr)
{
    /* Following variables are required for correct_region_boxes in Darknet implementation*/
    /* Note: This implementation refers to the "darknet detector test" */
    mtx.lock();
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
    /* Clear the detected result list */
    det.clear();

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
                    tx = floatarr[offs];
                    ty = floatarr[yolo_index(n, offs, 1)];
                    tw = floatarr[yolo_index(n, offs, 2)];
                    th = floatarr[yolo_index(n, offs, 3)];
                    tc = floatarr[yolo_index(n, offs, 4)];
                    /* Compute the bounding box */
                    /*get_region_box*/
                    center_x = ((float) x + sigmoid(tx)) / (float) num_grid;
                    center_y = ((float) y + sigmoid(ty)) / (float) num_grid;
                    box_w = (float) exp(tw) * anchors[anchor_offset+2*b+0] / (float) MODEL_IN_W;
                    box_h = (float) exp(th) * anchors[anchor_offset+2*b+1] / (float) MODEL_IN_W;
                    /* Adjustment for VGA size */
                    /* correct_region_boxes */
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
                        det.push_back(d);
                    }
                }
            }
        }
    }
    /* Non-Maximum Supression filter */
    filter_boxes_nms(det, det.size(), TH_NMS);
    
    bbox.clear();
    trackerbbox = cv::Mat(0, 6, CV_32F);
    for (detection detect : det)
    {
        bbox_t dat;
        if (detect.prob < conf)
            continue;
        dat.name = label_file_map[detect.c].c_str();
        if (count(detection_object_vector.begin(), detection_object_vector.end(), dat.name) == 0)
            continue;

        dat.X = (int32_t)(detect.bbox.x - (detect.bbox.w / 2));
        dat.Y = (int32_t)(detect.bbox.y - (detect.bbox.h / 2));
        dat.W = (int32_t)detect.bbox.w;
        dat.H = (int32_t)detect.bbox.h;
        bbox.emplace_back(dat);
        cv::Mat bbox = (cv::Mat_<float>(1, 6) << dat.X, dat.Y, dat.W, dat.H, detect.prob, detect.c);
        cv::vconcat(trackerbbox, bbox, trackerbbox);
    }
    mtx.unlock();
    return ;
}

/*****************************************
* Function Name : check_above_or_below
* Description   : check the given point is above or below the line,
*                 added a small value of 1e-8 to avoid division by zero
* Arguments     : x = x coordinate of the point
*                 y = y coordinate of the point
* Return value  : int location of the point w.r.t the line
******************************************/
int check_above_or_below(int x, int y)
{
    double m = (pointy2 - pointy1) / ((pointx2 - pointx1) + 0.00000006);
    double yline = m * (x - pointx1) + pointy1;
    if(std::all_of(polygon.begin(), polygon.end(), [m](cv::Point p){ return p.y > (m * (p.x - pointx1) + pointy1); }))
    {
        if (y > yline)
            return 1;
        else
            return 0;
    }
    else
    {
        if (y < yline)
            return 1;
        else
            return 0;
    }
}

/*****************************************
* Function Name : check_inside_rectangle
* Description   : check the given point is inside the region defined using the polygon,
* Arguments     : x = x coordinate of the point
*                 y = y coordinate of the point
* Return value  : bool location of the point w.r.t the line
******************************************/
bool check_inside_rectangle(int x, int y)
{
    int result = pointPolygonTest(polygon, cv::Point(x, y), false);
    if (result == 1)
        return 1;
    else
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

    printf("\n[INFO] Inference Thread Starting\n");

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

        /*Gets Pre-process starting time*/
        ret = timespec_get(&pre_start_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Pre-process Start Time\n");
            goto err;
        }

        cv::Size size(MODEL_IN_H, MODEL_IN_W);
        cv::resize(input_image, input_image, size);
        cv::cvtColor(input_image, input_image, cv::COLOR_BGR2RGB);
        input_image = hwc2chw(input_image);
        input_image.convertTo(input_image, CV_32FC3,1.0 / 255.0, 0);
        if (!input_image.isContinuous())
        input_image = input_image.clone();

        ret = timespec_get(&pre_end_time, TIME_UTC);
        if ( 0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to Get Pre-process End Time\n");
            goto err;
        }

        /*Set Pre-processing output to be inference input. */
        runtime.SetInput(0, input_image.ptr<float>());
        
        /*Pre-process Time Result*/
        pre_time = (float)((time_difference_msec(pre_start_time, pre_end_time)));

        /*Gets inference starting time*/
        ret = timespec_get(&start_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Inference Start Time\n");
            goto err;
        }
        
        #ifdef V2H
            runtime.Run(drpai_freq);
        #elif V2L
            runtime.Run();
        #endif

        /*Gets AI Inference End Time*/
        ret = timespec_get(&inf_end_time, TIME_UTC);
        if ( 0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to Get Inference End Time\n");
            goto err;
        }
        /*Inference Time Result*/
        ai_time = (float)((time_difference_msec(start_time, inf_end_time)));

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
        /*Gets Post-process End Time*/
        ret = timespec_get(&post_end_time, TIME_UTC);
        if ( 0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to Get Post-process End Time\n");
            goto err;
        }
        /*Post-process Time Result*/
        post_time = (float)((time_difference_msec(post_start_time, post_end_time)));
        total_time = pre_time + ai_time + post_time;
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
    /* Set camera resolution */
    /* set width */
    g_cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    /* set height */
    g_cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
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

        g_cap >> g_frame;
        /* Breaking the loop if no video frame is detected */
        if (g_frame.empty())
        {
            std::cout << "[INFO] Video ended or corrupted frame !\n";
            goto capture_end;
        }
        else
        {   
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
    cv::Mat background(DISP_OUTPUT_HEIGHT, DISP_OUTPUT_WIDTH, frame_g.type(), cv::Scalar(0, 0, 0));
    /* Resize the original image to fit within 960x720 */
    cv::Mat resizedImage;
    cv::resize(frame_g, resizedImage, cv::Size(DISP_IMAGE_OUTPUT_WIDTH, DISP_IMAGE_OUTPUT_HEIGHT));
    /* Copy the resized image to the left side of the background (0 to 960) */
    cv::Rect roi(cv::Rect(0, 0, resizedImage.cols, resizedImage.rows));
    resizedImage.copyTo(background(roi));
    return background;
}

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
        std::cout << "[INFO] Double tap !!!" << std::endl;
        sem_trywait(&terminate_req_sem);
    }
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
    uint32_t idx = 0;
    config_read();
    uint8_t img_buf_id;
    std::map<int, int> id_time;
    std::set<int> unique_ids = {};
    std::map<int, int> location_history;
    long int infer_time_ms;
    cv::Mat bgra_image;
    std::stringstream stream;
    std::string result_str;
    int8_t region_count;
    int tracker_id;
    int class_id;
    std::string class_name;
    int8_t kmin = stoi(ini_values["tracking"]["kmin"]);
    conf = stof(ini_values["tracking"]["conf"]);

    std::string detection_object_string = ini_values["tracking"]["objects"];
    std::stringstream detection_object_ss(detection_object_string);
    std::string item;
    while (std::getline(detection_object_ss, item, ','))
    {
        detection_object_vector.push_back(item);
    }
    std::cout << "*******************Tracking/Detection Parameters*******************" << std::endl;
    std::cout << "\n[INFO] Selected objects to track\n\n";
    for (const auto &item : detection_object_vector)
        std::cout<< item << std::endl;

    std::string DISPLAY_TEXT = ini_values["display"]["display_text"];
    std::string DISPLAY_REGION_TEXT = ini_values["display"]["region_display_text"];
    std::string g_pipeline = "appsrc ! videoconvert ! autovideosink sync=false ";
    #ifdef V2H
        float font_size = .9;
        float font_size_double_click = .7;
        float font_weight = 2;
    #elif V2L
        float font_size = .6;
        float font_size_double_click = .5;
        float font_weight = 2;
    #endif
    float font_size_dt = 0.75;
    float font_size_bb = 0.5;
    float font_weight_bb = 1;
    if (DISPLAY_TEXT.size() > 20 || DISPLAY_REGION_TEXT.size() > 20)
    {
        font_size_dt = .45;
    }

    sort::Sort::Ptr mot = std::make_shared<sort::Sort>(1, 3, 0.3f);
    cv::namedWindow("Object Tracker", cv::WINDOW_NORMAL);
    cv::setWindowProperty("Object Tracker", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

    cv::namedWindow("Object Tracker", cv::WINDOW_NORMAL);
    cv::setWindowProperty("Object Tracker", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    cv::setMouseCallback("Object Tracker", mouse_callback_button_click);

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
            bgra_image = yuyv_image;
            infer_time_ms = total_time;
            cv::Mat tracks = mot->update(trackerbbox);
            region_count = 0;
            /* result tracks */
            for (int i = 0; i < tracks.rows; ++i)
            {
                bbox_t dat;
                tracker_id = int(tracks.at<float>(i, 8));
                class_id = int(tracks.at<float>(i, 5));
                class_name = label_file_map[class_id];
                dat.X = tracks.at<float>(i, 0);
                dat.Y = tracks.at<float>(i, 1);
                dat.W = tracks.at<float>(i, 2);
                dat.H = tracks.at<float>(i, 3);
                if (id_time.find(tracker_id) == id_time.end())
                {
                    dat.name = class_name + " Id : " + std::to_string(tracker_id);
                }
                else
                {
                    dat.name = class_name + " Id: " + std::to_string(tracker_id) + " Time: " + std::to_string(id_time[tracker_id] / 1000);
                }
                int s = check_above_or_below((int)(dat.X + dat.W / 2), (int)(dat.Y + dat.H));
                if (s)
                {
                    if (location_history.find(tracker_id) == location_history.end())
                        location_history[tracker_id] = s;
                    else
                    {
                        if (!location_history[tracker_id])
                        {
                            actual_count++;
                        }
                        location_history[tracker_id] = s;
                    }
                }
                else
                {
                    if (location_history.find(tracker_id) == location_history.end())
                        location_history[tracker_id] = s;
                    else
                    {
                        if (location_history[tracker_id])
                        {
                            actual_count--;
                            if(actual_count < 0)
                                actual_count = 0;
                        }
                        location_history[tracker_id] = s;
                    }
                }
                bool is_in_rect = check_inside_rectangle((int)(dat.X + dat.W / 2), (int)(dat.Y + dat.H));
                if (is_in_rect)
                {
                    region_count++;
                    if (id_time.find(tracker_id) == id_time.end())
                    {
                        id_time[tracker_id] = infer_time_ms;
                    }
                    else
                    {
                        id_time[tracker_id] += infer_time_ms;
                    }
                }
                if (dat.Y < 20){
                    dat.Y = 20;
                }
                cv::Rect rect(dat.X, dat.Y, dat.W, dat.H);                
                cv::rectangle(bgra_image, rect, cv::Scalar(0, 255, 0), 1.5);
                font_weight_bb = 1;
                font_size_bb = 0.5;
                cv::Size text_size = cv::getTextSize(dat.name, cv::FONT_HERSHEY_SIMPLEX, font_size_bb, font_weight_bb, 0);
                if (text_size.width > dat.W)
                {
                    font_size_bb = 0.3;
                    text_size = cv::getTextSize(dat.name, cv::FONT_HERSHEY_SIMPLEX, font_size_bb, font_weight_bb, 0);
                } 
                cv::Rect rect_text_box(dat.X, dat.Y - 20, text_size.width + 20, 20);
                cv::rectangle(bgra_image, rect_text_box, cv::Scalar(0, 255, 0), cv::FILLED);
                cv::putText(bgra_image, dat.name, cv::Point(dat.X + 10, dat.Y - 7), cv::FONT_HERSHEY_SIMPLEX, font_size_bb, cv::Scalar(0, 0, 0), font_size_bb, cv::LINE_AA);
            }
            cv::line(bgra_image, cv::Point(pointx1, pointy1), cv::Point(pointx2, pointy2), cv::Scalar(0, 0, 255), 4);
            cv::polylines(bgra_image, polygon, true, cv::Scalar(0, 255, 0), 2);
            bgra_image = create_output_frame(bgra_image);
            cv::putText(bgra_image, "Preprocess Time   : " + float_to_string(pre_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 60), cv::FONT_HERSHEY_SIMPLEX, font_size, cv::Scalar(255, 255, 255), font_weight, cv::LINE_AA);
            cv::putText(bgra_image, "AI Inference Time  : " + float_to_string(ai_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 95), cv::FONT_HERSHEY_SIMPLEX, font_size, cv::Scalar(255, 255, 255), font_weight, cv::LINE_AA);
            cv::putText(bgra_image, "Postprocess Time  : " + float_to_string(post_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 127), cv::FONT_HERSHEY_SIMPLEX, font_size, cv::Scalar(255, 255, 255), font_weight, cv::LINE_AA);
            cv::putText(bgra_image, DISPLAY_TEXT + " : " + std::to_string(actual_count), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 180), cv::FONT_HERSHEY_SIMPLEX, font_size_dt, cv::Scalar(255, 255, 255), font_weight, cv::LINE_AA);
            cv::putText(bgra_image, DISPLAY_REGION_TEXT + " : " + std::to_string(region_count), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 210), cv::FONT_HERSHEY_SIMPLEX, font_size_dt, cv::Scalar(255, 255, 255), font_weight, cv::LINE_AA);
            cv::putText(bgra_image, "Double Click to exit the Application.", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 10, DISP_IMAGE_OUTPUT_HEIGHT - 40), cv::FONT_HERSHEY_SIMPLEX, font_size_double_click, cv::Scalar(255, 255, 255), font_weight, cv::LINE_AA);
            cv::putText(bgra_image, "Objects Detected : ", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 270), cv::FONT_HERSHEY_SIMPLEX, font_size, cv::Scalar(255, 255, 255), font_weight, cv::LINE_AA);
            mtx.lock();
            for (int i = 0; i < bbox.size(); i++)
            {
                cv::putText(bgra_image, bbox[i].name, cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 30, (320 + (i * 30))), cv::FONT_HERSHEY_SIMPLEX, font_size, cv::Scalar(255, 255, 255), font_weight, cv::LINE_AA);
            }
            mtx.unlock();
            cv::cvtColor(bgra_image,bgra_image,cv::COLOR_BGR2BGRA);
            cv::imshow("Object Tracker", bgra_image);
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
* Function Name : get_drpai_start_addr
* Description   : Get DRP-AI Memory Area Address via DRP-AI Driver
* Arguments     : int drpai_fd
* Return value  : drpai start address 
******************************************/
#ifdef V2H
    uint64_t get_drpai_start_addr(int drpai_fd)
#elif V2L
    uint32_t get_drpai_start_addr(int drpai_fd)
#endif
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
        "media-ctl -d /dev/media0 -V \"\'rzg2l_csi2 10830400.csi2\':1 [fmt:UYVY8_2X8/640x480 field:none]\""
    };

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
    FILE* pipe = popen(command, "r");
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
* Function Name : init_drpai
* Description   : Function to initialize DRP-AI.
* Arguments     : drpai_fd: DRP-AI file descriptor
* Return value  : If non-zero, DRP-AI memory start address.
*                 0 is failure.
******************************************/
#ifdef V2H
uint64_t init_drpai(int drpai_fd)
#elif V2L
uint32_t init_drpai(int drpai_fd)
#endif
{
    int ret = 0;
#ifdef V2H
    uint64_t drpai_addr = 0;
#elif V2L
    uint32_t drpai_addr = 0;
#endif  
    /*Get DRP-AI memory start address*/
    drpai_addr = get_drpai_start_addr(drpai_fd);

    if (drpai_addr == 0)
    {
        return 0;
    }

    return drpai_addr;
}

int32_t main(int32_t argc, char * argv[])
{
    int8_t main_proc = 0;
    int8_t ret_main = 0;
    int8_t ret = 0;

    /*Disable OpenCV Accelerator due to the use of multithreading */
    #ifdef V2H
    unsigned long OCA_list[16];
    for(int i = 0; i < 16; i++) OCA_list[i] = 0;
    OCA_Activate(&OCA_list[0]);
    #endif

    /*Multithreading Variables*/
    int32_t create_thread_ai = -1;
    int32_t create_thread_key = -1;
    int32_t create_thread_exit = -1;
    int32_t create_thread_capture = -1;
    int32_t sem_create = -1;

    InOutDataType input_data_type;
    bool runtime_status = false;
    std::string gstreamer_pipeline;
    
    if (argc < 2) 
    {
        std::cout << "[ERROR] Please specify Input Source\n";

        #ifdef V2H
            std::cout << "[INFO] usage: ./object_tracker USB.\n";
        #elif V2L
            std::cout << "[INFO] usage: ./object_tracker USB|MIPI.\n";
        #endif
        
        std::cout << "[INFO] End Application.\n";
        return -1;
    }
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
        /* Input Source : MIPI Camera */
        case 2:
        {
            std::cout << "[INFO] MIPI CAMERA \n";
            mipi_cam_init();
            std::string media_port = query_device_status("CRU");
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";

        }
        break;
        default:
        {
            std::cout << "[ERROR] Invalid Input source\n";
            #ifdef V2H
                std::cout << "[INFO] usage: ./object_tracker USB.\n";
            #elif V2L
                std::cout << "[INFO] usage: ./object_tracker USB|MIPI.\n";
            #endif
            std::cout << "[INFO] End Application.\n";
            return -1;
        }
    }
    std::map<std::string, std::string> args;
    /* Parse input arguments */
    for (int i = 1; i < argc; ++i) 
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
    
    #ifdef V2H
         /* DRP-AI Frequency Setting */
        if (args.find("--drpai_freq") != args.end() && std::stoi(args["--drpai_freq"]) <= 127 && std::stoi(args["--drpai_freq"]) > 0)
            drpai_freq = stoi(args["--drpai_freq"]);
        else 
            drpai_freq = DRPAI_FREQ;
        std::cout<<"\n[INFO] DRPAI FREQUENCY : "<<drpai_freq<<"\n";
        /* AI Application for RZ/V2H */
        printf("\nAI Application for RZ/V2H\n");
        printf("Model : Darknet YOLOv3 | %s\n", model_dir.c_str());
    #elif V2L
        /* AI Application for RZ/V2L */
        printf("\nAI Application for RZ/V2L\n");
        printf("Model : Darknet TINY YOLOv3 | %s\n", model_dir.c_str());
    #endif
    if (args.find("--setup") != args.end() && args["--setup"] == "true" || !data_present())
    {
        Draw d(640, 480, gstreamer_pipeline);
        if(input_source == "MIPI")
        {
            d.set_skip_frames();
        }
        d.drawDisplay();
    }
    data_read();

    int drpai_fd = open("/dev/drpai0", O_RDWR);
    if (0 > drpai_fd)
    {
        std::cerr << "[ERROR] Failed to open DRP-AI Driver : errno=" << errno << std::endl;
        std::cout << "[INFO] End Application.\n";
        return -1;
    }
    /* Set drpai mem start address */
    uint64_t drpaimem_addr_start = 0;

    /*Load Label from label_list file*/
    label_file_map = load_label_file(label_list);
    if (label_file_map.empty())
    {
        fprintf(stderr,"[ERROR] Failed to load label file: %s\n", label_list.c_str());
        ret = -1;
        goto end_main;
    }

    /*Load model_dir structure and its weight to runtime object */
    drpaimem_addr_start = init_drpai(drpai_fd);
   
    if ((uint32_t)NULL == drpaimem_addr_start) 
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address.\n");
        goto end_main;
    }

    runtime_status = runtime.LoadModel(model_dir, drpaimem_addr_start + DRPAI_MEM_OFFSET);

    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load model.\n");
        goto end_main;
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
        goto end_main;
    }
    else
    {
        fprintf(stderr, "[ERROR] Input data type : neither FP32 nor FP16.\n");
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
    create_thread_ai = pthread_create(&ai_inf_thread, NULL, R_Inf_Thread, NULL);
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
        ret = wait_join(&ai_inf_thread, AI_THREAD_TIMEOUT);
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
