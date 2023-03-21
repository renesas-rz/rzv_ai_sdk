# RZ/V2L AI Applications 

## Overview
This repo consists of the various sample AI application that are implemented on the RZV2L evaluation board kit. 

## Hardware Requirements and Setup

Users need some additional hardware setup for executing the sample application. 
Each hardware requirements are specified in the respective `readme` of the sample applications.
Here it is specified how to connect those hardware equipment to the RZV2L Evaluation Board Kit.

###### Lists of hardware equipments required
- RZ/V2L Evaluation Board Kit
- USB camera 
- USB mouse 
- USB Keyboard
- USB Hub 
- HDMI monitor
- micro HDMI to HDMI cable [for connecting to the board display]
- USB C type Power cable
- SD card [more than 16 GB] (only required for the file system) 
    >Note: User can use NFS also on host PC.


The connection ports are mentioned as 


<img src=./git_images/rzv2l_connection.JPG width="420">

The number info is present as:
1. Power connection port to the RZV2L evaluation board kit
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
- Connect ethernet at terminal `8` (required for NFS)

#### Software Requirements

For building the sample application
- Ubuntu 20.04
- OpenCV 4.x
- C++11 or higher

## Startup Guide
The users are mandate to follow the [startup guide]() provided by the Renesas.
After completion of the startup guide, users are expected to have
- Bootup RZV2L Evaluation board kit
- tvm_drp_ai docker container running on the host machine.
    >Note: The docker container is required for building the sample applications. Users can skip this, if they want to use the pre-built binaries.
- Necessary Hardware equipments

## Sample Application list
The sample applications already developed for RZ/V2L Evaluation Board Kit are listed as:

### 1. Footfall Counter 

This sample application [Footfall Counter](./Footfall_Counter) will count the number of persons entering the certain boundaries. There is added functionality of calculation time taken for people on the certain region of interest.\
Both the boundary line and the area of interest are decided by the user and can be set inside the config file.

### 2. Face Authentication

This sample application [Face Authentication](./face_authentication) will recognize the face of the person and verify the same with images stored in the database.\
This application could be used for passport verification at the airport.

### 3. Smart Parking Solutions
