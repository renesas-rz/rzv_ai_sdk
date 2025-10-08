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
#ifndef REGEX_FUNCTION_H
#define REGEX_FUNCTION_H

#include <boost/regex.hpp>
//#include "../comm_define.h"

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


struct ymd_struct {
    bool matched;
    std::string format;
    std::string year;
    std::string month;
    std::string day;

};

std::map<boost::regex, std::string> create_regex_dict();
ymd_struct get_yymmddd(const std::map<boost::regex, std::string>& regex_dict,std::string inp_str);


#endif