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
#include "define.h"

/*****************************************
* Global Variables
******************************************/
/* Map to store input source list */
std::map<std::string, int> input_source_map =
{
    {"VIDEO", 1},
    {"USB", 2},
    #ifdef V2L
        {"MIPI", 3}
    #endif
};

/*Multithreading*/
static sem_t terminate_req_sem;
static pthread_t ai_inf_thread;
static pthread_t capture_thread;
static pthread_t exit_thread;
static pthread_t kbhit_thread;

/*Flags*/
static std::atomic<uint8_t> inference_start (0);
static std::atomic<uint8_t> img_obj_ready   (0);

/*AI Inference for DRPAI*/
/* DRP-AI TVM[*1] Runtime object */
#ifdef V2H
    MeraDrpRuntimeWrapper cnn_runtime;
    MeraDrpRuntimeWrapper mlp_runtime;
#elif V2L
    MeraDrpRuntimeWrapper runtime;
#endif

/*Global Variables*/
const std::string non_violence      = "Non Violence activity";
const std::string violence          = "Violence activity detected !";
const std::string none              = "None";
std::string result                  = none;

/* flag for detecting window exit*/
bool exitClick          = false;

bool errorHandle    = false;

float threshold     = 0.5;
float val           = 1.0;
double count        = 0;

/* variables to calculate total fps and inference time */
int g_fps;
uint32_t g_out_size_arr;

std::vector<float> floatarr(1);
std::vector<cv::Mat> stacked_data;

std::vector<double> x;
std::vector<double> y;

cv::Mat display;

cv::Mat input_image;
cv::Mat yuyv_image;

/* Sets a flag to indicate whether a double click has been detected. */
bool doubleClick = false;

static Wayland wayland;

/* variables to calculate inference time */
static float pre_time   = 0;
static float post_time  = 0;
static float total_ai_time    = 0;

#ifdef V2H
    static float cnn_ai_time    = 0;
    static float mlp_ai_time    = 0;

    /*DRP-AI Frequency setting*/
    static int32_t drpai_freq;

    static float font_scale = 1;
    static float font_thickness = 2;
    float font_size = .9;
    float font_weight = 2;
    int offset = 40;
#elif V2L
    static float ai_time    = 0;

    static float font_scale = 0.8;
    static float font_thickness = 2;
    float font_size = .7;
    float font_weight = 2;
    int offset = 30;
#endif


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
 * Function Name     : get_runtime_data
 * Description       : Function to get inference data.
 * Arguments         : model_runtime runtime chosen for inference data extraction
 * Return value      : *float floatarr = processed output
 ******************************************/
