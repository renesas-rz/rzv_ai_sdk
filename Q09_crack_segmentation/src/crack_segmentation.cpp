/*
 * Original Code (C) Copyright Edgecortix, Inc. 2022
 * Modified Code (C) Copyright Renesas Electronics Corporation 2023
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
#include "MeraDrpRuntimeWrapper.h"
#include "opencv2/core.hpp"
#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <vector>
#include <glob.h>
#include <cmath>
#include <cstring>
#include <linux/drpai.h>
#include <fcntl.h>
#include <sys/ioctl.h>
/*DRP-AI memory area offset for model objects*/
/*Offset value depends on the size of memory area used by DRP-AI Pre-processing Runtime Object files*/
#define DRPAI_MEM_OFFSET    (0x38E0000)
/*Output text colour info */
#define WHITE   cv::Scalar(255, 255, 255)

/*Model input info*/
#define MODEL_IN_H          (224)
#define MODEL_IN_W          (224)

/*Total Display out*/
#define DISP_OUTPUT_WIDTH   (1280)
#define DISP_OUTPUT_HEIGHT  (720)
/*Image display out*/
#define IMAGE_OUTPUT_WIDTH  (960)
#define IMAGE_OUTPUT_HEIGHT (720)


/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper model_runtime;

/* flags to detect quit-key function and image mode*/
bool g_quit_application   = false;
bool g_image_mode         = false;

/* variables to calculate total fps and inference time */
int g_duration;
int g_fps;
uint32_t g_out_size_arr;

/* gstreamer output pipeline */
std::string g_pipeline = "appsrc ! videoconvert ! autovideosink sync=false ";
std::vector<float> floatarr(1);

cv::Mat g_frame;
cv::Mat g_fn_frame;
cv::VideoCapture g_cap;
cv::VideoWriter output_writer(g_pipeline, cv::CAP_GSTREAMER,cv::VideoWriter::fourcc('H', '2', '6', '4'), 1, 
                              cv::Size(DISP_OUTPUT_WIDTH, DISP_OUTPUT_HEIGHT), true);

/* Map to store input source list */
std::map<std::string, int> input_source_map =
{
    {"VIDEO", 1},
    {"IMAGE", 2},
    {"CAMERA", 3}
};

