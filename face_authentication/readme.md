# Face Recognition Application

## Application: Overview
The face authentication application is a cutting-edge software that can validate individuals sitting in front of a 
camera and the face given in the doucumnet ID (either office, passport, etc.) . Using advanced computer vision algorithms and facenet model, 
the software can accurately detect and validate faces in real-time.

The application is designed to be user-friendly and can be used in a wide range of settings, including airports, public buildings, 
workplaces, law enforcement, and retail environments. With a simple and intuitive interface, users can easily validate new images with the document image IDs.

This kind of application makes it easier to automate the authentication process, thus minimizing the redundant human intervention. 

[Demo Video](https://renesasgroup.sharepoint.com/:v:/r/sites/QuestGlobalxRenesasRZAIAppDev/Shared%20Documents/General/Delivarables_Storage/face_recognition/face_recognition.mp4?csf=1&web=1&e=lE2urj)

## Application: Requirements

#### Hardware Requirements
- RZ/V2L board
- USB camera
- USB mouse
- USB Keyboard
- USB Hub
- HDMI monitor & Cable

#### Software Requirements
- Ubuntu 20.04
- OpenCV 4.x
- C++11 or higher

## Application : Build Stage

>**Note:** User can skip to the next stage (deploy) if they don't want to build the application. All pre-built binaries are provided.

**Note:** This project expects the user to have completed [Getting Startup Guide]() provided by Renesas. 

After completion of the guide, the user is expected of following things.
- the Board Set Up and booted. 
- SD Card (or NFS) Prepared 
- The docker image amd container for drp_ai_tvm running on host machine.
- libtvm_runtime.so file 

>**Note:** Docker environment is required for building the sample application. 


### Application: File Generation

- Copy the repository from the GitHub to the desired location.
```sh
export PROJECT_PATH=<path_to_the_cloned_directory>
```
```sh
cd $PROJECT_PATH/face_authentication/
```

- Now copy this src folder to the data directory (mounted directory for the created `drp_ai_tvm` docker container)

- Run the bash terminal of the docker container 
- Go to the `src` directory which was copied earlier.
- Now build the application on docker environment by following the steps below
```sh
cd src
```
```sh
mkdir -p build && cd build
```
```sh
cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
```
```sh
make -j$(nproc)
```
The following application file would be genarated in the `src/build` directory
- face_recoginition

## Application: Deploy Stage

For the ease of deployment all the deployables file and folders for RZV2L are provided on the [exe](./exe) folder.

|File | Details |
|:---|:---|
|facenet_model | Model object files for deployment. |
|face_rec_bg | image for application background. |
|face_recoginition | application file. |


Follow the steps mentioned below to deploy the project on RZV2L Board. 
* At the `home/root/tvm` directory of the rootfs (SD Card/NFS) for RZV2L board.
   * Copy the genarted `face_recoginition` application file 
   * Copy the `face_rec_bg.jpg` image
   * Copy the `facenet_model` folder

* Copy the libtvm_runtime.so to usr/lib64 directory of the rootfs (SD card/NFS) RZV2L board.

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
            |── face_recoginition
            └── face_rec_bg.jpg
```

## Application: Runtime Stage


* Go to the `tvm` directory of the rootfs
   ```sh
   cd <path_to_deployables>/
   ```
* Run the application in the terminal of the RZV2L board using the command
	```sh
    ./face_recoginition
    ```


#### GUI for running the application
--------------------------------
- The application can be used to authenticate the real time image of the person with the face on the document ID.
- The application consists of two buttons.
	- ***Add ID image:*** Button for taking pictures from the document IDs.
	- ***Validate:*** Button for validating the real face with document face ID.

	<img src=./images/face_authentication_front.JPG width="420" height="360">

* Then Click on the `Add ID image` button for recognizing the face from the document ID. 
	- The user have to allign the doumented face to the bounding box provided to be captured.
* Then click on the `Validate` button to capture the real time image of the person that needs to be validated
    - Only 3 attempts of validating is provided. After that the application exit to initial state.
* Press the `Esc` button to stop the validate and come back to Start page of the GUI.
* Please go through the demo video to get a better picture of the sample application.
## Application: Specifications

#### Model Details
FaceNet model is used which provide the embedding vectors of the images.

FaceNet - https://arxiv.org/abs/1503.03832

We then apply cosine similarity to match the incoming images.\
The threshold kept for the match is `0.23`.

The AI inference time for the model is `450` msec.






