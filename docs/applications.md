---
layout: default
---

<div class="container" style="max-width:100%;">
    <div class="row">
        <div id="page-top" class="top col-12">
            AI Applications<br>
            for RZ/V series
        </div>
    </div>
</div>
<br>
<h5 align="left">
    AI Applications are provided with pre-trained AI models. <br><br>
    Select each application to access the source code.<br><br><br>
    To run the AI Applications without constructing the AI SDK environment, refer to <a href="{{ site.url }}{{ site.baseurl }}{% link index.md %}#demo">Demo</a>.
</h5>

<br>

<!-- Copy applications.html start -->

<h3 id="agriculture" align="left"><i>Agriculture</i></h3>
<div class="container">
    <div class="row">
        <div id="agriculture1" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Agriculture1_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Defense wild animals for crop</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Detect the types of animals that enter your farm or barn for pest control.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 07_Animal_detection<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> Animals Detection Images Dataset+Images.cv+Coco Dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/07_Animal_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="agriculture2" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Agriculture2_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Fruit and Vegetable Plant Disease Check</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Supports farmer by classifying whether the plant has a disease or not.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q07_plant_disease_classification<br>
                    <b>Model:</b> Custom<br>
                    <b>Dataset:</b> New Plant Diseases Dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q07_plant_disease_classification" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">9fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="agriculture3" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Agriculture3_RanchLivestockManagement.jpg" alt="application">
                <dt style="color: #2a289d;">Ranch Livestock Management</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Counts the number of livestock to help monitor the number of animals bred in a ranch.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q08_object_counter (Animal Counting)<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">6fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="building" align="left"><i>Smart Building</i></h3>
<div class="container">
    <div class="row">
        <div id="building1" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartBuilding1_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Elevator passengers Counting</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Issues alerts if the elevator is overcrowded and exceeds its capacity.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 01_Head_count<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> HollywoodHeads<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/01_Head_count" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="building2" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartBuilding2_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Conference Room Usage Monitor</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Monitors if the meeting room is vacant by counting the number of people in the room.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 11_Head_count_topview<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> Various dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="building3" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartBuilding3_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Lighting Control</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Automatically controls the lighting according to the situation by counting the number of people in the room.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 11_Head_count_topview<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> Various dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="building4" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartBuilding4_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Security Area Intrusion Detection</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Detects illegal intrusions to security area in the office.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 02_Line_crossing_object_counting<br>
                    <b>Model:</b> TinyYOLOv2<br>
                    <b>Dataset:</b> COCO<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">13fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="building5" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartBuilding5_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Wear management at construction sites</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Analyzes the equipment of workers before entering the construction site by detecting the necessary equipment such as helmet or vest. It can be used to reduce the overload of monitoring person and ensure workers to wear appropriate equipment.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 04_Safety_helmet_vest_detection<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> Safety Helmet Detection on kaggle<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/04_Safety_helmet_vest_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="building6" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartBuilding6_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Touchless Controller for elevator</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    By using hand gestures, elevator operation can be done without touching the buttons.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 12_Hand_gesture_recognition_v2<br>
                    <b>Model:</b> TinyYOLOv2+ResNet18<br>
                    <b>Dataset:</b> YOLO-Hand-Detection for hand detection and HAgrid for classifier<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/12_Hand_gesture_recognition_v2" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">11~20fps for single hand</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="building7" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartBuilding7_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Employee ID check for Restricted Area</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Checks the employee ID and the person matches before entering to restricted area.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q02_face_authentication<br>
                    <b>Model:</b> FaceNet<br>
                    <b>Dataset:</b> FaceNet<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">2fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="city" align="left"><i>Smart City</i></h3>
