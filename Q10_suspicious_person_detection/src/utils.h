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
/* Prevents the header file from being included multiple times. */
#ifndef UTILS
#define UTILS

/* Includes necessary header files. */
#include <iostream>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <chrono>
#include <dirent.h>
#include <cstring>

/* Defines constants that are used in the code. */
#ifndef BITS_PER_LONG
#define BITS_PER_LONG (sizeof(long) * 8)
#endif

#ifndef EV_REL
#define EV_REL 0x02
#endif

#ifndef EV_MAX
#define EV_MAX 0x1F
#endif

/*  Declares a class called devices. */
class devices
{
    private:
        /* Initializes variables to track the duration between mouse clicks. */
        std::chrono::high_resolution_clock::time_point t1;
        std::chrono::high_resolution_clock::time_point t2;
        std::chrono::high_resolution_clock::time_point t3;
        std::chrono::high_resolution_clock::time_point t4;

        int duration        = 0;
        int duration_sc     = 0;
        int duration_cd     = 0;

        const int tm_difference     = 200;
        const int tm_clk_difference = 190; 

        bool last_click     = false;
        bool first_click    = false;
        bool second_click   = false;

        /* Finds the path to the mouse event device. */
        std::string find_mouse_event(void);
    public:
        /* Detects mouse clicks. */
        int detect_mouse_click(void);
};

#endif