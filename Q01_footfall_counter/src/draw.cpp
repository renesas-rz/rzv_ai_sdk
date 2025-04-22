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
/*****************************************
 * Includes
 ******************************************/
#include "draw.h"
#include <fstream>


/*****************************************
 * Function Name : Draw
 * Description   : Constuctor to initialize button and text positions
 * Arguments     : width = width of app window
 *                 height  = height of app window
 *                 pipeline  = gstreamer pipeline
 ******************************************/
Draw::Draw(int width, int height, std::string pipeline): width(width), height(height), gstream(pipeline)
{
    line_button_lt.x = (int)(width*0.2);
    line_button_lt.y = (int)(height*0.75 - 40);
    line_button_rb.x = (int)(width*0.45);
    line_button_rb.y = (int)(height*0.75 + 40);
    polygon_button_lt.x = (int)(width*0.55);
    polygon_button_lt.y = (int)(height*0.75 - 40);
    polygon_button_rb.x = (int)(width*0.8);
    polygon_button_rb.y = (int)(height*0.75 + 40);
    line_button_text.x = line_button_lt.x + 20;
    line_button_text.y = line_button_lt.y + 50;
    polygon_button_text.x = polygon_button_lt.x + 10;
    polygon_button_text.y = polygon_button_lt.y + 50;

    user_guide_text.x = (int)(width*0.05);
    user_guide_text.y = (int)(height*0.1);
    user_guide_text_1.x = user_guide_text.x;
    user_guide_text_1.y = user_guide_text.y + 30;
    user_guide_text_2.x = user_guide_text.x;
    user_guide_text_2.y = user_guide_text.y + 60;

}

/*****************************************
 * Function Name : drawLine
 * Description   : mouse callback function to draw line
 * Arguments     : event = type of mouse event
 *                 x, y  = x, y coordinate of mouse event
 *                 f = flags (optional)
 *                 data (optional)
 ******************************************/
void Draw::drawLine(int event, int x, int y, int f, void * data)
{
    Draw *anInstance = static_cast<Draw *>(data);
    switch (event)
    {
    case cv::EVENT_LBUTTONDOWN:
        if (!anInstance->has_overlap 
            && anInstance->width - 100 < x 
            && x < anInstance->width
            && 0 < y 
            && y < 40)
        {
            anInstance->done_line = true;
        }
        else
        {
            anInstance->clicked = true;
            anInstance->P1.x = x;
            anInstance->P1.y = y;
            anInstance->P2.x = x;
            anInstance->P2.y = y;
        }
        break;

    case cv::EVENT_LBUTTONUP:
        anInstance->P2.x = x;
        anInstance->P2.y = y;
        anInstance->clicked = false;
        anInstance->done = true;
        anInstance->overlap_check();
        break;

    case cv::EVENT_MOUSEMOVE:
        if (anInstance->clicked)
        {
            anInstance->P2.x = x;
            anInstance->P2.y = y;
        }
        break;

    default:
        break;
    }
}

/*****************************************
 * Function Name : drawPolygon
 * Description   : mouse callback function to draw polygon
 * Arguments     : event = type of mouse event
 *                 x, y  = x, y coordinate of mouse event
 *                 f = flags (optional)
 *                 data (optional)
 ******************************************/
void Draw::drawPolygon(int event, int x, int y, int f, void * data)
{
    Draw *anInstance = static_cast<Draw *>(data);
    switch (event)
    {
    case cv::EVENT_LBUTTONDOWN:
        if(anInstance->width - 100 < x 
            && x < anInstance->width
            && 0 < y 
            && y < 40)
        {
            anInstance->polygon.clear();
        }
        else if (!anInstance->has_overlap 
            && anInstance->polygon.size() > 2 
            && anInstance->width - 100 < x 
            && x < anInstance->width 
            && 42 < y 
            && y < 82)
        {
            anInstance->done_polygon = true;
        }
        else
        {
            anInstance->polygon.push_back(cv::Point(x, y));
        }
        break;

    case cv::EVENT_LBUTTONUP:
        anInstance->overlap_check();
        break;

    case cv::EVENT_RBUTTONDOWN:
        anInstance->polygon.clear();
        break;

    default:
        break;
    }
}

/*****************************************
 * Function Name : buttonMouseCallback
 * Description   : mouse callback function of home page
 * Arguments     : event = type of mouse event
 *                 x, y  = x, y coordinate of mouse event
 *                 f = flags (optional)
 *                 data (optional)
 ******************************************/
