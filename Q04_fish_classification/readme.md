# Fish Classification Application

## Application: Overview
The fish classification application allows to classify between 9 different fish species.

0. "Black Sea Sprat",
1. "Gilt-Head Bream",
2. "Horse Mackerel",
3. "Red Mullet",
4. "Red Sea Bream",
5. "Sea Bass",
6. "Shrimp",
7. "Striped Red Mullet",
8. "Trout",

The application could be used to classify fishes during fish farming, or from certain areas on the sea/river through drones, etc.  

It has 4 modes of running.

1. Using MIPI Camera
2. Using Image as input
3. Using Video as input
4. Input from Websocket

#### Demo Video:
The Demo videos for the fish classification application can be found at

- [Image & Video Mode](https://renesasgroup.sharepoint.com/:v:/r/sites/QuestGlobalxRenesasRZAIAppDev/Shared%20Documents/General/Delivarables_Storage/fish_classification/fish_classification_IMAGE_VIDEO.mp4?csf=1&web=1&e=lmpZLT)

- [Camera Mode](https://renesasgroup.sharepoint.com/:v:/r/sites/QuestGlobalxRenesasRZAIAppDev/Shared%20Documents/General/Delivarables_Storage/fish_classification/fish_classification_CAMERA.mp4?csf=1&web=1&e=38bEU5)

- [Web App Mode](https://renesasgroup.sharepoint.com/:v:/r/sites/QuestGlobalxRenesasRZAIAppDev/Shared%20Documents/General/Delivarables_Storage/fish_classification/fish_classification_ws_demo.mp4?csf=1&web=1&e=mvRVCu)

## Application: Requirements

#### Hardware Requirements
- RZ/V2L Evaluation Board Kit
    - Coral Camera
- USB Mouse
- USB Keyboard
- USB Hub
- HDMI monitor & Cable

#### Software Requirements
- Ubuntu 20.04
- OpenCV 4.x
- C++11 or higher

#### Python Package Installation (Optional)
> Note: Required only for Host Machine for running the application through Websocket
- Flask
- Flask-SocketIO
- numpy
- opencv-python
- python-socketio
- Werkzeug

	
## Application: Build Stage

>**Note:** User can skip to the next stage (deploy) if they don't want to build the application. All pre-built binaries are provided.

**Note:** This project expects the user to have completed [Getting Startup Guide](../README.md#startup-guide) provided by Renesas. 

After completion of the guide, the user is expected of following things.
- The Board Set Up and booted. 
- SD Card Prepared 
- The docker image amd container for `rzv2l_ai_sdk_image` running on host machine.

>**Note:** Docker container is required for building the sample application. By default the Renesas will provide the container named as `rzv2l_ai_sdk_container`. Please use the docker container name as assigned by the user when building the container.

#### Application: File Generation

1. Copy the repository from the GitHub to the desired location. 
    1. It is recommended to copy/clone the repository on the `data` folder which is mounted on the `rzv2l_ai_sdk_container` docker container. 
    ```sh
    cd <path_to_data_folder_on_host>
    git clone https://github.com/renesas-rz/rzv_ai_sdk.git
    ```
   >Note: Please verify the git repository url if error occurs.
2. Run the docker container and open the bash terminal on the container.

> Note: All the build steps/commands listed below are executed on the docker container terminal.

3. Assign path to the `data` directory mounted on the `rzv2l_ai_sdk_container` docker container

```sh
export PROJECT_PATH=/drp_ai_tvm/data/
```

4. Go to the `src` directory of the application

```sh
cd ${PROJECT_PATH}/rzv_ai_sdk/Q04_fish_classification/fish_application/src/
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
- fish_classification


## Application: Deploy Stage

#### Mode: Board Deployment
##### Folder Structure in the board
```sh
/
└── home
    └── root
        └── tvm
            ├── fish_classification_model
            │   ├── deploy.json
            │   ├── deploy.params
            │   └── deploy.so
            │  
            └── fish_classification

```

#### Mode: Websocket Application (Optional)
- Copy the fish web application [folder](./fish_web_app_exe/) to the host machine.
- Copy the generated fish_classification application to the copied folder.

```sh
cd fish_web_app_exe
```
```python
pip install -r requirements.txt
```

## Application: Runtime Stage

##### Mode: Camera Input
- The application takes input from MIPI Coral Camera.
- Run the MIPI camera script, placed in `/home/root/` directory
```sh
./v4l2-init.sh
```
> Note: The output resolution depends on the input camera resolution, which could be modified from the script, before running it. Default resolution:1920x1080
```sh 
./fish_classification CAMERA 
```

##### Mode: Image Input
```sh
./fish_classification IMAGE <img_file_path>
```
> Note: Tested with image file format `.png` and `.jpg`.

<img src=./images/fish_image_mode.JPG width="480">

##### Mode: Video Input

```sh 
./fish_classification VIDEO <video_file_path>
```
> Note: Tested with video file format `.mp4` and `.avi`.


##### Mode: Websocket (Optional)
* Get IP config of the RZ/V2L Board, Run the command on the RZ/V2L board terminal.
```sh
ifconfig
```

* On Host machine
```sh
cd fish_web_app_exe
python3 app.py
```

1. Local server will start running, visit the IP address in any of the browser. 

2. Enter the IP address of the board.

    <img src=./images/fish_web_app_step1.JPG width="480">

3. If it is successfully connected to board, it will redirect to prediction page.
    
    <img src=./images/fish_web_app_step2.JPG width="480">

4. Select fish image press Send Photo. 

    <img src=./images/fish_web_app_step3.JPG width="480">

    <img src=./images/fish_web_app_step4.JPG width="480">

### Application: Termination
- Press `Esc` key to terminate the application.


## Application: Specifications

#### Model Details

```python
==========================================================================================
Layer (type:depth-idx)                   Output Shape              Param #
==========================================================================================
├─Sequential: 1-1                        [-1, 9]                   --
|    └─Conv2d: 2-1                       [-1, 32, 62, 62]          896
|    └─ReLU: 2-2                         [-1, 32, 62, 62]          --
|    └─BatchNorm2d: 2-3                  [-1, 32, 62, 62]          64
|    └─Conv2d: 2-4                       [-1, 64, 60, 60]          18,496
|    └─ReLU: 2-5                         [-1, 64, 60, 60]          --
|    └─BatchNorm2d: 2-6                  [-1, 64, 60, 60]          128
|    └─MaxPool2d: 2-7                    [-1, 64, 20, 20]          --
|    └─Conv2d: 2-8                       [-1, 128, 18, 18]         73,856
|    └─ReLU: 2-9                         [-1, 128, 18, 18]         --
|    └─MaxPool2d: 2-10                   [-1, 128, 9, 9]           --
|    └─Conv2d: 2-11                      [-1, 256, 7, 7]           295,168
|    └─ReLU: 2-12                        [-1, 256, 7, 7]           --
|    └─Flatten: 2-13                     [-1, 12544]               --
|    └─Linear: 2-14                      [-1, 9]                   112,905
|    └─Softmax: 2-15                     [-1, 9]                   --
==========================================================================================
Total params: 501,513
Trainable params: 501,513
Non-trainable params: 0
Total mult-adds (M): 108.63
==========================================================================================
Input size (MB): 0.05
Forward/backward pass size (MB): 5.80
Params size (MB): 1.91
Estimated Total Size (MB): 7.76
==========================================================================================

```

#### Dataset 
This dataset contains 9 different seafood types.
The dataset includes gilt head bream, red sea bream, sea bass, red mullet, horse mackerel,
black sea sprat, striped red mullet, trout, shrimp image samples.

[Dataset-Link](https://www.kaggle.com/datasets/crowww/a-large-scale-fish-dataset)

#### AI Inference time
Total AI inference time (Pre-processing + AI model inference) - 28ms (35FPS)


