# Face Authentication Application

## Application: Overview
The face authentication application is a cutting-edge software that can validate individuals sitting in front of a 
camera and the face given in the document ID (either office, passport, etc.) . Using advanced computer vision algorithms and faceNet model, 
the software can accurately detect and validate faces in real-time.

The application is designed to be user-friendly and can be used in a wide range of settings, including airports, public buildings, 
workplaces, law enforcement, and retail environments. With a simple and intuitive interface, users can easily validate new images with the document image IDs.

This kind of application makes it easier to automate the authentication process, thus minimizing the redundant human intervention. 


It has following camera input modes.

|Mode        |RZ/V2L    |RZ/V2H    |RZ/V2N    |
|:---        |:---      |:---      |:---      |
|USB Camera  |Supported |Supported |Supported |
|MIPI Camera |Supported | -        | -        |

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
       <td>RZ/V2N AI SDK v6.00</td>
     </tr>
 </table>  

### Demo

Following is the demo for RZ/V2L EVK.  
<img src="./images/Q02_face.gif" width="480">

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
    |RZ/V2H EVK|`rzv2h_ai_sdk_container`  |
    |RZ/V2N EVK|`rzv2n_ai_sdk_container`  |

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
3. Go to the application source code directory.  
    ```sh
    cd ${PROJECT_PATH}/Q02_face_authentication/src
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
5. The following application file would be generated in the `${PROJECT_PATH}/Q02_face_authentication/src/build` directory
    - face_recognition


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

Each folder contains following items.
|File | Details |
|:---|:---|
|facenet_model | Model object files for deployment. |
|face_rec_bg.jpg | Image for application background. |
|face_recognition | Application file. |

### Instruction  
1. Copy the following files to the `/home/root/tvm` directory of the rootfs (SD Card) for the board.
    |File | Details |
    |:---|:---|
    |All files in `EXE_DIR` directory | Including `deploy.so` file. |
    |`face_recognition ` application file | Generated the file according to [Application File Generation](#application-file-generation) |

4. Check if `libtvm_runtime.so` exists under `/usr/lib*` directory of the rootfs (SD card) on the board.

5. Folder structure in the rootfs (SD Card) would look like:

   For RZ/V2L and RZ/V2H
    ```
    |-- usr
    |   `-- lib64
    |       `-- libtvm_runtime.so
    `-- home
        `-- root
            `-- tvm
                |-- facenet_model
                |   |-- deploy.json
                |   |-- deploy.params
                |   `-- deploy.so
                |-- face_rec_bg.jpg
                `-- face_recognition
    ```
   For RZ/V2N
    ```
    |-- usr
    |   `-- lib
    |       `-- libtvm_runtime.so
    `-- home
        `-- weston
            `-- tvm
                |-- facenet_model
                |   |-- deploy.json
                |   |-- deploy.params
                |   `-- deploy.so
                |-- face_rec_bg.jpg
                `-- face_recognition
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

   For RZ/V2L and RZ/V2H
    - For USB Camera Mode
    ```sh
    ./face_recognition USB
    ```
    - For MIPI Camera Mode (RZ/V2L only)
    ```sh
    ./face_recognitionr MIPI
    ```
   For RZ/V2N
    - For USB Camera Mode
    ```sh
    su 
    ./face_recognition USB
    exit # After terminated the application.
    ```
    > Note: MIPI Camera Mode is only supported by RZ/V2L EVK.

3. Following window shows up on HDMI screen.  

    1) The application can be used to authenticate the real time image of the person with the face on the document ID.
    2) This application consists of three pages.

        1. The main page consists of Two buttons.
            - ***Add ID image:*** Button for taking pictures from the document IDs.
            - ***Validate:*** Button for validating the real face with document face ID.

            <img src=./images/face_authentication_front.png width="420" height="360">

        2. Then Click on the `Add ID image` button for recognizing the face from the document ID. We can see a new window. it contains two buttons.
            - ***Add Face:*** Button for taking pictures.
            - ***Back:*** It retrieves the previous page(Main page).

            <img src=./images/FaceAuthentication_Addface.png width="420" height="360">

            1. The user have to align the documented face to the bounding box provided to be captured.
            2. Click `Add Face` button to capture the photo.
            3. User can Click `Back` button to retrieves the previous page(Main page).
            4. User can `Mouse Double Click` to terminate the application.

        3. Then click on the `Validate` button to capture the real time image of the person that needs to be validated. We can see a new Window. It contains two buttons.
            - ***Validate:*** It is used to capture the real time image.
            - ***Back:*** It retrieves the previous page(Main page).

            <img src=./images/FaceAuthentication_validate.png width="420" height="360">

            1. User need to align their face on the box shown on the display.
            2. Click `Validate` button to capture the real time image.Only 3 attempts of validating is provided. After that the application exit to initial state.
            3. User can Click `Back` button to retrieves the previous page(Main page).
            4. User can `Mouse Double Click` to terminate the application.

    3) Sucessfull result will be shown as below. 

        <img src=./images/FaceAuthentication_result.png width="420" height="360">

        Please go through the demo video to get a better picture of the sample application.
        
4. Termination
    - Application can be terminated by clicking the left mouse double click.
    - Alternatively, to force close the application, switch from the application window to the terminal by pressing `Super(windows key)+Tab` and press `CTRL + C`.
   

## Application: Configuration
### AI Model  
[FaceNet model](https://arxiv.org/abs/1503.03832) is used which provide the embedding vectors of the images.   

The model used is the pre-trained model.   
We then apply cosine similarity to match the incoming images.   
The threshold kept for the match is `0.23`.   

### AI inference time
|Board | AI model | AI inference time|
|:---|:---|:---|
|RZ/V2L EVK |FaceNet | Approximately 465ms  |
|RZ/V2H EVK |FaceNet | Approximately 195ms  |
|RZ/V2N EVK |FaceNet | Approximately 192ms  |

### Processing

|Processing | RZ/V2L EVK | RZ/V2H EVK and RZ/V2N EVK |
|:---|:---|:---|
|Pre-processing | Processed by CPU. | Processed by CPU. |
|Inference | Processed by DRP-AI and CPU. | Processed by DRP-AI and CPU. |
|Post-processing | Processed by CPU. | Processed by CPU. |

### Image buffer size

|Board | Camera capture buffer size|HDMI output buffer size|
|:---|:---|:---|
|RZ/V2L EVK | VGA (640x480) in YUYV format  | HD (1280x720) in BGRA format  |
|RZ/V2H EVK and RZ/V2N EVK | VGA (640x480) in YUYV format  | FHD (1920x1080) in BGRA format  |
 
  
## Reference
- For RZ/V2H EVK and RZ/V2N EVK, this application supports USB camera only with 640x480 resolution.     
To use FHD, please use MIPI camera.   
Please refer to following URL for how to change camera input to MIPI camera.  
[https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications](https://renesas-rz.github.io/rzv_ai_sdk/latest/about-applications#mipi).  

## License
Apache License 2.0    
For third party OSS library, please see the source code file itself. 