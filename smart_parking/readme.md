# Parking Slot Detection
## Overview
The Parking Slot Detection software is an advanced tool that helps users to detect whether a parking slot is empty or occupied. 
With this software, users can easily draw parking slots and detect their status in real-time.

The software comes with an intuitive user interface that allows users to easily draw parking slots with just a few clicks. 
Once the parking slots are drawn, the software uses advanced algorithms (using custom CNN model) to detect the status of each slot, whether it is vacant or occupied.

With this software, users can monitor parking areas such as parking lots, garages, or on-street parking spaces in real-time. 
It provides an accurate and efficient way to manage parking spaces, helping to reduce congestion and improve traffic flow.


Average FPS -200/slot 

Total FPS - 200/(num of slots)
```sh
eg) 10slots available,

FPS - 200/10 ->20
```
> **Note:** The FPS may change based on the FPS of the input video.

## Requirments


#### Hardware Requirement
- RZ/V2L board
- USB camera (no driver installation) connected to board
- USB mouse (no driver installation) connected to board
- USB Hub (no driver installation) connected to board
- HDMI monitor connected to board

#### Software Requirement 
- Ubuntu 20.04
- OpenCV 4.x
- C++11 or higher

## Building Application

## BUILDING APPLICATION


**NOTE:** This project expects the user to have completed

* the Board Set Up,
* SD Card Preparation steps
* AI SDK Set Up steps mentioned in the RZV2L_AI_SDK_Instruction_guide. After this step docker image amd container will be created.
* Docker environment is required for building the sample application.
* Copy the src directory from this GitHub to the data directory (mounted directory for created docker container) created at the 3rd Step of AI SDK Set Up.


### Application File Generation

Build the application on docker environment by following the steps below
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

`parkinglot_detection` application file would be genarated in the src/build directory.


## Deploying the project
	

Follow the steps mentioned below to deploy the project on RZV2L Board.

* Copy the genarted parkinglot_detection application file to the home/root/tvm directory of the SD Card prepared
  for RZV2L board.
* Copy the libtvm_runtime.so to usr/lib64 directory of the SD card RZV2L board.
* Run the application in the terminal of the RZV2L board using the command,

```sh
./parkinglot_detection <videofile_name.mp4>
```
for inference from video. 

>**Note:** By default, the application will take inference from WebCam.


>**Note:** For the videofile to get executed, ensure that the video file is present inside the home/root/tvm directory of the SD Card prepared.


#### Folder Structure in the board

```
├── usr/
│   └── lib64/
│       └── libtvm_runtime.so
└── home/
    └── root/
        └── tvm/
            ├── parkingmodel_onnx/
            │   ├── deploy.json
            │   ├── deploy.params
            │   └── deploy.so
            ├── sample.mp4
            └── parkinglot_detection
```
## Application Details

#### Model Details


The model used is the custom CNN model. 
/model_parking.png
```python
        Layer (type)               Output Shape         Param #
================================================================
            Conv2d-1           [-1, 32, 26, 26]             896
         MaxPool2d-2           [-1, 32, 13, 13]               0
            Conv2d-3           [-1, 64, 11, 11]          18,496
         MaxPool2d-4             [-1, 64, 5, 5]               0
            Conv2d-5            [-1, 128, 3, 3]          73,856
           Flatten-6                 [-1, 1152]               0
            Linear-7                    [-1, 2]           2,306
================================================================
Total params: 95,554
Trainable params: 95,554
Non-trainable params: 0
----------------------------------------------------------------
Input size (MB): 0.01
Forward/backward pass size (MB): 0.30
Params size (MB): 0.36
Estimated Total Size (MB): 0.67

```
#### Run the application
- The application consists of two buttons when the application is run. 

Edit Slots and Run Inference

- First click on edit the slots button to add the slots on the parking slots.
- Now you will see 2 other buttons. `add slot` and `remove slots`
- To add the slot, press `add slot` button. 
- Now when you see the camera screen, 
- simply press and hold the mouse left click on the screen to start drawing the bounding boxes
- release the click to finish drawing boxes.
- You can draw multiple bounding boxes using the above 2 steps
- After you have drawn the slots, press `esc` key to go to the home screen
- Click on the run inference button







