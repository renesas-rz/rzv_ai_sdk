# Face Recognition Application

## Application: Overview
The face recognition application is a cutting-edge software that can identify individuals sitting in front of a 
camera by comparing their faces to a database of pre-existing images. Using advanced computer vision algorithms and facenet model, 
the software can accurately detect and recognize faces in real-time.

The application is designed to be user-friendly and can be used in a wide range of settings, including airports, public buildings, 
workplaces, law enforcement, and retail environments. With a simple and intuitive interface, users can easily add new images to the 
database and configure the software to recognize specific individuals.


## Application: Requirements

#### Hardware Requirements
- RZ/V2L board
- USB camera
- USB mouse
- USB Keyboard
- USB Hub
- HDMI monitor

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
|preprocess_tvm_v2l/ | Pre-processing Runtime Object files. |
|tinyyolov3_onnx | Model object files for deployment. |
|coco-lables-2014_2017.txt | Label list for Object Detection. |
|config.ini | user input config for line, region and object. |
|object_tracker | application file. |


Follow the steps mentioned below to deploy the project on RZV2L Board. 
* At the `home/root/tvm` directory of the rootfs (SD Card/NFS) for RZV2L board.
   * Create a directory named `dataset`, for storing the images to be detected. 
   * Copy the genarted `face_recoginition` application file 
   * Copy the `face_rec_bg.jpg` image
   * Copy the `facenetmodel_onnx` folder

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
            ├── facenetmodel_onnx/
            │   ├── deploy.json
            │   ├── deploy.params
            │   └── deploy.so
            ├── dataset
            |── face_recoginition
            └── face_rec_bg.jpg
```

## Application: Runtime Stage


* Store the images of the faces to be detected in the `dataset` directory created in RZ/V2L board.
* Run the application in the terminal of the RZV2L board using the command
	./face_recoginition


#### GUI for running the application
--------------------------------

- The application consists of three buttons when the application is run.
	- Add faces from directory: Button for converting images in the dataset directory for comprison purposes
	- Add faces: Button for taking pictures from the camera.
	- Recoginze: Button for running the face recognization

	<img src=./images/face_authentication_front.JPG width="420" height="360">

- First click on the `Add faces from directory` button, which converts all the images in the dataset directory for comparison purpose.
* Then Click on the `Recoginze` button for recognizing the face sitting in front of the camera. 
	- The user have to allign to the bounding box provided to be captured.
* If a new face needs to be added through the connected camera, click on the `Add faces` button

* Press the `Esc` button to stop the recognize and come back to Start page of the GUI.

## Application: Specifications

#### Model Details
FaceNet model is used which provide the embedding vectors of the images.
FaceNet - https://arxiv.org/abs/1503.03832

We then apply cosine similarity to match the incoming images.
The threshold kept for the match is `0.23`.

The AI inference time for the model is `450` msec.






