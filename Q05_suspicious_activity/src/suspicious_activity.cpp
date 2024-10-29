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
***********************************************************************************************************************
/*****************************************
 * includes
 *****************************************/
#include <builtin_fp16.h>
#include <fstream>
#include <string>
#include <sys/time.h>
#include <climits>
#include <cstdlib>
#include <thread>
#include <cstring>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "MeraDrpRuntimeWrapper.h"
#include "opencv2/core.hpp"
#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/plot.hpp"
#include <vector>
#include <glob.h>
#include <cmath>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <string.h>
#include <queue>
#include <linux/drpai.h>
#define DRPAI_MEM_OFFSET        (0x38E0000)

#define WHITE                   cv::Scalar(255, 255, 255)
#define GREEN                   cv::Scalar(0, 255, 0)
#define RED                     cv::Scalar(0, 0, 255)
#define BLUE                    cv::Scalar(255, 0, 0)

#define MODEL_IN_H (128)
#define MODEL_IN_W (128)
#define MODEL_IN_C (3)

/* Default Batch size */
const int BATCH_SIZE        = 10;
/* Default buffer size */
unsigned int BUFFER_SIZE    = 2;
/* Default frame interval */
unsigned int FRAME_INTERVAL = 10; 

bool running_process_frame     = true;
bool plot_g = false;
bool doubleClicked = false;

int wait_key        = 0;
int duration        = 0;
unsigned int fps    = 0;

float threshold     = 0.5;
float val           = 1.0;
float font_size     = 0.7;
float font_weight   = 2;
double count        = 0;

uint32_t out_size_arr;
/*Argument Index*/
uint8_t arg_index   = 0;

std::vector<double> x;
std::vector<double> y;
std::queue<cv::Mat> frame_queue;
std::vector<float> floatarr(1);

const std::string non_violence      = "Non Violence activity";
const std::string violence          = "Violence activity detected !";
const std::string none              = "None";
std::string input_source            = "";
std::string video_source            = "";
std::string source                  = "";
std::string result                  = none;
std::string frame_interval          = "";
std::string buffer_size             = "";

cv::VideoCapture cap;
cv::Mat frame;
cv::Mat display;
cv::Scalar Color;

MeraDrpRuntimeWrapper embedding_model;
MeraDrpRuntimeWrapper prediction_model;

void camera_thread(void);
void process_frames(void);
void plot_graph(float value);
void start_runtime(bool flag,float *input);
void capture_frame(std::string cap_pipeline);

float float16_to_float32(uint16_t a);
cv::Mat hwc2chw(const cv::Mat &image);
cv::Mat run_inference(cv::Mat frame);

/* Map to store input source list */
std::map<std::string, int> input_source_map =
{
    {"VIDEO", 1},
    #ifdef V2L
        {"MIPI", 2},
    #endif
    {"USB", 3}
};

#ifdef V2H
    #define DRPAI_FREQ                 (2)
    /*DRP-AI Frequency setting*/
    static int32_t drpai_freq;
#endif

/*****************************************
* Function Name : get_drpai_start_addr
* Description   : Function to get the start address of DRP-AI Memory Area.
* Arguments     : -
* Return value  : uint32_t = DRP-AI Memory Area start address in 32-bit.
******************************************/
uint32_t get_drpai_start_addr()
{
    int fd = 0;
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
    cv::hconcat(matArray, MODEL_IN_C, flat_image);
    return flat_image;
}


/*****************************************
 * Function Name     : mouse_callback_button_click
 * Description       : Slot Frame mouse callback(add slot and remove slot functionality).
 ******************************************/
void mouse_callback_button_click(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDBLCLK)
    {
        doubleClicked = true;
        std::cout << "\n[INFO] Double Tap !!\n";
    }
}

/*****************************************
 * Function Name : camera_thread
 * Description   : function to show the ouput camera result
 ******************************************/
