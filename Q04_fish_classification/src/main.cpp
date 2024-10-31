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
#include "utils.h"

/*****************************************
 * Global Variables
 ******************************************/

/*Multithreading*/
static sem_t terminate_req_sem;
static sem_t producer;
static sem_t consumer;
static pthread_t ai_inf_thread;
static pthread_t capture_thread;
static pthread_t exit_thread;
static pthread_t kbhit_thread;
static std::mutex mtx;

/*Flags*/
static std::atomic<uint8_t> inference_start(0);
static std::atomic<uint8_t> img_obj_ready(0);

/*Global Variables*/
float *drpai_output_buf;
std::map<std::string, int> input_source_map =
    {
        {"WS", 1},
        {"USB", 2},
        {"IMAGE", 3},
        {"VIDEO", 4},
        #ifdef V2L
            {"MIPI", 5}
        #endif
    };

unsigned int out;
cv::Mat bgra_image;

std::string score_per = "";
std::map<float,int> result;

/*AI Inference for DRPAI*/
/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper runtime;

static float pre_time = 0;
static float post_time = 0;
static float ai_time = 0;
static float total_time = 0;

cv::Mat yuyv_image;
cv::Mat input_image;
cv::Mat frame_g;

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> ini_values;

bool doubleClick = false;
cv::Mat frame_ws;

#ifdef V2H
    /*DRP-AI Frequency setting*/
    static int32_t drpai_freq;
    static float font_scale = 1;
    static float font_thickness = 1;
#elif V2L
    static float font_scale = 0.8;
    static float font_thickness = 1;
#endif

bool websocket=false;
uint32_t out_size_arr;
using INI_FORMAT = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

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
    if (0 == ret_err)
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
 * Function Name : R_exit_Thread
 * Description   : Executes the double click exit thread
 * Arguments     : threadid = thread identification
 * Return value  : -
 ******************************************/
void *R_exit_Thread(void *threadid)
{
    /*Semaphore Variable*/
    int32_t kh_sem_check = 0;

    /*Variable for checking return value*/
    int8_t ret = 0;
    devices dev;

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
            goto exit_end;
        }

        dev.detect_mouse_click();
        if (doubleClick)
        {
            goto err;
        }
    }

/*Error Processing*/
err:
    /*Set Termination Request Semaphore to 0*/
    sem_trywait(&terminate_req_sem);
    goto exit_end;

exit_end:
    printf("Exit Thread Terminated\n");
    pthread_exit(NULL);
}

/**
 * @brief Resize the image with aspect ratio
 *
 * @param input_img
 * @param resize_height
 * @return cv::Mat
 */
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

/*****************************************
 * Function Name : softmax
 * Description   : Function for Post Processing
 * Arguments     : val[] = array to be computed Softmax
 *                 size = size of array
 * Return value  : -
 ******************************************/
void softmax(float *val, int32_t size)
{
    float max_num = -INT_MAX;
    float sum = 0;
    int32_t i;
    for (i = 0; i < size; i++)
    {
        max_num = std::max(max_num, val[i]);
    }

    for (i = 0; i < size; i++)
    {
        val[i] = (float)exp(val[i] - max_num);
        sum += val[i];
    }

    for (i = 0; i < size; i++)
    {
        val[i] = val[i] / sum;
    }
    return;
}
/*****************************************
 * Function Name : web_inference
 * Description   : AI inference for web app
 * Arguments     : None
 * Return value  : int - class index
 ******************************************/
