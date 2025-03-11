---
layout: default
---

<div class="container">
    <div id="page-top" class="row webtop ">
        <div class="col-12 col-lg-5">
            <div class="row">
                <div class="col-12 col-sm-6 col-lg-12">
                    <span style="font-size: 38px">
                        RZ/V AI Web
                    </span>
                </div>
                <div class="col-12 col-sm-6 col-lg-12">
                    <p class="ms-3">
                        <a class="btn btn-secondary chkout-btn mt-1" 
                            style=" text-align:left;" 
                            href="{{ site.url }}{{ site.baseurl }}{% link ai-software.md %}" 
                            role="button">
                            <span class="banner-title" style="line-height:1.0;">
                                <span style="font-size:80%;">
                                    First, check out 
                                </span><br>
                                <span style="font-size:100%;">
                                    RZ/V AI Software
                                </span>
                            </span><br>
                        </a>
                    </p>    
                </div>
            </div>
        </div>
        <!-- <div class="col-7 top-message lg-no-display">
            <i>
                <span class="main-message">The best solution for starting your AI applications.</span>
                <br>
                <span class="sub-message">
                    AI Applications and AI SDK are quick and easy solutions for starting AI.  
                    <br>
                    It provides various AI applications for free.
                </span>
            </i>
        </div> -->
    </div>
</div>
<div class="container">
    <div class="row">
        <div class="col-12 text-center">
        <!-- <div class="col-12 text-center lg-display"> -->
            <!-- <br> -->
            <br>
            <i>
                <h4 class="mb-2">
                    The best solution for starting your AI applications.
                </h4>
                <h5>
                    AI Applications and AI SDK are quick and easy solutions for starting AI.  <br>
                    It provides various AI applications for free.
                </h5>
            </i>
        </div>
        <!-- <br> -->
        <div class="col-12 text-center mb-5">
            <br>
            <a href="img/top_rzv.svg" data-lightbox="group"><img src="img/top_rzv.svg" alt="AI Application and AI SDK overview"></a><br>
        </div>
        <br>
        <br>
        <br>
    </div>
</div>
<br>
<h3 id="new" >
    What's new
</h3>
<div class="container">
    <div class="row">
        <div class="col-12">
            <h6 align="right" >
                2025.3.11
            </h6>
            <ul>
                <li>
                    <b>AI Applications v5.10</b> is released.
                    <ul>
                        <li> 
                            Added RZ/V2N Evaluation Board Kit support for 51 applications.
                        </li>
                        <li> 
                            Updated the AI model used in 3 applications.
                            <ul>
                                <li> 
                                    Multi-Camera Parking Lot Management
                                </li>
                                <li> 
                                    Multi-Camera Vehicle Detector
                                </li>
                                <li> 
                                    Car Accident Prevention Alert
                                </li>
                            </ul>
                        </li>
                        <li> 
                            Supported RZ/V2N AI SDK v5.00.
                        </li>
                    </ul>
                </li>
            </ul>
            For more details, see <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}"><b>AI Applications</b></a>.
            <br>
            <br>
            <ul>
                <li>
                    <b>RZ/V2N AI SDK v5.00</b> is released.
                    <ul>
                        <li> 
                            Supported DRP-AI TVM v2.3.0.<br>
                        </li>
                        <li> 
                            Supported RZ/V2N Linux BSP v1.0.0.<br>
                        </li>
                        <li>
                            Supported Graphics Library Unrestricted Version v3.1.2.3.<br>
                        </li>
                        <li>
                            Supported Video Codec Library v3.3.3.1.<br>
                        </li>
                        <li>
                            Supported OpenCV Accelerator v1.10.<br>
                        </li>
                    </ul>
                </li>
            </ul>
            For more details, see <a href="{{ site.url }}{{ site.baseurl }}{% link ai-sdk.md %}#v2n-spec"><b>RZ/V2N AI SDK Specification</b></a>.
            <br>
            <br>
        </div>
        <div class="col-12" align="right">
            <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link history.md %}" role="button">
                View Version History >
            </a>
        </div>
    </div>
