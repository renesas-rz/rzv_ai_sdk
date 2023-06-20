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
 * File Name    : image.cpp
 * Version      : v1.00
 * Description  : RZ/V2L AI SDK Sample Application: Expiry Date Extraction
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
    int32_t i;

    for (i = 0; i < WL_BUF_NUM; i++)
    {
        munmap(img_buffer[i], img_w * img_h * img_c);
    }
    close(udmabuf_fd);
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
 * Function Name : init
 * Description   : Function to initialize img_buffer in Image class
 *                 This application uses udmabuf in order to
 *                 continuous memory area for DRP-AI input data
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
    int32_t i;
    int32_t j;

    /*Initialize input image information */
    img_w = w;
    img_h = h;
    img_c = c;
    /*Initialize output image information*/
    out_w = ow;
    out_h = oh;
    out_c = oc;

    uint32_t out_size = out_w * out_h * out_c;
    udmabuf_fd = open("/dev/udmabuf0", O_RDWR);
    if (0 > udmabuf_fd)
    {
        return -1;
    }
    for (i = 0; i < WL_BUF_NUM; i++)
    {
        img_buffer[i] = (unsigned char *)mmap(NULL, out_size, PROT_READ | PROT_WRITE, MAP_SHARED, udmabuf_fd, UDMABUF_OFFSET + i * out_size);
        if (MAP_FAILED == img_buffer[i])
        {
            return -1;
        }
        /* Write once to allocate physical memory to u-dma-buf virtual space.
         * Note: Do not use memset() for this.
         *       Because it does not work as expected. */
        {
            for (j = 0; j < out_size; j++)
            {
                img_buffer[i][j] = 0;
            }
        }
    }
    return 0;
}

/*****************************************
 * Function Name : write_char
 * Description   : Display character in overlap buffer
 * Arguments     : code = code to be displayed
 *                 x = X coordinate to display character
 *                 y = Y coordinate to display character
 *                 color = character color
 * Return value  : -
 ******************************************/
void Image::write_char(char code, uint32_t x, uint32_t y, uint32_t color, uint32_t backcolor)
{
    uint32_t height;
    uint32_t width;
    char *p_pattern;
    uint8_t mask = 0x80;

    if ((code >= 0x20) && (code <= 0x7e))
    {
        p_pattern = (char *)&g_ascii_table[code - 0x20][0];
    }
    else
    {
        p_pattern = (char *)&g_ascii_table[10][0]; /* '*' */
    }

    /* Drawing */
    for (height = 0; height < font_h; height++)
    {
        for (width = 0; width < font_w; width++)
        {
            if (p_pattern[width] & mask)
            {
                draw_point_yuyv(width + x, height + y, color);
            }
            else
            {
                draw_point_yuyv(width + x, height + y, backcolor);
            }
        }
        mask = (uint8_t)(mask >> 1);
    }
    return;
}

/*****************************************
 * Function Name : write_string_rgb
 * Description   : OpenCV putText() in RGB
 * Arguments     : str = string to be drawn
 *                 x = bottom left coordinate X of string to be drawn
 *                 y = bottom left coordinate Y of string to be drawn
 *                 scale = scale for letter size
 *                 color = letter color must be in RGB, e.g. white = 0xFFFFFF
 * Return Value  : -
 ******************************************/
void Image::write_string_rgb(std::string str, uint32_t x, uint32_t y, float scale, uint32_t color)
{
    uint8_t thickness = CHAR_THICKNESS;
    /*Extract RGB information*/
    uint8_t r = (color >> 16) & 0x0000FF;
    uint8_t g = (color >> 8) & 0x0000FF;
    uint8_t b = color & 0x0000FF;
    /*OpenCV image data is in BGRA */
    cv::Mat bgra_image(out_h, out_w, CV_8UC4, img_buffer[buf_id]);
    /*Color must be in BGR order*/
    //cv::putText(bgra_image, str.c_str(), cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, scale, cv::Scalar(b, g, r), thickness);
    cv::putText(bgra_image, str, cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, scale, cv::Scalar(b, g, r), thickness);
}

/**
 * @brief Get grayscaled cropped image
 *
 * @param x
 * @param y
 * @param width
 * @param height
 * @return cv::Mat
 */
cv::Mat Image::get_crop_gray(int32_t x_center, int32_t y_center, int32_t width, int32_t height)
{
    /* xmin, ymin extraction*/
    int32_t x_min = x_center - round(width / 2.);
    int32_t y_min = y_center - round(height / 2.);

    /*Increasing the crop section */
    x_min -= CROP_IMG_STRETCH;
    y_min -= CROP_IMG_STRETCH;
    width += CROP_IMG_STRETCH*2;
    height += CROP_IMG_STRETCH*2;

    /* Check if the rectangle box is in the image range */
    x_min = x_min < 0 ? 0: x_min;
    y_min = y_min < 0 ? 0 : y_min;
    width = x_min+width < img_w - 1? width : img_w - x_min -1;
    height= y_min+height < img_h - 1? height : img_h - y_min -1;

    /*OpenCV original image data is in YUYV format  */
    cv::Mat org_image(img_h, img_w, CV_8UC2, img_buffer[buf_id]);

    /*Define the region of interest (ROI) using a rectangle */
    cv::Rect roi(x_min, y_min, width, height);

    /*Extract the cropped region from the color image */
    cv::Mat cropped_image = org_image(roi);

    /*Convert BGRA image to grayscale */
    cv::Mat grayscale_image;
    cv::cvtColor(cropped_image, grayscale_image, cv::COLOR_YUV2GRAY_YUYV);

    return grayscale_image;
}

