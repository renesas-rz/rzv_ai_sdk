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
#ifndef DEFINE_MACRO_H
#define DEFINE_MACRO_H

/*****************************************
* includes
******************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <float.h>
#include <atomic>
#include <semaphore.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include <climits>
#include <mutex>
#include <set>
#include <linux/drpai.h>
#include <builtin_fp16.h>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "wayland.h"

/*Including Tessseract libraries*/
#include "common/date_chck_module/date_check.h"
#include "common/regex_module/regex_function.h"
#include "common/tess_module/TesseractEngine.h"
#include "common/text_proc_module/TextProc.h"

static Wayland wayland;
/* Empty since labels will be loaded from label_list file */
static std::vector<std::string> label_file_map = {};

/*****************************************
* Macro for YOLOv3
******************************************/
/*****************************************
* Static Variables for YOLOv3
* Following variables need to be changed in order to custormize the AI model
*  - model_dir = directory name of DRP-AI TVM[*1] Model Object files
******************************************/
/* Class labels to be classified */
const static std::string label_list     = "date_class_labels.txt";
/* Number of class to be detected */
#define NUM_CLASSES                 (4)
/* Number for [region] layer num parameter */
#define NUM_BB                      (3)
/* Thresholds */
#define TH_PROB                     (0.5f)
#define TH_NMS                      (0.5f)
// /* Size of input image to the model */
#define MODEL_IN_W                  (416)
#define MODEL_IN_H                  (416)

#ifdef V2H
    /* Model Binary */
    const static std::string model_dir = "expiry_yolov3_onnx";
    #define NUM_INF_OUT_LAYER           (3)
    /* Number of grids in the image. The length of this array MUST match with the NUM_INF_OUT_LAYER */
    const static uint8_t num_grids[] = { 13, 26, 52 };
    /* Anchor box information */
    const static double anchors[] =
    {
        10, 13,
        16, 30,
        33, 23,
        30, 61,
        62, 45,
        59, 119,
        116, 90,
        156, 198,
        373, 326
    };
#elif V2L
    /* Model Binary */
    #define NUM_INF_OUT_LAYER           (2)
    const static std::string model_dir = "date_detection_tinyyolov3";
    /* Number of grids in the image. The length of this array MUST match with the NUM_INF_OUT_LAYER */
    const static uint8_t num_grids[] = { 13, 26 };  
    /* Anchors for Tiny Yolo V3*/
    const static double anchors[] =
    {
        21, 12,
        57, 11,
        104, 15,
        62, 27,
        146, 28,
        206, 47
    };
#endif


/*****************************************
* Macro for Application
******************************************/
#define IMAGE_CHANNEL_BGRA          (4)
/*Waiting Time*/
#define WAIT_TIME                   (1000) /* microseconds */

/*Timer Related*/
#define CAPTURE_TIMEOUT             (20)  /* seconds */
#define AI_THREAD_TIMEOUT           (20)  /* seconds */
/*DRP-AI memory area offset for model objects*/
/*Offset value depends on the size of memory area used by DRP-AI Pre-processing Runtime Object files*/
#define DRPAI_MEM_OFFSET            (0)

/*Maximum DRP-AI Timeout threshold*/
#define DRPAI_TIMEOUT               (5)

/*Frame threshold to execute inference in every loop
 *This value must be determined by DRP-AI processing time and capture processing time.
 *For your information YOLOv3 takes around 50 msec and capture takes around 50 msec. */
#define INF_FRAME_NUM               (2)

/*Camera Capture Image Information*/
#define CAM_IMAGE_WIDTH             (640)
#define CAM_IMAGE_HEIGHT            (480)
#define CAM_IMAGE_CHANNEL_YUY2      (2)

#define CAP_BUF_NUM                 (6)

/*DRP-AI Input image information*/
#define DRPAI_IN_WIDTH              (CAM_IMAGE_WIDTH)
#define DRPAI_IN_HEIGHT             (CAM_IMAGE_HEIGHT)
#define DRPAI_IN_CHANNEL_YUY2       (CAM_IMAGE_CHANNEL_YUY2)

/* Display Image Information*/
#define IMAGE_CHANNEL_BGRA          (4)

#ifdef V2H
    #define DISP_IMAGE_OUTPUT_WIDTH     (1480)
    #define DISP_IMAGE_OUTPUT_HEIGHT    (1080)
    #define DISP_OUTPUT_WIDTH           (1920)
    #define DISP_OUTPUT_HEIGHT          (1080)
#elif V2L
    #define DISP_IMAGE_OUTPUT_WIDTH     (960)
    #define DISP_IMAGE_OUTPUT_HEIGHT    (720)
    #define DISP_OUTPUT_WIDTH           (1280)
    #define DISP_OUTPUT_HEIGHT          (720)
#endif


/*Waiting Time*/
#define WAIT_TIME                   (1000) /* microseconds */

/*Timer Related*/
#define CAPTURE_TIMEOUT             (20)  /* seconds */
#define AI_THREAD_TIMEOUT           (20)  /* seconds */
#define EXIT_THREAD_TIMEOUT         (10)  /* seconds */
#define KEY_THREAD_TIMEOUT          (5)   /* seconds */


/*Image:: Text information to be drawn on image*/
#define CHAR_SCALE_LARGE            (0.85)
#define CHAR_SCALE_SMALL            (0.7)
#define CHAR_SCALE_SMALLER          (0.5)
#define CHAR_SCALE_XS               (0.3)
#define CHAR_THICKNESS              (1)
#define CHAR_THICKNESS_OUT          (2)
#define LINE_HEIGHT                 (30) /*in pixel*/
#define LINE_HEIGHT_OFFSET          (20) /*in pixel*/
#define WHITE_DATA                  (0xFFFFFFu) /* in RGB */
#define CV_WHITE                    cv::Scalar(255, 255, 255)
#define CV_BLACK                    cv::Scalar(0, 0, 0)
#define CV_GREEN                    cv::Scalar(0, 255, 0)
#define CV_RED                      cv::Scalar(0, 0, 255)
#define CV_FONT                     cv::FONT_HERSHEY_SIMPLEX

#ifdef V2H
    /* DRPAI_FREQ is the frequency settings  */
    /* for DRP-AI.                           */
    /* Basically use the default values      */
    #define DRPAI_FREQ                 (2)
    /* DRPAI_FREQ can be set from 1 to 127   */
    /* 1,2: 1GHz                             */
    /* 3: 630MHz                             */
    /* 4: 420MHz                             */
    /* 5: 315MHz                             */
    /* ...                                   */
    /* 127: 10MHz                            */
    /* Calculation Formula:                  */
    /*     1260MHz /(DRPAI_FREQ - 1)         */
    /*     (When DRPAI_FREQ = 3 or more.)    */
#endif


#endif
