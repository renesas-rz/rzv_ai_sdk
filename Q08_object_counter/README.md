# Object Counter Application

## Application: Overview
The Object Counter Application is a user-friendly and efficient generic software tool that can be used to create custom counting applications for any scenario. This application uses the advanced YOLOV3/Tiny YOLOv3 algorithm to identify and count objects in images or videos.

### Use Cases
The Generic Counter Application is a powerful tool that can be used to count objects in a variety of settings, including:

- **Animal Counting**: The application can be fine tuned to count the animals only. This application can be used for zoo or farm monitoring, also could be used to prevent the road hazards due to animal interference. The list of animals on which the AI model is trained is available in [animal_class.txt](./exe/animal/animal_class.txt)

- **Vehicle Counting**: The application can be fine tuned to count the vehicle instances per frame. This application can then be used for traffic monitoring at government/corporate buildings.The list of vehicles on which the AI model is trained is available in [vehicle_class.txt](./exe/vehicle/vehicle_class.txt)

- **General Counting**: The general counting applications can be used to count any type of object, from people and cars to inventory and products. They are often used in businesses to track customer traffic, inventory levels, and employee productivity. The list of objects on which the AI model is trained is available in [coco_class.txt](./exe/coco/coco_class.txt)

The other use cases could be: 

- **Manufacturing**: The application can be used to count parts on a production line or to measure the output of a machine.
- **Retail**: The application can be used to count products on a shelf or to track the number of customers in a store.
- **Safety**: The application can be used to count people in a crowd or to monitor the traffic flow in a city.

### Key Features
Here are some of the key features of the Generic Counter Application:

- **Automatic Object Detection**: 
    The application utilizes YOLOv3/Tiny YOLOv3 model for detection, identifying and localizing objects specified within the provided frame.
- **Flexible**: 
    The application can be customized to meet the specific needs of any counting scenario.
- **Customizable Settings**: 
    Users can adjust the detection and classification parameters by using the config file provided in the repository.

It has following camera input modes.
| Mode | RZ/V2L | RZ/V2H and RZ/V2N |
|:---|:---|:---|
| MIPI Camera| Supported | - |
| USB Camera| Supported | Supported |

Users can select detection target from following list
- Animal
- Vehicle
- General (COCO dataset)

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

