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
* File Name    : regex_function.cpp
* Version      : v1.00
* Description  : RZ/V2L AI SDK Sample Application: Expiry Date Extraction
***********************************************************************************************************************/

/*****************************************
* Includes
******************************************/
#include "regex_function.h"

/**
 * @brief Create a regex dict object
 * To store compiled regex object, 
 * removing the need to recompile every time for input string
 * 
 * @return std::map<boost::regex, std::string> 
 */
std::map<boost::regex, std::string> create_regex_dict() {
    
    // regex string wrt year, month, day
    std::string yr_rgx = R"((?<year>\d{4})?)"; // YYYY 
    std::string yr_rgx_2dig = R"((?<year>\d{2})?)"; // YY
    std::string mnth_rgx = R"((?<month>(?:[a-zA-Z]{3}|0?[1-9]|1[0-2]))?)"; // MMM
    std::string day_rgx = R"((?<day>[0123]?\d{1})?)"; // DD 
    std::string sprt_rgx = R"([\W_]*)"; // zero or more special characters
    std::string mnth_rgx_ws = R"((?:[\W_]+(?<month>0?[1-9]|1[0-2]|[a-zA-z]{3}))?)";// - MM(with separator)
    std::string day_rgx_ws = R"((?:[\W_]+(?<day>[0123]?\d))?)";// -DD 
    std::string yr_rgx_ws = R"((?:[\W_]+(?<year>\d{2}|\d{4}))?)"; // -YYYY or -YY

    // defining regex patterns
    std::vector<std::string> regex_patterns = {
        R"(^)" + day_rgx + mnth_rgx_ws + sprt_rgx + yr_rgx_ws + R"($)", // DD-MMM-YY
        R"(^)" + yr_rgx_2dig + mnth_rgx_ws + day_rgx_ws + R"($)", // YY-MMM-DD
        R"(^)" + mnth_rgx +  day_rgx_ws + yr_rgx_ws + R"($)", // MMM-DD-YY
        R"(^)" + yr_rgx  + mnth_rgx_ws + day_rgx_ws + R"($)", // YYYY-MMM-DD
        R"(^)" + day_rgx + mnth_rgx_ws +  yr_rgx_ws + R"($)", // DD-MMM-YYYY
        R"(^)" + day_rgx + R"((th|st|nd|rd))"  + mnth_rgx_ws  + yr_rgx_ws + R"($)", // DDst-MMM-YYYY
        R"(^)" + mnth_rgx +  day_rgx_ws +  yr_rgx_ws + R"($)", // MMM-DD-YYYY
    };

    // defining date formats
    std::vector<std::string> date_formats = {
        "DD-MMM-YY",
        "YY-MMM-DD",
        "MMM-DD-YY",
        "YYYY-MMM-DD",
        "DD-MMM-YYYY",
        "DDst-MMM-YYYY",
        "MMM-DD-YYYY",
    };

    // initializing regex dictionary containing key as regex object and date-format as string
    std::map<boost::regex, std::string> regex_dict;

    // loop and fill up
    for (std::size_t i = 0; i < regex_patterns.size(); ++i) {
        // insert key-value to the map after compiling the patterns    
        regex_dict.emplace(boost::regex(regex_patterns[i]), date_formats[i]);
    }

    printf("Regex dictionary updated \n");

    return regex_dict;
}

/**
 * @brief Get the year-month-day object
 * 
 * @param regex_dict 
 * @param inp_str 
 */
ymd_struct get_yymmddd(const std::map<boost::regex, std::string>& regex_dict,
                   std::string inp_str){
    // store the result on the structure

    ymd_struct result;
    result.matched = false;
    
    for (const auto& pair : regex_dict) {

        // extract pairs 
        const auto& regex_obj = pair.first;
        const auto& date_format = pair.second;
        // store match objects if matched with compiled regex object
        boost::smatch match;
        if (boost::regex_match(inp_str, match, regex_obj)) {
            result.matched=true;
            result.format=date_format;
            if (match["year"].str().length()==2)
            {
                result.year = "20" + match["year"].str();
            } 
            else 
            {
                result.year = match["year"].str();
            }
            
            result.month = match["month"].str();
            result.day = match["day"].str();
            break;
        }    
    }

    return result;
    
}