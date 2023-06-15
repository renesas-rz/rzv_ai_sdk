#include "text_processing.h"

/**
 * @brief remove white spaces from start and end
 * 
 * @param char_arr 
 * @return char* 
 */
std::string trim_white_spc(char* char_arr) {
    // Remove leading whitespace
    while (isspace(*char_arr)) {
        ++char_arr;
    }
    
    // If the string is empty after removing leading whitespace
    if (*char_arr == '\0') {
        return char_arr;
    }
    
    // Remove trailing whitespace
    char* end = char_arr + strlen(char_arr) - 1;
    while (end > char_arr && isspace(*end)) {
        --end;
    }
    
    // Null-terminate the string after removing trailing whitespace
    *(end + 1) = '\0';
    
    return std::string(char_arr);
}