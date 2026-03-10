---
layout: default
---

<div class="container">
    <div class="row">
        <div class="top col-12">
            RZ/V Reference Applications
        </div>
    </div>
</div>

<br>
<br>
This page shows the RZ/V Reference Applications, which are a set of sample applications that help your solution development not only for AI, but also for camera control, encoding, etc..<br>
For any enquiries, please use Renesas Technical Support.<br>
<a class="btn btn-secondary square-button ms-3 mt-1" 
    style="text-align:left;" 
    href="https://www.renesas.com/support" 
    role="button"
    target="_blank" 
    rel="noopener noreferrer">
    <span class="banner-title" style="line-height:1.0;">
        Technical Support >
        <br>
        <span style="font-size:70%;font-weight: normal;">
            Forum, FAQ and Support Tickets.<br>
        </span>
    </span>
</a>
<br>
<br>
<div class="container">
    <div class="row">
        <div id="ref1" class="application_card col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/ref_app/renesas_v2n_isp_960x540.jpg" alt="application">
                <dt class="mt-1" style="color: #2a289d;">Dual Camera Video Encode + AI Reference</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    The reference application for camera system control with LSI-integrated ISP.<br>
                    Input images are captured by two camera sensors via MIPI-I/F, which are processed by the LSI-integrated ISP.<br>
                    Each image is subjected to encoding and AI processing. <br>
                    AI processing options are classification, object detection, etc..<br>
                    The output can be checked on PC sent via Ethernet.
                    <br>
                    <br>
                    The sample application is included in the RZ/V ISP Support Package and requires users to submit secure access request.<br><br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="partnerlinkbutton_parent">
                            <a class="partnerlinkbutton" 
                                href="https://www.renesas.com/software-tool/rzv2n-isp-support-package" 
                                style="color:white"
                                target="_blank" rel="noopener noreferrer">
                                RZ/V2N >
                            </a>
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="ref2" class="application_card col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/ref_app/renesas_face-mosaic1_trimmed_resized.jpg" alt="application">
                <dt class="mt-1" style="color: #2a289d;">Face mosaic application</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Image data is captured using a USB camera, and human heads are detected using AI processing. <br>
                    The detected heads are subjected to a mosaic process, and the results are displayed on a monitor via HDMI.<br>
                    On RZ/V2H, image processing is performed by OpenCV Accelerator.<br><br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="partnerlinkbutton_parent">
                            <a class="partnerlinkbutton" 
                                href="https://github.com/renesas-rz/rzv_sample_apps/tree/main/S01_face_mosaic" 
                                style="color:white"
                                target="_blank" rel="noopener noreferrer">
                                Click >
                            </a>
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="ref3" class="application_card col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/ref_app/renesas_distortion-correction2_resized.jpg" alt="application">
                <dt class="mt-1" style="color: #2a289d;">Lens distortion correction application</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Image data is captured using a MIPI camera, and lens distortion is corrected using OpenCV's remap. <br>
                    The processed results are displayed alongside the camera image on a display via HDMI.<br> 
                    Image processing can also be performed by OpenCV Accelerator.<br>
                    This application also has a calibration function, so it can handle distortion caused by various lenses.<br><br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="partnerlinkbutton_parent">
                            <a class="partnerlinkbutton" 
                                href="https://github.com/renesas-rz/rzv_sample_apps/tree/main/S02_remap" 
                                style="color:white"
                                target="_blank" rel="noopener noreferrer">
                                Click >
                            </a>
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <br>
        <br>
        <div id="ref4" class="application_card col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/ref_app/renesas_dashcam_960x540.jpg" alt="application">
                <dt class="mt-1" style="color: #2a289d;">Dashcam System Control Reference</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    The reference application for dashcam system.<br>
                    Input images are captured by two camera sensors via MIPI-I/F which are processed by the LSI-integrated ISP.<br>
                    Each image is subjected to video encoding and AI processing.<br>
                    AI processing can be selected from the Driver Monitoring, the gaze detection, etc..  <br>
                    Output can be verified in two ways.  
                    <ul class="mb-0">
                        <li>
                        The result can be displayed on PC via Ethernet;<br>
                        </li>
                        <li>
                        The output image is saved on microSD card for recording purposes.<br>
                        </li>
                    </ul>
                    <br>
                    The application is included in the RZ/V ISP Support Package as <b>"Sample application No.2"</b>, and requires users to submit secure access request. 
                    <br><br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="partnerlinkbutton_parent">
                            <a class="partnerlinkbutton" 
                                href="https://www.renesas.com/software-tool/rzv2n-isp-support-package" 
                                style="color:white"
                                target="_blank" rel="noopener noreferrer">
                                RZ/V2N >
                            </a>
                        </div>
                    </dd>
                </dl>
            </li>
        </div> 
        <br>
    </div>
<!-- Template -->
    <!-- <div class="row">
        <div class="col-12">
            <h3>Company Name</h3>
        </div>
        <div class="col-9">
            Company overview, features, etc.<br>
        </div>
        <div class="col-3">
            <img src="img/community/no_image.jpg" alt="board"/>
        </div>
    </div>
    <br>
    <div class="row">
        <div id="" class="application_card col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/community/no_image.jpg" alt="application">
                <dt class="mt-1" style="color: #2a289d;">Application Name</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    The application image size must be size of 960x540. The maximum number of characters for application name above and application explanation (this statement) is note stated, but note that longer sentense may not look fancy.<br><br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="partnerlinkbutton_parent">
                            <a class="partnerlinkbutton" 
                                href="" 
                                style="color:white"
                                target="_blank"
                                rel="noopener noreferrer">
                                Click >
                            </a>
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
        <div id="" class="application_card col-lg-6 col-xl-4">
            <li class="griditem" style="list-style: none;">
                <img src="img/SmartCIty9_960x540.jpg" alt="application">
                <dt class="mt-1" style="color: #2a289d;">Application Name</dt>
                <h6 class="appstatus" align="right"><b><br /></b></h6>
                <div class="griditem-add">
                    Explanation Explanation  Explanation  Explanation  Explanation  Explanation  Explanation  Explanation  Explanation  Explanation  Explanation  Explanation.<br><br>
                </div>
                <dl>
                    <dd style="display: flex">
                        <div class="partnerlinkbutton_parent">
                            <a class="partnerlinkbutton" 
                                href="" 
                                style="color:white"
                                target="_blank"
                                rel="noopener noreferrer">
                                Click >
                            </a>
                        </div>
                    </dd>
                </dl>
            </li>
        </div>
    </div> -->
<!-- Template End -->
    <br>
    <br>
    <br>
    <div class="row">
        <div class="col-12" align="right">
            <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}" role="button">
                Back to Home >
            </a>
        </div>
    </div>
</div>
