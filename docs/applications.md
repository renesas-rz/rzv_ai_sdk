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
    <br>
    <br>
    To see the overview about AI Applications, please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link about-applications.md %}">About AI Applications</a> page.<br>
</h5>
<a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link about-applications.md %}" role="button">
    <span class="banner-title">About AI Applications</span><br>
    <span class="banner-line">
    What is AI Applications?<br>
    How is directory/file structured?<br>
    How can I download the previous version?<br></span>
</a>
<br>

<div id="agriculture" class="category_section container pb-4" data-category="Agriculture">
<h3 align="left"><i>Agriculture</i></h3>
<div class="container">
    <div class="row">
            <div id="agriculture1" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Animal"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Agriculture1_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Defense wild animals for crop</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detect the types of animals that enter your farm or barn for pest control.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 07_Animal_detection<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> Animals Detection Images Dataset+Images.cv+Coco Dataset<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/07_Animal_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/07_Animal_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="agriculture2" class="application_card col-lg-6 col-xl-4"
                data-model="Custom"
                data-targetobj="Other"
                data-label="Updated!"
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Agriculture2_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Fruit and Vegetable Plant Disease Check</dt>
                    <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                    <div class="griditem-add">
                        Supports farmer by classifying whether the plant has a disease or not.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q07_plant_disease_classification<br>
                        <b>Model:</b> Custom<br>
                        <b>Dataset:</b> New Plant Diseases Dataset<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q07_plant_disease_classification" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">14fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q07_plant_disease_classification" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">500fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="agriculture3" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Animal"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Agriculture3_RanchLivestockManagement.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Ranch Livestock Management</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Counts the number of livestock to help monitor the number of animals bred in a ranch.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q08_object_counter (Animal Counting)<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">18fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
        </div>
        <br>
        <br>
    </div>
</div>
<div id="building" class="category_section container pb-4" data-category="Smart Building">
<h3 align="left"><i>Smart Building</i></h3>
<div class="container">
    <div class="row">
            <div id="building1" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Head"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartBuilding1_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Elevator passengers Counting</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Issues alerts if the elevator is overcrowded and exceeds its capacity.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 01_Head_count<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> HollywoodHeads<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/01_Head_count" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/01_Head_count" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="building2" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Head"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartBuilding2_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Conference Room Usage Monitor</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Monitors if the meeting room is vacant by counting the number of people in the room.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 11_Head_count_topview<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="building3" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Head"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartBuilding3_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Lighting Control</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Automatically controls the lighting according to the situation by counting the number of people in the room.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 11_Head_count_topview<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="building4" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Person"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartBuilding4_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Security Area Intrusion Detection</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detects illegal intrusions to security area in the office.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 02_Line_crossing_object_counting<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> HollywoodHeads<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">20fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="building5" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Other"
                data-label="Updated!"
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartBuilding5_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Wear management at construction sites</dt>
                    <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                    <div class="griditem-add">
                        Analyzes the equipment of workers before entering the construction site by detecting the necessary equipment such as helmet or vest. It can be used to reduce the overload of monitoring person and ensure workers to wear appropriate equipment.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 04_Safety_helmet_vest_detection<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> helmet-safety-vest-detection+Kaggle dataset<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/04_Safety_helmet_vest_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/04_Safety_helmet_vest_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="building6" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv2+ResNet-18/YOLOv3"
                data-targetobj="Hand"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartBuilding6_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Touchless Controller for elevator</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        By using hand gestures, elevator operation can be done without touching the buttons.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 12_Hand_gesture_recognition_v2<br>
                        <b>Model:</b> Tiny YOLOv2+ResNet-18 | YOLOv3<br>
                        <b>Dataset:</b> YOLO-Hand-Detection/HaGRID | HaGRID<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/12_Hand_gesture_recognition_v2" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">13fps<br>for single hand</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/12_Hand_gesture_recognition_v2" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="building7" class="application_card col-lg-6 col-xl-4"
                data-model="FaceNet"
                data-targetobj="Face"
                data-label="Updated!"
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartBuilding7_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Employee ID check for Restricted Area</dt>
                    <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                    <div class="griditem-add">
                        Checks the employee ID and the person matches before entering to restricted area.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q02_face_authentication<br>
                        <b>Model:</b> FaceNet<br>
                        <b>Dataset:</b> FaceNet<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">2fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">5fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="building8" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3"
                data-targetobj="Vehicle"
                data-label="New!"
                data-device="RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/no_image.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Multi-Camera Parking Lot Management</dt>
                    <h6 class="appstatus" align="right"><b>New!</b></h6>
                    <div class="griditem-add">
                        Monitors cars or other vehicles going in and out of a parking lot.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> -<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 14_Multi_camera_vehicle_detection<br>
                        <b>Model:</b> Tiny YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/14_Multi_camera_vehicle_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">200fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
        </div>
        <br>
        <br>
    </div>