</div>
<br>
<br>
<br>
<h3 id="getting-started" >Getting Started</h3>
<div class="container">
    <div class="row">
        <div class="col-12 col-sm-8">
            Renesas RZ/V AI Software Development Kit (AI SDK) is the most comprehensive solution for building end-to-end accelerated AI applications.  
            <br>
            <br>
            Getting Started is a complete guide to learn how to run RZ/V AI Applications with RZ/V AI SDK.
            <br>
            <!-- <h5>Get your target board now and <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}">GET STARTED.</a></h5> -->
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left; width: 70%;" href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" role="button">
                <span class="banner-title" style="line-height:1.0;">
                    <span style="font-size:70%;">
                        Get the target board now and
                    </span><br>
                    Get Started!
                </span><br>
                <span class="banner-line">
                    How to startup RZ/V board? How to run AI Applications?
                </span>
            </a>
            <br>
            <br>
            <a href="#video">Tutorial video</a> will help you understand better. <br>
        </div>
        <div class="start col-12 col-sm-4">
            <!-- <img  src="img/get_started.svg" alt="Get Started"/> -->
            <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}">
                <img src="img/get_started.svg" alt="Get Started">
            </a>
        </div>
    </div>
</div>
 
<br>
<br>
<br>

<h3 id="ai-applications">AI Applications</h3>
<!-- <p align="center">
    AI Applications provides the source code, pre-build application binary and pre-trained AI model objects,<br>
    which allow you to select the application from various use cases, and run it on the board immediately.<br>
    To see the overview about AI Applications, please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link about-applications.md %}">About AI Applications</a> page.<br>
</p>
<p align="center">Choose the category of applications.</p> -->

<div class="container">
    <div class="row">
        <div class="col-12">
            AI Applications provides the source code, pre-build application binary and pre-trained AI model objects, which allow you to select the application from various use cases, and run it on the board immediately.<br>
        </div>
    </div>
    <div class="row">
        <div class="col-12">
            <h4 class="u_line">
                Find your AI Application
            </h4>
        </div>
        <div class="col-12 col-lg-6 col-xl-4">
            <a class="btn btn-secondary square-button ms-3 mt-1" 
                style="text-align:left; width: 100%;" 
                href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}" 
                role="button">
                <span class="banner-title" style="line-height:1.0;">
                    RZ/V AI Applications >
                </span><br>
                <span class="banner-line lg-no-display">
                    List of AI Applications<br>
                    Can be used AS IS.
                </span>
            </a>
        </div>
        <div class="col-12 col-lg-6 col-xl-4">
            <a class="btn btn-secondary square-button-gray ms-3 mt-1" 
                style="text-align:left; width: 100%; " 
                href="{{ site.url }}{{ site.baseurl }}{% link about-applications.md %}" 
                role="button">
                <span class="banner-title" style="line-height:1.0;">
                    About AI Applications >
                </span><br>
                <span class="banner-line lg-no-display">
                    What is AI Applications?<br>
                    How is directory/file structured?
                </span>
            </a>
        </div>
    </div>
</div>
<div class="container">
    <div class="row mb-5">
        <div class="col-12 mb-2">
            <h4 class="u_line">
                Category
            </h4>
            You can search the AI Application by its category.
            <br>
        </div>
        <div class="col-6 col-lg-4 col-xxl-3">
            <div id="agriculture" class="category pb-2">
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#agriculture">
                        <img width="100%" src="img/agriculture.jpg" alt="category"/>
                        <p class="mt-1 mb-0">Agriculture</p>
                    </a> 
            </div>
        </div>
        <div class="col-6 col-lg-4 col-xxl-3">
            <div id="healthcare" class="category pb-2">
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#healthcare">
                        <img width="100%" src="img/healthcare.jpg" alt="category"/>
                        <p class="mt-1 mb-0">Healthcare</p>
                    </a> 
            </div>
        </div>
        <div class="col-6 col-lg-4 col-xxl-3">
            <div id="industrial" class="category pb-2">
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#industrial">
                        <img width="100%" src="img/industry.jpg" alt="category"/>
                        <p class="mt-1 mb-0">Industrial</p>
                    </a> 
            </div>
        </div>
        <div class="col-6 col-lg-4 col-xxl-3">
            <div id="building" class="category pb-2">
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#building">
                        <img width="100%" src="img/building.jpg" alt="category"/>
                        <p class="mt-1 mb-0">Smart Building</p>
                    </a> 
            </div>
        </div>
        <div class="col-6 col-lg-4 col-xxl-3">
            <div id="city" class="category pb-2">
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#building">
                        <img width="100%" src="img/city.jpg" alt="category"/>
                        <p class="mt-1 mb-0">Smart City</p>
                    </a> 
            </div>
        </div>
        <div class="col-6 col-lg-4 col-xxl-3">
            <div id="home" class="category pb-2">
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#home">
                        <img width="100%" src="img/home.jpg" alt="category"/>
                        <p class="mt-1 mb-0">Smart Home</p>
                    </a> 
            </div>
        </div>
        <div class="col-6 col-lg-4 col-xxl-3">
            <div id="retail" class="category pb-2">
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#retail">
                        <img width="100%" src="img/retail.jpg" alt="category"/>
                        <p class="mt-1 mb-0">Retail</p>
                    </a> 
            </div>
        </div>
    </div>
