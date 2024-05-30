/*
 * Original Code (C) Copyright Edgecortx, Inc. 2022
 * Modified Code (C) Copyright Renesas Electronics Corporation 2024
 *　
 *  *1 DRP-AI TVM is powered by EdgeCortix MERA™ Compiler Framework.
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
 * File Name    : crack segmentation
 * Version      : 0.1
 * Description  : RZ/V2L SDK AI Application: Crack Segmentation
 ***********************************************************************************************************************/
/*****************************************
 * includes
 *****************************************/
#include <builtin_fp16.h>
#include <fstream>
#include <string>
#include <sys/time.h>
#include <cstdlib>
#include <climits>
#include <cstdlib>
#include <thread>
#include <cstring>
#include <vector>
#include <glob.h>
#include <cmath>
#include <cstring>
#include <unistd.h>
#include <linux/drpai.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "MeraDrpRuntimeWrapper.h"
#include "opencv2/core.hpp"
#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "wayland.h"
#include "utils.h"
#include <thread>

/*DRP-AI memory area offset for model objects*/
/*Offset value depends on the size of memory area used by DRP-AI Pre-processing Runtime Object files*/
#define DRPAI_MEM_OFFSET    (0)

/*Output text colour info */
#define WHITE   cv::Scalar(255, 255, 255)

/*Model input info*/
#define MODEL_IN_H          (224)
#define MODEL_IN_W          (224)

/*Total Display out*/
#define DISP_OUTPUT_WIDTH   (1920)
#define DISP_OUTPUT_HEIGHT  (1080)
/*Image display out*/
#define IMAGE_OUTPUT_WIDTH  (1480)
#define IMAGE_OUTPUT_HEIGHT (1080)

#define IMAGE_CHANNEL_BGRA          (4)

/* DRPAI_FREQ is the frequency settings  */
/* for DRP-AI.                           */
/* Basically use the default values      */

#define DRPAI_FREQ                  (2)
/* DRPAI_FREQ can be set from 1 to 127   */
/* 1,2: 1GHz                             */
/* 3: 630MHz                             */
/* 4: 420MHz                             */
/* 5: 315MHz                             */
/* ...                                   */
/* 127: 10MHz                            */
/* Calculation Formula:                  */
/*     1260MHz /(DRPAI_FREQ - 1)         */
/*     (When DRPAI_FREQ = 3 or more.)    */

/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper model_runtime;

/* flags to detect image mode*/
bool g_image_mode         = false;
/* flag for detecting double click*/
bool doubleClick          = false;

/* variables to calculate total fps and inference time */
int g_duration;
int g_fps;
uint32_t g_out_size_arr;

std::vector<float> floatarr(1);

cv::Mat g_frame;
cv::Mat g_fn_frame;
cv::VideoCapture g_cap;

static Wayland wayland;
static int32_t drpai_freq;

/* Map to store input source list */
std::map<std::string, int> input_source_map =
{
    {"VIDEO", 1},
    {"IMAGE", 2},
    {"USB", 3}
};

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
        std::cerr << "[ERROR] Failed to get DRP-AI Memory Area : errno=" << errno << std::endl;
        return 0;
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
    cv::resize(frame_g, resizedImage, cv::Size(IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT));
    /* Copy the resized image to the left side of the background (0 to 960) */
    cv::Rect roi(cv::Rect(0, 0, resizedImage.cols, resizedImage.rows));
    resizedImage.copyTo(background(roi));
    return background;
}

/*****************************************
 * Function Name     : start_preprocessing
 * Description       : Function to perform the pre processing.
 * Arguments         : cv::Mat frame = frame input address
 * Return value      : cv::Mat frame = pre-processed mat frame output
 ******************************************/
cv::Mat start_preprocessing(cv::Mat frame)
{
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    frame = hwc2chw(frame);
    /*convert to FP32*/
    frame.convertTo(frame, CV_32FC3,1.0 / 255.0, 0);
    /*deep copy, if not continuous*/
    if (!frame.isContinuous())
    frame = frame.clone();
    return frame;
}