void Draw::buttonMouseCallback(int event, int x, int y, int f, void * data) 
{
    Draw *anInstance = static_cast<Draw *>(data);
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (anInstance->polygon_button_lt.x < x 
            && x < anInstance->polygon_button_rb.x 
            && anInstance->polygon_button_lt.y < y 
            && y < anInstance->polygon_button_rb.y) 
        {
            std::cout << "[INFO] Cliked Draw Polygon \n";
            anInstance->select_polygon = true;
            anInstance->done_polygon = false;
        }
        else if (anInstance->line_button_lt.x < x 
            && x < anInstance->line_button_rb.y 
            && anInstance->line_button_lt.y < y 
            && y < anInstance->line_button_rb.y)
        {
            std::cout << "[INFO] Cliked Draw Line \n";
            anInstance->select_line = true;
            anInstance->done_line = false;
        }
        else if (anInstance->width - 100 < x 
            && x < anInstance->width
            && 0 < y 
            && y < 60)
        {
            anInstance->save();
            anInstance->termination_clicked = true;
        }
    }
}

/*****************************************
 * Function Name : drawLinePage
 * Description   : Window to draw line
 ******************************************/
void Draw::drawLinePage()
{
    cv::Mat frame = cam_frame.clone();
    std::cout << "[INFO] Imshow Line Select!!\n";
    cv::destroyAllWindows();
    cv::namedWindow("Line", cv::WINDOW_NORMAL);
    cv::setMouseCallback("Line", drawLine, this);
    while(1) 
    {
        cv::Mat frame = cam_frame.clone();
        cv::putText(frame, "Draw a Line", user_guide_text, cv::FONT_HERSHEY_SIMPLEX, 0.8, red, 2);
         if (has_overlap)
        {
            cv::putText(frame, "Do not overlap with the polygon.", user_guide_text_1, cv::FONT_HERSHEY_SIMPLEX, 0.8, red, 2);
        }
        else 
        {
            cv::rectangle(frame, cv::Point(width - 100, 0), cv::Point(width, 40), ash, -1);
            cv::putText(frame, "Done", cv::Point(width - 80, 25), cv::FONT_HERSHEY_SIMPLEX, 0.8, white, 2);
        }
        if(done_polygon)
        {
            cv::polylines(frame, polygon, true, cv::Scalar(0, 255, 0), 2);
        }
        if (clicked)
        {
            cv::line(frame, P1, P2, red, 4);
        }
        if (!clicked && done)
        {
            expand_line();
            cv::line(frame, new_P1, new_P2, red, 4);
        }
        cv::imshow("Line", frame);
        cv::waitKey(1);
        if(done_line) break;
    }
    cv::destroyWindow("Line");
}

/*****************************************
 * Function Name : drawPolygonPage
 * Description   : Window to draw polygon
 ******************************************/
void Draw::drawPolygonPage()
{
    cv::Mat frame = cam_frame.clone();
    cv::destroyAllWindows();
    cv::namedWindow("Polygon", cv::WINDOW_NORMAL);
    cv::setMouseCallback("Polygon", drawPolygon, this);
    while(1) 
    {
        cv::Mat frame = cam_frame.clone();
        cv::putText(frame, "Click vertices of polygon", user_guide_text, cv::FONT_HERSHEY_SIMPLEX, 0.8, red, 2);
        cv::rectangle(frame, cv::Point(width - 100, 0), cv::Point(width, 40), ash, -1);
        cv::putText(frame, "Reset", cv::Point(width - 80, 25), cv::FONT_HERSHEY_SIMPLEX, 0.8, white, 2);
        if (has_overlap)
        {
            cv::putText(frame, "Do not overlap with the line.", user_guide_text_1, cv::FONT_HERSHEY_SIMPLEX, 0.8, red, 2);
        }
        if (!has_overlap && polygon.size() > 2) 
        {
            cv::rectangle(frame, cv::Point(width - 100, 42), cv::Point(width, 82), ash, -1);
            cv::putText(frame, "Done", cv::Point(width - 80, 67), cv::FONT_HERSHEY_SIMPLEX, 0.8, white, 2);
        }
        if (done_line)
        {
            cv::line(frame, new_P1, new_P2, red, 4);
        }
        if (polygon.size() != 0) cv::polylines(frame, polygon, true, cv::Scalar(0, 255, 0), 2);
        cv::imshow("Polygon", frame);
        cv::waitKey(1);
        if (done_polygon) break;
    }
    cv::destroyWindow("Polygon");
}

/*****************************************
 * Function Name : drawSelectPage
 * Description   : Window to select line/polygon page
 ******************************************/