<img src = "./images/Q08_object_counter.gif" width="480">

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
 |<img src=./images/hw_conf_v2l.png width=600>|<img src=./images/hw_conf_v2h.png width=600>  |<img src=./images/hw_conf_v2n.png width=600> |

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
3. Go to the application source code directory.  
    ```sh
    cd ${PROJECT_PATH}/Q08_object_counter/src
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
    **For RZ/V2H and RZ/V2N**
    ```sh
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake -DV2H=ON ..
    make -j$(nproc)
    ```
    >Note: Since RZ/V2N is a brother chip of RZ/V2H, the same source code can be used.
6. The following application file would be generated in the `${PROJECT_PATH}/Q08_object_counter/src/build` directory
    - object_counter


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
|RZ/V2H EVK and RZ/V2N EVK|[exe_v2h](./exe_v2h)  |  
 > Note: Since RZ/V2N is a brother chip of RZ/V2H, the same execution environment can be used.  

Each folder contains following items.
|File | Details |
|:---|:---|
|coco/tinyyolov3_onnx | **[RZ/V2L only]** Model object files for Coco Detection |
|coco/yolov3_onnx | **[RZ/V2H and RZ/V2N]** Model object files for Coco Detection |
|coco/coco_class.txt | Label list for Coco Detection |
|coco/config.ini | User input model config object | 
|animal/animal_onnx | Model object files for Animal Detection |
|animal/animal_class.txt | Label list for Animal Detection |
|animal/config.ini | User input model config object | 
|vehicle/vehicle_onnx | Model object files for Vehicle Detection |
|vehicle/vehicle_class.txt | Label list for Vehicle Detection |
|vehicle/config.ini | User input model config object | 
|app_conf.ini | User input application config object |
|object_counter | Application file |


### Instruction
1. **[For RZ/V2H and RZ/V2N]** Run following commands to download the necessary file.  
Replace each variable according to your board.  
    ```sh
    cd <path_to_data_folder_on_host>/data/Q08_object_counter/<EXE_PATH> 
    wget <URL>
    ```
    | Target | `EXE_PATH` |`URL` |`SO_FILE` |`File Location` |
    |:---|:---|:---|:---|:---|
    |Animal|[exe_v2h/animal/animal_onnx](./exe_v2h/animal/animal_onnx) | `https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v5.00/Q08_object_counter_animal_deploy_tvm_v2h-v230.so` |<span style="font-size: small">`Q08_object_counter_animal_deploy_tvm_v2h-v230.so`</span> |[Release v5.00](https://github.com/renesas-rz/rzv_ai_sdk/releases/tag/v5.00/)  |
    |Vehicle|[exe_v2h/vehicle/vehicle_onnx](./exe_v2h/vehicle/vehicle_onnx) | `https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v5.00/Q08_object_counter_vehicle_deploy_tvm_v2h-v230.so` |<span style="font-size: small">`Q08_object_counter_vehicle_deploy_tvm_v2h-v230.so`</span> |[Release v5.00](https://github.com/renesas-rz/rzv_ai_sdk/releases/tag/v5.00/)  |
    |COCO|[exe_v2h/coco/yolov3_onnx](./exe_v2h/coco/yolov3_onnx) | `https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v5.00/Q08_object_counter_coco_deploy_tvm_v2h-v230.so` |<span style="font-size: small">`Q08_object_counter_coco_deploy_tvm_v2h-v230.so`</span> |[Release v5.00](https://github.com/renesas-rz/rzv_ai_sdk/releases/tag/v5.00/)  |
    > Note: Since RZ/V2N is a brother chip of RZ/V2H, the same execution environment can be used.

    - E.g., for Animal counting, use following commands.
        ```sh
        cd <path_to_data_folder_on_host>/data/rzv_ai_sdk/Q08_object_counter/exe_v2h/animal/animal_onnx
        wget https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v5.00/Q08_object_counter_animal_deploy_tvm_v2h-v230.so
        ```
2. **[For RZ/V2H and RZ/V2N]** Rename the `Q08_object_counter_*.so` to `deploy.so`.
    ```sh
    mv Q08_object_counter_*.so deploy.so
    ```
3. Copy the following files to the `/home/root/tvm` directory of the rootfs (SD Card) for the board.
    |File | Details |
    |:---|:---|
    |All files in `EXE_DIR` directory | Including `deploy.so` file. |
    |`object_counter` application file | Generated the file according to [Application File Generation](#application-file-generation) |

4. Check if `libtvm_runtime.so` exists under `/usr/lib64` directory of the rootfs (SD card) on the board.

5. Folder structure in the rootfs (SD Card) would look like:
    ```
    |-- usr
    |   `-- lib64
    |       `-- libtvm_runtime.so
    `-- home
        `-- root
            `-- tvm
                |-- coco
                |   |-- tinyyolov3_onnx       #RZ/V2L only
                |   |   |-- deploy.json       #RZ/V2L only
                |   |   |-- deploy.params     #RZ/V2L only
                |   |   `-- deploy.so         #RZ/V2L only
                |   |
                |   |-- yolov3_onnx           #RZ/V2H and RZ/V2N
                |   |   |-- deploy.json       #RZ/V2H and RZ/V2N
                |   |   |-- deploy.params     #RZ/V2H and RZ/V2N
                |   |   `-- deploy.so         #RZ/V2H and RZ/V2N
                |   |-- coco_class.txt 
                |   `-- config.ini
                |-- animal
                |   |-- animal_onnx
                |   |   |-- deploy.json
                |   |   |-- deploy.params
                |   |   `-- deploy.so
                |   |-- animal_class.txt
                |   `-- config.ini
                |-- vehicle
                |   |-- vehicle_onnx
                |   |   |-- deploy.json
                |   |   |-- deploy.params
                |   |   `-- deploy.so
                |   |-- vehicle_class.txt
                |   `-- config.ini
                |-- app_conf.ini
                `-- object_counter
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

2. Change the values in `app_conf.ini` as per the requirements. Detailed explanation of the `app_conf.ini` file is given at [below section](#explanation-of-the-app_confini-file).
    
    ```sh
    vi app_conf.ini
    ```

3. Run the application.
    ```sh
    ./object_counter <mode> <camera>
    ```    
    - mode options
        |Value  |Description                          |
        |-------|-------------------------------------|
        |COCO   | Detects coco objects listed         |
        |animal | Detects animals listed              |
        |vehicle| Detects automobiles listed          |   
    
    >**Note:** The mode will be the section name in app_conf.ini file.

    - camera options      
        |Value|Description                            |
        |-----|---------------------------------------|
        |MIPI | MIPI camera as input **[RZ/V2L only]**|
        |USB  | USB camera as input                   |    

    For example, to run in "animal" mode with a USB camera, write the following command.    
    ```sh
    ./object_counter animal USB
    ```

3. Following window shows up on HDMI screen.  

    |RZ/V2L EVK (Animal) | RZ/V2H EVK and RZ/V2N EVK* (Animal) |
    |:---|:---|
    |<img src=./images/Q08_animal.png width=350>| <img src=./images/animal_v2h.png width=350>  |

    > *Performance in the screenshot is for RZ/V2H EVK.

    On application window, following information is displayed.  
    - Camera capture  
    - AI result 
    - Processing time  
        <!-- - Total AI Time: Sum of all processing time below.  
        - Inference: Processing time taken for AI inference.  
        - PreProcess: Processing time taken for AI pre-processing.  
        - PostProcess: Processing time taken for AI post-processing.<br>(excluding the time for drawing on HDMI screen).   -->
        
4. To terminate the application, switch the application window to the terminal by using `Super(windows key)+Tab` and press ENTER key on the terminal of the board.

 > Note: Since RZ/V2N is a brother chip of RZ/V2H, the same execution environment is used, which causes inconsistency in display contents,  
 i.e., RZ/V2N application log contains "RZ/V2H".  
 This will be solved in the future version.

## Application: Configuration 
### AI Model
- RZ/V2L
    - Tiny YOLOv3: [Darknet](https://pjreddie.com/darknet/yolo/)  
    Dataset: [COCO](https://cocodataset.org/#home)
    Input size: 1x3x416x416  
    Output1 size: 1x13x13x255 (COCO) / 1x13x13x54 (Animal) / 1x13x13x45 (Vehicle)   
    Output2 size: 1x26x26x255 (COCO) / 1x26x26x54 (Animal) / 1x26x26x45 (Vehicle)   
  
- RZ/V2H and RZ/V2N
    - YOLOv3: [Darknet](https://pjreddie.com/darknet/yolo/)  
    Dataset: [COCO](https://cocodataset.org/#home)  
    Input size: 1x3x416x416   
    Output1 size: 1x13x13x255 (COCO) / 1x13x13x54 (Animal) / 1x13x13x45 (Vehicle)    
    Output2 size: 1x26x26x255 (COCO) / 1x26x26x54 (Animal) / 1x26x26x45 (Vehicle)    
    Output2 size: 1x52x52x255 (COCO) / 1x52x52x54 (Animal) / 1x52x52x45 (Vehicle)    

### Dataset

| Model   | Dataset | Description |
|---|---|---| 
| coco    | [Dataset Link](https://cocodataset.org/#download) | Dataset used is the same as mentioned in the research paper |
| animal  | [Dataset Link](https://huggingface.co/datasets/myyyyw/NTLNP) | Dataset of wildlife in the mixed coniferous broad-leaved forest |
| vehicle | [Site](https://universe.roboflow.com/) | Combined multiple sources for different classes from the given site. Sources used are listed in below table |

| Class   | Dataset for RZ/V2L EVK | Dataset for RZ/V2H EVK and RZ/V2N EVK |
|---|---|---|
| motorcycle | [Dataset](https://universe.roboflow.com/vehicle-mscoco/vehicles-coco) | [Dataset](https://universe.roboflow.com/vehicle-mscoco/vehicles-coco) |
| bus | [Dataset 1](https://universe.roboflow.com/titu/bus-jm7t3), [Dataset 2](https://universe.roboflow.com/final-year-project-shhpl/bus-detection-2wlyo), [Dataset 3](https://universe.roboflow.com/fyp-object-detection-tc8af/sya-bus) |  [Dataset 1](https://universe.roboflow.com/titu/bus-jm7t3), [Dataset 2](https://universe.roboflow.com/final-year-project-shhpl/bus-detection-2wlyo), [Dataset 3](https://universe.roboflow.com/fyp-object-detection-tc8af/sya-bus)|
| car | [Dataset 1](https://universe.roboflow.com/hungdk-t8jb0/nhandienxeoto-udgcp), [Dataset 2](https://universe.roboflow.com/project-fjp7n/car-detection-vwdhg) |  [Dataset 1](https://universe.roboflow.com/hungdk-t8jb0/nhandienxeoto-udgcp), [Dataset 2](https://universe.roboflow.com/project-fjp7n/car-detection-vwdhg) |
| policecar | [Dataset 1](https://universe.roboflow.com/fyp-tc-idn2o/police-cars-sumfm), [Dataset 2](https://universe.roboflow.com/maryam-mahmood-6hoeq/pol-tslhg) |  [Dataset 1](https://universe.roboflow.com/fyp-tc-idn2o/police-cars-sumfm), [Dataset 2](https://universe.roboflow.com/maryam-mahmood-6hoeq/pol-tslhg)|
| ambulance | [Dataset 1](https://universe.roboflow.com/ambulance-k0z3x/ambulance-detection-azspv), [Dataset 2](https://universe.roboflow.com/school-87zwx/emegency-vehicle-detection) | [Dataset 1](https://universe.roboflow.com/ambulance-k0z3x/ambulance-detection-azspv), [Dataset 2](https://universe.roboflow.com/school-87zwx/emegency-vehicle-detection)|
| truck | [Dataset 1](https://universe.roboflow.com/project-school-ulsua/truck-detection-g88di), [Dataset 2](https://universe.roboflow.com/kmec/truck-detection-vka5s) |[Dataset 1](https://universe.roboflow.com/project-school-ulsua/truck-detection-g88di), [Dataset 2](https://universe.roboflow.com/kmec/truck-detection-vka5s) |
| bicycle | [Dataset 1](https://universe.roboflow.com/vtc-ywqwf/tt-aio6y), [Dataset 2](https://universe.roboflow.com/north-south-university-faox7/bicycle-bdti6) |[Dataset 1](https://universe.roboflow.com/vtc-ywqwf/tt-aio6y), [Dataset 2](https://universe.roboflow.com/north-south-university-faox7/bicycle-bdti6), [Dataset 3](https://cocodataset.org/#download) |
| bike | [Dataset 1](https://universe.roboflow.com/subham-bhansali-fedah/bike-detection-tzvlj), [Dataset 2](https://universe.roboflow.com/fyp-object-detection-tc8af/sya-bike) | [Dataset 1](https://universe.roboflow.com/subham-bhansali-fedah/bike-detection-tzvlj), [Dataset 2](https://universe.roboflow.com/fyp-object-detection-tc8af/sya-bike)|
| Auto |  [Dataset 1](https://universe.roboflow.com/rutviknirma/smart-traffic-management-system), [Dataset 2](https://universe.roboflow.com/graduation-project-rtgrc/tuk-tuk-labelling) | [Dataset 1](https://universe.roboflow.com/rutviknirma/smart-traffic-management-system), [Dataset 2](https://universe.roboflow.com/graduation-project-rtgrc/tuk-tuk-labelling) |
| LCV |  [Dataset 1](https://universe.roboflow.com/project-final-ltl6m/vehicle-detection-inlat), [Dataset 2](https://universe.roboflow.com/pooja-shri-v/lcvs-zqmsu) | [Dataset 1](https://universe.roboflow.com/project-final-ltl6m/vehicle-detection-inlat), [Dataset 2](https://universe.roboflow.com/pooja-shri-v/lcvs-zqmsu) |
| Fire engine |  [Dataset 1](https://universe.roboflow.com/grad-project-tjt2u/fire-truck-xumw3), [Dataset 2](https://universe.roboflow.com/pouria-maleki/firetruck) | [Dataset 1](https://universe.roboflow.com/grad-project-tjt2u/fire-truck-xumw3), [Dataset 2](https://universe.roboflow.com/pouria-maleki/firetruck)  |

>Note: Link for motorcycle dateset has additional classes bus, car and truck which is also used for training  


### AI inference time
|Board | AI model | AI inference time|
|:---|:---|:---|
|RZ/V2L EVK|Tiny YOLOv3| Approximately 57 ms  |
|RZ/V2H EVK |YOLOv3 | Approximately 26 ms  |
|RZ/V2N EVK |YOLOv3 | Approximately 82 ms  |

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
|RZ/V2H EVK and RZ/V2N EVK  | VGA (640x480) in YUYV format  | FHD (1920x1080) in BGRA format  |
  
### Explanation of the `app_conf.ini` file

- The section name can be of your choice. And it will be the mode name.

- The section should contains three variables - `model_path`, `label_path` & `config_path`.

  - The `model_path` value is the path to the folder containing compiled model. The folder should also contains also contain preprocess folder. 

  - The `label_path` value is the path to the label list the model supports.

  - The `config_path` value is the path to the model configuration ini file. Detailed explanation of the `config.ini` file is given at below section.

### Explanation of the `config.ini` file

- The [**detect**] section contains three variables - `conf`, `anchors` & `objects`.

  - The `conf` value is the confidence threshold used for object detection,
  - The `anchors` are the yolo anchors for the object detection. 
  - The `objects` represents class to be identified and it can be changed to other classes present on the class label list.

- To modify the configuration settings, edit the values in this file using VI Editor.

```sh
vi config.ini
```

## Reference
- For RZ/V2H EVK and RZ/V2N EVK, this application supports USB camera only with 640x480 resolution.  
FHD resolution is supported by e-CAM22_CURZH camera (MIPI).  
Please refer to following URL for how to change camera input to MIPI camera.  
[https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications](https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications#mipi).  

## License 
Apache License 2.0  
For third party OSS library, please see the source code file itself. 