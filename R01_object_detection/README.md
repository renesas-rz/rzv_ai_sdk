# Object Detection

## Application: Overview
This application is designed to detect objects in the capture image of Camera and displays the result on HDMI screen.

This software could be useful in a variety of settings, such as retail stores, museums, and events.  
The AI model used for the sample application is [YOLOV3](https://arxiv.org/pdf/1804.02767.pdf).

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
    <tr>
      <td>RZ/V2H Evaluation Board Kit (RZ/V2H EVK)</td>
      <td>RZ/V2H AI SDK v5.20</td>
    </tr>
    <tr>
      <td>RZ/V2N Evaluation Board Kit (RZ/V2N EVK)</td>
      <td>RZ/V2N AI SDK v6.00 </td>
    </tr>
    
</table>

### Input/Output
<table>
    <tr>
      <th>Board</th>
      <th>Input</th>
      <th>Output</th>
    </tr>
    <tr>
      <td>RZ/V2L EVK</td>
      <td>MIPI camera</td>
      <td rowspan="3">HDMI</td>
    </tr>
    <tr>
      <td >RZ/V2H EVK</td>
      <td rowspan="2" style="text-align:center;">USB camera</td>
    </tr>
    <tr>
      <td >RZ/V2N EVK</td>
    </tr>
</table>


## Application: Requirements

### Hardware Requirements
<table>
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
      <td rowspan="4">RZ/V2N</td>
      <td>RZ/V2N EVK</td>
      <td>Evaluation Board Kit for RZ/V2N.</td>
    </tr>
    <tr>
      <td>AC Adapter</td>
      <td>USB Power Delivery adapter for the board power supply.<br>
      100W is required.</td>
    </tr>
    <tr>
      <td>HDMI Cable</td>
      <td>Used to connect the HDMI Monitor and the board.<br>
      RZ/V2N EVK has HDMI port.</td>
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
      Must have over 16GB capacity of blank space.<br>
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

|RZ/V2L EVK | RZ/V2H EVK | RZ/V2N EVK |
|:---|:---|:---|
|<img src=./img/hw_conf_v2l.png width=600>|<img src=./img/hw_conf_v2h.png width=600> |<img src=./img/hw_conf_v2n.png width=600> |

>**Note 1:** When using the keyboard connected to RZ/V Evaluation Board, the keyboard layout and language are fixed to English.  
**Note 2:** For RZ/V2H EVK, there are USB 2.0 and USB 3.0 ports.  
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
    |RZ/V2N EVK|`rzv2n_ai_sdk_container`  |

    >**Note 1:** Docker environment is required for building the sample application.  
<!--    >**Note 2:** Since RZ/V2N is a brother chip of RZ/V2H, the same environment can be used. -->


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
4. Go to the application source code directory.  
    ```sh
    cd ${PROJECT_PATH}/R01_object_detection/src
    ```

5. Create and move to the `build` directory.
    ```sh
    mkdir -p build && cd build
    ```
6. Build the application by following the commands below. 
  
    ```sh
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
    make -j$(nproc)
    ```

7. The following application file would be generated in the `${PROJECT_PATH}/R01_object_detection/src/build` directory
    - object_detection


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
|RZ/V2N EVK|[exe_v2n](./exe_v2n)  |
<!-- > Note: Since RZ/V2N is a brother chip of RZ/V2H, the same execution environment can be used.   -->
  
Each folder contains following items.
|File | Details |
|:---|:---|
|licenses | License information of AI model. <br>Not necessary for running application. |
|yolov3_onnx | Model object files for deployment.<br>Pre-processing Runtime Object files included. |
|yolov3_onnx_fhd | **For `exe_v2h` only.**  <br>Required when using FHD camera input image.<br>See [Reference](#reference). |
|coco-lables-2014_2017.txt | Label list for Object Detection. |
|object_detection | application file. |

### Instruction
1. Register the working directory path to an environment variable.<br>
The environment variable WORK is the working directory path that you set in Step 4-2 of [Getting Started Guide](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started.html#step4).

    ```sh
    export WORK=<path to the working directory>/ai_sdk_work
    export APPS_PATH=${WORK}/ai_sdk_setup/data/rzv_ai_sdk
    ```

2. Run following commands to download the necessary file.  
Replace each variable according to your board.  
    ```sh
    cd ${APPS_PATH}/R01_object_detection/<EXE_DIR>/yolov3_onnx
    wget <URL>/<SO_FILE>
    ```
    |Board | `EXE_DIR` |`URL` |`SO_FILE` |File Location |
    |:---|:---|:---|:---|:---|
    |RZ/V2L EVK|[exe_v2l](./exe_v2l)  |<span style="font-size: small">`https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v5.00/`</span>  |<span style="font-size: small">`R01_object_detection_deploy_tvm_v2l-v230.so`</span>  |[Release v5.00](https://github.com/renesas-rz/rzv_ai_sdk/releases/tag/v5.00/)  |
    |RZ/V2H EVK|[exe_v2h](./exe_v2h)  |<span style="font-size: small">`https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v5.00/`</span>  |<span style="font-size: small">`R01_object_detection_deploy_tvm_v2h-v230.so`</span> |[Release v5.00](https://github.com/renesas-rz/rzv_ai_sdk/releases/tag/v5.00/)  |
    |RZ/V2N EVK|[exe_v2n](./exe_v2n)  |<span style="font-size: small">`https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v6.00/`</span>  |<span style="font-size: small">`R01_object_detection_deploy_tvm_v2n-v251.so`</span> |[Release v6.00](https://github.com/renesas-rz/rzv_ai_sdk/releases/tag/v6.00/)  |
<!--    > Note: Since RZ/V2N is a brother chip of RZ/V2H, the same execution environment can be used.  -->

    - E.g., for RZ/V2L EVK, use following commands.
        ```sh
        cd ${APPS_PATH}/R01_object_detection/exe_v2l/yolov3_onnx
        wget https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v5.00/R01_object_detection_deploy_tvm_v2l-v230.so
        ```
3. Rename the `R01_object_detection_deploy_*.so` to `deploy.so`.
    ```sh
    mv <SO_FILE> deploy.so
    ```
4. Copy the following files to the `/home/root/tvm` directory (RZ/V2L, RZ/V2H) or `/home/weston/tvm` directory (RZ/V2N) of the rootfs (SD Card) for the board.
    |File | Details |
    |:---|:---|
    |All files in `EXE_DIR` directory | Including `deploy.so` file. |
    |`object_detection` application file | Generated the file according to [Application File Generation](#application-file-generation) |

5. Folder structure in the rootfs (SD Card) is shown below.<br>
   Check if `libtvm_runtime.so` exists in the rootfs directory (SD card) on the board.
   
   - For RZ/V2L and RZ/V2H
    ```
    |-- usr/
    |   `-- lib64/
    |       `-- libtvm_runtime.so
    |
    `-- home/
        `-- root/
            `-- tvm/ 
                |-- yolov3_onnx/
                |   |-- preprocess
                |   |-- deploy.json
                |   |-- deploy.params
                |   `-- deploy.so
                |-- coco-labels-2014_2017.txt
                `-- object_detection
    ```
   - For RZ/V2N
    ```
    |-- usr/
    |   `-- lib/
    |       `-- libtvm_runtime.so
    |
    `-- home/
        `-- weston/
            `-- tvm/ 
                |-- yolov3_onnx/
                |   |-- preprocess
                |   |-- deploy.json
                |   |-- deploy.params
                |   `-- deploy.so
                |-- coco-labels-2014_2017.txt
                `-- object_detection
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
   - For RZ/V2L and RZ/V2H
    ```sh
    cd /home/root/tvm
    ```
   - For RZ/V2N
    ```sh
    cd /home/weston/tvm
    ```

2. Run the application.
   - For RZ/V2L and RZ/V2H
    ```sh
    ./object_detection
    ```
   - For RZ/V2N
    ```sh
    su
    ./object_detection
    exit    # After pressing ENTER key to terminate the application.
    ```
>**Note:** For RZ/V2N AI SDK v6.00 and later, you need to switch to the root user with the 'su' command when running an application.<br>
This is because when you run an application from a weston-terminal, you are switched to the "weston" user, which does not have permission to run the /dev/xxx device used in the application.<br>

3. Following window shows up on HDMI screen.  

    |RZ/V2L EVK | RZ/V2H EVK | RZ/V2N EVK |
    |:---|:---|:---|
    |<img src=./img/objectdetection.png width=350>| <img src=./img/objectdetection_v2h.png width=350>  | <img src=./img/objectdetection_v2n.png width=350>  |

    On application window, following information is displayed.  
    - Camera capture  
    - Object Detection result (Bounding boxes, class name and score.)  
    - Processing time  
        - Total AI Time: Sum of all processing time below.  
        - Inference: Processing time taken for AI inference.  
        - PreProcess: Processing time taken for AI pre-processing.  
        - PostProcess: Processing time taken for AI post-processing.<br>(excluding the time for drawing on HDMI screen).  
        
4. To terminate the application, switch the application window to the terminal by using `Super(windows key)+Tab` and press ENTER key on the terminal of the board.


## Application: Configuration 
### AI Model
- YOLOv3: [Darknet](https://pjreddie.com/darknet/yolo/)  
Dataset: [COCO](https://cocodataset.org/#home)  
Input size: 1x3x416x416  
Output1 size: 1x13x13x255  
Output2 size: 1x26x26x255  
Output3 size: 1x52x52x255   

### AI inference time
|Board | AI inference time|
|:---|:---|
|RZ/V2L EVK| Approximately 380ms  |
|RZ/V2H EVK | Approximately 30ms  |
|RZ/V2N EVK | Approximately 77ms  |

### Processing

|Processing | Details |
|:---|:---|
|Pre-processing | Processed by DRP-AI. <br> |
|Inference | Processed by DRP-AI and CPU. |
|Post-processing | Processed by CPU. |


### Image buffer size

|Board | Camera capture buffer size|HDMI output buffer size|
|:---|:---|:---|
|RZ/V2L EVK| VGA (640x480) in YUYV format  | HD (1280x720) in BGRA format  |
|RZ/V2H EVK and RZ/V2N EVK | VGA (640x480) in YUYV format  | FHD (1920x1080) in BGRA format  |


> **Note:** This application allocates the DRP-AI input buffer with **640x640** resolution in order to maintain the same aspect ratio with **416x416** square size of YOLOv3 input shape after the resize pre-processing.  
  
Following is the buffer flow.  

<img src=./img/buffer_flow.png width="800">


## Reference
- For RZ/V2H EVK and RZ/V2N EVK, this application supports USB camera only with 640x480 resolution.  
FHD resolution is supported by e-CAM22_CURZH camera (MIPI).  
Please refer to following URL for how to change camera input to MIPI camera.  
[https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications](https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications#mipi).  

## License
For AI model, see following directory..  
|Board | AI Model | License directory|
|:---|:---|:---|
|RZ/V2L EVK| YOLOv3  | `exe_v2l/licenses`  |
|RZ/V2H EVK| YOLOv3  | `exe_v2h/licenses`  |
|RZ/V2N EVK| YOLOv3  | `exe_v2n/licenses`  |
