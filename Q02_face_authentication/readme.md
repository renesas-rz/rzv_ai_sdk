# Face Authentication Application

## Application: Overview
The face authentication application is a cutting-edge software that can validate individuals sitting in front of a 
camera and the face given in the document ID (either office, passport, etc.) . Using advanced computer vision algorithms and faceNet model, 
the software can accurately detect and validate faces in real-time.

The application is designed to be user-friendly and can be used in a wide range of settings, including airports, public buildings, 
workplaces, law enforcement, and retail environments. With a simple and intuitive interface, users can easily validate new images with the document image IDs.

This kind of application makes it easier to automate the authentication process, thus minimizing the redundant human intervention. 

[Demo Video: TBD]()

## Application: Requirements

#### Hardware Requirements
- RZ/V2L Evaluation Board Kit
- USB Camera
- USB Mouse
- USB Keyboard
- USB Hub
- HDMI monitor & Cable

#### Software Requirements
- Ubuntu 20.04
- OpenCV 4.x
- C++11 or higher

## Application: Build Stage

>**Note:** User can skip to the [deploy stage](#application-deploy-stage) if they don't want to build the application. All pre-built binaries are provided.

**Note:** This project expects the user to have completed [Getting Startup Guide](../README.md#startup-guide) provided by Renesas. 

After completion of the guide, the user is expected of following things.
- The Board Set Up and booted. 
- SD Card Prepared 
- The docker image amd container for `rzv2l_ai_sdk_image` running on host machine.

>**Note:** Docker container is required for building the sample application. By default the Renesas will provide the container named as `rzv2l_ai_sdk_container`. Please use the docker container name as assigned by the user when building the container.

#### Application File Generation
1. Copy the repository from the GitHub to the desired location. 
    1. It is recommended to copy/clone the repository on the `data` folder which is mounted on the `rzv2l_ai_sdk_container` docker container. 
    ```sh
    cd <path_to_data_folder_on_host>
    git clone https://github.com/renesas-rz/rzv_ai_sdk.git
    ```
    >Note: Please verify the git repository url if error occurs.

2. Run the docker container and open the bash terminal on the container.

> Note: All the build steps/commands listed below are executed on the docker container terminal.

3. Assign path to the `data` directory mounted on the `rzv2l_ai_sdk_container` docker container

```sh
export PROJECT_PATH=/drp_ai_tvm/data/
```

4. Go to the `src` directory of the application

```sh
cd ${PROJECT_PATH}/rzv_ai_sdk/Q02_face_authentication/src/
```
>**Note:**`rzv_ai_sdk` is the repository name corresponding to the cloned repository. Please verify the repository name if error occurs.

5. Build the application on docker environment by following the steps below
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
- face_recognition

## Application: Deploy Stage

For the ease of deployment all the deployable files and folders for RZ/V2L are provided on the [exe](./exe) folder.

|File | Details |
|:---|:---|
|facenet_model | Model object files for deployment. |
|face_rec_bg | Image for application background. |
|face_recognition | Application file. |


Follow the steps mentioned below to deploy the project on RZ/V2L Board. 
* At the `/home/root/tvm` directory of the rootfs (SD Card) for RZ/V2L board. 
   * Copy the files present in [exe](./exe) directory, which are listed in the table above
   * Copy the generated `face_recognition` application file, if the application file is built at [build stage](#application-build-stage)

* Check if libtvm_runtime.so is there on `/usr/lib64` directory of the rootfs (SD card) RZ/V2L board.

#### Folder Structure in the board
----
```
├── usr/
│   └── lib64/
│       └── libtvm_runtime.so
└── home/
    └── root/
        └── tvm/
            ├── facenet_model/
            │   ├── deploy.json
            │   ├── deploy.params
            │   └── deploy.so
            |── face_recognition
            └── face_rec_bg.jpg
```

## Application: Runtime Stage

* For running the application, run the commands as shown below on the RZ/V2L Evaluation Board console.
    * Go to the `/home/root/tvm` directory of the rootfs
    ```sh
    cd /home/root/tvm
    ```
    * Run the application in the terminal of the RZ/V2L board using the command
	```sh
    ./face_recognition
    ```


#### GUI for running the application
--------------------------------
1. The application can be used to authenticate the real time image of the person with the face on the document ID.
2. The application consists of two buttons.
	- ***Add ID image:*** Button for taking pictures from the document IDs.
	- ***Validate:*** Button for validating the real face with document face ID.

	<img src=./images/face_authentication_front.JPG width="420" height="360">

3. Then Click on the `Add ID image` button for recognizing the face from the document ID. 
	1. The user have to align the documented face to the bounding box provided to be captured.
    2. Press `Enter` key on the keyboard to capture the photo.
    3. User can press `Esc` key to exit to initial stage.

4. Then click on the `Validate` button to capture the real time image of the person that needs to be validated
    1. User need to align their face on the box shown on the display.
    2. Press `Enter` key on the keyboard to capture the real time image.
    3. Only 3 attempts of validating is provided. After that the application exit to initial state.
    4. User can press `Esc` key to exit to initial stage.

6. Please go through the demo video to get a better picture of the sample application.

#### Application: Termination
- Application can be terminated by pressing `Esc` key on the keyboard connected to the board.
- Alternatively, User can force close the application using `CTRL+c` on the board console.

## Application: Specifications

#### Model Details
FaceNet model is used which provide the embedding vectors of the images.

FaceNet - https://arxiv.org/abs/1503.03832

The model used is the pre-trained model.

We then apply cosine similarity to match the incoming images.\
The threshold kept for the match is `0.23`.

The AI inference time for the model is `450` msec.






