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
 * File Name    : face_recognition.cpp
 * Version      : 1.0
 * Description  : RZ/V2L SDK AI Application: Face Authentication
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
#include "opencv2/core.hpp"
#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include <glob.h>
#include <cmath>
#include "PreRuntime.h"
#include "MeraDrpRuntimeWrapper.h"

#define BLUE                        cv::Scalar(255, 0, 0)
#define WHITE                       cv::Scalar(255, 255, 255)
#define BLACK                       cv::Scalar(0, 0, 0)
#define GREEN                       cv::Scalar(0, 255, 0)
#define RED                         cv::Scalar(0, 0, 255)
#define ASH                         cv::Scalar(150, 150, 150)
/* DRP-AI memory offset for model object file*/
#define DRPAI_MEM_OFFSET            (0X38E0000)

using namespace cv;
using namespace std;

MeraDrpRuntimeWrapper runtime;
MeraDrpRuntimeWrapper runtime_age;

std::string model_dir = "facenet_model";
std::string str1 = "Add ID Image";
std::string str2 = "Validate";
std::string str3 = "X";

unsigned int add_faces_x0   = 189;
unsigned int add_faces_y0   = 350;
unsigned int add_faces_x1   = 353;
unsigned int add_faces_y1   = 400;

unsigned int recognize_x0   = 481;
unsigned int recognize_y0   = 350;
unsigned int recognize_x1   = 631;
unsigned int recognize_y1   = 400;

unsigned int termination_x0 = 1150;
unsigned int termination_y0 = 10;
unsigned int termination_x1 = 1180;
unsigned int termination_y1 = 40;

unsigned int back_x0 = 0;
unsigned int back_y0 = 0;
unsigned int back_x1 = 60;
unsigned int back_y1 = 30;

unsigned int winWidth   = 0;
unsigned int winHeight  = 0;

cv::Mat img;
cv::Mat image;
cv::Mat frame;

vector<float> floatarr(512);
vector<float> img_arr1(512);
vector<float> img_arr2(512);

/* Image buffer (u-dma-buf) */
unsigned char *img_buffer;
unsigned int try_cnt;
bool add_face_clicked           = false;
bool recognize_face_clicked     = false;
bool termination_clicked        = false;
bool back_clicked               = false;
bool img1_array1_udated         = false;
bool img1_array2_udated         = false;
bool cam_kill_esc_key           = false;
bool backButtonClicked          = false;
bool addOrValidateButtonClicked = false;

uint64_t drpaimem_addr_start = 0;
bool runtime_status = false; 
std::string gstreamer_pipeline;

int ptb1;
int ptb2;
int ptb3;
int ptb4;

std::map<std::string, int> input_source_map =
{
    {"MIPI", 1},
    {"USB", 2}
};

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
 * Function Name : cosine_similarity
 * Description   : This function computes the cosine similarity between two input
 *                 feature vectors represented as std::vector<float>.
 * Arguments     : features1 = std::vector<float>
 *                 features2 = std::vector<float>
 * Return value  : float value that represents the cosine similarity
 *                 between the two input feature vectors.
 ******************************************/
float cosine_similarity(const std::vector<float> &features1, const std::vector<float> &features2)
{
    if ((features1.empty() || features2.empty()) || (features1.size() != features2.size()))
        return 0.0;
    float dot_product = 0.0;
    for (int i = 0; i < features1.size(); i++)
    {
        dot_product += features1[i] * features2[i];
    }
    float norm1 = 0.0;
    float norm2 = 0.0;
    for (int i = 0; i < features1.size(); i++)
    {
        norm1 += features1[i] * features1[i];
        norm2 += features2[i] * features2[i];
    }
    norm1 = std::sqrt(norm1);
    norm2 = std::sqrt(norm2);
    float similarity = 0.0;
    if (norm1 != 0.0 && norm2 != 0.0)
    {
        similarity = dot_product / (norm1 * norm2);
    }
    return similarity;
}
/*****************************************
 * Function Name : euclidean_distance
 * Description   : This function takes two vectors of floats (a and b)
 *                 and an integer n as parameters and returns a float representing the Euclidean distance between the two vectors.
 * Arguments     : vector<float> a: a vector of float values representing the first vector for which to compute the Euclidean distance.
 *                 vector<float> b: a vector of float values representing the second vector for which to compute the Euclidean distance.
 * Return value  : float value representing the Euclidean distance between the two input vectors a and b.
 ******************************************/