void camera_thread(void)
{
    int frame_count = 0;
    cv::Point text_position(15, 30);
    cv::Point text_position_fps(535, 30);
    cv::Point text_position_inftm(359,55);
    /*start capturing frames*/
    
    while (true)
    {
        frame_count++;
        cv::Mat frame;
        cap.read(frame);
        /* Breaking the loop if no video frame is detected */
        if (frame.empty())
        {
            std::cout << "[INFO] Video ended or corrupted frame !\n";
            running_process_frame = false;
            break;
        }
        /*check frame interval based on the FRAME_INTERVAL parameter*/
        if (frame_count % FRAME_INTERVAL != 0)
        {
            cv::resize(frame, frame, cv::Size(640, 480), cv::INTER_LINEAR);
            if (result != none)
            {
                Color = (result == violence) ? RED : GREEN;
                putText(frame, result, text_position, cv::FONT_HERSHEY_COMPLEX, font_size, Color, font_weight);
                putText(frame, "FPS : "+ std::to_string(fps), text_position_fps, cv::FONT_HERSHEY_COMPLEX, font_size, GREEN, font_weight);
                putText(frame, "AI-Inference Time(ms): "+ std::to_string(duration), text_position_inftm, cv::FONT_HERSHEY_COMPLEX, 0.55, GREEN,font_weight);
            }
            /* display output frame*/
            putText(frame,"Double Click to exit the Application!!", cv::Point((int)(frame.cols/2 - frame.cols/10) + 50, (int)(frame.rows) -20), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLUE, 1, cv::LINE_AA);
            cv::imshow("Camera", frame);
            cv::setMouseCallback("Camera", mouse_callback_button_click);
            wait_key = cv::waitKey(1);
            if (doubleClicked)
            {
                running_process_frame = false;
                break;
            }
            /* display graph*/
            if((x.size()> 10 || y.size()> 10) && plot_g == true)
            {
                cv::imshow("Graph Plot",display );
                cv::setMouseCallback("Graph Plot", mouse_callback_button_click);
                cv::waitKey(5);
                plot_g = false;
            }
            continue;
        }
        else
        {
            /*push frames to the queue for processing if queue size is not 100*/
            if (frame_queue.size()<100)
                frame_queue.push(frame);
            frame_count = 0;
        }
    }
    cap.release();
    cv::destroyAllWindows();
}

/******************************************
 * Function Name : plot_graph
 * Description   : function to plot graph with respect to the threshold value.
 * Arguments     : float value , output threshold value.
 ******************************************/
void plot_graph(float value)
{
    count++;
    /* push back the count and threshold value to vector array */
    if(x.size()< 20 || y.size()< 20)
    {
        x.push_back(count);
        y.push_back(value);
    }
    else
    {
        x.erase(x.begin());
        y.erase(y.begin());
    }

    cv::Mat1d xData(x);
    cv::Mat1d yData(y);
    /* Set text position on graph*/
    cv::Point text_position(40,60);
    cv::Ptr<cv::plot::Plot2d> plot = cv::plot::Plot2d::create(xData,yData);
    
    plot->setPlotSize(640,480);
    plot->setMaxY(2);
    plot->setMinY(-2);
    plot->setMaxX(count+1);

    /* Plot graph*/
    plot->render(display);
    cv::flip(display,display,0);
    cv::Rect roi(0,0,640,431);
    display = display(roi);
    Color = (value >= 0.5) ? GREEN : RED;
    putText(display,"Threshold : "+ std::to_string(value), text_position, cv::FONT_HERSHEY_COMPLEX, font_size, Color, font_weight);
    putText(display,"1",cv::Point(10,119), cv::FONT_HERSHEY_COMPLEX,0.65,WHITE,1);
    putText(display,"0.5",cv::Point(10,183), cv::FONT_HERSHEY_COMPLEX,0.65,WHITE,1);
    putText(display,"Double Click to exit the Application!!", cv::Point((int)(display.cols/2 - display.cols/10) + 50, (int)(display.rows) -20), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLUE, 1, cv::LINE_AA);
    plot_g = true;
    return;
}

/*****************************************
 * Function Name     : start_runtime
 * Description       : Function to perform the pre processing and post processing.
 * Arguments         : *input = frame input address
 * Return value      : *float floatarr = pre-processed and post-processed output
 ******************************************/
void start_runtime(bool flag,float *input)
{
    MeraDrpRuntimeWrapper model_runtime = (flag == true)?embedding_model:prediction_model;
    /*Set Pre-processing output to be inference input. */
    model_runtime.SetInput(0, input);
    #ifdef V2H
        model_runtime.Run(drpai_freq);
    #elif V2L
            model_runtime.Run();
    #endif
    /* Get the number of output.  */
    auto output_num = model_runtime.GetNumOutput();
    /* get output buffer */
    auto output_buffer = model_runtime.GetOutput(0);
    out_size_arr = std::get<2>(output_buffer);
    floatarr.resize(out_size_arr);
    /* Post-processing for FP16 */
    if (InOutDataType::FLOAT16 == std::get<0>(output_buffer))
    {
        /* Extract data in FP16 <uint16_t>. */
        uint16_t *data_ptr = reinterpret_cast<uint16_t *>(std::get<1>(output_buffer));
        for (int n = 0; n < out_size_arr; n++)
        {
            if(flag == true)
            {
                /* Cast FP16 output data to FP32. */
                floatarr[n] = float16_to_float32(data_ptr[n]);
            }
            else
            {
                /* Cast FP16 output data to FP32. */
                auto prediction = float16_to_float32(data_ptr[n]);
                if (prediction >= threshold)
                    result = non_violence;
                else
                    result = violence;
                val = (float)prediction;
            }
        }
    }
    else
    {
        std::cout << "[ERROR] Output data type : not floating point." << std::endl;
        exit(0);
    }
}