/*****************************************
 * Function Name     : start_runtime
 * Description       : Function to perform the pre processing and post processing.
 * Arguments         : *input = frame input address
 * Return value      : *float floatarr = pre-processed and post-processed output
 ******************************************/
float *start_runtime(float *input)
{
    /*Set Pre-processing output to be inference input. */
    model_runtime.SetInput(0, input);
    model_runtime.Run(drpai_freq);
    /* Get the number of output.  */
    auto output_num = model_runtime.GetNumOutput();
    if (output_num != 1)
    {
        std::cout << "[ERROR] Output size : not 1." << std::endl;
        abort();
    }
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
 * Function Name : colour_convert
 * Description   : function to convert white colour to green colour.
 * Arguments     : Mat image
 * Return value  : Mat result
 ******************************************/
cv::Mat colour_convert(cv::Mat image)
{
    /* Convert the image to HSV */ 
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    /* Define the lower and upper HSV range for white color */
    cv::Scalar lower_white = cv::Scalar(0, 0, 200); // Adjust these values as needed
    cv::Scalar upper_white = cv::Scalar(180, 30, 255); // Adjust these values as needed

    /* Create a mask for the white color */
    cv::Mat mask;
    cv::inRange(hsv, lower_white, upper_white, mask);

    /* Create a green image */
    cv::Mat green_image = cv::Mat::zeros(image.size(), image.type());
    green_image.setTo(cv::Scalar(0, 100, 0), mask);

    /* Replace white regions in the original image with green */
    cv::Mat result;
    cv::bitwise_and(image, image, result, ~mask);
    cv::add(result, green_image, result);
    cv::resize(result, result, cv::Size(MODEL_IN_H, MODEL_IN_W));
    /* return result */
    return result;
}

/*****************************************
 * Function Name : run_inference
 * Description   : takes Mat frame as the input and passes through the model runtime and returns the output
 * Arguments     : Mat frame
 * Return value  : Mat frame
 ******************************************/
cv::Mat run_inference(cv::Mat frame)
{
    float *output;
    /*font size to be used for text output*/
    float font_size = .9;
    /*font weight*/
    float font_weight = 2;
    float min_threshold = 0.3;

    /*coordinates for inference speed*/
    cv::Point ai_inf_postion(IMAGE_OUTPUT_WIDTH + 10, 60);
    /*coordinated for fps*/
    cv::Point fps_postion(IMAGE_OUTPUT_WIDTH + 15, 90);

    cv::Mat input_frame,output_frame;
    input_frame = frame;

    /* get inference start time */
    auto t1 = std::chrono::high_resolution_clock::now();
    
    cv::Size size(MODEL_IN_H, MODEL_IN_W);
    /*resize the image to the model input size*/
    cv::resize(frame, frame, size);
    auto t1_pre = std::chrono::high_resolution_clock::now();
    /* start pre-processing */
    frame = start_preprocessing(frame);
    auto t2_pre = std::chrono::high_resolution_clock::now(); 
    int preprocess_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2_pre - t1_pre).count();
    std::cout << "\n[INFO] preprocess Time(ms): " << preprocess_duration <<" ms \n";

    /*start inference using drp runtime*/
    output = start_runtime(frame.ptr<float>());
    /* convert float32 format to opencv mat image format */ 
    cv::Mat img_mask(MODEL_IN_H,MODEL_IN_W,CV_32F,(void*)output);
    /* setting minimum threshold to heatmap */ 
    cv::threshold(img_mask,img_mask,min_threshold,0.0,cv::THRESH_TOZERO);
    cv::normalize(img_mask, img_mask, 0.0, 1.0, cv::NORM_MINMAX);
    /* Scale the float values to 0-255 range for visualization */
    cv::Mat heatmap_scaled;
    img_mask.convertTo(heatmap_scaled, CV_8U, 255.0);
    /* Create a grayscale heatmap */
    cv::applyColorMap(heatmap_scaled, img_mask, cv::COLORMAP_INFERNO);

    /* get inference end time */
    auto t2 = std::chrono::high_resolution_clock::now(); 
    
    g_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    g_fps = 1000/g_duration;
    std::cout << "\n[INFO] AI-Inference Time(ms): " << g_duration << " ms\n" <<"[INFO] FPS: "<<g_fps<<"\n";

    cv::cvtColor(img_mask, output_frame, cv::COLOR_RGB2BGR);

    /* convert white colour from output frame to green colour */
    output_frame = colour_convert(output_frame);

    cv::resize(input_frame, input_frame, cv::Size(IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT));
    cv ::cvtColor(input_frame, input_frame, cv::COLOR_RGB2BGR);
    cv::resize(output_frame, output_frame, cv::Size(IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT));
    cv::threshold(output_frame, output_frame, 0.7, 255, 3);

    /* blending both input and ouput frames that have same size and format and combined one single frame */
    cv::addWeighted(input_frame, 1.0, output_frame, 0.5, 0.0, output_frame);
    /* resize the output image with respect to output window size */
    cv::cvtColor(output_frame, output_frame, cv::COLOR_RGB2BGR);
    output_frame = create_output_frame(output_frame);
    /*put inference time inside the display frame*/
    cv::putText(output_frame, "AI Inference time [ms] : " + std::to_string(g_duration), ai_inf_postion, 
                cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
    /*put FPS inside display frame*/
    cv::putText(output_frame, "       Total FPS : " + std::to_string(g_fps), fps_postion, 
                    cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
    cv::Point text_pos(IMAGE_OUTPUT_WIDTH + 10, IMAGE_OUTPUT_HEIGHT - 40);

    return output_frame;
}

/******************************************
 * Function Name : capture_frame
 * Description   : function to open camera or video source with respect to the source pipeline.
 * Arguments     : string cap_pipeline input source pipeline
 ******************************************/
void capture_frame(std::string cap_pipeline,std::string input_source)
{
    /* Capture stream of frames from camera using G-streamer pipeline */
    g_cap.open(cap_pipeline, cv::CAP_GSTREAMER);
    if (!g_cap.isOpened())
    {
        /* This section prompt an error message if no video stream is found */
        std::cout << "[ERROR] Error opening "<< input_source <<" source!!\n"
                  << std::endl;
        return;
    }
    /* Taking an everlasting loop to show the output */
    while (!doubleClick)
    {
        g_cap >> g_frame;
        /* Breaking the loop if no video frame is detected */
        if (g_frame.empty())
        {
            std::cout << "[INFO] Video ended or corrupted frame !\n";
            return;
        }
        else
        {   
            /* run inference with respect to captured frame */         
            g_fn_frame = run_inference(g_frame);
            cv::cvtColor(g_fn_frame, g_fn_frame, cv::COLOR_BGR2BGRA);
            /* check for image mode*/
            if(g_image_mode == true)
                return;
            wayland.commit(g_fn_frame.data, NULL);
        }
    }
    return;
}

/*****************************************
 * Function Name : mouse_exit
 * Description   : function to exit on double click
 * Return value  : -
 ******************************************/
void mouse_exit()
{
    std::cout << "\n[INFO] Exit Thread Started" << std::endl;
    std::cout << "\n[INFO] Double Click To Exit" << std::endl;
    devices dev;
    dev.detect_mouse_click();
}

/*****************************************
 * Function Name : keyboard_exit
 * Description   : function to exit on double click
 * Return value  : -
 ******************************************/
void keyboard_exit()
{
    std::cout << "\n[INFO] Keyboard Exit Thread Started" << std::endl;
    int32_t key = 0;
    while(true)
    {
        key = getchar();
        if (key == 10 || doubleClick == true)
        {
            /* When key is pressed. */
            printf("[INFO] Enter key Detected.\n");
            doubleClick = true;
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

int main(int argc, char **argv)
{
    bool runtime_status = false;
    uint64_t drpaimem_addr_start = 0;

    /*Disable OpenCV Accelerator due to the use of multithreading */
    unsigned long OCA_list[16];
    for(int i = 0; i < 16; i++) OCA_list[i] = 0;
    OCA_Activate(&OCA_list[0]);

    /* G-streamer input pipeline*/
    std::string gstreamer_pipeline;
    /* Model Binary */
    std::string model_dir = "crack_segmentation_model";


    /* Check the input source is valid.*/
    if (argc < 2 || argc > 4) 
    {
        std::cout << "\n[ERROR] Please specify Input Source" << std::endl;
        std::cout << "[INFO] usage: ./crack_segmentation USB|VIDEO|IMAGE [Input_file for VIDEO/IMAGE]" << std::endl;
        std::cout << "\n[INFO] End Application\n";
        return -1;
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
    /* DRP-AI Frequency Setting */
    if (args.find("--drpai_freq") != args.end() && std::stoi(args["--drpai_freq"]) <= 127 && std::stoi(args["--drpai_freq"]) > 0) 
        drpai_freq = std::stoi(args["--drpai_freq"]);
    else 
        drpai_freq = DRPAI_FREQ;
    std::cout<<"\n[INFO] DRPAI FREQUENCY : "<<drpai_freq<<"\n";

    errno = 0;
    int drpai_fd = open("/dev/drpai0", O_RDWR);
    if (0 > drpai_fd)
    {
        std::cerr << "[ERROR] Failed to open DRP-AI Driver : errno=" << errno << std::endl;
        return -1;
    }

    /* Initialize DRP-AI (Get DRP-AI memory address and set DRP-AI frequency)*/
    drpaimem_addr_start = init_drpai(drpai_fd);
    std::cout<<"drpaimem_addr_start: "<<drpaimem_addr_start<<"\n";
    if (drpaimem_addr_start == 0) 
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address.\n");
        close(drpai_fd);
	    return -1;
    }
    runtime_status = model_runtime.LoadModel(model_dir, drpaimem_addr_start+DRPAI_MEM_OFFSET);
    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load model.\n");
	    close(drpai_fd);
        return -1;
    }
    std::cout << "[INFO] loaded runtime model :" << model_dir << "\n\n";

    /* Initialize wayland */
    int8_t ret = 0;
    ret = wayland.init(0, DISP_OUTPUT_WIDTH, DISP_OUTPUT_HEIGHT, IMAGE_CHANNEL_BGRA);
    if(0 != ret)
    {
        fprintf(stderr, "[ERROR] Failed to initialize Image for Wayland\n");
        return -1;
    }

    std::thread exit_thread(mouse_exit);
    exit_thread.detach();
    std::thread keyboard_exit_thread(keyboard_exit);
    keyboard_exit_thread.detach();

    /* Get input Source WS/VIDEO/CAMERA */
    std::string input_source = argv[1];
    switch (input_source_map[input_source])
    {
        /* Input Source : Video */
        case 1:
        {
            std::cout << "[INFO] Video \n";
            /* read input video */
            std::string video_path = argv[2];
            /* g-streamer pipeline to read input video source */
            gstreamer_pipeline = "filesrc location=" + video_path + " ! decodebin ! videoconvert ! appsink";
            capture_frame(gstreamer_pipeline,input_source);
        }
        break;
        /* Input Source : Image */
        case 2:
        {
            std::cout << "[INFO] Image \n";
            g_image_mode = true;
            /* read input image */
            std::string image_path = argv[2];
            /* g-streamer pipeline to read input image source */
            gstreamer_pipeline = "filesrc location=" + image_path + " ! jpegdec ! videoconvert ! appsink";
            capture_frame(gstreamer_pipeline,input_source);
            while(doubleClick == false)
            {
                wayland.commit(g_fn_frame.data, NULL);
            }
        }
        break;
        /* Input Source : USB Camera */
        case 3:
        {
            std::cout << "[INFO] USB CAMERA \n";
            /* check the status of device */
            std::string media_port = query_device_status("usb");
            /* g-streamer pipeline to read input image source */
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
            capture_frame(gstreamer_pipeline,input_source);
            break;
        }
        /* default case */
        default:
        {
            std::cout << "[ERROR] Invalid Input source\n";
            std::cout << "\n[ERROR] Please specify Input Source" << std::endl;
            std::cout << "[INFO] usage: ./crack_segmentation USB|VIDEO|IMAGE [Input_file for VIDEO/IMAGE]" << std::endl;
            std::cout << "\n[INFO] End Application\n";
        return -1;
        }
    }
    close(drpai_fd);
    wayland.exit();
    std::cout << "[INFO] Application End\n";
    return 0;
}