</div>
<div id="city" class="category_section container pb-4" data-category="Smart City">
<h3 align="left"><i>Smart City</i></h3>
<div class="container">
    <div class="row">
            <div id="city1" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Head"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity1_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Congestion Detection in Railway Station</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Monitors the congestion level on trains and buses by detecting the number of passengers.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 11_Head_count_topview<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city2" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Person"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity2_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Prohibited Area Management</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Prevents accidents and detects illegal intrusions in construction site by detecting the entry to prohibited areas.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 02_Line_crossing_object_counting<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> HollywoodHeads<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">20fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city3" class="application_card col-lg-6 col-xl-4"
                data-model="ResNet-18+Tiny YOLOv2"
                data-targetobj="Face"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity3_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Distracted driving detection</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Issues an alert when the driver is distracted by detecting the line of sight.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 09_Human_gaze_detection<br>
                        <b>Model:</b> ResNet-18+Tiny YOLOv2<br>
                        <b>Dataset:</b> ETH-XGaze/WIDERFACE<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/09_Human_gaze_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">8fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/09_Human_gaze_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">182fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city4" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Person"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity6_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Duration monitoring for surveillance camera</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Prevents the theft by monitoring whether there is a suspicious person wandering around the specified area.  Can be used in car dealer, housing, etc.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q01_footfall_counter<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> COCO<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">15fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">33fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city5" class="application_card col-lg-6 col-xl-4"
                data-model="Custom"
                data-targetobj="Vehicle"
                data-label=""
                data-device="RZ/V2L,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity4_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Parking Spot Reservation</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detects the occupancy of parking spot for reservation system.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> -<br>
                        <b>Function:</b> Q03_smart_parking<br>
                        <b>Model:</b> Custom<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q03_smart_parking" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">4-7 msec<br>per slot</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city6" class="application_card col-lg-6 col-xl-4"
                data-model="Custom"
                data-targetobj="Vehicle"
                data-label=""
                data-device="RZ/V2L,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity7_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Illegal Parking Check</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detects the parking violation by monitoring the car presence in a restricted area.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> -<br>
                        <b>Function:</b> Q03_smart_parking<br>
                        <b>Model:</b> Custom<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q03_smart_parking" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">4-7 msec<br>per slot</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city7" class="application_card col-lg-6 col-xl-4"
                data-model="FaceNet"
                data-targetobj="Face"
                data-label="Updated!"
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity5_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Passport check support</dt>
                    <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                    <div class="griditem-add">
                        Supports passport check in airport immigration by checking the match of users face and their passport.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q02_face_authentication<br>
                        <b>Model:</b> FaceNet<br>
                        <b>Dataset:</b> FaceNet<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">2fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">5fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city8" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Head"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity8_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Bus passenger counting</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Counts the number of passengers on public transportation. It is also effective in preventing children from being left behind on school buses.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 11_Head_count_topview<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city9" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Person"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCIty9_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Backtravel Detection</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detects people going backwards on one-way stairs, aisles, or escalators. Helps preventing congestion and accidents.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 02_Line_crossing_object_counting<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> HollywoodHeads<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">20fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city10" class="application_card col-lg-6 col-xl-4"
                data-model="CNN+MLP"
                data-targetobj="Other"
                data-label=""
                data-device="RZ/V2L,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity10_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Violence Activity Check in Surveillance Camera</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Supports the surveillance system by monitoring the suspicious/violent activity.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> -<br>
                        <b>Function:</b> Q05_suspicious_activity<br>
                        <b>Model:</b> CNN+MLP<br>
                        <b>Dataset:</b> Real Life Violence Situations Dataset<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q05_suspicious_activity" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city11" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Animal"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity11_BirdDamagePrevention.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Bird Damage Prevention</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Counts birds captured by the camera and alerts the user. It can be used to prevent bird damage in parks, residential areas, or fields.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q08_object_counter (Animal Counting)<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">18fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city12" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Vehicle"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity12_BlindSpotMonitor.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Blind Spot Monitor</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detects vehicles that enter the driver's blind spot. It can detect motorcycles and bicycles to help prevent accidents when turning a corner.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q08_object_counter (Vehicle Counting)<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">18fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city13" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3"
                data-targetobj="Vehicle"
                data-label="Updated!"
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity13_PrecedingVehicleMovementAlert.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Preceding Vehicle Movement Alert</dt>
                    <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                    <div class="griditem-add">
                        Detects the departure of the preceding vehicle. It prevents the driver from a delayed start when waiting at a traffic light or in a traffic jam.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 13_Car_ahead_departure_detection<br>
                        <b>Model:</b> Tiny YOLOv3<br>
                        <b>Dataset:</b> COCO<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/13_Car_ahead_departure_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">20fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/13_Car_ahead_departure_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">167fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city14" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Vehicle"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity14_EmergencyVehiclesDetector.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Emergency Vehicles Detector</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detects an emergency vehicle approaching from behind and alerts the driver. The driver can notice the emergency vehicle at an early stage.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q08_object_counter (Vehicle Counting)<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">18fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city15" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Vehicle"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity15_IllegalBicycleApproachDetection.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Illegal Bicycle Approach Detection</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detects whether motorcycles are in pedestrian-only areas. It can prevent illegal parking or accidents.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q08_object_counter (Vehicle Counting)<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">18fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city16" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Vehicle"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity16_BicycleRentalStockManagement.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Bicycle Rental Stock Management</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Counts the number of bicycles that are not being used in bicycle rental shops to support bicycle inventory management.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q08_object_counter (Vehicle Counting)<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">18fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city17" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Vehicle"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity17_IllegalBicycleParkingMonitorSupport.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Illegal Bicycle Parking Monitor Support</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detects illegally abandoned bicycles in front of train stations or other locations to reduce burdens on patrols.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q08_object_counter (Vehicle Counting)<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">18fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city18" class="application_card col-lg-6 col-xl-4"
                data-model="Unet"
                data-targetobj="Crack"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity18_InfrastructureDefectPrevention.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Infrastructure Defect Prevention</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detect cracks in tunnels or road surfaces. It helps to find deterioration and damage to infrastructure.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q09_crack_segmentation<br>
                        <b>Model:</b> Unet<br>
                        <b>Dataset:</b> Crack Segmentation Dataset<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q09_crack_segmentation" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">11fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q09_crack_segmentation" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">100fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city19" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Person"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartCity19_CrimePreventionSupportforSchool.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Crime Prevention Support for School</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detects suspiciously dressed persons at schools or cram schools to help prevent crimes in which dangerous individuals attempt to harm students.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q10_suspicious_person_detection<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q10_suspicious_person_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">16fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q10_suspicious_person_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city20" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3"
                data-targetobj="Vehicle"
                data-label="New!"
                data-device="RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/no_image.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Multi-Camera Vehicle Detector</dt>
                    <h6 class="appstatus" align="right"><b>New!</b></h6>
                    <div class="griditem-add">
                        Allows multi-directional detection of vehicle existence with multiple cameras.  It can prevent car accidents by noticing the cars outside of human sight.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> -<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 14_Multi_camera_vehicle_detection<br>
                        <b>Model:</b> Tiny YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/14_Multi_camera_vehicle_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">200fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city21" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3"
                data-targetobj="Vehicle"
                data-label="New!"
                data-device="RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/no_image.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Car Accident Prevention Alert</dt>
                    <h6 class="appstatus" align="right"><b>New!</b></h6>
                    <div class="griditem-add">
                        Alerts children or elderly individuals that there are vehicles nearby from wearable/portable devices attached to their backpacks by multi-directional vehicle detection.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> -<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 14_Multi_camera_vehicle_detection<br>
                        <b>Model:</b> Tiny YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/14_Multi_camera_vehicle_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">200fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city22" class="application_card col-lg-6 col-xl-4"
                data-model="Unet"
                data-targetobj="Other"
                data-label="New!"
                data-device="RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/no_image.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Driving Support with Road Lane Segmentation</dt>
                    <h6 class="appstatus" align="right"><b>New!</b></h6>
                    <div class="griditem-add">
                        Notifies drivers approaching the warning area by segmenting the road lane and crosswork.  It can prevent car accidents against people.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> -<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 15_Road_lane_segmentation<br>
                        <b>Model:</b> Unet<br>
                        <b>Dataset:</b> Road Lane Segmentation<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/15_Road_lane_segmentation" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">77fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="city23" class="application_card col-lg-6 col-xl-4"
                data-model="Unet"
                data-targetobj="Other"
                data-label="New!"
                data-device="RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/no_image.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Visual Walking Support</dt>
                    <h6 class="appstatus" align="right"><b>New!</b></h6>
                    <div class="griditem-add">
                        Notifies the people who require visual support when crossing the side lane or using the crosswalk.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> -<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 15_Road_lane_segmentation<br>
                        <b>Model:</b> Unet<br>
                        <b>Dataset:</b> Road Lane Segmentation<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/15_Road_lane_segmentation" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">77fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
        </div>
        <br>
        <br>
    </div>