int web_inference()
{
    cv::Mat frame = cv::imread("test.png");
    /* Preprocess */
    cv::Size size(MODEL_IN_H, MODEL_IN_W);
    cv::resize(frame, frame, size);
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    frame = hwc2chw(frame);
    frame.convertTo(frame, CV_32FC3, 1.0 / 255.0, 0);
    /* deep copy, if not continuous */
    if (!frame.isContinuous())
        frame = frame.clone();

    /* Inference */
    runtime.SetInput(0, frame.ptr<float>());
    #ifdef V2H
        runtime.Run(drpai_freq);
    #elif V2L
        runtime.Run();
    #endif
    /* Postprocess */

    /* Get the number of output.  */
    auto output_num = runtime.GetNumOutput();
    /* get output buffer */
    auto output_buffer = runtime.GetOutput(0);
    out_size_arr = std::get<2>(output_buffer);
    std::vector<float> floatarr(out_size_arr);
     /* Post-processing for FP16 */
    if (InOutDataType::FLOAT16 == std::get<0>(output_buffer))
    {
        std::cout << "[INFO] Output data type : FP16.\n";
        /* Extract data in FP16 <uint16_t>. */
        uint16_t *data_ptr = reinterpret_cast<uint16_t *>(std::get<1>(output_buffer));
        for (int n = 0; n < out_size_arr; n++)
        {
            /* Cast FP16 output data to FP32. */
            floatarr[n] = float16_to_float32(data_ptr[n]);
        }
    }
    softmax(floatarr.data() , out_size_arr);
    int max_ind = -1;
    float max_value = -1;
    for (int n = 0; n < out_size_arr; n++)
    {
        if (floatarr[n] > max_value)
        {
            max_value = floatarr[n];
            max_ind = n;
        }
    }
    return (max_value > threshold) ? max_ind : -1;
}


/*****************************************
 * Function Name : R_Capture_Thread
 * Description   : Executes the V4L2 capture with Capture thread.
 * Arguments     : cap_pipeline = gstreamer pipeline
 * Return value  : -
 ******************************************/
void *R_Capture_Thread(void *cap_pipeline)
{
    std::string &gstream = *(static_cast<std::string *>(cap_pipeline));
    /*Semaphore Variable*/
    int32_t capture_sem_check = 0;
    int8_t ret = 0;
    cv::Mat g_frame;
    cv::VideoCapture g_cap;

    printf("[INFO] Capture Thread Starting\n");

    g_cap.open(gstream, cv::CAP_GSTREAMER);
    
    if (!g_cap.isOpened())
    {
        std::cout << "[ERROR] Error opening video stream or camera !\n"
                  << std::endl;
        goto err;
    }

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
        usleep(WAIT_TIME);
    }

/*Error Processing*/
err:
    sem_trywait(&terminate_req_sem);
    goto capture_end;

capture_end:
    /*To terminate the loop in AI Inference Thread.*/
    inference_start.store(1);

    printf("Capture Thread Terminated\n");
    pthread_exit(NULL);
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

    std::vector<float> output_arr(1);

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
        sem_wait(&producer);
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
        pre_time = (float)((timedifference_msec(pre_start_time, pre_end_time)));

        /*Gets inference starting time*/
        ret = timespec_get(&start_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Inference Start Time\n");
            goto err;
        }

        /*start inference using drp runtime*/
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
        ai_time = (float)((timedifference_msec(start_time, inf_end_time)));

        /*Gets Post-process starting time*/
        ret = timespec_get(&post_start_time, TIME_UTC);
        if (0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Post-process Start Time\n");
            goto err;
        }
        /*Process to read the DRPAI output data.*/
        /* Get the number of output.  */
        auto output_num = runtime.GetNumOutput();
        if (output_num != 1)
        {
            std::cout << "[ERROR] Output size : not 1." << std::endl;
            goto err;
        }
        /* get output buffer */
        auto output_buffer = runtime.GetOutput(0);
        out_size_arr = std::get<2>(output_buffer);
        output_arr.resize(out_size_arr);
         /* Post-processing for FP16 */
        if (InOutDataType::FLOAT16 == std::get<0>(output_buffer))
        {
            std::cout << "[INFO] Output data type : FP16.\n";
            /* Extract data in FP16 <uint16_t>. */
            uint16_t *data_ptr = reinterpret_cast<uint16_t *>(std::get<1>(output_buffer));
            for (int n = 0; n < out_size_arr; n++)
            {
                /* Cast FP16 output data to FP32. */
                output_arr[n] = float16_to_float32(data_ptr[n]);
            }
        }
        softmax(output_arr.data() , out_size_arr);
        mtx.lock();
        result.clear();
        for (int n = 0; n < out_size_arr; n++)
        {
            result[output_arr[n]] = n;
        }
        mtx.unlock();
        /*Gets Post-process End Time*/
        ret = timespec_get(&post_end_time, TIME_UTC);
        if ( 0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to Get Post-process End Time\n");
            goto err;
        }
        /*Post-process Time Result*/
        post_time = (float)((timedifference_msec(post_start_time, post_end_time)));
        total_time = pre_time + ai_time + post_time;
        inference_start.store(0);
        sem_post(&consumer);
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
 * Function Name : getipaddress
 * Description   : function to retrieve the ip address of the board
 * Return value  : String IP-Address
 ******************************************/
