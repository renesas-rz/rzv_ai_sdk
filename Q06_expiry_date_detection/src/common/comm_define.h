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

#ifndef DEFINE_COMM_MACRO_H
#define DEFINE_COMM_MACRO_H

/*****************************************
* includes
******************************************/
#include <builtin_fp16.h>
#include <cctype>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>
#include <glob.h>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <map>
#include <mutex>
#include <opencv2/opencv.hpp>

/*****************************************
* Model Directory Information
******************************************/
/* Model Binary */
const static std::string model_dir = "date_tinyyolov3_onnx";
/* Pre-processing Runtime Object */
const static std::string pre_dir = model_dir + "/preprocess";

/* Class labels to be classified */
const static std::string label_list = "date_class_labels.txt";

/* Empty List since labels will be loaded from label_list file */
static std::vector<std::string> label_file_map = {};

/*****************************************
 * Macro for YOLOv3
 ******************************************/
/* Number of class to be detected */
#define NUM_CLASS (4)
/* Number for [region] layer num parameter */
#define NUM_BB (3)
#define NUM_INF_OUT_LAYER (2)
/* Thresholds */
#define TH_PROB (0.2f)
#define TH_NMS (0.5f)
/* Size of input image to the model */
#define MODEL_IN_W (416)
#define MODEL_IN_H (416)

/* Number of grids in the image. The length of this array MUST match with the NUM_INF_OUT_LAYER */
const static uint8_t num_grids[] = {13, 26};
/* Number of DRP-AI output */
const static uint32_t INF_OUT_SIZE = (NUM_CLASS + 5) * NUM_BB * num_grids[0] * num_grids[0] + (NUM_CLASS + 5) * NUM_BB * num_grids[1] * num_grids[1];
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

/****************************************
 * Text Extraction Related variable
 *****************************************/
/* Structure to store the date variable*/
struct date_struct
{
    std::string txt_extr;
    std::string year;
    std::string month;
    std::string day;
    int32_t remaining_days;
};
/*Image crop height to be fed to Tesseract OCR*/
#define MIN_CROP_HEIGHT             (84) 
#define TESS_IMG_RESOLUTION         (330)
#define CROP_IMG_STRETCH            (5) // Pixel value Used to extended crop section from the image
#define PREF_YR                     "20" // prefix for the 2 digit year; (23) -> (2023) 

//#define REM_DAY_DISP_OFF               // don't show the remaining days

#endif