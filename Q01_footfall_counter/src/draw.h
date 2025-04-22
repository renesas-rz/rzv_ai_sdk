/***********************************************************************************************************************
* Copyright 2024 Renesas Electronics Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***********************************************************************************************************************/
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

#ifndef DRAW_H
#define DRAW_H

#include "opencv2/opencv.hpp"

class Draw{
    public:
        Draw(int width, int height, std::string pipeline);
        void drawDisplay();
        void set_skip_frames();
    private:
        static void drawLine(int event, int x, int y, int f, void *);
        static void drawPolygon(int event, int x, int y, int f, void *);
        static void buttonMouseCallback(int event, int x, int y, int f, void *);
        cv::Mat getFrame();
        void drawLinePage();
        void drawPolygonPage();
        void drawSelectPage();
        void expand_line();
        void overlap_check();
        void save();
    private:
        int width, height;
        cv::Mat original_image, frame, cam_frame;
        cv::Point P1, P2, new_P1, new_P2;
        std::vector<cv::Point> polygon;
        cv::Point line_button_lt, line_button_rb, polygon_button_lt, polygon_button_rb;
        cv::Point line_button_text, polygon_button_text;
        cv::Point user_guide_text, user_guide_text_1, user_guide_text_2;
        std::string file = "background_image.jpg";
        std::string app_name = "DrawApp";
        std::string gstream;
        cv::Scalar white = cv::Scalar(255, 255, 255);
        cv::Scalar ash = cv::Scalar(150, 150, 150);
        cv::Scalar red = cv::Scalar(0, 0, 255);
        bool select_line = false;
        bool select_polygon = false;
        bool termination_clicked = false;
        bool clicked = false;
        bool done = false;
        bool done_line = false;
        bool done_polygon = false;
        bool skip_frames = false;
        bool has_overlap = false;
};

#endif