/*****************************************
 * Function Name : run_inference
 * Description   : frame preprocessing and postprocessing.
 * Arguments     : Mat frame
 * Return value  : Mat mat
 ******************************************/
cv::Mat run_inference(cv::Mat frame)
{
    cv::Size size(MODEL_IN_H, MODEL_IN_W);
    /*resize the image to the model input size*/
    cv::resize(frame, frame, size);
    /*convert to FP32*/
    frame.convertTo(frame, CV_32FC3);
    divide(frame, 255.0, frame);
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    frame = hwc2chw(frame);
    /*deep copy, if not continuous*/
    if (!frame.isContinuous())
        frame = frame.clone();
    /*start inference using drp runtime*/
    start_runtime(true,frame.ptr<float>());
    cv::Mat mat(out_size_arr, 1, CV_32FC1, floatarr.data());
    return mat;   
}

/*****************************************
 * Function Name : process_frames
 * Description   : frame preprocessing and postprocessing.
 ******************************************/
void process_frames(void)
{
    std::vector<cv::Mat> frames;
    std::vector<cv::Mat> features;
    
    /* Model Binary */
    std::string cnn_model = "cnn_module";
    /* Model Binary */
    std::string mlp_model = "mlp_module";

    uint64_t drpaimem_addr_start = 0;
    bool runtime_status = false;


    drpaimem_addr_start = get_drpai_start_addr();
    if ((uint64_t)NULL == drpaimem_addr_start) 
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address.\n");
        /*Error processing, i.e., return, goto, etc.*/
        return;
    }
    /* Load model_dir structure and its weight to model_runtime object */
    runtime_status = embedding_model.LoadModel(cnn_model, drpaimem_addr_start+DRPAI_MEM_OFFSET);
    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load CNN model.\n");
        /*Error processing, i.e., return, goto, etc.*/
        return;
    }
    /* Load model_dir structure and its weight to model_runtime object */
    runtime_status = prediction_model.LoadModel(mlp_model, drpaimem_addr_start);
    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load MLP model.\n");
        /*Error processing, i.e., return, goto, etc.*/
        return;
    }

    std::cout << "\n[INFO] loaded CNN model:" << cnn_model << "\n";
    std::cout << "\n[INFO] loaded MLP model:" << mlp_model << "\n\n";

    while (running_process_frame)
    {
        /* checking input frame array is empty or not */
        if (frame_queue.empty())
            continue;
        cv::Mat frame = frame_queue.front();
        frame_queue.pop();
        auto t1 = std::chrono::high_resolution_clock::now();
        /* checking the input frame is empty or not*/
        if(frame.empty())
        {
            std::cout << "[ERROR] Unable to read frame" << std::endl;
            break;
        }
        /* run inference*/
        cv::Mat feature_vector = run_inference(frame);
        features.push_back(feature_vector);
        if (features.size() >= BATCH_SIZE)
        {
            cv::Mat combined_features;
            /* vertical concatenation */
            vconcat(features, combined_features);
            start_runtime(false,combined_features.ptr<float>());

            auto t2 = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            float fps_val = (float)duration;
            fps = (int)ceil(1000/fps_val);
            std::cout << "\n[INFO] FPS(s): " << fps << " s\n";
            std::cout << "\n[INFO] AI-Inference Time(ms): " << duration << " ms\n\n";
            features.erase(features.begin(), features.begin() + BUFFER_SIZE);
        }
        plot_graph(val);
    }
    return;
}

/******************************************
 * Function Name : capture_frame
 * Description   : function to open camera or video source with respect to the source pipeline.
 * Arguments     : string cap_pipeline input source pipeline
 ******************************************/
