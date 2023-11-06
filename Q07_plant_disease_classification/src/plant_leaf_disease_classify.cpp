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
 * File Name    : plant_leaf_disease_classify.cpp
 * Version      : 1.0
 * Description  : RZ/V2L SDK AI Application: Plant leaf disease classification
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
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>    /* For O_RDWR */
#include <sys/ioctl.h>
#include <linux/drpai.h>
/*DRP-AI memory area offset for model objects*/
/*Offset value depends on the size of memory area used by DRP-AI Pre-processing Runtime Object files*/
#define DRPAI_MEM_OFFSET        (0x38E0000)

#define ASH                     cv::Scalar(150, 150, 150)
#define WHITE                   cv::Scalar(255, 255, 255)
#define BLUE                    cv::Scalar(255, 0, 0)
#define GREEN                   cv::Scalar(0, 255, 0)
#define RED                     cv::Scalar(0, 0, 255)
#define BLACK                   cv::Scalar(0, 0, 0)

using namespace cv;
using namespace std;

/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper runtime;
/*Model input info*/
#define MODEL_IN_H (256)
#define MODEL_IN_W (256)
#define MODEL_IN_C (3)

/*Frame input info*/
#define FRAME_IN_H (480)
#define FRAME_IN_W (640)
#define FRAME_IN_C (3)

/*Threshold value info*/
#define threshold 0.6

bool drawing_box  = false;
bool doneClicked = false;
bool exitClicked = false;

int slot_id;
unsigned int out;
int duration;
int winWidth = 0;
int winHeight = 0;

std::string score_per = "";
std::string input_source = "";
std::string input_file = "";
std::string gstreamer_pipeline = "";
std::vector<float>floatarr(1);
std::vector<Rect> boxes;
Point2f box_start, box_end;

cv::VideoCapture cap;
cv::Rect rect;
cv::Mat img;
cv::Mat frames;
cv::Mat frame;
std::string path;

/* Map to store label list */
std::map<int, std::string> class_names;

/* Map to store input source list */
std::map<std::string, int> input_source_map = {
    {"VIDEO", 1},
    {"MIPI", 2},
    {"USB", 3},
    {"IMAGE", 4}
};

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
 * Function Name : run_inference
 * Description   : frame preprocessing and postprocessing.
 * Arguments     : Mat frame
 * Return value  : int 0 - 8 succeeded
 *                  otherwise  -1
 ******************************************/