<div class="container">
    <div class="row">
        <div id="city1" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity1_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Congestion Detection in Railway Station</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Monitors the congestion level on trains and buses by detecting the number of passengers.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 11_Head_count_topview<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> Various dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city2" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity2_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Prohibited Area Management</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Prevents accidents and detects illegal intrusions in construction site by detecting the entry to prohibited areas.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 02_Line_crossing_object_counting<br>
                    <b>Model:</b> TinyYOLOv2<br>
                    <b>Dataset:</b> COCO<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">13fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city3" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity3_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Distracted driving detection</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Issues an alert when the driver is distracted by detecting the line of sight.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 09_Human_gaze_detection<br>
                    <b>Model:</b> ResNet-18+Tiny YOLOv2<br>
                    <b>Dataset:</b> ETH-XGaze+WIDERFACE<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/09_Human_gaze_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city4" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity6_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Duration monitoring for surveillance camera</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Prevents the theft by monitoring whether there is a suspicious person wandering around the specified area.  Can be used in car dealer, housing, etc.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q01_footfall_counter<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> COCO<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">9fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city5" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity4_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Parking Spot Reservation</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Detects the occupancy of parking spot for reservation system.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q03_smart_parking<br>
                    <b>Model:</b> Custom<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q03_smart_parking" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">4-7 msec per slot</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city6" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity7_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Illegal Parking Check</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Detects the parking violation by monitoring the car presence in a restricted area.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q03_smart_parking<br>
                    <b>Model:</b> Custom<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q03_smart_parking" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">4-7 msec per slot</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city7" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity5_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Passport check support</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Supports passport check in airport immigration by checking the match of users face and their passport.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q02_face_authentication<br>
                    <b>Model:</b> FaceNet<br>
                    <b>Dataset:</b> FaceNet<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">2fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city8" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity8_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Bus passenger counting</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Counts the number of passengers on public transportation. It is also effective in preventing children from being left behind on school buses.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 11_Head_count_topview<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> Various dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city9" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCIty9_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Backtravel Detection</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Detects people going backwards on one-way stairs, aisles, or escalators. Helps preventing congestion and accidents.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 02_Line_crossing_object_counting<br>
                    <b>Model:</b> TinyYOLOv2<br>
                    <b>Dataset:</b> COCO<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">13fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city10" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity10_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Violence Activity Check in Surveillance Camera</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Supports the surveillance system by monitoring the suspicious/violent activity.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q05_suspicious_activity<br>
                    <b>Model:</b> EfficientNet+MLP<br>
                    <b>Dataset:</b> Real Life Violence Situations Dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q05_suspicious_activity" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">2fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city11" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity11_BirdDamagePrevention.jpg" alt="application">
                <dt style="color: #2a289d;">Bird Damage Prevention</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Counts birds captured by the camera and alerts the user. It can be used to prevent bird damage in parks, residential areas, or fields.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q08_object_counter (Animal Counting)<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">6fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city12" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity12_BlindSpotMonitor.jpg" alt="application">
                <dt style="color: #2a289d;">Blind Spot Monitor</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Detects vehicles that enter the driver's blind spot. It can detect motorcycles and bicycles to help prevent accidents when turning a corner.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q08_object_counter (Vehicle Counting)<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">6fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city13" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity13_PrecedingVehicleMovementAlert.jpg" alt="application">
                <dt style="color: #2a289d;">Preceding Vehicle Movement Alert</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Detects the departure of the preceding vehicle. It prevents the driver from a delayed start when waiting at a traffic light or in a traffic jam.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 13_Car_ahead_departure_detection (Vehicle Counting)<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/13_Car_ahead_departure_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">20fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city14" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity14_EmergencyVehiclesDetector.jpg" alt="application">
                <dt style="color: #2a289d;">Emergency Vehicles Detector</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Detects an emergency vehicle approaching from behind and alerts the driver. The driver can notice the emergency vehicle at an early stage.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q08_object_counter (Vehicle Counting)<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">6fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city15" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity15_IllegalBicycleApproachDetection.jpg" alt="application">
                <dt style="color: #2a289d;">Illegal Bicycle Approach Detection</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Detects whether motorcycles are in pedestrian-only areas. It can prevent illegal parking or accidents.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q08_object_counter (Vehicle Counting)<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">6fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city16" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity16_BicycleRentalStockManagement.jpg" alt="application">
                <dt style="color: #2a289d;">Bicycle Rental Stock Management</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Counts the number of bicycles that are not being used in bicycle rental shops to support bicycle inventory management.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q08_object_counter (Vehicle Counting)<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">6fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city17" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity17_IllegalBicycleParkingMonitorSupport.jpg" alt="application">
                <dt style="color: #2a289d;">Illegal Bicycle Parking Monitor Support</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Detects illegally abandoned bicycles in front of train stations or other locations to reduce burdens on patrols.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q08_object_counter (Vehicle Counting)<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">6fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city18" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity18_InfrastructureDefectPrevention.jpg" alt="application">
                <dt style="color: #2a289d;">Infrastructure Defect Prevention</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Detect cracks in tunnels or road surfaces. It helps to find deterioration and damage to infrastructure.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q09_crack_segmentation<br>
                    <b>Model:</b> Unet<br>
                    <b>Dataset:</b> Crack Segmentation Dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q09_crack_segmentation" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">8fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="city19" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCity19_CrimePreventionSupportforSchool.jpg" alt="application">
                <dt style="color: #2a289d;">Crime Prevention Support for School</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Detects suspiciously dressed persons at schools or cram schools to help prevent crimes in which dangerous individuals attempt to harm students.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q10_suspicious_person_detection<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q10_suspicious_person_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">6fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="healthcare" align="left"><i>Healthcare</i></h3>
