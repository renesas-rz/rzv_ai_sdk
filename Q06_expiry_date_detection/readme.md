# Expiry Date Extraction

## Application: Overview
This application is designed to extract expiry date information from the food items or medicines. 

The application was made to extract year, month and day from certain YYMMDD formats. 
Extracted date formats from 

"DD-MMM-YY",
"YY-MMM-DD",
"MMM-DD-YY",
"YYYY-MMM-DD",
"DD-MMM-YYYY",
"DDst-MMM-YYYY",
"MMM-DD-YYYY"

This software could be useful in a variety of settings, such as retail stores, hospitals, etc. 
where managers/users need to verify the product expiry dates.

The AI model used for the sample application is [TinyYoloV3](https://arxiv.org/pdf/1804.02767.pdf).

#### Image Mode 

The application to test with images is provided here [Link](./etc/readme.md)

#### Demo 
<!-- <img src = "./images/ObjectTracking.gif" width="480" height="320"> -->
TBD

## Application: Requirements

#### Hardware Requirements
- RZ/V2L Evaluation Board Kit
    - Coral camera 
- USB Camera [optional]
- USB Keyboard
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
- [Boost C++ libraries](https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source) 


## Application: Build Stage

>**Note:** User can skip to the next stage (deploy) if they don't want to build the application. All pre-built binaries are provided.

**Note:** This project expects the user to have completed [Getting Startup Guide](../README.md#startup-guide) provided by Renesas. 

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

    >Note: Please verify the git repository url if error occurs

2. Run(or start) the docker container and open the bash terminal on the container.

> Note: All the build steps/commands listed below are executed on the docker container bash terminal.

3. Assign path to the `data` directory mounted on the `rzv2l_ai_sdk_container` docker container

```sh
export PROJECT_PATH=/drp_ai_tvm/data/
```
4. Go to the `src` directory of the application

```sh
cd ${PROJECT_PATH}/rzv_ai_sdk/Q06_expiry_date_detection/src/
```
>**Note:**`rzv_ai_sdk` is the repository name corresponding to the cloned repository. Please verify the repository name if error occurs.

5. Download the `boost` tar file
```sh
wget https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.bz2
```
>**Note:** It is expected that the docker container is able to connect to the internet. If that's not the case, User can use the same command on the host PC to download the file. Make sure you are on the `src` folder present on the mounted `data` directory.

6. Extract tar file to the current location 

```sh
tar -xvf boost_1_81_0.tar.bz2
```

7. Copy the boost files to the `include` folder 
```sh
cp -r boost_1_81_0/boost include/
```
8. Remove boost files [Optional]

```sh
rm boost_1_81_0.tar.bz2
rm -rf boost_1_81_0
```
9. [Optional] For Coral Camera Application, uncomment [`// #define INPUT_CORAL`](./src/define.h#L131) 
```
# define INPUT_CORAL
```
10. Build the application on docker environment by following the steps below

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
- date_extraction


## Application: Deploy Stage

For the ease of deployment all the deployable files and folders for RZ/V2L are provided on the [exe](./exe) folder.

|File | Details |
|:---|:---|
|date_tinyyolov3_onnx | Model object files and pre-process files for deployment. |
|date_class_labels.txt | Label list for Object Detection. |
|date_extraction | application file. |


Follow the steps mentioned below to deploy the project on RZ/V2L Board. 
* At the `/home/root/tvm` directory of the rootfs (on SD Card) for RZ/V2L board.
   * Copy the files present in [exe](./exe) directory, which are listed in the table above.
   * Copy the generated `date_extraction` application file if the application file is built at [build stage](#application-build-stage)

* Check if libtvm_runtime.so is there on `/usr/lib64` directory of the rootfs (SD card) RZ/V2L board.


Folder structure in the rootfs (SD Card) would look like:

```sh
├── usr/
│   └── lib64/
│       └── libtvm_runtime.so
└── home/
    └── root/
        └── tvm/ 
            ├── date_tinyyolov3_onnx/
            │   ├── deploy.json
            │   ├── deploy.params
            │   ├── deploy.so 
            │   └── preprocess/
            ├── date_class_labels.txt
            └── date_extraction

```
>**Note:** The directory name could be anything instead of `tvm`. If you copy the whole `exe` folder on the board. You are not required to rename it `tvm`.

## Application: Run Stage
* For running the application, run the commands as shown below on the RZ/V2L Evaluation Board Kit console.
    * Go to the `/home/root/tvm` directory of the rootfs
    ```sh
    cd /home/root/tvm
    ```
    * Run the application
    ```sh
    ./date_extraction
    ```

#### Application: Termination 
- Switch from the application window to the terminal with using `Super(windows key)+Tab` and press `ENTER` key on the terminal of RZ/V2L Board.

## Application: Specifications

#### Model Details

- Tiny Yolov3 is used

#### Dataset

- Dataset used is the same as mentioned in the below research paper 
[Link](https://www.sciencedirect.com/science/article/pii/S0957417422006728?via%3Dihub)


## Known Issue

1. The tesseract engine will work fine mostly on solid black with white background. The tesseract engine used is v3.05.  
2. The model used is TinyYolov3 for date detection for increasing the performance. 
For better performance, user can use YoloV3 which is lot complex in nature.
3. For efficient date detection, User are expected to take image with proper lighting and contrast. 
4. USB Camera has shown much better resolution than coral camera. 
5. The date on the RZ/V2L board could be different. 

- To check use following on board terminal.
```sh
date
```
- To set to current date [if different]
```sh
date +%Y%m%d -s "20230615" 
```






