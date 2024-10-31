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
/*****************************************
 * includes
 ******************************************/
#include <builtin_fp16.h>
#include <fstream>
#include <sys/time.h>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <glob.h>
#include <cmath>
#include <unistd.h>
#include <linux/drpai.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

#include "MeraDrpRuntimeWrapper.h"
#include "face.h"

#ifdef V2H
    /* DRPAI_FREQ is the frequency settings  */
    /* for DRP-AI.                           */
    /* Basically use the default values      */
    #define DRPAI_FREQ                 (2)
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
#endif


/*Wayland Display Image Information*/
#ifdef V2H
    #define IMAGE_OUTPUT_WIDTH          (1820)
    #define IMAGE_OUTPUT_HEIGHT         (980)
#elif V2L
    #define IMAGE_OUTPUT_WIDTH          (1180)
    #define IMAGE_OUTPUT_HEIGHT         (620)
#endif
#define IMAGE_CHANNEL_BGRA          (4)

/*Output text colour info */
#define BLUE                        cv::Scalar(255, 0, 0)
#define WHITE                       cv::Scalar(255, 255, 255)
#define BLACK                       cv::Scalar(0, 0, 0)
#define GREEN                       cv::Scalar(0, 255, 0)
#define RED                         cv::Scalar(0, 0, 255)
#define ASH                         cv::Scalar(150, 150, 150)

/* GUI button "Add ID Image" */
unsigned int add_faces_x0   = 0;
unsigned int add_faces_y0   = 0;
unsigned int add_faces_x1   = 0;
unsigned int add_faces_y1   = 0;

/* GUI button "Validate" */
unsigned int recognize_x0   = 0;
unsigned int recognize_y0   = 0;
unsigned int recognize_x1   = 0;
unsigned int recognize_y1   = 0;

/* GUI button "add_face" or "validate" */
int btn_x;
int btn_y;
int btn_w;
int btn_h;

/* Map to store input camera source list */
std::map<std::string, int> input_source_map =
{
    {"USB", 1},
    #ifdef V2L
        {"MIPI", 2}
    #endif
};

std::string gstreamer_pipeline;
uint64_t drpaimem_addr_start = 0;
/*DRP-AI memory area offset for model objects*/
/*Offset value depends on the size of memory area used by DRP-AI Pre-processing Runtime Object files*/
#define DRPAI_MEM_OFFSET            (0)
/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper runtime;
#ifdef V2H
    /*DRP-AI Frequency setting*/
    static int32_t drpai_freq;
#endif
std::string model_dir   = "facenet_model";

bool add_face_clicked           = false;
bool recognize_face_clicked     = false;
bool termination_clicked        = false;
bool capture_key_hit            = false;
bool has_captured_img1          = false;
bool has_captured_img2          = false;
bool backButtonClicked          = false;
bool addOrValidateButtonClicked = false;

/*****************************************
* Function Name : get_drpai_start_addr
* Description   : Get DRP-AI Memory Area Address via DRP-AI Driver
* Arguments     : -
* Return value  : drpai start address 
******************************************/
#ifdef V2H
    uint64_t get_drpai_start_addr(int drpai_fd)
#elif V2L
    uint32_t get_drpai_start_addr(int drpai_fd)