float *get_runtime_data(MeraDrpRuntimeWrapper model_runtime)
{
    /* Get the number of output.  */
    auto output_num = model_runtime.GetNumOutput();
    /* get output buffer */
    auto output_buffer = model_runtime.GetOutput(0);
    g_out_size_arr = std::get<2>(output_buffer);
    floatarr.resize(g_out_size_arr);
     /* Post-processing for FP16 */
    if (InOutDataType::FLOAT16 == std::get<0>(output_buffer))
    {
        /* Extract data in FP16 <uint16_t>. */
        uint16_t *data_ptr = reinterpret_cast<uint16_t *>(std::get<1>(output_buffer));
        for (int n = 0; n < g_out_size_arr; n++)
        {
            /* Cast FP16 output data to FP32. */
            floatarr[n] = float16_to_float32(data_ptr[n]);
        }
    }
    return floatarr.data();
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
 * Function Name : keyboard_exit
 * Description   : function to exit on Enter Key press
 * Return value  : -
 ******************************************/
void keyboard_exit()
{
    std::cout << "\n[INFO] Keyboard Exit Thread Started\n";
    int32_t key = 0;
    while(true)
    {
        key = getchar();
        if (key == 10 || exitClick == true)
        {
            /* When key is pressed. */
            printf("[INFO] Enter key Detected.\n");
            exitClick = true;
            break;
        }
    }
    std::cout << "[INFO] Keyboard Exit Thread Finished" << std::endl;
}

/*****************************************
 * Function Name : query_device_status
 * Description   : function to check USB/MIPI device is connected.
 * Return value  : media_port, media port that device is connected.
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

/******************************************
 * Function Name : plot_graph
 * Description   : function to plot graph with respect to the threshold value.
 * Return value  : 1 if plot is ready else 0
 ******************************************/
int plot_graph()
{
    if((x.size()< 10 || y.size()< 10)) return 0;
    cv::Mat1d xData(x);
    cv::Mat1d yData(y);
    /* Set text position on graph*/
    cv::Ptr<cv::plot::Plot2d> plot = cv::plot::Plot2d::create(xData,yData);
    
    plot->setMaxY(1.25);
    plot->setMinY(-0.25);
    plot->setMaxX(count+1);
    plot->setShowText(false);
    plot->setInvertOrientation(true);
    plot->setPlotSize(50,50);
    /* Plot graph*/
    plot->render(display);
    return 1;
}



/*****************************************
 * Function Name : print_usage_info
 * Description   : function to print usage info.
 ******************************************/
void print_usage_info()
{   
    #ifdef V2H
        std::cout << "[INFO] usage: ./suspicious_activity USB|VIDEO [Input_file for VIDEO]" << std::endl;
    #elif V2L
        std::cout << "[INFO] usage: ./suspicious_activity USB|VIDEO|MIPI [Input_file for VIDEO]" << std::endl;
    #endif
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

    static struct timespec pre_start_time;
    static struct timespec pre_end_time;
    static struct timespec post_start_time;
    static struct timespec post_end_time;

    #ifdef V2H
        /*Variable for Performance Measurement*/
        static struct timespec cnn_inf_start_time;
        static struct timespec cnn_inf_end_time;
        static struct timespec mlp_inf_start_time;
        static struct timespec mlp_inf_end_time;

        float *extracted_feature;
    #elif V2L
        static struct timespec inf_start_time;
        static struct timespec inf_end_time;
    #endif

    float *violence_prediction;

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

        cv::Mat resized_image, float_image, normalized_image;
        cv::resize(input_image, resized_image, cv::Size(INPUT_WIDTH, INPUT_HEIGHT));
        cv::cvtColor(resized_image, resized_image, cv::COLOR_BGR2RGB);
        resized_image.convertTo(float_image, CV_32F, 1.0 / 255.0);

        cv::subtract(float_image, cv::Scalar(0.5, 0.5, 0.5), normalized_image);
        cv::divide(normalized_image, cv::Scalar(0.5, 0.5, 0.5), normalized_image);

        // Change HWC to CHW format
        std::vector<cv::Mat> channels(3);
        cv::split(normalized_image, channels);
        cv::Mat chw_image;
        cv::vconcat(channels, chw_image);

        if (!chw_image.isContinuous())
        chw_image = chw_image.clone();

        stacked_data.push_back(chw_image);

        ret = timespec_get(&pre_end_time, TIME_UTC);
        if ( 0 == ret)
        {
            fprintf(stderr, "[ERROR] Failed to get Pre-process End Time\n");
            goto err;
        }
        /*Pre-process Time Result*/
        pre_time = (float)((time_difference_msec(pre_start_time, pre_end_time)));

        std::cout << "\n[INFO] FRAMES STACKED : " << stacked_data.size() <<"\n";
        

        if (stacked_data.size() >= BATCH_SIZE)
        {   
            cv::Mat combined_frames;

            /* vertical concatenation */
            vconcat(stacked_data, combined_frames);
            
            #ifdef V2H

                cnn_runtime.SetInput(0, combined_frames.ptr<float>());

                /* get CNN inference start time */
                ret = timespec_get(&cnn_inf_start_time, TIME_UTC);
                if (0 == ret)
                {
                    fprintf(stderr, "[ERROR] Failed to get CNN Inference Start Time\n");
                }

                /*start CNN inference using drp runtime*/
                cnn_runtime.Run(drpai_freq);

                /* get CNN inference end time */
                ret = timespec_get(&cnn_inf_end_time, TIME_UTC);
                if (0 == ret)
                {
                    fprintf(stderr, "[ERROR] Failed to get CNN Inference End Time\n");
                }
                cnn_ai_time = (float)((time_difference_msec(cnn_inf_start_time, cnn_inf_end_time)));

                extracted_feature = get_runtime_data(cnn_runtime);
                mlp_runtime.SetInput(0, extracted_feature);

                /* get MLP inference start time */
                ret = timespec_get(&mlp_inf_start_time, TIME_UTC);
                if (0 == ret)
                {
                    fprintf(stderr, "[ERROR] Failed to get MLP Inference Start Time\n");
                }

                /*start MLP inference using drp runtime*/
                mlp_runtime.Run(drpai_freq);

                /* get MLP inference end time */
                ret = timespec_get(&mlp_inf_end_time, TIME_UTC);
                if (0 == ret)
                {
                    fprintf(stderr, "[ERROR] Failed to get MLP Inference End Time\n");
                }
                mlp_ai_time = (float)((time_difference_msec(mlp_inf_start_time, mlp_inf_end_time)));
                violence_prediction = get_runtime_data(mlp_runtime);

            #elif V2L
                runtime.SetInput(0, combined_frames.ptr<float>());
                /* get MLP inference start time */
                ret = timespec_get(&inf_start_time, TIME_UTC);
                if (0 == ret)
                {
                    fprintf(stderr, "[ERROR] Failed to get MLP Inference Start Time\n");
                }

                /*start inference using drp runtime*/
                runtime.Run();

                /* get inference end time */
                ret = timespec_get(&inf_end_time, TIME_UTC);
                if (0 == ret)
                {
                    fprintf(stderr, "[ERROR] Failed to get Inference End Time\n");
                }
                ai_time = (float)((time_difference_msec(inf_start_time, inf_end_time)));
                violence_prediction = get_runtime_data(runtime);

            #endif

            /* Post-processing part */
            /* get post-processing start time */
            ret = timespec_get(&post_start_time, TIME_UTC);
            if (0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to get Post-process Start Time\n");
            }

            int predictedClass = std::max_element(violence_prediction, violence_prediction + 2) - violence_prediction;
            result = (predictedClass == 0) ? violence : non_violence;

            if (result == non_violence)
            {
                val = 1;
            }
            else
            {
                val = 0;
            }

            count++;
            /* push back the count and threshold value to vector array */
            if(x.size()< 20 || y.size()< 20)
            {
                x.push_back(count);
                y.push_back(val);
            }
            else
            {
                x.erase(x.begin());
                y.erase(y.begin());
            }
            stacked_data.erase(stacked_data.begin(), stacked_data.begin() + BUFFER_SIZE);

            /* get post-processing end time */
            ret = timespec_get(&post_end_time, TIME_UTC);
            if (0 == ret)
            {
                fprintf(stderr, "[ERROR] Failed to get Post-process End Time\n");
            }
            post_time = (float)((time_difference_msec(post_start_time, post_end_time)));


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

    devices dev;
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

    printf("[INFO] Exit Thread Starting\n");
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
    printf("[INFO] Exit Thread Terminated\n");
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
    cv::VideoCapture g_cap;

    printf("[INFO] Capture Thread Starting\n");

    g_cap.open(gstream, cv::CAP_GSTREAMER);
    if (!g_cap.isOpened())
    {
        std::cout << "[ERROR] Error opening video stream or camera !\n"
                  << std::endl;
        goto err;
    }
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
    /* wayland Index = 0 */
    uint32_t idx = 0;

    /*font size to be used for text output*/
    int result_cnt = 0;
    float *extracted_feature;
    float *violence_prediction;

    cv::Mat bgra_image;
    
    std::string g_pipeline = "appsrc ! videoconvert ! autovideosink sync=false ";

    /*coordinates for total ai time*/
    cv::Point total_time_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 60);
    /*coordinates for pre-processing time*/
    cv::Point pre_process_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 60 + offset);
    /*coordinates for inference time*/
    cv::Point inf_position(DISP_IMAGE_OUTPUT_WIDTH + 10,  60 + (2 * offset));
    /*coordinates for post-processing time*/
    cv::Point post_process_postion(DISP_IMAGE_OUTPUT_WIDTH + 10,  60 + (3 * offset));
    cv::Point result_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 380);
    cv::Point plot_postion(DISP_IMAGE_OUTPUT_WIDTH + 20, 400);
    cv::Point threshold_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 600);
    cv::Point value_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 630);

    cv::Scalar Color;

    /* Initialize wayland */
    ret = wayland.init(idx, DISP_OUTPUT_WIDTH, DISP_OUTPUT_HEIGHT, IMAGE_CHANNEL_BGRA);
    if(0 != ret)
    {
        fprintf(stderr, "[ERROR] Failed to initialize Image for Wayland\n");
        goto err;
    }
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
            /*get all time calculations*/
            std::cout << "\n[INFO] pre-process Time(ms)               : " << float_to_string(pre_time) <<" ms \n";
            #ifdef V2H
                std::cout << "[INFO] CNN Inference Time(ms)             : " << float_to_string(cnn_ai_time) << " ms\n";
                std::cout << "[INFO] MLP Inference Time(ms)             : " << float_to_string(mlp_ai_time) << " ms\n";
                total_ai_time = pre_time + cnn_ai_time + mlp_ai_time + post_time;
            #elif V2L
                std::cout << "[INFO] Inference Time(ms)                 : " << float_to_string(ai_time) << " ms\n";
                total_ai_time = pre_time + ai_time + post_time;
            #endif

            std::cout << "[INFO] post-process Time(ms)              : " << float_to_string(post_time) <<" ms \n";

            g_fps = 1000/total_ai_time;
            std::cout<<"[INFO] FPS                                : "<<g_fps<<"\n";

            bgra_image = create_output_frame(yuyv_image);

            /*put inference time inside the display frame*/
            cv::putText(bgra_image, "Total AI Time (ms)  : " + float_to_string(total_ai_time), total_time_postion, 
                        cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
            
            cv::putText(bgra_image, "Preprocess  : " + float_to_string(pre_time), pre_process_postion, 
                        cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);

            #ifdef V2H
                cv::putText(bgra_image,"Inference Time  : " + float_to_string(cnn_ai_time + mlp_ai_time), inf_position, 
                        cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_thickness);
            #elif V2L
                cv::putText(bgra_image,"Inference Time  : " + float_to_string(ai_time), inf_position, 
                        cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_thickness);
            #endif

            cv::putText(bgra_image, "Postprocess  : " + float_to_string(post_time), post_process_postion, 
                            cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);

            Color = (result == violence) ? RED : GREEN;

            if (result != none)
            {   
                cv::putText(bgra_image,result, result_postion, 
                                cv::FONT_HERSHEY_SIMPLEX, font_size, Color, font_weight);
            }

            if(plot_graph())
            {
	            cv::resize(display, display, cv::Size(200, 150));
                cv::Rect roi(plot_postion, display.size());
                display.copyTo(bgra_image(roi));
                cv::putText(bgra_image,"1",cv::Point(DISP_IMAGE_OUTPUT_WIDTH, 425), cv::FONT_HERSHEY_COMPLEX,0.65,WHITE,1);
                cv::putText(bgra_image,"0",cv::Point(DISP_IMAGE_OUTPUT_WIDTH, 525), cv::FONT_HERSHEY_COMPLEX,0.65,WHITE,1);
            }
            std::stringstream low_pre;
            low_pre << std::fixed << std::setprecision(1) << threshold;
            std::string threshold_low_pre = low_pre.str();

            cv::putText(bgra_image, "Threshold : " + threshold_low_pre, threshold_postion, 
                            cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
            
            std::stringstream low_pre_val;
            low_pre_val << std::fixed << std::setprecision(1) << val;
            std::string val_low_pre = low_pre_val.str();

            cv::putText(bgra_image, "Value : " + val_low_pre, value_postion, 
                    cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
            cv::cvtColor(bgra_image, bgra_image, cv::COLOR_BGR2BGRA);
            /*Update Wayland*/
            wayland.commit(bgra_image.data, NULL);
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
    
    #ifdef V2H
        bool cnn_runtime_status = false;
        bool mlp_runtime_status = false;
    #elif V2L
        bool runtime_status = false;
    #endif

    std::string gstreamer_pipeline;

    

    if (argc < 2) 
    {     
        errorHandle = true;
    }
    else 
    {
      std::string input_source = argv[1];
      #ifdef V2H
        if (input_source == "USB" && argc >= 2)
      #elif V2L
        if ((input_source == "USB" || input_source == "MIPI") && argc >= 2)
      #endif
        errorHandle = false;
      else if(input_source == "VIDEO" && argc >= 3)
        errorHandle = false;
      else
        errorHandle = true;
    }
    if (errorHandle)
    {
        std::cout << "[ERROR] Please specify Input Source\n";
        print_usage_info();
        std::cout << "[INFO] End Application.\n";
        return -1;
    }

    std::string input_source = argv[1];
    switch (input_source_map[input_source])
    {   
        /* Input Source : Video */
        case 1:
        {
            std::cout << "[INFO] Video Mode \n";
            /* read input video */
            std::string video_path = argv[2];
            /* g-streamer pipeline to read input video source */
            gstreamer_pipeline = "filesrc location=" + video_path + " ! decodebin ! videoconvert ! appsink";
        }
        break;
        /* Input Source : USB Camera */
        case 2:
        {
            std::cout << "[INFO] USB CAMERA \n";
            std::string media_port = query_device_status("usb");
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
        }
        break;
        /* Input Source : MIPI Camera */
        case 3:
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
                std::cout << "[INFO] usage: ./suspicious_activity USB|VIDEO [Input_file for VIDEO].\n";
            #elif V2L
                std::cout << "[INFO] usage: ./suspicious_activity USB|VIDEO|MIPI [Input_file for VIDEO]\n";
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
    #elif V2L
        /* AI Application for RZ/V2L */
        printf("\nAI Application for RZ/V2L\n");
    #endif
    

    int drpai_fd = open("/dev/drpai0", O_RDWR);
    if (0 > drpai_fd)
    {
        std::cerr << "[ERROR] Failed to open DRP-AI Driver : errno=" << errno << std::endl;
        std::cout << "[INFO] End Application.\n";
        return -1;
    }
    /* Set drpai mem start address */
    uint64_t drpaimem_addr_start = 0;

    /*Load model_dir structure and its weight to runtime object */
    drpaimem_addr_start = init_drpai(drpai_fd);
   
    if ((uint32_t)NULL == drpaimem_addr_start) 
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address.\n");
        close(drpai_fd);
        goto end_main;
    }

    #ifdef V2H
        cnn_runtime_status = cnn_runtime.LoadModel(cnn_model_dir, drpaimem_addr_start+DRPAI_MEM_OFFSET);
        if(!cnn_runtime_status)
        {
            fprintf(stderr, "[ERROR] Failed to load CNN model.\n");
            close(drpai_fd);
            return -1;
        }
        std::cout << "[INFO] loaded CNN runtime model :" << cnn_model_dir << "\n\n";

        mlp_runtime_status = mlp_runtime.LoadModel(mlp_model_dir, drpaimem_addr_start);
        if(!mlp_runtime_status)
        {
            fprintf(stderr, "[ERROR] Failed to load MLP model.\n");
            close(drpai_fd);
            return -1;
        }
        std::cout << "[INFO] loaded MLP runtime model :" << mlp_model_dir << "\n\n";
    #elif V2L
        runtime_status = runtime.LoadModel(model_dir, drpaimem_addr_start);
        if(!runtime_status)
        {
            fprintf(stderr, "[ERROR] Failed to load the video classifier model.\n");
            close(drpai_fd);
            return -1;
        }
    #endif

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

    /* Create exit Thread */
    create_thread_exit = pthread_create(&exit_thread, NULL, R_exit_Thread, NULL);
    if (0 != create_thread_exit)
    {
        fprintf(stderr, "[ERROR] Failed to create exit Thread.\n");
        ret_main = -1;
        goto end_threads;
    }
    /* Detached exit thread */
    pthread_detach(exit_thread);

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
    /* Exit wayland */
    wayland.exit();
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