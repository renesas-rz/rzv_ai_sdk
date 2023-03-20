FACE RECOGNITION APPLICATION USING FACENET MODEL
----------------------------------------
The face recognition application is a cutting-edge software that can identify individuals sitting in front of a 
camera by comparing their faces to a database of pre-existing images. Using advanced computer vision algorithms and facenet model, 
the software can accurately detect and recognize faces in real-time.

The application is designed to be user-friendly and can be used in a wide range of settings, including airports, public buildings, 
workplaces, law enforcement, and retail environments. With a simple and intuitive interface, users can easily add new images to the 
database and configure the software to recognize specific individuals.


REQUIREMENTS
------------
* Hardware Requirements
	RZ/V2L board
	USB camera
	USB mouse
	USB Keyboard
	USB Hub
	HDMI monitor

* Software Requirements
	Ubuntu 20.04
	OpenCV 4.x
	C++11 or higher

APPLICATION : Build Stage
-----

NOTE: This project expects the user to have completed

	* the Board Set Up,
	* SD Card Preparation steps
	* AI SDK Set Up steps mentioned in the RZV2L_AI_SDK_Instruction_guide. After this step docker image amd container will be created.
	* Docker environment is required for building the sample application.
	* Copy the src directory from this GitHub to the data directory (mounted directory for created docker container)
	  created at the 3rd Step of AI SDK Set Up.

Application: File Generation

* Copy the repository from the GitHub to the desired location.

	export PROJECT_PATH=<path_to_the_cloned_directory>
	cd $PROJECT_PATH/face_recoginition/

* Now copy this src folder to the data directory (mounted directory for the created drp_ai_tvm docker container)

	Run the bash terminal of the docker container
	Go to the src directory which was copied earlier.
	Now build the application on docker environment by following the steps below
		cd src
		mkdir -p build && cd build
		cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain/runtime.cmake ..
		make -j$(nproc)
	

* The following application file would be genarated in the src/build directory
	face_recoginition

* Follow the steps mentioned below to deploy the project on RZ/V2L evaluation Board.

	At the home/root/tvm directory of the rootfs (SD Card/NFS) for RZ/V2L evaluation board.

		Create a directory named dataset, for storing the images to be detected.
		Copy the genarted face_recoginition application file
		Copy the face_rec_bg.jpg image
		Copy the facenetmodel_onnx folder
		Copy the libtvm_runtime.so to usr/lib64 directory of the rootfs (SD card/NFS) RZV2L board.

	Copy the libtvm_runtime.so to usr/lib64 directory of the rootfs (SD card/NFS) RZV2L board.

Folder Structure in the board
-----------------------------
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

Application: Runtime Stage
---------------------------

* Store the images of the faces to be detected in the dataset directory created in RZ/V2L board.
* Run the application in the terminal of the RZV2L board using the command
	./face_recoginition


GUI for running the application
--------------------------------

* The application consists of three buttons when the application is run.
	> Add faces from directory - Button for converting images in the dataset directory for comprison purposes
	> Add faces - Button for taking pictures from the camera.
	> Recoginze - Button for Face face_recoginition

* First click on the "Add faces from directory" button, which converts all the images in the dataset directory for comparison purpose.
* Then Click on the "Recoginze" button for recognizing the face sitting in front of the camera.
* If a new face needs to be added through the connected camera, click on the "Add faces button"

* Press the "Esc" button to stop the recognize and come back to Start page of the GUI.


Model Used
----------

Facenet - https://arxiv.org/abs/1503.03832