#endif
{
    int fd  = 0;
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

/*****************************************
 * Function Name : get_input_source
 * Description   : function to check the camera source is MIPI or USB
 * Return value  : return -1 , ERROR condition.
 *                 return 0 , success.  
 ******************************************/
int get_input_source(std::string camera_source)
{
    switch (input_source_map[camera_source])
    {
        /* Input Source : USB Camera */
        case 1:
        {
            std::cout << "[INFO] USB CAMERA \n";
            /* check the status of device */
            std::string media_port = query_device_status("usb");
            if (media_port == "")
            {
                fprintf(stderr, "\n[ERROR] USB Camera not connected. \n");
                return -1;
            }
            /* gstremer pipeline to read input image source */
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
            break;
        }
        /* Input Source : MIPI Camera */
        case 2:
        {
            std::cout << "[INFO] MIPI CAMERA \n";
            mipi_cam_init();
            /* check the status of device */
            std::string media_port = query_device_status("CRU");
            /* gstremer pipeline to read input image source */
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
        }
        break;

        /* default case/ Invalid case */
        default:
        {
            std::cout<<"\n[ERROR] Invalid input source\n";
            #ifdef V2H
                std::cout<<"[INFO] usage: ./face_recognition USB\n";
            #elif V2L
                std::cout<<"[INFO] usage: ./face_recognition USB|MIPI\n";
            #endif
            std::cout<<"[INFO] End Application\n";
            return -1;
        }
    }
    return 0;
}

/*****************************************
 * Function Name : hwc2chw
 * Description   : This function takes an input image in HWC (height, width, channels)
 *                 format and returns an output image in CHW (channels, height, width) format.
 * Arguments     : image = cv::Mat
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
 * Function Name : run_inference
 * Description   : This is a function that takes a cropped image as input, runs inference on it using a runtime object,
 *                 and returns a vector of float values as output.
 * Arguments     : croppedImg = Mat format.
 *
 * Return value  : The return value of the above function is a vector of float values.
 *                 These float values represent the output of a neural network inference model run on the input image.
 ******************************************/
std::vector<float> run_inference(cv::Mat croppedImg)
{
    static struct timespec start_time;
    static struct timespec end_time;
    static float ai_time = 0;
    std::vector<cv::Mat> bgr_channels;
    split(croppedImg, bgr_channels);
    cv::Mat eq_b, eq_g, eq_r;
    equalizeHist(bgr_channels[0], eq_b);
    equalizeHist(bgr_channels[1], eq_g);
    equalizeHist(bgr_channels[2], eq_r);
    std::vector<cv::Mat> eq_channels = {eq_b, eq_g, eq_r};
    cv::Mat eq;
    merge(eq_channels, eq);
    croppedImg = eq;
    cv::Mat patch1;
    std::vector<float> floatarr_inf(2);
    cv::Mat rgb_img;
    cv::Mat resized_img;
    cv::Size size(160, 160);
    cv::resize(croppedImg, resized_img, size, cv::INTER_LINEAR);
    cv::cvtColor(resized_img, rgb_img, cv::COLOR_BGR2RGB);
    cv::Mat inp_img;
    inp_img = hwc2chw(rgb_img);
    patch1 = inp_img;
    uint8_t ret = 0;
    cv::Mat patch_con;
    if (!patch1.isContinuous())
        patch_con = patch1.clone();
    else
        patch_con = patch1;
    cv::Mat patch_norm;
    cv::normalize(patch_con, patch_norm, 0, 1, cv::NORM_MINMAX, CV_32FC1);
    float *temp_input = new float[patch_norm.rows * patch_norm.cols * 3];
    memcpy(temp_input, patch_norm.ptr<float>(), patch_norm.total() * 3 * sizeof(float));
    runtime.SetInput(0, temp_input);
    /*Gets inference starting time*/
    timespec_get(&start_time, TIME_UTC);
    /*start inference using drp runtime*/
    #ifdef V2H
        runtime.Run(drpai_freq);
    #elif V2L
        runtime.Run();
    #endif
    timespec_get(&end_time, TIME_UTC);
    ai_time = (float)((timedifference_msec(start_time, end_time)));
    std::cout << "[Info] AI Inference time: " << ai_time << std::endl;
    auto output_num = runtime.GetNumOutput();
    if (output_num != 1)
    {
        std::cerr << "[ERROR] Output size : not 1." << std::endl;
        std::vector<float> error = {0};
        return error;
    }
    auto output_buffer = runtime.GetOutput(0);
    int64_t out_size = std::get<2>(output_buffer);
    floatarr_inf.resize(out_size);
    float *data_ptr = reinterpret_cast<float *>(std::get<1>(output_buffer));
    for (int n = 0; n < out_size; n++)
    {
        floatarr_inf[n] = data_ptr[n];
    }
    delete[] temp_input;
    return floatarr_inf;
}

/*****************************************
 * Function Name : ButtonCallBack.
 * Description   : This is a mouse callback function that is triggered when a mouse button is clicked.
 * Arguments     : event: represents the mouse event (e.g., left button down, right button up)
 *                 x, y: the x and y coordinates of the mouse click.
 *                 flags: additional flags associated with the mouse event (e.g., control key pressed).
 *                 userdata: a pointer to user-defined data that can be used to pass additional information 
 *                 to the callback function.
 ******************************************/
void ButtonCallBack(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        cv::Rect backButton = cv::Rect(0, 0, 120, 60);
        cv::Rect addOrValidateButton = cv::Rect(btn_x, btn_y, btn_w, btn_h);
        if (backButton.contains(cv::Point(x, y)))
        {
            backButtonClicked = true;
            std::cout<<"[INFO] Back Button Clicked\n";
        }
        else if (addOrValidateButton.contains(cv::Point(x, y)))
        {
            addOrValidateButtonClicked = true;
            std::cout<<"[INFO] Captured Frame\n";
        }
    }
    else if(event == cv::EVENT_LBUTTONDBLCLK)
    {
        backButtonClicked = true;
        termination_clicked = true;
    }
}

