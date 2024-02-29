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
* File Name    : image.cpp
* Version      : v3.00
* Description  : RZ/V2H AI SDK Sample Application for Object Detection
***********************************************************************************************************************/

/*****************************************
* Includes
******************************************/
#include "image.h"

Image::Image()
{

}


Image::~Image()
{
}

/*****************************************
* Function Name : get_H
* Description   : Function to get the image height
*                 This function is NOT used currently.
* Arguments     : -
* Return value  : img_h = current image height
******************************************/
uint32_t Image::get_H()
{
    return img_h;
}


/*****************************************
* Function Name : get_W
* Description   : Function to get the image width
*                 This function is NOT used currently.
* Arguments     : -
* Return value  : img_w = current image width
******************************************/
uint32_t Image::get_W()
{
    return img_w;
}


/*****************************************
* Function Name : get_C
* Description   : Function to set the number of image channel
*                 This function is NOT used currently.
* Arguments     : c = new number of image channel to be set
* Return value  : -
******************************************/
uint32_t Image::get_C()
{
    return img_c;
}


/*****************************************
* Function Name : get_mat
* Description   : Function to return the cv::Mat
* Arguments     : -
* Return value  : cv::Mat
******************************************/
cv::Mat Image::get_mat()
{
    return img_mat;
}


/*****************************************
* Function Name : set_mat
* Description   : Function to register cv::Mat to Image class
* Arguments     : input_mat = input cv::Mat to be registered.
* Return value  : -
******************************************/
void Image::set_mat(const cv::Mat& input_mat)
{
    img_mat = input_mat.clone();
}


/*****************************************
* Function Name : init
* Description   : Function to initialize Image class
* Arguments     : w = input image width in YUYV
*                 h = input image height in YUYV
*                 c = input image channel in YUYV
*                 ow = output image width in BGRA to be displayed via Wayland
*                 oh = output image height in BGRA to be displayed via Wayland
*                 oc = output image channel in BGRA to be displayed via Wayland
* Return value  : 0 if succeeded
*                 not 0 otherwise
******************************************/
uint8_t Image::init(uint32_t w, uint32_t h, uint32_t c,
                    uint32_t ow, uint32_t oh, uint32_t oc)
{
    /*Initialize input image information */
    img_w = w;
    img_h = h;
    img_c = c;
    /*Initialize output image information*/
    out_w = ow;
    out_h = oh;
    out_c = oc;
    return 0;
}

/*****************************************
* Function Name : write_string_rgb
* Description   : OpenCV putText() in RGB
* Arguments     : str = string to be drawn
*                 align_type = left-align if 1 and right-align if 2
*                 x = bottom left coordinate X of string to be drawn
*                 y = bottom left coordinate Y of string to be drawn
*                 scale = scale for letter size
*                 color = color of bounding box. must be in RGB, e.g. white = 0xFFFFFF
* Return Value  : -
******************************************/
void Image::write_string_rgb(std::string str, uint8_t align_type,  uint32_t x, uint32_t y, float scale, uint32_t color)
{
    uint8_t thickness = CHAR_THICKNESS;
    /*Extract RGB information*/
    uint8_t r = (color >> 16) & RGB_FILTER;
    uint8_t g = (color >>  8) & RGB_FILTER;
    uint8_t b = color & RGB_FILTER;
    int ptx = 0;
    int pty = 0;
    /*OpenCV image data is in BGRA */
    cv::Mat bgra_image = img_mat.clone();

    int baseline = 0;
    cv::Size size = cv::getTextSize(str.c_str(), cv::FONT_HERSHEY_SIMPLEX, scale, thickness + 2, &baseline);
    if (align_type == 1)
    {
        ptx = x;
        pty = y;
    }
    else if (align_type == 2)
    {
        ptx = out_w - (size.width + x);
        pty = y;
    }
    /*Color must be in BGR order*/
    cv::putText(bgra_image, str.c_str(), cv::Point(ptx, pty), cv::FONT_HERSHEY_SIMPLEX, 
                    scale, cv::Scalar(0x00, 0x00, 0x00, 0xFF), thickness + 2);
    cv::putText(bgra_image, str.c_str(), cv::Point(ptx, pty), cv::FONT_HERSHEY_SIMPLEX, 
                    scale, cv::Scalar(b, g, r, 0xFF), thickness);

    img_mat = bgra_image.clone();

}