</div>
<div id="healthcare" class="category_section container pb-4" data-category="Healthcare">
<h3 align="left"><i>Healthcare</i></h3>
<div class="container">
    <div class="row">
            <div id="healthcare1" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv2+HRNet"
                data-targetobj="Person"
                data-label="Updated!"
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Healthcare1_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Physical Condition Monitor</dt>
                    <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                    <div class="griditem-add">
                        Support the early rescue by detecting any changes in the body condition of patients/users in the hospitals and care facility when they are alone.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 03_Elderly_fall_detection<br>
                        <b>Model:</b> Tiny YOLOv2+HRNet<br>
                        <b>Dataset:</b> E-FPDS,FPDS_v2 Dataset/COCO | E-FPDS,FPDS_v2 Dataset/MPII Human Pose Dataset<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/03_Elderly_fall_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">5fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/03_Elderly_fall_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">175fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="healthcare2" class="application_card col-lg-6 col-xl-4"
                data-model="HRNet+Custom"
                data-targetobj="Person"
                data-label="New!"
                data-device="RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/no_image.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Yoga Pose Monitor</dt>
                    <h6 class="appstatus" align="right"><b>New!</b></h6>
                    <div class="griditem-add">
                        Detects the human body and analyzes the pose of yoga to correct the posture.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> -<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q12_yoga_pose_estimation<br>
                        <b>Model:</b> HRNet+Custom<br>
                        <b>Dataset:</b> COCO+Yoga Pose Classification<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q12_yoga_pose_estimation" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">53fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
        </div>
        <br>
        <br>
    </div>
