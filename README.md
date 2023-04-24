# RZ/V2L AI Applications 

## Overview
This repository consists of the various sample AI applications that are implemented on the RZ/V2L evaluation board kit.\
Each application is provided in their respective folder alongside the respective `readme.md` file to operate the application.

## Hardware Requirements and Setup

Users need some additional hardware setup for executing the sample application. 
Each hardware requirements are specified in the respective `readme.md` of the sample applications.

Here it is specified how to connect those hardware equipment to the RZ/V2L Evaluation Board Kit.

###### Lists of hardware equipments required
- RZ/V2L Evaluation Board Kit
    - RZ/V2L Board
    - USB Serial Cable
    - MIPI Camera Module (Google Coral Camera)
- USB Camera 
- USB Mouse 
- USB Keyboard
- USB Hub 
- HDMI monitor for the board display
- micro HDMI to HDMI cable [for connecting to the board display]
- USB C type Power cable
- SD card [more than 16 GB] 

The connection ports are mentioned as 


<img src=./git_images/rzv2l_connection.JPG width="420">

The number information is present as:
1. Power connection port (USB Type-C) to the RZ/V2L evaluation board kit
2. Power ON/OFF button
3. Board Reset button
4. Serial connection port for connecting Host PC and the board
5. Micro HDMI port to connect the HDMI Display to the board
6. USB port to connect the USB Hub/USB device to the board
7. SD Card Port
8. Ethernet port  

#### Board Setup
- Connect power supply to the board at terminal `1`.
- Connect serial port cable between host PC and the board at terminal `4`.
- Connect micro HDMI cable to terminal `5` and the other end of the cable to the display
- Connect USB Hub at terminal `6`
    - Connect USB Camera, USB Mouse, USB Keyboard to the USB Hub
- Connect SD Card at terminal `7` (required for SD card file system)
- Connect ethernet at terminal `8` (optional)

#### Additional Requirements

For building the sample applications
- Linux Host PC with more than 100 GB free space is required.
- Ubuntu 20.04 LTS
- OpenCV 4.x
- C++11 or higher



## Startup Guide

The users are mandate to follow the [startup guide](https://renesas-rz.github.io/rzv_ai_sdk/getting_started.html) provided by the Renesas, before building the sample application.
After completion of the startup guide, users are expected to have
- Completed the bootup procedure of RZ/V2L Evaluation board kit
- `rzv2l_ai_sdk_image` docker container running on the host machine. This docker container will contain RZ/V2L sdk and tvm environment.
    >Note: The docker container is required for building the sample applications. Users can skip this, if they want to use the pre-built binaries.
- Necessary Hardware equipments

## Sample Application list
The sample applications already developed for RZ/V2L Evaluation Board Kit are listed as:

### 1. Footfall Counter 

This sample application [Footfall Counter](./Q01_footfall_counter) will count the number of persons entering the certain boundaries. There is added functionality of calculation time taken for people on the certain region of interest.\
Both the boundary line and the area of interest are decided by the user and can be set inside the config file.

### 2. Face Authentication

This sample application [Face Authentication](./Q02_face_authentication) will recognize the face of the person and verify the same with images stored in the database.\
This application could be used for passport verification at the airport.

### 3. Smart Parking Solutions

This sample application [Smart Parking](./Q03_smart_parking) will detect the available parking slots from the real time camera feed using computer vision advanced algorithms.\
The application could be used to get the available parking slots information from the certain parking area in real time.

## Operating the sample application
- Each sample application folder have their respective `readme.md` file to modify and run the sample application.

## References