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
 * File Name    : parkinglot_detection.cpp
 * Version      : 1.0
 * Description  : DRP-AI TVM[*1] Application Example
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
#include "MeraDrpRuntimeWrapper.h"
#include "opencv2/core.hpp"
#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include <cmath>
#include <queue>
#include <thread>
#include "PreRuntime.h"

/* DRP-AI memory offset for model object file*/
#define DRPAI_MEM_OFFSET            (0X38E0000)

using namespace cv;
using namespace std;

/* Global variables */
vector<Rect> boxes;

Mat img;
Mat frame1 = Mat::zeros(400, 400, CV_8UC3);

std::string filename;

Point2f box_start, box_end;
cv::Rect rect;
bool add_slot_in_figure = false;
bool start_inference_parking_slot = false;
bool drawing_box = false;
bool re_draw = false;
bool camera_input = false;

const std::string model_dir = "parking_model";
const std::string app_name = "Parking Lot Assistance";

int slot_id;

MeraDrpRuntimeWrapper runtime;

uint64_t drpaimem_addr_start = 0;
bool runtime_status = false; 

/**
 * Convert HWC format to CHW
*/
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
 * Function Name     : get_patches
 * Description       : Function for drawing bounding box for parking slot.
 * Arguments         : event = int number
 *                         x = int number
 *                         y = int number
 ******************************************/

void get_patches(int event, int x, int y, int flags, void *param)
{   
    cv::Mat frame_copy = img.clone();     
    if (event == EVENT_LBUTTONDOWN)
    {   drawing_box = true;
        box_start = Point2f(x, y); 
    }
    else if (event ==  EVENT_MOUSEMOVE)
    { 
        if(drawing_box)
        box_end = Point2f(x,y);
    }
    else if (event == EVENT_LBUTTONUP)
    {
        drawing_box = false;
        box_end = Point2f(x, y);
        putText(img, "id: " + to_string(slot_id + 1), box_start, FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 0, 0), 2);
        slot_id += 1;
        rect = cv::Rect(box_start, box_end);
        Rect box(box_start, box_end);
        boxes.push_back(box);
    }
    if(drawing_box)
    {    
        rectangle(frame_copy, box_start, box_end, Scalar(0, 0, 255), 2);
    }
    else if (!rect.empty())
    {    
        rectangle(frame_copy, rect, cv::Scalar(0, 0, 255),2);
    }
    for (int i = 0; i < boxes.size(); i++)
    {
         rectangle(img, boxes[i], Scalar(0, 0, 255), 2);
    }
    box_end = Point2f(x, y);   
    imshow("image", frame_copy);
}
/*****************************************
 * Function Name     : draw_rectangle
 * Description       : Function for initializing get patches.
 * Return value      : int = int number
 ******************************************/
int draw_rectangle(void)
{
    slot_id = boxes.size();
    for (int i = 0; i < boxes.size(); i++)
    {
        rectangle(img, boxes[i], Scalar(0, 0, 255), 2);
        putText(img, "id: " + to_string(i + 1), Point(boxes[i].x + 10, boxes[i].y - 10), FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 0, 0), 2);
    }
    unsigned int key = 0;
    cv::namedWindow("image", cv::WINDOW_NORMAL);
    cv::imshow("image", img);
    cv::setMouseCallback("image", get_patches, &img);
    key = cv::waitKey(0);
    std::cout << "key:" << key << "\n";
    if (key == 114) // Wait for 'r' key press to redraw!!
    {
        std::cout << "re-draw!!\n";
        cv::destroyAllWindows();
        return 1;
    }
    else
    {
        cv::destroyAllWindows();
        return 0;
    }
}
/*****************************************
 * Function Name     : addButtonCallback
 * Description       : add slots to the boxes vector(user can draw bounding box)
 ******************************************/
void addButtonCallback(int, void *)
{
    cv::VideoCapture vid;
redraw_rectangle:
    if (camera_input)
        vid.open(0);
    else
        vid.open(filename);
    for (int frame = 0; frame < 10; frame++)
    {
        vid.read(img);
    }
    bool is_success = vid.read(img);
    if (is_success == true)
        std::cout << "Draw rectangle !!!\n";
    vid.release();
    re_draw = draw_rectangle();
    if (re_draw == true)
        goto redraw_rectangle;
}
/*****************************************
 * Function Name     : removeButtonCallback
 * Description       : remove slot from the boxes vector based on the user input(comma separated input)
 ******************************************/
