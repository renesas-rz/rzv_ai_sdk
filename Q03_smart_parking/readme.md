# Parking Slot Detection
## Application: Overview
The Parking Slot Detection software is an advanced tool that helps users to detect whether a parking slot is empty or occupied. 
With this software, users can easily draw parking slots and detect their status in real-time.

The software comes with an intuitive user interface that allows users to easily draw parking slots with just a few clicks.

Once the parking slots are drawn, the software uses advanced algorithms (using custom CNN model) to detect the status of each slot, whether it is vacant or occupied.

With this software, users can monitor parking areas such as parking lots, garages, or on-street parking spaces in real-time. 
It provides an accurate and efficient way to manage parking spaces, helping to reduce congestion and improve traffic flow.

It has 3 modes of running.

1. Using MIPI Camera
2. Using USB Camera
3. Using Video as input

### Supported Product  
<table>
    <tr>
      <th>Product</th>
      <th>Supported AI SDK version</th>
    </tr>
    <tr>
      <td>RZ/V2L Evaluation Board Kit (RZ/V2L EVK)</td>
      <td>RZ/V2L AI SDK v5.00</td>
    </tr>
</table>

#### Demo 

<img src = "./images/SmartParking.gif" width="480" height="320">

Average FPS: 200/slot 

Total FPS: 200/(num of slots)
```
example) 10 slots available,

FPS - 200/10 ->20
```
> **Note:** The FPS may change based on the FPS of the input video.

## Application: Requirements

#### Hardware Requirements
- RZ/V2L Evaluation Board Kit
- USB Camera
- MIPI Camera
- USB Mouse
- USB Keyboard (Only required when removing added slots)
- USB Hub
- HDMI Monitor & Cable


