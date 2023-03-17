# Footfall Counter

## Overview
This application is designed to track and count the number of people entering a designated boundary line,
while simultaneously reducing the count for those exiting the boundary line.

Additionally, the application 
has the ability to measure the time spent by a particular person within a specified region of interest.

This software could be useful in a variety of settings, such as retail stores, museums, and events,
where managers need to monitor and analyze traffic flow and customer behavior.

The AI model used for the sample application is [TinyYoloV3](https://arxiv.org/pdf/1804.02767.pdf).

**NOTE:** This sample application can be used to track different objects, like animal, car, etc. The list of objects that can be tracked are provided in [coco labels txt](./exe/coco-labels-2014_2017.txt) file. 

**Demo video :** 



https://user-images.githubusercontent.com/126070033/223024685-540114e5-a871-470c-b2f8-a3cd0ce070bb.mp4



## Requirements

#### Hardware Requirements
- RZ/V2L Evaluation Board Kit
- USB camera 
- HDMI monitor with resolution 1280x720 
- micro HDMI to HDMI cable 
- SD Card/NFS (for file system)
>**Note:** All external devices will be attached to the board and does not require any driver installation (Plug n Play Type)
#### Software Requirements
- Ubuntu 20.04
- OpenCV 4.x
- C++11 or higher 
- [Boost C++ libraries](https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source) 
- [Eigen linear algebra library](https://eigen.tuxfamily.org/index.php?title=Main_Page)


## Building Application

**Note:** This project expects the user to have completed [Getting Startup Guide]() provided by Renesas. 

After completion of the guide, the user is expected of following things.
- the Board Set Up and booted. 
- SD Card (or NFS) Prepared 
- The docker image amd container for drp_ai_tvm running on host machine.
- libtvm_runtime.so file 

>**Note:** Docker environment is required for building the sample application. 


#### Application File Generation
- Copy the repository from the GitHub to the desired location.
```sh
export PROJECT_PATH=<path_to_the_cloned_directory>
```
```sh
cd $PROJECT_PATH/Footfall_Counter/
```
- Download the boost tar file
```sh
wget https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.bz2
```
- extract tar file to the desired location 
```sh
tar -xvf boost_1_81_0.tar.bz2
```
- copy the boost files to the `src/include` folder of the 
```sh
cp -r boost_1_81_0/boost src/include/
```

- Now copy this src folder to the data directory (mounted directory for created `drp_ai_tvm` docker container)

- Run the bash terminal of the docker container 
- Go to the `src` directory which was copied earlier.
- Now build the application on docker environment by following the steps below
```sh
cd src
```
```sh
mkdir -p build && cd build
```
```sh
cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
```
```sh
make -j$(nproc)
```
The following application file would be genarated in the `src/build` directory
- object_tracker


## Deploying the Application

For the ease of deployment all the deployables file and folders for RZV2L are provided on the [exe](./exe) folder.

|File | Details |
|:---|:---|
|preprocess_tvm_v2l/ | Pre-processing Runtime Object files. |
|tinyyolov3_onnx | compiled model for RZV2L.|
|coco-lables-2014_2017.txt | Label list for Object Detection. |
|config.ini | user input config for line, region and object |
|object_tracker | application file. |


Follow the steps mentioned below to deploy the project on RZV2L Board. 
* At the `home/root/tvm` directory of the rootfs (SD Card/NFS) for RZV2L board.
   * Copy the genarted `object_tracker` application file 
   * Copy the `preprocess_tvm_v2l` directory
   * Copy the config.ini file
   * Copy the coco-labels-2014_2017.txt file
   * Copy the `tinyyolov3_onnx` directory

* Copy the libtvm_runtime.so to usr/lib64 directory of the rootfs (SD card/NFS) RZV2L board.

* For Running the application,
  * Change the values in config.ini as per the requirements. Detailed explanation of the config.ini file is given at below section.
  * Run the application in the terminal of the RZV2L board using the command,
```sh
./object_tracker
```
Folder structure in the prepared SD Card would look like:
```sh
├── usr/
│   └── lib64/
│       └── libtvm_runtime.so
└── home/
    └── root/
        └── tvm/ 
            ├── tinyyolov3_onnx/
            │   ├── deploy.json
            │   ├── deploy.params
            │   └── deploy.so
            ├── preprocess_tvm_v2l
            ├── coco-labels-2014_2017.txt
            ├── config.ini
            └── object_tracker

```
>**Note:** The directory name could be anything instead of `tvm`. If you copy the whole `exe` folder on the board. You are not required to rename it `tvm`.

## Application configuration 

###### Explanation of the `config.ini` file 

The file contains three sections: [**line**], [**region**], and [**tracking**].

>**Note:** The x,y coordintes are ranged from [0,0] to [img_height, img_width]. The img_height and img_width depends on the camera capture resolution. This sample application is tested on 640x480 image.

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

>**Note:**  As per recent development status, the application have been tested for 100 numbers of people on the certain region without any error occuring, so if the use cases are expected for the number of people on the certain region to be less than 100, there is no need for code modification.

- Currently for storing the person id and the time spent on the region of interest [ROI] is stored on the board memeory as key-value pair. As board memory consumption is limited, this procedure could be moved to the Database/Cache which could be hosted on the cloud or host machine.

- Customers can install SQL Database/Cache on the cloud or host-machine. 

- After each sec the application can call the API for inserting the data on the DB, if not present. and show the time taken for the persons in the ROI

- When the person goes out of the ROI, the application can call the API to remove the person data from the DB and cache.