std::string getipaddress()
{
    std::string ip_address = "NULL";
    struct ifaddrs *ifAddrStruct = NULL;
    struct ifaddrs *ifa = NULL;
    void *tmpAddrPtr = NULL;
    /* The getifaddrs() function creates a linked list of structures
       describing the network interfaces of the local system*/
    getifaddrs(&ifAddrStruct);
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        /* The ifa_addr field points to a structure containing the interface
       address. */
        if (!ifa->ifa_addr)
        {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) /* check it is IPV4  is a valid IP4 Address */
        {
            tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            /* The ifa_name points to the null-terminated interface name. */
            std::string ifaname = ifa->ifa_name;
            if (ifaname.find("eth") == 0 || ifaname.find("enp") == 0)
            {
                ip_address = std::string(addressBuffer);
                /* returns the IP address*/
                return ip_address;
            }
        }
    }
    /* returns the IP(NULL) address*/
    return ip_address;
}


/*****************************************
 * Function Name    : create_output_frame
 * Description      : create the output frame with space for displaying inference details
 * Arguments        : cv::Mat frame_g, input frame to be displayed in the background
 * Return value     : cv::Mat background, final display frame to be written to gstreamer pipeline
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
    /*Variable for image buffer id*/
    uint8_t img_buf_id;
    /* wayland Index = 0 */
    uint32_t idx = 0;

    std::string class_name;
    int result_cnt = 0;
    float re_fl;

    /* Initialize waylad */
    ret = wayland.init(idx, IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT, IMAGE_CHANNEL_BGRA);
    if (0 != ret)
    {
        fprintf(stderr, "[ERROR] Failed to initialize Image for Wayland\n");
        return -1;
    }

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
        /* Check img_obj_ready flag which is set in Capture Thread. */
        if (img_obj_ready.load())
        {
            sem_wait(&consumer);
            bgra_image = yuyv_image;
            result_cnt = 0;
            /* Draw bounding box on the frame */
            bgra_image = create_output_frame(bgra_image);
            cv::putText(bgra_image, "Total AI Time[ms] : " + float_to_string(total_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 5, 60), cv::FONT_HERSHEY_DUPLEX, font_scale, WHITE, font_thickness);
            cv::putText(bgra_image, "Inference : " + float_to_string(ai_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 100), cv::FONT_HERSHEY_DUPLEX, font_scale, WHITE, font_thickness);
            cv::putText(bgra_image, "Preprocess : " + float_to_string(pre_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 140), cv::FONT_HERSHEY_DUPLEX, font_scale, WHITE, font_thickness);
            cv::putText(bgra_image, "Postprocess : " + float_to_string(post_time), cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 20, 180), cv::FONT_HERSHEY_DUPLEX, font_scale, WHITE, font_thickness);
            cv::putText(bgra_image,"Top Results:", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 5, (DISP_IMAGE_OUTPUT_HEIGHT/2) - 100), cv::FONT_HERSHEY_SIMPLEX, font_scale, WHITE, font_thickness);
            mtx.lock();
            for (auto it = result.rbegin(); it != result.rend(); it++)
            {
                result_cnt++;
                if(result_cnt > 5) break;
                re_fl = (float)(*it).first*100;
                if (re_fl != re_fl) {continue;}
                re_fl = std::round(re_fl);
                int val = ceil(re_fl);
                class_name = label_file_map[(*it).second];
                std::cout << "Top " << result_cnt << " ["
                                  << std::right << std::setw(5) << std::fixed << std::setprecision(1) << re_fl
                                  << "% ] : [" << label_file_map[(*it).second] << "]" << std::endl;
                cv::putText(bgra_image,"Top "+std::to_string(result_cnt)+" ["+std::to_string(val)+"%] : ["+class_name+"]", cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 15, DISP_IMAGE_OUTPUT_HEIGHT/2 - 100 + result_cnt * 40), cv::FONT_HERSHEY_SIMPLEX, font_scale - 0.3, WHITE, font_thickness);
                if (result_cnt == 1)
                {   
                    if(val > threshold*100)
                    {
                        cv::putText(bgra_image, "Fish class: "+ std::string(class_name), cv::Point(40, 35), cv::FONT_HERSHEY_SIMPLEX, font_scale, GREEN, font_thickness + 1);
                        cv::putText(bgra_image, "Score: "+ float_to_string(re_fl) +"%", cv::Point(40, 83), cv::FONT_HERSHEY_SIMPLEX, font_scale, GREEN, font_thickness +1);  
                    }
                    else
                    {
                        cv::putText(bgra_image,"Cannot Identify ! ",cv::Point(40, 30), cv::FONT_HERSHEY_SIMPLEX, font_scale, RED, font_thickness + 2);
                    }
                }
            }
            mtx.unlock();
            cv::cvtColor(bgra_image, bgra_image, cv::COLOR_BGR2BGRA);
            wayland.commit(bgra_image.data, NULL);
            img_obj_ready.store(0);
            sem_post(&producer);
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
    std::cout<<"[INFO] MIPI CAM Init \n";
    const char* commands[4] =
    {
        "media-ctl -d /dev/media0 -r",
        "media-ctl -d /dev/media0 -V \"\'ov5645 0-003c\':0 [fmt:UYVY8_2X8/640x480 field:none]\"",
        "media-ctl -d /dev/media0 -l \"\'rzg2l_csi2 10830400.csi2\':1 -> \'CRU output\':0 [1]\"",
        "media-ctl -d /dev/media0 -V \"\'rzg2l_csi2 10830400.csi2\':1 [fmt:UYVY8_2X8/640x480 field:none]\""
    };

    /* media-ctl command */
    for (int i=0; i<4; i++)
    {
        std::cout<<commands[i]<<"\n";
        ret = system(commands[i]);
        std::cout<<"system ret = "<<ret<<"\n";
        if (ret<0)
        {
            std::cout<<"[ERROR]"<<__func__<<": failed media-ctl commands. index = "<<i<<"\n";
            return;
        }
    }
}

