Parking slot Detection using Custom CNN Model
----------------------------------------

The Parking Slot Detection software is an advanced tool that helps users to detect whether a parking slot is empty or occupied. 
With this software, users can easily draw parking slots and detect their status in real-time.

The software comes with an intuitive user interface that allows users to easily draw parking slots with just a few clicks. 
Once the parking slots are drawn, the software uses advanced algorithms to detect the status of each slot, whether it is vacant or occupied.

With this software, users can monitor parking areas such as parking lots, garages, or on-street parking spaces in real-time. 
It provides an accurate and efficient way to manage parking spaces, helping to reduce congestion and improve traffic flow.


Average FPS -200/slot
Total FPS - 200/(num of slots)

eg) 10slots available,

FPS - 200/10 ->20

Note: The FPS may change based on the FPS of the input video.


REQUIREMENTS
------------
RZ/V2L board
Ubuntu 20.04
OpenCV 4.x
C++11 or higher

BUILDING APPLICATION
--------------------
NOTE: This project expects the user to have completed

* the Board Set Up,
* SD Card Preparation steps
* AI SDK Set Up steps mentioned in the RZV2L_AI_SDK_Instruction_guide. After this step docker image amd container will be created.
* Docker environment is required for building the sample application.
* Copy the src directory from this GitHub to the data directory (mounted directory for created docker container) created at the 3rd Step of AI SDK Set Up.


Application File Generation
-------------------------
Build the application on docker environment by following the steps below
	1. $cd src
	2. $mkdir build
	3. $cd build
	4. cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
	5. make -j$(nproc)

parkinglot_detection application file would be genarated in the src/build directory.

Deploying the project
---------------------	

Follow the steps mentioned below to deploy the project on RZV2L Board.

* Copy the genarted parkinglot_detection application file to the home/root/tvm directory of the SD Card prepared
  for RZV2L board.
* Copy the libtvm_runtime.so to usr/lib64 directory of the SD card RZV2L board.
* Run the application in the terminal of the RZV2L board using the command,
./parkinglot_detection <videofile_name.mp4> for inference from video. By default, the application will take inference from WebCam.

Note: For the videofile to get executed, ensure that the video file is present inside the home/root/tvm directory of the SD Card prepared.


Folder Structure in the board
-----------------------------
/
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


Model Details
----------------
----------------------------------------------------------------
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









