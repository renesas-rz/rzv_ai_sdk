# FOOTFALL COUNTER USING TINYYOLOV3

## Overview
This application is designed to track and count the number of people entering a designated boundary line,
while simultaneously reducing the count for those exiting the boundary line.

Additionally, the application 
has the ability to measure the time spent by a particular person within a specified region of interest.

This software could be useful in a variety of settings, such as retail stores, museums, and events,
where managers need to monitor and analyze traffic flow and customer behavior.

**Demo video :** 



https://user-images.githubusercontent.com/126070033/223024685-540114e5-a871-470c-b2f8-a3cd0ce070bb.mp4



## Requirements

- RZ V2L Board
- Ubuntu 20.04
- OpenCV 4.x
- C++11 or higher
- TinyYoloV3 Model
- Boost C++ libraries
- Eigen linear algebra library


## Building Application

**NOTE:** This project expects the user to have completed 
- the Board Set Up, 
- SD Card Preparation steps 
- AI SDK Set Up steps mentioned in the [RZV2L_AI_SDK_Instruction_guide](). After this step docker image amd container will be created. 
- Docker environment is required for building the sample application. 
- Copy the src directory from this GitHub to the data directory (mounted directory for created docker container) created at the 3rd Step of AI SDK Set Up.

### Application File Generation

Download the boost files to the src folder using the below command

```sh
wget https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.bz2
```
Build the application on docker environment by following the steps below
```sh
cd src
```
```sh
mkdir -p build
```
```sh
cd build
```
```sh
cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
```
```sh
make -j$(nproc)
```
`object_tracker` application file would be genarated in the src/build directory.


## Deploying the Application

For the ease of deployment all the deployables file and folders for RZV2L are provided on the "rzv2l_board_deploy" folder.

|File | Details |
|:---|:---|
|preprocess_tvm_v2l/ | Pre-processing Runtime Object files. |
|tinyyolov3_onnx | compiled model for RZV2L.|
|coco-lables-2014_2017.txt | Label list for Object Detection. |
|config.ini | user input config for line, region and object |
|libtvm_runtime.so | runtime library for rzv2l. |
|object_tracker | application file. |


Follow the steps mentioned below to deploy the project on RZV2L Board. 

    * Copy the genarted object_tracker file to the home/root/tvm directory of the SD Card prepared
      for RZV2L board.
    * Copy config.ini file to the home/root/tvm directory of the SD Card prepared
      for RZV2L board.
    * Copy the preprocess_tvm_v2l directory to the home/root/tvm directory of the SD Card prepared
      for RZV2L board.
    * Copy the coco-labels-2014_2017.txt to the home/root/tvm directory of RZV2L board.
    * Copy the libtvm_runtime.so to usr/lib64 directory of the SD card RZV2L board.
    * Change the values in config.ini as per the requirements. Detailed explanation of the config.ini file is 
      given at below section.
    * Run the application in the terminal of the RZV2L board using the command,
	./object_tracker

Folder structure in the prepared SD Card would look like:
```sh
├── usr/
│   └── lib64/
│       └── libtvm_runtime.so
└── home/
    └── root/
        └── tvm/
            ├── output_directory/
            │   ├── deploy.json
            │   ├── deploy.params
            │   └── deploy.so
            ├── preprocess_tvm_v2l
            ├── coco-labels-2014_2017.txt
            ├── config.ini
            └── object_tracker

```

## Application configuration 

Explanation of the `config.ini` file 

The file contains three sections: [**line**], [**region**], and [**tracking**].

- **NOTE:** The x,y coordintes are ranged from [0,0] to [img_height, img_width]. The img_height and img_width depends on the camera capture resolution. This sample application is tested on 640x480 image.

- The [**line**] section contains four key-value pairs that define the coordinates of the boundary line to be drawn.\
The x1, y1, x2, and y2 values correspond to the x and y coordinates of the boundary line's
starting and ending points.

- The [**region**] section contains five key-value pairs, which defines the Region of Interest.\
The n value indicates the number of points that define a region, followed by x and y coordinates
for each point.\
The region is defined by connecting these points in the order they are listed.

- The [**tracking**] section contains two key-value pairs.\
The conf value is a confidence threshold used for object tracking, and the kmin value is the minimum number of keypoints required for tracking.\
The object tracked here is of class "Person", it can be changed to other classes present on the coco labels.


To modify the configuration settings, edit the values in this file using VI Editor, from the RZV2L Board.

### Time Tracking Backend Integration

- **Note:**  As per recent development status, the application have been tested for 100 numbers of people on the certain region without any error occuring, so if the use cases are expected for the number of people on certain region to be less than 100, there is no need for code modification.

- Currently for storing the person id and the time spent on the region of interest [ROI] is stored on the board memeory as key-value pair. As board memory consumption is limited, this procedure could be moved to the Database/Cache as well on the cloud or host machine.

- Customers can install SQL Database/Cache on the cloud or host-machine. 

- After each sec the application can call the API for inserting the data on the DB, if not present. and show the time taken for the persons in the ROI

- When the person goes out of the ROI, the application can call the API to remove the person data from the DB and cache.