</div>
<div id="home" class="category_section container pb-4" data-category="Smart Home">
<h3 align="left"><i>Smart Home</i></h3>
<div class="container">
    <div class="row">
            <div id="home1" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Head"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartHome1_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Air Conditioner Control</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Automatically controls the air conditioning according to the situation by counting the number of people in the room.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 11_Head_count_topview<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="home2" class="application_card col-lg-6 col-xl-4"
                data-model="ArcFace/ResNet-50"
                data-targetobj="Face"
                data-label=""
                data-device="RZ/V2L,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartHome4_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Smart TV</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Provides smart TV system, which switches to favorite TV channel by collecting the data of family members and TV contents that they watched.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> -<br>
                        <b>Function:</b> 06_Face_recognition_spoof_detection<br>
                        <b>Model:</b> ArcFace/ResNet-50<br>
                        <b>Dataset:</b> VGGFace2<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/06_Face_recognition_spoof_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">6fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="home3" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Animal"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartHome2_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Pet Detection in Kitchen and Child's Room</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Issues an alert when your pets have entered dangerous areas such as kitchen or children room.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 07_Animal_detection<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> Animals Detection Images Dataset+Images.cv+Coco Dataset<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/07_Animal_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/07_Animal_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="home4" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv2+ResNet-18/YOLOv3"
                data-targetobj="Hand"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartHome3_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Touchless Controller for Kitchen Appliance</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Allows you to control electrical appliances by the hand gestures without touching them.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 12_Hand_gesture_recognition_v2<br>
                        <b>Model:</b> Tiny YOLOv2+ResNet-18 | YOLOv3<br>
                        <b>Dataset:</b> YOLO-Hand-Detection/HaGRID | HaGRID<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/12_Hand_gesture_recognition_v2" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">13fps<br>for single hand</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/12_Hand_gesture_recognition_v2" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="home5" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3+Tesseract/YOLOv3+Tesseract"
                data-targetobj="Other"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/SmartHome5_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Food Package Expiry Date Check</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Monitors the expiry date of food placed in the refrigerator.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q06_expiry_date_detection<br>
                        <b>Model:</b> Tiny YOLOv3+Tesseract | YOLOv3+Tesseract<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q06_expiry_date_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">16fps for<br>Tiny YOLOv3</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q06_expiry_date_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps for<br>YOLOv3</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
        </div>
        <br>
        <br>
    </div>
