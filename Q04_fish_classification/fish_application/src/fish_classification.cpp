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
#define MODEL_IN_H (64)
#define MODEL_IN_W (64)
#define MODEL_IN_C (3)

MeraDrpRuntimeWrapper runtime;
std::string model_dir = "fish_classification_model";
std::map<int, std::string> class_names = {
    {0, "Black Sea Sprat"},
    {1, "Gilt-Head Bream"},
    {2, "Horse Mackerel"},
    {3, "Red Mullet"},
    {4, "Red Sea Bream"},
    {5, "Sea Bass"},
    {6, "Shrimp"},
    {7, "Striped Red Mullet"},
    {8, "Trout"},
    {9, "Cannot Identify !"}};
unsigned int out;
cv::Mat frame;
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
 * Function Name : run_inference
 * Description   : takes Mat frame as the input and passes through the model runtime and returns the output
 * Arguments     : Mat frame
 * Return value  : int 0 - 8 succeeded
 *                 otherwise  -1
 ******************************************/
int run_inference(cv::Mat frame)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    cv::Size size(MODEL_IN_H, MODEL_IN_W);
    cv::resize(frame, frame, size);
    frame.convertTo(frame, CV_32FC3);
    divide(frame, 255.0, frame);
    cv::Mat normalized, rgb_frame, frame_chw;
    cv::cvtColor(frame, rgb_frame, cv::COLOR_BGR2RGB);
    frame_chw = hwc2chw(rgb_frame);
    if (!frame_chw.isContinuous())
        frame_chw = frame_chw.clone();
    float *temp_input = new float[frame_chw.total()];
    memcpy(temp_input, frame_chw.data, frame_chw.total() * sizeof(float));
    runtime.SetInput(0, temp_input);
    runtime.Run();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout<<"\nAI-Inference Time(ms): "<<duration<<" ms\n";
    
    auto output_num = runtime.GetNumOutput();
    if (output_num != 1)
    {
        std::cout << "[ERROR] Output size : not 1." << std::endl;
        return -1;
    }
    auto output_buffer = runtime.GetOutput(0);
    int64_t out_size = std::get<2>(output_buffer);
    int max_ind = -1;
    float max_value = -1;
    float threshold = 0.9;
    float floatarr[out_size];
    if (InOutDataType::FLOAT16 == std::get<0>(output_buffer))
    {
        uint16_t *data_ptr = reinterpret_cast<uint16_t *>(std::get<1>(output_buffer));
        for (int n = 0; n < out_size; n++)
        {
            floatarr[n] = float16_to_float32(data_ptr[n]);
            if (floatarr[n] > max_value)
            {
                max_value = floatarr[n];
                max_ind = n;
            }
        }
        if (max_value > threshold)
            return max_ind;
        else
            return -1;
    }
    else
    {
        std::cout << "[ERROR] Output data type : not floating point." << std::endl;
        return -1;
    }
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
    getifaddrs(&ifAddrStruct);
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr)
        {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) // check it is IPV4 // is a valid IP4 Address
        {
            tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            std::string ifaname = ifa->ifa_name;
            if (ifaname.find("eth") == 0 || ifaname.find("enp") == 0)
            {
                ip_address = std::string(addressBuffer);
                return ip_address;
            }
        }
    }
    return ip_address;
}
/*****************************************
 * Function Name : show_result
 * Description   : function to show the inference result through the UI
 * Arguments     : int out
 ******************************************/
void show_result(int out)
{
    std::string str1 = "Fish class: ";
    std::string str4 = "Cannot Identify !";
    if (out != -1)
    {
        std::cout << "\n[INFO] Identified Fish: " << class_names[out] << "\n\n";
        std::string str2 = std::string(class_names[out]);
        std::string str3 = str1 + str2;
        cv::putText(frame, str3, cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0, GREEN, 2);
    }
    else
        cv::putText(frame, str4, cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0, RED, 2);
}
int main(int argc, char **argv)
{
    int wait_key = 0;
    std::cout << "[INFO] loaded model :" << model_dir << "\n\n";
    runtime.LoadModel(model_dir);
    std::string input_source = argv[1];
    if (input_source == "WS")
    {
        std::cout << "[INFO] WebSocket \n";
        std::string ip_address = getipaddress();
        std::cout << "[INFO] IP address:" << ip_address << "\n";
        std::string port = "2002";
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
        if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
            std::cout << " [ERROR] Failed to bind socket to server address." << std::endl;
        if (listen(server_fd, 10) == -1)
            std::cout << "[ERROR] Failed to listen for incoming connections." << std::endl;
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
            ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
            if (bytes_received == -1)
                std::cout << "[ERROR] Failed to receive image data." << std::endl;
            else
            {
                std::cout.flush();
                fflush(stdout);
                cv::Mat frame = cv::imread("test.png");
                out = run_inference(frame);
                if (out >= 0 && out <= 8)
                    send(client_fd, class_names[out].c_str(), class_names[out].length(), 0);
                else
                    send(client_fd, class_names[9].c_str(), class_names[9].length(), 0);
            }
        }
        close(server_fd);
    }
    else if (input_source == "VIDEO")
    {
        std::cout << "[INFO] Video \n";
        cv::VideoCapture cap(argv[2]);
        if (!cap.isOpened())
            std::cout << "[ERROR] Error opening video stream or file" << std::endl;
        while (1)
        {
            cap >> frame;
            if (frame.empty())
                break;
            out = run_inference(frame);
            show_result(out);
            cv::imshow("output", frame);
            wait_key = cv::waitKey(30);
            if (wait_key == 27)
                break;
        }
        cap.release();
        cv::destroyAllWindows();
    }
    else if (input_source == "IMAGE")
    {
        std::cout << "[INFO] Image \n";
        frame = cv::imread(argv[2]);
        out = run_inference(frame);
        show_result(out);
        cv::imshow("output", frame);
        cv::waitKey(2000);
    }
    else if (input_source == "CAMERA")
    {
        std::cout << "[INFO] CAMERA \n";
        cv::VideoCapture cap;
        cap.open(0, cv::CAP_GSTREAMER);
        while (true)
        {
            cap >> frame;
            if (frame.empty())
            {
                std::cout << "[ERROR] image not opened !\n";
                break;
            }
            else
            {
                out = run_inference(frame);
                show_result(out);
                imshow("output", frame);
                wait_key = cv::waitKey(50);
                if (wait_key == 27)
                    break;
            }
        }
    }
}
