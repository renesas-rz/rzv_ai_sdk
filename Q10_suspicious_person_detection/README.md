
# Suspicious Person Detection Application

The suspicious person detection application uses the advanced Tiny-YOLOv3 algorithm to automatically detect suspicious and non-suspicious people in real-time camera streams. It can identify and classify people in images or videos, and can be used to help security personnel monitor public areas for potential threats.

It can be used to enhance **Safety**  in different public places around the world like Banks, offices, Hospitals, Airports, shopping malls, Examination halls, Railway stations, etc.

## Key Features
Here are some of the key features of the Suspicious Person Detection Application:

- **Automatic Detection**: 
    The application utilizes Tiny-yolov3 model for detection, identifying and localizing people specified within the provided frame.
- **Customizable Settings**: 
    Users can adjust the detection parameters by using the config file provided in the repository.


# Requirements

### Hardware Requirements

- RZ/V2L Evaluation Board Kit
- USB camera 
- USB Keyboard
- HDMI monitor with resolution 1280x720 
- micro HDMI to HDMI cable 
- SD Card (for file system)

### Software Requirements

- OpenCV 4.x
- C++11 or higher

## Application: Build Stage

>**Note:** User can skip to the next stage (deploy) if they don't want to build the application. All pre-built binaries are provided.

**Note:** This project expects the user to have completed [Getting Startup Guide](../README.md#startup-guide) provided by Renesas

After completion of the guide, the user is expected of following things.
- The Board Set Up and booted. 
- SD Card Prepared 
- The docker image amd container for `rzv2l_ai_sdk_image` running on host machine.

>**Note:** Docker container is required for building the sample application. By default the Renesas will provide the container named as `rzv2l_ai_sdk_container`. Please use the docker container name as assigned by the user when building the container.

#### Application File Generation
1. Copy the repository from the GitHub to the desired location. 
2. It is recommended to copy/clone the repository on the `data` folder which is mounted on the `rzv2l_ai_sdk_container` docker container. 

    ```sh
    cd <path_to_data_folder_on_host>
    git clone https://github.com/renesas-rz/rzv_ai_sdk.git
    ```

3. Run(or start) the docker container and open the bash terminal on the container.

> Note: All the build steps/commands listed below are executed on the docker container bash terminal.

4. Assign path to the `data` directory mounted on the `rzv2l_ai_sdk_container` docker container.

```sh
export PROJECT_PATH=/drp_ai_tvm/data/
```

5. Go to the `src` directory of the application

```sh
cd ${PROJECT_PATH}/rzv_ai_sdk/Q10_suspecious_person_detection/src/
```
6. Build the application on docker environment by following the steps below

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
- suspecious_person_detector


## Application: Deploy Stage

For the ease of deployment all the deployable files and folders for RZ/V2L are provided on the [exe](./exe) folder.

|File | Details |
|:---|:---|
|suspicious_onnx | Model object files for Suspicious Detection |
|suspicious_class.txt | Label list for Suspicious Detection |
|config.ini | User input config object file | 
|suspicious_person_detector | Application file |

Follow the steps mentioned below to deploy the project on RZ/V2L Board. 
* At the `/home/root/tvm` directory of the rootfs (on SD Card) for RZ/V2L board.
* Copy the files present in [exe](./exe) directory, which are listed in the table above.
* Copy the generated `suspicious_person_detector` application file if the application file is built at [build stage](#application-build-stage)
* Check if libtvm_runtime.so is there on `/usr/lib64` directory of the rootfs (SD card) RZ/V2L board.

Folder structure in the rootfs (SD Card) would look like:
```sh
├── usr/
│   └── lib64/
│       └── libtvm_runtime.so
└── home/
    └── root/
        └── tvm/ 
            ├── suspicious_onnx/
            │   ├── deploy.json
            │   ├── deploy.params
            │   ├── deploy.so
            │   └── preprocess/
            │   
            ├── suspicious_class.txt            │   
            ├── config.ini
            └── suspicious_person_detector

```


>**Note:** The directory name could be anything instead of `tvm`. If you copy the whole `exe` folder on the board. You are not required to rename it `tvm`.

## Application: Run Stage

For running the application, run the commands as shown below on the RZ/V2L Evaluation Board console.

1. Go to the `/home/root/tvm` directory of the rootfs
  ```sh
  cd /home/root/tvm
  ```

2. Change the values in `config.ini` as per the requirements. Detailed explanation of the `config.ini` file is given at below section.
  ```sh
  vi config.ini
  ```

3. Run the application in the terminal of the RZ/V2L evaluation board kit using the command
  - For MIPI Camera
  ```sh
  ./suspicious_person_detector
  ```
  - For USB Camera
  ```sh
 ./suspicious_person_detector USB
  ```

The expected output will be the same as shown in the demo video

### Application: Runtime output details

The runtime application will look something like this

#### MIPI Camera Mode
  <img src=./images/Q10_suspicious_mipi2.gif width="480">

#### USB Camera Mode
  <img src=./images/Q10_suspicious_usb.gif width="480">

Frame Per Sec (FPS) is shown on top right corner.

### Application: Termination 
Switch from the application window to the terminal with using `Super(windows key)+Tab` and press `ENTER` key on the terminal of RZ/V2L Board.

## Application: Specifications

### Default Model Details

Tiny Yolov3 is used. Model weights are taken from [Darknet-Yolo](https://pjreddie.com/darknet/yolo/).

Then the model is retrained with below mentioned dataset. 

### Dataset

Dataset used is the custom labelled dataset

### AI inference time
The AI inference time is 150-190 msec.

## Application: Configuration 

### Explanation of the `config.ini` file

- The config.ini file should contain two sections [**path**] & [**detect**].

- The section [**path**] should contains two variables - 'model_path' & 'label_path'.

- The model_path value is the path to the folder containing compliled model. The folder should also contains also contain preprocess folder. 

- The label_path value is the path to the label list the model supports.

- The [**detect**] section contains three variables - 'conf', 'anchors' & 'objects'.

- The conf value is the confidence threshold used for object detection, and objects represents class and it can be changed to other classes present on the label list.

- The anchors are a set of predefined bounding boxes values of a certain height and width. These boxes are defined to capture the scale and aspect ratio of specific object classes you want to detect and are typically chosen based on object sizes in your training datasets.

- To modify the configuration settings, edit the values in this file using VI Editor, from the RZ/V2L Board.