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
* File Name    : box.h
* Version      : v1.00
* Description  : RZ/V2L AI SDK Sample Application: Expiry Date Extraction
***********************************************************************************************************************/

#ifndef BOX_H
#define BOX_H

#include <vector>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*****************************************
* Box : Bounding box coordinates and its size
******************************************/
typedef struct
{
    float x, y, w, h;
} BBox;

/*****************************************
* detection : Detected result
******************************************/
typedef struct detection
{
    BBox bbox;
    int32_t c;
    float prob;
} detection;

/*****************************************
* Functions
******************************************/
float box_iou(BBox a, BBox b);
float overlap(float x1, float w1, float x2, float w2);
float box_intersection(BBox a, BBox b);
float box_union(BBox a, BBox b);
void filter_boxes_nms(std::vector<detection> &det, int32_t size, float th_nms);

#endif
