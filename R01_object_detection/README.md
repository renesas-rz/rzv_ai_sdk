# Object Detection

## Application: Overview
This application is designed to detect objects in the capture image of MIPI Camera Module and displays the result on HDMI screen.

This software could be useful in a variety of settings, such as retail stores, museums, and events.  
The AI model used for the sample application is [YOLOV3](https://arxiv.org/pdf/1804.02767.pdf).

## Application: Requirements

#### Hardware Requirements
- RZ/V2L Evaluation Board Kit
    - RZ/V2L Board
    - MIPI Camera Module (Google Coral Camera)
    - USB cable
- HDMI monitor : Display the application.
- micro HDMI to HDMI cable : Connect HDMI monitor and RZ/V2L Board.
- SD Card : Used as filesystem.
- USB Hub : Used for connecting USB Mouse and USB Keyboard to the board.
- USB Mouse : Used for HDMI screen control.
- USB Keyboard : Used for terminal input.
>**Note:** All external devices will be attached to the board and does not require any driver installation (Plug n Play Type)

Connect the hardware as shown below.  

<img src=./img/hw_conf.jpg width=550>   

##### Notes
1. To see which port to be connected, refer to [Hardware Requirements and Setup](https://github.com/renesas-rz/rzv_ai_applications/tree/develop#hardware-requirements-and-setup).  
2. When using the keyboard connected to RZ/V2L Evaluation Board, the keyboard layout and language are fixed to English.

## Application: Build Stage

>**Note:** User can skip to the next stage (deploy) if they don't want to build the application. All pre-built binaries are provided.

This project expects the user to have completed [Getting Startup Guide](https://renesas-rz.github.io/rzv_ai_sdk/getting_started.html) provided by Renesas. 

After completion of the guide, the user is expected of following things.
- The board setup is done.
- SD card is prepared.
- The docker container of `rzv2l_ai_sdk_image` is running on the host machine.

>**Note:** Docker environment is required for building the sample application. 


#### Application File Generation
1. On your host machine, copy the repository from the GitHub to the desired location. 
    1. It is recommended to copy/clone the repository on the `data` folder which is mounted on the `rzv2l_ai_sdk_container` docker container as shown below. 
    ```sh
    cd <path_to_data_folder_on_host>/data
    git clone https://github.com/renesas-rz/rzv_ai_sdk.git
    ```
    > Note 1: Please verify the git repository url if error occurs

    > Note 2: This command will download whole repository, which include all other applications, if you have already downloaded the repository of the same version, you may not need to run this command.
    
2. Run (or start) the docker container and open the bash terminal on the container.  
Here, we use the `rzv2l_ai_sdk_container` as the name of container created from  `rzv2l_ai_sdk_image` docker image.  
    > Note that all the build steps/commands listed below are executed on the docker container bash terminal.  

3. Set your clone directory to the environment variable.  
    ```sh
    export PROJECT_PATH=/drp-ai_tvm/data/rzv_ai_sdk
    ```
3. Go to the application source code directory.  
    ```sh
    cd ${PROJECT_PATH}/R01_object_detection/src
    ```
4. Build the application by following the commands below.  
    ```sh
    mkdir -p build && cd build
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
    make -j$(nproc)
    ```
5. The following application file would be genarated in the `${PROJECT_PATH}/R01_object_detection/src/build` directory
- object_detection


## Application: Deploy Stage
For the ease of deployment all the deployables file and folders for RZV2L are provided on the [exe](./exe) folder.

|File | Details |
|:---|:---|
|licecnses | License information of AI model. <br>Not necessary for running application. |
|yolov3_onnx | Model object files for deployment.<br>Pre-processing Runtime Object files included. |
|coco-lables-2014_2017.txt | Label list for Object Detection. |
|object_detection | application file. |

1. Follow the steps below to deploy the project on RZV2L Board. 
    1. Run the commands below to download the `R01_object_detection_deploy_tvm-v111.so` from [Release v2.00](https://github.com/renesas-rz/rzv_ai_sdk/releases/tag/v2.00/)
    ```
    cd ${PROJECT_PATH}/R01_object_detection/exe/yolov3_onnx
    wget https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v2.00/R01_object_detection_deploy_tvm-v111.so
    ```
    2. Rename the `R01_object_detection_deploy_tvm-v111.so` to `deploy.so`.
    ```
    mv R01_object_detection_deploy_tvm-v111.so deploy.so
    ```
    3. Copy the following files to the `/home/root/tvm` directory of the rootfs (SD Card) for RZV2L Board.
        -  All files in [exe](./exe) directory. (Including `deploy.so` file.)
        -  `object_detection` application file if you generated the file according to [Application File Generation](#application-file-generation)
    4. Check if `libtvm_runtime.so` is there on `/usr/lib64` directory of the rootfs (SD card) on RZ/V2L board.

2. Folder structure in the rootfs (SD Card) would look like:
```sh
├── usr/
│   └── lib64/
│       └── libtvm_runtime.so
└── home/
    └── root/
        └── tvm/ 
            ├── yolov3_onnx/
            │   ├── preprocess
            │   ├── deploy.json
            │   ├── deploy.params
            │   └── deploy.so
            ├── coco-labels-2014_2017.txt
            └── object_detection
```
>**Note:** The directory name could be anything instead of `tvm`. If you copy the whole `exe` folder on the board. You are not required to rename it `tvm`.

## Application: Run Stage
1. On RZ/V2L Board terminal, go to the `tvm` directory of the rootfs.
```sh
cd /home/root/tvm
```

2. Run the application.
```sh
./object_detection
```
3. Following window shows up on HDMI screen.  

    <img src=./img/objectdetection.png width=350>   

    On application window, following information is displayed.  
    - Camera capture  
    - Object Detection result (Bounding boxes, class name and score.)  
    - Processing time  
        - Total AI Time: Sum of all processing time below.  
        - Inference: Processing time taken for AI inference.  
        - PreProces: Processing time taken for AI pre-processing.  
        - PostProcess: Processing time taken for AI post-processing.<br>(excluding the time for drawing on HDMI screen).  
        
4. To terninate the application, switch the application window to the terminal with using `Super(windows key)+Tab` and &nbsp;press ENTER key on the terminal of RZ/V2L Board.


## Application: Configuration 
### AI Model
- YOLOv3: [Darknet](https://pjreddie.com/darknet/yolo/)  
Dataset: [COCO](https://cocodataset.org/#home)  
Input size: 1x3x416x416  
Output1 size: 1x13x13x255  
Output2 size: 1x26x26x255  
Output3 size: 1x52x52x255   

### AI inference time
The AI inference time is around 430 msec.

### Processing

|Processing | Details |
|:---|:---|
|Pre-processing | Processed by DRP-AI. |
|Inference | Processed by DRP-AI and CPU. |
|Post-processing | Processed by CPU. |

## License
For AI model, see `exe/licenses` directory.  