int run_inference(Mat frame)
{   
    float *output;
    int max_ind     = -1;
    float max_value = -1;
    std::map<float,int> result;
    int result_cnt = 0;
    auto t1 = std::chrono::high_resolution_clock::now();
    /* pre processing the input frame */
    cv::Size size(MODEL_IN_H, MODEL_IN_W);
    /*resize the image to the model input size*/
    cv::resize(frame, frame, size);
    /*convert to FP32*/
    frame.convertTo(frame, CV_32FC3);
    divide(frame, 255.0, frame);
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    frame = hwc2chw(frame);
    /* deep copy, if not continuous */
    if (!frame.isContinuous())
        frame = frame.clone();
    result.clear();
    float *temp_input = frame.ptr<float>();
    /*start inference using drp runtime*/
    if ((frame.ptr<float>()) != 0)
    {
        /*Set Pre-processing output to be inference input. */
        runtime.SetInput(0, temp_input);
        runtime.Run();
        /* Get the number of output.  */
        auto output_num = runtime.GetNumOutput();
        if (output_num != 1)
        {
            std::cout << "[ERROR] Output size : not 1." << std::endl;
            return -1;
        }
        /* get output buffer */
        auto output_buffer = runtime.GetOutput(0);
        int64_t out_size = std::get<2>(output_buffer);
        floatarr.resize(out_size);
        

         /* Post-processing for FP16 */
        if(InOutDataType::FLOAT16 == std::get<0>(output_buffer))
        {
            std::cout << "[INFO] FLOAT16 Datatype\n";
            /* Extract data in FP16 <uint16_t>. */
            uint16_t *data_ptr = reinterpret_cast<uint16_t *>(std::get<1>(output_buffer));
            for (int n = 0; n < out_size; n++)
            { 
                /* Cast FP16 output data to FP32. */
                floatarr[n]= float16_to_float32(data_ptr[n]);
                softmax(floatarr.data(),out_size);
                result[floatarr[n]] = n;
                if (floatarr[n] > max_value)
                {
                     max_value = floatarr[n];
                     max_ind = n;
                }
            }
            auto t2 = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            std::cout<<"\n[INFO] AI-Inference Time(ms): "<<duration<<" ms\n";
            
            float score = floor(((max_value)*100)*100)/100;
            score_per = std::to_string(score);
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
    }
    else
    {
        std::cout << "[INFO]not setting the input!!!\n";
        return -1;
    }
    return 0;
}

/*****************************************
 * Function Name : classification
 * Description   : frame preprocessing and postprocessing.
 * Arguments     : out int index number
 ******************************************/
void classification(int out)
{   
    if (out != -1)
    {   
        int8_t counter=1;
        char *strg = new char[class_names[out].length()+1];
        std::strcpy(strg,class_names[out].c_str());
        //std::cout << "\n[INFO] Class:" << class_names[out] << "\n";
        cv::resize(frame, frame, cv::Size(FRAME_IN_W,FRAME_IN_H),cv::INTER_LINEAR);
        char *tknv = strtok(strg, "___");
        std::string tknv1,tknv2;
        while (tknv != NULL)
        {
            if(counter == 1)
            {
                std::cout<<"\n[INFO] Plant leaf: " << tknv << "\n";
                tknv1 = std::string(tknv);
            }
            else if(counter == 2)
            {
                std::cout<<"\n[INFO] Status: " << tknv << "\n";
                tknv2 = std::string(tknv);
            }
        tknv = strtok(NULL, "___");
        counter++;
        }
        cv::putText(frame, "Plant leaf: "+tknv1, cv::Point(5, 17), cv::FONT_HERSHEY_SIMPLEX, 0.6, BLUE, 2);
        cv::putText(frame, "Status: "+tknv2, cv::Point(5, 39), cv::FONT_HERSHEY_SIMPLEX, 0.6, BLUE, 2);
        cv::putText(frame, "Score: "+score_per+"%", cv::Point(5, 60), cv::FONT_HERSHEY_SIMPLEX, 0.6,BLUE, 2);  
        cv::putText(frame,"AI-Inference Time(ms): "+std::to_string(duration), cv::Point(5, 80), cv::FONT_HERSHEY_SIMPLEX, 0.6, BLUE, 2);    
        cv::waitKey(30);
    }
    else
        cv::putText(frame,"Cannot Identify ! ",cv::Point(5, 17), cv::FONT_HERSHEY_SIMPLEX, 0.6, RED, 2);
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
void buttonCallBack(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDBLCLK)
        exitClicked = true;
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
    Rect doneButton = Rect(0, 0, 60, 30);
    if (event == EVENT_LBUTTONDOWN)
    {
        if (doneButton.contains(Point(x, y)))
        {
            doneClicked = true;
            drawing_box = false;
        }
        else
        {
            drawing_box = true;
            box_start = Point2f(x, y);
        }
    }
    else if (event == EVENT_MOUSEMOVE && drawing_box == true)
    {
        if (drawing_box)
            box_end = Point2f(x, y);
    }
    else if (event == EVENT_LBUTTONUP && drawing_box == true)
    {
        drawing_box = false;
        box_end = Point2f(x, y);
        putText(img, "area_selected", box_start, FONT_HERSHEY_COMPLEX, 1.0, BLUE, 2);
        slot_id += 1;
        rect = cv::Rect(box_start, box_end);
        Rect box(box_start, box_end);
        boxes.push_back(box);
    }
    else if (event == cv::EVENT_LBUTTONDBLCLK)
    {
        exitClicked = true;
        drawing_box = false;
    }

    if (drawing_box)
    {
        rectangle(frame_copy, box_start, box_end, RED, 2);
    }
    else if (!rect.empty())
    {
        rectangle(frame_copy, rect, RED, 2);
    }
    for (int i = 0; i < boxes.size(); i++)
    {
        rectangle(img, boxes[i],RED, 2);
    }
    box_end = Point2f(x, y);
    cv::resize(frame_copy, frame_copy, cv::Size(FRAME_IN_W,FRAME_IN_H), cv::INTER_LINEAR);
    imshow("image", frame_copy);
    if(doneClicked || exitClicked)
    {
        destroyAllWindows();
    }
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
 * Function Name     : draw_rectangle
 * Description       : Function for initializing get patches.
 * Return value      : int = int number
 ******************************************/
int draw_rectangle(void)
{
    slot_id = boxes.size();
    cv::resize(img, img, cv::Size(FRAME_IN_W,FRAME_IN_H), cv::INTER_LINEAR);
    winWidth = img.cols;
    winHeight = img.rows;
    for (int i = 0; i < boxes.size(); i++)
    {
        rectangle(img, boxes[i], RED, 2);
        putText(img, "id: " + to_string(i + 1), Point(boxes[i].x + 10, boxes[i].y - 10), FONT_HERSHEY_DUPLEX, 1.0, BLUE, 2);
    }
    cv::putText(img, "Select area to classify(draw box)", cv::Point(60, 70), cv::FONT_HERSHEY_SIMPLEX, 0.6, GREEN, 2);
    Rect doneButton(0, 0, 60, 30);
    rectangle(img, doneButton, ASH, -1);
    putText(img, "Done", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, BLACK, 1, LINE_AA);
    putText(img,"Double Click to exit the Application!!", Point((int)(winWidth/2 - winWidth/10) + 50, (int)(winHeight) -20), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLUE, 1, LINE_AA);
    // cv::putText(img, "and Press 'ENTER' key", cv::Point(50, 77), cv::FONT_HERSHEY_SIMPLEX, 0.8, RED, 2);
    cv::namedWindow("image", cv::WINDOW_NORMAL);
    cv::imshow("image", img);
    cv::setMouseCallback("image", get_patches, &img);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
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
 * Function Name : capture_frame
 * Description   : function to open camera or video source with respect to the source pipeline.
 * Arguments     : string cap_pipeline input source pipeline
 ******************************************/
void capture_frame(std::string cap_pipeline)
{
    int8_t key  = 0;
    std::cout << "cap pipeline:  " << cap_pipeline << "\n";
    /* Capture stream of frames from camera using Gstreamer pipeline */
    cap.open(cap_pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened())
    {
        /* This section prompt an error message if no video stream is found */
        std::cout << "[ERROR] Error opening video stream or camera !\n" << std::endl;
        return;
    }
    /* getting only first frame to draw the box */
    for (int frame = 0; frame < 5; frame++)
    {   
        cap.read(img);
    }
    bool is_success = cap.read(img);
    if (is_success == true)
    {
        std::cout << "[INFO] Draw rectangle !!!\n";
        draw_rectangle();
    }
    else
    {
        std::cout << "[ERROR] Error opening video stream or camera \n";
        cap.release();
        destroyAllWindows();
        return;
    }
    /* Taking an everlasting loop to show the video */     
    while (!exitClicked)
    {
        cap >> frame;
        /* Breaking the loop if no video frame is detected */
        if (frame.empty())
        {
            std::cout << "[INFO] Video ended or corrupted frame !\n";
            return;
        }
        cv::resize(frame, frame, cv::Size(FRAME_IN_W,FRAME_IN_H), cv::INTER_LINEAR);
        cout<< boxes[0] <<endl;
        cout << "reach\n";
        frames = frame(boxes[0]);
        out = run_inference(frames);
        classification(out);
        std::string stips2 = std::to_string(duration);
        int64_t FPS = 1000/duration;
        std::cout<<"\nFPS: "<<FPS<<endl;
        cv::putText(frame, "FPS: "+std::to_string(FPS), cv::Point(FRAME_IN_W-100, 20), cv::FONT_HERSHEY_SIMPLEX, 0.7, BLUE, 2);        
        cv::rectangle(frame, boxes[0], BLUE, 2);
        putText(frame,"Double Click to exit the Application!!", Point((int)(FRAME_IN_W/2 - FRAME_IN_W/10) + 50, (int)(FRAME_IN_H) -20), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLUE, 1, LINE_AA);
        cv::imshow("output", frame);
        cv::setMouseCallback("output", buttonCallBack);
        waitKey(1);
    }
    cap.release();/* Releasing the buffer memory */
    destroyAllWindows();
    return;
}

/*****************************************
 * Function Name : input_source_select
 * Description   : function to select input source
 * Return value  : 0  = Input source selected
 *                 -1 = Error selecting inputh source
 ******************************************/
int input_source_select(void)
{
     /* Get input Source VIDEO/CAMERA */
    switch (input_source_map[input_source])
    {
    /* Input Source : Video */
    case 1:
        {
            std::cout << "[INFO] Video \n";
            gstreamer_pipeline = "filesrc location=" + input_file + " ! decodebin ! videoconvert ! appsink";
        }
        break;
    /* Input Source : MIPI Camera */
    case 2:
        {
            std::cout << "[INFO] MIPI CAMERA \n";
            std::string media_port = query_device_status("CRU");
            if (media_port == "")
            {
                fprintf(stderr, "[ERROR] MIPI Camera not connected. \n");
                return -1;
            }
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
            /* MIPI Camera Setup */
            mipi_cam_init();
        }
        break;
    /* Input Source : USB Camera */
    case 3:
        {
            std::cout << "[INFO] USB CAMERA \n";
            std::string media_port = query_device_status("usb");
            if (media_port == "")
            {
                fprintf(stderr, "[ERROR] USB Camera not connected. \n");
                return -1;
            }
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
        }
        break;
    /* Input Source : Image */
    case 4:
        {
            std::cout << "[INFO] Image \n";
            /* read input image */
            frame = cv::imread(input_file);
        }
        break;
    default:
        {
            std::cout << "[ERROR] Please specify Input Source" << std::endl;
            std::cout << "[INFO] Usage : ./plant_leaf_disease_classify MIPI|USB|VIDEO|IMAGE [Input_file for VIDEO|IMAGE]" << std::endl;
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{

    if (argc < 2 || argc > 3) 
    {
        std::cout << "[ERROR] Please specify Input Source" << std::endl;
        std::cout << "[INFO] Usage : ./plant_leaf_disease_classify MIPI|USB|VIDEO|IMAGE [Input_file for VIDEO|IMAGE]" << std::endl;
        std::cout << "\n[INFO] End Application\n";
        return -1;
    }

    input_source = argv[1];

    if (input_source != "VIDEO" && input_source != "IMAGE" && argc == 3) 
    {
        std::cout << "[ERROR] Please specify Input Source" << std::endl;
        std::cout << "[INFO] Usage : ./plant_leaf_disease_classify MIPI|USB|VIDEO|IMAGE [Input_file for VIDEO|IMAGE]" << std::endl;
        std::cout << "\n[INFO] End Application\n";
        return -1;
    }
    
    if ((input_source == "VIDEO" || input_source == "IMAGE")) 
    {
        if(argc == 2)
        {
            std::cout << "[ERROR] Please specify Input Source" << std::endl;
            std::cout << "[INFO] Usage : ./plant_leaf_disease_classify MIPI|USB|VIDEO|IMAGE [Input_file for VIDEO|IMAGE]" << std::endl;
            std::cout << "\n[INFO] End Application\n";
            return -1;
        }
        input_file = argv[2];
    }

    /*Select input Source MIPI/USB/IMAGE/VIDEO*/
    if(input_source_select() == -1)
    {
        std::cout << "\n[INFO] End Application\n";
        return -1;
    }

    /* Model Binary */
    std::string model_dir = "plant_dis_onnx";
    /*  class list file */
    std::string plant_class_list = "plant_leaf_disease_class.txt";
    /* Load fish class list */
    class_names = load_label_file(plant_class_list);
    if (class_names.empty())
    {
        std::cerr << "[ERROR] failed to load fish class list: " << plant_class_list << std::endl;
        return 0;
    }
    
    uint64_t drpaimem_addr_start = 0;
    bool runtime_status = false;
    /*Load model_dir structure and its weight to runtime object */
    drpaimem_addr_start = get_drpai_start_addr();
    if ((uint64_t)NULL == drpaimem_addr_start) 
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address.\n");
        /*Error processing, i.e., return, goto, etc.*/
        return -1;
    }
    runtime_status = runtime.LoadModel(model_dir, drpaimem_addr_start+DRPAI_MEM_OFFSET);
    if(!runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load model.\n");
        /*Error processing, i.e., return, goto, etc.*/
        return -1;
    }
    cout << "loaded model :" << model_dir << "\n\n";

    if(input_source == "IMAGE")
    {
        out = run_inference(frame);
        classification(out);
        cv::imshow("output", frame);
        cv::waitKey(3000);
    } 
    else
    {
        /* Open camera and capture frame*/
        capture_frame(gstreamer_pipeline);
    }
    std::cout<< "\n[INFO] Application End \n";
    return 0;
}
