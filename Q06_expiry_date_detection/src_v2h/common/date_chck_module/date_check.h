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
/***********************************************************************************************************************
* File Name    : date_check.h
* Version      : v1.00
* Description  : RZ/V2H AI SDK Sample Application: Expiry Date Extraction
***********************************************************************************************************************/

#ifndef DATE_CHECK_H
#define DATE_CHECK_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include <algorithm>

#include <string>
#include <unordered_map>

class DateChecker {
public:
    DateChecker();
    bool is_expired(int& currentYear, int& currentMonth, int& currentDay, int& inputYear, int& inputMonth, int& inputDay);
    int calculate_days_left(std::string& year, std::string& month, std::string& day);

private:

    void get_curr_date(int& currentYear, int& currentMonth, int& currentDay);
    void convert_date_int(std::string& year, std::string& month, std::string& day, int& inputYear, int& inputMonth, int& inputDay);
    std::unordered_map<std::string, int> monthMap;
    int get_days_in_mnth(int month, int year);
    bool is_leap_year(int year);
    
    
};

#endif