</div>
<div id="industrial" class="category_section container pb-4" data-category="Industrial">
<h3 align="left"><i>Industrial</i></h3>
<div class="container">
    <div class="row">
            <div id="industrial1" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Head"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Industrial1_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Work Area Personnel Management</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Monitors attendance of workers by counting their number entered in the work area.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 01_Head_count<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> HollywoodHeads<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/01_Head_count" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/01_Head_count" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="industrial2" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Person"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Industrial4_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Access Control</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Monitors the total number of visitors by counting the number of people who have passed through the entrance/exit.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 02_Line_crossing_object_counting<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> HollywoodHeads<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">20fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/02_Line_crossing_object_counting" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="industrial3" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Other"
                data-label="Updated!"
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Industrial2_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Helmet and safety vest wearing monitor</dt>
                    <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                    <div class="griditem-add">
                        Increase the safety level in the factory by monitoring the helmet use.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 04_Safety_helmet_vest_detection<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> helmet-safety-vest-detection+Kaggle dataset<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/04_Safety_helmet_vest_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/04_Safety_helmet_vest_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="industrial4" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv2+ResNet-18/YOLOv3"
                data-targetobj="Hand"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Industrial3_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Touchless Controller for Industrial machine</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Machine button operation can be done without contact using gestures in factory.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 12_Hand_gesture_recognition_v2<br>
                        <b>Model:</b> Tiny YOLOv2+ResNet-18 | YOLOv3<br>
                        <b>Dataset:</b> YOLO-Hand-Detection/HaGRID | HaGRID<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/12_Hand_gesture_recognition_v2" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">13fps<br>for single hand</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/12_Hand_gesture_recognition_v2" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="industrial5" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv2+DeepPose/YOLOv3+DeepPose"
                data-targetobj="Face"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Industrial5_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Driver Monitoring System</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detects whether the driver is looking aside, yawning or closing his eyes. Prevents car accidents by detecting when the driver is getting sleepy while driving.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 10_Driver_monitoring_system<br>
                        <b>Model:</b> Tiny YOLOv2+DeepPose | YOLOv3+DeepPose<br>
                        <b>Dataset:</b> WIDERFACE/WFLW | Custom/WFLW<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/10_Driver_monitoring_system" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">7fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/10_Driver_monitoring_system" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="industrial6" class="application_card col-lg-6 col-xl-4"
                data-model="Custom"
                data-targetobj="Other"
                data-label="Updated!"
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Industrial6_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Species check support in Fish Factory</dt>
                    <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                    <div class="griditem-add">
                        Classifies the fish species shown in the camera to support the fish processing industry.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q04_fish_classification<br>
                        <b>Model:</b> Custom<br>
                        <b>Dataset:</b> Fish Dataset<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q04_fish_classification" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">20fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q04_fish_classification" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">250fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="industrial7" class="application_card col-lg-6 col-xl-4"
                data-model="Unet"
                data-targetobj="Crack"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Industrial7_DefectInspectionSupport.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Defect Inspection Support</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Monitors the factory production line to detect cracks in the manufactured products. It supports the product inspection process.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q09_crack_segmentation<br>
                        <b>Model:</b> Unet<br>
                        <b>Dataset:</b> Crack Segmentation Dataset<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q09_crack_segmentation" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">11fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q09_crack_segmentation" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">100fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="industrial8" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Other"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Industrial8_Aquaculture_Industrial_Support.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Aquaculture Industrial Support</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Monitors fish to help aquaculture operators to manage their resources.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q11_fish_detection<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q11_fish_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">17fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q11_fish_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">39fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
        </div>
        <br>
        <br>
    </div>