<div class="container">
    <div class="row">
        <div id="healthcare1" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Healthcare1_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Physical Condition Monitor</dt>
                <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                <div class="griditem-add">
                    Support the early rescue by detecting any changes in the body condition of patients/users in the hospitals and care facility when they are alone.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 03_Elderly_fall_detection<br>
                    <b>Model:</b> TinyYOLOv2+HRNet<br>
                    <b>Dataset:</b> PASCAL VOC+COCO<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/03_Elderly_fall_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">5fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="home" align="left"><i>Smart Home</i></h3>
<div class="container">
    <div class="row">
        <div id="home1" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartHome1_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Air Conditioner Control</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Automatically controls the air conditioning according to the situation by counting the number of people in the room.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 11_Head_count_topview<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> Various dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="home2" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartHome4_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Smart TV</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Provides smart TV system, which switches to favorite TV channel by collecting the data of family members and TV contents that they watched.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 06_Face_recognition_spoof_detection<br>
                    <b>Model:</b> ResNet-50<br>
                    <b>Dataset:</b> VGGFace2<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/06_Face_recognition_spoof_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">11fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="home3" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartHome2_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Pet Detection in Kitchen and Child's Room</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Issues an alert when your pets have entered dangerous areas such as kitchen or children room.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 07_Animal_detection<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> Animals Detection Images Dataset+Images.cv+Coco Dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/07_Animal_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="home4" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartHome3_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Touchless Controller for Kitchen Appliance</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Allows you to control electrical appliances by the hand gestures without touching them.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 12_Hand_gesture_recognition_v2<br>
                    <b>Model:</b> TinyYOLOv2+ResNet18<br>
                    <b>Dataset:</b> YOLO-Hand-Detection for hand detection and HAgrid for classifier<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/12_Hand_gesture_recognition_v2" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">11~20fps for single hand</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="home5" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartHome5_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Food Package Expiry Date Check</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Monitors the expiry date of food placed in the refrigerator.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q06_expiry_date_detection<br>
                    <b>Model:</b> TinyYOLOv3+Tesseract<br>
                    <b>Dataset:</b> ExpDate<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q06_expiry_date_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">9fps for TinyYOLOv3</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="industrial" align="left"><i>Industrial</i></h3>
