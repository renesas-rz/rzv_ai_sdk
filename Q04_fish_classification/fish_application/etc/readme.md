# Web Application: Fish Classification

In web application mode, User can use any host machine (Windows/Linux) which is connected to the board, and can run the application through web browser. Detect images through the local host itself.

- [Web App Mode](https://renesasgroup.sharepoint.com/:v:/r/sites/QuestGlobalxRenesasRZAIAppDev/Shared%20Documents/General/Delivarables_Storage/fish_classification/fish_classification_ws_demo.mp4?csf=1&web=1&e=mvRVCu)

## Application: Requirements

#### Hardware Requirements
- RZ/V2L Evaluation Board Kit
    - Coral Camera
- USB Mouse
- USB Keyboard
- USB Hub
- HDMI monitor & Micro HDMI Cable
- Ethernet Cable [Required to connect to the board network]

#### Software Requirements for building the application
- Ubuntu 20.04
- OpenCV 4.x
- C++11 or higher



#### Python Package Installation (for running webapp:optional) 
> Note: Required only for Host Machine for running the application through Websocket
- Flask
- Flask-SocketIO
- numpy
- opencv-python
- python-socketio
- Werkzeug

## Application: Build Stage (Optional)
Follow the procedures given on the [`readme.md`](../../readme.md/#application-build-stage)

The following application file would be generated after this procedure.
- fish_classification

## Application: Deploy Stage (on Host PC) 

> Note: Below command are for linux host machine, User can also translate them to Windows PC commands
1. Copy the fish web application [folder (`fish_web_app_exe`)](./fish_application/etc/fish_web_app_exe/) to the host machine(any host machine which is connected to the same network as the V2L board).
```sh
export WORK=<path/to/fish_web_app_exe>
cd $WORK
```

2.  If fish_classification application is generated, copy it to the `fish_web_app_exe` folder.

3. Make sure python3 (>=3.8) and python3-pip is installed on the machine

```sh
sudo apt update
sudo apt -y upgrade 
sudo apt install software-properties-common
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt install python3.8
```

```sh
sudo apt-get install -y python3-pip
```
4. Install application requirements

```python
pip3 install -r requirements.txt
```

## Application: Runtime Stage

* Get IP config of the RZ/V2L Board, Run the command on the RZ/V2L board terminal.

```sh
ifconfig
```
* cd to the folder containing the fish_web_app_exe in the host machine.

```sh
cd $WORK
```

* On Host machine folder `fish_web_app_exe`
```sh
python3 app.py
```

1. Local server will start running, visit the IP address in any of the browser. 

2. Enter the IP address of the board. eg:- 192.168.197.202

    <img src=./images/fish_web_app_step1.JPG width="480">

3. If it is successfully connected to board, it will redirect to prediction page.
    
    <img src=./images/fish_web_app_step2.JPG width="480">

4. Select fish image press Send Photo. 

    <img src=./images/fish_web_app_step3.JPG width="480">

    <img src=./images/fish_web_app_step4.JPG width="480">


## Application: Specifications

This section is same as mentioned in the [`readme.md`](../../readme.md#application-specifications)