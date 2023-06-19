#include "date_check.h"

/* Constructor */
DateChecker::DateChecker() {
    monthMap = {
        {"JAN", 1}, {"FEB", 2}, {"MAR", 3}, {"APR", 4}, {"MAY", 5}, {"JUN", 6},
        {"JUL", 7}, {"AUG", 8}, {"SEP", 9}, {"OCT", 10}, {"NOV", 11}, {"DEC", 12}
    };
}

// Function to get the current year, month, and day as integers
void DateChecker::getCurrentDate(int& currentYear, int& currentMonth, int& currentDay) {
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    struct std::tm* currentTimeStruct = std::localtime(&currentTimeT);
    currentYear = currentTimeStruct->tm_year + 1900;
    currentMonth = currentTimeStruct->tm_mon + 1;
    currentDay = currentTimeStruct->tm_mday;
}


// Function to convert year, month, and day strings to integers
void DateChecker::convertToDate(const std::string& year, const std::string& month, const std::string& day, 
                                int& targetYear, int& targetMonth, int& targetDay) {
    
    /* Year */
    if (year.length()>0)
        std::istringstream(year) >> targetYear;
    
    /* Month */
    if (month.length()>0)
    {
        if (month.length() == 2 && month[0] == '0') 
        {
            // Remove leading zero if month is "08" or "09"
            std::string monthNoZero = month.substr(1);
            std::istringstream(monthNoZero) >> targetMonth;
        }
        else if (month.length() > 2 )
        {
            std::string targetMonthUpper = month;
            std::transform(targetMonthUpper.begin(), targetMonthUpper.end(), targetMonthUpper.begin(), ::toupper);
            targetMonth = monthMap[targetMonthUpper];
        
        } 
        else 
        {
            std::istringstream(month) >> targetMonth;
        }
    }

    /* Day*/
    if (day.length()> 0 )
    {
        if (day.length() == 2 && day[0] == '0') 
        {
            // Remove leading zero if month is "08" or "09"
            std::string monthNoZero = month.substr(1);
            std::istringstream(monthNoZero) >> targetMonth;
        }
        else 
        {
            std::istringstream(day) >> targetDay;
        }
    }   
    
}

// Function to check if the specified date has passed the current date
bool DateChecker::is_expired(int& currentYear, int& currentMonth, int& currentDay, int& targetYear, int& targetMonth, int& targetDay) {

    /* Check for expiry date */
    if (targetYear < currentYear) {
        return true;
    } 
    else if (targetYear > currentYear) 
    {
        return false;
    } 
    else 
    {
        if (targetMonth < currentMonth) {
            return true;
        } else if (targetMonth > currentMonth) {
            return false;
        } else {
            return targetDay < currentDay;
        }
    }
}


bool DateChecker::isLeapYear(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int DateChecker::getDaysInMonth(int month, int year) 
{
    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year))
        return 29;
    else
        return daysInMonth[month - 1];
}

int DateChecker::calculateDaysRemaining(const std::string& year, const std::string& month, const std::string& day) 
{
    int daysRemaining = 0;

    int currentYear, currentMonth, currentDay;

    getCurrentDate(currentYear, currentMonth, currentDay);
    
    int targetYear = -1, targetMonth = -1, targetDay = -1;

    /* Covert to integer for the target year */
    convertToDate(year, month, day, targetYear, targetMonth, targetDay);

    /* Handle empty data */
    if (targetYear == -1)
        targetYear = currentYear ; 
    
    if (targetDay == -1) 
        targetDay = 1 ;
    
    if (targetMonth == -1)
        targetMonth = currentMonth ;

    /* if the expiry is in range */
    if (is_expired(currentYear,  currentMonth,  currentDay,  targetYear,  targetMonth,  targetDay))
    {
        return -1;
    }
    else 
    { 
        if (currentYear == targetYear && currentMonth == targetMonth) {
        // Current year and month are the same as the target year and month
        return targetDay - currentDay;
        
        }

        // Calculate the days remaining in the current year
        if (currentYear == targetYear) {
            /* Get days with respect to next month to target month */
            for (int month = currentMonth + 1; month <= targetMonth; ++month) {
                daysRemaining += getDaysInMonth(month, currentYear);
            }

            /* calculate days in current month and reduce the current day to get the remaining day*/
            daysRemaining += getDaysInMonth(currentMonth, currentYear) - currentDay;
            /* Add the target days remaining for the target month */
            daysRemaining += targetDay;
        } 
        else 
        {
            /* Calculate the days remaining in the current year */ 
            for (int month = currentMonth + 1; month <= 12; ++month) {
                daysRemaining += getDaysInMonth(month, currentYear);
            }
            /* calculate days in current month and reduce the current day to get the remaining day*/
            daysRemaining += getDaysInMonth(currentMonth, currentYear) - currentDay;

            // Calculate the days in the intermediate years (if any)
            for (int year = currentYear + 1; year < targetYear; ++year) {
                daysRemaining += isLeapYear(year) ? 366 : 365;
            }

            // Calculate the days in the target year up to the target date
            for (int month = 1; month < targetMonth; ++month) {
                daysRemaining += getDaysInMonth(month, targetYear);
            }
            daysRemaining += targetDay;
        }
            
        return daysRemaining;
    }

    
}