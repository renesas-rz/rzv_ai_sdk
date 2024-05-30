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
* File Name    : date_check.cpp
* Version      : v1.00
* Description  : RZ/V2H AI SDK Sample Application: Expiry Date Extraction
***********************************************************************************************************************/

/*****************************************
* Includes
******************************************/

#include "date_check.h"

/* Constructor */
DateChecker::DateChecker() {
    monthMap = {
        {"JAN", 1}, {"FEB", 2}, {"MAR", 3}, {"APR", 4}, {"MAY", 5}, {"JUN", 6},
        {"JUL", 7}, {"AUG", 8}, {"SEP", 9}, {"OCT", 10}, {"NOV", 11}, {"DEC", 12}
    };
    
}

// Function to get the current year, month, and day as integers
void DateChecker::get_curr_date(int& curr_year, int& curr_month, int& curr_day) {
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    struct std::tm* currentTimeStruct = std::localtime(&currentTimeT);
    curr_year = currentTimeStruct->tm_year + 1900;
    curr_month = currentTimeStruct->tm_mon + 1;
    curr_day = currentTimeStruct->tm_mday;
}


// Function to convert year, month, and day strings to integers
void DateChecker::convert_date_int(std::string& year, std::string& month, std::string& day, 
                                int& target_year, int& target_month, int& target_day) {
    
    /* Year */
    if (year.length()>0)
    {
        std::istringstream(year) >> target_year;
    }
    /* Month */
    if (month.length()>0)
    {
        if (month.length() == 2 && month[0] == '0') 
        {
            // Remove leading zero if month is "08" or "09"
            std::string monthNoZero = month.substr(1);
            std::istringstream(monthNoZero) >> target_month;
        }
        else if (month.length() > 2 )
        {
            std::string target_monthUpper = month;
            std::transform(target_monthUpper.begin(), target_monthUpper.end(), target_monthUpper.begin(), ::toupper);
            target_month = monthMap[target_monthUpper];
        
        } 
        else 
        {
            std::istringstream(month) >> target_month;
        }
    }

    /* Day*/
    if (day.length()> 0 )
    {
        if (day.length() == 2 && day[0] == '0') 
        {
            // Remove leading zero if month is "08" or "09"
            std::string dayNoZero = day.substr(1);
            std::istringstream(dayNoZero) >> target_month;
        }
        else 
        {
            std::istringstream(day) >> target_day;
        }
    }   
    
}

// Function to check if the specified date has passed the current date
bool DateChecker::is_expired(int& curr_year, int& curr_month, int& curr_day, int& target_year, int& target_month, int& target_day) {

    /* Check for expiry date */
    if (target_year < curr_year) {
        return true;
    } 
    else if (target_year > curr_year) 
    {
        return false;
    } 
    else 
    {
        if (target_month < curr_month) {
            return true;
        } else if (target_month > curr_month) {
            return false;
        } else {
            return target_day < curr_day;
        }
    }
}

/**
 * @brief Check whether the year is a leap or not
 * 
 * @param year [int]
 * @return true 
 * @return false 
 */
bool DateChecker::is_leap_year(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * @brief Get days in the month for the corresponding year
 * 
 * @param month 
 * @param year 
 * @return int 
 */
int DateChecker::get_days_in_mnth(int month, int year) 
{
    const int days_in_mnth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && is_leap_year(year))
        return 29;
    else
        return days_in_mnth[month - 1];
}


/**
 * @brief Calculate remaining days 
 * 
 * @param year : target year 
 * @param month : target month
 * @param day : target day 
 * @return int : number of days remaining [-1 if target<current]
 */
int DateChecker::calculate_days_left(std::string& year, std::string& month, std::string& day) 
{
    int days_left = 0; // Not including the current day 

    int curr_year, curr_month, curr_day;

    get_curr_date(curr_year, curr_month, curr_day);
    
    int target_year = -1, target_month = -1, target_day = -1;

    /* Covert to integer for the target year */
    convert_date_int(year, month, day, target_year, target_month, target_day);

    /* Handle empty data */
    if (target_year == -1)
        target_year = curr_year ; // if expiry year is missing, set it to the current one
    
    if (target_day == -1) 
        target_day = 1 ; // if expiry day is missing, taken as 1st of the month 
    
    if (target_month == -1)
        target_month = curr_month ; // if expiry month is missing, set it to the current one

    /* if the expiry is in range */
    if (is_expired(curr_year,  curr_month,  curr_day,  target_year,  target_month,  target_day))
    {
        return -1;
    }
    else 
    { 
        if (curr_year == target_year && curr_month == target_month) {
        // Current year and month are the same as the target year and month
        return target_day - curr_day;
        
        }

        // Calculate the days remaining in the current year
        if (curr_year == target_year) {
            /* Get days with respect to next month till target month */
            for (int month = curr_month + 1; month < target_month; ++month) {
                days_left += get_days_in_mnth(month, curr_year);
            }

            /* calculate days in current month and reduce the current day to get the remaining day*/
            days_left += get_days_in_mnth(curr_month, curr_year) - curr_day;

            /* Add the target days remaining for the target month */
            days_left += target_day;
        } 
        else 
        {
            /* Calculate the days remaining in the current year */ 
            for (int month = curr_month + 1; month <= 12; ++month) {
                days_left += get_days_in_mnth(month, curr_year);
            }
            /* calculate days in current month and reduce the current day to get the remaining day*/
            days_left += get_days_in_mnth(curr_month, curr_year) - curr_day;

            // Calculate the days in the intermediate years (if any)
            for (int year = curr_year + 1; year < target_year; ++year) {
                days_left += is_leap_year(year) ? 366 : 365;
            }

            // Calculate the days in the target year up to the target date
            for (int month = 1; month < target_month; ++month) {
                days_left += get_days_in_mnth(month, target_year);
            }
            days_left += target_day;
        }
            
        return days_left; 
    }

    
}