<div class="container">
    <div class="row">
        <div id="industrial1" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Industrial1_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Work Area Personnel Management</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Monitors attendance of workers by counting their number entered in the work area.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 01_Head_count<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> HollywoodHeads<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/01_Head_count" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="industrial2" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Industrial4_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Access Control</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Monitors the total number of visitors by counting the number of people who have passed through the entrance/exit.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 02_Line_crossing_object_counting<br>
                    <b>Model:</b> TinyYOLOv2<br>
                    <b>Dataset:</b> COCO<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">13fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="industrial3" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Industrial2_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Helmet and safety vest wearing monitor</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Increase the safety level in the factory by monitoring the helmet use.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 04_Safety_helmet_vest_detection<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> Safety Helmet Detection on kaggle<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/04_Safety_helmet_vest_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="industrial4" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Industrial3_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Touchless Controller for Industrial machine</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Machine button operation can be done without contact using gestures in factory.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 12_Hand_gesture_recognition_v2<br>
                    <b>Model:</b> TinyYOLOv2+ResNet18<br>
                    <b>Dataset:</b> YOLO-Hand-Detection for hand detection and HAgrid for classifier<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/12_Hand_gesture_recognition_v2" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">11~20fps for single hand</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="industrial5" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Industrial5_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Driver Monitoring System</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Detects whether the driver is looking aside, yawning or closing his eyes. Prevents car accidents by detecting when the driver is getting sleepy while driving.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 10_Driver_monitoring_system<br>
                    <b>Model:</b> TinyYOLOv2+DeepPose<br>
                    <b>Dataset:</b> WIDERFACE/WFLW<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/10_Driver_monitoring_system" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">6fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="industrial6" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Industrial6_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Species check support in Fish Factory</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Classifies the fish species shown in the camera to support the fish processing industry.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q04_fish_classification<br>
                    <b>Model:</b> EfficientNet based<br>
                    <b>Dataset:</b> Fish Dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q04_fish_classification" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">15fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="industrial7" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Industrial7_DefectInspectionSupport.jpg" alt="application">
                <dt style="color: #2a289d;">Defect Inspection Support</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Monitors the factory production line to detect cracks in the manufactured products. It supports the product inspection process.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q09_crack_segmentation<br>
                    <b>Model:</b> Unet<br>
                    <b>Dataset:</b> Crack Segmentation Dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q09_crack_segmentation" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">8fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="industrial8" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Industrial8_Aquaculture_Industrial_Support.jpg" alt="application">
                <dt style="color: #2a289d;">Aquaculture Industrial Support</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Monitors fish to help aquaculture operators to manage their resources.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q11_fish_detection<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q11_fish_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">7fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="retail" align="left"><i>Retail</i></h3>
<div class="container">
    <div class="row">
        <div id="retail1" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Retail1_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Congestion Detection</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Issues an alert when the store is overcrowded with more customers.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 11_Head_count_topview<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> Various dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="retail2" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Retail3_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Smart POS</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Supports checking ages of customers by checking their age in front of the casher and linking the information with their purchase.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 05_Age_gender_detection<br>
                    <b>Model:</b> ResNet-18/ResNet-50<br>
                    <b>Dataset:</b> Unknown<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/05_Age_gender_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">27fps/11fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="retail3" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Retail4_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Marketing Interest Analysis</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    "Monitors the gaze direction of customer in the retail store,  which can be used to collect marketing information."<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 09_Human_gaze_detection<br>
                    <b>Model:</b> ResNet-18+Tiny YOLOv2<br>
                    <b>Dataset:</b> ETH-XGaze+WIDERFACE<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/09_Human_gaze_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="retail4" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Retail2_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Staying and flow line monitoring</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Collects marketing data by monitoring the number of people and duration of their stay in a certain place.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q01_footfall_counter<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> COCO<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">9fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="retail5" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Retail5_960x540.jpg" alt="application">
                <dt style="color: #2a289d;">Exhibition Participants Monitoring</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Monitor the number of visitors to an exhibition or other open space. Changes in the number of participants can also be detected since it counts the number of participants in real time.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> 11_Head_count_topview<br>
                    <b>Model:</b> YOLOv3<br>
                    <b>Dataset:</b> Various dataset<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">3fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="retail6" class="col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/Retail6_Store_Crime_Prevention.jpg" alt="application">
                <dt style="color: #2a289d;">Store Crime Prevention</dt>
                <h6 class="appstatus" align="right"><b>New!</b></h6>
                <div class="griditem-add">
                    Detects suspiciously dressed persons in convenience stores or unmanned stores to prevent theft.<br><br>
                </div>
                <div class="appspec">
                    <b>Supported AI SDK:</b> v2.10<br>
                    <b>Function:</b> Q10_suspicious_person_detection<br>
                    <b>Model:</b> TinyYOLOv3<br>
                    <b>Dataset:</b> Custom<br>
                    <br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="devicelinkbutton_parent">
                            <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q10_suspicious_person_detection" style="color:white">RZ/V2L ></a>
                            <!-- <p class="Perf-Framerate">6fps</p>-->
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
    </div>
</div>
<br>
<br>
<div class="container">
    <div class="row">
        <div class="col-12" align="right">
            <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#page-top" role="button">
Back to Top >
            </a>
        </div>
    </div>
</div>
<br>
<br>
    