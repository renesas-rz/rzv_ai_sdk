# Surface Defect Segmentation Application

## Application: Overview
Surface crack segmentation is the task of automatically identifying and segmenting cracks in images of surfaces. This is a challenging task due to the variability in crack appearance, the presence of noise and other artifacts, and the need to distinguish cracks from other surface features.

Surface crack segmentation has a wide range of applications, including:

- Structural health monitoring: The early detection of cracks in infrastructure can help to prevent major structural failures.
- Road condition assessment: The identification of cracks in roads can help to improve safety and reduce maintenance costs.
- Concrete inspection: The detection of cracks in concrete can help to identify potential problems with the structural integrity of the material.
- Painting and coating inspection: The identification of cracks in paint or coatings can help to prevent the ingress of moisture and other harmful substances.


| Mode | RZ/V2L | RZ/V2H | RZ/V2N |
|:---|:---|:---|:---|
| MIPI Camera| Supported | - | - |
| USB Camera| Supported | Supported |Supported |
| Image | Supported | Supported | Supported |
| Video | Supported | Supported | - |

### Supported Product
<table>
     <tr>
       <th>Product</th>
       <th>Supported AI SDK version</th>
     </tr>
     <tr>
       <td>RZ/V2L Evaluation Board Kit (RZ/V2L EVK)</td>
       <td>RZ/V2L AI SDK v7.00</td>
     </tr>
     <tr>
       <td>RZ/V2H Evaluation Board Kit (RZ/V2H EVK)</td>
       <td>RZ/V2H AI SDK v6.00</td>
     </tr>
     <tr>
       <td>RZ/V2N Evaluation Board Kit (RZ/V2N EVK)</td>
       <td>RZ/V2N AI SDK v6.00</td>
     </tr>
 </table>  

### Demo 

<img src = "./images/crack.gif" width="480">


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
      <td rowspan="4">RZ/V2N</td>
      <td>RZ/V2N EVK</td>
      <td>Evaluation Board Kit for RZ/V2N.</td>
    </tr>
    <tr>
      <td>AC Adapter</td>
      <td>USB Power Delivery adapter for the board power supply.<br>
      60W is required.</td>
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
      Operating Environment: Ubuntu 22.04
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

>**Note 1:** All external devices will be attached to the board and does not require any driver installation (Plug n Play Type)   
**Note 2:** For RZ/V2H EVK, there are USB 2.0 and USB 3.0 ports.  
USB camera needs to be connected to appropriate port based on its requirement.

Connect the hardware as shown below.  

|RZ/V2L EVK | RZ/V2H EVK | RZ/V2N EVK |
 |:---|:---|:---|
 |<img src=./images/hw_conf_v2l.png width=600>|<img src=./images/hw_conf_v2h.png width=600>  |<img src=./images/hw_conf_v2n.png width=600> |

>**Note:** When using the keyboard connected to RZ/V Evaluation Board, the keyboard layout and language are fixed to English.

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
    |RZ/V2H EVK  |`rzv2h_ai_sdk_container`  |
    |RZ/V2N EVK | `rzv2n_ai_sdk_container`  |

    >**Note 1:** Docker environment is required for building the sample application.  


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
    cd ${PROJECT_PATH}/Q09_crack_segmentation/src
    ```

5. Create and move to the `build` directory.
    ```sh
    mkdir -p build && cd build
    ``````
6. Build the application by following the commands below.  
   
    ```sh
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
    make -j$(nproc)
    ```
   
7. The following application file would be generated in the `${PROJECT_PATH}/Q09_crack_segmentation/src/build` directory
    - crack_segmentation

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
|RZ/V2H EVK |[exe_v2h](./exe_v2h)  |  
|RZ/V2N EVK |[exe_v2n](./exe_v2n)  |

Each folder contains following items.
|File | Details |
|:---|:---|
|crack_segmentation_model | Model object files for deployment. |
|crack_segmentation | Application file. |
|video_sample.mp4 | Sample input video for video mode. |
|sample.jpg | Sample input image for image mode. |

### Instruction