/*****************************************
* Function Name : get_drpai_start_addr
* Description   : Function to get the start address of DRP-AI Memory Area.
* Arguments     : -
* Return value  : uint32_t = DRP-AI Memory Area start address in 32-bit.
******************************************/
uint32_t get_drpai_start_addr()
{
    int fd  = 0;
    int ret = 0;
    drpai_data_t drpai_data;
    errno = 0;
    fd = open("/dev/drpai0", O_RDWR);
    if (0 > fd )
    {
        fprintf(stderr, "[ERROR] Failed to open DRP-AI Driver : errno=%d\n", errno);
        return (uint32_t)NULL;
    }
    /* Get DRP-AI Memory Area Address via DRP-AI Driver */
    ret = ioctl(fd , DRPAI_GET_DRPAI_AREA, &drpai_data);
    if (-1 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI Memory Area : errno=%d\n", errno);
        return (uint32_t)NULL;
    }
    return drpai_data.address;
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
 * Return value     : cv::Mat background, final display frame to be written to gstreamer pipeline
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
    model_runtime.Run();
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
 * Description   : function to convert white colur to green colur.
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
    float font_size = 0.65;
    /*font weight*/
    float font_weight = 2;

    /*coordinates for inference speed*/
    cv::Point ai_inf_postion(970, 60);
    /*coordinated for fps*/
    cv::Point fps_postion(975, 90);

    cv::Mat input_frame,output_frame;

    /* get inference start time */
    auto t1 = std::chrono::high_resolution_clock::now();
    
    cv::Size size(MODEL_IN_H, MODEL_IN_W);
    /*resize the image to the model input size*/
    cv::resize(frame, frame, size);
    input_frame = frame;
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

    cv::threshold(img_mask,img_mask,-0.5,255,cv::THRESH_BINARY);  
    img_mask.convertTo(img_mask,CV_8UC1);

    /* get inference end time */
    auto t2 = std::chrono::high_resolution_clock::now(); 
    
    g_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    g_fps = 1000/g_duration;
    std::cout << "\n[INFO] AI-Inference Time(ms): " << g_duration << " ms\n" <<"[INFO] FPS: "<<g_fps<<"\n";

    cv::cvtColor(img_mask, output_frame, cv::COLOR_RGB2BGR);

    /* convert white colur from output frame to green colur */
    output_frame = colour_convert(output_frame);

    /* blending both input and ouput frames that have same size and format and combined one single frame */
    cv::addWeighted(input_frame, 0.9, output_frame, 0.5, 0.0, output_frame);
    /* resize the output image with respect to output window size */
    cv::cvtColor(output_frame, output_frame, cv::COLOR_BGR2RGB);
    cv::resize(output_frame, output_frame, cv::Size(IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT));
    output_frame = create_output_frame(output_frame);
    /*put inference time inside the display frame*/
    cv::putText(output_frame, "AI Inference time : " + std::to_string(g_duration) + " [ms]", ai_inf_postion, 
                cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
    /*put FPS inside display frame*/
        cv::putText(output_frame, "       Total FPS : " + std::to_string(g_fps), fps_postion, 
                    cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
    return output_frame;
}

/*****************************************
 * Function Name    : get_quit_key
 * Description      : Get application quit key from keyboard
 *****************************************/
void get_quit_key(void)
{
    /*continuous loop for checking exist trigger*/
    while (true)
    {
        /*get input from the user */
        int key = getchar();
        /*if [ENTER] key is pressed*/
        if (key == 10)
        {
            std::cout << "[INFO] Enter Key Pressed!\n";
            g_quit_application = true;
        }
    }
}

/******************************************
 * Function Name : capture_frame
 * Description   : function to open camera or video source with respect to the source pipeline.
 * Arguments     : string cap_pipeline input source pipeline
 ******************************************/
void capture_frame(std::string cap_pipeline)
{
    std::cout << "cap pipeline" << cap_pipeline << "\n";
    /* Capture stream of frames from camera using Gstreamer pipeline */
    g_cap.open(cap_pipeline, cv::CAP_GSTREAMER);
    if (!g_cap.isOpened())
    {
        /* This section prompt an error message if no video stream is found */
        std::cout << "[ERROR] Error opening video stream or camera !\n"
                  << std::endl;
        return;
    }
    /* Taking an everlasting loop to show the output */
    while (true)
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
            /* check for image mode*/
            if(g_image_mode == true)
                return;
            /*write the final frame to the gstreamer pipeline*/
            output_writer.write(g_fn_frame);
            /* check for if the quit key is pressed */
            if(g_quit_application == true)
            {
                g_quit_application = false;
                break;
            }
        }
    }
    return;
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

int main(int argc, char **argv)
{
    uint64_t drpaimem_addr_start = 0;
    bool runtime_status = false;

    /* Gstreamer input pipeline*/
    std::string gstreamer_pipeline;
    /* Model Binary */
    std::string model_dir = "crack_segmentation_model";
    /* Load model_dir structure and its weight to runtime object */
    drpaimem_addr_start = get_drpai_start_addr();
    std::cout<<"drpaimem_addr_start: "<<drpaimem_addr_start<<"\n";
    if ((uint64_t)NULL == drpaimem_addr_start) 
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address.\n");
        return -1;
    }
    runtime_status = model_runtime.LoadModel(model_dir, drpaimem_addr_start+DRPAI_MEM_OFFSET);
    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load model.\n");
        return -1;
    }
    std::cout << "[INFO] loaded runtime model :" << model_dir << "\n\n";
    /* Get input Source WS/VIDEO/CAMERA */
    std::string input_source = argv[1];

    /* Thread to detect [ENTER] key to quit application */
    std::thread end_app_thread(get_quit_key);
    end_app_thread.detach();

    switch (input_source_map[input_source])
    {
        /* Input Source : Video */
        case 1:
        {
            std::cout << "[INFO] Video \n";
            /* read input video */
            std::string video_path = argv[2];
            /* gstremer pipeline to read input video source */
            gstreamer_pipeline = "filesrc location=" + video_path + " ! decodebin ! videoconvert ! appsink";
            capture_frame(gstreamer_pipeline);
        }
        break;
        /* Input Source : Image */
        case 2:
        {
            std::cout << "[INFO] Image \n";
            g_image_mode = true;
            /* read input image */
            std::string image_path = argv[2];
            /* gstremer pipeline to read input image source */
            gstreamer_pipeline = "filesrc location=" + image_path + " ! jpegdec ! videoconvert ! appsink";
            capture_frame(gstreamer_pipeline);
            
            std::cout<<"[INFO] Press [ENTER] key to End Application\n";
            while(g_quit_application == false)
                output_writer.write(g_fn_frame);
        }
        break;
        /* Input Source : Camera */
        case 3:
        {
            std::cout << "[INFO] CAMERA \n";
            /* gstremer pipeline to load camera */
            gstreamer_pipeline = "v4l2src device=/dev/video0 ! videoconvert ! appsink";
            /* MIPI Camera Setup */
            mipi_cam_init();
            /* Open camera and capture frame*/
            capture_frame(gstreamer_pipeline);
            break;
        }
        default:
        {
            std::cout << "[ERROR] Invalid Input source\n";
        }
    }
    std::cout << "[INFO] Application End\n";
    return 0;
}
