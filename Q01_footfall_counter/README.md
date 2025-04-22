# Footfall Counter

## Application: Overview
This application is designed to track and count the number of people entering a designated boundary line,
while simultaneously reducing the count for those exiting the boundary line.

Additionally, the application 
has the ability to measure the time spent by a particular person within a specified region of interest.

This software could be useful in a variety of settings, such as retail stores, museums, and events,
where managers need to monitor and analyze traffic flow and customer behavior.

The AI model used for the sample application is [YOLOV3/Tiny YOLOv3](https://arxiv.org/pdf/1804.02767.pdf).

**NOTE:** This sample application can be used to track different objects, like animal, car, etc. The list of objects that can be tracked are provided in [coco labels txt](./exe/coco-labels-2014_2017.txt) file. 

It has following mode of running.

| Mode | RZ/V2L | RZ/V2H and RZ/V2N |
|:---|:---|:---|
| USB Camera| Supported | Supported |
| MIPI Camera| Supported | - |

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
       <td>RZ/V2N AI SDK v5.00</td>
     </tr>
 </table>

### Demo 
Following is the demo for RZ/V2H EVK.  
<img src = "./images/ObjectTracking.gif" width="480" height="320">

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
            MIPI Camera Module(Google Coral Camera)
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

|RZ/V2L EVK | RZ/V2H EVK | RZ/V2N EVK |
 |:---|:---|:---|
 |<img src=./images/hw_conf_v2l.png width=600>|<img src=./images/hw_conf_v2h.png width=600>  |<img src=./images/hw_conf_v2n.png width=600>  |

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
    |RZ/V2H EVK and RZ/V2N EVK|`rzv2h_ai_sdk_container`  |

    >**Note 1:** Docker environment is required for building the sample application.  
    >**Note 2:** Since RZ/V2N is a brother chip of RZ/V2H, the same environment can be used. 


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
    cd ${PROJECT_PATH}/Q01_footfall_counter/src
    ```
5. Create and move to the `build` directory.
    ```sh
    mkdir -p build && cd build
    ``````
6. Build the application by following the commands below.  
   **For RZ/V2L**
    ```sh
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
    make -j$(nproc)
    ```
    **For RZ/V2H and RZ/V2N**
    ```sh
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake -DV2H=ON ..
    make -j$(nproc)
    ```
    >Note: Since RZ/V2N is a brother chip of RZ/V2H, the same source code can be used.
7. The following application file would be generated in the `${PROJECT_PATH}/Q01_footfall_counter/src/build` directory
    - object_tracker


## Application: Deploy Stage
### Prerequisites
This section expects the user to have completed Step 7-1 of [Getting Started Guide](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started.html#step7) provided by Renesas. 

After completion of the guide, the user is expected of following things.
- microSD card setup is done.

### File Configuration
For ease of deployment, all deployable files and folders are provided in the following folders.  
|Board | `EXE_DIR` |
|:---|:---|
|RZ/V2L EVK|[exe_v2l](./exe_v2l)  |
|RZ/V2H EVK and RZ/V2N EVK|[exe_v2h](./exe_v2h)  |
 > Note: Since RZ/V2N is a brother chip of RZ/V2H, the same execution environment can be used.  

Each folder contains following items.

|File | Details |
|:---|:---|
|tinyyolov3_onnx | **[RZ/V2L only]** Model object files for deployment. |
|d-yolov3 | **[RZ/V2H and RZ/V2N]** Model object files for deployment. |
|coco-labels-2014_2017.txt | Label list for Object Detection. |
|config.ini | user input config for line, region and object. |
|data.txt | File to save user input for line, region. |
|background_image.jpg | Background image. |
|object_tracker | application file. |

### Instruction
1. **[For RZ/V2H and RZ/V2N]** Run following commands to download the necessary file.  
    ```sh
      cd <path_to_data_folder_on_host>/data/rzv_ai_sdk/Q01_footfall_counter/exe_v2h/d-yolov3
      wget https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v5.00/Q01_footfall_counter_deploy_tvm_v2h-v230.so
    ```
    > Note: Since RZ/V2N is a brother chip of RZ/V2H, the same execution environment can be used.  
2. **[For RZ/V2H and RZ/V2N]** Rename the `Q01_footfall_counter_deploy_*.so` to `deploy.so`.
    ```sh
    mv Q01_footfall_counter_deploy_*.so deploy.so
    ```
3. Copy the following files to the `/home/root/tvm` directory of the rootfs (SD Card) for the board.
    |File | Details |
    |:---|:---|
    |All files in `EXE_DIR` directory | Including `deploy.so` file. |
    |`object_tracker` application file | Generated the file according to [Application File Generation](#application-file-generation) |

4. Check if `libtvm_runtime.so` exists under `/usr/lib64` directory of the rootfs (SD card) on the board.

5. Folder structure in the rootfs (SD Card) would look like:
    ```
    |-- usr
    |   `-- lib64
    |       `-- libtvm_runtime.so
    `-- home
        `-- root
            `-- tvm
                |-- tinyyolov3_onnx           #RZ/V2L only        
                |   |-- deploy.json           #RZ/V2L only
                |   |-- deploy.params         #RZ/V2L only
                |   `-- deploy.so             #RZ/V2L only
                |
                |-- d-yolov3                  #RZ/V2H and RZ/V2N
                |   |-- deploy.json           #RZ/V2H and RZ/V2N
                |   |-- deploy.params         #RZ/V2H and RZ/V2N
                |   `-- deploy.so             #RZ/V2H and RZ/V2N
                |-- config.ini
                |-- coco-labels-2014_2017.txt
                |-- data.txt
                |-- background_image.jpg
                `-- object_tracker
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
    - For USB Camera Mode
    ```sh
    ./object_tracker USB [--setup=true]
    ```
    - For MIPI Camera Mode (RZ/V2L only)
    ```sh
    ./object_tracker MIPI [--setup=true]
    ```
    >**Note:** Enabling --setup=true option allows user's to draw line and polygon. 
4. If setup option is enabled, a window to configure line and polygon will appear.
    1. DrawApp

        Click either the "Draw Line" or "Draw Polygon" button to open the drawing board for the selected shape.

        <img src=./images/draw_1.png width=420>
    2. Draw Line

        Hold the left mouse button and move the mouse to draw a line. Click "Done" to exit.

        <img src=./images/draw_2.png width=420>
    3. Draw Polygon

        Click to place polygon vertices (at least 3). The shape must not cross the red line. Click "Done" to finish or "Reset" to redraw.

        <img src=./images/draw_3.png width=420>
    4. Save

        After drawing a line and polygon, click the "Save" button to save and exit the DrawApp window.

        <img src=./images/draw_4.png width=420>
5. Following window shows up on HDMI screen.  

    |RZ/V2L EVK | RZ/V2H EVK and RZ/V2N EVK* |
    |:---|:---|
    |<img src=./images/Q01_image_V2L.png width=420>| <img src=./images/Q01_image_V2H.png width=420>  |
    
    > *Performance in the screenshot is for RZ/V2H EVK.

    <!-- On application window, following information is displayed.  
    - Camera capture  
    - AI result 
    - Processing time  
        - Total AI Time: Sum of all processing time below.  
        - Inference: Processing time taken for AI inference.  
        - PreProcess: Processing time taken for AI pre-processing.  
        - PostProcess: Processing time taken for AI post-processing.<br>(excluding the time for drawing on HDMI screen).   -->
        
      - The application will track the person if the person crossed the `red line` and increment the `human count` and decrement it when the person crosses again.
      - As per current logic, left to right crossing will increment the human count, and right to left crossing will decrement the count.
      - Users need to arrange the line according to the requirement.
      - The application will also keep track of the person in the available region `green box` and increment the `person in region` count. It will also decrement the count if the person leaves the area.
      - Each person tracked is given a unique `id`.
          - The `time` parameter of the tracked person indicates the time spent on the desired location. This incremented at regular interval.

5. To terminate the application, switch the application window to the terminal by using `Super(windows key)+Tab` and press ENTER key on the terminal of the board.

> Note: Since RZ/V2N is a brother chip of RZ/V2H, the same execution environment is used, which causes inconsistency in display contents,  
 i.e., RZ/V2N application log contains "RZ/V2H".  
 This will be solved in the future version.

## Application: Configuration 
### AI Model
#### RZ/V2L EVK
- TinyYOLOv3: [Darknet](https://pjreddie.com/darknet/yolo/)  
Dataset: [COCO](https://cocodataset.org/#home)  
Input size: 1x3x416x416  
Output1 size: 1x13x13x255  
Output2 size: 1x26x26x255  

#### RZ/V2H EVK and RZ/V2N EVK
- YOLOv3: [Darknet](https://pjreddie.com/darknet/yolo/)  
Dataset: [COCO](https://cocodataset.org/#home)  
Input size: 1x3x416x416  
Output1 size: 1x13x13x255  
Output2 size: 1x26x26x255  
Output3 size: 1x52x52x255   

### AI inference time

|Board | AI model | AI inference time|
|:---|:---|:---|
|RZ/V2L EVK|Tiny YOLOv3| Approximately 68 ms  |
|RZ/V2H EVK |YOLOv3 | Approximately 29 ms  |
|RZ/V2N EVK |YOLOv3 | Approximately 87 ms  |

### Processing

|Processing | RZ/V2L EVK | RZ/V2H EVK and RZ/V2N EVK |
|:---|:---|:---|
|Pre-processing | Processed by CPU. | Processed by CPU. |
|Inference | Processed by DRP-AI and CPU. | Processed by DRP-AI and CPU. |
|Post-processing | Processed by CPU. |Processed by CPU. |


### Image buffer size

|Board | Camera capture buffer size|HDMI output buffer size|
|:---|:---|:---|
|RZ/V2L EVK| VGA (640x480) in YUYV format  | HD (1280x720) in BGRA format  |
|RZ/V2H EVK and RZ/V2N EVK | VGA (640x480) in YUYV format  | FHD (1920x1080) in BGRA format  |
  

### Explanation of the `config.ini` file 

The file contains two sections: [**tracking**] and [**display**].

- The [**tracking**] section contains three key-value pairs.\
The conf value is a confidence threshold used for object tracking, and the kmin value is the minimum number of key-points required for tracking. The objects value is for the class that should be tracked.

>**Note:** The object tracked here is of class "Person", it can be changed to other classes present on the coco labels.

- The [**display**] section contains two key-value pairs.\
The display_text and region_display_text is for the texts that should be displayed in UI.

To modify the configuration settings, edit the values in this file using VI Editor, from the Board.

### Time Tracking Backend Integration

>**Note:**  As per recent development status, the application have been tested for 100 numbers of people on the certain region without any error occurring, so if the use cases are expected for the number of people on the certain region to be less than 100, there is no need for code modification.

- Currently for storing the person id and the time spent on the region of interest [ROI] is stored on the board memory as key-value pair. As board memory consumption is limited, this procedure could be moved to the Database/Cache which could be hosted on the cloud or host machine.

- Customers can install SQL Database/Cache on the cloud or host-machine. 

- After each sec the application can call the API for inserting the data on the DB, if not present. and show the time taken for the persons in the ROI

- When the person goes out of the ROI, the application can call the API to remove the person data from the DB and cache.

## Reference
- For RZ/V2H EVK and RZ/V2N EVK, this application supports USB camera only with 640x480 resolution.  
FHD resolution is supported by e-CAM22_CURZH camera (MIPI).  
Please refer to following URL for how to change camera input to MIPI camera.  
[https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications](https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications#mipi).  

## License 
Apache License 2.0   
For third party OSS library, please see the source code file itself.