</div>
<div id="retail" class="category_section container pb-4" data-category="Retail">
<h3 align="left"><i>Retail</i></h3>
<div class="container">
    <div class="row">
            <div id="retail1" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Head"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Retail1_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Congestion Detection</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Issues an alert when the store is overcrowded with more customers.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 11_Head_count_topview<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="retail2" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv2+FairFace"
                data-targetobj="Face"
                data-label="Updated!"
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Retail3_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Smart POS</dt>
                    <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                    <div class="griditem-add">
                        Supports checking ages of customers by checking their age in front of the casher and linking the information with their purchase.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 05_Age_gender_detection<br>
                        <b>Model:</b> Tiny YOLOv2+FairFace<br>
                        <b>Dataset:</b> WIDERFACE/FairFace<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/05_Age_gender_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">10fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/05_Age_gender_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">182fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="retail3" class="application_card col-lg-6 col-xl-4"
                data-model="ResNet-18+Tiny YOLOv2"
                data-targetobj="Face"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Retail4_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Marketing Interest Analysis</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Monitors the gaze direction of customer in the retail store, which can be used to collect marketing information.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 09_Human_gaze_detection<br>
                        <b>Model:</b> ResNet-18+Tiny YOLOv2<br>
                        <b>Dataset:</b> ETH-XGaze/WIDERFACE<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/09_Human_gaze_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">8fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/09_Human_gaze_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">182fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="retail4" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Person"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Retail2_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Staying and flow line monitoring</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Collects marketing data by monitoring the number of people and duration of their stay in a certain place.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q01_footfall_counter<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> COCO<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">15fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">33fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="retail5" class="application_card col-lg-6 col-xl-4"
                data-model="YOLOv3"
                data-targetobj="Head"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Retail5_960x540.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Exhibition Participants Monitoring</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Monitor the number of visitors to an exhibition or other open space. Changes in the number of participants can also be detected since it counts the number of participants in real time.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> 11_Head_count_topview<br>
                        <b>Model:</b> YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">3fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
            <div id="retail6" class="application_card col-lg-6 col-xl-4"
                data-model="Tiny YOLOv3/YOLOv3"
                data-targetobj="Person"
                data-label=""
                data-device="RZ/V2L,RZ/V2H,"
                >
                <li class="griditem" style="list-style: none;">
                    <img src="img/Retail6_Store_Crime_Prevention.jpg" alt="application">
                    <dt class="mt-1" style="color: #2a289d;">Store Crime Prevention</dt>
                    <h6 class="appstatus" align="right"><b><br /></b></h6>
                    <div class="griditem-add">
                        Detects suspiciously dressed persons in convenience stores or unmanned stores to prevent theft.<br><br>
                    </div>
                    <div class="appspec">
                        <b>Supported RZ/V2L AI SDK:</b> v5.00<br>
                        <b>Supported RZ/V2H AI SDK:</b> v5.00<br>
                        <b>Function:</b> Q10_suspicious_person_detection<br>
                        <b>Model:</b> Tiny YOLOv3 | YOLOv3<br>
                        <b>Dataset:</b> Custom<br>
                        <br>
                    </div>
                    <dl>
                        <dd style="display: flex">
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q10_suspicious_person_detection" style="color:white">RZ/V2L ></a>
                                <p class="Perf-Framerate">16fps</p>
                            </div>
                            <div class="devicelinkbutton_parent">
                                <a class="devicelinkbutton" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q10_suspicious_person_detection" style="color:white">RZ/V2H ></a>
                                <p class="Perf-Framerate">40fps</p>
                            </div>
                        </dd>
                    </dl>
                </li>
            </div>
        </div>
        <br>
        <br>
    </div>
</div>
<div class="container">
    <div class="row">
        <div class="col-12" style="color: #b1b1b1; font-size: 12px;">
            <i>
                For license information, please see <a href="{{ site.url }}{{ site.baseurl }}{% link about-applications.md %}">About AI Applications.</a>
            </i>
        </div>
    </div>
</div>
<div class="container">
    <div class="row">
        <div class="col-12" align="right">
            <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#page-top" role="button">
Back to Top >
            </a>
        </div>
    </div>
</div>
<p>
    <br>
    <br>
