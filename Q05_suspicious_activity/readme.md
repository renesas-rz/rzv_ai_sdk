# Suspicious Activity Classification Application

## Application: Overview
The suspicious  activity classification application allows to classify between Violence and Non-Violence from video input using a custom AI model which has a CNN module for feature extraction and MLP for aggregating features.


It has following mode of running.
| Mode | RZ/V2L | RZ/V2H and RZ/V2N |
|:---|:---|:---|
| MIPI Camera | Supported | - |
| USB Camera | Supported | Supported |
| Video | Supported | Supported |


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
<img src="./images/SuspiciousActivity.gif" width="480" height="320">

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
 |<img src=./images/hw_conf_v2l.png width=600>|<img src=./images/hw_conf_v2h.png width=600>  |<img src=./images/hw_conf_v2n.png width=600> |

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
    |RZ/V2H EVK and RZ/V2N EVK |`rzv2h_ai_sdk_container`  |

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
    cd ${PROJECT_PATH}/Q05_suspicious_activity/src
    ```
5. Create and move to the `build` directory.
    ```sh
    mkdir -p build && cd build
    ```
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
7. The following application file would be generated in the `${PROJECT_PATH}/Q05_suspicious_activity/src/build` directory
    - suspicious_activity


## Application: Deploy Stage
### Prerequisites
This section expects the user to have completed Step 7-1 of [Getting Started Guide](https://renesas-rz.github.io/rzv_ai_sdk/latest/getting_started.html#step7) provided by Renesas. 

After completion of the guide, the user is expected of following things.
- microSD card setup is done.

### File Configuration
For the ease of deployment all the deployable file and folders are provided in following folders.  
|Board | `EXE_DIR` |
|:---|:---|
|RZ/V2L EVK|[exe_v2l](./exe_v2l)  |
|RZ/V2H EVK and RZ/V2N EVK|[exe_v2h](./exe_v2h)  |  
 > Note: Since RZ/V2N is a brother chip of RZ/V2H, the same execution environment can be used.  

Each folder contains following items.
|File | Details |
|:---|:---|
|cnn_module | CNN Model object files for deployment |
|mlp_module | MLP Model object files for deployment |
|suspicious_activity | application file |
|violence.mp4 | sample video for VIDEO mode |
|non_violence.mp4 | sample video for VIDEO mode  |

>**Note:** For **V2L** the CNN and MLP part are combined into a single model and have a combined_module directory which contains object files for deployment.
### Instruction

1. Copy the following files to the `/home/root/tvm` directory of the rootfs (SD Card) for the board.
    |File | Details |
    |:---|:---|
    |All files in `EXE_DIR` directory | Including `deploy.so` file. |
    |`suspicious_activity` application file | Generated the file according to [Application File Generation](#application-file-generation) |

2. Check if `libtvm_runtime.so` exists under `/usr/lib64` directory of the rootfs (SD card) on the board.

3. Folder structure in the rootfs (SD Card) would look like:
    
    For **V2H and V2N**:
    ```
    |-- usr
    |   `-- lib64
    |       `-- libtvm_runtime.so
    `-- home
        `-- root
            `-- tvm
                |-- cnn_module  
                |   |-- deploy.json             
                |   |-- deploy.params           
                |   `-- deploy.so               
                |-- mlp_module          
                |   |-- deploy.json             
                |   |-- deploy.params           
                |   `-- deploy.so               
                |-- suspicious_activity
                |-- violence.mp4 
                `-- non_violence.mp4 
    ```
    For **V2L**:
    ```
    |-- usr
    |   `-- lib64
    |       `-- libtvm_runtime.so
    `-- home
        `-- root
            `-- tvm
                |-- combined_module  
                |   |-- deploy.json             
                |   |-- deploy.params           
                |   `-- deploy.so               
                |-- suspicious_activity
                |-- violence.mp4 
                `-- non_violence.mp4 
    ```
>**Note:** The directory name could be anything instead of `tvm`. If you copy the whole `EXE_DIR` folder on the board, you are not required to rename it `tvm`. For **V2L** the `CNN` and `MLP` part are combined into a single model as shown above.

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
    
