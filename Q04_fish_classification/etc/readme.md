# Web Application: Fish Classification

In web application mode, User can use any host machine (Windows/Linux) which is connected to the board, and can run the application through web browser. Classify images through the local host itself.

#### Web App Mode Demo
<img src = "./images/FishClassification_Websocket.gif" width="480" height="320">


## Application: Requirements

#### Hardware Requirements
- RZ/V2L Evaluation Board Kit
    - USB Serial Cable [Required to connect to board]
- Ethernet Cable [Required to connect to the board network]

[Details](https://github.com/renesas-rz/rzv_ai_sdk/blob/main/README.md)

#### Software Requirements for building the Webapp
- Ubuntu 20.04 
- OpenCV 4.x
- C++11 or higher

#### Software Requirements for running the Webapp 
- Python 3.8
- pip3
- virtualenv

>Note: To install the requirements follow [step3](#application-deploy-stage-on-host-pc#L53)

#### Python3 Package Requirements for Host PC
> Note: Required only for Host Machine for running the application through Websocket. These package installation procedure is mentioned [here](#application-deploy-stage-on-host-pc#L88)
- Flask
- Flask-SocketIO
- numpy
- opencv-python
- python-socketio
- Werkzeug

## Application: Build Stage
Follow the procedures given on the [`readme.md`](../readme.md/#application-build-stage)

The following application file would be generated after this procedure.
- fish_classification

## Application: Deploy Stage (on Host PC) 

> Note: Below command are for linux host machine, User can also translate them to Windows PC commands
1. Copy the fish web application [`fish_web_app_exe`](./fish_web_app_exe/) to the host machine (any host machine which is connected to the same network as the V2L board).
>Note: Within the same network means, the host and board should be able to communicate with each other through LAN. E.g. Host IP: 192.168.197.200 and Board IP: 192.168.197.161


```sh
export WORK=<path/to/fish_web_app_exe>
cd $WORK
```

2.  If fish_classification application is generated, copy it to the `fish_web_app_exe` folder.

3. Make sure python3 (>=3.8) and python3-pip is installed on the machine. 

```sh
python3 --version
```
```sh
pip3 --version
```
If any of the command shows `unknown command` error. Please follow below steps to install.

For installing Python 3.8

```sh
sudo apt update
sudo apt -y upgrade 
sudo apt install software-properties-common
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt install python3.8
```

For installing pip3

```sh
sudo apt-get install -y python3-pip
```

4. For installing python virtualenv
```sh
sudo apt install virtualenv
```

5. Install application python requirements

```sh
cd $WORK
./init_app.sh
```

>Note: If permission error occurs, Use
```sh
chmod a+x init_app.sh
```

## Application: Runtime Stage

* Please note that the Host PC require internet connection to run the web application. 

* Get IP config of the RZ/V2L Board, Run the command on the RZ/V2L board terminal.

```sh
ifconfig
```

* On Host machine folder `fish_web_app_exe`

```sh
cd $WORK
./start_app.sh 
```

>Note: If permission error occurs, Use
```sh
chmod a+x start_app.sh
```

1. Local server will start running `http://127.0.0.1:5000/`, visit the IP address in any of the browser. 

    <img src=./images/fish_web_app_step0.JPG width="480">


2. Enter the IP address of the board. eg:- 192.168.197.161

    <img src=./images/fish_web_app_step1.JPG width="480">

3. If it is successfully connected to board, it will redirect to prediction page.
    
    <img src=./images/fish_web_app_step2.JPG width="480">

4. Select fish image press Send Photo. 

    <img src=./images/fish_web_app_step3.JPG width="480">

    <img src=./images/fish_web_app_step4.JPG width="480">


## Application: Specifications

This section is same as mentioned in the [`readme.md`](../readme.md#application-specifications)
