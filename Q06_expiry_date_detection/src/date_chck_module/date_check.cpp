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
                                int& inputYear, int& inputMonth, int& inputDay) {
    
    /* Year */
    if (year.length()>0)
        std::istringstream(year) >> inputYear;
    
    /* Month */
    if (month.length()>0)
    {
        if (month.length() == 2 && month[0] == '0') 
        {
            // Remove leading zero if month is "08" or "09"
            std::string monthNoZero = month.substr(1);
            std::istringstream(monthNoZero) >> inputMonth;
        }
        else if (month.length() > 2 )
        {
            std::string inputMonthUpper = month;
            std::transform(inputMonthUpper.begin(), inputMonthUpper.end(), inputMonthUpper.begin(), ::toupper);
            inputMonth = monthMap[inputMonthUpper];
        
        } 
        else 
        {
            std::istringstream(month) >> inputMonth;
        }
    }

    /* Day*/
    if (day.length()> 0 )
    {
        if (day.length() == 2 && day[0] == '0') 
        {
            // Remove leading zero if month is "08" or "09"
            std::string monthNoZero = month.substr(1);
            std::istringstream(monthNoZero) >> inputMonth;
        }
        else 
        {
            std::istringstream(day) >> inputDay;
        }
    }   
    
}

// Function to check if the specified date has passed the current date
bool DateChecker::is_expired(int& currentYear, int& currentMonth, int& currentDay, int& inputYear, int& inputMonth, int& inputDay) {

    /* Check for expiry date */
    if (inputYear < currentYear) {
        return true;
    } 
    else if (inputYear > currentYear) 
    {
        return false;
    } 
    else 
    {
        if (inputMonth < currentMonth) {
            return true;
        } else if (inputMonth > currentMonth) {
            return false;
        } else {
            return inputDay < currentDay;
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
    
    int inputYear = -1, inputMonth = -1, inputDay = -1;

    convertToDate(year, month, day, inputYear, inputMonth, inputDay);

    /* Handle empty data */
    if (inputYear == -1)
        inputYear = currentYear ; 
    
    if (inputDay == -1) 
        inputDay = 1 ;
    
    if (inputMonth == -1)
        inputMonth = currentMonth ;

    /* if the expiry is in range */
    if (is_expired(currentYear,  currentMonth,  currentDay,  inputYear,  inputMonth,  inputDay))
    {
        return -1;
    }
    else 
    {
        // Calculate the days remaining in the current year
        for (int month = currentMonth + 1; month <= 12; ++month) {
            daysRemaining += getDaysInMonth(month, currentYear);
        }
        daysRemaining += getDaysInMonth(currentMonth, currentYear) - currentDay;

        // Calculate the days in the intermediate years (if any)
        for (int year = currentYear + 1; year < inputYear; ++year) {
            daysRemaining += isLeapYear(year) ? 366 : 365;
        }

        // Calculate the days in the input year up to the input date
        for (int month = 1; month < inputMonth; ++month) {
            daysRemaining += getDaysInMonth(month, inputYear);
        }
        daysRemaining += inputDay;

        return daysRemaining;
    }

    
}