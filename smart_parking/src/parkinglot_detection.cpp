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
 * Description  : RZ/V2L SDK AI Application: Parking Lot Detection
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
using namespace cv;
using namespace std;
using namespace cv;
Mat img;
Mat frame1 = Mat::zeros(400, 400, CV_8UC3);
vector<Rect> boxes;
Point2f box_start;
bool add_slot_in_figure = false;
bool start_inference_parking_slot = false;
bool drawing_box = false;
bool re_draw;
int slot_id;
std::string filename;
bool camera_input;
/******************************************
 * Function Name : timedifference_msec
 * Arguments     : t0 = processing start time
 *                 t1 = processing end time
 * Return value  : processing time in mili-seconds
 ******************************************/
static double timedifference_msec(struct timespec t0, struct timespec t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1000.0 / 1000.0;
}
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
    if (event == EVENT_LBUTTONDOWN)
    {
        drawing_box = true;
        box_start = Point2f(x, y);
    }
    else if (event == EVENT_LBUTTONUP)
    {
        drawing_box = false;
        Point2f box_end = Point2f(x, y);
        Rect box(box_start, box_end);
        boxes.push_back(box);
        rectangle(img, box_start, Point2f(x, y), Scalar(0, 0, 255), 2);
        putText(img, "id: " + to_string(slot_id + 1), box_start, FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 0, 0), 2);
        slot_id += 1;
        imshow("image", img);
    }
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
    bool is_sucess = vid.read(img);
    if (is_sucess == true)
        std::cout << "Draw rectangle !!!\n";
    vid.release();
    re_draw = draw_rectangle();
    if (re_draw == 1)
        goto redraw_rectangle;
}
/*****************************************
 * Function Name     : removeButtonCallback
 * Description       : remove slot from the boxes vector based on the user input(comma seperated input)
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
        boxes.erase(boxes.begin() + indicesToRemove[i]);
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
int main(int argc, char **argv)
{
    cv::VideoCapture vid1;
    if (argc == 1)
    {
        std::cout << "Loading from camera input...\n";
        camera_input = true;
    }
    else
    {
        filename = argv[1];
        camera_input = false;
        std::cout << "Loading from :" << filename << "\n";
    }

    std::string app_name = "Parking Lot Assistance";

    struct timespec start_time, end_time;
    int width = 900, height = 600;
    unsigned int re_draw = 0;
    MeraDrpRuntimeWrapper runtime;
    std::string model_dir = "parkingmodel_onnx";
    runtime.LoadModel(model_dir);
    cout << "loaded model" << endl;
    Rect box;
    Mat patch1, patch_con, patch_norm, inp_img;
    namedWindow(app_name, WINDOW_NORMAL);
    resizeWindow(app_name, 1200, 800);
    while (waitKey(1) != 'q')
    {
        Mat frame;
        frame = cv::imread("parking_bg.jpg");
        if (add_slot_in_figure)
        {
            vid1.release();
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
            rectangle(frame, Point(415, 523), Point(565, 573), Scalar(150, 150, 150), -1);
            putText(frame, "Edit Slots", Point(415 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
        }
        if (start_inference_parking_slot)
        {
            if (camera_input)
                vid1.open(0);
            else
                vid1.open(filename);
            rectangle(frame, Point(687, 523), Point(900, 573), Scalar(150, 150, 150), -1);
            putText(frame, "Start Inference", Point(687 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
            start_inference_parking_slot = false;
            destroyAllWindows();
            std::cout << "Running tvm runtime" << std::endl;
            while (1)
            {
                auto t1 = std::chrono::high_resolution_clock::now();
                vid1 >> img;
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
                        return 0;
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
                putText(img, "FPS: " + to_string(1000 / duration), Point(img.cols - 120, img.rows - 40), FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 0, 0), 2);
                imshow("img", img);
                if (waitKey(1) == 27)
                    break;
            }
        }
        else
        {
            rectangle(frame, Point(687, 523), Point(900, 573), Scalar(150, 150, 150), -1);
            putText(frame, "Start Inference", Point(687 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
        }
        setMouseCallback(app_name, mouse_callback_button_click);
        imshow(app_name, frame);
    }
    return 0;
}
