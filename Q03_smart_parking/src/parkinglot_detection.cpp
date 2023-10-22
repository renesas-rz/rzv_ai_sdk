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
#include <cmath>
#include <queue>
#include <thread>
#include "MeraDrpRuntimeWrapper.h"
#include "opencv2/core.hpp"
#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "PreRuntime.h"

using namespace cv;
using namespace std;

/*DRP-AI memory area offset for model objects*/
/*Offset value depends on the size of memory area used by DRP-AI Pre-processing Runtime Object files*/
#define DRPAI_MEM_OFFSET            (0X38E0000)

/* Global variables */
/* flags for mouse callback functions*/
bool add_slot_in_figure = false;
bool start_inference_parking_slot = false;
bool exit_all = false;
bool drawing_box = false;
bool re_draw = false;
bool stop = false;
bool runtime_status = false; 

const string model_dir = "parking_model";
const string app_name = "Parking Lot Assistance";

int slot_id = 0;
int winWidth = 0;

uint64_t drpaimem_addr_start = 0;

vector<Rect> boxes;

Mat img;
Mat frame1 = Mat::zeros(400, 400, CV_8UC3);

/* gstreamer output pipeline */
std::string gstreamer_pipeline;
std::string input_mode;
std::string input_source;

Point2f box_start, box_end;
Rect rect;

/*AI Inference for DRPAI*/
/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper runtime;

/* Map to store input source list */
std::map<std::string, int> input_mode_map =
{
    {"CAMERA", 1},
    {"VIDEO", 2}
};

/*****************************************
 * Function Name : hwc2chw
 * Description   : This function takes an input image in HWC (height, width, channels)
 *                 format and returns an output image in CHW (channels, height, width) format.
 * Arguments     : image = cv::Mat
 * Return value  : flat_image = cv::Mat
 ******************************************/
Mat hwc2chw(const Mat &image)
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
 * Function Name     : mouse_callback_button_click
 * Description       : Slot Frame mouse callback(add slot and remove slot functionality).
 ******************************************/
void mouse_callback_button_click(int event, int x, int y, int flags, void *userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        /*Add slot button*/
        if (415 < x && x < 565 && 523 < y && y < 573)
            add_slot_in_figure = true;
        /*start inference button*/
        else if (687 < x && x < 837 && 523 < y && y < 573)
            start_inference_parking_slot = true;
        /*exit button*/
        else if (1150 < x && x < 1180 && 10 < y && y < 50)
            exit_all = true;
    }
}

/*****************************************
 * Function Name     : backOrExitButtonCallback
 * Description       : back and exit mouse callback(back and exit functionality in 
 *                     add slot, remove slot and inference window)
 ******************************************/
