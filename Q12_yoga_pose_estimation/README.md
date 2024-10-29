# Yoga Pose Estimation

## Application: Overview
The Yoga pose estimation application automatically detects and analyze human body poses while doing yoga.
It can be used for a wide variety of applications such as:
- **Virtual yoga sessions**: Real-time feedback on poses and alignment during virtual sessions.
- **Fitness app**: Tracking yoga practice, correcting postures, and guiding users through routines.
- **Rehabilitation**: Monitoring exercises in physical therapy to ensure correct form.

### Key Features
Here are some of the key features of the Fish Detection Application:

- **Full body joint detection**: 
    The application utilizes HR-Net model to analyze an image or video feed to locate key body parts and estimate their positions. It identifies the key joints and their connections to form a "skeleton" of the body.
- **Pose classification**: 
     The detected pose is compared against a set of known yoga poses. The classification model can then classify which yoga pose is being performed.

It has following modes of running.

|Mode | RZ/V2H |
|:---|:---|
|MIPI Camera|`-`|
|USB Camera|`Supported`|
|Image|`Supported`|
|Video|`Supported`|


### Supported Product
- RZ/V2H Evaluation Board Kit (RZ/V2H EVK)

### Demo

Following is the demo for RZ/V2H EVK.  
<img src="./images/yoga_pose_estimation_v2h_demo.gif" width="480">

## Application: Requirements

### Hardware Requirements
<table class="gstable">
    <tr>
      <th>For</th>
      <th>Equipment</th>
      <th>Details</th>
    </tr>
    <tr>
      <td rowspan="4">RZ/V2H</td>
      <td>RZ/V2H EVK</td>
      <td>Evaluation Board Kit for RZ/V2H.</td>
    </tr>
    <tr>
      <td>AC Adapter</td>
      <td>USB Power Delivery adapter for the board power supply.<br>
      100W is required.</td>
    </tr>
    <tr>
      <td>HDMI Cable</td>
      <td>Used to connect the HDMI Monitor and the board.<br>
      RZ/V2H EVK has HDMI port.</td>
    </tr>
    <tr>
      <td>USB Camera</td>
      <td>Used as a camera input source.</td>
    </tr>
    <tr>
      <td rowspan="8">Common</td>
      <td>USB Cable Type-C</td>
      <td>Connect AC adapter and the board.</td>
    </tr>
    <tr>
      <td>HDMI Monitor</td>
      <td>Used to display the graphics of the board.</td>
    </tr>
    <tr>
      <td>microSD card</td>
      <td>Used as the filesystem.<br>
      Must have over 4GB capacity of blank space.<br>
      Operating Environment: Transcend UHS-I microSD 300S 16GB</td>
    </tr>
    <tr>
      <td>Linux PC</td>
      <td>Used to build application and setup microSD card.<br>
      Operating Environment: Ubuntu 20.04</td>
    </tr>
    <tr>
      <td>SD card reader</td>
      <td>Used for setting up microSD card.<br></td>
    </tr>
    <tr>
      <td>USB Hub</td>
      <td>Used to connect USB Keyboard and USB Mouse to the board.</td>
    </tr>
    <tr>
      <td>USB Keyboard</td>
      <td>Used to type strings on the terminal of board.</td>
    </tr>
    <tr>
      <td>USB Mouse</td>
      <td>Used to operate the mouse on the screen of board.</td>
    </tr>
  </table>

>**Note:** All external devices will be attached to the board and does not require any driver installation (Plug n Play Type)   

Connect the hardware as shown below.  

| RZ/V2H EVK |
|:---|
|<img src=./images/hw_conf_v2h.png width=600>  |

>**Note 1:** When using the keyboard connected to RZ/V Evaluation Board, the keyboard layout and language are fixed to English.   
>**Note 2:** For RZ/V2H EVK, there are USB 2.0 and USB 3.0 ports.  
USB camera needs to be connected to appropriate port based on its requirement.

## Application: Build Stage