2. Run the application.
    - For video Mode
    ```sh
   ./suspicious_activity VIDEO violence.mp4
    ```
    - For USB Camera Mode
    ```sh
    ./suspicious_activity USB
    ```
    - For MIPI Camera Mode (RZ/V2L only)
    ```sh
    ./suspicious_activity MIPI
    ```

3. Following window shows up on HDMI screen.  

    |RZ/V2L EVK | RZ/V2H EVK and RZ/V2N EVK* |
    |:---|:---|
    |<img src=./images/v2l_result.jpg width=350>| <img src=./images/v2h_result.jpg width=350>  |

    > *Performance in the screenshot is for RZ/V2H EVK.

    On application window, following information is displayed.  
    - Camera capture  
    - Video classification result (Graph plot, video classification result and score.)
    - Processing time  
        - Total AI Time: Sum of all processing time below.  
        - Inference: Processing time taken for AI inference.  
        - PreProcess: Processing time taken for AI pre-processing.  
        - PostProcess: Processing time taken for AI post-processing.<br>(excluding the time for drawing on HDMI screen).  
        
4. To terminate the application, switch the application window to the terminal by using `Super(windows key)+Tab ` and press ENTER key on the terminal of the board.

> Note: Since RZ/V2N is a brother chip of RZ/V2H, the same execution environment is used, which causes inconsistency in display contents,  
 i.e., RZ/V2N application log contains "RZ/V2H".  
 This will be solved in the future version.

## Application: Configuration 
### AI Model

##### CNN Module

```python
================================================================
        Layer (type)               Output Shape         Param #
================================================================
            Conv2d-1         [-1, 32, 112, 112]             896
            Conv2d-2           [-1, 64, 28, 28]          18,496
            Conv2d-3            [-1, 128, 7, 7]          73,856
================================================================
Total params: 93,248
Trainable params: 93,248
Non-trainable params: 0
----------------------------------------------------------------
Input size (MB): 5.74
Forward/backward pass size (MB): 3.49
Params size (MB): 0.36
Estimated Total Size (MB): 9.59
----------------------------------------------------------------
```

##### MLP Module

```python
================================================================
        Layer (type)               Output Shape         Param #
================================================================
            Linear-1              [-1, 10, 256]         295,168
            Linear-2                    [-1, 2]           1,026
================================================================
Total params: 296,194
Trainable params: 296,194
Non-trainable params: 0
----------------------------------------------------------------
Input size (MB): 0.04
Forward/backward pass size (MB): 0.02
Params size (MB): 1.13
Estimated Total Size (MB): 1.19
----------------------------------------------------------------

```
>**Note:** For **V2L** the CNN and MLP part are combined into a single model.

#### Dataset 
Dataset Contains 1000 Violence and 1000 non-violence videos collected from youtube videos.
[Dataset-Link](https://www.kaggle.com/datasets/karandeep98/real-life-violence-and-nonviolence-data)

### Accuracy
|Training Accuracy | Validation Accuracy |
|:---|:---|
|94.2% | 90.7% |

### AI inference time
|Board | Inference time |
|:---|:---|
|RZ/V2L EVK | Approximately 30 ms |
|RZ/V2H EVK | Approximately 1~27msec|
|RZ/V2N EVK | Approximately 1~26msec|

### Processing

|Processing | Details |
|:---|:---|
|Pre-processing | Processed by CPU. <br> |
|Inference | Processed by DRP-AI and CPU. |
|Post-processing | Processed by CPU. |


### Image buffer size

|Board | Camera capture buffer size|HDMI output buffer size|
|:---|:---|:---|
|RZ/V2L EVK| VGA (640x480) in YUYV format  | HD (1280x720) in BGRA format  |
|RZ/V2H EVK and RZ/V2N EVK| VGA (640x480) in YUYV format  | FHD (1920x1080) in BGRA format  |
  
  
## Reference
 
- For RZ/V2H EVK and RZ/V2N EVK, this application supports USB camera only with 640x480 resolution.\
To use FHD, please use MIPI camera.\
Please refer to following URL for how to change camera input to MIPI camera.\
[https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications](https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications#mipi).

## License
Apache License 2.0
For third party OSS library, please see the source code file itself. 