/**
 * @brief 
 * 
 * @param input_img 
 * @param resize_height 
 * @return cv::Mat 
 */
cv::Mat Image::resize_gray_image(const cv::Mat &input_img, int32_t resize_height)
{
    cv::Mat resized_img;

    // Resize to specified height while maintaining aspect ratio
    if (input_img.rows < resize_height)
    {

        double aspect_ratio = (double)input_img.cols / (double)input_img.rows;
        int resize_width = (int)(resize_height * aspect_ratio);
        cv::resize(input_img, resized_img, cv::Size(resize_width, resize_height), 0, 0, cv::INTER_CUBIC);

        return resized_img;
    }
    else
    {
        return input_img;
    }
}

/*****************************************
 * Function Name : write_string
 * Description   : Display character string in overlap buffer
 * Arguments     : pcode = A pointer to the character string to be displayed
 *                 x = X coordinate to display character string
 *                 y = Y coordinate to display character string
 *                 color = character string color
 * Return Value  : -
 ******************************************/
void Image::write_string(const char *pcode, uint32_t x, uint32_t y, uint32_t color, uint32_t backcolor)
{
    uint32_t i;
    uint32_t len = strlen(pcode);

    x = x < 0 ? 2 : x;
    x = (x > img_w - (i * font_w)) ? img_w - (i * font_w) - 2 : x;
    y = y < 0 ? 2 : y;
    y = (y > img_h - font_h) ? img_h - font_h - 2 : y;

    for (i = 0; i < len; i++)
    {
        write_char(pcode[i], (x + (i * font_w)), y, color, backcolor);
    }

    return;
}

/*****************************************
 * Function Name : draw_point_yuyv
 * Description   : Draw a single point on YUYV image
 * Arguments     : x = X coordinate to draw a point
 *                 y = Y coordinate to draw a point
 *                 color = point color
 * Return Value  : -
 ******************************************/
void Image::draw_point_yuyv(int32_t x, int32_t y, uint32_t color)
{
    uint32_t x0 = (uint32_t)x & ~0x1;

    uint32_t draw_u = (color >> 8) & 0xFF;
    uint32_t draw_v = (color >> 0) & 0xFF;

    uint32_t target_u = img_buffer[buf_id][(y * img_w + x0) * img_c + 1];
    uint32_t target_v = img_buffer[buf_id][(y * img_w + x0) * img_c + 3];

    img_buffer[buf_id][(y * img_w + x0) * img_c + 1] = (draw_u + target_u) / 2;
    img_buffer[buf_id][(y * img_w + x0) * img_c + 3] = (draw_v + target_v) / 2;

    if ((x & 1) == 0)
    {
        img_buffer[buf_id][(y * img_w + x0) * img_c] = (color >> 16) & 0xFF;
    }
    else
    {
        img_buffer[buf_id][(y * img_w + x0) * img_c + 2] = (color >> 16) & 0xFF;
    }
    return;
}

/*****************************************
 * Function Name : draw_line
 * Description   : Draw a single line
 * Arguments     : x0 = X coordinate of a starting point
 *                 y0 = Y coordinate of a starting point
 *                 x1 = X coordinate of a end point
 *                 y1 = Y coordinate of a end point
 *                 color = line color
 * Return Value  : -
 ******************************************/
void Image::draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;
    int32_t sx = 1;
    int32_t sy = 1;
    float de;
    int32_t i;

    /* Change direction */
    if (0 > dx)
    {
        dx *= -1;
        sx *= -1;
    }

    if (0 > dy)
    {
        dy *= -1;
        sy *= -1;
    }

    draw_point_yuyv(x0, y0, color);

    if (dx > dy)
    {
        /* Horizontal Line */
        for (i = dx, de = i / 2; i; i--)
        {
            x0 += sx;
            de += dy;
            if (de > dx)
            {
                de -= dx;
                y0 += sy;
            }
            draw_point_yuyv(x0, y0, color);
        }
    }
    else
    {
        /* Vertical Line */
        for (i = dy, de = i / 2; i; i--)
        {
            y0 += sy;
            de += dx;
            if (de > dy)
            {
                de -= dy;
                x0 += sx;
            }
            draw_point_yuyv(x0, y0, color);
        }
    }
    return;
}