</p>
<div class="container">
    <div id="application-filter" class="bg-light">
        <div id="filter-title">
            <h1 id="filter-titlecolor">Filter</h1>
            <button id="application-filter-erase-button" class="btn erase" aria-label="Erase" style="">
                <svg xmlns="http://www.w3.org/2000/svg"  font-size="30" fill="currentColor" class="bi bi-eraser">
                    <b>Clear all</b>
                </svg>
            </button>
        </div>
        <div id="application-filter-body">

            <div id="category-filter">
                <h3 id="category-filter-titlecolor">Category</h3>
                <div class="checkbox-group">
                    <input type="checkbox" id="Agriculture" class="filter_content" value="Agriculture">
                    <label for="Agriculture">Agriculture</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Smart Building" class="filter_content" value="Smart Building">
                    <label for="Smart Building">Smart Building</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Smart City" class="filter_content" value="Smart City">
                    <label for="Smart City">Smart City</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Healthcare" class="filter_content" value="Healthcare">
                    <label for="Healthcare">Healthcare</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Smart Home" class="filter_content" value="Smart Home">
                    <label for="Smart Home">Smart Home</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Industrial" class="filter_content" value="Industrial">
                    <label for="Industrial">Industrial</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Retail" class="filter_content" value="Retail">
                    <label for="Retail">Retail</label>
                </div>
            </div>
            <div id="model-filter">
                <h3 id="category-filter-titlecolor">Model</h3>
                <div class="checkbox-group">
                    <input type="checkbox" id="YOLOv3" class="filter_content" value="YOLOv3">
                    <label for="YOLOv3">YOLOv3</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Unet" class="filter_content" value="Unet">
                    <label for="Unet">Unet</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Tiny YOLOv3" class="filter_content" value="Tiny YOLOv3">
                    <label for="Tiny YOLOv3">Tiny YOLOv3</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Tiny YOLOv2" class="filter_content" value="Tiny YOLOv2">
                    <label for="Tiny YOLOv2">Tiny YOLOv2</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Tesseract" class="filter_content" value="Tesseract">
                    <label for="Tesseract">Tesseract</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="ResNet-50" class="filter_content" value="ResNet-50">
                    <label for="ResNet-50">ResNet-50</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="ResNet-18" class="filter_content" value="ResNet-18">
                    <label for="ResNet-18">ResNet-18</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="MLP" class="filter_content" value="MLP">
                    <label for="MLP">MLP</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="HRNet" class="filter_content" value="HRNet">
                    <label for="HRNet">HRNet</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="FairFace" class="filter_content" value="FairFace">
                    <label for="FairFace">FairFace</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="FaceNet" class="filter_content" value="FaceNet">
                    <label for="FaceNet">FaceNet</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="DeepPose" class="filter_content" value="DeepPose">
                    <label for="DeepPose">DeepPose</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Custom" class="filter_content" value="Custom">
                    <label for="Custom">Custom</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="CNN" class="filter_content" value="CNN">
                    <label for="CNN">CNN</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="ArcFace" class="filter_content" value="ArcFace">
                    <label for="ArcFace">ArcFace</label>
                </div>
            </div>
            <div id="target_object-filter">
                <h3 id="category-filter-titlecolor">Target Object</h3>
                <div class="checkbox-group">
                    <input type="checkbox" id="Animal" class="filter_content" value="Animal">
                    <label for="Animal">Animal</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Crack" class="filter_content" value="Crack">
                    <label for="Crack">Crack</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Face" class="filter_content" value="Face">
                    <label for="Face">Face</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Hand" class="filter_content" value="Hand">
                    <label for="Hand">Hand</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Head" class="filter_content" value="Head">
                    <label for="Head">Head</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Other" class="filter_content" value="Other">
                    <label for="Other">Other</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Person" class="filter_content" value="Person">
                    <label for="Person">Person</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Vehicle" class="filter_content" value="Vehicle">
                    <label for="Vehicle">Vehicle</label>
                </div>
            </div>
            <div id="device-filter">
                <h3 id="category-filter-titlecolor">Device</h3>
                <div class="checkbox-group">
                    <input type="checkbox" id="RZ/V2L" class="filter_content" value="RZ/V2L">
                    <label for="RZ/V2L">RZ/V2L</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="RZ/V2H" class="filter_content" value="RZ/V2H">
                    <label for="RZ/V2H">RZ/V2H</label>
                </div>
            </div>
            <div id="label-filter">
                <h3 id="category-filter-titlecolor">Status</h3>
                <div class="checkbox-group">
                    <input type="checkbox" id="New!" class="filter_content" value="New!">
                    <label for="New!">New!</label>
                </div>
                <div class="checkbox-group">
                    <input type="checkbox" id="Updated!" class="filter_content" value="Updated!">
                    <label for="Updated!">Updated!</label>
                </div>
            </div>
        </div>
    </div>

    <button id="application-filter-visible-button" class="btn btn-muted ">
        <svg width="16" height="16" font-size="30" fill="currentColor" class="bi bi-3x" viewBox="0 0 16 16" style="">
            <use xlink:href="assets/img/bootstrap-icons.svg#funnel"></use>
        </svg>
    </button>
    <div id="application-filter-button-container">
        <button id="application-filter-hide-button" class="btn close" aria-label="Close">
            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" font-size="30" fill="currentColor" class="bi bi-x-lg" viewBox="0 0 16 16">
                <path d="M2.146 2.854a.5.5 0 1 1 .708-.708L8 7.293l5.146-5.147a.5.5 0 0 1 .708.708L8.707 8l5.147 5.146a.5.5 0 0 1-.708.708L8 8.707l-5.146 5.147a.5.5 0 0 1-.708-.708L7.293 8 2.146 2.854Z"></path>
            </svg>
        </button>
    </div>
</div>

