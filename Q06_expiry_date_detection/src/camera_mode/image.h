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
* File Name    : image.h
* Version      : v1.00
* Description  : RZ/V2L AI SDK Sample Application: Expiry Date Extraction
***********************************************************************************************************************/

#ifndef IMAGE_H
#define IMAGE_H
#include <opencv2/opencv.hpp>
#include "define.h"
#include "ascii.h"
#include "../common/comm_define.h"


class Image
{
    public:
        Image();
        ~Image();

        uint8_t* img_buffer[WL_BUF_NUM];
        uint8_t get_buf_id();
        void write_string_rgb(std::string str, uint32_t x, uint32_t y, float size, uint32_t color);

        uint8_t udmabuf_fd;
        uint32_t get_H();
        uint32_t get_W();
        uint32_t get_C();
        uint8_t at(int32_t a);
        void set(int32_t a, uint8_t val);

        uint8_t init(uint32_t w, uint32_t h, uint32_t c, uint32_t ow, uint32_t oh, uint32_t oc);
        void draw_rect(int32_t x, int32_t y, int32_t w, int32_t h, const char* str);
        void convert_format();
        void convert_size();
        void camera_to_image(const uint8_t* buffer, int32_t size);
        cv::Mat get_crop_gray(int32_t x, int32_t y, int32_t width, int32_t height);
        cv::Mat resize_gray_image(const cv::Mat &input_img, int32_t resize_height);
    private:
        uint8_t buf_id = 0;

        /* Input Image (YUYV from V4L2) Information */
        uint32_t img_h;
        uint32_t img_w;
        uint32_t img_c;
        /* Output Image (BGRA for Wayland) Information */
        uint32_t out_h;
        uint32_t out_w;
        uint32_t out_c;

        uint32_t front_color            = BLACK_DATA;
        uint32_t back_color             = WHITE_DATA;
        uint32_t front_color_yuyv       = BLACK_DATA_YUYV;
        uint32_t back_color_yuyv        = WHITE_DATA_YUYV;
        uint8_t font_w = FONTDATA_WIDTH;
        uint8_t font_h = FONTDATA_HEIGHT;
        void draw_point_yuyv(int32_t x, int32_t y, uint32_t color);
        void draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);
        void write_char(char code,  uint32_t x,  uint32_t y, uint32_t color, uint32_t backcolor);
        void write_string(const char * pcode, uint32_t x, uint32_t y, uint32_t color, uint32_t backcolor);
};

#endif
