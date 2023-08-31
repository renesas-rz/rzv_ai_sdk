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
        <div class="col-lg-6 col-xl-4">
            <a id="agriculture1" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/07_Animal_detection">
                <img class="appimage" src="img/Agriculture1_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Defense wild animals for crop</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Detect the types of animals that enter your farm or barn for pest control.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 07_Animal_detection<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: Animals Detection Images Dataset+Images.cv+Coco Dataset<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="agriculture2" class="applications" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q07_plant_disease_classification">
                <img class="appimage" src="img/Agriculture2_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Fruit and Vegetable Plant Disease Check</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Supports farmer by classifying whether the plant has a disease or not.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: Q07_plant_disease_classification<br>
                        <b>Model</b>: Custom<br>
                        <b>Dataset</b>: New Plant Diseases Dataset<br>
                        <!-- <b>Performance</b>: 9fps -->
                    </li>
                </ul>
            </a>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="building" align="left"><i>Smart Building</i></h3>
<div class="container">
    <div class="row">
        <div class="col-lg-6 col-xl-4">
            <a id="building1" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/01_Head_count">
                <img class="appimage" src="img/SmartBuilding1_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Elevator passengers Counting</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Issues alerts if the elevator is overcrowded and exceeds its capacity.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 01_Head_count<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: HollywoodHeads<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="building2" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview">
                <img class="appimage" src="img/SmartBuilding2_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Conference Room Usage Monitor</p>
                        <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                        Monitors if the meeting room is vacant by counting the number of people in the room.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 11_Head_count_topview<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: Various dataset<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="building3" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview">
                <img class="appimage" src="img/SmartBuilding3_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Lighting Control</p>
                        <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                        Automatically controls the lighting according to the situation by counting the number of people in the room.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 11_Head_count_topview<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: Various dataset<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="building4" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting">
                <img class="appimage" src="img/SmartBuilding4_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Security Area Intrusion Detection</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Detects illegal intrusions to security area in the office.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 02_Line_crossing_object_counting<br>
                        <b>Model</b>: TinyYOLOv2<br>
                        <b>Dataset</b>: COCO<br>
                        <!-- <b>Performance</b>: 13fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="building5" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/04_Safety_helmet_vest_detection">
                <img class="appimage" src="img/SmartBuilding5_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Wear management at construction sites</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Analyzes the equipment of workers before entering the construction site by detecting the necessary equipment such as helmet or vest. It can be used to reduce the overload of monitoring person and ensure workers to wear appropriate equipment.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 04_Safety_helmet_vest_detection<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: Safety Helmet Detection on kaggle<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="building6" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/12_Hand_gesture_recognition_v2">
                <img class="appimage" src="img/SmartBuilding6_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Touchless Controller for elevator</p>
                        <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                        By using hand gestures, elevator operation can be done without touching the buttons.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 12_Hand_gesture_recognition_v2<br>
                        <b>Model</b>: TinyYOLOv2+ResNet18<br>
                        <b>Dataset</b>: YOLO-Hand-Detection for hand detection and HAgrid for classifier<br>
                        <!-- <b>Performance</b>: 11~20fps for single hand -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="building7" class="applications" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication">
                <img class="appimage" src="img/SmartBuilding7_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Employee ID check for Restricted Area</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Checks the employee ID and the person matches before entering to restricted area.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: Q02_face_authentication<br>
                        <b>Model</b>: FaceNet<br>
                        <b>Dataset</b>: FaceNet<br>
                        <!-- <b>Performance</b>: 2fps -->
                    </li>
                </ul>
            </a>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="city" align="left"><i>Smart City</i></h3>