<script>
    document.addEventListener('DOMContentLoaded', function () {

        function toggleButtons() {
            if (window.innerWidth < 992) {
                document.getElementById('application-filter').style.display = 'none';
                document.getElementById('application-filter-visible-button').style.display = 'block';
                document.getElementById('application-filter-erase-button').style.display = 'none';
                document.getElementById('application-filter-hide-button').style.display = 'none';
            } else {
                document.getElementById('application-filter').style.display = 'block';
                document.getElementById('application-filter-visible-button').style.display = 'none';
                document.getElementById('application-filter-erase-button').style.display = 'block';
                document.getElementById('application-filter-hide-button').style.display = 'none';
            }
        }

        toggleButtons();

        document.getElementById('application-filter-visible-button').addEventListener('click', function () {
            document.getElementById('application-filter').style.display = 'block';
            document.getElementById('application-filter-erase-button').style.display = 'block';
            document.getElementById('application-filter-hide-button').style.display = 'block';
            this.style.display = 'none';
        });

        document.getElementById('application-filter-hide-button').addEventListener('click', function () {
            document.getElementById('application-filter').style.display = 'none';
            document.getElementById('application-filter-erase-button').style.display = 'none';
            document.getElementById('application-filter-visible-button').style.display = 'block';
            this.style.display = 'none';
        });

        document.getElementById('application-filter-erase-button').addEventListener('click', function () {
            document.querySelectorAll('.filter_content').forEach(function (checkbox) {
                checkbox.checked    = false;
            });
            filterData();
        });

        window.addEventListener('resize', toggleButtons);

        document.querySelectorAll('.filter_content').forEach(function (checkbox) {
            checkbox.addEventListener('change', filterData);
        });
        
    });

    function filterData() {
        let selectedCategories = getSelectedValues('category-filter');

        let selectedModels = getSelectedValues('model-filter');
        let selectedTargetObjs = getSelectedValues('target_object-filter');
        let selectedDevices = getSelectedValues('device-filter');
        // let selectedInputSrcs = getSelectedValues('input_source-filter');
        let selectedLabels = getSelectedValues('label-filter');

        let cateDivs = document.querySelectorAll('.category_section');
        let appsDivs = document.querySelectorAll('[data-model], [data-targetobj], [data-device], [data-label]');//, [data-inputsrc]');
        appsDivs.forEach(function (div) {
            let models      = div.getAttribute('data-model').split(/[+/]/).filter(Boolean);
            let targetobjs  = div.getAttribute('data-targetobj').split(',').filter(Boolean);
            let devices     = div.getAttribute('data-device').split(',').filter(Boolean);
            // let inputsrcs   = div.getAttribute('data-inputsrc').split(',').filter(Boolean);
            let labels     = div.getAttribute('data-label').split(',').filter(Boolean);

            let modelCondition = selectedModels.length === 0 || models.some(function(value) {
                return selectedModels.includes(value.trim());
            });
            let targetObjCondition = selectedTargetObjs.length === 0 || targetobjs.some(function(value) {
                return selectedTargetObjs.includes(value.trim());
            });
            let deviceCondition = selectedDevices.length === 0 || devices.some(function(value) {
                return selectedDevices.includes(value.trim());
            }); 
            // let inputSrcCondition = selectedInputSrcs.length === 0 || inputsrcs.some(function(value) {
            //     return selectedInputSrcs.includes(value.trim());
            // }); 
            let labelCondition = selectedLabels.length === 0 || labels.some(function(value) {
                return selectedLabels.includes(value.trim());
            }); 

                        toggleVisibility(div, modelCondition && targetObjCondition && deviceCondition && labelCondition );// && inputSrcCondition);
        });

        cateDivs.forEach(function (div) {
            let category = div.getAttribute('data-category');

            let categoryCondition = selectedCategories.length === 0 || selectedCategories.includes(category);
            toggleVisibility(div, categoryCondition);

            let appCards = div.querySelectorAll('.application_card');
            let allAppCardsCollapsed = Array.from(appCards).every(function (appCard) {
                return appCard.classList.contains('collapse');
            });
            if (allAppCardsCollapsed) div.classList.add('collapse');

            scrollToTop();
        });
    }

    function getSelectedValues(filter_id) {
        let filterGroup = document.getElementById(filter_id);
        if(!filterGroup)    return [];
        return Array.from(filterGroup.getElementsByClassName('filter_content'))
            .filter(function (checkbox) {
                return checkbox.checked;
            })
            .map(function (checkbox) {
                return checkbox.value;
            });
    }

    function toggleVisibility(element, isVisible) {
        if (isVisible) {
            element.classList.remove('collapse');
        } else {
            element.classList.add('collapse');
        }
    }

    function scrollToTop() {
        window.scrollTo({
            top: 0,
            behavior: 'smooth'
        });
    }

</script>
<!----------------------------------------->
