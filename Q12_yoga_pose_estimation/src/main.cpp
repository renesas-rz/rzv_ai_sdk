/*
 * Original Code (C) Copyright Edgecortix, Inc. 2022
 * Modified Code (C) Copyright Renesas Electronics Corporation 2024
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
 *****************************************/
#include <fstream>
#include <string>
#include <sys/time.h>
#include <vector>
#include "MeraDrpRuntimeWrapper.h"
#include "iostream"
#include "opencv2/opencv.hpp"
#include "wayland.h"
#include "define.h"
#include <thread>

/* DRP-AI TVM[*1] Runtime object */
MeraDrpRuntimeWrapper keypoint_runtime;
MeraDrpRuntimeWrapper pose_classifier_runtime;

/* flags to detect image mode*/
bool g_image_mode         = false;
/* flag for detecting window exit*/
bool exitClick          = false;

/* variables to calculate total fps and inference time */
int g_duration;
int g_fps;
uint32_t g_out_size_arr;

std::vector<float> floatarr(1);

cv::Mat g_frame;
cv::Mat g_fn_frame;
cv::VideoCapture g_cap;

int img_height;
int img_width;

static Wayland wayland;

/* Map to store label list */
std::map<int, std::string> label_file_map;

/* Map to store input source list */
std::map<std::string, int> input_source_map =
{
    {"VIDEO", 1},
    {"IMAGE", 2},
    {"USB", 3}
};

// keypoint connections
std::vector<std::pair<int, int>> skeleton = {
    {15, 13}, {13, 11}, {16, 14}, {14, 12}, {11, 12},
    {5, 11}, {6, 12}, {5, 6}, {5, 7}, {6, 8}, {7, 9},
    {8, 10}, {1, 2}, {0, 1}, {0, 2}, {1, 3}, {2, 4},
    {3, 5}, {4, 6}
};

/* variables to calculate inference time */
static float keypoint_pre_time   = 0;
static float keypoint_post_time  = 0;
static float keypoint_ai_time    = 0;
static float classifier_pre_time   = 0;
static float classifier_post_time  = 0;
static float classifier_ai_time    = 0;
static float total_ai_time    = 0;


static struct timespec keypoint_inf_start_time;
static struct timespec keypoint_inf_end_time;
static struct timespec keypoint_pre_start_time;
static struct timespec keypoint_pre_end_time;
static struct timespec keypoint_post_start_time;
static struct timespec keypoint_post_end_time;
static struct timespec classifier_inf_start_time;
static struct timespec classifier_inf_end_time;
static struct timespec classifier_pre_start_time;
static struct timespec classifier_pre_end_time;
static struct timespec classifier_post_start_time;
static struct timespec classifier_post_end_time;

/*coordinates for total ai time*/
cv::Point total_time_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 60);
/*coordinates for keypoint heading*/
cv::Point keypoint_head_position(DISP_IMAGE_OUTPUT_WIDTH + 10, 100);
/*coordinates for keypoint pre-process time*/
cv::Point key_pre_process_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 130);
/*coordinates for keypoint inference time*/
cv::Point key_ai_inf_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 160);
/*coordinates for keypoint post-process time*/
cv::Point key_post_process_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 190);
/*coordinates for pose classifier heading*/
cv::Point pose_classifier_head_position(DISP_IMAGE_OUTPUT_WIDTH + 10, 240);
/*coordinates for pose classifier pre-process time*/
cv::Point pose_pre_process_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 270);
/*coordinates for pose classifier inference time*/
cv::Point pose_ai_inf_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 300);
/*coordinates for pose classifier post-process time*/
cv::Point pose_post_process_postion(DISP_IMAGE_OUTPUT_WIDTH + 10, 330);

/*DRP-AI Frequency setting*/
static int32_t drpai_freq;
static float font_scale = 1.15;
static float font_thickness = 2;

