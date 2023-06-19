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
    int calculateDaysRemaining(const std::string& year, const std::string& month, const std::string& day);

private:

    void getCurrentDate(int& currentYear, int& currentMonth, int& currentDay);
    void convertToDate(const std::string& year, const std::string& month, const std::string& day, int& inputYear, int& inputMonth, int& inputDay);
    std::unordered_map<std::string, int> monthMap;
    int getDaysInMonth(int month, int year);
    bool isLeapYear(int year);
    
};

#endif