void backOrExitButtonCallback(int event, int x, int y, int flags, void *userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {

        Rect backButton = Rect(0, 0, 60, 30);
        Rect exitButton = Rect((winWidth-60), 0, winWidth, 30);
        /*back button*/
        if (backButton.contains(Point(x, y)))
            stop = true;
        /*exit button*/
        else if (exitButton.contains(Point(x, y)))
        {   stop = true;
            exit_all = true;
        }
    }
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
        Rect backButton = Rect(0, 0, 60, 30);
        Rect exitButton = Rect((winWidth-60), 0, winWidth, 30);
        if (backButton.contains(Point(x, y)))
        {
            drawing_box = false;
            stop = true;
        }
        else if (exitButton.contains(Point(x, y)))
        {
            drawing_box = false;
            stop = true;
            exit_all = true;
        }
        else
            box_start = Point2f(x, y);
    }
    else if (event ==  EVENT_MOUSEMOVE && stop == false)
    { 
        if(drawing_box)
            box_end = Point2f(x,y);
    }
    else if (event == EVENT_LBUTTONUP && stop == false)
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
    if(stop == true)
    {
        destroyAllWindows();
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
    winWidth = img.cols;
    Rect backButton(0, 0, 60, 30);
    Rect exitButton((winWidth-60), 0, winWidth, 30);
    rectangle(img, backButton, Scalar(255, 255, 255), -1);
    putText(img, "Back", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
    rectangle(img, exitButton, Scalar(255, 255, 255), -1);
    putText(img, "Exit", Point((winWidth-50), 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, LINE_AA);
    for (int i = 0; i < boxes.size(); i++)
    {
        rectangle(img, boxes[i], Scalar(0, 0, 255), 2);
        putText(img, "id: " + to_string(i + 1), Point(boxes[i].x + 10, boxes[i].y - 10), FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 0, 0), 2);
    }
    int key = 0;
    cv::namedWindow("image", cv::WINDOW_NORMAL);
    cv::imshow("image", img);
    cv::setMouseCallback("image", get_patches, &img);
    key = cv::waitKey(0);
    if (key == 114) // Wait for 'r' key press to redraw!!
    {
        std::cout << "re-draw!!\n";
        cv::destroyAllWindows();
        return 1;
    }
    else if(key == 13)
    {
        cv::destroyAllWindows();
        return 0;
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
    vid.open(gstreamer_pipeline, cv::CAP_GSTREAMER);
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
    winWidth = frame.cols;
    Rect backButton(0, 0, 60, 30);
    Rect exitButton((winWidth-60), 0, winWidth, 30);
    rectangle(frame, backButton, Scalar(255, 255, 255), -1);
    putText(frame, "Back", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
    rectangle(frame, exitButton, Scalar(255, 255, 255), -1);
    putText(frame, "Exit", Point((winWidth-50), 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, LINE_AA);
    putText(frame, "Enter comma separated integers to remove:", Point(50, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, LINE_AA);
    imshow("Frame", frame);
    string inputText;
    int key = -1;
    while (key != 13)
    {
        if ((key >= '0' && key <= '9') || key == ',')
            inputText += (char)key;
        putText(frame, inputText, Point(100, 100), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);
        imshow("Frame", frame);
        setMouseCallback("Frame", backOrExitButtonCallback);
        if(stop == true)
        {
            destroyAllWindows();
            break;
        }
        key = waitKey(10);
    }
    vector<int> indicesToRemove;
    stringstream ss(inputText);
    string token;
    while (getline(ss, token, ','))
    {
        int index;
        if(stringstream(token) >> index)
        {
            indicesToRemove.push_back(index);
        }
    }
    sort(indicesToRemove.rbegin(), indicesToRemove.rend());
    for (int i : indicesToRemove)
    {
        if(i > 0 && i <= boxes.size())
            boxes.erase(boxes.begin() + (i-1));
    }
}

/*****************************************
 * Function Name : process_frames
 * Description   : takes Mat frames as the input and passes through the model runtime and process the frames
 * Arguments     : queue Mat frames
 * Return value  : void
 ******************************************/
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
            winWidth = img.cols;
            Rect backButton(0, 0, 60, 30);
            Rect exitButton((winWidth-60), 0, winWidth, 30);
            rectangle(img, backButton, Scalar(255, 255, 255), -1);
            putText(img, "Back", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
            rectangle(img, exitButton, Scalar(255, 255, 255), -1);
            putText(img, "Exit", Point((winWidth-50), 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, LINE_AA);
            imshow("Inference", img);
            waitKey(10);
            setMouseCallback("Inference", backOrExitButtonCallback);
            if(stop)
            {
                destroyAllWindows();
                break;
            }
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
        return (uint32_t)NULL;
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
 * Function Name : capture_frame
 * Description   : function to capture from Camera(MIPI/USB) or Video
 * Arguments     : cap_pipeline = string
 *                 input_mode   = string
 *                 Mat frames   = queue
 *                 stop         = bool
 * Return value  : void
 ******************************************/
void capture_frame(std::string cap_pipeline, std::string input_mode, queue<Mat> &frames, bool &stop)
{
    cv::VideoCapture g_cap;
    /* Capture stream of frames from camera using Gstreamer pipeline */
    g_cap.open(cap_pipeline, cv::CAP_GSTREAMER);
    if (!g_cap.isOpened())
    {
        /* This section prompt an error message if no video stream is found */
        std::cout << "[ERROR] Error opening " << input_mode << " source!!\n"
                  << std::endl;
        return;
    }
    /* Taking an everlasting loop to show the output */
    Mat frame;
    while (!stop)
    {
        g_cap.read(frame);
        /* Breaking the loop if no video frame is detected */
        if (frame.empty())
        {
            std::cout << "[INFO] Video ended or corrupted frame !\n";
            return;
        }
        frames.push(frame);
    }
}

/*****************************************
 * Function Name : input_source_select
 * Description   : function to select input source
 * Arguments     : input_mode   = string
 *                 input_source = string
 * Return value  : 0  = Input source selected
 *                 -1 = Error selecting inputh source
 ******************************************/
int input_source_select(std::string input_mode, std::string input_source)
{
    switch (input_mode_map[input_mode])
    {
        /* Input Source : Camera */
        case 1:
        {
            /* MIPI Camera */
            if(input_source == "MIPI")
            {
                std::cout << "[INFO] MIPI CAMERA \n";
                mipi_cam_init();
                /* check the status of device */
                std::string media_port = query_device_status("CRU");
                if(media_port == "")
                {
                    fprintf(stderr, "[ERROR] MIPI Camera not connected. \n");
                    return -1;
                }
                /* gstremer pipeline to read input image source */
                gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
            }
            /* USB Camera */
            else if(input_source == "USB")
            {
                std::cout << "[INFO] USB CAMERA \n";
                /* check the status of device */
                std::string media_port = query_device_status("usb");
                if (media_port == "")
                {
                    fprintf(stderr, "[ERROR] USB Camera not connected. \n");
                    return -1;
                }
                /* gstremer pipeline to read input image source */
                gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
            }
            else
            {
                std::cout << "[ERROR] Invalid Camera Source :" << input_source << std::endl;
                return -1;
            }
            break;
        }
        /* Input Source : VIDEO */
        case 2:
        {
            std::cout << "[INFO] VIDEO \n";
            /* read input image */
            std::cout << "Loading from :" << input_source << "\n";
            /* gstremer pipeline to read input image source */
            gstreamer_pipeline = "filesrc location=" + input_source + " ! decodebin ! videoconvert ! appsink";
            break;
        }
        default:
        {
            std::cout << "[ERROR] Invalid Input mode :" << input_mode << std::endl;
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    if( argc == 2  )
    {
        input_mode = argv[1];
        if(input_mode == "CAMERA")
            std::cout<<"[ERROR] please specify MIPI/USB camera\n";
        else if(input_mode == "VIDEO")
            std::cout<<"[ERROR] please specify the Video path\n";
        else
            std::cout << "[ERROR] Input Source not given\n";
        std::cout << "[INFO] End Application\n";
        return -1;
    }
    else if( argc == 3  )
    {
        input_mode = argv[1];
        input_source = argv[2];
    }
    else
    {
        /* End application */
        std::cout << "[ERROR] Invalid arguments\n";
        std::cout << "[INFO] End Application\n";
        return -1;
    }
    if(input_source_select(input_mode, input_source) == -1)
    {
        std::cout << "\n[INFO] Terminating Application\n";
        return -1;
    }
    /*Load model_dir structure and its weight to runtime object */
    drpaimem_addr_start = get_drpai_start_addr();

    if (drpaimem_addr_start == (uint64_t)NULL)
    {
        /* Error notifications are output from function get_drpai_start_addr(). */
	    fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address. \n");
        return -1;
    }

    runtime_status = runtime.LoadModel(model_dir, drpaimem_addr_start + DRPAI_MEM_OFFSET);
    
    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load model. \n");
        return -1;
    }

    std::cout << "loaded model:" << model_dir << "\n";
    
    namedWindow(app_name, WINDOW_NORMAL);
    resizeWindow(app_name, 1200, 800);
    while (waitKey(1))
    {
        Mat frame;
        frame = cv::imread("parking_bg.jpg");
        cv::resize(frame, frame, cv::Size(1200,800));
        /* Edit slots button */
        rectangle(frame, Point(415, 523), Point(565, 573), Scalar(255, 0, 0), -1);
        putText(frame, "Edit Slots", Point(415 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 1);
        /* Start Inference Button */
        rectangle(frame, Point(687, 523), Point(900, 573), Scalar(255, 0, 0), -1);
        putText(frame, "Start Inference", Point(687 + (int)150 / 4, 553), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 1);
        /* exit button */
        rectangle(frame, Point(1150, 10), Point(1180, 40), Scalar(0, 0, 255), -1);
        putText(frame, "X", Point(1155, 35), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
        /* Edit slot window */
        if (add_slot_in_figure)
        {
            add_slot_in_figure = false;
            destroyAllWindows();
            namedWindow("Slot", WINDOW_NORMAL);
            resizeWindow("Slot", 400, 400);
            Rect addButtonRect(50, 50, 150, 100);
            Rect removeButtonRect(200, 50, 150, 100);
            /* Add slot button in edit slot window */
            rectangle(frame1, addButtonRect, Scalar(0, 255, 0), -1);
            putText(frame1, "Add Slot", Point(75, 105), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
            /* remove slot button in edit slot window */
            rectangle(frame1, removeButtonRect, Scalar(0, 0, 255), -1);
            putText(frame1, "Remove Slot", Point(210, 105), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
            imshow("Slot", frame1);
            stop = false;
            /* Mouse button click callback for edit slot window */
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
        /* Inference window */
        else if (start_inference_parking_slot)
        {
            start_inference_parking_slot = false;
            destroyAllWindows();
            std::cout << "Running tvm runtime" << std::endl;

            queue<Mat> frames;
            stop = false;
            thread readThread(capture_frame, gstreamer_pipeline, input_mode, ref(frames), ref(stop));
            cout << "Waiting for read frames to add frames to buffer!!!!!" << endl;
            this_thread::sleep_for(std::chrono::seconds(0));
            thread processThread(process_frames, ref(frames), ref(stop));
            cout << "Processing thread started......" << endl;
            waitKey(0);
            stop = false;
            readThread.join();
            processThread.join();
        }
        /* Exit the application */
        else if (exit_all)
        {
            destroyAllWindows();
            std::cout << "\n[INFO] Terminating Application" << std::endl;
            break;
        }
        /* Mouse button click callback for main Window */
        setMouseCallback(app_name, mouse_callback_button_click);
        imshow(app_name, frame);
    }
    return 0;
}