void capture_frame(std::string cap_pipeline)
{
    /* Capture stream of frames from camera using Gstreamer pipeline */
    cap.open(cap_pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened())
    {
        /* This section prompt an error message if no video stream is found */
        std::cout << "[ERROR] Error opening video stream or camera !\n" << std::endl;
        return;
    }
    else
    {
        /* Start thread camera_start*/ 
        std::thread camera_start(camera_thread);
        process_frames();
        /* Wait for camera_start finish */ 
        camera_start.join();
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
 * Description   : function to check USB/MIPI device is connectod.
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
 * Function Name : input_source_select
 * Description   : function to select input source
 * Return value  : 0  = Input source selected
 *                 -1 = Error selecting inputh source
 ******************************************/
int input_source_select(void)
{
    switch (input_source_map[input_source])
    {
        /* Input Source : Video file */
        case 1:
        {
            arg_index = 1;
            std::cout << "[INFO] VIDEO mode\n";
            std::cout << "Loading from :" << video_source << "\n";
            source = "filesrc location=" + video_source + " ! decodebin ! videoconvert ! appsink";
            break;
        }

        /* Input Source : MIPI Camera */
        case 2:
        {
            arg_index = 0;
            std::cout << "[INFO] MIPI CAMERA mode\n";
            /* check the status of device */
            std::string media_port = query_device_status("CRU");
            if (media_port == "")
            {
                fprintf(stderr, "[ERROR] MIPI Camera not connected. \n");
                return -1;
            }
            mipi_cam_init();
            /* gstremer pipeline to read input image source */
            source = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
            break;
        }
        /* Input Source : USB Camera */
        case 3:
        {
            arg_index = 0;
            std::cout << "[INFO] USB CAMERA mode\n";
            /* check the status of device */
            std::string media_port = query_device_status("usb");
            if (media_port == "")
            {
                fprintf(stderr, "[ERROR] USB Camera not connected. \n");
                return -1;
            }
            /* gstremer pipeline to read input image source */
            source = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
            break;
        }
        default:
        {
            std::cout << "[ERROR] Please specify Input Source" << std::endl;
            std::cout << "[INFO] Usage : ./suspicious_activity MIPI|USB|VIDEO [Input_file for VIDEO]" << std::endl;
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    #ifdef V2H
        /*Disable OpenCV Accelerator due to the use of multithreading */
        unsigned long OCA_list[16];
        for (int i = 0; i < 16; i++)
            OCA_list[i] = 0;
        OCA_Activate(&OCA_list[0]);
    #endif


    if (argc < 2 || argc > 5) 
    {
        std::cout << "[ERROR] Please specify Input Source" << std::endl;
        std::cout << "[INFO] Usage : ./suspicious_activity MIPI|USB|VIDEO [Input_file for VIDEO]" << std::endl;
        std::cout << "\n[INFO] End Application\n";
        return -1;
    }

    input_source = argv[1];
    if (input_source != "VIDEO" && (argc == 3 || argc == 5)) 
    {
        std::cout << "[ERROR] Please specify Input Source" << std::endl;
        std::cout << "[INFO] Usage : ./suspicious_activity MIPI|USB|VIDEO [Input_file for VIDEO]" << std::endl;
        std::cout << "\n[INFO] End Application\n";
        return -1;
    }
    
    if ((input_source == "VIDEO")) 
    {
        if(argc == 2 || argc == 4)
        {
            std::cout << "[ERROR] Please specify Input Source" << std::endl;
            std::cout << "[INFO] Usage : ./suspicious_activity MIPI|USB|VIDEO [Input_file for VIDEO]" << std::endl;
            std::cout << "\n[INFO] End Application\n";
            return -1;
        }
        video_source = argv[2];
    }
    /*Select input Source MIPI/USB/VIDEO*/
    if(input_source_select() == -1)
    {
        std::cout << "\n[INFO] Application END\n";
        return -1;
    }

    /* Minimum-Maximum vlue range of Frame interval and buffer size */
    const uint8_t frame_interval_min    = 1;
    const uint8_t frame_interval_max    = 16;
    const uint8_t buffer_size_min       = 0;
    const uint8_t buffer_size_max       = 10;    

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
        std::cout<<"\n[INFO] DRPAI FREQUENCY : "<<drpai_freq<<"\n";
    #endif

    /* Fetching Frame interval & Buffer size from arguments */
    (!(argv[2+arg_index]) || (atoi(argv[2+arg_index]) <= frame_interval_min || atoi(argv[2+arg_index]) >= frame_interval_max)) ? std::cout << "[INFO] Default Frame interval: " : std::cout << "[INFO] Frame interval: ";
    FRAME_INTERVAL = (!(argv[2+arg_index]) || ( atoi(argv[2+arg_index]) <= frame_interval_min || atoi(argv[2+arg_index]) >= frame_interval_max)) ? FRAME_INTERVAL : atoi(argv[2+arg_index]);
    std::cout<<FRAME_INTERVAL<<"\n";

    ((!(argv[3+arg_index]) || (atoi(argv[3+arg_index]) <= buffer_size_min || atoi(argv[3+arg_index]) >= buffer_size_max)) || (!(argv[2+arg_index]))) ? std::cout << "[INFO] Default Buffer size: " : std::cout << "[INFO] Buffer size: ";
    BUFFER_SIZE = ((!(argv[3+arg_index]) || (atoi(argv[3+arg_index]) <= buffer_size_min || atoi(argv[3+arg_index]) >= buffer_size_max)) || (!(argv[2+arg_index])) ) ? BUFFER_SIZE : atoi(argv[3+arg_index]);
    std::cout<<BUFFER_SIZE<<"\n";
    /* Capture frame */
    capture_frame(source);
    std::cout << "\n[INFO] Application End\n";
    return 0;
}