<div class="container">
    <div class="row">
        <div class="col-lg-6 col-xl-4">
            <a id="city1" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview">
                <img class="appimage" src="img/SmartCity1_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Congestion Detection in Railway Station</p>
                        <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                        Monitors the congestion level on trains and buses by detecting the number of passengers.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 11_Head_count_topview<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: Various dataset<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="city2" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting">
                <img class="appimage" src="img/SmartCity2_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Prohibited Area Management</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Prevents accidents and detects illegal intrusions in construction site by detecting the entry to prohibited areas.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 02_Line_crossing_object_counting<br>
                        <b>Model</b>: TinyYOLOv2<br>
                        <b>Dataset</b>: COCO<br>
                        <!-- <b>Performance</b>: 13fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="city3" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/09_Human_gaze_detection">
                <img class="appimage" src="img/SmartCity3_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Distracted driving detection</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Issues an alert when the driver is distracted by detecting the line of sight.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 09_Human_gaze_detection<br>
                        <b>Model</b>: ResNet-18+Tiny YOLOv2<br>
                        <b>Dataset</b>: ETH-XGaze+WIDERFACE<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="city4" class="applications" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter">
                <img class="appimage" src="img/SmartCity6_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Duration monitoring for surveillance camera</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Prevents the theft by monitoring whether there is a suspicious person wandering around the specified area.  Can be used in car dealer, housing, etc.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: Q01_footfall_counter<br>
                        <b>Model</b>: TinyYOLOv3<br>
                        <b>Dataset</b>: COCO<br>
                        <!-- <b>Performance</b>: 9fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="city5" class="applications" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q03_smart_parking">
                <img class="appimage" src="img/SmartCity4_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Parking Spot Reservation</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Detects the occupancy of parking spot for reservation system.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: Q03_smart_parking<br>
                        <b>Model</b>: Custom<br>
                        <b>Dataset</b>: Custom<br>
                        <!-- <b>Performance</b>: 4-7 msec per slot -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="city6" class="applications" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q03_smart_parking">
                <img class="appimage" src="img/SmartCity7_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Illegal Parking Check</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Detects the parking violation by monitoring the car presence in a restricted area.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: Q03_smart_parking<br>
                        <b>Model</b>: Custom<br>
                        <b>Dataset</b>: Custom<br>
                        <!-- <b>Performance</b>: 4-7 msec per slot -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="city7" class="applications" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication">
                <img class="appimage" src="img/SmartCity5_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Passport check support</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Supports passport check in airport immigration by checking the match of users face and their passport.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: Q02_face_authentication<br>
                        <b>Model</b>: FaceNet<br>
                        <b>Dataset</b>: FaceNet<br>
                        <!-- <b>Performance</b>: 2fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="city8" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview">
                <img class="appimage" src="img/SmartCity8_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Bus passenger counting</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Counts the number of passengers on public transportation. It is also effective in preventing children from being left behind on school buses.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 11_Head_count_topview<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: Various dataset<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="city9" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting">
                <img class="appimage" src="img/SmartCIty9_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Backtravel Detection</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Detects people going backwards on one-way stairs, aisles, or escalators. Helps preventing congestion and accidents.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 02_Line_crossing_object_counting<br>
                        <b>Model</b>: TinyYOLOv2<br>
                        <b>Dataset</b>: COCO<br>
                        <!-- <b>Performance</b>: 13fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="city10" class="applications" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q05_suspicious_activity">
                <img class="appimage" src="img/SmartCity10_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Violence Activity Check in Surveillance Camera</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Supports the surveillance system by monitoring the suspicious/violent activity.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: Q05_suspicious_activity<br>
                        <b>Model</b>: EfficientNet+MLP<br>
                        <b>Dataset</b>: Real Life Violence Situations Dataset<br>
                        <!-- <b>Performance</b>: 2fps -->
                    </li>
                </ul>
            </a>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="healthcare" align="left"><i>Healthcare</i></h3>
<div class="container">
    <div class="row">
        <div class="col-lg-6 col-xl-4">
            <a id="healthcare1" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/03_Elderly_fall_detection">
                <img class="appimage" src="img/Healthcare1_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Physical Condition Monitor</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Support the early rescue by detecting any changes in the body condition of patients/users in the hospitals and care facility when they are alone.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 03_Elderly_fall_detection<br>
                        <b>Model</b>: TinyYOLOv2+HRNet<br>
                        <b>Dataset</b>: PASCAL VOC+COCO<br>
                        <!-- <b>Performance</b>: 5fps -->
                    </li>
                </ul>
            </a>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="home" align="left"><i>Smart Home</i></h3>
