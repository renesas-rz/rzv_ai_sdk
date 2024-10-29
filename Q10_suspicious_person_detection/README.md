
# Suspicious Person Detection Application

## Application: Overview
The [suspicious person](#suspicious-person-definition) detection application uses the advanced Tiny-YOLOv3/YOLOv3 algorithm to automatically detect suspicious and non-suspicious people in real-time camera streams. It can identify and classify people in images or videos, and can be used to help security personnel monitor public areas for potential threats.

It can be used to enhance **Safety**  in different public places around the world like Banks, offices, Hospitals, Airports, shopping malls, Examination halls, Railway stations, etc.

### Key Features
Here are some of the key features of the Suspicious Person Detection Application:

- **Automatic Detection**: 
    The application utilizes Tiny-yolov3/yolov3 model for detection, identifying and localizing people specified within the provided frame.
- **Customizable Settings**: 
    Users can adjust the detection parameters by using the config file provided in the repository.

It has following camera input modes.
| Mode | RZ/V2L | RZ/V2H |
|:---|:---|:---|
| MIPI Camera| Supported | - |
| USB Camera| Supported | Supported |

### Supported Product
- RZ/V2L Evaluation Board Kit (RZ/V2L EVK)
- RZ/V2H Evaluation Board Kit (RZ/V2H EVK)

### Demo

Following is the demo for RZ/V2H EVK.  
<img src="./images/Q10_suspicious_demo.gif" width="480">

## Application: Requirements

### Hardware Requirements
<table class="gstable">
    <tr>
      <th>For</th>
      <th>Equipment</th>
      <th>Details</th>
    </tr>
    <tr>
      <td rowspan="3">RZ/V2L</td>
      <td>RZ/V2L EVK</td>
      <td>Evaluation Board Kit for RZ/V2L.<br>Includes followings.
        <ul class="mb-1">
          <li>
            MIPI Camera Module(Google Coral Camera)<br>
            Used as a camera input source.
          </li>
          <li>MicroUSB to Serial Cable for serial communication.</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td>AC Adapter</td>
      <td>USB Power Delivery adapter for the board power supply.</td>
    </tr>
    <tr>
      <td>MicroHDMI Cable</td>
      <td>Used to connect the HDMI Monitor and the board.<br>
      RZ/V2L EVK has microHDMI port.</td>
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

|RZ/V2L EVK | RZ/V2H EVK |
|:---|:---|
|<img src=./images/hw_conf_v2l.png width=600>|<img src=./images/hw_conf_v2h.png width=600>  |

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
    |RZ/V2L EVK|`rzv2l_ai_sdk_container`  |
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
E.g., for RZ/V2L, use the `rzv2l_ai_sdk_container` as the name of container created from  `rzv2l_ai_sdk_image` docker image.  
    > Note that all the build steps/commands listed below are executed on the docker container bash terminal.  

3. Set your clone directory to the environment variable.  
    ```sh
    export PROJECT_PATH=/drp-ai_tvm/data/rzv_ai_sdk
    ```
3. Go to the application source code directory.  
    ```sh
    cd ${PROJECT_PATH}/Q10_suspicious_person_detection/src
    ```
4. Create and move to the `build` directory.
    ```sh
    mkdir -p build && cd build
    ``````
5. Build the application by following the commands below.  
    **For RZ/V2L**
    ```sh
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
    make -j$(nproc)
    ```
    **For RZ/V2H**
    ```sh
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake -DV2H=ON ..
    make -j$(nproc)
    ```
6. The following application file would be generated in the `${PROJECT_PATH}/Q10_suspicious_person_detection/src/build` directory
    - suspicious_person_detector


## Application: Deploy Stage
### Prerequisites
This section expects the user to have completed Step 7-1 of [Getting Started Guide](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started.html#step7) provided by Renesas. 

After completion of the guide, the user is expected of following things.
- microSD card setup is done.

### File Configuration
For the ease of deployment all the deployable files and folders are provided in following folders.  
|Board | `EXE_DIR` |
|:---|:---|
|RZ/V2L EVK|[exe_v2l](./exe_v2l)  |
|RZ/V2H EVK|[exe_v2h](./exe_v2h)  |

Each folder contains following items.
|File | Details |
|:---|:---|
|suspicious_onnx | Model object files for Suspicious Detection |
|suspicious_class.txt | Label list for Suspicious Detection |
|config.ini | User input config object file | 
|suspicious_person_detector | Application file |

### Instruction
1. [FOR RZ/V2H only] Run following commands to download the necessary file. 
   ```sh
   cd <path_to_data_folder_on_host>/data/rzv_ai_sdk/Q10_suspicious_person_detection/exe_v2h/suspicious_onnx
   wget https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v5.00/Q10_suspicious_person_detection_deploy_tvm_v2h-v230.so
   ```

2. [FOR RZ/V2H only] Rename the `Q10_suspicious_person_detection_deploy_*.so` to `deploy.so`.
    ```sh
    mv Q10_suspicious_person_detection_deploy_*.so deploy.so
    ```

3. Copy the following files to the `/home/root/tvm` directory of the rootfs (SD Card) for the board.
    |File | Details |
    |:---|:---|
    |All files in `EXE_DIR` directory | Including `deploy.so` file. |
    |`suspicious_person_detector` application file | Generated the file according to [Application File Generation](#application-file-generation) |

4. Check if `libtvm_runtime.so` exists under `/usr/lib64` directory of the rootfs (SD card) on the board.

5. Folder structure in the rootfs (SD Card) would look like:
    ```
    |-- usr
    |   `-- lib64
    |       `-- libtvm_runtime.so
    `-- home
        `-- root
            `-- tvm
                |-- suspicious_onnx
                |   |-- deploy.json
                |   |-- deploy.params
                |   `-- deploy.so
                |-- config.ini
                |-- suspicious_class.txt 
                `-- suspicious_person_detector
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
    cd /home/root/tvm/
    ```

2. Change the values in `config.ini` as per the requirements. Detailed explanation of the `config.ini` file is given at [below section](#explanation-of-the-configini-file).
    ```sh
    vi config.ini
    ```

3. Run the application.
    - For MIPI Camera (RZ/V2L only)
     ```sh
     ./suspicious_person_detector MIPI
     ```
    - For USB Camera
     ```sh
     ./suspicious_person_detector USB
     ```
4. Following window shows up on HDMI screen.  

    |RZ/V2L EVK | RZ/V2H EVK |
    |:---|:---|
    |<img src=./images/suspicious_result1.png width=350>| <img src=./images/suspicious_result2.png width=350>  |

    On application window, following information is displayed.  
    - Camera capture  
    - Object Detection result (Bounding boxes, class name and score.)
    - Processing time  
        - Total AI Time: Sum of all processing time below.  
        - Inference: Processing time taken for AI inference.  
        - PreProcess: Processing time taken for AI pre-processing.  
        - PostProcess: Processing time taken for AI post-processing.<br>(excluding the time for drawing on HDMI screen).
    - Confidence values for "suspicious" or "non-suspicious" inference results  
        
5. To terminate the application, switch the application window to the terminal by using `Super(windows key)+Tab ` and press ENTER key on the terminal of the board.


## Application: Configuration 
### AI Model
- RZ/V2L
    - Tiny YOLOv3: [Darknet](https://pjreddie.com/darknet/yolo/)  
    Dataset: Custom labelled dataset with classes listed [here](./exe_v2l/suspicious_class.txt)   
    Input size: 1x3x416x416  
    Output1 size: 1x13x13x21  
    Output2 size: 1x26x26x21  
  
- RZ/V2H
    - YOLOv3: [Darknet](https://pjreddie.com/darknet/yolo/)  
    Dataset: Custom labelled dataset with classes listed [here](./exe_v2h/suspicious_class.txt)  
    Input size: 1x3x416x416  
    Output1 size: 1x13x13x21  
    Output2 size: 1x26x26x21  
    Output3 size: 1x52x52x21  

### AI inference time
|Board | AI model | AI inference time|
|:---|:---|:---|
|RZ/V2L EVK|Tiny YOLOv3| Approximately 61 ms  |
|RZ/V2H EVK |YOLOv3 | Approximately 25 ms  |

### Processing

|Processing | Details |
|:---|:---|
|Pre-processing | Processed by CPU. <br> |
|Inference | Processed by DRP-AI and CPU. |
|Post-processing | Processed by CPU. |

### Explanation of the `config.ini` file
- The config.ini file should contain two sections [**path**] & [**detect**].
- The section [**path**] should contains two variables - 'model_path' & 'label_path'.
- The model_path value is the path to the folder containing compiled model. The folder should also contains also contain preprocess folder. 
- The label_path value is the path to the label list the model supports.
- The [**detect**] section contains three variables - 'conf', 'anchors' & 'objects'.
- The conf value is the confidence threshold used for object detection, and objects represents class and it can be changed to other classes present on the label list.
- The anchors are a set of predefined bounding boxes values of a certain height and width. These boxes are defined to capture the scale and aspect ratio of specific object classes you want to detect and are typically chosen based on object sizes in your training datasets.
- To modify the configuration settings, edit the values in this file using VI Editor, from the RZ/V2L or RZ/V2H Evaluation Board Kit.

### Image buffer size

|Board | Camera capture buffer size|HDMI output buffer size|
|:---|:---|:---|
|RZ/V2L EVK| VGA (640x480) in YUYV format  | HD (1280x720) in BGRA format  |
|RZ/V2H EVK | VGA (640x480) in YUYV format  | FHD (1920x1080) in BGRA format  |

## Reference
 
- For RZ/V2H EVK, this application supports USB camera only with 640x480 resolution.\
To use FHD, please use MIPI camera.\
Please refer to following URL for how to change camera input to MIPI camera.\
[https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications](https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications#mipi).

## License
Apache License 2.0   
For third party OSS library, please see the source code file itself. 