/*****************************************
 * Function Name : query_device_status
 * Description   : function to check USB device is connectod.
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



int32_t main(int32_t argc, char *argv[])
{
    int8_t main_proc = 0;
    int8_t ret = 0;
    int8_t ret_w = 0;
    int8_t ret_main = 0;

    /*Multithreading Variables*/
    int32_t create_thread_capture = -1;
    int32_t create_thread_ai      = -1;
    int32_t create_thread_exit = -1;
    int32_t create_thread_key = -1;
    int32_t sem_create = -1;
    int32_t sem_producer = -1;
    int32_t sem_consumer = -1;

    InOutDataType input_data_type;
    bool runtime_status = false;
    bool errorHandle = false;
    std::string gstreamer_pipeline;
    std::map<std::string, std::string> args;
    std::string source;

    #ifdef V2H
        /*Disable OpenCV Accelerator due to the use of multithreading */
        unsigned long OCA_list[16];
        for(int i = 0; i < 16; i++) OCA_list[i] = 0;
        OCA_Activate(&OCA_list[0]);
    #endif
    
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

    if (argc < 2)
    {
        errorHandle = true;
    }
    else
    {
        std::string input_source = argv[1];
        if ((input_source == "USB" || input_source == "MIPI" || input_source == "WS") && argc >= 2)
            errorHandle = false;
        else if((input_source == "IMAGE"|| input_source == "VIDEO") && argc >= 3)
            errorHandle = false;
        else
            errorHandle = true;
    }
    if (errorHandle)
    {
        std::cout << "\n[ERROR] Please specify proper argument/Input Source" << std::endl;
        #ifdef V2H
            std::cout << "[INFO] usage: ./fish_classification USB|IMAGE|VIDEO [Input_file for IMAGE|VIDEO]" << std::endl;
        #elif V2L
            std::cout << "[INFO] usage: ./fish_classification USB|IMAGE|VIDEO|MIPI [Input_file for IMAGE|VIDEO]"<< std::endl;
        #endif
        std::cout << "\n[INFO] End Application\n";
        return -1;
    }

    #ifdef V2H
         /* DRP-AI Frequency Setting */
        if (args.find("--drpai_freq") != args.end() && std::stoi(args["--drpai_freq"]) <= 127 && std::stoi(args["--drpai_freq"]) > 0)
            drpai_freq = stoi(args["--drpai_freq"]);
        else 
            drpai_freq = DRPAI_FREQ;
        std::cout<<"\n[INFO] DRPAI FREQUENCY : "<<drpai_freq<<"\n";
        printf("AI Application for RZ/V2H\n");
        printf("Model : classification model | %s\n", ini_values["path"]["model_path"].c_str());
    #elif V2L
        /* AI Application for RZ/V2L */
        printf("AI Application for RZ/V2L\n");
        printf("Model : classification model | %s\n", ini_values["path"]["model_path"].c_str());
    #endif

    /* Access input source arguments */
    std::string input_source = argv[1];
    switch (input_source_map[input_source])
    {

        /* Input Source : Websocket*/
        case 1:
        {
            std::cout << "[INFO] WebSocket \n";
            websocket=true;
        }
        break;
        /* Input Source : USB Camera */
        case 2:
        {
            std::cout << "[INFO] USB CAMERA mode\n";
            std::string media_port = query_device_status("usb");
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
        }
        break;
        case 3:
        {
            std::cout << "[INFO] IMAGE mode \n";
            /* read input image */
            std::string image_path = argv[2];
            // Extract the file extension
            size_t dotPos = image_path.find_last_of('.');
            std::string extension = image_path.substr(dotPos + 1);
            if (dotPos != std::string::npos && (extension == "jpg" || extension == "JPG" || extension == "jpeg" || extension == "JPEG")) 
            {
                gstreamer_pipeline = "filesrc location=" + image_path + " ! jpegdec ! videoconvert ! videoscale ! video/x-raw, width=640, height=480 ! appsink";
            }
            else if (dotPos != std::string::npos && (extension =="png"|| extension =="PNG"))
            {
                gstreamer_pipeline = "filesrc location=" + image_path + " ! pngdec ! videoconvert ! videoscale ! video/x-raw, width=640, height=480 ! appsink";
            }
            else
            {
                std::cout << "\n[ERROR] Please specify proper argument/Input Source" << std::endl;
                #ifdef V2H
                    std::cout << "[INFO] usage: ./fish_classification USB|IMAGE|VIDEO [Input_file for IMAGE|VIDEO]" << std::endl;
                #elif V2L
                    std::cout << "[INFO] usage: ./fish_classification USB|IMAGE|VIDEO|MIPI [Input_file for IMAGE|VIDEO]"<< std::endl;
                #endif
                std::cout << "\n[INFO] End Application\n";
                return -1;
            }
        }
        break;
        case 4:
        {
            std::cout << "[INFO] VIDEO mode \n"; 
            std::string input_file = argv[2];
            gstreamer_pipeline = "filesrc location=" + input_file + " ! decodebin ! videoconvert ! appsink";

        }
        break;
        /* Input Source : MIPI */
        case 5:
        {
            std::cout << "[INFO] MIPI CAMERA \n";
            /* MIPI Camera Setup */
            mipi_cam_init();
            /* check the status of device */
            std::string media_port = query_device_status("CRU");
            if (media_port == "")
            {
                fprintf(stderr, "\n[ERROR] MIPI Camera not connected. \n");
                return -1;
            }
            /* gstremer pipeline to read input image source */
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
        }
        break;
        default:
        {
            std::cout << "\n[ERROR] Please specify proper argument/Input Source" << std::endl;
            #ifdef V2H
                std::cout << "[INFO] usage: ./fish_classification USB|IMAGE|VIDEO [Input_file for IMAGE|VIDEO]" << std::endl;
            #elif V2L
                std::cout << "[INFO] usage: ./fish_classification USB|IMAGE|VIDEO|MIPI [Input_file for IMAGE|VIDEO]"<< std::endl;
            #endif
            std::cout << "\n[INFO] End Application\n";
            return -1;
        }
    }

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
        fprintf(stderr, "[ERROR] Failed to load label file:");
        printf("Application End\n");
        ret = -1;
        return -1;
    }

    /*Load model_dir structure and its weight to runtime object */
    drpaimem_addr_start = init_drpai(drpai_fd);

    if ((uint32_t)NULL == drpaimem_addr_start)
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address.\n");
        printf("Application End\n");
        return -1;   
     }

    runtime_status = runtime.LoadModel(model_dir, drpaimem_addr_start + DRPAI_MEM_OFFSET);
    if (!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load model.\n");
        printf("Application End\n");
        return -1; 
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
        printf("Application End\n");
        return -1; 
    }
    else
    {
        fprintf(stderr, "[ERROR] Input data type : neither FP32 nor FP16.\n");
        printf("Application End\n");
        return -1; 
    }

    if(websocket)
    {
        /* Fetching the ip address of RZV2H dev module*/
        std::string ip_address = getipaddress();
        std::cout << "[INFO] IP address:" << ip_address << "\n";
        std::string port = "2002";
        /*create socket */
        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1)
        {
            std::cout << "[ERROR] Failed to create socket." << std::endl;
        }
        struct in_addr address;
        if (inet_aton(ip_address.c_str(), &address) == 0)
          std::cout << "[ERROR] Invalid IP address." << std::endl;
        struct sockaddr_in server_address;
        memset(&server_address, 0, sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_addr = address;
        server_address.sin_port = htons(stoi(port));
        /*bind the socket to  host address*/
        if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
            std::cout << " [ERROR] Failed to bind socket to server address." << std::endl;
        if (listen(server_fd, 10) == -1)
            std::cout << "[ERROR] Failed to listen for incoming connections." << std::endl;
        /*start communcation with client*/
        while (true)
        {
            struct sockaddr_in client_address;
            socklen_t client_address_len = sizeof(client_address);
            int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_address_len);
            if (client_fd == -1)
            {
                std::cout << "[ERROR] Failed to accept incoming connection." << std::endl;
                continue;
            }
            char buffer[1024 * 1024 * 3];
            /*receive data from client*/
            ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
            if (bytes_received == -1)
                std::cout << "[ERROR] Failed to receive image data." << std::endl;
            else
            {
                /*inference operation*/
                out = web_inference();
                /*return the results to ws client*/
                send(client_fd, label_file_map[out].c_str(), label_file_map[out].length(), 0);
            }
        }
        close(server_fd);
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

    sem_producer = sem_init(&producer, 0, 1);
    if (0 != sem_producer)
    {
        fprintf(stderr, "[ERROR] Failed to producer Semaphore.\n");
        ret_main = -1;
        goto end_threads;
    }

    sem_consumer = sem_init(&consumer, 0, 0);
    if (0 != sem_consumer)
    {
        fprintf(stderr, "[ERROR] Failed to consumer Semaphore.\n");
        ret_main = -1;
        goto end_threads;
    }

    /*Create Capture Thread*/
    create_thread_capture = pthread_create(&capture_thread, NULL, R_Capture_Thread, (void *)&gstreamer_pipeline);
    if (0 != create_thread_capture)
    {
        sem_trywait(&terminate_req_sem);
        fprintf(stderr, "[ERROR] Failed to create Capture Thread.\n");
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

    /*Create exit Thread*/
    create_thread_exit = pthread_create(&exit_thread, NULL, R_exit_Thread, NULL);
    if (0 != create_thread_exit)
    {
        fprintf(stderr, "[ERROR] Failed to create exit Thread.\n");
        ret_main = -1;
        goto end_threads;
    }
    /* Detached exit thread */
    pthread_detach(exit_thread);

    /*Create Key Hit Thread*/
    create_thread_key = pthread_create(&kbhit_thread, NULL, R_Kbhit_Thread, NULL);
    if (0 != create_thread_key)
    {
        fprintf(stderr, "[ERROR] Failed to create Key Hit Thread.\n");
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
        ret = wait_join(&kbhit_thread, EXIT_THREAD_TIMEOUT);
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
    if (0 == sem_producer)
    {
        sem_destroy(&producer);
    }
    if (0 == sem_consumer)
    {
        sem_destroy(&consumer);
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
    printf("Application End\n");
    return ret_main;
}