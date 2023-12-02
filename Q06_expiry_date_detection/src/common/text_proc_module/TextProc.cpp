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
* File Name    : TextProc.cpp
* Version      : v1.00
* Description  : RZ/V2L AI SDK Sample Application: Expiry Date Extraction
***********************************************************************************************************************/

/*****************************************
* Includes
******************************************/
#include "TextProc.h"
#include <iostream>
#include <algorithm>
#include <cctype>

/**
 * @brief remove white spaces from start and end
 * 
 * @param char_arr 
 * @return std::string 
 */
std::string trim_white_spc(char* char_arr) 
{
    std::string ex_string;
    /* Remove leading whitespace */
    while (isspace(*char_arr)) 
    {
        ++char_arr;
    }
    /* If the string is empty after removing leading whitespace */
    if (*char_arr == '\0') {
        return char_arr;
    }
    /* Remove trailing whitespace */
    char* end = char_arr + strlen(char_arr) - 1;
    while (end > char_arr && isspace(*end)) {
        --end;
    }
    /* Null-terminate the string after removing trailing whitespace */
    *(end + 1) = '\0';
    ex_string = std::string(char_arr);
    /* Remove all space from the extracted string */
    ex_string.erase(std::remove_if(ex_string.begin(), ex_string.end(), ::isspace), ex_string.end());
    /* Replace all "O" with "0" in the extracted string */
    std::replace(ex_string.begin(), ex_string.end(),'O','0');
    return ex_string;
}