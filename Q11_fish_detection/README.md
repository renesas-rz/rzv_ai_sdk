
# Fish Detection Application

The Fish detection application uses the advanced Tiny-YOLOv3 algorithm to automatically detect fishes in real-time camera streams.
Fish detection applications can be used in a variety of different settings, including:

- **On-board vessels:** Fish detection applications can be installed on fishing vessels to help fishermen identify and track fish schools.
- **Underwater vehicles:** Fish detection applications can be equipped on underwater vehicles to monitor fish populations and study fish behavior in their natural environment.
- **Aquaculture facilities:** Fish detection applications can be used in aquaculture facilities to monitor fish health and track fish growth.
- **Research laboratories:** Fish detection applications can be used in research laboratories to study fish behavior and identify new fish species.

### Key Features
Here are some of the key features of the Fish Detection Application:

- **Automatic Detection**: 
    The application utilizes Tiny-yolov3 model for detection, identifying and localizing people specified within the provided frame.
- **Customizable Settings**: 
    Users can adjust the detection parameters by using the config file provided in the repository.

### Demo 

<img src=./images/Q11_fish_usb.gif width="480">


## Application: Requirements

### Hardware Requirements

- RZ/V2L Evaluation Board Kit
  - MIPI Camera
- USB Camera (optional)
- USB Keyboard
- USB Hub
- HDMI monitor with resolution 1280x720 
- Micro HDMI to HDMI cable 
- SD Card (for file system)

[Hardware Setup Steps](https://github.com/renesas-rz/rzv_ai_sdk/#hardware-requirements-and-setup)

### Software Requirements

- OpenCV 4.x
- C++11 or higher

## Application: Build Stage

>**Note:** User can skip to the next stage (deploy) if they don't want to build the application. All pre-built binaries are provided.

**Note:** This project expects the user to have completed [Getting Started Guide](https://github.com/renesas-rz/rzv_ai_sdk/blob/main/README.md#startup-guide) provided by Renesas

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
    git clone -b fish_detection --single-branch https://github.com/renesas-rz/rzv_ai_sdk.git
    ```

3. Run(or start) the docker container and open the bash terminal on the container.

> Note: All the build steps/commands listed below are executed on the docker container bash terminal.

4. Assign path to the `data` directory mounted on the `rzv2l_ai_sdk_container` docker container.

```sh
export PROJECT_PATH=/drp-ai_tvm/data/
```

5. Go to the `src` directory of the application

```sh
cd ${PROJECT_PATH}/rzv_ai_sdk/Q11_fish_detection/src/
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
- fish_detector


## Application: Deploy Stage

For the ease of deployment all the deployable files and folders for RZ/V2L are provided on the [exe](./exe) folder.

|File | Details |
|:---|:---|
|fish_detection_model | Model object files for Fish Detection |
|fish_class.txt | Label list for Fish Detection |
|config.ini | User input config object file | 
|fish_detector | Application file |

Follow the steps mentioned below to deploy the project on RZ/V2L Evaluation Board. 
* At the `/home/root/tvm` directory of the rootfs (on SD Card) for RZ/V2L Evaluation Board.
* Copy the files present in [exe](./exe) directory, which are listed in the table above.
* Copy the generated `fish_detector` application file if the application file is built at [build stage](#application-build-stage)
* Check if libtvm_runtime.so is there on `/usr/lib64` directory of the rootfs (SD card) RZ/V2L Evaluation Board.

Folder structure in the rootfs (SD Card) would look like:
```sh
├── usr/
│   └── lib64/
│       └── libtvm_runtime.so
└── home/
    └── root/
        └── tvm/ 
            ├── fish_detection_model/
            │   ├── deploy.json
            │   ├── deploy.params
            │   ├── deploy.so
            │   └── preprocess/
            │   
            ├── fish_class.txt           
            ├── config.ini
            └── fish_detector

```


>**Note:** The directory name could be anything instead of `tvm`. If you copy the whole `exe` folder on the board. You are not required to rename it `tvm`.

## Application: Run Stage

For running the application, run the commands as shown below on the RZ/V2L Evaluation Board console.

1. Go to the `/home/root/tvm` directory of the rootfs
  ```sh
  cd /home/root/tvm
  ```

2. Change the values in `config.ini` as per the requirements. Detailed explanation of the `config.ini` file is given at below [section](#explanation-of-the-configini-file).
  ```sh
  vi config.ini
  ```

3. Run the application in the terminal of the RZ/V2L Evaluation board kit using the command
  - For MIPI Camera
  ```sh
  ./fish_detector
  ```
  - For USB Camera
  ```sh
  ./fish_detector USB
  ```

The expected output will be the same as shown in the demo video

### Application: Runtime output details

The runtime application will look something like this
  
  <img src=./images/expected_results.JPG width="420">

1. For each frame the detected fishes will be shown as a bounding box with confidence score. Each detected fish will be classified to which spicies they belong.
2. AI-inference time for each frame and Frame Per Sec (FPS) is shown on top right corner.
3. The class confidence is also shown for each class detected on the frame.



### Application: Termination 

Switch from the application window to the terminal with using `Super(windows key)+Tab` and press `ENTER` key on the terminal of RZ/V2L Evaluation Board.

## Application: Specifications

### Model Details

Tiny Yolov3 is used. Model weights are taken from [Darknet-Yolo](https://pjreddie.com/darknet/yolo/).

Then the model is retrained with below mentioned dataset. 

### Dataset

Dataset used is the custom labelled dataset with classes listed [here](./exe/fish_class.txt).


### AI inference time
The AI inference time is 120-160 msec.

## Application: Configuration 

### Explanation of the `config.ini` file

- The config.ini file should contain two sections [**path**] & [**detect**].

- The section [**path**] should contains two variables - 'model_path' & 'label_path'.

- The `model_path` value is the path to the folder containing compiled model. The folder should also contains also contain preprocess folder. 

- The `label_path` value is the path to the label list the model supports.

- The [**detect**] section contains three variables - 'conf', 'anchors' & 'objects'.

- The `conf` value is the confidence threshold used for object detection.

- The `anchors` are a set of predefined bounding boxes values of a certain height and width. These boxes are defined to capture the scale and aspect ratio of specific object classes you want to detect and are typically chosen based on object sizes in your training datasets.

- The `objects` represents class and it can be changed to other classes present on the label list.

- To modify the configuration settings, edit the values in this file using VI Editor, from the RZ/V2L Evaluation Board.