</div>

<br>
<br>
<h3 id="demo">Demo</h3>
<div class="container">
    <div class="row">
        <div class="col-12">
            With the demo binary, users can try the AI Applications without having AI SDK environment.<br>
            Download the Demo for your Evaluation Board Kit (EVK) and see each How to Use Guide.
            <div class="row">
                <div class="col-12 col-xxl-6">
                    <h4 class="u_line">
                        For RZ/V2L EVK
                    </h4>
                    <div class="row">
                        <div class="col-5">
                            <p class="ms-3">
                                <a class="btn btn-primary download-button" href="https://www.renesas.com/document/sws/rzv2l-ai-applications-demo-sd-image-version-500" role="button">
                                    Download RZ/V2L AI Applications Demo
                                </a>
                            </p>
                            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link demo.md %}" role="button">
                                <span class="banner-title" style="line-height:1.0;">
                                    <span style="font-size:70%;">
                                        RZ/V2L AI Applications Demo
                                    </span><br>
                                    How to Use Guide
                                </span><br>
                                <span class="banner-line">
                                    What is RZ/V2L AI Applications Demo?<br>
                                    How can I run the Demo?<br>
                                </span>
                            </a>
                        </div>
                        <div class="col-7">
                            <ul>
                                <li>
                                    Environment:
                                    <ul>
                                        <li>
                                            AI Applications v5.00
                                        </li>
                                        <li>
                                            RZ/V2L AI SDK v5.00
                                        </li>
                                    </ul>
                                </li>
                                <li>
                                    Demo zip file size: 2.8GB
                                </li>
                            </ul>
                        </div>
                    </div>
                    <br><br>
                 </div>
                <div class="col-12 col-xxl-6">
                    <h4 class="u_line">
                        For RZ/V2H EVK
                    </h4>
                    <div class="row">
                        <div class="col-5">
                            <p class="ms-3">
                                <a class="btn btn-primary download-button" href="https://www.renesas.com/document/sws/rzv2h-ai-applications-demo-sd-image-version-500" role="button">
                                    Download RZ/V2H AI Applications Demo
                                </a>
                            </p>    
                            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link demo_v2h.md %}" role="button">
                                <span class="banner-title" style="line-height:1.0;">
                                    <span style="font-size:70%;">
                                        RZ/V2H AI Applications Demo
                                    </span><br>
                                    How to Use Guide
                                </span><br>
                                <span class="banner-line">
                                    What is RZ/V2H AI Applications Demo?<br>
                                    How can I run the Demo?<br>
                                </span>
                            </a>
                        </div>
                        <div class="col-7">
                            <ul>
                                <li>
                                    Environment:
                                    <ul>
                                        <li>
                                            AI Applications v5.00
                                        </li>
                                        <li>
                                            RZ/V2H AI SDK v5.00
                                        </li>
                                    </ul>
                                </li>
                                <li>
                                    Demo zip file size: 3.4GB
                                </li>
                            </ul>
                        </div>
                    </div>
                    <br><br>
                </div>
            </div>
        </div>
    </div>
</div>

<br>
<br>
<h3 id="video">Video</h3>
<div class="container">
    <div class="row">
        <div class="col-12">
            <h4 class="u_line" id="training-video">
                Training video
            </h4>
        </div>
        <div class="col-12">
            Tutorial videos to explain the contents of Getting Started.
            <br><br>
        </div>
    </div>
    <div class="row">
