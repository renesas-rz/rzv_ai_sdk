# Parking Slot Detection
## Application: Overview
The Parking Slot Detection software is an advanced tool that helps users to detect whether a parking slot is empty or occupied. 
With this software, users can easily draw parking slots and detect their status in real-time.

The software comes with an intuitive user interface that allows users to easily draw parking slots with just a few clicks.

Once the parking slots are drawn, the software uses advanced algorithms (using custom CNN model) to detect the status of each slot, whether it is vacant or occupied.

With this software, users can monitor parking areas such as parking lots, garages, or on-street parking spaces in real-time. 
It provides an accurate and efficient way to manage parking spaces, helping to reduce congestion and improve traffic flow.

[**Demo Video**](https://renesasgroup.sharepoint.com/:v:/r/sites/QuestGlobalxRenesasRZAIAppDev/Shared%20Documents/General/Delivarables_Storage/smart_parking/sample_output.avi?csf=1&web=1&e=GEdqCZ)

Average FPS: 200/slot 

Total FPS: 200/(num of slots)
```
example) 10 slots available,

FPS - 200/10 ->20
```
> **Note:** The FPS may change based on the FPS of the input video.

## Requirments

#### Hardware Requirement
- RZ/V2L board
- USB camera 
- USB mouse 
- USB Keyboard
- USB Hub 
- HDMI monitor 
>**Note:** All external devices will be attached to the board and does not require any driver installation (Plug n Play Type)
#### Software Requirement 
- Ubuntu 20.04 
- OpenCV 4.x
- C++11 or higher

## Application: Build Stage

>**Note:** User can skip to the next stage (deploy) if they don't want to build the application. All pre-built binaries are provided.

**Note:** This project expects the user to have completed [Getting Startup Guide](../README.md#startup-guide) provided by Renesas. 

After completion of the guide, the user is expected of following things.
- the Board Set Up and booted. 
- SD Card (or NFS) Prepared 
- The docker image amd container for drp_ai_tvm running on host machine.
- libtvm_runtime.so file 

>**Note:** Docker environment is required for building the sample application. 


#### Application: File Generation
- Copy the repository from the GitHub to the desired location.
```sh
export PROJECT_PATH=<path_to_the_cloned_directory>
```
```sh
cd $PROJECT_PATH/smart_parking/
```
Now copy this src folder to the data directory (mounted directory for the created `drp_ai_tvm` docker container)

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
- parkinglot_detection


## Application: Deploy Stage

For ease of deployment all the files required for deployment are provided on the [deploy folder](./exe)	

|File | Details |
|:---|:---|
|parkingmodel_onnx | Model object files for deployment. |
|parking_bg.jpg | Front image for the application. |
|sample.mp4 | user sample input video. |
|parkinglot_detection | application file. |

Follow the steps mentioned below to deploy the project on RZ/V2L evaluation Board.

* At the home/root/tvm directory of the rootfs (SD Card/NFS) for RZ/V2L evaluation board.
   * Copy the genarted parkinglot_detection application file 
   * Copy the parking_bg.jpg image
   * Copy the parkingmodel_onnx folder

* Copy the libtvm_runtime.so to usr/lib64 directory of the rootfs (SD card/NFS) RZV2L board.
 

>**Note:** By default, the application will take inference from WebCam.

>**Note:** For the videofile to get executed, ensure that the video file is present inside the home/root/tvm directory of the rootfs of the board.

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
            |── parkinglot_detection
            └── parking_bg.jpg
            
```
## Application: Runtime Stage

* Run the application in the terminal of the RZV2L board using the command,
   * go to the `tvm` directory of the rootfs
   ```sh
   cd <path_to_deployables>/
   ```
   * for inference from video 
   ```sh 
   ./parkinglot_detection <videofile_name.mp4>
   ```
   * for inference from the camera feed 
   ```sh
   ./parkinglot_detection
   ```
#### GUI for running the application
- The application consists of two buttons when the application is run. 
   - Edit Slots and Start Inference
   
     <img src=./images/parking_app_front.JPG width="420">
   
- First click on edit the slots button to add the slots on the parking slots.
- Now you will see 2 other buttons. `add slot` and `remove slots`

     <img src=./images/park_add_remove.JPG width="360" height="240">

- To add the slot, press `add slot` button. 
- Now when you see the camera screen, 
- simply press and hold the mouse left click on the screen to start drawing the bounding boxes
- release the click to finish drawing boxes.
- You can draw multiple bounding boxes using the above 2 steps

     <img src=./images/slot_add.JPG width="480">

- After you have drawn the slots, press `esc` key to go to the home screen
- Click on the run inference button
- To close the running application, press `esc` key.
- You can similiarly remove the added slots as well

     <img src=./images/remove_slots.jpg width="360" height="240">

## Application: Specifications

#### Model Details

The model used is the custom CNN model. 

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

The network diagram will be as follows: 
<img src=./model_info/model_parking.png width="360">

#### Dataset 
The dataset used is the custom datasets. 
Please contact on this email to access the dataset:
- Shyam.N@quest-global.com

###### AI inference
The AI inference time is 4-7 msec per slot. 

## References