void removeButtonCallback(int, void *)
{
    Mat frame = Mat::zeros(600, 600, CV_8UC3);
    putText(frame, "Enter comma separated integers to remove:", Point(50, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, LINE_AA);
    imshow("Frame", frame);
    string inputText;
    int key = -1;
    while (key != 13)
    {
        key = waitKey(0);
        if (key != 13)
            inputText += (char)key;
        putText(frame, inputText, Point(100, 100), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);
        imshow("Frame", frame);
    }
    vector<int> indicesToRemove;
    stringstream ss(inputText);
    int index;
    while (ss >> index)
    {
        indicesToRemove.push_back(index);
        if (ss.peek() == ',')
            ss.ignore();
    }
    for (int i = indicesToRemove.size() - 1; i >= 0; i--)
    {
        boxes.erase(boxes.begin() + indicesToRemove[i-1]);
    }
}
/*****************************************
 * Function Name     : mouse_callback_button_click
 * Description       : Slot Frame mouse callback(add slot and remove slot functionality).
 ******************************************/
void mouse_callback_button_click(int event, int x, int y, int flags, void *userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        if (415 < x && x < 565 && 523 < y && y < 573)
            add_slot_in_figure = true;
        else if (687 < x && x < 837 && 523 < y && y < 573)
            start_inference_parking_slot = true;
    }
}

void read_frames(const string &videoFile, queue<Mat> &frames, bool &stop)
{
    VideoCapture cap;
    if (filename == "0")
        cap.open(0);
    else
        cap.open(videoFile);
    if (!cap.isOpened())
    {
        cerr << "Failed " << videoFile << endl;
        return;
    }
    Mat frame;
    while (!stop)
    {
        cap.read(frame);
        if (frame.empty())
        {
            break;
        }
        frames.push(frame);
    }
}

void process_frames(queue<Mat> &frames, bool &stop)
{
    
    Rect box;
    Mat patch1, patch_con, patch_norm, inp_img;
    while (!stop)
    {
        if (!frames.empty())
        {
            auto t1 = std::chrono::high_resolution_clock::now();
            Mat frame = frames.front();
            frames.pop();
            img = frame;
            for (int i = 0; i < boxes.size(); i++)
            {
                box = boxes[i];
                patch1 = img(box);
                resize(patch1, patch1, Size(28, 28));
                cvtColor(patch1, patch1, COLOR_BGR2RGB);
                inp_img = hwc2chw(patch1);
                if (!inp_img.isContinuous())
                    patch_con = inp_img.clone();
                else
                    patch_con = inp_img;
                cv::normalize(patch_con, patch_norm, 0, 1, cv::NORM_MINMAX, CV_32FC1);
                float *temp_input = new float[patch_norm.total() * 3];
                memcpy(temp_input, patch_norm.ptr<float>(), 3 * patch_norm.total() * sizeof(float));
                runtime.SetInput(0, temp_input);
                runtime.Run();
                auto output_num = runtime.GetNumOutput();
                if (output_num != 1)
                {
                    std::cerr << "[ERROR] Output size : not 1." << std::endl;
                    return;
                }
                auto output_buffer = runtime.GetOutput(0);
                int64_t out_size = std::get<2>(output_buffer);
                float floatarr[out_size];
                float *data_ptr = reinterpret_cast<float *>(std::get<1>(output_buffer));
                for (int n = 0; n < out_size; n++)
                {
                    floatarr[n] = data_ptr[n];
                }
                if (floatarr[0] > floatarr[1])
                {
                    putText(img, "id: " + to_string(i + 1), Point(boxes[i].x + 10, boxes[i].y - 10), FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 0, 0), 2);
                    cv::rectangle(img, boxes[i], Scalar(0, 0, 255), 2);
                    cv::putText(img, "occupied", Point(boxes[i].x - 10, boxes[i].y + boxes[i].height + 25), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 255), 2, false);
                }
                else
                {
                    putText(img, "id: " + to_string(i + 1), Point(boxes[i].x + 10, boxes[i].y - 10), FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 0, 0), 2);
                    cv::rectangle(img, boxes[i], Scalar(0, 255, 0), 2);
                    cv::putText(img, "empty", Point(boxes[i].x + 10, boxes[i].y + boxes[i].height + 25), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 255, 0), 2, false);
                }
            }
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            putText(img, "DRP-AI Processing Time(ms): " + to_string(duration), Point(img.cols - 380, img.rows - 07), FONT_HERSHEY_DUPLEX, .65, Scalar(255, 0, 0), 2);

            if (waitKey(10)==27)// Wait for 'Esc' key press to stop inference window!!
            {   
            stop = true;
            destroyAllWindows();
            break;
            }
        imshow("Inference", img);
        }
        
    }
}

