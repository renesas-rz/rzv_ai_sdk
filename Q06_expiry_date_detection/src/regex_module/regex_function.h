#ifndef REGEX_FUNCTION_H
#define REGEX_FUNCTION_H

#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <boost/regex.hpp>

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