<!-- Video panel start -->
        <div class="col-12 col-md-6 col-xl-4 mb-5">
            <div class="griditem" style="list-style: none;">
                <div class="video-wrapper">
                    <iframe 
                        class="video-iframe"
                        src="https://www.youtube.com/embed/ErmISuWkkBQ" 
                        title="YouTube video player" 
                        frameborder="0" 
                        allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" 
                        allowfullscreen>
            </iframe>
                </div>
                <div class="row mt-2">
                    <div class="col-11 pe-0">
                        <b>
                            <a href="https://youtu.be/ErmISuWkkBQ">
                                RZ/V2H AI Applications Tutorial - Getting Started v3.00 (Youtube) 
                            </a>
                        </b>
                    </div>
                    <div class="col-1 ps-0">
                        <h6 class="mb-0" style="color: gray;" align="right">24:36</h6>
                    </div>
                </div>
                <div class="griditem-add">
                    <ul>
                        <li>
                            <b>Latest Tutorial Video for RZ/V2H</b>
                        </li>
                        <li>
                            For RZ/V2H Evaluation Board Kit.
                        </li>
                        <li>
                            For <b>RZ/V2H</b> AI SDK <b>v3.00</b>.
                            <h6>
                                <ul>
                <li>
                                        Only supports eSD bootloader.
                                    </li>
                                </ul>
                            </h6>
                </li>
            </ul>
        </div>
            </div>
        </div>
        <!-- Video panel end -->
        <!-- Video panel start -->
        <div class="col-12 col-md-6 col-xl-4 mb-5">
            <div class="griditem" style="list-style: none;">
                <div class="video-wrapper">
                    <iframe 
                        class="video-iframe"
                        src="https://www.youtube.com/embed/CPeE2q3TdOY" 
                        title="YouTube video player" 
                        frameborder="0" 
                        allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" 
                        allowfullscreen>
            </iframe>
                </div>
                <div class="row mt-2">
                    <div class="col-11 pe-0">
                        <b>
                            <a href="https://youtu.be/CPeE2q3TdOY">
                                RZ/V2L AI Applications Tutorial - Getting Started v2.10 (Youtube) 
                            </a>
                        </b>
                    </div>
                    <div class="col-1 ps-0">
                        <h6 class="mb-0" style="color: gray;" align="right">25:43</h6>
                    </div>
                </div>
                <div class="griditem-add">
                    <ul>
                        <li>
                            <b>Latest Tutorial Video for RZ/V2L</b>
                        </li>
                        <li>
                            For RZ/V2L Evaluation Board Kit.
                        </li>
                        <li>
                            For <b>RZ/V2L</b> AI SDK <b>v2.10</b>.
                            <h6>
                                <ul>
                                    <li>
                                        Supports both eSD and eMMC bootloader.
                                    </li>
                <li>
                    In this video, eSD bootloader is used.
                </li>
            </ul>
                            </h6>
                        </li>
                    </ul>
                </div>
            </div>
        </div>
        <!-- Video panel end -->
        <!-- Video panel start -->
        <div class="col-12 col-md-6 col-xl-4 mb-5">
            <div class="griditem" style="list-style: none;">
                <div class="video-wrapper">
                    <iframe 
                        class="video-iframe"
                        src="https://www.youtube.com/embed/wFbTomH8oPs" 
                        title="YouTube video player" 
                        frameborder="0" 
                        allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" 
                        allowfullscreen>
            </iframe>
                </div>
                <div class="row mt-2">
                    <div class="col-11 pe-0">
                        <b>
                            <a href="https://youtu.be/wFbTomH8oPs">
                                RZ/V2L AI Applications Tutorial - Getting Started v1.00 (Youtube)
                            </a>
                        </b>
                    </div>
                    <div class="col-1 ps-0">
                        <h6 class="mb-0" style="color: gray;" align="right">33:56</h6>
                    </div>
                </div>
                <div class="griditem-add">
                    <ul>
                <li>
                            For RZ/V2L Evaluation Board Kit.
                        </li>
                        <li>
                            For <b>RZ/V2L</b> AI SDK <b>v1.10</b>.
                            <h6>
                                <ul>
                                    <li>
                                        Only supports eMMC bootloader.
                                    </li>
                                </ul>
                            </h6>
                        </li>
                    </ul>
                </div>
            </div>
        </div>
        <!-- Video panel end -->
    </div>
    <br>
    <div class="row">
        <div class="col-12">
            <h4 class="u_line" id="app-video">
                AI Applications video
            </h4>
        </div>
        <div class="col-12">
            Video to show sample use-cases of <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}">RZ/V AI Applications</a>.
                    <br><br>
        </div>
    </div>
    <div class="row">
        <!-- Video panel start -->
        <div class="col-12 col-md-6 col-xl-4 mb-5" id="agriculture1">
            <div class="griditem" style="list-style: none;">
                <div class="video-wrapper">
                    <iframe 
                        class="video-iframe"
                        src="https://www.youtube.com/embed/CjX_DyCVtM8" 
                        title="YouTube video player" 
                        frameborder="0" 
                        allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" 
                        allowfullscreen>
                    </iframe>
                </div>
                <div class="row mt-2">
                    <div class="col-11 pe-0">
                        <b>
                            <a href="https://youtu.be/CjX_DyCVtM8">
                                    Agriculture :<br>
                                    Defense Wild Animals for Crop (YouTube)
                            </a>
                        </b>
                    </div>
                    <div class="col-1 ps-0">
                        <h6 class="mb-0" style="color: gray;" align="right">1:31</h6>
                    </div>
                </div>
                <div class="griditem-add">
                    <ul class="mb-2">
                        <li>
                            Environment
                            <h6 class="mb-1">
                                <ul>
                                    <li>
                                        RZ/V2H Evaluation Board Kit
                                    </li>
                                    <li>
                                        AI Applications v4.00
                                    </li>
                                    <li>
                                        Input: USB Camera (640x480)
                                    </li>
                                    <li>
                                        Output: HDMI (1920x1080)
                                    </li>
                                </ul>
                            </h6>
                        </li>
                    </ul>
                    <p align="right" class="m-0">
                        <a class="devicelinkbutton" 
                            href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#agriculture1" 
                            style="color:white">
                            More Details >
                        </a>
                    </p>
                </div>
            </div>
        </div>
        <!-- Video panel end -->
        <!-- Video panel start -->
        <div class="col-12 col-md-6 col-xl-4 mb-5" id="building2">
            <div class="griditem" style="list-style: none;">
                <div class="video-wrapper">
                    <iframe 
                        class="video-iframe"
                        src="https://www.youtube.com/embed/XELOK3NJq68" 
                        title="YouTube video player" 
                        frameborder="0" 
                        allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" 
                        allowfullscreen>
                    </iframe>
                </div>
                <div class="row mt-2">
                    <div class="col-11 pe-0">
                        <b>
                            <a href="https://youtu.be/XELOK3NJq68">
                                Smart Building :<br>
                                Conference Room Usage Monitor (YouTube)
                            </a>
                        </b>
                    </div>
                    <div class="col-1 ps-0">
                        <h6 class="mb-0" style="color: gray;" align="right">1:59</h6>
                    </div>
                </div>
                <div class="griditem-add">
                    <ul class="mb-2">
                        <li>
                            Environment
                            <h6 class="mb-1">
                                <ul>
                                    <li>
                                        RZ/V2H Evaluation Board Kit
                                    </li>
                                    <li>
                                        AI Applications v4.00
                                    </li>
                                    <li>
                                        Input: USB Camera (640x480)
                                    </li>
                                    <li>
                                        Output: HDMI (1920x1080)
                                    </li>
                                </ul>
                            </h6>
                        </li>
                    </ul>
                    <p align="right" class="m-0">
                        <a class="devicelinkbutton" 
                            href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#building2" 
                            style="color:white">
                            More Details >
                        </a>
                    </p>
                </div>
            </div>
        </div>
        <!-- Video panel end -->
        <!-- Video panel start -->
        <div class="col-12 col-md-6 col-xl-4 mb-5" id="industrial2">
            <div class="griditem" style="list-style: none;">
                <div class="video-wrapper">
                    <iframe 
                        class="video-iframe"
                        src="https://www.youtube.com/embed/neH2vfbJQP8" 
                        title="YouTube video player" 
                        frameborder="0" 
                        allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" 
                        allowfullscreen>
                    </iframe>
                </div>
                <div class="row mt-2">
                    <div class="col-11 pe-0">
                        <b>
                            <a href="https://youtu.be/neH2vfbJQP8">
                                Industrial :<br>
                                Access Control (YouTube)
                            </a>
                        </b>
                    </div>
                    <div class="col-1 ps-0">
                        <h6 class="mb-0" style="color: gray;" align="right">1:42</h6>
                    </div>
                </div>
                <div class="griditem-add">
                    <ul class="mb-2">
                        <li>
                            Environment
                            <h6 class="mb-1">
                                <ul>
                                    <li>
                                        RZ/V2H Evaluation Board Kit
                                    </li>
                                    <li>
                                        AI Applications v4.00
                                    </li>
                                    <li>
                                        Input: USB Camera (640x480)
                                    </li>
                                    <li>
                                        Output: HDMI (1920x1080)
                </li>
            </ul>
                            </h6>
                        </li>
                    </ul>
                    <p align="right" class="m-0">
                        <a class="devicelinkbutton" 
                            href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#industrial2" 
                            style="color:white">
                            More Details >
                        </a>
                    </p>
        </div>
    </div>
        </div>
        <!-- Video panel end -->
    </div>