/*****************************************
* Function Name : write_string_rgb_boundingbox
* Description   : Draw bounding box with label in RGB
* Arguments     : str = string to be drawn
*                 align_type = left-align if 1 and right-align if 2
*                 x_min = top left coordinate X of box to be drawn
*                 y_min = top left coordinate Y of box to be drawn
*                 x_max = bottom right coordinate X of box to be drawn
*                 y_max = bottom right coordinate Y of box to be drawn
*                 scale = scale for letter size
*                 color = color of bounding box. must be in RGB, e.g. white = 0xFFFFFF
*                 str_color = color of letter. must be in RGB, e.g. white = 0xFFFFFF
* Return Value  : -
******************************************/
void Image::write_string_rgb_boundingbox(std::string str, uint8_t align_type, 
    uint32_t x_min, uint32_t y_min, uint32_t x_max, uint32_t y_max,
    float scale, uint32_t color, uint32_t str_color)
{
    uint8_t thickness = CHAR_THICKNESS_BB;
    /*Extract RGB information*/
    uint8_t r = (color >> 16) & RGB_FILTER;
    uint8_t g = (color >>  8) & RGB_FILTER;
    uint8_t b = color & RGB_FILTER;
    
    uint8_t r_str = (str_color >> 16) & RGB_FILTER;
    uint8_t g_str = (str_color >>  8) & RGB_FILTER;
    uint8_t b_str = str_color & RGB_FILTER;
	
    int ptx = 0;
    int pty = 0;
    /*OpenCV image data is in BGRA */
    cv::Mat bgra_image = img_mat.clone();
    int baseline = 0;

    /*Color must be in BGR order*/
    /*Draw Bounding Box with white double line */
    cv::rectangle(bgra_image, cv::Point(x_min+BOX_LINE_SIZE,y_min+BOX_LINE_SIZE), 
                    cv::Point(x_max-BOX_LINE_SIZE,y_max-BOX_LINE_SIZE), 
                    cv::Scalar(0xFF, 0xFF, 0xFF, 0xFF), BOX_DOUBLE_LINE_SIZE);
    cv::rectangle(bgra_image, cv::Point(x_min,y_min), 
                    cv::Point(x_max,y_max), 
                    cv::Scalar(b, g, r, 0xFF), BOX_LINE_SIZE);

    cv::Size size = cv::getTextSize(str.c_str(), cv::FONT_HERSHEY_SIMPLEX, scale, thickness + 2, &baseline);
    if (align_type == align_l)
    {
        ptx = x_min;
        pty = y_min;
    }
    else if (align_type == align_r)
    {
        ptx = img_w - (size.width + x_min);
        pty = y_min;
    }
    /*Draw label rectangle*/
    cv::rectangle(bgra_image, cv::Point(ptx-BOX_LINE_SIZE+1,pty+size.height+2), 
                    cv::Point(ptx+size.width,pty), cv::Scalar(b, g, r, 0xFF), cv::FILLED);
    /*Draw text as bounding box label in BLACK*/
    cv::putText(bgra_image, str.c_str(), cv::Point(ptx, pty+size.height), 
                    cv::FONT_HERSHEY_SIMPLEX, scale, cv::Scalar(b_str, g_str, r_str, 0xFF), thickness);

    img_mat = bgra_image.clone();
}
/*****************************************
* Function Name : draw_rect
* Description   : Draw a rectangle
* Arguments     : x = X coordinate of the center of rectangle
*                 y = Y coordinate of the center of rectangle
*                 w = width of the rectangle
*                 h = height of the rectangle
*                 str = string to label the rectangle
*                 color = color code for bounding box
*                 label_color = color code for label text
* Return Value  : -
******************************************/
void Image::draw_rect(int32_t x, int32_t y, int32_t w, int32_t h, const char * str,uint32_t color,uint32_t label_color)
{
    int32_t x_min = x - round(w / 2.);
    int32_t y_min = y - round(h / 2.);
    int32_t x_max = x + round(w / 2.) - 1;
    int32_t y_max = y + round(h / 2.) - 1;
    /* Check the bounding box is in the image range */
    x_min = x_min < 1 ? 1 : x_min;
    x_max = ((img_w - 2) < x_max) ? (img_w - 2) : x_max;
    y_min = y_min < 1 ? 1 : y_min;
    y_max = ((img_h - 2) < y_max) ? (img_h - 2) : y_max;

    /* Draw the bounding box and class and probability*/
    write_string_rgb_boundingbox(str,1,x_min, y_min,x_max,y_max,CHAR_SCALE_BB,color, label_color);

    return;
}


/*****************************************
* Function Name : convert_size
* Description   : Scale up the input data to the intermediate data using OpenCV.
*                 To convert to the final output size (1280x720), fill the right margin of the
*                 intermediate data (960x720) with black.
* Arguments     : -
* Return value  : -
******************************************/
void Image::convert_size(int in_w, int resize_w, bool is_padding)
{
    if (in_w == resize_w)
    {
        return;
    }

    cv::Mat org_image = img_mat;
    cv::Mat resize_image;

    if (is_padding)
    {
        cv::resize(org_image, resize_image, cv::Size(), 1.0 * out_h / img_h, 1.0 * out_h / img_h);
        copyMakeBorder(resize_image, resize_image, 0, 0, 0, out_w - resize_image.cols, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0, 255));
        img_mat = resize_image;
    }
    else
    {
        cv::resize(org_image, resize_image, cv::Size(), 1.0 * resize_w / in_w, 1.0 * resize_w / in_w);
        img_mat = resize_image;
    }
}
