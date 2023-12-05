# Fish Classification Application

## Application: Overview
The fish classification application allows to classify between 31 different fish species.
[Label List](./src/fish_class_list.txt)

The application could be used to classify fishes during fish farming, or from certain areas on the sea/river through drones, etc.  

It has 4 modes of running.

1. Using MIPI Camera
2. Using USB Camera
3. Using Image as input
4. Using Video as input
5. Input from Websocket [Link to Readme](./etc/readme.md)

#### Demo:

<img src = "./images/FishClassification.gif" width="480" height="320">



## Application: Requirements

#### Hardware Requirements
- RZ/V2L Evaluation Board Kit
- MIPI Camera
- USB Camera
- USB Mouse
- USB Keyboard
- USB Hub
- HDMI monitor & Micro HDMI Cable


[Hardware Setup Steps](https://github.com/renesas-rz/rzv_ai_sdk/#hardware-requirements-and-setup)

#### Software Requirements for building the application
- Ubuntu 20.04
- OpenCV 4.x
- C++11 or higher

## Application: Build Stage

>**Note:** User can skip to the next stage (deploy) if they don't want to build the application. All pre-built binaries are provided.

**Note:** This project expects the user to have completed [Getting Started Guide](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started) provided by Renesas. 

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
   >Note 1: Please verify the git repository url if error occurs.

   >Note 2: This command will download whole repository, which include all other applications. if you have already downloaded the repository of the same version, you may not need to run this command.

2. Run the docker container and open the bash terminal on the container.

> Note: All the build steps/commands listed below are executed on the docker container terminal.

3. Assign path to the `data` directory mounted on the `rzv2l_ai_sdk_container` docker container

```sh
export PROJECT_PATH=/drp-ai_tvm/data/
```

4. Go to the `src` directory of the application

```sh
cd ${PROJECT_PATH}/rzv_ai_sdk/Q04_fish_classification/src/
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

For the ease of deployment all the deployable files and folders for RZ/V2L are provided on the [exe](./exe) folder.

|File | Details |
|:---|:---|
|fish_classification_model | Model object files for deployment. |
|fish_class_list.txt | Label list for Fish classes |
|Bangus.jpg | sample image |
|output.mp4 | sample video |
|fish_classification | application file. |

Follow the steps mentioned below to deploy the project on RZ/V2L Evaluation Board Kit. 
1. Copy following files to the `/home/root/tvm` directory of the rootfs (on SD Card) for RZ/V2L Evaluation Board Kit.
   1. The files present in [exe](./exe) directory, which are listed in the table above.
   2. The generated `fish_classification` application file if the application file is built at [build stage](#application-build-stage)

2. Check if libtvm_runtime.so is there on `/usr/lib64` directory of the rootfs (SD card) RZ/V2L Evaluation Board Kit.

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
            ├── fish_class_list.txt
            ├── Bangus.jpg
            ├── output.mp4
            └── fish_classification

```

>**Note:** The directory name could be anything instead of `tvm`. If you copy the whole `exe` folder on the board. You are not required to rename it `tvm`.

## Application: Runtime Stage

* For running the application, run the commands as shown below on the RZ/V2L Evaluation Board console.
  * Go to the `/home/root/tvm` directory of the rootfs
  ```sh
  cd /home/root/tvm
  ```
##### Mode: MIPI Camera Input
- The application takes input from MIPI Coral Camera.

> Note: The output resolution depends on the input camera resolution, which could be modified from the script, before running it. Default resolution:1920x1080
```sh 
./fish_classification MIPI 
```

##### Mode: USB Camera Input
- The application takes input from USB Camera.

```sh 
./fish_classification USB 
```
##### Mode: Image Input

```sh
./fish_classification IMAGE Bangus.jpg
```
> Note: Tested with image file format `.png` and `.jpg`.


<img src=./images/img_sample.PNG width="480">


##### Mode: Video Input

```sh 
./fish_classification VIDEO output.mp4
```
> Note: Tested with video file format `.mp4` and `.avi`.

### Application: Termination
- Use `Mouse Double Click` to terminate the application.
- Alternatively, to force close the application, switch from the application window to the terminal by pressing Super(windows key)+Tab and press CTRL + C.

## Application: Specifications

#### Model Details

```python
==========================================================================================
Layer (type:depth-idx)                   Output Shape              Param #
==========================================================================================
├─Sequential: 1-1                        [-1, 512, 7, 7]           --
|    └─Conv2d: 2-1                       [-1, 64, 112, 112]        9,408
|    └─BatchNorm2d: 2-2                  [-1, 64, 112, 112]        128
|    └─ReLU: 2-3                         [-1, 64, 112, 112]        --
|    └─MaxPool2d: 2-4                    [-1, 64, 56, 56]          --
|    └─Sequential: 2-5                   [-1, 64, 56, 56]          --
|    |    └─BasicBlock: 3-1              [-1, 64, 56, 56]          73,984
|    |    └─BasicBlock: 3-2              [-1, 64, 56, 56]          73,984
|    |    └─BasicBlock: 3-3              [-1, 64, 56, 56]          73,984
|    └─Sequential: 2-6                   [-1, 128, 28, 28]         --
|    |    └─BasicBlock: 3-4              [-1, 128, 28, 28]         230,144
|    |    └─BasicBlock: 3-5              [-1, 128, 28, 28]         295,424
|    |    └─BasicBlock: 3-6              [-1, 128, 28, 28]         295,424
|    |    └─BasicBlock: 3-7              [-1, 128, 28, 28]         295,424
|    └─Sequential: 2-7                   [-1, 256, 14, 14]         --
|    |    └─BasicBlock: 3-8              [-1, 256, 14, 14]         919,040
|    |    └─BasicBlock: 3-9              [-1, 256, 14, 14]         1,180,672
|    |    └─BasicBlock: 3-10             [-1, 256, 14, 14]         1,180,672
|    |    └─BasicBlock: 3-11             [-1, 256, 14, 14]         1,180,672
|    |    └─BasicBlock: 3-12             [-1, 256, 14, 14]         1,180,672
|    |    └─BasicBlock: 3-13             [-1, 256, 14, 14]         1,180,672
|    └─Sequential: 2-8                   [-1, 512, 7, 7]           --
|    |    └─BasicBlock: 3-14             [-1, 512, 7, 7]           3,673,088
|    |    └─BasicBlock: 3-15             [-1, 512, 7, 7]           4,720,640
|    |    └─BasicBlock: 3-16             [-1, 512, 7, 7]           4,720,640
├─Sequential: 1-2                        [-1, 31]                  --
|    └─AdaptiveConcatPool2d: 2-9         [-1, 1024, 1, 1]          --
|    |    └─AdaptiveMaxPool2d: 3-17      [-1, 512, 1, 1]           --
|    |    └─AdaptiveAvgPool2d: 3-18      [-1, 512, 1, 1]           --
|    └─Flatten: 2-10                     [-1, 1024]                --
|    └─BatchNorm1d: 2-11                 [-1, 1024]                2,048
|    └─Dropout: 2-12                     [-1, 1024]                --
|    └─Linear: 2-13                      [-1, 512]                 524,288
|    └─ReLU: 2-14                        [-1, 512]                 --
|    └─BatchNorm1d: 2-15                 [-1, 512]                 1,024
|    └─Dropout: 2-16                     [-1, 512]                 --
|    └─Linear: 2-17                      [-1, 31]                  15,872
==========================================================================================
Total params: 21,827,904
Trainable params: 21,827,904
Non-trainable params: 0
Total mult-adds (G): 3.71
==========================================================================================
Input size (MB): 0.57
Forward/backward pass size (MB): 54.38
Params size (MB): 83.27
Estimated Total Size (MB): 138.21
```

#### Dataset 


'Bangus', 'Big Head Carp', 'Black Spotted Barb', 'Catfish', 'Climbing Perch', 'Fourfinger Threadfin', 'Freshwater Eel', 'Glass Perchlet', 'Goby', 'Gold Fish', 'Gourami', 'Grass Carp', 'Green Spotted Puffer', 'Indian Carp', 'Indo-Pacific Tarpon', 'Jaguar Gapote', 'Janitor Fish', 'Knifefish', 'Long-Snouted Pipefish', 'Mosquito Fish', 'Mudfish', 'Mullet', 'Pangasius', 'Perch', 'Scat Fish', 'Silver Barb', 'Silver Carp','Silver Perch', 'Snakehead', 'Tenpounder', 'Tilapia'

Dataset properties:
The total number of images: 13,304 image
Training set size: 8791 images
Test set size: 2751 images
The number of classes: 1760

[Dataset-Link](https://www.kaggle.com/datasets/markdaniellampa/fish-dataset)

#### AI Inference time
Total AI inference time (Pre-processing + AI model inference) - 65ms (15 FPS)

| Training Accuracy   |Validation Accuracy   |  Testing Accuracy |
|---|---|---|
|  98.2 | 97.7  | 94.5  |