/*****************************************
* Function Name : get_drpai_start_addr
* Description   : Function to get the start address of DRPAImem.
* Arguments     : -
* Return value  : uint32_t = DRPAImem start address in 32-bit.
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
        LOG(FATAL) << "[ERROR] Failed to open DRP-AI Driver : errno=" << errno;
        return NULL;
    }

    /* Get DRP-AI Memory Area Address via DRP-AI Driver */
    ret = ioctl(fd , DRPAI_GET_DRPAI_AREA, &drpai_data);
    if (-1 == ret)
    {
        LOG(FATAL) << "[ERROR] Failed to get DRP-AI Memory Area : errno=" << errno ;
        return (uint32_t)NULL;
    }

    return drpai_data.address;
}


int main(int argc, char **argv)
{
    
    /*Load model_dir structure and its weight to runtime object */
    drpaimem_addr_start = get_drpai_start_addr();

    if (drpaimem_addr_start == (uint64_t)NULL)
    {
        /* Error notifications are output from function get_drpai_start_addr(). */
	    fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address. \n");
        return -1;
    }

    // runtime_status = false
    runtime_status = runtime.LoadModel(model_dir, drpaimem_addr_start + DRPAI_MEM_OFFSET);
    
    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load model. \n");
        return -1;
    }

    std::cout << "loaded model:" << model_dir << "\n";
    
    if (argc == 1)
    {
        std::cout << "Loading from camera input...\n";
        camera_input = true;
        filename = "0";
    }
    else
    {
        filename = argv[1];
        camera_input = false;
        std::cout << "Loading from :" << filename << "\n";
    }
    namedWindow(app_name, WINDOW_NORMAL);
    resizeWindow(app_name, 1200, 800);
    while (waitKey(1) != 'q')
    {
        Mat frame;
        frame = cv::imread("parking_bg.jpg");
        cv::resize(frame, frame, cv::Size(1200,800));
        if (add_slot_in_figure)
        {
            rectangle(frame, Point(415, 523), Point(565, 573), Scalar(150, 150, 150), -1);
            putText(frame, "Edit Slots", Point(415 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            add_slot_in_figure = false;
            destroyAllWindows();
            namedWindow("Slot", WINDOW_NORMAL);
            resizeWindow("Slot", 400, 400);
            Rect addButtonRect(50, 50, 150, 100);
            Rect removeButtonRect(200, 50, 150, 100);
            rectangle(frame1, addButtonRect, Scalar(0, 255, 0), -1);
            putText(frame1, "Add Slot", Point(75, 105), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
            rectangle(frame1, removeButtonRect, Scalar(0, 0, 255), -1);
            putText(frame1, "Remove Slot", Point(210, 105), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
            imshow("Slot", frame1);

            setMouseCallback(
                "Slot", [](int event, int x, int y, int flags, void *userdata)
                {
                if (event == EVENT_LBUTTONDOWN) 
                {
                    Rect addButtonRect = Rect(50, 50, 150, 100);
                    Rect removeButtonRect = Rect(200, 50, 150, 100);
                    if (addButtonRect.contains(Point(x, y))) 
                        addButtonCallback(0, 0);
                    else if (removeButtonRect.contains(Point(x, y))) 
                    removeButtonCallback(0, 0);
                } },
                NULL);
            waitKey(0);
        }
        else
        {
            rectangle(frame, Point(415, 523), Point(565, 573), Scalar(255, 0, 0), -1);
            putText(frame, "Edit Slots", Point(415 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 1);
        }
        if (start_inference_parking_slot)
        {
            rectangle(frame, Point(687, 523), Point(900, 573), Scalar(0, 0, 0), -1);
            putText(frame, "Start Inference", Point(687 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 1);
            start_inference_parking_slot = false;
            destroyAllWindows();
            std::cout << "Running tvm runtime" << std::endl;

            queue<Mat> frames;
            bool stop = false;
            thread readThread(read_frames, filename, ref(frames), ref(stop));
            cout << "Waiting for read frames to add frames to buffer!!!!!" << endl;
            this_thread::sleep_for(std::chrono::seconds(0));
            thread processThread(process_frames, ref(frames), ref(stop));
            cout << "Processing thread started......" << endl;
            waitKey(0);
            stop = false;
            readThread.join();
            processThread.join();
        }
        else
        {
            rectangle(frame, Point(687, 523), Point(900, 573), Scalar(255, 0, 0), -1);
            putText(frame, "Start Inference", Point(687 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 1);
        }
        setMouseCallback(app_name, mouse_callback_button_click);
        imshow(app_name, frame);
    }
    return 0;
}
