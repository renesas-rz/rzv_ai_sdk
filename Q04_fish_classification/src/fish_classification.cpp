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
 * File Name    : fish_classification.cpp
 * Version      : 1.0
 * Description  : RZ/V2L SDK AI Application: Fish Classification
 ***********************************************************************************************************************/
/*****************************************
 * includes
 *****************************************/
#include <builtin_fp16.h>
#include <fstream>
#include <string>
#include <sys/time.h>
#include <climits>
#include <cstdlib>
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>


#define GREEN cv::Scalar(0, 255, 0)
#define RED cv::Scalar(0, 0, 255)
/*Model input info*/
#define MODEL_IN_H (224)
#define MODEL_IN_W (224)
#define MODEL_IN_C (3)

/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper model_runtime;


int duration,fps;
unsigned int out;
uint32_t out_size_arr;
std::vector<float> floatarr(1);
std::string score_per = "";
cv::Mat frame;
cv::VideoCapture cap;

/* Map to store label list */
std::map<int, std::string> class_names;

/* Map to store input source list */
std::map<std::string, int> input_source_map = {
    {"WS", 1},
    {"VIDEO", 2},
    {"IMAGE", 3},
    {"CAMERA", 4}};


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
    out_size_arr = std::get<2>(output_buffer);
    floatarr.resize(out_size_arr);
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
    return floatarr.data();
}
/*****************************************
* Function Name : softmax
* Description   : Function for Post Processing
* Arguments     : val[] = array to be computed Softmax
*                 size = size of array
* Return value  : -
******************************************/
void softmax(float* val, int32_t size)
{
    float max_num = -INT_MAX;
    float sum = 0;
    int32_t i;
    for ( i = 0 ; i<size ; i++ )
    {
        max_num = std::max(max_num, val[i]);
    }

    for ( i = 0 ; i<size ; i++ )
    {
        val[i]= (float) exp(val[i] - max_num);
        sum+= val[i];
    }

    for ( i = 0 ; i<size ; i++ )
    {
        val[i]= val[i]/sum;
    }
    return;
}

/*****************************************
 * Function Name : run_inference
 * Description   : takes Mat frame as the input and passes through the model runtime and returns the output
 * Arguments     : Mat frame
 * Return value  : int 0 - 30
 *                 int -1 if not found 
 *     
 ******************************************/
int run_inference(cv::Mat frame)
{
    float *output;
    auto t1 = std::chrono::high_resolution_clock::now();
    std::map<float,int> result;
    int result_cnt = 0;
    cv::Size size(MODEL_IN_H, MODEL_IN_W);
    /*resize the image to the model input size*/
    cv::resize(frame, frame, size);
    /*convert to FP32*/
    frame.convertTo(frame, CV_32FC3);
    /*deep copy, if not continuous*/
    if (!frame.isContinuous())
        frame = frame.clone();
    result.clear();
    /*start inference using drp runtime*/
    output = start_runtime(frame.ptr<float>());

    softmax(output,out_size_arr);
    auto t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    fps = 1000/duration;
    std::cout << "\n[INFO] AI-Inference Time(ms): " << duration << " ms\n" <<"[INFO] FPS: "<<fps<<"\n";
    int max_ind = -1;
    float max_value = -1;
    float threshold = 0.6;
    for (int n = 0; n < out_size_arr; n++)
    {
        result[floatarr[n]] = n;
        if (output[n] > max_value)
        {
            max_value = output[n];
            max_ind = n;
        }
    }
    /* Print Top-5 results. */
    std::cout << "\n[INFO] Result -----------------------"<< std::endl;
    for (auto it = result.rbegin(); it != result.rend(); it++)
    {
        result_cnt++;
        if(result_cnt > 5) break;
        float re_fl = (float)(*it).first*100;
        re_fl = std::round(re_fl);
        std::cout << "Top "<< result_cnt << " ["
            << std::right << std::setw(5) << std::fixed << std::setprecision(1) << re_fl
            <<"% ] : [" << class_names[(*it).second] << "]" <<std::endl;
        if(result_cnt == 1)score_per = std::to_string(re_fl);
    }
    score_per.erase(5);
    return (max_value > threshold) ? max_ind : -1;
}


/*****************************************
 * Function Name     : load_label_file
 * Description       : Load label list text file and return the label list that contains the label.
 * Arguments         : label_file_name = filename of label list. must be in txt format
 * Return value      : std::map<int, std::string> list = list text file which contains labels
 *                     empty if error occured
 ******************************************/
