/*
 * Original Code (C) Copyright Edgecortix, Inc. 2022
 * Modified Code (C) Copyright Renesas Electronics Corporation 2023
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
 * Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : recognize_base.h
 * Version      : 1.0
 * Description  : RZ/V2L SDK AI Application: Suspicious person detection.
 ***********************************************************************************************************************/

#pragma once
#ifndef RECOGNIZE_BASE_H
#define RECOGNIZE_BASE_H

/*****************************************
 * Includes
 ******************************************/
#include <condition_variable>
#include <mutex>
#include <queue>
#include "../includes.h"
#include "../camera/camera.h"
#include "../util/system_analyzer.h"
#include "../util/recognize_define.h"
#include "../util/box.h"
#include "../util/MeraDrpRuntimeWrapper.h"
#include "irecognize_model.h"
#include "recognize_data.h"
#include "../command/object_detection.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <set>

#define WAIT_TIME                   (1000) /* microseconds */
/*Timer Related*/
/* seconds */
#define CAPTURE_TIMEOUT             (20)          
/* seconds */
#define AI_THREAD_TIMEOUT           (20)        
/* seconds */
#define FRAMERATE_THREAD_TIMEOUT    (20) 
/*Total Display out*/
#define DISP_OUTPUT_WIDTH           (1280)
#define DISP_OUTPUT_HEIGHT          (720)
/*Image display out*/
#define IMAGE_OUTPUT_WIDTH          (960)
#define IMAGE_OUTPUT_HEIGHT         (720)

#define GREEN                       cv::Scalar(0, 255, 0)
#define RED                         cv::Scalar(0, 0, 255)
#define BLUE                        cv::Scalar(255, 0, 0)
#define WHITE                       cv::Scalar(255, 255, 255)
#define BOX_COLOUR                  cv::Scalar(102, 204, 0)

#define SUSPICIOUS                  "suspicious"

class RecognizeBase
{

public:
    RecognizeBase();
    ~RecognizeBase() {}

    int32_t initialize(IRecognizeModel *model);
    /*For running two models in 1 loop.*/
    int32_t initialize(IRecognizeModel *model, IRecognizeModel *model_2);

    virtual int32_t recognize_start();
    virtual void recognize_end();
    void start_recognize();

    uint32_t get_drpai_start_addr();
    void fps_calculation(void);
    void object_detector(void);
    void show_result(void);
    cv::Mat create_output_frame(cv::Mat frame_g);
    /*font size to be used for text output*/
    float font_size = 0.65;
    /*font weight*/
    float font_weight = 2;
    /* quit application key detect flag */
    bool quit_application = false;
    bool init = true;
    /*start and stop time for inference time/fps calculations*/
    long int init_time, end_time;
    /*time for one inference*/
    long int time_one;
    /*inference time in ms*/
    long int infer_time_ms;
    std::vector<detection> postproc_data;
    cv::Mat g_bgra_image;
    /*pipeline for gstreamer output */
    std::string g_pipeline = "appsrc ! videoconvert ! autovideosink sync=false ";
    /*opencv video writer to write data to gstreamer pipeline,h264 format for compression */
    cv::VideoWriter output_writer;

private:
    void predict_thread();
    static void *get_quit_key(void *);
    static void *predict_thread_wrapper(void *object);
    static void run_predict(RecognizeBase *arg);

    static void *capture_thread(void *arg);
    static void *tvm_inference_thread(void *arg);
    static void *framerate_thread(void *arg);
    void inference_preprocess(void *arg, uint8_t model_id, uint32_t width, uint32_t height, 
                                float **out_ptr, uint32_t *out_size);
    void inference_postprocess(void *arg, uint8_t model_id, recognizeData_t &data);
    void send_result(void *arg, uint8_t model_id, recognizeData_t &data);
    int32_t end_all_threads();
    void close_camera();
    int8_t wait_join(pthread_t *p_join_thread, uint32_t join_time);
    double timedifference_msec(struct timespec t0, struct timespec t1);
    int32_t get_time(timespec &time_t);
    string get_send_image(uint8_t *image);

    int8_t file_exist(std::string filename);
    int8_t model_exist(std::string dir);

    pthread_t _pthread_ai_inf;
    pthread_t _pthread_capture;
    pthread_t _pthread_framerate;
    pthread_t _pthread_thPredict;
    pthread_t _pthread_quit_key;

    bool blRunPredict = false;
    /* variants */
    shared_ptr<Camera> _capture;

    int32_t _outBuffSize;
    /* for threads */
    bool _capture_running;
    bool _inf_running;
    bool _fps_runnning;

    std::atomic<bool> capture_enabled;
    std::atomic<int32_t> _ai_frame_count;
    std::atomic<int32_t> _camera_frame_count;

    mutex mtx_;
    condition_variable cv_;
    bool wake_;

    /* for capture */
    volatile uint32_t capture_address;
    uint8_t *input_data;

    /*AI Inference for DRP-AI*/
    std::string dir;

    /*objects to be detected from the config.ini file*/
    std::set<std::string> detection_object_set;
    /*filtered bb for displaying*/
    vector<bbox_t> detection_bb_vector;

    int32_t cap_w;
    int32_t cap_h;
    int32_t cap_c;
    int32_t model_w;
    int32_t model_h;
    int32_t model_c;
    uint8_t mode;

    shared_ptr<IRecognizeModel> _model;

    LinuxSystemAnalyzer _analyzer;

    /*For two model application*/
    shared_ptr<IRecognizeModel> _model_2;

    std::string dir_2;
    int32_t cap_w_2;
    int32_t cap_h_2;
    int32_t cap_c_2;
    int32_t model_w_2;
    int32_t model_h_2;
    int32_t model_c_2;
    uint8_t mode_2 = MODE_TVM_UNKNOWN;
    int32_t _outBuffSize_2;

    constexpr static int32_t YUY2_NUM_CHANNEL = (2);
    constexpr static int32_t YUY2_NUM_DATA = (4);

    constexpr static int8_t MODEL_OBJ_NUM = (3);
    std::string model_obj_names[MODEL_OBJ_NUM] =
        {
            "deploy.json",
            "deploy.params",
            "deploy.so"
        };
};

#endif