[Hardware Setup Steps](https://github.com/renesas-rz/rzv_ai_sdk/#hardware-requirements-and-setup)

>**Note:** All external devices will be attached to the board and does not require any driver installation (Plug n Play Type)
#### Software Requirements 
- Ubuntu 20.04 
- OpenCV 4.x
- C++11 or higher

## Application: Build Stage

>**Note:** User can skip to the [deploy stage](#application-deploy-stage) if they don't want to build the application. All pre-built binaries are provided.

**Note:** This project expects the user to have completed [Getting Startup Guide](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started) provided by Renesas. 

After completion of the guide, the user is expected of following things.
- The Board Set Up and booted. 
- SD Card Prepared 
- The docker image and container for `rzv2l_ai_sdk_image` running on host machine.

>**Note:** Docker container is required for building the sample application. By default the Renesas will provide the container named as `rzv2l_ai_sdk_container`. Please use the docker container name as assigned by the user when building the container.

#### Application: File Generation
1. Copy the repository from the GitHub to the desired location. 
    1. It is recommended to copy/clone the repository on the `data` folder which is mounted on the `rzv2l_ai_sdk_container` docker container. 
    ```sh
    cd <path_to_data_folder_on_host>
    git clone https://github.com/renesas-rz/rzv_ai_sdk.git
    ```
   >Note 1: Please verify the git repository url if error occurs.

   >Note 2: This command will download whole repository, which include all other applications. If you have already downloaded the repository of the same version, you may not need to run this command.

2. Run the docker container and open the bash terminal on the container.

> Note: All the build steps/commands listed below are executed on the docker container terminal.

3. Assign path to the `data` directory mounted on the `rzv2l_ai_sdk_container` docker container

```sh
export PROJECT_PATH=/drp-ai_tvm/data/
```

4. Go to the `src` directory of the application

```sh
cd ${PROJECT_PATH}/rzv_ai_sdk/Q03_smart_parking/src/
```
>**Note:**`rzv_ai_sdk` is the repository name corresponding to the cloned repository. Please verify the repository name if error occurs.
5. Build the application on docker environment by following the steps below

```sh
mkdir -p build && cd build
```
```sh
cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
```
```sh
make -j$(nproc)
```

The following application file would be generated in the `src/build` directory
- parkinglot_detection


## Application: Deploy Stage

For ease of deployment all the files required for deployment are provided on the [exe](./exe) folder.

|File | Details |
|:---|:---|
|parking_model | Model object files for deployment. |
|parking_bg.jpg | Front image for the application. |
|sample.mp4 | User sample input video. |
|parkinglot_detection | Application file. |

Follow the steps mentioned below to deploy the project on RZ/V2L evaluation Board.

* At the home/root/tvm directory of the rootfs (SD Card) for RZ/V2L evaluation board.
   * Copy the files present in [exe](./exe) directory, which are listed in the table above
   * Copy the generated parkinglot_detection application file, if the application file is built at [build stage](#application-build-stage)
   
* Check if libtvm_runtime.so is there on `/usr/lib64/` directory of the rootfs (SD card) RZ/V2L board.


>**Note:** For the video file to get executed, ensure that the video file is present inside the home/root/tvm directory of the rootfs of the board.

#### Folder Structure in the board

```
├── usr/
│   └── lib64/
│       └── libtvm_runtime.so
└── home/
    └── root/
        └── tvm/
            ├── parking_model/
            │   ├── deploy.json
            │   ├── deploy.params
            │   └── deploy.so
            ├── sample.mp4
            |── parkinglot_detection
            └── parking_bg.jpg
            
```
## Application: Runtime Stage

* For running the application, run the commands as shown below on the RZ/V2L Evaluation Board Kit console.
    * Go to the `/home/root/tvm` directory of the rootfs
    ```sh
    cd /home/root/tvm
    ```
   * To run inference from video 

   ```sh 
   ./parkinglot_detection VIDEO <videofile_name.mp4>
   ```

   * To run inference from the MIPI camera feed 

   ```sh
   ./parkinglot_detection MIPI
   ```
   
   * To run inference from the USB camera feed 

   ```sh
   ./parkinglot_detection USB
   ```

#### GUI for running the application

>**Note:** The application GUI is same for either of the sample video or the camera. 

1. The application consists of two buttons when the application is run. 
   - `Edit Slots` and `Start Inference`
   
     <img src=./images/parking_app_front.JPG width="420">
   
2. First click on `Edit Slots` button to add the slots on the parking slots.

   - Now you will see 2 other buttons. `Add Slot` and `Remove Slot`

     <img src=./images/park_add_remove.JPG width="360" height="240">

3. To add the slot, press `Add Slot` button. 
   1. When you see the camera(or the sample video) screen.
   2. The Bounding box needs to be drawn where the user would like to detect the occupancy. 
   3. simply press and hold the mouse left click on the screen to start drawing the bounding boxes
   4. release the click to finish drawing boxes.
   5. Multiple bounding boxes can be drawn

     <img src=./images/slot_add.JPG width="480">

4. After you have drawn the slots, press `Back` button on the window to go to the home screen
5. Click on the `Start inference` button
6. To close the running application, Double click on the window.
7. To remove the added slots
   1. Click on the `Remove Slot` button
   2. Type the parking slot IDs that needs to be removed.
   3. Click on the `Back` button to go to the home screen

     <img src=./images/remove_slots.jpg width="360" height="240">

#### Application: Runtime output details

The runtime application will look something like this 

<img src=./images/smrt_prk_out.JPG width="480">

- Each bounding boxes (BB) are the parking slots drawn by the user
   - Green BB are the empty slots
   - Red BB are the occupied slots
- Each slot identified by the user is assigned some ID. The IDs are assigned in the sequence the BB are drawn.
- `DRP-AI Processing Time(ms)` is also shown in the bottom right corner. 

#### Application: Termination
- Application can be terminated by Double clicking on the window.
- Alternatively, User can force close the application using `CTRL+c` on the board console.

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


<img src=./model_info/model_parking.png width="110" height="480">

#### Dataset 
The dataset used is the custom datasets. 
Please contact on this email to access the dataset:
- Shyam.N@quest-global.com

###### AI inference
The AI inference time is 4-7 msec per slot. 

## FAQs







