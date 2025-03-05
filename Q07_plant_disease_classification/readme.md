# Plant leaf disease classification

## Application: Overview
The Plant leaf disease classification application allows to classify between 38 different plant leaf disease/healthy. The developed model is able to recognize 38 different types of plant disease out of 14 different plants. The label list is provided at [`plant_leaf_disease_class.txt`](./exe_v2h/plant_leaf_disease_class.txt)


The application could be used to classify plant leaf whether healthy or not in agricultural sector 

It has 4 modes of running.

|Mode | RZ/V2L | RZ/V2H and RZ/V2N |
|:---|:---|:---|
|MIPI Camera|`Supported`|`-`|
|USB Camera|`Supported`|`Supported`|
|Image|`Supported`|`Supported`|
|Video|`Supported`|`Supported`|

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
      <td>RZ/V2H AI SDK v5.00</td>
    </tr>
    <tr>
      <td>RZ/V2N Evaluation Board Kit (RZ/V2N EVK)</td>
      <td>RZ/V2N AI SDK v5.00</td>
    </tr>
</table>

### Demo

Following is the demo for RZ/V2L EVK.  
<img src="./images/plant_leaf_disease.gif" width="480" height="320">

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
    cd ${PROJECT_PATH}/Q07_plant_disease_classification/src
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
7. The following application file would be generated in the `${PROJECT_PATH}//Q07_plant_disease_classification/src/build` directory
    - plant_leaf_disease_classify


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
|plant_dis_onnx | Model object files for deployment |
|plant_leaf_disease_class.txt | Label list for Object Detection |
|plant_leaf_disease_classify | application file |
|sampleimg.jpg | sample image for image mode |


### Instruction
1. Copy the following files to the `/home/root/tvm` directory of the rootfs (SD Card) for the board.
    |File | Details |
    |:---|:---|
    |All files in `EXE_DIR` directory | Including `deploy.so` file. |
    |`plant_leaf_disease_classify` application file | Generated the file according to [Application File Generation](#application-file-generation) |

2. Check if `libtvm_runtime.so` exists under `/usr/lib64` directory of the rootfs (SD card) on the board.

3. Folder structure in the rootfs (SD Card) would look like:
    ```
    |-- usr
    |   `-- lib64
    |       `-- libtvm_runtime.so
    `-- home
        `-- root
            `-- tvm
                |-- plant_dis_onnx
                |   |-- deploy.json
                |   |-- deploy.params
                |   `-- deploy.so 
                |-- plant_leaf_disease_class.txt
                |-- plant_leaf_disease_classify
                |-- plantvid.mp4
                `-- sampleimg.jpg
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
    
2. Run the application.
    - For Image Mode
    ```sh
    ./plant_leaf_disease_classify IMAGE sampleimg.jpg
    ```
    - For USB Camera Mode
    ```sh
    ./plant_leaf_disease_classify USB
    ```
    - For MIPI Camera Mode [RZ/V2L only]
    ```sh
    ./plant_leaf_disease_classify MIPI
    ```
    - For VIDEO Mode
    ```sh
    ./plant_leaf_disease_classify VIDEO plantvid.mp4
    ```
    > Note : Due to the number of equipped IP on RZ/V2N, this application will show the error when using the hardware decoding (H.264/H.265) with VIDEO input for RZ/V2N.  CPU decoding, i.e., MJPEG, can be used.

3. Select area for classification.

    The user needs to draw the box for which specific area to classify.

    After selecting the area (rectangle box drawn via mouse connected to board), press Enter key on keyboard connected to the board, or click "Done" button at the top-left corner, to trigger the inference and shows the classification result.
    
      <img src=./images/select_roi.jpg width=350>

4. Following window shows up on HDMI screen.  

    |RZ/V2L EVK | RZ/V2H EVK and RZ/V2N EVK* |
    |:---|:---|
    |<img src=./images/resl_v2l.png width=350>| <img src=./images/resl_v2h.png width=350>  |

    > *Performance in the screenshot is for RZ/V2H EVK.

    On application window, following information is displayed.  
    - Camera capture  
    - Classification result (class name, status and score.)
    - Processing time taken for AI inference.
    - Frames per Second
    - Top 5 Classification Results (Based on the score)  
        
5. To terminate the application, follow the termination method below.
   - For RZ/V2L, application can be terminated by pressing `Esc` key on the USB keyboard connected to the board or alternatively, user can force
   close the application using CTRL+c on the board console.
   - For RZ/V2H and RZ/V2N, switch the application window to the terminal by using `Super(windows key)+Tab ` and press ENTER key on the terminal of the board.

> Note: Since RZ/V2N is a brother chip of RZ/V2H, the same execution environment is used, which causes inconsistency in display contents,  
i.e., RZ/V2N application log contains "RZ/V2H".  
This will be solved in the future version.

## Application: Configuration 
### AI Model

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


```
#### Dataset 
The class labels are mentioned in the [`plant_leaf_disease_class.txt`](./exe_v2h/plant_leaf_disease_class.txt)
This dataset consists of about 87K rgb images of healthy and diseased crop leaves which is categorized into 38 different classes. The total dataset is divided into 80/20 ratio of training and validation set preserving the directory structure. A new directory containing 33 test images is created later for prediction purpose.

[Dataset Link](https://www.kaggle.com/datasets/vipoooool/new-plant-diseases-dataset)

### AI inference time
|Board | AI inference time|
|:---|:---|
|RZ/V2L EVK| Approximately 70 ms  |
|RZ/V2H EVK | Approximately  2 ms  |
|RZ/V2N EVK | Approximately  6 ms  |

### Processing

|Processing | RZ/V2L EVK | RZ/V2H EVK and RZ/V2N EVK |
|:---|:---|:---|
|Pre-processing | Processed by CPU | Processed by CPU |
|Inference | Processed by DRP-AI and CPU | Processed by DRP-AI and CPU |
|Post-processing | Processed by CPU | Processed by CPU |


### Image buffer size

|Board | Camera capture buffer size|HDMI output buffer size|
|:---|:---|:---|
|RZ/V2L EVK| VGA (640x480) in YUYV format  | HD (1280x720) in BGRA format  |
|RZ/V2H EVK and RZ/V2N EVK | VGA (640x480) in YUYV format  | FHD (1920x1080) in BGRA format  |
  
  
## Reference
 
- For RZ/V2H EVK and RZ/V2N EVK, this application supports USB camera only with 640x480 resolution.\
To use FHD, please use MIPI camera.\
Please refer to following URL for how to change camera input to MIPI camera.\
[https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications](https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications#mipi).

## License
Apache License 2.0   
For third party OSS library, please see the source code file itself. 