void Draw::drawSelectPage()
{
    cv::putText(frame, "Draw a line and a region", user_guide_text, cv::FONT_HERSHEY_SIMPLEX, 0.8, red, 2);
    cv::putText(frame, "Once the setup is done,", user_guide_text_1, cv::FONT_HERSHEY_SIMPLEX, 0.8, red, 2);
    cv::putText(frame, "\"Save\" button will be shown", user_guide_text_2, cv::FONT_HERSHEY_SIMPLEX, 0.8, red, 2);

    /* button for "Line" */
    cv::rectangle(frame, line_button_lt, line_button_rb, ash, -1);
    cv::putText(frame, "Draw Line", line_button_text, cv::FONT_HERSHEY_SIMPLEX, 0.75, white, 2);
    /* button for "Region of interest" */
    cv::rectangle(frame, polygon_button_lt, polygon_button_rb, ash, -1);
    cv::putText(frame, "Draw Region", polygon_button_text, cv::FONT_HERSHEY_SIMPLEX, 0.7, white, 2);
    
    if(done_line && done_polygon)
    {
        cv::rectangle(frame, cv::Point(width - 100, 0), cv::Point(width, 40), ash, -1);
        cv::putText(frame, "Save", cv::Point(width - 80, 25), cv::FONT_HERSHEY_SIMPLEX, 0.8, white, 2);
    }

    cv::namedWindow(app_name, cv::WINDOW_NORMAL);
    cv::setMouseCallback(app_name, buttonMouseCallback, this);
    cv::imshow(app_name, frame);
}

/*****************************************
 * Function Name : drawDisplay
 * Description   : Main function to navigate between pages/windows
 ******************************************/
void Draw::drawDisplay()
{
    original_image = cv::imread(file);
    cv::resize(original_image, original_image, cv::Size(width, height));
    frame = original_image.clone();
    cam_frame = getFrame();
    cv::resize(cam_frame, cam_frame, cv::Size(width, height));
    while(cv::waitKey(1))
    {
        if(select_line){
            drawLinePage();
            select_line = false;
        }
        else if(select_polygon)
        {
            drawPolygonPage();
            select_polygon = false;
        }else
        {
            drawSelectPage();
        }
        if(termination_clicked)
        {
            cv::destroyAllWindows();
            break;
        }
    }
}

/*****************************************
 * Function Name : getFrame
 * Description   : function to capture sample frame from gstreamer pipeline
 * Return value  : cv::Mat frame
 ******************************************/
cv::Mat Draw::getFrame()
{
    cv::VideoCapture g_cap;
    cv::Mat frame;
    int count = 0;
    g_cap.open(gstream, cv::CAP_GSTREAMER);
    if (!g_cap.isOpened())
    {
        std::cout << "[ERROR] Error opening video stream or camera !\n"<< std::endl;
    }
    if(skip_frames)
    {
        while (count < 5)
        {
            g_cap >> frame;
            count++;
        }   
    }
    g_cap >> frame;
    return frame;
}

/*****************************************
 * Function Name : save
 * Description   : Function to save configure values to a file
 ******************************************/
void Draw::save()
{
    std::ofstream myfile ("data.txt");
    int i = 0;
    if (myfile.is_open())
    {
        myfile << "Point 1:" << new_P1.x << " " << new_P1.y << "\n";
        myfile << "Point 2:" << new_P2.x << " " << new_P2.y << "\n";
        for (cv::Point point: polygon)
        {
            myfile << "Polygon Point " << i << ":" << point.x << " " << point.y << "\n";
            i++;
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

/*****************************************
 * Function Name : set_skip_frames
 * Description   : Function to enable skip frames
 ******************************************/
void Draw::set_skip_frames()
{
    skip_frames = true;
}

/*****************************************
 * Function Name : expand_line
 * Description   : Function to extrapolate the line
 ******************************************/
void Draw::expand_line()
{
    double m = (P2.y - P1.y) / (double)(P2.x - P1.x);
    double b = P1.y - m * P1.x;
    int n = 500;

    new_P1.x = P1.x - n;
    new_P1.y = m * new_P1.x + b;
    new_P2.x = P2.x + n;
    new_P2.y = m * new_P2.x + b;
}

/*****************************************
 * Function Name : overlap_check
 * Description   : Function to check overlap 
 *                  between line and polygon.
 ******************************************/
void Draw::overlap_check()
{
    double m = (P2.y - P1.y) / ((P2.x - P1.x) + 0.00000006);
    if(std::any_of(polygon.begin(), polygon.end(), [m, P1 = this->P1](cv::Point p){ return p.y > (m * (p.x - P1.x) + P1.y); })
    && std::any_of(polygon.begin(), polygon.end(), [m, P1 = this->P1](cv::Point p){ return p.y < (m * (p.x - P1.x) + P1.y); }))
    {
        has_overlap = true;
    }
    else
    {
        has_overlap = false;
    }
}