>**Note:** User can skip to the [next stage (deploy)](#application-deploy-stage) if they do not want to build the application.  
All pre-built binaries are provided.

### Prerequisites
This section expects the user to have completed Step 5 of [Getting Started Guide](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started.html) provided by Renesas. 

After completion of the guide, the user is expected of following things.
- AI SDK setup is done.
- Following docker container is running on the host machine.
    |Board | Docker container |
    |:---|:---|
    |RZ/V2H EVK|`rzv2h_ai_sdk_container`  |

    >**Note:** Docker environment is required for building the sample application. 


### Application File Generation
1. On your host machine, copy the repository from the GitHub to the desired location. 
    1. It is recommended to copy/clone the repository on the `data` folder, which is mounted on the Docker container. 
    ```sh
    cd <path_to_data_folder_on_host>/data
    git clone https://github.com/renesas-rz/rzv_ai_sdk.git
    ```
    >Note: This command will download the whole repository, which include all other applications.  
    If you have already downloaded the repository of the same version, you may not need to run this command.  

2. Run (or start) the docker container and open the bash terminal on the container.  
E.g.,use the `rzv2h_ai_sdk_container` as the name of container created from  `rzv2h_ai_sdk_image` docker image.  
    > Note that all the build steps/commands listed below are executed on the docker container bash terminal.  

3. Set your clone directory to the environment variable.  
    ```sh
    export PROJECT_PATH=/drp-ai_tvm/data/rzv_ai_sdk
    ```
3. Go to the application source code directory.  
    ```sh
    cd ${PROJECT_PATH}/Q12_yoga_pose_estimation/src
    ```

4. Create and move to the `build` directory.
    ```sh
    mkdir -p build && cd build
    ``````
4. Build the application by following the commands below.  
    ```sh
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
    make -j$(nproc)
    ```
5. The following application file would be generated in the `${PROJECT_PATH}/Q12_yoga_pose_estimation/src/build` directory
    - pose_estimator


## Application: Deploy Stage
### Prerequisites
This section expects the user to have completed Step 7-1 of [Getting Started Guide](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started.html#step7) provided by Renesas. 

After completion of the guide, the user is expected of following things.
- microSD card setup is done.

### File Configuration
For the ease of deployment all the deployable files and folders are provided in following folders.  
|Board | `EXE_DIR` |
|:---|:---|
|RZ/V2H EVK|[exe_v2h](./exe_v2h)  |

Each folder contains following items.
|File | Details |
|:---|:---|
|keypoint_detection_model | keypoint Model object files for deployment. |
|pose_classifier_model | classifier Model object files for deployment. |
|labels.txt | Label list for Pose classification. |
|pose_estimator | application file. |
|sample_images | Sample image files. |
|yoga_sample.mp4 | Sample video file. |

### Instruction
1. Copy the files to the `/home/root/tvm` directory of the rootfs (SD Card) for the board.
    |File | Details |
    |:---|:---|
    |All files in `EXE_DIR` directory | Including `deploy.so` file. |
    |`pose_estimator` application file | Generated the file according to [Application File Generation](#application-file-generation) |

2. Check if `libtvm_runtime.so` exists under `/usr/lib64` directory of the rootfs (SD card) on the board.

3. Folder structure in the rootfs (SD Card) would look like:
    ```sh
    |-- usr
    |   `-- lib64
    |       `-- libtvm_runtime.so
    `-- home
        `-- root
            `-- tvm
                |-- keypoint_detection_model
                |   |-- deploy.json
                |   |-- deploy.params
                |   |-- deploy.so
                |
                |-- pose_classifier_model
                |   |-- deploy.json
                |   |-- deploy.params
                |   |-- deploy.so
                |
                |-- sample_images
                |-- yoga_sample.mp4
                |-- labels.txt
                `-- pose_estimator
    ```
>**Note:** The directory name could be anything instead of `tvm`. If you copy the whole `EXE_DIR` folder on the board, you are not required to rename it `tvm`.

## Application: Run Stage

### Prerequisites
This section expects the user to have completed Step 7-3 of [Getting Started Guide](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started.html#step7-3) provided by Renesas. 

After completion of the guide, the user is expected of following things.  
- The board setup is done.  
- The board is booted with microSD card, which contains the application file.  

### Instruction
1. On Board terminal, go to the `tvm` directory of the rootfs.
    ```sh
    cd /home/root/tvm
    ```

2. Run the application.
    - For USB Camera Mode
    ```sh
    ./pose_estimator USB
    ```
    - For IMAGE Mode
    ```sh
    ./pose_estimator IMAGE "path to the input image"
    ```
    - For VIDEO Mode
    ```sh
    ./pose_estimator VIDEO "path to the input video"
    ```
3. Following window shows up on HDMI screen.  

    | RZ/V2H EVK |
    |:---|
    |<img src=./images/yoga_pose_estimation_v2h.jpg width=350>  |

    On application window, following information is displayed.  
    - Camera capture  
    - Pose estimation result (Bounding boxes, Pose name and score.)  
    - Processing time 
        - Total AI time: Total time taken for the end to end inference
        - Preprocess: Total time taken for pre-processing the input for both key-point detection and pose classifier models.
        - Inference: Processing time taken for AI inference for both key-point detection and pose classifier models.
        - Postprocess: Total time taken for post-processing the model outputs for both key-point detection and pose classifier models.
        
4. To terminate the application, switch the application window to the terminal by using `Super(windows key)+Tab ` and press ENTER key on the terminal of the board.

## Application: Configuration
### AI Model  

- RZ/V2H
    - HR-Net: [Github](https://github.com/HRNet/HRNet-Human-Pose-Estimation) for keypoint detection  
    Dataset: [COCO dataset](https://cocodataset.org/#download)  
    Input size: 1x3x256x192  
    Output size: 1x17x64x48

    - NeuralNet(custom): for pose classification  
    Dataset: [Kaggle dataset](https://www.kaggle.com/datasets/ujjwalchowdhury/yoga-pose-classification)  
    Input size: 1x1x1x24  
    Output size: 1x1x1x5

  #### Target classes:
    - Downdog Pose
    - Goddess Pose
    - Plank Pose
    - Tree Pose
    - Warrior II Pose

     

### AI inference time
|Board |  AI inference time <br>for keypoint detection| AI inference time <br>for pose classification |
|:---:|:---:| :---:|
|RZ/V2H EVK | Approximately 18 ms  | Approximately 1 ms  |

### Processing

|Processing | Details |
|:---|:---|
|Pre-processing | Processed by CPU. |
|Inference | Processed by DRP-AI and CPU. |
|Post-processing | Processed by CPU. |

### Image buffer size

|Board | Camera capture buffer size|HDMI output buffer size|
|:---|:---|:---|
|RZ/V2H EVK | VGA (640x480) in YUYV format  | FHD (1920x1080) in BGRA format  |
 
  
## Reference
- For RZ/V2H EVK, this application supports USB camera only with 640x480 resolution.     
To use FHD, please use MIPI camera.   
Please refer to following URL for how to change camera input to MIPI camera.  
[https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications](https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications#mipi).  

## License
Apache License 2.0