<div class="container">
    <div class="row">
        <div class="col-lg-6 col-xl-4">
            <a id="home1" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview">
                <img class="appimage" src="img/SmartHome1_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Air Conditioner Control</p>
                        <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                        Automatically controls the air conditioning according to the situation by counting the number of people in the room.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 11_Head_count_topview<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: Various dataset<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="home2" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/06_Face_recognition_spoof_detection">
                <img class="appimage" src="img/SmartHome4_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Smart TV</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Provides smart TV system, which switches to favorite TV channel by collecting the data of family members and TV contents that they watched.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 06_Face_recognition_spoof_detection<br>
                        <b>Model</b>: ResNet-50<br>
                        <b>Dataset</b>: VGGFace2<br>
                        <!-- <b>Performance</b>: 11fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="home3" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/07_Animal_detection">
                <img class="appimage" src="img/SmartHome2_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Pet Detection in Kitchen and Child's Room</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Issues an alert when your pets have entered dangerous areas such as kitchen or children room.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 07_Animal_detection<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: Animals Detection Images Dataset+Images.cv+Coco Dataset<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="home4" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/12_Hand_gesture_recognition_v2">
                <img class="appimage" src="img/SmartHome3_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Touchless Controller for Kitchen Appliance</p>
                        <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                        Allows you to control electrical appliances by the hand gestures without touching them.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 12_Hand_gesture_recognition_v2<br>
                        <b>Model</b>: TinyYOLOv2+ResNet18<br>
                        <b>Dataset</b>: YOLO-Hand-Detection for hand detection and HAgrid for classifier<br>
                        <!-- <b>Performance</b>: 11~20fps for single hand -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="home5" class="applications" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q06_expiry_date_detection">
                <img class="appimage" src="img/SmartHome5_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Food Package Expiry Date Check</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Monitors the expiry date of food placed in the refrigerator.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: Q06_expiry_date_detection<br>
                        <b>Model</b>: TinyYOLOv3+Tesseract<br>
                        <b>Dataset</b>: ExpDate<br>
                        <!-- <b>Performance</b>: 9fps for TinyYOLOv3 -->
                    </li>
                </ul>
            </a>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="industrial" align="left"><i>Industrial</i></h3>
<div class="container">
    <div class="row">
        <div class="col-lg-6 col-xl-4">
            <a id="industrial1" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/01_Head_count">
                <img class="appimage" src="img/Industrial1_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Work Area Personnel Management</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Monitors attendance of workers by counting their number entered in the work area.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 01_Head_count<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: HollywoodHeads<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="industrial2" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/02_Line_crossing_object_counting">
                <img class="appimage" src="img/Industrial4_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Access Control</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Monitors the total number of visitors by counting the number of people who have passed through the entrance/exit.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 02_Line_crossing_object_counting<br>
                        <b>Model</b>: TinyYOLOv2<br>
                        <b>Dataset</b>: COCO<br>
                        <!-- <b>Performance</b>: 13fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="industrial3" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/04_Safety_helmet_vest_detection">
                <img class="appimage" src="img/Industrial2_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Helmet and safety vest wearing monitor</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Increase the safety level in the factory by monitoring the helmet use.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 04_Safety_helmet_vest_detection<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: Safety Helmet Detection on kaggle<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="industrial4" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/12_Hand_gesture_recognition_v2">
                <img class="appimage" src="img/Industrial3_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Touchless Controller for Industrial machine</p>
                        <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                        Machine button operation can be done without contact using gestures in factory.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 12_Hand_gesture_recognition_v2<br>
                        <b>Model</b>: TinyYOLOv2+ResNet18<br>
                        <b>Dataset</b>: YOLO-Hand-Detection for hand detection and HAgrid for classifier<br>
                        <!-- <b>Performance</b>: 11~20fps for single hand -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="industrial5" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/10_Driver_monitoring_system">
                <img class="appimage" src="img/Industrial5_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Driver Monitoring System</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Detects whether the driver is looking aside, yawning or closing his eyes. Prevents car accidents by detecting when the driver is getting sleepy while driving.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 10_Driver_monitoring_system<br>
                        <b>Model</b>: TinyYOLOv2+DeepPose<br>
                        <b>Dataset</b>: WIDERFACE/WFLW<br>
                        <!-- <b>Performance</b>: 6fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="industrial6" class="applications" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q04_fish_classification">
                <img class="appimage" src="img/Industrial6_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Species check support in Fish Factory</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Classifies the fish species shown in the camera to support the fish processing industry.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: Q04_fish_classification<br>
                        <b>Model</b>: EfficientNet based<br>
                        <b>Dataset</b>: Fish Dataset<br>
                        <!-- <b>Performance</b>: 15fps -->
                    </li>
                </ul>
            </a>
        </div>
    </div>
