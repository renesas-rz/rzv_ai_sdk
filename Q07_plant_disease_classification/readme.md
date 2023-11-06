# Plant leaf disease classification

## Application: Overview
The Plant leaf disease classification application allows to classify between 38 different plant leaf disease/healthy. The developed model is able to recognize 38 different types of plant disease out of 14 different plants. The label list is provided at [`exe/plant_leaf_disease_class.txt`](./exe/plant_leaf_disease_class.txt)


The application could be used to classify plant leaf whether healthy or not in agricultural sector 

It has 4 modes of running.

1. Using MIPI Camera
2. Using USB Camera
2. Using Image as input
3. Using Video as input

#### Demo 

<img src = "./images/plant_leaf_disease.gif" width="480" height="320">


## Application: Requirements

#### Hardware Requirements
- RZ/V2L Evaluation Board Kit
- MIPI Camera 
- USB Camera
- USB Keyboard
- USB Mouse
- USB Hub
- HDMI monitor with resolution 1280x720 
- micro HDMI to HDMI cable 
- SD Card (for file system)

[Hardware Setup Steps](https://github.com/renesas-rz/rzv_ai_sdk/#hardware-requirements-and-setup)

>**Note:** All external devices will be attached to the board and does not require any driver installation (Plug n Play Type)


#### Software Requirements
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

#### Application File Generation
1. Copy the repository from the GitHub to the desired location. 
    1. It is recommended to copy/clone the repository on the `data` folder which is mounted on the `rzv2l_ai_sdk_container` docker container. 
    ```sh
    cd <path_to_data_folder_on_host>
    git clone https://github.com/renesas-rz/rzv_ai_sdk.git
    ```
    > Note 1: Please verify the git repository url if error occurs.

    > Note 2: This command will download whole repository, which include all other applications. if you have already downloaded the repository of the same version, you may not need to run this command.
    
2. Run(or start) the docker container and open the bash terminal on the container.

> Note: All the build steps/commands listed below are executed on the docker container bash terminal.

3. Assign path to the `data` directory mounted on the `rzv2l_ai_sdk_container` docker container

```sh
export PROJECT_PATH=/drp-ai_tvm/data/
```
4. Go to the `src` directory of the application

```sh
cd ${PROJECT_PATH}/rzv_ai_sdk/Q07_plant_disease_classification/src/
```
>**Note:** It is expected that the docker container is able to connect to the internet. If that's not the case, User can use the same command on the host PC to download the file. Make sure you are on the `src` folder present on the mounted `data` directory.

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
- plant_leaf_disease_classify

## Application: Deploy Stage

For the ease of deployment all the deployable files and folders for RZ/V2L are provided on the [exe](./exe) folder.

Follow the steps mentioned below to deploy the project on RZ/V2L Board. 
* At the `/home/root/tvm` directory of the rootfs (on SD Card) for RZ/V2L board.
   * Copy the files present in [exe](./exe) directory, which are listed in the table above.
   * Copy the generated `plant_leaf_disease_classify` application file if the application file is built at [build stage](#application-build-stage)

* Check if libtvm_runtime.so is there on `/usr/lib64` directory of the rootfs (SD card) RZ/V2L board.


Folder structure in the rootfs (SD Card) would look like:

```sh
├── usr/
│   └── lib64/
│       └── libtvm_runtime.so
└── home/
    └── root/
        └── tvm/ 
            ├── plant_dis_onnx/
            │   ├── deploy.json
            │   ├── deploy.params
            │   └── deploy.so
            ├── plant_leaf_disease_class.txt
            ├── plantvid.mp4
            ├── sampleimg.jpg
            └── plant_leaf_disease_classify


```
>**Note:** The directory name could be anything instead of `tvm`. If you copy the whole `exe` folder on the board. You are not required to rename it `tvm`.

## Application: Run Stage

* For running the application, run the commands as shown below on the RZ/V2L Evaluation Board console.
  * Go to the `/home/root/tvm` directory of the rootfs
  ```sh
  cd /home/root/tvm
  ```

##### Mode: MIPI Camera Input
- The application takes input from MIPI Coral Camera.

```sh 
./plant_leaf_disease_classify MIPI 
```

##### Mode: USB Camera Input
- The application takes input from MIPI Coral Camera.

```sh 
./plant_leaf_disease_classify USB 
```

##### Mode: Image Input
```sh
./plant_leaf_disease_classify IMAGE sampleimg.jpg
```
> Note: Tested with image file format `.png` and `.jpg`.


##### Mode: Video Input

```sh 
./plant_leaf_disease_classify VIDEO plantvid.mp4
```
> Note: Tested with video file format `.mp4` and `.avi`.

* The expected output will be the same as shown in the demo video

#### Application: Runtime output details

- The application will classify the whether the plant leaf is healthy or diseased. 

##### Video/Camera Mode
- The user can draw the box for which specific area to classify from both VIDEO and CAMERA approach. After selecting the area(rectangle box drawn via mouse connected to board) press `Done` button in left corner of the window. The inference starts and shows the classification result.

<img src=./images/Plant_vid_mode_ar_select.JPG width="480">

- Classification result, inference time(ms), Score(%) is shown on top left corner
Frame Per Sec (FPS) is shown on top right corner

<img src=./images/plant_vid_mode_play.JPG width="480">

##### Image Mode
- Classification result, inference time(ms) and Score(%) is shown on top left corner

<img src=./images/Plant_img_mode.JPG width="480">



#### Application: Termination
- Application can be terminated by Double clicking on the window.
- Alternatively, to force close the application, switch from the application window to the terminal by pressing `Super(windows key)+Tab` and press `CTRL + C`.


## Application: Specifications 


#### Model Details

```python 

----------------------------------------------------------------
        Layer (type)               Output Shape         Param #
================================================================
            Conv2d-1         [-1, 64, 256, 256]           1,792
       BatchNorm2d-2         [-1, 64, 256, 256]             128
              ReLU-3         [-1, 64, 256, 256]               0
            Conv2d-4        [-1, 128, 256, 256]          73,856
       BatchNorm2d-5        [-1, 128, 256, 256]             256
              ReLU-6        [-1, 128, 256, 256]               0
         MaxPool2d-7          [-1, 128, 64, 64]               0
            Conv2d-8          [-1, 128, 64, 64]         147,584
       BatchNorm2d-9          [-1, 128, 64, 64]             256
             ReLU-10          [-1, 128, 64, 64]               0
           Conv2d-11          [-1, 128, 64, 64]         147,584
      BatchNorm2d-12          [-1, 128, 64, 64]             256
             ReLU-13          [-1, 128, 64, 64]               0
           Conv2d-14          [-1, 256, 64, 64]         295,168
      BatchNorm2d-15          [-1, 256, 64, 64]             512
             ReLU-16          [-1, 256, 64, 64]               0
        MaxPool2d-17          [-1, 256, 16, 16]               0
           Conv2d-18          [-1, 512, 16, 16]       1,180,160
      BatchNorm2d-19          [-1, 512, 16, 16]           1,024
             ReLU-20          [-1, 512, 16, 16]               0
        MaxPool2d-21            [-1, 512, 4, 4]               0
           Conv2d-22            [-1, 512, 4, 4]       2,359,808
      BatchNorm2d-23            [-1, 512, 4, 4]           1,024
             ReLU-24            [-1, 512, 4, 4]               0
           Conv2d-25            [-1, 512, 4, 4]       2,359,808
      BatchNorm2d-26            [-1, 512, 4, 4]           1,024
             ReLU-27            [-1, 512, 4, 4]               0
        MaxPool2d-28            [-1, 512, 1, 1]               0
          Flatten-29                  [-1, 512]               0
           Linear-30                   [-1, 38]          19,494
================================================================
Total params: 6,589,734
Trainable params: 6,589,734
Non-trainable params: 0
----------------------------------------------------------------
Input size (MB): 0.75
Forward/backward pass size (MB): 343.95
Params size (MB): 25.14
Estimated Total Size (MB): 369.83
----------------------------------------------------------------
None

base ResNet9 architecture

```

#### Dataset 
The class labels are mentioned in the [`plant_leaf_disease_class.txt`](./exe/plant_leaf_disease_class.txt)
This dataset consists of about 87K rgb images of healthy and diseased crop leaves which is categorized into 38 different classes. The total dataset is divided into 80/20 ratio of training and validation set preserving the directory structure. A new directory containing 33 test images is created later for prediction purpose.

[Dataset Link](https://www.kaggle.com/datasets/vipoooool/new-plant-diseases-dataset)




#### AI Inference time
Total AI inference time (Pre-processing + AI model inference) - 110 ms.

| Training Accuracy   |Validation Accuracy   |  Testing Accuracy |
|---|---|---|
|  94.2 | 93.1  | 90.5  |

