/*
 * Original Code (C) Copyright Edgecortix, Inc. 2022
 * Modified Code (C) Copyright Renesas Electronics Corporation 2023
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
* Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : define.h
* Version      : v1.00
* Description  : RZ/V2L AI SDK Sample Application: Expiry Date Extraction
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
#include <sys/time.h>
#include <climits>
#include <builtin_fp16.h>
#include <mutex>
#include <string>
#include <unordered_map>


/*****************************************
* Static Variables for YOLOv3
* Following variables need to be changed in order to custormize the AI model
*  - model_dir = directory name of DRP-AI TVM[*1] Model Object files
******************************************/
/* Model Binary */
const static std::string model_dir = "date_tinyyolov3_onnx";
/* Pre-processing Runtime Object */
const static std::string pre_dir = model_dir + "/preprocess";
/* Anchor box information */
const static double anchors[] =
{
    21, 12,  
    57, 11, 
    104, 15,  
    62, 27, 
    146, 28, 
    206, 47
};
/* Class labels to be classified */
const static std::string label_list     = "date_class_labels.txt";
/* Empty since labels will be loaded from label_list file */
static std::vector<std::string> label_file_map = {};

/*****************************************
* Macro for YOLOv3
******************************************/

/* Number of class to be detected */
#define NUM_CLASS                   (4)
/* Number for [region] layer num parameter */
#define NUM_BB                      (3)
#define NUM_INF_OUT_LAYER           (2)
/* Thresholds */
#define TH_PROB                     (0.5f)
#define TH_NMS                      (0.5f)
/* Size of input image to the model */
#define MODEL_IN_W                  (416)
#define MODEL_IN_H                  (416)

/* Number of grids in the image. The length of this array MUST match with the NUM_INF_OUT_LAYER */
const static uint8_t num_grids[] = { 13, 26};
/* Number of DRP-AI output */
const static uint32_t INF_OUT_SIZE  = (NUM_CLASS + 5) * NUM_BB * num_grids[0] * num_grids[0]
                                      + (NUM_CLASS + 5) * NUM_BB * num_grids[1] * num_grids[1]; 

/*****************************************
* Macro for Application
******************************************/
/* Coral Camera support */
#define INPUT_CORAL

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

/*Camera Capture Information */
#ifdef INPUT_CORAL
#define CAP_BUF_NUM                 (6)
#else /* INPUT_CORAL */
#define CAP_BUF_NUM                 (3)
#endif /* INPUT_CORAL */

/*DRP-AI Input image information*/
#define DRPAI_IN_WIDTH              (CAM_IMAGE_WIDTH)
#define DRPAI_IN_HEIGHT             (CAM_IMAGE_HEIGHT)
#define DRPAI_IN_CHANNEL_YUY2       (CAM_IMAGE_CHANNEL_YUY2)

/*Wayland Display Image Information*/
#define IMAGE_OUTPUT_WIDTH          (1280)
#define IMAGE_OUTPUT_HEIGHT         (720)
#define IMAGE_CHANNEL_BGRA          (4)
#define WL_BUF_NUM                  (2)

/*udmabuf memory area Information*/
#define UDMABUF_OFFSET              (CAM_IMAGE_WIDTH * CAM_IMAGE_HEIGHT * CAM_IMAGE_CHANNEL_YUY2 * CAP_BUF_NUM)
#define UDMABUF_INFIMAGE_OFFSET     (IMAGE_OUTPUT_WIDTH * IMAGE_OUTPUT_HEIGHT * IMAGE_CHANNEL_BGRA * WL_BUF_NUM + UDMABUF_OFFSET)

/*Image:: Text information to be drawn on image*/
#define CHAR_SCALE_LARGE            (0.8)
#define CHAR_SCALE_SMALL            (0.7)
#define CHAR_THICKNESS              (2)
#define LINE_HEIGHT                 (30) /*in pixel*/
#define LINE_HEIGHT_OFFSET          (20) /*in pixel*/
#define TEXT_WIDTH_OFFSET           (10) /*in pixel*/
#define TIME_LINE_NUM               (4) /*Total, inference, preprocess, postprocess*/
#define TIME_TOTAL_ID               (0)
#define TIME_INF_ID                 (1)
#define TIME_PRE_ID                 (2)
#define TIME_POST_ID                (3)
#define WHITE_DATA                  (0xFFFFFFu) /* in RGB */
#define BLACK_DATA                  (0x000000u)
#define WHITE_DATA_YUYV             (0xEB8080u) /* in YUYV */
#define BLACK_DATA_YUYV             (0x108080u)
/*RESIZE_SCALE=((OUTPUT_WIDTH/IMAGE_WIDTH > OUTPUT_HEIGHT/IMAGE_HEIGHT) ?
        OUTPUT_HEIGHT/IMAGE_HEIGHT : OUTPUT_WIDTH/IMAGE_WIDTH)*/
#define RESIZE_SCALE                (1.5)


/*Waiting Time*/
#define WAIT_TIME                   (1000) /* microseconds */

/*Timer Related*/
#define CAPTURE_TIMEOUT             (20)  /* seconds */
#define AI_THREAD_TIMEOUT           (20)  /* seconds */
#define KEY_THREAD_TIMEOUT          (5)   /* seconds */

/*****************************************
* For image.cpp
******************************************/
/*For drawing the bounding box label on image*/
#define FONTDATA_WIDTH              (6)
#define FONTDATA_HEIGHT             (8)

/****************************************
 * Structure to store the date variable
*****************************************/
struct date_struct
{
    std::string txt_extr;
    std::string year;
    std::string month;
    std::string day;
};

#define MIN_CROP_HEIGHT             (32)
#define TESS_IMG_RESOLUTION         (330)
#define CROP_IMG_STRETCH            (10) // Pixel value Used to extended crop section from the image


#endif