/*****************************************
* Function Name : get_drpai_start_addr
* Description   : Get DRP-AI Memory Area Address via DRP-AI Driver
* Arguments     : int drpai_fd
* Return value  : drpai start address 
******************************************/
uint64_t get_drpai_start_addr(int drpai_fd)
{
    int ret = 0;
    drpai_data_t drpai_data;
    errno = 0;
    /* Get DRP-AI Memory Area Address via DRP-AI Driver */
    ret = ioctl(drpai_fd , DRPAI_GET_DRPAI_AREA, &drpai_data);
    if (-1 == ret)
    {
        std::cerr << "[ERROR] Failed to get DRP-AI Memory Area : errno=" << errno;
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
uint64_t init_drpai(int drpai_fd)
{
    int ret = 0;
    uint64_t drpai_addr = 0;
    /*Get DRP-AI memory start address*/
    drpai_addr = get_drpai_start_addr(drpai_fd);

    if (drpai_addr == 0)
    {
        return 0;
    }

    return drpai_addr;
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
 * Return value     : cv::Mat background, final display frame to be written to g-streamer pipeline
 *****************************************/
cv::Mat create_output_frame(cv::Mat frame_g)
{
    /* Create a black background image of size 1080x720 */
    cv::Mat background(DISP_OUTPUT_HEIGHT, DISP_OUTPUT_WIDTH, frame_g.type(), cv::Scalar(0, 0, 0));
    /* Resize the original image to fit within 960x720 */
    cv::Mat resizedImage;
    cv::resize(frame_g, resizedImage, cv::Size(DISP_IMAGE_OUTPUT_WIDTH, DISP_IMAGE_OUTPUT_HEIGHT));
    /* Copy the resized image to the left side of the background (0 to 960) */
    cv::Rect roi(cv::Rect(0, 0, resizedImage.cols, resizedImage.rows));
    resizedImage.copyTo(background(roi));
    return background;
}

/*****************************************
 * Function Name     : start_preprocessing
 * Description       : Function to perform the pre processing.
 * Arguments         : cv::Mat input_frame = frame input address
 * Return value      : cv::Mat frame_nn = pre-processed mat frame output
 ******************************************/
cv::Mat start_preprocessing(cv::Mat input_frame)
{
    img_height = input_frame.rows;
    img_width = input_frame.cols;

    cv::Mat input_img;
    cv::cvtColor(input_frame, input_img, cv::COLOR_BGR2RGB);

    int input_width = MODEL_IN_W;
    int input_height = MODEL_IN_H;

    cv::resize(input_img, input_img, cv::Size(input_width, input_height));

    input_img.convertTo(input_img, CV_32FC3);

    cv::Scalar img_std(0.229f, 0.224f, 0.225f);

    float img_scale = 1.0f / 255.0f;
    input_img *= img_scale;

    cv::Scalar img_mean(0.485, 0.456, 0.406);
    input_img -= img_mean;

    input_img /= img_std;

    cv::Mat frame_nn(1, 3 * input_img.rows * input_img.cols, CV_32F);
    int index = 0;
    for (int c = 0; c < 3; ++c) {
        for (int h = 0; h < input_img.rows; ++h) {
            for (int w = 0; w < input_img.cols; ++w) {
                frame_nn.at<float>(0, index++) = input_img.at<cv::Vec3f>(h, w)[c];
            }
        }
    }

    std::vector<int> dims = {1, 3, input_img.rows, input_img.cols};
    frame_nn = frame_nn.reshape(1, dims);
    return frame_nn;

}

/*****************************************
 * Function Name : extract_keypoints
 * Description   : process the heatmaps to extract keypoints
 * Arguments     : heatmaps_data = heatmap array
 * Return value  : keypoints = extracted keypoints
 ******************************************/
std::vector<cv::Point2f> extract_keypoints(float* heatmaps_data)
{   
    int batch_size = 1;
    int num_heatmaps = 17;
    int map_h = 64;
    int map_w = 48;

    cv::Mat heatmaps(batch_size, num_heatmaps * map_h * map_w, CV_32F, heatmaps_data);
    heatmaps = heatmaps.reshape(1, {batch_size, num_heatmaps, map_h, map_w});

    cv::Mat flattened_heatmaps = heatmaps.reshape(1, {batch_size * num_heatmaps, map_h * map_w});

    cv::Mat summed_heatmaps;
    cv::reduce(flattened_heatmaps, summed_heatmaps, 0, cv::REDUCE_SUM, CV_32FC3);

    summed_heatmaps = summed_heatmaps.reshape(1, {map_h, map_w});

    cv::Mat resized_heatmap;
    cv::resize(summed_heatmaps, resized_heatmap, cv::Size(img_width, img_height),cv::INTER_LINEAR);

    float conf_threshold = 0.5f;

    float scale_x = static_cast<float>(img_width) / map_w;
    float scale_y = static_cast<float>(img_height) / map_h;


    std::vector<float> max_vals(num_heatmaps);
    std::vector<cv::Point2f> keypoints(num_heatmaps, cv::Point2f(std::nanf(""), std::nanf("")));

    //obtain keypoints from peak heatmap values
    for (int i = 0; i < num_heatmaps; ++i) {
        float* heatmap_ptr = heatmaps_data + i * map_h * map_w;
        cv::Mat heatmap(map_h, map_w, CV_32F, heatmap_ptr);

        double minVal, maxVal;
        cv::Point maxLoc;
        cv::minMaxLoc(heatmap, &minVal, &maxVal, nullptr, &maxLoc);

        max_vals[i] = static_cast<float>(maxVal);

        if (max_vals[i] >= conf_threshold) {
            keypoints[i] = cv::Point2f(maxLoc.x * scale_x, maxLoc.y * scale_y);
        }
    }

    return keypoints;

}

/*****************************************
 * Function Name     : validPoint
 * Description       : Function to check wether a given kepoint is valid or not.
 * Arguments         : point = a keypoint tuple with x & y coordinates.
 * Return value      : a boolean value indicating wether the point is valid.
 ******************************************/
bool validPoint(const cv::Point2f& point) {
    return point.x >= 0 && point.y >= 0;
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
 * Function Name     : float_to_string
 * Description       : Convert float to string with precision
 * Arguments         : number = float number to be converted
 *                     precision = int number to set precision
 * Return value      : string = string number
 ******************************************/
std::string float_to_string(float number, int precision = 2)
{
    std::stringstream stream;  
    stream.precision(precision);
    stream << std::fixed << number;  
    return stream.str();
}

/*****************************************
 * Function Name     : draw_skelton
 * Description       : Function to draw the skeltons over detected keypoints on the image.
 * Arguments         : keypoints = keypoints extracted from heatmaps
 *                     bgra_image = image to be drawn on
 *                     invalid_counts = count of missed points
 * Return value      : bgra_image = image with drawn keypoints
 ******************************************/
cv::Mat draw_skelton(std::vector<cv::Point2f> keypoints, cv::Mat bgra_image,int& invalid_counts)
{
    

    float scale = 1.0f / 150.0f;
    int thickness = std::min(static_cast<int>(bgra_image.rows * scale), static_cast<int>(bgra_image.cols * scale));


    for (size_t i = 0; i < skeleton.size(); ++i) {
        int point1_id = skeleton[i].first;
        int point2_id = skeleton[i].second;

        cv::Point2f point1 = keypoints[point1_id];
        cv::Point2f point2 = keypoints[point2_id];

        if (validPoint(point1)) {
            cv::circle(bgra_image, cv::Point(static_cast<int>(point1.x), static_cast<int>(point1.y)),
                       static_cast<int>(thickness * 1.5), GREEN, -1, cv::LINE_AA);
        }
        else {
            invalid_counts++;
        }

        if (validPoint(point2)) {
            cv::circle(bgra_image, cv::Point(static_cast<int>(point2.x), static_cast<int>(point2.y)),
                       static_cast<int>(thickness * 1.5), GREEN, -1, cv::LINE_AA);
        }
        else {
            invalid_counts++;
        }

        if (!validPoint(point1) || !validPoint(point2)) {
            continue;
        }

        cv::line(bgra_image, cv::Point(static_cast<int>(point1.x), static_cast<int>(point1.y)),
                 cv::Point(static_cast<int>(point2.x), static_cast<int>(point2.y)),
                 YELLOW, thickness, cv::LINE_AA);
    }

    return bgra_image;
}

/*****************************************
 * Function Name     : start_runtime
 * Description       : Function to perform the pre processing and post processing.
 * Arguments         : model_runtime runtime chosen for inference
                     : *input = frame input address
 * Return value      : *float floatarr = pre-processed and post-processed output
 ******************************************/
float *start_runtime(MeraDrpRuntimeWrapper model_runtime, float *input)
{
    /*Set Pre-processing output to be inference input. */
    model_runtime.SetInput(0, input);

    model_runtime.Run(drpai_freq);

    /* Get the number of output.  */
    auto output_num = model_runtime.GetNumOutput();
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

std::tuple<int, int, int, int> generate_bbox(std::vector<cv::Point2f>& keypoints) {
    
    float xmin = std::numeric_limits<float>::max();
    float ymin = std::numeric_limits<float>::max();
    float xmax = std::numeric_limits<float>::lowest();
    float ymax = std::numeric_limits<float>::lowest();

    for (const auto& keypoint : keypoints) {
        float x = keypoint.x;
        float y = keypoint.y;

        // Check if keypoint coords is not null
        if (!std::isnan(x) && !std::isnan(y)) {
            xmin = std::min(xmin, x);
            ymin = std::min(ymin, y);
            xmax = std::max(xmax, x);
            ymax = std::max(ymax, y);
        }
    }

    return std::make_tuple(static_cast<int>(xmin), static_cast<int>(ymin),
                           static_cast<int>(xmax), static_cast<int>(ymax));
}

/*****************************************
* Function Name : softmax
* Description   : Function for Post Processing
* Arguments     : val[] = array to be computed Softmax
*                 size = size of array
* Return value  : -
******************************************/
void softmax(float *val, int32_t size)
{
    float max_num = -INT_MAX;
    float sum = 0;
    int32_t i;
    for (i = 0; i < size; i++)
    {
        max_num = std::max(max_num, val[i]);
    }

    for (i = 0; i < size; i++)
    {
        val[i] = (float)exp(val[i] - max_num);
        sum += val[i];
    }

    for (i = 0; i < size; i++)
    {
        val[i] = val[i] / sum;
    }
    return;
}


/*****************************************
 * Function Name : run_inference
 * Description   : takes Mat frame as the input and passes through the model runtime and returns the output
 * Arguments     : Mat frame
 * Return value  : Mat frame
 ******************************************/
cv::Mat run_inference(cv::Mat frame)
{   
    float *heatmaps;
    float *pose_pred;
    bool have_valid_pose = false;
    /*font size to be used for text output*/
    float font_size = .9;
    float font_weight = 2;
    float min_threshold = 0.3;
    
    std::map<float, int> pose_result;
    int result_cnt = 0;

    int ret = 0;


    cv::Mat output_frame;
    output_frame = frame.clone();
    /* get keypoint pre-processing start time */
    ret = timespec_get(&keypoint_pre_start_time, TIME_UTC);
    if (0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get keypoint Pre-process Start Time\n");
    }

    /* start pre-processing */
    frame = start_preprocessing(frame);
    /* get keypoint pre-processing end time */
    ret = timespec_get(&keypoint_pre_end_time, TIME_UTC);
    if ( 0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to Get keypoint Pre-process End Time\n");
    }

    /*Keypoint pre-process Time*/
    keypoint_pre_time = (float)((timedifference_msec(keypoint_pre_start_time, keypoint_pre_end_time)));

    /* get keypoint inference start time */
    ret = timespec_get(&keypoint_inf_start_time, TIME_UTC);
    if (0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get keypoint inference Start Time\n");
    }
    /*start inference using drp runtime*/
    heatmaps = start_runtime(keypoint_runtime, frame.ptr<float>());
    /* get keypoint inference end time */
    ret = timespec_get(&keypoint_inf_end_time, TIME_UTC);
    if (0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get keypoint inference End Time\n");
    }

    /*Keypoint pre-process Time Result*/
    keypoint_ai_time = (float)((timedifference_msec(keypoint_inf_start_time, keypoint_inf_end_time)));

    /* Post-processing part for keypoint*/
    /* get keypoint post-process start time */
    ret = timespec_get(&keypoint_post_start_time, TIME_UTC);
    if (0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get keypoint Post-process Start Time\n");
    }
    std::vector<cv::Point2f> keypoints = extract_keypoints(heatmaps);
    // Get the bounding box from keypoints
    auto [xmin, ymin, xmax, ymax] = generate_bbox(keypoints);
    /* get keypoint post-process end time */
    ret = timespec_get(&keypoint_post_end_time, TIME_UTC);
    if (0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get keypoint Post-process End Time\n");
    }
    keypoint_post_time = (float)((timedifference_msec(keypoint_post_start_time, keypoint_post_end_time)));

    /* get pose classifier pre-processing start time */
    ret = timespec_get(&classifier_pre_start_time, TIME_UTC);
    if (0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get Pose classifier Pre-process Start Time\n");
    }
    /* start pose classifier pre-processing */
    std::vector<float> pose_input;
    
    for (int i = 5; i < keypoints.size(); ++i) {
  
    if (std::isnan(keypoints[i].x) || std::isnan(keypoints[i].y)) {
            pose_input.push_back(0);
            pose_input.push_back(0);
            continue;
    }

    pose_input.push_back(keypoints[i].x / img_width);
    pose_input.push_back(keypoints[i].y / img_height);
    
    }
    /* get pose classifier pre-processing end time */
    ret = timespec_get(&classifier_pre_end_time, TIME_UTC);
    if (0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get Pose classifier Pre-process End Time\n");
    }
    classifier_pre_time = (float)((timedifference_msec(classifier_pre_start_time, classifier_pre_end_time)));


    /* get pose classifier inference start time */
    ret = timespec_get(&classifier_inf_start_time, TIME_UTC);
    if (0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get Pose classifier Inference Start Time\n");
    }
    /*start inference using drp runtime*/
    pose_pred = start_runtime(pose_classifier_runtime, pose_input.data());
    /* get pose classifier inference end time */
    ret = timespec_get(&classifier_inf_end_time, TIME_UTC);
    if (0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get Pose classifier Inference End Time\n");
    }
    classifier_ai_time = (float)((timedifference_msec(classifier_inf_start_time, classifier_inf_end_time)));
    
    /* Post-processing part for pose classifier*/
    /* get pose classifier post-processing start time */
    ret = timespec_get(&classifier_post_start_time, TIME_UTC);
    if (0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get Pose classifier Post-process Start Time\n");
    }
     /* Softmax 1000 class scores. */
    softmax(&pose_pred[0], 5);

     for (int n = 0; n < 5; n++)
    {
        pose_result[pose_pred[n]] = n;
    }
    /* get pose classifier post-processing end time */
    ret = timespec_get(&classifier_post_end_time, TIME_UTC);
    if (0 == ret)
    {
        fprintf(stderr, "[ERROR] Failed to get Pose classifier Post-process End Time\n");
    }
    classifier_post_time = (float)((timedifference_msec(classifier_post_start_time, classifier_post_end_time)));

    /*get all time calculations*/
    std::cout << "\n[INFO] keypoint detection pre-process Time(ms) : " << float_to_string(keypoint_pre_time) <<" ms \n";
    std::cout << "\n[INFO] Keypoint detection Inference Time(ms)   : " << float_to_string(keypoint_ai_time) << " ms\n";
    std::cout << "\n[INFO] keypoint detection post-process Time(ms): " << float_to_string(keypoint_post_time) <<" ms \n";
    std::cout << "\n[INFO] Pose classifier pre-process Time(ms)    : " << float_to_string(classifier_pre_time) <<" ms \n";
    std::cout << "\n[INFO] Pose classifier Inference Time(ms)      : " << float_to_string(classifier_ai_time) << " ms\n";
    std::cout << "\n[INFO] Pose classifier post-process Time(ms)   : " << float_to_string(classifier_post_time) <<" ms \n";

    total_ai_time = keypoint_pre_time + keypoint_ai_time + keypoint_post_time + classifier_ai_time + classifier_pre_time + classifier_post_time;
    g_fps = 1000/total_ai_time;
    std::cout<<"[INFO] FPS: "<<g_fps<<"\n";
    

    float bbox_offsetter = std::abs(keypoints[skeleton[4].first].x - keypoints[skeleton[4].second].x);
    int offset = static_cast<int>(bbox_offsetter / 1.5);

    int invalid_point_counts = 0;

    output_frame = draw_skelton(keypoints, output_frame,invalid_point_counts);

    have_valid_pose = (xmin > -1 && ymin > -1 && xmax > -1 && ymax > -1 && offset > -1) && invalid_point_counts < 15;

    // Check if the bounding box is valid (not -1)
    if (have_valid_pose) {
        cv::rectangle(output_frame,
                      cv::Point(xmin - offset, ymin - offset),
                      cv::Point(xmax + offset, ymax + offset),
                      GREEN, 2);
        // Text to display
        std::map<float, int>::reverse_iterator it = pose_result.rbegin();
        // Access the key and value of the element with the highest key
        float highest_score = it->first;
        int value = it->second;
        const std::string text = label_file_map[value];

        int baseline = 0;
        cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.4, 1, &baseline);

        int text_x = xmin - offset;
        int text_y = ymin - offset;

        cv::rectangle(output_frame, 
                      cv::Point(text_x, text_y - textSize.height), 
                      cv::Point(text_x + textSize.width, text_y), 
                      GREEN, -1);

        cv::putText(output_frame, text, cv::Point(text_x, text_y), 
                    cv::FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1);

    } else {
        std::cout << "No valid bounding box found." << std::endl;
    }

    output_frame = create_output_frame(output_frame);

    /*put inference time inside the display frame*/
    cv::putText(output_frame, "Total AI Time (ms): " + float_to_string(total_ai_time), total_time_postion, 
                cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);

    cv::putText(output_frame,"Keypoint Detection:", keypoint_head_position, 
                cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_thickness);
    cv::putText(output_frame, "Preprocess  : " + float_to_string(keypoint_pre_time), key_pre_process_postion, 
                cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
    cv::putText(output_frame, "Inference    : " + float_to_string(keypoint_ai_time), key_ai_inf_postion, 
                    cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
    cv::putText(output_frame, "Postprocess : " + float_to_string(keypoint_post_time), key_post_process_postion, 
                    cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
    
    cv::putText(output_frame,"Pose Classifier:", pose_classifier_head_position, 
                cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_thickness);
    cv::putText(output_frame, "Preprocess  : " + float_to_string(classifier_pre_time), pose_pre_process_postion, 
                cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
    cv::putText(output_frame, "Inference    : " + float_to_string(classifier_ai_time), pose_ai_inf_postion, 
                    cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
    cv::putText(output_frame, "Postprocess : " + float_to_string(classifier_post_time), pose_post_process_postion, 
                    cv::FONT_HERSHEY_SIMPLEX, font_size, WHITE, font_weight);
    
    if (have_valid_pose) {

        result_cnt = 0;
        /* Print Top-5 results. */
        std::cout << "Result ----------------------- " << std::endl;
        
        int y0 = DISP_IMAGE_OUTPUT_HEIGHT/2 + 200;
        int dy = 40;
        int y = 0;
        for (auto it = pose_result.rbegin(); it != pose_result.rend(); it++) {
            result_cnt++;
            y = y0+result_cnt*dy;
            if (result_cnt > 5)
                break;
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << (float)(*it).first * 100;
            std::string formattedNumber = oss.str();

            std::cout << "  Top " << result_cnt << " ["
                    << std::right << std::setw(5) << std::fixed << std::setprecision(1) << (float)(*it).first * 100
                    << "%] : [" << label_file_map[(*it).second] << "]" << std::endl;
            cv::putText(output_frame,"Top Results:",cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 10, (DISP_IMAGE_OUTPUT_HEIGHT/2) + 100), cv::FONT_HERSHEY_SIMPLEX, font_scale - 0.1, WHITE, font_thickness);
            cv::putText(output_frame,"Top "+std::to_string(result_cnt)+" ["+formattedNumber+"%] : ["+label_file_map[(*it).second]+"]",
                    cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 10,y - 100), cv::FONT_HERSHEY_SIMPLEX, font_scale - 0.3, WHITE, font_thickness);

        }

    }
    else {

        cv::putText(output_frame,"No valid pose detected!!!",cv::Point(DISP_IMAGE_OUTPUT_WIDTH + 10, (DISP_IMAGE_OUTPUT_HEIGHT/2) - 100), cv::FONT_HERSHEY_SIMPLEX, font_scale - 0.1, RED, font_thickness);
        std::cout << "NO VALID POSE DETECTED !!!"<<std::endl;
    }
    return output_frame;
}

/******************************************
 * Function Name : capture_frame
 * Description   : function to open camera or video source with respect to the source pipeline.
 * Arguments     : string cap_pipeline input source pipeline
 ******************************************/
void capture_frame(std::string cap_pipeline,std::string input_source)
{
    /* Capture stream of frames from camera using G-streamer pipeline */
    g_cap.open(cap_pipeline, cv::CAP_GSTREAMER);
    if (!g_cap.isOpened())
    {
        /* This section prompt an error message if no video stream is found */
        std::cout << "[ERROR] Error opening "<< input_source <<" source!!\n"
                  << std::endl;
        return;
    }
    /* Taking an everlasting loop to show the output */
    while (!exitClick)
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
            cv::cvtColor(g_fn_frame, g_fn_frame, cv::COLOR_BGR2BGRA);
            /* check for image mode*/
            if(g_image_mode == true)
                return;
            wayland.commit(g_fn_frame.data, NULL);
        }
    }
    return;
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
 * Function Name : keyboard_exit
 * Description   : function to exit on Enter Key press
 * Return value  : -
 ******************************************/
void keyboard_exit()
{
    std::cout << "\n[INFO] Keyboard Exit Thread Started\n";
    int32_t key = 0;
    while(true)
    {
        key = getchar();
        if (key == 10 || exitClick == true)
        {
            /* When key is pressed. */
            printf("[INFO] Enter key Detected.\n");
            exitClick = true;
            break;
        }
    }
    std::cout << "[INFO] Keyboard Exit Thread Finished" << std::endl;
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
 * Function Name : print_usage_info
 * Description   : function to print usage info.
 ******************************************/
void print_usage_info()
{
    std::cout << "[INFO] usage: ./keypoint_detector USB|VIDEO|IMAGE [Input_file for VIDEO/IMAGE]" << std::endl;
}

int main(int argc, char **argv)
{
    bool keypoint_runtime_status = false;
    bool pose_classifier_runtime_status = false;
    uint64_t drpaimem_addr_start = 0;
    bool errorHandle = false;
    std::string input_source;

    /*Disable OpenCV Accelerator due to the use of multithreading */
    unsigned long OCA_list[16];
    for(int i = 0; i < 16; i++) OCA_list[i] = 0;
    OCA_Activate(&OCA_list[0]);

    /* G-streamer input pipeline*/
    std::string gstreamer_pipeline;

    label_file_map = load_label_file(labels);
    if (label_file_map.empty())
    {
        std::cerr << "[ERROR] Label file : failed to load " << labels << std::endl;
        return 0;
    }


    /* Check the input source is valid.*/
    if (argc < 2)
    {
        errorHandle = true;
    }
    else
    {
        input_source = argv[1];
        if ((input_source == "USB") && argc >= 2)
            errorHandle = false;
        else if((input_source == "IMAGE"|| input_source == "VIDEO") && argc >= 3)
            errorHandle = false;
        else
            errorHandle = true;
    }
    if (errorHandle)
    {
        std::cout << "\n[ERROR] Please specify proper argument/Input Source" << std::endl;
        print_usage_info();
        std::cout << "\n[INFO] End Application\n";
        return -1;
    }

    
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
        /* AI Application for RZ/V2H */
        printf("\nAI Application for RZ/V2H\n");

    errno = 0;
    int drpai_fd = open("/dev/drpai0", O_RDWR);
    if (0 > drpai_fd)
    {
        std::cerr << "[ERROR] Failed to open DRP-AI Driver : errno=" << errno << std::endl;
        return -1;
    }

    /* Initialize DRP-AI (Get DRP-AI memory address and set DRP-AI frequency)*/
    drpaimem_addr_start = init_drpai(drpai_fd);
    if (drpaimem_addr_start == 0) 
    {
        fprintf(stderr, "[ERROR] Failed to get DRP-AI memory area start address.\n");
        close(drpai_fd);
	    return -1;
    }
    /* Initialize wayland */
    int8_t ret = 0;
    ret = wayland.init(0, DISP_OUTPUT_WIDTH, DISP_OUTPUT_HEIGHT, IMAGE_CHANNEL_BGRA);
    if(0 != ret)
    {
        fprintf(stderr, "[ERROR] Failed to initialize Image for Wayland\n");
        return -1;
    }

    std::thread keyboard_exit_thread(keyboard_exit);
    keyboard_exit_thread.detach();

    /* Get input Source WS/VIDEO/CAMERA */
    switch (input_source_map[input_source])
    {
        /* Input Source : Video */
        case 1:
        {
            std::cout << "[INFO] Video \n";
            /* read input video */
            std::string video_path = argv[2];
            /* g-streamer pipeline to read input video source */
            gstreamer_pipeline = "filesrc location=" + video_path + " ! decodebin ! videoconvert ! appsink";
        }
        break;
        /* Input Source : Image */
        case 2:
        {
            std::cout << "[INFO] Image \n";
            g_image_mode = true;
            /* read input image */
            std::string image_path = argv[2];
            // Extract the file extension
            size_t dotPos = image_path.find_last_of('.');
            std::string extension = image_path.substr(dotPos + 1);
            if (dotPos != std::string::npos && (extension == "jpg" || extension == "JPG" || extension == "jpeg" || extension == "JPEG")) 
            {
                gstreamer_pipeline = "filesrc location=" + image_path + " ! jpegdec ! videoconvert ! videoscale ! video/x-raw, width=640, height=480 ! appsink";
            }
            else if (dotPos != std::string::npos && (extension =="png"|| extension =="PNG"))
            {
                gstreamer_pipeline = "filesrc location=" + image_path + " ! pngdec ! videoconvert ! videoscale ! video/x-raw, width=640, height=480 ! appsink";
            }
            else
            {
                std::cout << "\n[ERROR] Please specify proper argument/Input Source" << std::endl;
                print_usage_info();
                std::cout << "[INFO] End Application.\n";
                return -1;
            }
            
        }
        break;
        /* Input Source : USB Camera */
        case 3:
        {
            std::cout << "[INFO] USB CAMERA \n";
            /* check the status of device */
            std::string media_port = query_device_status("usb");
            /* g-streamer pipeline to read input image source */
            gstreamer_pipeline = "v4l2src device=" + media_port + " ! videoconvert ! appsink";
        }
        break;
        /* default case */
        default:
        {
            std::cout << "[ERROR] Invalid Input source\n";
            std::cout << "\n[ERROR] Please specify Input Source" << std::endl;
            print_usage_info();
            std::cout << "\n[INFO] End Application\n";
            
            return -1;
        }
    }
    
    keypoint_runtime_status = keypoint_runtime.LoadModel(keypoint_model_dir, drpaimem_addr_start+DRPAI_MEM_OFFSET);
    if(!keypoint_runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load Keypoint model.\n");
	    close(drpai_fd);
        return -1;
    }
    std::cout << "[INFO] loaded Keypoint runtime model :" << keypoint_model_dir << "\n\n";

    pose_classifier_runtime_status = pose_classifier_runtime.LoadModel(pose_classifier_model_dir, drpaimem_addr_start);
    if(!pose_classifier_runtime_status)
    {
        fprintf(stderr, "[ERROR] Failed to load Pose Classifier model.\n");
	    close(drpai_fd);
        return -1;
    }
    std::cout << "[INFO] loaded Pose Classifier runtime model :" << pose_classifier_model_dir << "\n\n";


    capture_frame(gstreamer_pipeline,input_source);
    if(g_image_mode){
         while(exitClick == false)
        {
            wayland.commit(g_fn_frame.data, NULL);
        }
    }
    
    wayland.exit();
    /*Close DRP-AI Driver.*/
    if (0 < drpai_fd)
    {
        errno = 0;
        ret = close(drpai_fd);
        if (0 != ret)
        {
            fprintf(stderr, "[ERROR] Failed to close DRP-AI Driver: errno=%d\n",errno);
        }
    }
    std::cout << "[INFO] Application End\n";
    return 0;

}