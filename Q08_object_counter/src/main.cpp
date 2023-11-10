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
 * File Name    : main.cpp
 * Version      : 1.0
 * Description  : RZ/V2L AI SDK Use-case Application for object counting.
 ***********************************************************************************************************************/

/*****************************************
 * Includes
 ******************************************/
#include "recognize/recognize_base.h"
#include "recognize/yolo/tvm_drpai_yolo.h"
#include "cereal/cereal.hpp"

std::string mode;
/* RecognizeBase base class Object */
static RecognizeBase *g_rc;
bool DEFAULT_MIPI_CAMERA = true;
std::string DEFAULT_MODE = "COCO";
int32_t main(int32_t argc, char *argv[])
{
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> ini_values = CommonFunc::config_read("app_conf.ini");
    if (argc > 1)
    {
        mode = argv[1];
        if (ini_values.find(mode) == ini_values.end())
        {
            std::cout << mode << " OPTION INVALID" << std::endl;
            mode = DEFAULT_MODE;
            std::cout << "Default mode selected" << std::endl;
        }
        else
        {
            std::cout << mode << " OPTION VALID" << std::endl;
        }
    }
    else
    {
        mode = DEFAULT_MODE;
        std::cout << "Default mode selected" << std::endl;
    }
    if (argc > 2)
    {
        std::string cam = argv[2];
        std::cout << cam << std::endl;
        if(cam == "USB")
        {
            DEFAULT_MIPI_CAMERA = false;
        }
    }
    /* creates a new instance RecognizeBase class */
    g_rc = new RecognizeBase();
    /*initialize recognize model using tiny-yolov3 */
    g_rc->initialize(new TVM_YOLO_DRPAI(MODE_TVM_TINYYOLOV3_DRPAI, ini_values[mode]));
    /*start the recognition using tiny-yolov3 model*/
    g_rc->recognize_start();
}