</div>
<br>
<br>
<br>
<br>
<!-- <h3 id="blog">Blogs</h3> -->
<!-- <div class="container">
    <div class="row">
        <div class="col-12"> -->
            <!-- <div>
                <h5 class="mb-2">
                    <a href="https://www.renesas.com/blogs/check-out-latest-features-ai-applications-v210">Check Out the Latest Features in AI Applications v2.10!</a>
                </h5>
                <div class="container">
                    <div class="row">
                        <div class="col-8">
                            Introducing the lineup of RZ/V AI applications, offered with AI Applications v2.10.
                        </div>
                        <div class="col-4" align="right">
                            Published: <b>Dec. 22, 2023.</b>
                        </div>
                    </div>
                </div>
            </div> -->
            <!-- <br>
            <hr style="border-top: 1px solid grey;">
            <div>
                <h5 class="mb-2">
                    <a href="https://www.renesas.com/blogs/check-out-new-features-ai-applications-v200">Check Out the New Features in AI Applications v2.00!</a>
                </h5>
                <div class="container">
                    <div class="row">
                        <div class="col-8">
                            To facilitate the tedious task of designing AI solutions from scratch, Renesas proposes RZ/V MPU AI Apps, AI applications that can be easily implemented without AI training.
                        </div>
                        <div class="col-4" align="right">
                            Published: <b>Sep. 22, 2023.</b>
                        </div>
                    </div>
                </div>
            </div> -->
            <!-- <br>
            <hr style="border-top: 1px solid grey;">
            <div>
                <h5 class="mb-2">
                    <a href="https://www.renesas.com/blogs/lets-find-ai-apps-you-want-introducing-renesas-ai-apps-available-free-charge">Let's find the AI Apps You Want, Introducing Renesas AI Apps Available Free of Charge</a>
                </h5>
                <div class="container">
                    <div class="row">
                        <div class="col-8">
                            Introduction to RZ/V AI applications that can be easily implemented without AI training
                        </div>
                        <div class="col-4" align="right">
                            Published: <b>Jun. 12, 2023.</b>
                        </div>
                    </div>
                </div>
            </div>
            <br>
            <hr style="border-top: 1px solid grey;"> -->
        <!-- </div>
    </div>
