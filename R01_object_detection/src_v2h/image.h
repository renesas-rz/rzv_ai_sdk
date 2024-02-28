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
/***********************************************************************************************************************
* File Name    : image.h
* Version      : v3.00
* Description  : RZ/V2H AI SDK Sample Application for Object Detection
***********************************************************************************************************************/

#ifndef IMAGE_H
#define IMAGE_H

#include "define.h"
#include <opencv2/opencv.hpp>

class Image
{
    public:
        Image();
        ~Image();

        cv::Mat img_mat;

        void write_string_rgb(std::string str, uint8_t align_type, uint32_t x, uint32_t y, float size, uint32_t color);
        void write_string_rgb_boundingbox(std::string str, uint8_t align_type,  
                uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max,
                float scale, uint32_t color, uint32_t str_color);
        void draw_rect(int32_t x, int32_t y, int32_t w, int32_t h, const char* str,uint32_t color, uint32_t label_color);

        uint32_t get_H();
        uint32_t get_W();
        uint32_t get_C();

        uint8_t init(uint32_t w, uint32_t h, uint32_t c, uint32_t ow, uint32_t oh, uint32_t oc);
        void convert_size(int in_w, int resize_w, bool is_padding);
        void set_mat(const cv::Mat& input_mat);
        cv::Mat get_mat();

    private:
        /* Input Image (BGR from camera) Information */
        uint32_t img_h;
        uint32_t img_w;
        uint32_t img_c;
        /* Output Image (BGRA for Wayland) Information */
        uint32_t out_h;
        uint32_t out_w;
        uint32_t out_c;

        uint8_t align_l         = ALIGHN_LEFT;
        uint8_t align_r         = ALIGHN_RIGHT;
};

#endif