/*****************************************
 * Function Name : capture_frame
 * Description   : This function captures a frame from a video source (in this case, a webcam) 
 *                 and displays it on the screen.
 * Arguments     : string cap_pipeline input source pipeline
 * Return value  : returns the cropped image as a Mat object.
 ******************************************/
cv::Mat capture_frame(std::string cap_pipeline)
{
    std::cout << "Capture frame\n";
    cv::VideoCapture vid;
    vid.set(cv::CAP_PROP_BUFFERSIZE, 2);
    cv::Mat frame;
    cv::Mat img;
    cv::Mat croppedImg;
    
    vid.open(cap_pipeline, cv::CAP_GSTREAMER);
    vid >> frame;
    cv::resize(frame, frame, cv::Size(IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT));
    int height = frame.rows;
    int width = frame.cols;
    cv::Rect roi((int)(frame.cols/2-width/8), (int)(frame.rows/2-width/8), width/3, height/3); /* x,y,w,h */ 
    cv::Point pt1((int)(width/2-width/6), (int)(height/2-width/6));
    cv::Point pt2((int)(width/2+width/6), (int)(height/2+width/6));
    cv::Point btn_pt1((int)(width/2-width/10), (int)(height/2-width/4));
    cv::Point btn_pt2((int)(width/5), (int)(height/10));
    cv::Point txt_pt1((int)(width/2 - 240), (int)(height/6));
    cv::Point txt_pt2((int)(width/2 - 200), (int)(height/6));
    btn_x = (int)(IMAGE_OUTPUT_WIDTH * 0.5 - 100);
    btn_y = (int)(IMAGE_OUTPUT_HEIGHT * 0.85);
    btn_w = (int)(220);
    btn_h = (int)(60);
    capture_key_hit = false;
    while (!capture_key_hit)
    {
        vid >> frame;
        cv::cvtColor(frame, frame, cv::COLOR_BGR2BGRA);
        cv::resize(frame, frame, cv::Size(IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT));
        cv::flip(frame, img, 1);
        cv::rectangle(img, pt1, pt2, BLUE, 3);

        /* back button */
        cv::Rect backButton(0, 0, 120, 60);
        cv::rectangle(img, backButton, ASH, -1);
        cv::putText(img, "Back", cv::Point(30, 35), cv::FONT_HERSHEY_SIMPLEX, 0.8, BLACK, 2, cv::LINE_AA);
        
        /* add-face or validate button and text*/
        cv::Rect addOrValidateButton(btn_x, btn_y, btn_w, btn_h);
        cv::rectangle(img, addOrValidateButton, ASH, -1);
        if(add_face_clicked)
        {
            cv::putText(img, "Adjust ID image into the box!", txt_pt1, cv::FONT_HERSHEY_SIMPLEX, 1, BLUE, 2, cv::LINE_AA);
            cv::putText(img, "Add Face", cv::Point(btn_x + 40, btn_y + 40), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2, cv::LINE_AA);
        }
        else if(recognize_face_clicked)
        {
            cv::putText(img, "Adjust Face into the box!", txt_pt2, cv::FONT_HERSHEY_SIMPLEX, 1, BLUE, 2, cv::LINE_AA);
            cv::putText(img, "Validate", cv::Point(btn_x + 50, btn_y + 40), cv::FONT_HERSHEY_SIMPLEX, 1, BLACK, 2, cv::LINE_AA);
        }
        cv::waitKey(10);
        if(addOrValidateButtonClicked || backButtonClicked)
        {
            if(addOrValidateButtonClicked && add_face_clicked)
            {
                has_captured_img1 = true;
            }
            else if(addOrValidateButtonClicked && recognize_face_clicked)
            {
                has_captured_img2 = true;
            }
            capture_key_hit = true;
        }

        cv::imshow("Select face", img);  
        cv::setMouseCallback("Select face", ButtonCallBack);
    }
    addOrValidateButtonClicked = false;
    backButtonClicked = false;
    cv::destroyWindow("Select face");
    croppedImg = img(roi); 
    cv::resize(croppedImg, croppedImg, cv::Size(64, 64), cv::INTER_LINEAR);
    return croppedImg;
}