/*****************************************
 * Function Name : draw_rect
 * Description   : Draw a rectangle
 * Arguments     : x = X coordinate of the center of rectangle
 *                 y = Y coordinate of the center of rectangle
 *                 w = width of the rectangle
 *                 h = height of the rectangle
 *                 str = string to label the rectangle
 * Return Value  : -
 ******************************************/
void Image::draw_rect(int32_t x, int32_t y, int32_t w, int32_t h, const char *str)
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

    /* Draw the class and probability */
    write_string(str, x_min + 1, y_min + 1, back_color_yuyv, front_color_yuyv);
    /* Draw the bounding box */
    draw_line(x_min, y_min, x_max, y_min, front_color_yuyv);
    draw_line(x_max, y_min, x_max, y_max, front_color_yuyv);
    draw_line(x_max, y_max, x_min, y_max, front_color_yuyv);
    draw_line(x_min, y_max, x_min, y_min, front_color_yuyv);
    draw_line(x_min - 1, y_min - 1, x_max + 1, y_min - 1, back_color_yuyv);
    draw_line(x_max + 1, y_min - 1, x_max + 1, y_max + 1, back_color_yuyv);
    draw_line(x_max + 1, y_max + 1, x_min - 1, y_max + 1, back_color_yuyv);
    draw_line(x_min - 1, y_max + 1, x_min - 1, y_min - 1, back_color_yuyv);

    return;
}

/*****************************************
 * Function Name : convert_format
 * Description   : Convert YUYV image to BGRA format
 * Arguments     : -
 * Return value  : -
 ******************************************/
void Image::convert_format()
{
    cv::Mat yuyv_image(img_h, img_w, CV_8UC2, img_buffer[buf_id]);
    cv::Mat bgra_image;
    cv::Mat out_image(img_h, img_w, CV_8UC4, img_buffer[buf_id]);
    cv::cvtColor(yuyv_image, bgra_image, cv::COLOR_YUV2BGRA_YUYV);
    memcpy(out_image.data, bgra_image.data, img_w * img_h * out_c);
}

/*****************************************
 * Function Name : convert_size
 * Description   : Scale up the input data (640x480) to the intermediate data (960x720) using OpenCV.
 *                 To convert to the final output size (1280x720), fill the right margin of the
 *                 intermediate data (960x720) with black.
 * Arguments     : -
 * Return value  : -
 ******************************************/
void Image::convert_size()
{
    cv::Mat org_image(img_h, img_w, CV_8UC4, img_buffer[buf_id]);
    cv::Mat resize_image;
    uint32_t resized_width = img_w * RESIZE_SCALE;
    /* Resize: 640x480 to 960x720 */
    cv::resize(org_image, resize_image, cv::Size(), RESIZE_SCALE, RESIZE_SCALE);

    /* Padding: 960x720 to 1280x720 */
    uint8_t *dst = img_buffer[buf_id];
    uint8_t *src = resize_image.data;
    int32_t i;
    int32_t j;

    for (i = 0; i < out_h; i++)
    {
        memcpy(dst, src, resized_width * out_c);
        dst += (resized_width * out_c);
        src += (resized_width * out_c);
        for (j = 0; j < (out_w - resized_width) * out_c; j += out_c)
        {
            dst[j] = 0;        // B
            dst[j + 1] = 0;    // G
            dst[j + 2] = 0;    // R
            dst[j + 3] = 0xff; // A
        }
        dst += ((out_w - resized_width) * out_c);
    }
}

/*****************************************
 * Function Name : camera_to_image
 * Description   : Function to copy the external image buffer data to img_buffer
 *                 This is only place where the buf_id is updated.
 * Arguments     : buffer = buffer to copy the image data
 *                 size = size of buffer
 * Return value  : none
 ******************************************/
void Image::camera_to_image(const uint8_t *buffer, int32_t size)
{
    /* Update buffer id */
    buf_id = ++buf_id % WL_BUF_NUM;
    memcpy(img_buffer[buf_id], buffer, sizeof(uint8_t) * size);
}

/*****************************************
 * Function Name : at
 * Description   : Get the value of img_buffer at index a.
 *                 This function is NOT used currently.
 * Arguments     : a = index of img_buffer
 * Return Value  : value of img_buffer at index a
 ******************************************/
uint8_t Image::at(int32_t a)
{
    return img_buffer[buf_id][a];
}

/*****************************************
 * Function Name : set
 * Description   : Set the value of img_buffer at index a.
 *                 This function is NOT used currently.
 * Arguments     : a = index of img_buffer
 *                 val = new value to be set
 * Return Value  : -
 ******************************************/
void Image::set(int32_t a, uint8_t val)
{
    img_buffer[buf_id][a] = val;
    return;
}
/*****************************************
 * Function Name : get_buf_id
 * Description   : Get the value of the buf_id.
 * Arguments     : -
 * Return Value  : value of buf_id-
 ******************************************/
uint8_t Image::get_buf_id(void)
{
    return buf_id;
}
