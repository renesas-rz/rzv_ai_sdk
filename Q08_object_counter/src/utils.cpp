#include "utils.h"

extern bool doubleClick;

int devices::detect_mouse_click(void)
{
    /* Gets the full path to the mouse event device. */
    std::string full_path = find_mouse_event();
    /* Converts the full path to a const char pointer. */
    const char* device_path = full_path.c_str();
    /* Opens the mouse event device file. */
    int fd = open(device_path, O_RDONLY);
    if (fd < 0) 
    {
        std::cerr << "Error opening input device" << std::endl;
        return 1;
    }
    /* Enters a loop to read mouse events. */
    while (true) 
    {
        struct input_event ev;
        /* Reads a mouse event from the device file. */
        ssize_t bytesRead = read(fd, &ev, sizeof(struct input_event));
        /* Checks if the event is a key event and if the key code is for the left or right mouse button. */
        if (bytesRead == sizeof(struct input_event) && ev.type == EV_KEY &&
            (ev.code == BTN_LEFT || ev.code == BTN_RIGHT)) 
        {
            /* Checks if the key is being pressed (value == 1) or released (value == 0). */
            if (ev.value == 0) 
            {
                if(first_click == true)
                {
                    t2 = std::chrono::high_resolution_clock::now();
                    duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    first_click = false;
                }  
                if(second_click == true)
                {
                    t4 = std::chrono::high_resolution_clock::now();
                    duration_sc = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();
                    second_click = false;
                }
                /* If the second click has occurred and the duration between clicks is less than 110 milliseconds,
                   then a double click has been detected. */
                if(duration_cd < tm_clk_difference && duration_cd != 0 && duration < tm_difference 
                && duration != 0 && duration_sc < tm_difference && duration_sc != 0)
                {
                    std::cout<<"[INFO] Double click detected\n";
                    duration            = 0;
                    duration_cd         = 0;
                    duration_sc         = 0;
                    doubleClick         = true;
                    break;
                }
            }
            else if (ev.value == 1) 
            {
                t1 = std::chrono::high_resolution_clock::now();
                if(first_click == false && duration < tm_difference && duration != 0)
                {
                    t3 = std::chrono::high_resolution_clock::now();
                    duration = 0;
                    second_click = true;
                }
                if(second_click == true)
                    duration_cd = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
                first_click = true;
            }
        }
    }
    /* Closes the mouse event device file. */
    close(fd);
    /* Returns 0 if no double click was detected. */
    return 0;
}

std::string devices::find_mouse_event(void) 
{
    /* Path to the directory containing all input devices. */
    const char* inputDirPath = "/dev/input/";
    /* Opens the input directory.*/ 
    DIR* dir = opendir(inputDirPath);
    if (!dir) 
    {
        std::cerr << "Error opening input directory" << std::endl;
        exit(1);
    }
    /* Iterates over all entries in the input directory. */ 
    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) 
    {
        /* Skips entries that start with a dot (i.e., hidden files). */
        if (entry->d_name[0] == '.') 
        {
            continue;
        }
        /* Constructs the full path to the input device. */
        std::string fullPath = inputDirPath + std::string(entry->d_name);
        int fd = open(fullPath.c_str(), O_RDONLY | O_NONBLOCK);
        if (fd < 0) 
        {
            continue;
        }
        /* Checks if the input device has relative axis (e.g., a mouse). */
        if (ioctl(fd, EVIOCGBIT(0, EV_MAX), sizeof(long)*EV_MAX)) 
        {
            unsigned long evBits[EV_MAX];
            ioctl(fd, EVIOCGBIT(0, EV_MAX), evBits);
            /* Returns the path to the device if the EV_REL bit is set (i.e., the device has relative axis). */
            if (evBits[EV_REL / BITS_PER_LONG] & (1 << (EV_REL % BITS_PER_LONG))) 
            {
                close(fd);
                closedir(dir);
                return fullPath;
            }
        }
        /* Closes the input device file. */
        close(fd);
    }
    /* Closes the input directory. */
    closedir(dir);
    /* Prints an error message and exits the program if no mouse device is found. */
    std::cerr << "No mouse device found" << std::endl;
    exit(1);
}