/*****************************************
 * Function Name : mouse_callback_button_click.
 * Description   : This is a mouse callback function that is triggered when a mouse button is clicked.
 * Arguments     : event: represents the mouse event (e.g., left button down, right button up)
 *                 x, y: the x and y coordinates of the mouse click.
 *                 flags: additional flags associated with the mouse event (e.g., control key pressed).
 *                 userdata: a pointer to user-defined data that can be used to pass additional information 
 *                 to the callback function.
 ******************************************/
void mouse_callback_button_click(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (add_faces_x0 < x && x < add_faces_x1 && add_faces_y0 < y && y < add_faces_y1)
        {
            std::cout << "[INFO] Clicked add face \n";
            add_face_clicked = true;
        }
        else if (recognize_x0 < x && x < recognize_x1 && recognize_y0 < y && y < recognize_y1) 
        {
            std::cout << "[INFO] Cliked compare face \n";
            recognize_face_clicked = true;
        }
    }
    /*mouse button double click callback*/ 
    else if (event == cv::EVENT_LBUTTONDBLCLK)
    {
        std::cout << "[INFO] Double tap !!\n";
        termination_clicked = true;
    }
}

int main(int argc, char **argv)
{
    /* check the input source is valid or not */
    if(argc < 2)
    {
        /* End application */
        std::cout<<"\n[ERROR] Please specify Input Source.\n";
        #ifdef V2H
            std::cout<<"[INFO] usage: ./face_recognition USB\n";
        #elif V2L
            std::cout<<"[INFO] usage: ./face_recognition USB|MIPI\n";
        #endif

        std::cout << "\n[INFO] End Application.\n";
        return -1;
    }
    std::string input_source = argv[1];
    /* check input source status */
    int source_status = get_input_source(input_source);
    if(source_status < 0)
        return -1;
    #ifdef V2H
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

        std::cout << "\n[INFO] DRPAI FREQUENCY : " << drpai_freq << "\n";
    #endif

    int drpai_fd = open("/dev/drpai0", O_RDWR);
    if (0 > drpai_fd)
    {
        std::cerr << "[ERROR] Failed to open DRP-AI Driver : errno=" << errno << std::endl;
        std::cout << "[INFO] End Application.\n";
        return -1;
    }

    /*Load model_dir structure and its weight to runtime object */
    drpaimem_addr_start = init_drpai(drpai_fd);
    bool runtime_status = false;
    if ((uint32_t)NULL == drpaimem_addr_start) 
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address.\n");
        return 0;
    }

    runtime_status = runtime.LoadModel(model_dir, drpaimem_addr_start + DRPAI_MEM_OFFSET);

    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load model.\n");
        return 0;
    }

    std::cout << "[INFO] Loaded model: " << model_dir << std::endl;
    
    /* GUI window */
    const std::string app_name = "Face Recognition";
    /* set output window */
    cv::namedWindow(app_name, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_NORMAL);

    add_faces_x0 = (int)(IMAGE_OUTPUT_WIDTH*0.25);
    add_faces_y0 = (int)(IMAGE_OUTPUT_HEIGHT*0.75 - 40);
    add_faces_x1 = (int)(IMAGE_OUTPUT_WIDTH*0.25 + 275);
    add_faces_y1 = (int)(IMAGE_OUTPUT_HEIGHT*0.75 + 40);
    recognize_x0 = (int)(IMAGE_OUTPUT_WIDTH*0.75 - 275);
    recognize_y0 = (int)(IMAGE_OUTPUT_HEIGHT*0.75 - 40);
    recognize_x1 = (int)(IMAGE_OUTPUT_WIDTH*0.75);
    recognize_y1 = (int)(IMAGE_OUTPUT_HEIGHT*0.75 + 40);
    int center_w = (int)(IMAGE_OUTPUT_WIDTH*0.5);
    int quater_h = (int)(IMAGE_OUTPUT_HEIGHT*0.25);

    cv::Mat bg_image = cv::imread("face_rec_bg.jpg");
    cv::Mat output_image;
    // cv::cvtColor(bg_image, bg_image, cv::COLOR_BGR2BGRA);
    cv::resize(bg_image, bg_image, cv::Size(IMAGE_OUTPUT_WIDTH, IMAGE_OUTPUT_HEIGHT));
    output_image = bg_image.clone();
    cv::imshow(app_name, output_image);
    int attempt = 0;
    Face face;   

    while(cv::waitKey(1))
    {
        output_image = bg_image.clone();
        if(add_face_clicked) 
        {
            /* capture pre-processed image */
            cv::Mat croppedImg = capture_frame(gstreamer_pipeline);
            /* run inference */
            face.setImage_arr1(run_inference(croppedImg));
            if (has_captured_img1)
            {
                cv::putText(output_image, "Face added !!", cv::Point(center_w - 110 , quater_h - 40), cv::FONT_HERSHEY_SIMPLEX, 1.0, GREEN, 2);
                attempt = 0;
            }
            cv::imshow(app_name, output_image);
            cv::waitKey(2000);
            add_face_clicked = false;

        }
        else if(recognize_face_clicked) 
        {
            if(!has_captured_img1)
            {
                cv::putText(output_image, "Add ID image before validation", cv::Point(center_w - 200 , quater_h - 40), cv::FONT_HERSHEY_SIMPLEX, 0.8, RED, 2);
            }
            else
            {
                cv::Mat croppedImg = capture_frame(gstreamer_pipeline);
                face.setImage_arr2(run_inference(croppedImg));
            }
            if(has_captured_img1 && has_captured_img2)
            {
                attempt++;
                has_captured_img2 = false;
                if(attempt == 3)
                {
                    has_captured_img1 = false;
                    has_captured_img2 = false;
                }
                if("match" == face.compare_with_existing_faces())
                {
                    std::cout<< "Face authentication using ID is succesfull" <<std::endl;
                    cv::putText(output_image, "Face authentication using ID is succesfull !!!", cv::Point(center_w - 350 , quater_h - 40), cv::FONT_HERSHEY_SIMPLEX, 1.0, GREEN, 2);
                }
                else
                {
                    std::cout<< "Face authentication failed" <<std::endl;
                    cv::putText(output_image, "Face authentication failed !!!", cv::Point(center_w - 250 , quater_h - 40), cv::FONT_HERSHEY_SIMPLEX, 1.0, RED, 2);
                }
                cv::putText(output_image, "Remaining attempts: " + std::to_string((3 - attempt)), cv::Point(center_w - 210, IMAGE_OUTPUT_HEIGHT - 100), cv::FONT_HERSHEY_SIMPLEX, 1.0, GREEN, 2);
            }
            cv::imshow(app_name, output_image);
            cv::waitKey(2000);
            recognize_face_clicked = false;
        }
        else if(termination_clicked) 
        {
            cv::destroyAllWindows();
            std::cout << "Exit\n";
            break;
        }
        /* button for "Add ID image" */
        cv::rectangle(output_image, cv::Point(add_faces_x0, add_faces_y0), cv::Point(add_faces_x1, add_faces_y1), ASH, -1);
        cv::putText(output_image, "Add ID image", cv::Point(add_faces_x0 + 30, add_faces_y0 + 50), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
        /* button for "Validate" */
        cv::rectangle(output_image, cv::Point(recognize_x0, recognize_y0), cv::Point(recognize_x1, recognize_y1), ASH, -1);
        cv::putText(output_image, "Validate", cv::Point(recognize_x0 + 75, recognize_y0 + 50), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);

        cv::putText(output_image,"Double Click to exit the Application!!", cv::Point(IMAGE_OUTPUT_WIDTH - 440, IMAGE_OUTPUT_HEIGHT - 50), cv::FONT_HERSHEY_SIMPLEX, 0.7, WHITE, 2, cv::LINE_AA);
        cv::setMouseCallback(app_name, mouse_callback_button_click);
        cv::imshow(app_name, output_image);
    }
    /*Close DRP-AI Driver.*/
    if (0 < drpai_fd)
    {
        errno = 0;
        uint8_t ret = close(drpai_fd);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to close DRP-AI Driver: errno=%d\n", errno);
        }
    }
    cv::destroyAllWindows();
    std::cout << "\n[INFO] Application End\n";
    return 0;
}