std::map<int, std::string> load_label_file(std::string label_file_name)
{
    int n = 0;
    std::map<int, std::string> list;
    std::ifstream infile(label_file_name);
    if (!infile.is_open())
    {
        return list;
    }
    std::string line;
    while (getline(infile, line))
    {
        list[n++] = line;
        if (infile.fail())
        {
            std::map<int, std::string> empty;
            return empty;
        }
    }
    return list;
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
 * Function Name : show_result
 * Description   : display the inference results using opencv 
 * Arguments     : int out
 ******************************************/
void show_result(int out)
{
    if (out != -1)
    {
        std::cout << "\n[INFO] Identified Fish: " << class_names[out] << "\n\n";
        cv::putText(frame,  "Fish class: " + std::string(class_names[out]), cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 1.0, GREEN, 2);
        cv::putText(frame,  "Score: " + score_per, cv::Point(20, 70), cv::FONT_HERSHEY_SIMPLEX, 0.8, GREEN, 2);
    }
    else
        cv::putText(frame,  "Cannot Identify !", cv::Point(20, 60), cv::FONT_HERSHEY_SIMPLEX, 1.0, RED, 2);
    cv::putText(frame,  "AI-Inference Time(ms): "+std::to_string(duration), cv::Point(20, 95), cv::FONT_HERSHEY_SIMPLEX, 0.7, GREEN, 2);    
    cv::putText(frame,  "FPS: " + std::to_string(fps), cv::Point(20,120), cv::FONT_HERSHEY_SIMPLEX, 0.7, GREEN, 2);    
}


/*****************************************
 * Function Name : capture_frame
 * Description   : function to open camera or video source with respect to the source pipeline.
 * Arguments     : string cap_pipeline input source pipeline
 ******************************************/
void capture_frame(std::string cap_pipeline)
{
    int wait_key;
    std::cout << "cap pipeline" << cap_pipeline << "\n";
    /* Capture stream of frames from camera using Gstreamer pipeline */
    cap.open(cap_pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened())
    {
        /* This section prompt an error message if no video stream is found */
        std::cout << "[ERROR] Error opening video stream or camera !\n" << std::endl;
        return;
    }
    /* Taking an everlasting loop to show the video */
    while (true)
    {
        cap >> frame;
        /* Breaking the loop if no video frame is detected */
        if (frame.empty())
        {
            std::cout << "[INFO] Video ended or corrupted frame !\n";
            return;
        }
        else
        {
            out = run_inference(frame);
            show_result(out);
            imshow("output", frame);
            wait_key = cv::waitKey(30); /* Allowing 30 milliseconds frame processing time and initiating break condition */
            if (wait_key == 27) /* If 'Esc' is entered break the loop */
                break;
        }
    }
    cap.release(); /* Releasing the buffer memory */
    cv::destroyAllWindows();
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

int main(int argc, char **argv)
{
    /* Model Binary */
    std::string model_dir = "fish_classification_model";
    /* Fish class list file */
    std::string fish_class_list = "fish_class_list.txt";
    /* Load fish class list */
    class_names = load_label_file(fish_class_list);
    if (class_names.empty())
    {
        std::cerr << "[ERROR] failed to load fish class list: " << fish_class_list << std::endl;
        return 0;
    }
    /* Load model_dir structure and its weight to model_runtime object */
    model_runtime.LoadModel(model_dir);
    std::cout << "[INFO] loaded runtime model :" << model_dir << "\n\n";
    /* Get input Source WS/VIDEO/CAMERA */
    std::string input_source = argv[1];
    switch (input_source_map[input_source])
    {
        /* Input Source : Websocket*/
        case 1:
        {
            std::cout << "[INFO] WebSocket \n";
            /* Fetching the ip address of RZV2L dev module*/
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
                    /*read the data received from client*/
                    cv::Mat frame = cv::imread("test.png");
                    out = run_inference(frame);
                    /*return the results to ws client*/
                    send(client_fd, class_names[out].c_str(), class_names[out].length(), 0);
                }
            }
            close(server_fd);
            break;
        }
        /* Input Source : Video */
        case 2:
        {
            std::cout << "[INFO] Video \n";
            /* Open camera and capture frame*/
            capture_frame(argv[2]);
        }
        break;
        /* Input Source : Image */
        case 3:
        {
            std::cout << "[INFO] Image \n";
            /* read input image */
            frame = cv::imread(argv[2]);
            out = run_inference(frame);
            show_result(out);
            cv::imshow("output", frame);
            cv::waitKey(1000);
        }
        break;
        /* Input Source : Camera */
        case 4:
        {
            std::cout << "[INFO] CAMERA \n";
            std::string gstreamer_pipeline = "v4l2src device=/dev/video0 ! videoconvert ! appsink";
            /* MIPI Camera Setup */
            mipi_cam_init();
            /* Open camera and capture frame*/
            capture_frame(gstreamer_pipeline);
            break;
        }
    }
    std::cout << "[INFO] Application End\n";
}
