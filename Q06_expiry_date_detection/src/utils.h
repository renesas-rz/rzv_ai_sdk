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
    public:
        /* Initializes variables to track the duration between mouse clicks. */
        std::chrono::high_resolution_clock::time_point t1;
        std::chrono::high_resolution_clock::time_point t2;
        std::chrono::high_resolution_clock::time_point t3;
        std::chrono::high_resolution_clock::time_point t4;

        int duration        = 0;
        int duration_sc     = 0;
        int duration_cd     = 0;

        /* Mouse button up and down time difference */
        const int tm_difference     = 110;
        /* Mouse button first click and second click time difference */
        const int tm_clk_difference = 190; 

        bool last_click     = false;
        bool first_click    = false;
        bool second_click   = false;

        /* Sets a flag to indicate whether a double click has been detected. */
        bool g_quit_application   = false;

        /* Detects mouse clicks. */
        int detect_mouse_click(void);
        /* Finds the path to the mouse event device. */
        std::string find_mouse_event(void);
        /* function to check USB/MIPI device is connected. */
        std::string query_device_status(std::string device_type);
        /* MIPI cam init */
        void mipi_cam_init(void);
};

#endif