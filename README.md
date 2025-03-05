# RZ/V AI Applications 

## Overview
This repository consists of the various functions of AI applications that are implemented on the RZ/V evaluation board kit.\
Each application is provided in their respective folder alongside the respective `readme.md` file to operate the application.

## Hardware Requirements and Setup

Users need some additional hardware setup for executing the application. 
Each hardware requirements are specified in the respective `readme.md` of the applications.

### Supported board
- [RZ/V2L Evaluation Board Kit](#rzv2l-evaluation-board-kit)  
- [RZ/V2H Evaluation Board Kit](#rzv2h-evaluation-board-kit)  
- [RZ/V2N Evaluation Board Kit](#rzv2n-evaluation-board-kit)  

### RZ/V2L Evaluation Board Kit
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
7. SD Card Port for eMMC Bootloader
8. SD Card Port for eSD Bootloader
9. MIPI Camera connection port
10. Ethernet port  

#### Board Setup
- Connect power supply to the board at terminal `1`.
- Connect serial port cable between host PC and the board at terminal `4`.
- Connect micro HDMI cable to terminal `5` and the other end of the cable to the display
- Connect USB Hub at terminal `6`
    - Connect USB Camera, USB Mouse, USB Keyboard to the USB Hub
- Connect SD Card at terminal `7` for for eMMC Bootloader or terminal `8` for eSD Bootloader (required for SD card file system)
- Connect MIPI Camera at port `9` (if required)
- Connect ethernet at terminal `10` (optional)

#### Additional Requirements

For building the applications
- Linux Host PC with more than 100 GB free space is required.
- Ubuntu 20.04 LTS
- OpenCV 4.x
- C++11 or higher

### RZ/V2H Evaluation Board Kit
Please refer to [Getting Started](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started) for the details of RZ/V2H Evaluation Board Kit.

### RZ/V2N Evaluation Board Kit
Please refer to [Getting Started](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started) for the details of RZ/V2N Evaluation Board Kit.

## Startup Guide

The users are mandate to follow the [Getting Started](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started) provided by the Renesas, before building the application.
After completion of the startup guide, users are expected to have
- Completed the bootup procedure of RZ/V Evaluation board kit
- Docker container running on the host machine. This docker container will contain AI SDK and DRP-AI TVM environment.
    >Note: The docker container is required for building the applications. Users can skip this, if they want to use the pre-built binaries.
- Necessary Hardware equipments

## Functions of AI Applications
The applications already developed for RZ/V Evaluation Board Kit are listed as:

### 1. Footfall Counter 

The [Footfall Counter](./Q01_footfall_counter) application will count the number of persons entering the certain boundaries. There is added functionality of calculation time taken for people on the certain region of interest.\
Both the boundary line and the area of interest are decided by the user and can be set inside the config file.

### 2. Face Authentication

The [Face Authentication](./Q02_face_authentication) application will recognize the face of the person and verify the same with images stored in the database.\
This application could be used for passport verification at the airport.

### 3. Smart Parking Solutions

The [Smart Parking](./Q03_smart_parking) application will detect the available parking slots from the real time camera feed using computer vision advanced algorithms.\
The application could be used to get the available parking slots information from the certain parking area in real time.

### 4. Fish Classification 
The [Fish Classification](./Q04_fish_classification) application will classify the species of fishes using either image, video or camera feed.\
The application can be used at fish markets or super market to identify the species of the fish. 

### 5. Suspicious Activity Recognition
The [Suspicious activity classification](./Q05_suspicious_activity) application will take a camera or video input and classify whether the activity is suspicious or non-suspicious.
Some user-config like `FRAME_INTERVAL`, `BUFFER_SIZE`, etc can be passed through command line during execution. The detail explanation is provided in the application `readme.md`.\
This application could be used for security purpose in government or corporate buildings. 

### 6. Expiry Date Detection 
The [Expiry Date Detection](./Q06_expiry_date_detection) application will extract the expiry date from the image or the camera feed and can show the remaining days for the product expiry.\
The application could be used at medical or grocery store to extract the expiry date information on the product with less manual intervention.

### 7. Plant Disease Classification 
The [Plant disease classification](./Q07_plant_disease_classification) application will classify the diseases for certain plants.\
This application could be used for farm monitoring and plant disease prevention and cure.

### 8. Object Counter 
The [Object Counter](./Q08_object_counter) application is a user-friendly and efficient generic software tool that can be used to create custom counting applications for any scenario.

### 9. Crack Segmentation
The [Crack Segmentation](./Q09_crack_segmentation) application is used for the task of automatically identifying and segmenting cracks in images of surfaces.

### 10. Suspicious Person Detection
The [Suspicious Person Detection](./Q10_suspicious_person_detection) application is a software used to automatically detect suspicious and non-suspicious people in real-time camera streams.

### 11. Fish Detection
The [Fish Detection](./Q11_fish_detection) application is a software used to automatically detect fishes in real-time camera streams.

### 12. Yoga Pose Estimation
The [Yoga Pose Estimation](./Q12_yoga_pose_estimation) application is a software used to automatically identify and analyze the key points of a person's body while they are performing yoga poses.

## Operating the application
- Each application folder have their respective `readme.md` file to modify and run the application.

## References