</div>
<br>
<br>
<h3 id="retail" align="left"><i>Retail</i></h3>
<div class="container">
    <div class="row">
        <div class="col-lg-6 col-xl-4">
            <a id="retail1" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview">
                <img class="appimage" src="img/Retail1_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Congestion Detection</p>
                        <h6 class="appstatus" align="right"><b>Updated!</b></h6>
                        Issues an alert when the store is overcrowded with more customers.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 11_Head_count_topview<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: Various dataset<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="retail2" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/05_Age_gender_detection">
                <img class="appimage" src="img/Retail3_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Smart POS</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Supports checking ages of customers by checking their age in front of the casher and linking the information with their purchase.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 05_Age_gender_detection<br>
                        <b>Model</b>: ResNet-18/ResNet-50<br>
                        <b>Dataset</b>: Unknown<br>
                        <!-- <b>Performance</b>: 27fps/11fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="retail3" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/09_Human_gaze_detection">
                <img class="appimage" src="img/Retail4_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Marketing Interest Analysis</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Monitors the gaze direction of customer in the retail store, which can be used to collect marketing information.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 09_Human_gaze_detection<br>
                        <b>Model</b>: ResNet-18+Tiny YOLOv2<br>
                        <b>Dataset</b>: ETH-XGaze+WIDERFACE<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="retail4" class="applications" href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter">
                <img class="appimage" src="img/Retail2_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Staying and flow line monitoring</p>
                        <h6 class="appstatus" align="right"><b><br /></b></h6>
                        Collects marketing data by monitoring the number of people and duration of their stay in a certain place.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: Q01_footfall_counter<br>
                        <b>Model</b>: TinyYOLOv3<br>
                        <b>Dataset</b>: COCO<br>
                        <!-- <b>Performance</b>: 9fps -->
                    </li>
                </ul>
            </a>
        </div>
        <div class="col-lg-6 col-xl-4">
            <a id="retail5" class="applications" href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/11_Head_count_topview">
                <img class="appimage" src="img/Retail5_960x540.jpg" alt="application"/>
                <ul class="applabel">
                    <li>RZ/V2L</li>
                </ul>
                <ul class="appdetails">
                    <li>
                        <p class="name">Exhibition Participants Monitoring</p>
                        <h6 class="appstatus" align="right"><b>New!</b></h6>
                        Monitor the number of visitors to an exhibition or other open space. Changes in the number of participants can also be detected since it counts the number of participants in real time.<br><br>
                        <b>Supported AI SDK</b>: v2.00<br>
                        <b>Function</b>: 11_Head_count_topview<br>
                        <b>Model</b>: YOLOv3<br>
                        <b>Dataset</b>: Various dataset<br>
                        <!-- <b>Performance</b>: 3fps -->
                    </li>
                </ul>
            </a>
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
    