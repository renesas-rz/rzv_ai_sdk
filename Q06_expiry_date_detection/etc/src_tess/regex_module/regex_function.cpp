#include "regex_function.h"

/**
 * @brief Create a regex dict object
 * To store combiled regex object, 
 * removing the need to recompile every time for input string
 * 
 * @return std::map<boost::regex, std::string> 
 */
std::map<boost::regex, std::string> create_regex_dict() {
    
    // regex string wrt year, month, day
    std::string yr_rgx = R"((?<year>\d{2}|\d{4})?)"; // YYYY 
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

    std::cout << "Regex dictionary updated" << std::endl;

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
            result.year = match["year"].str();
            result.month = match["month"].str();
            result.day = match["day"].str();
            break;
        }    
    }

    return result;
    
}