float euclidean_distance(vector<float> a, vector<float> b, int n)
{
    float dist = 0.0;
    double length_a;
    double length_b;
    for (int i = 0; i < n; i++)
    {
        length_a += a[i] * a[i];
    }
    for (int i = 0; i < n; i++)
    {
        length_b += b[i] * b[i];
    }
    for (int i = 0; i < n; i++)
    {
        float diff = a[i] / sqrt(length_a) - b[i] / sqrt(length_b);
        dist += diff * diff;
    }
    return sqrt(dist);
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
vector<float> run_inference(Mat croppedImg)
{
    std::vector<Mat> bgr_channels;
    split(croppedImg, bgr_channels);
    Mat eq_b, eq_g, eq_r;
    equalizeHist(bgr_channels[0], eq_b);
    equalizeHist(bgr_channels[1], eq_g);
    equalizeHist(bgr_channels[2], eq_r);
    std::vector<Mat> eq_channels = {eq_b, eq_g, eq_r};
    Mat eq;
    merge(eq_channels, eq);
    croppedImg = eq;
    Mat patch1;
    vector<float> floatarr_inf(2);
    cv::Mat rgb_img;
    cv::Mat resized_img;
    cv::Size size(160, 160);
    cv::resize(croppedImg, resized_img, size, INTER_LINEAR);
    cv::cvtColor(resized_img, rgb_img, cv::COLOR_BGR2RGB);
    cv::Mat inp_img;
    inp_img = hwc2chw(rgb_img);
    patch1 = inp_img;
    uint8_t ret = 0;
    Mat patch_con;
    if (!patch1.isContinuous())
        patch_con = patch1.clone();
    else
        patch_con = patch1;
    Mat patch_norm;
    cv::normalize(patch_con, patch_norm, 0, 1, cv::NORM_MINMAX, CV_32FC1);
    float *temp_input = new float[patch_norm.rows * patch_norm.cols * 3];
    memcpy(temp_input, patch_norm.ptr<float>(), patch_norm.total() * 3 * sizeof(float));
    runtime.SetInput(0, temp_input);
    runtime.Run();
    auto output_num = runtime.GetNumOutput();
    if (output_num != 1)
    {
        std::cerr << "[ERROR] Output size : not 1." << std::endl;
        vector<float> error = {0};
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
    if (event == EVENT_LBUTTONDOWN)
    {
        Rect backButton = Rect(0, 0, 60, 30);
        Rect exitButton = Rect((winWidth-60), 0, winWidth, 30);
        Rect addOrValidateButton = Rect(ptb1,ptb2,ptb3,ptb4);
        if (backButton.contains(Point(x, y)))
        {
            backButtonClicked = true;
        }
        else if (exitButton.contains(Point(x, y)))
        {   
            backButtonClicked = true;
            termination_clicked = true;
        }
        else if (addOrValidateButton.contains(Point(x, y)))
        {
            addOrValidateButtonClicked = true;
        }
    }
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
    if (event == EVENT_LBUTTONDOWN)
    {
        if (add_faces_x0 < x && x < add_faces_x1 && add_faces_y0 < y && y < add_faces_y1 && img1_array1_udated == false)
        {
            std::cout << "clicked add face \n";
            add_face_clicked = true;
        }
        else if (recognize_x0 < x && x < recognize_x1 && recognize_y0 < y && y < recognize_y1 && img1_array1_udated == true) 
        {
            std::cout << "cliked compare face \n";
            recognize_face_clicked = true;
        }
        else if((winWidth-50) < x && x < (winWidth-20) && 10 < y && y < 40)
        {
            std::cout << "cliked quit application \n";
            termination_clicked = true;
        }
    }
}
/*****************************************
 * Function Name : capture_frame
 * Description   : This function captures a frame from a video source (in this case, a webcam) 
 *                 and displays it on the screen.
 * Arguments     : string cap_pipeline input source pipeline
 * Return value  : returns the cropped image as a Mat object.
 ******************************************/
Mat capture_frame(std::string cap_pipeline)
{
    cout << "capture frame\n";
    Mat patch1;
    Mat img1;
    cv::VideoCapture vid;
    
    vid.open(cap_pipeline, cv::CAP_GSTREAMER);
    vid >> img1;
    int height = img1.rows;
    int width = img1.cols;
    int wait_key = 0;
    cv::Rect roi((int)(img1.cols/2-width/8), (int)(img1.rows/2-width/8), width/3, height/3); /* x,y,w,h */ 
    cv::Mat croppedImg;
    vector<string> predictions;
    while (1)
    {
        vid >> img1;
        flip(img1, img, 1);
   
        cv::Point pt1((int)(width/2-width/6), (int)(height/2-width/6));
        cv::Point pt2((int)(width/2+width/6), (int)(height/2+width/6));

        /* Store vertices in vector */
        std::vector<cv::Point> vertices;
        vertices.push_back(pt1);
        vertices.push_back(cv::Point(pt2.x, pt1.y));
        vertices.push_back(pt2);
        vertices.push_back(cv::Point(pt1.x, pt2.y));
        /* Draw rectangles */
        cv::polylines(img, std::vector<std::vector<cv::Point>>{vertices}, true, BLUE, 3);
        cv::putText(img, "Adjust face into the box!!", cv::Point(pt1.x,pt1.y-30), cv::FONT_HERSHEY_DUPLEX, 1, BLUE, 4, false);
        winWidth = img.cols;
        winHeight = img.rows;

        ptb1 = ((int)(winWidth/2-winWidth/10));
        ptb2 = ((int)(winHeight/2+winHeight/4));
        ptb3 = ((int)(winWidth/5));
        ptb4 = ((int)(winHeight/10));

        Rect backButton(0, 0, 60, 30);
        Rect exitButton((winWidth-60), 0, winWidth, 30);
        Rect addOrValidateButton((int)(winWidth/2-winWidth/10),(int)(winHeight/2+winHeight/4),(int)(winWidth/5),(int)(winHeight/10));
        rectangle(img, backButton, Scalar(255, 255, 255), -1);
        putText(img, "Back", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
        rectangle(img, exitButton, Scalar(255, 255, 255), -1);
        putText(img, "Exit", Point((winWidth-50), 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, LINE_AA);
        rectangle(img, addOrValidateButton, Scalar(255, 255, 255), -1);
        if(add_face_clicked)
            putText(img, "Add Face", cv::Point((int)(winWidth/2-winWidth/10) + 30,(int)(winHeight/2+winHeight/4) + 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
        else if(recognize_face_clicked)
            putText(img, "Validate", cv::Point((int)(winWidth/2-winWidth/10) + 30,(int)(winHeight/2+winHeight/4) + 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
        wait_key = waitKey(10);
        if(addOrValidateButtonClicked || backButtonClicked)
        {
            if(backButtonClicked)
            {
                cam_kill_esc_key = true;
                img1_array1_udated = false;
            }
            cv::destroyAllWindows();
            break;   
        }
        cv::Mat croppedImg = img(roi);
        cv::resize(croppedImg, croppedImg, Size(64, 64), INTER_LINEAR);
        cv::imshow("select face", img);  
        cv::setMouseCallback("select face", ButtonCallBack);
    }
    addOrValidateButtonClicked = false;
    backButtonClicked = false;
    croppedImg = img(roi); 
    return croppedImg;
}
/*****************************************
 * Function Name : compare_with_existing_faces
 * Description   : This function takes in a vector of floats floatarr representing the 
 *                 features of a face detected in an image,and compares it with the features of 
 *                 previously stored faces in text files located in the directory "faces/".
 * Arguments     : floatarr = vector<float>
 * Return value  : The return value of the function compare_with_existing_faces is a string.
 *                 It can be either the string "none" if there is no match or the path to the text file that 
 *                 contains the 512-dimensional feature vector of the matching face.
 ******************************************/
string compare_with_existing_faces(vector<float> floatarr1,vector<float> floatarr2)
{
    float co_thresh = 0.12; 
    float eu_thresh = 10.0;
    float max_value_co = 0.0;
    float min_value_eu = 10000000.0;
    float co_score = 0.0;
    float eu_distance = 0.0;
    string match = "none";
    co_score = cosine_similarity(floatarr1, floatarr2);
    eu_distance = euclidean_distance(floatarr1, floatarr2, 512);
    if (co_score > max_value_co)
        max_value_co = co_score;
    if (eu_distance < min_value_eu)
        min_value_eu = eu_distance;
    cout << "cosine similarity  : " << co_score <<"\n";
    cout << "euclidean_distance : " << eu_distance <<"\n";
    if ((min_value_eu < eu_thresh) && (max_value_co > co_thresh))
    {
        return "match";
    }
    else
    {
        try_cnt++;
        return "none";
    }
}
/*****************************************
 * Function Name : draw_rect_add_txt
 * Description   : This function to draws a rectangle and adds text on it.
 * Arguments     : The function takes four parameters: a string variable named "text" 
 *                 which represents the text to be added on the rectangle, 
 *                 and four integer variables named "x0", "y0", "x1", and "y1" 
 *                 which represent the coordinates of the rectangle's top-left and bottom-right corners.
 ******************************************/
void draw_rect_add_txt(string text, int x0, int y0, int x1, int y1,
                       cv::Scalar FILL_COLOUR,cv::Scalar TEXT_COLOUR,float text_scale,float text_thickness)
{
    rectangle(frame, Point(x0, y0), Point(x1, y1), FILL_COLOUR, -1);
    putText(frame, text, Point(x0 + (int)150 / 4, y0 + 30), 
            FONT_HERSHEY_SIMPLEX, text_scale, TEXT_COLOUR, text_thickness);
}
/*****************************************
 * Function Name : img_preprocess
 * Description   : This function is for preprocessing of input images(frames).
 * Arguments     : The function takes four parameters: a string variable named "text" 
 *                 which represents the text to be added on the rectangle, 
 *                 and four integer variables named "x0", "y0", "x1", and "y1" 
 *                 which represent the coordinates of the rectangle's top-left and bottom-right corners.
 ******************************************/
void img_preprocess(string text, int x0, int y0, int x1, int y1)
{
    if ((recognize_face_clicked == false) && (add_face_clicked == false))
        draw_rect_add_txt(text, x0, y0, x1, y1,ASH,WHITE,0.5,1);
    destroyAllWindows();
    /* capture pre-processed image */
    Mat croppedImg = capture_frame(gstreamer_pipeline);
    /* run infernce */
    floatarr = run_inference(croppedImg);
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

int get_input_source(std::string camera_source)
{
    switch (input_source_map[camera_source])
    {
        /* Input Source : MIPI Camera */
        case 1:
        {
            std::cout << "[INFO] MIPI CAMERA \n";
            mipi_cam_init();
            /* check the status of device */
            std::string media_port = query_device_status("CRU");
            if (media_port == "")
            {
                fprintf(stderr, "\n[ERROR] MIPI Camera not connected. \n");
                return -1;
            }
            /* gstremer pipeline to read input image source */
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
            break;
        }
        /* Input Source : USB Camera */
        case 2:
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
        /* default case/ Invalid case */
        default:
        {
            std::cout<<"\n[ERROR] Invalid CAMERA source: "<< camera_source <<"\n";
            std::cout<<"[INFO] End Application\n";
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    const std::string app_name = "Face Recognition";
    std::string input_source;
    std::string camera_source;
    /* check the input source is valid or not */
    if(argc == 2 || argc == 3)
    {
        /* get the valid input source */
        input_source = argv[1];
        if(input_source == "CAMERA")
        {
            if(argc == 2)
            {
                /* End application */
                std::cout<<"\n[ERROR] please specify MIPI/USB camera\n";
                std::cout << "[INFO] End Application\n";
                return -1;
            }
            else if(argc == 3)
                camera_source = argv[2];
        }
        else
        {
            /* End application */
            std::cout << "\n[ERROR] Invalid input source :"<<input_source<<"\n";
            std::cout << "[INFO] End Application\n";
            return -1;
        }
    }
    else
    {
        /* End application */
        std::cout << "\n[ERROR] Input Source not given\n";
        std::cout << "[INFO] End Application\n";
        return -1;
    }

    /* check input source status */
    int source_status = get_input_source(camera_source);
    if(source_status < 0)
        return -1;

    /* Load model_dir structure and its weight to runtime object */
    drpaimem_addr_start = get_drpai_start_addr();

    if (drpaimem_addr_start == (uint64_t)NULL)
    {
        /* Error notifications are output from function get_drpai_start_addr(). */
	    fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address. \n");
        return 0;
    }
    /* check model runtime status */
    runtime_status = runtime.LoadModel(model_dir, drpaimem_addr_start + DRPAI_MEM_OFFSET);
    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load model. \n");
        return 0;
    }
    cout << "loaded model:" << model_dir << endl;
    
    /* set outputwindow */
    namedWindow(app_name, WINDOW_NORMAL);
    resizeWindow(app_name,800,600);

    while (waitKey(1))
    {
        frame = cv::imread("face_rec_bg.jpg");
        /* check if any button is clicked */
        if ((add_face_clicked) || (recognize_face_clicked) || (termination_clicked))
        {
            /* check if addface button is clicked */
            if (add_face_clicked && img1_array1_udated == false)
            {
                /* pre-process and post-process section */
                img_preprocess(str1, add_faces_x0, add_faces_y0, add_faces_x1, add_faces_y1);
                if(cam_kill_esc_key == false)
                {
                    /* updates image array 1 */
                    for (int i = 0; i < 512; i++)
                    {
                        img_arr1[i] = floatarr[i];
                    }
                    frame = cv::imread("face_rec_bg.jpg");
                    cv::putText(frame, "Face added !!", cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0, GREEN, 2);
                    cv::imshow(app_name, frame);
                    cv::waitKey(2000);
                    img1_array1_udated = true;
                }
                add_face_clicked = false;
                cam_kill_esc_key = false;
            }
            /* check if validate button if clicked */
            else if (recognize_face_clicked && img1_array1_udated == true)
            {
                INIT:
                frame = cv::imread("face_rec_bg.jpg");
                /* pre-process and post-process section */
                img_preprocess(str2, recognize_x0, recognize_y0, recognize_x1, recognize_y1);
                if(cam_kill_esc_key == false)
                {
                    /* updates image array 2 */
                    for (int i = 0; i < 512; i++)
                    {
                        img_arr2[i] = floatarr[i];
                    }
                    /* compare two image arrays */
                    string match = compare_with_existing_faces(img_arr1,img_arr2);
                    cout << "return_string:" << match <<"\n";
                    cv::waitKey(10);
                    /* the two image array not matching */
                    if (match == "none")
                    {
                        /* checking whether if maxmum retry is happend or not */
                        if (try_cnt > 2)
                        {
                            cv::putText(frame,"Face authentication failed !!!", cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0, RED, 2);
                            try_cnt = 0;
                            std::fill(img_arr1.begin(),img_arr1.end(),0);
                            std::fill(img_arr2.begin(),img_arr2.end(),0);
                            img1_array1_udated = false;
                            cv::imshow(app_name, frame);
                            cv::waitKey(3000);
                        }
                        /* retry to add new image array */
                        else 
                        {
                            cv::putText(frame,"Face authentication failed,Please try again!!", cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0, RED, 2);
                            cv::imshow(app_name, frame);
                            cv::waitKey(3000);
                            goto INIT;
                        }
                    }
                    /* both image arrays are matching */
                    else if(match == "match")
                    {
                        cv::putText(frame,"Face authentication using ID is succesfull !!!", cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0, GREEN, 2);
                        cv::imshow(app_name, frame);
                        cv::waitKey(3000);
                        try_cnt = 0;
                        std::fill(img_arr1.begin(),img_arr1.end(),0);
                        std::fill(img_arr2.begin(),img_arr2.end(),0);
                        img1_array1_udated = false;
                    }  
                }
                recognize_face_clicked = false;
                cam_kill_esc_key = false;
            }
            /* Terminate application */
            else if(termination_clicked)
            {
                std::cout << "\n[INFO] End Application\n";
                break;
            }
        }
        /* check the termination butten is clicked */
        else
        {
            winWidth = frame.cols;
            /* button for add-face */
            draw_rect_add_txt(str1, add_faces_x0, add_faces_y0, add_faces_x1, add_faces_y1, ASH, WHITE,0.5,1);
            /* button for recogniz */
            draw_rect_add_txt(str2, recognize_x0, recognize_y0, recognize_x1, recognize_y1, ASH, WHITE,0.5,1);
            /* butten for termination */
            rectangle(frame, Point((winWidth-50), 10), Point((winWidth-20), 40), Scalar(0, 0, 255), -1);
            putText(frame, "X", Point((winWidth-45), 35), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
        }
        /* sets a common mouse callback for mouse butten click */
        setMouseCallback(app_name, mouse_callback_button_click);
        imshow(app_name, frame);
    }
    destroyAllWindows();
    return 0;
}