1. Copy the following files to the `/home/weston/tvm` directory of the rootfs (SD Card) for the board.
    |File | Details |
    |:---|:---|
    |All files in `EXE_DIR` directory | Including `deploy.so` file. |
    |`crack_segmentation` application file | Generated the file according to [Application File Generation](#application-file-generation) |

2. Check if `libtvm_runtime.so` exists under `/usr/lib` directory of the rootfs (SD card) on the board.

3. Folder structure in the rootfs (SD Card) would look like:

    ```
    |-- usr
    |   `-- lib
    |       `-- libtvm_runtime.so
    `-- home
        `-- weston
            `-- tvm
                |-- crack_segmentation_model
                |   |-- deploy.json
                |   |-- deploy.params
                |   `-- deploy.so
                |-- crack_segmentation
                |-- video_sample.mp4     # For RZ/V2H and RZ/V2L
                `-- sample.jpg
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
    cd /home/weston/tvm/
    su # To change user to root.
    ```
    >**Note:** Root previlage is required to access root owned hardware devices the application use. Run `exit` to end the root user mode.

2. Run the application.

    - For USB Camera Mode
    ```sh
    ./crack_segmentation USB
    ```
    - For MIPI Camera Mode [RZ/V2L only]
    ```sh
    ./crack_segmentation MIPI
    ```
    > Note: MIPI Camera Mode is only supported by RZ/V2L EVK.
    - For Image Mode
    ```sh
    ./crack_segmentation IMAGE sample.jpg
    ```
    > Note: Tested with image file format `.png` and `.jpg`.
    - For Video Input Mode [RZ/V2L and RZ/V2H only]
    ```sh 
    ./crack_segmentation VIDEO video_sample.mp4
    ```
     > Note : Tested with video file format `.mp4` and `.avi`.

    >Note: On RZ/V2L, CPU codec (i.e., MPEG-4, etc.) is not available if you use RZ/V2L AI SDK v7.00 and later. Please see [RZ/V2L AI SDK Configuration](https://renesas-rz.github.io/rzv_ai_sdk/latest/v2l-configuration.html)

    > Note:  On RZ/V2H, CPU codec (i.e., MPEG-4, etc.) is not available if you use RZ/V2H AI SDK v6.00 and later.  Please see [RZ/V2H AI SDK Configuration](https://renesas-rz.github.io/rzv_ai_sdk/latest/v2h-configuration.html).
     
    > Note : On RZ/V2N, VIDEO mode is not available since hardware decoding (H.264/H.265) cannot be used when DRP-AI is running. See [RZ/V2N AI SDK specification](https://renesas-rz.github.io/rzv_ai_sdk/latest/ai-sdk.html#footnote_v2n_drp_ai) for more details.
  
3. Following window shows up on HDMI screen.  

    |RZ/V2L EVK | RZ/V2H EVK and RZ/V2N EVK* |
    |:---|:---|
    |<img src=./images/Q09_crack_pic_v2l.png width=350>| <img src=./images/Q09_crack_pic_v2h.png width=350>  |

    > *Performance in the screenshot is for RZ/V2H EVK.

    - AI inferece time is shown on top right corner.
    - For RZ/V2L: The cracks detected are shown in green mask/region.
    - For RZ/V2H and RZ/V2N: A heatmap is used to illustrate the intensity of detected cracks, with hotter areas representing more severe cracks.
        
4. To terminate the application, switch the application window to the terminal by using `Super(windows key)+Tab` and press ENTER key on the terminal of the board.
5. Run `exit` command to end the root user mode.
    ```
    exit
    ```


## Application: Configuration 
### AI Model
- Model: [Unet](https://arxiv.org/pdf/1505.04597.pdf) model with resnet34 backbone.
- Dataset: [Crack Segmentation Dataset](https://www.kaggle.com/datasets/lakshaymiddha/crack-segmentation-dataset)
- Input Shape: 1x3x224x224
- Output Shape: 1x1x224x224  

### AI inference time
|Board | AI inference time|
|:---|:---|
|RZ/V2L EVK| Approximately  80 ms  |
|RZ/V2H EVK | Approximately  8 ms  |
|RZ/V2N EVK | Approximately  16 ms  |

### Processing

|Processing | Details |
|:---|:---|
|Pre-processing | Processed by CPU. |
|Inference | Processed by DRP-AI and CPU. |
|Post-processing | Processed by CPU. |


### Image buffer size

|Board | Camera capture buffer size|HDMI output buffer size|
|:---|:---|:---|
|RZ/V2L EVK | VGA (640x480) in YUYV format  | HD (1280x720) in BGRA format  |
|RZ/V2H EVK and RZ/V2N EVK | VGA (640x480) in YUYV format  | FHD (1920x1080) in BGRA format  |
  

## Reference
- For RZ/V2H EVK and RZ/V2N EVK, this application supports USB camera only with 640x480 resolution.     
FHD resolution is supported by e-CAM22_CURZH camera (MIPI).   
Please refer to following URL for how to change camera input to MIPI camera.  
[https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications](https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications#mipi).  

## License
Apache License 2.0   
For third party OSS library, please see the source code file itself. 