</div>
<br>
<br>
<br>
<br> -->

<h3 id="reference">Reference</h3>
<div class="container">
    <div class="row">
        <div class="col-12">
            Followings are references of related software/documentation.<br><br>
            <table class="gstable ms-4">
                <tr>
                    <th>Product</th>
                    <th>Link</th>
                    <th>Details</th>
                </tr>
                <tr>
                    <td rowspan="1">Common</td>
                    <td>
                        <a href="https://github.com/renesas-rz/rzv_drp-ai_tvm" target="_blank" rel="noopener noreferrer">
                            DRP-AI TVM
                        </a>
                    </td>
                    <td>
                        <small>
                        Machine Learning Compiler plugin for Apache TVM with AI accelerator DRP-AI.<br>
                        <b>Automatically installed in AI SDK.</b>
                        </small>
                    </td>
                </tr>
                <!-- RZ/V2L Reference -->
                <tr>
                    <td rowspan="3">RZ/V2L</td>
                    <td>
                        <a href="https://www.renesas.com/products/microcontrollers-microprocessors/rz-arm-based-high-end-32-64-bit-mpus/drp-ai-translator" target="_blank" rel="noopener noreferrer">
                            DRP-AI Translator
                        </a>
                    </td>
                    <td>
                        <small>
                        AI model conversion tool for DRP-AI embedded in RZ/V2L.<br>
                        Included in RZ/V2L AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/software-tool/rzv-verified-linux-package" target="_blank" rel="noopener noreferrer">
                            RZ/V Verified Linux Package
                        </a>
                    </td>
                    <td>
                        <small>
                        Linux Packages for MPUs of the RZ/V2L.<br>
                        Used in RZ/V2L AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/products/microcontrollers-microprocessors/rz-arm-based-high-end-32-64-bit-mpus/rzv2l-drp-ai-support-package" target="_blank" rel="noopener noreferrer">
                            RZ/V2L DRP-AI Support Package
                        </a>
                    </td>
                    <td>
                        <small>
                        Software to use DRP-AI with RZ/V Vefiried Linux Package, which includes DRP-AI Driver.<br>
                        Used in RZ/V2L AI SDK.
                        </small>
                    </td>
                </tr>
                <!-- RZ/V2H Reference -->
                <tr>
                    <td rowspan="9">RZ/V2H</td>
                    <td>
                            <a href="https://www.renesas.com/software-tool/drp-ai-translator-i8" target="_blank" rel="noopener noreferrer">
                                DRP-AI Translator i8
                            </a>
                    </td>
                    <td>
                        <small>
                        AI model conversion tool for DRP-AI embedded in RZ/V2H.<br>
                        Included in RZ/V2H AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/document/mas/rzv2h-bsp-manual-set-rtk0ef0045z94001azj-v100zip" target="_blank" rel="noopener noreferrer">
                            RZ/V2H BSP Manual Set
                        </a>
                    </td>
                    <td>
                        <small>
                        Document for Linux Drivers used in RZ/V2H AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/document/mas/rzv2h-group-and-rzv2n-group-linux-interface-specification-gstreamer-users-manual-software" target="_blank" rel="noopener noreferrer">
                            RZ/V2H Video Codec Library  User's Manual
                        </a>
                    </td>
                    <td>
                        <small>
                        RZ/V2H Group Linux Interface Specification GStreamer User's Manual: Software.<br>
                        Document for GStreamer in Video Codec Library used in RZ/V2H AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://github.com/renesas-rz/rzv2h_opencv_accelerator" target="_blank" rel="noopener noreferrer">
                            RZ/V2H OpenCV Accelerator 
                        </a>
                    </td>
                    <td>
                        <small>
                        OpenCV Accelerator which performs OpenCV function in high performance by using DRP.<br>
                        Used in RZ/V2H AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://github.com/renesas-rz/rzv2h_drp-ai_driver" target="_blank" rel="noopener noreferrer">
                            RZ/V2H DRP-AI Driver
                        </a>
                    </td>
                    <td>
                        <small>
                        Linux driver to use DRP-AI on RZ/V2H.<br>
                        Used in RZ/V2H AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/us/en/software-tool/rzv2h-ros2-package" target="_blank" rel="noopener noreferrer">
                            RZ/V2H ROS2 Package 
                        </a>
                    </td>
                    <td>
                        <small>
                        Package that can be applied to RZ/V2H AI SDK to use ROS2.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/software-tool/rzv-group-multi-os-package" target="_blank" rel="noopener noreferrer">
                            RZ/V Multi-OS Package 
                        </a>
                    </td>
                    <td>
                        <small>
                        Package consisting of RZ/V Flexible Software Package (FSP) as software package for Renesas MCU with Arm&reg; Cortex-M, R Core and OpenAMP as standardization API of framework for interprocessor communication for developing multi OS solution.<br>
                        This package can be applied to RZ/V2H AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/software-tool/rz-mpu-security-package" target="_blank" rel="noopener noreferrer">
                            RZ MPU Security Package 
                        </a>
                    </td>
                    <td>
                        <small>
                        This package is to add Security functions (Secure Boot, Trusted Execution Environment, Hardware Cryptographic IP, Secure Debug, Security Configurator) to RZ MPU.<br>
                        This package can be applied to RZ/V2H AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/software-tool/rzv2h-isp-support-package" target="_blank" rel="noopener noreferrer">
                            RZ/V2H ISP Support Package 
                        </a>
                    </td>
                    <td>
                        <small>
                        Package that can be applied to RZ/V2H AI SDK to use Built-in ISP.
                        </small>
                    </td>
                </tr>
                <!-- RZ/V2N Reference -->
                <tr>
                    <td rowspan="8">RZ/V2N</td>
                    <td>
                            <a href="https://www.renesas.com/software-tool/drp-ai-translator-i8" target="_blank" rel="noopener noreferrer">
                                DRP-AI Translator i8
                            </a>
                    </td>
                    <td>
                        <small>
                        AI model conversion tool for DRP-AI embedded in RZ/V2N.<br>
                        Included in RZ/V2N AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/document/swo/rzv2h-and-rzv2n-bsp-manual-set-rtk0ef0045z94001azj-v102zip" target="_blank" rel="noopener noreferrer">
                            RZ/V2N BSP Manual Set
                        </a>
                    </td>
                    <td>
                        <small>
                        Document for Linux Drivers used in RZ/V2N AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/document/mas/rzv2h-group-and-rzv2n-group-linux-interface-specification-gstreamer-users-manual-software" target="_blank" rel="noopener noreferrer">
                            RZ/V2N Video Codec Library User's Manual
                        </a>
                    </td>
                    <td>
                        <small>
                        RZ/V2N Group Linux Interface Specification GStreamer User's Manual: Software.<br>
                        Document for GStreamer in Video Codec Library used in RZ/V2N AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://github.com/renesas-rz/rzv2n_opencv_accelerator" target="_blank" rel="noopener noreferrer">
                            RZ/V2N OpenCV Accelerator 
                        </a>
                    </td>
                    <td>
                        <small>
                        OpenCV Accelerator which performs OpenCV function in high performance by using DRP.<br>
                        Used in RZ/V2N AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://github.com/renesas-rz/rzv2n_drp-ai_driver" target="_blank" rel="noopener noreferrer">
                            RZ/V2N DRP-AI Driver
                        </a>
                    </td>
                    <td>
                        <small>
                        Linux driver to use DRP-AI on RZ/V2N.<br>
                        Used in RZ/V2N AI SDK.
                        </small>
                    </td>
                </tr>
                <!-- 6月release <tr>
                    <td>
                        <a href="https://www.renesas.com/us/en/software-tool/rzv2n-ros2-package" target="_blank" rel="noopener noreferrer">
                            RZ/V2N ROS2 Package 
                        </a>
                    </td>
                    <td>
                        <small>
                        Package that can be applied to RZ/V2N AI SDK to use ROS2.
                        </small>
                    </td>
                </tr> -->
                <tr>
                    <td>
                        <a href="https://www.renesas.com/software-tool/rzv-group-multi-os-package" target="_blank" rel="noopener noreferrer">
                            RZ/V Multi-OS Package 
                        </a>
                    </td>
                    <td>
                        <small>
                        Package consisting of RZ/V Flexible Software Package (FSP) as software package for Renesas MCU with Arm&reg; Cortex-M, R Core and OpenAMP as standardization API of framework for interprocessor communication for developing multi OS solution.<br>
                        This package can be applied to RZ/V2N AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/software-tool/rz-mpu-security-package" target="_blank" rel="noopener noreferrer">
                            RZ MPU Security Package 
                        </a>
                    </td>
                    <td>
                        <small>
                        This package is to add Security functions (Secure Boot, Trusted Execution Environment, Hardware Cryptographic IP, Secure Debug, Security Configurator) to RZ MPU.<br>
                        This package can be applied to RZ/V2N AI SDK.
                        </small>
                    </td>
                </tr>
                <tr>
                    <td>
                        <a href="https://www.renesas.com/software-tool/rzv2n-isp-support-package" target="_blank" rel="noopener noreferrer">
                            RZ/V2N ISP Support Package 
                        </a>
                    </td>
                    <td>
                        <small>
                        Package that can be applied to RZ/V2N AI SDK to use Built-in ISP.
                        </small>
                    </td>
                </tr>
            </table>
        </div>
    </div>
</div>
<br>
<br>
<div class="container">
    <div class="row">
        <div class="col-12" align="right">
            <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}#page-top" role="button">
                Back to Top >
            </a>
        </div>
    </div>
</div>
