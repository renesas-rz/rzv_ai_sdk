---
layout: default
---
<script src="https://code.jquery.com/jquery.min.js"></script>
<!-- Title -->
<div class="container">
    <div class="row">
        <div class="top col-12">
            RZ/V AI Software Overview
        </div>
    </div>
</div>

<br>
<br>

<!-- Contents -->
<div class="container" id="overview">
    <div class="row">
        <div class="col-12">
            <h3 id="index">
                Index
            </h3>
            <ul>
                <li><a href="#intro">Introduction</a></li>
                <li><a href="#user-journey">User Journey</a></li>
                <li><a href="#wheretostart">Where to Start Your Development</a></li>
                <li>
                    <a href="#deliverables">Deliverables</a>
                    <ul>
                        <li><a href="#board">Board</a></li>
                        <li><a href="#software">Software/Tool</a></li>
                    </ul>
                </li>
                <li><a href="#reference">Reference</a></li>
            </ul>
        </div>
        <div class="col-12">
            <h3 id="intro">
                Introduction
            </h3>
            Among other devices provided by Renesas Electronics, RZ/V series is specialized to AI by embedding the Renesas DRP-AI accelerator delivering high performance at low power consumption.
            <br>
            AI application development requires a lot of work, starting with preparing an AI development environment.
            <br>
            Furthermore, development tasks often have to be repeated many times to achieve the target accuracy.
            <br>
            When AI model is ready to be used in actual user applications, the time and money spent here has been a major hurdle.
            <br>
            <br>
            Renesas provides <b>RZ/V AI Applications</b>, which can significantly shorten this AI development phase.
            <br>
            In addition, since AI Applications are developed using open source, they can be used not only for evaluation purposes but also for your mass production development.
            <br>
            <div class="col-12 text-center">
                <br>
                <a href="img/AI_dev_flow.svg" data-lightbox="group">
                    <img src="img/AI_dev_flow.svg" alt="">
                </a>
                <br>
            </div>
            <br>
            To expand AI development, Renesas also provide other development environments/tools, i.e., RZ/V AI Transfer Learning Tool to re-train the AI models used in AI Applications, etc..
            <br>
            This page explains about the summary of those AI software for RZ/V series.
            <br>
            <br>
        </div>
    </div>
</div>
<div class="container">
    <div class="row">
        <div class="col-12">
            <h3 id="user-journey">
                User Journey
            </h3>
            <h4 id="user-journey-overview" class="u_line">
                Overview
            </h4>
            Following diagram shows the user journey overview for RZ/V AI Software user.<br>
        </div>
        <div class="col-12 text-center mb-4">
            <br>
            <a href="img/user-journey.svg" data-lightbox="group">
                <img src="img/user-journey.svg" alt="">
            </a>
            <br>
        </div>
        <div class="col-12">
            <h4 class="u_line">
                AI Software Development Flow
            </h4>
            For each phase in <a href="#user-journey-overview"><b>user journey overview diagram</b></a>, development flow and related software are shown below.<br>
            For more details on each software, please check its documentation listed in <a href="#software"><b>Software/Tool Deliverables List</b></a>.<br>
        </div>
        <div class="col-12 text-center mb-4">
            <br>
            <a href="img/ai_sw_dev_flow.svg" data-lightbox="group">
                <img src="img/ai_sw_dev_flow.svg" alt="">
            </a>
            <br>
        </div>
    </div>
</div>
<br>
<br>

<br>
<br>
<div class="container">
    <div class="row">
        <div class="col-12">
            <h3 id="wheretostart">
                Where to Start Your Development
            </h3>
            Following diagram guides you to which software to start the development.<br>
            Click the button of your selected software and follow the instructions.<br>
        </div>
        <div class="col-12 text-center p-0">
            <br>
            <a href="img/where_to_start.svg" data-lightbox="group">
                <img src="img/where_to_start.svg" alt="">
            </a>
            <br>
            <br>
        </div>
        <div class="col-1 text-center p-0">
            <div class="btn btn-secondary square-button square-button-toggle-down btn_sw btn_partner" data-id="partner">
                  Click
            </div>
        </div>
        <div class="col-2 text-center p-0">
            <div class="btn btn-secondary square-button square-button-toggle-down btn_sw btn_ai btn_tvm" data-id="tvm">
                  Click
            </div>
        </div>
        <div class="col-1 text-center p-0">
            <div class="btn btn-secondary square-button square-button-toggle-down btn_sw btn_ai btn_tlt" data-id="tlt">
                  Click
            </div>
        </div>
        <div class="col-2 text-center p-0">
            <div class="btn btn-secondary square-button square-button-toggle-down btn_sw btn_ai btn_ai-apps" data-id="ai-apps">
                  Click
            </div>
        </div>
        <div class="col-2 text-center p-0">
            <div class="btn btn-secondary square-button square-button-toggle-down btn_sw btn_ai btn_ai-navi" data-id="ai-navi">
                  Click
            </div>
        </div>
        <div class="col-2 text-center p-0">
            <div class="btn btn-secondary square-button square-button-toggle-down btn_sw btn_linux btn_ai-sdk-src" data-id="ai-sdk-src">
                  Click
            </div>
        </div>
        <div class="col-2 text-center p-0">
            <div class="btn btn-secondary square-button square-button-toggle-down btn_sw btn_trial btn_ai-apps_demo" data-id="ai-apps-demo">
                  Click
            </div>
        </div>
        <br>
        <br>
    </div>
    <!-- Guide Box: hidden as default -->
    <div class="row contents-sw contents-sw-other partner" >
        <div class="col-12 contents-sw-title contents-sw-title-other">
            AI Partner
        </div>
        <div class="col-12">
            RZ/V AI Applications are free of charge and open source software, which can be used not only for evaluation purposes but also for your mass production development.<br>
            However, they only provide fixed AI models/dataset.
            <br>
            You can change the AI models/dataset by using our other software, i.e., RZ/V AI Transfer Learning Tool and DRP-AI TVM.
            <br>
            <br>
            If you do not have your own AI model, or prefer to use exisiting AI models created by reliable developers, you are recommended to ask our partners.<br>
            Our partners include as follows.
            <ul>
                <li>AI application developers</li>
                <li>AI model experts (performance/accuracy optimization, etc.)</li>
                <li>System integrators</li>
            </ul>
            Community page shows our partner applications that you can actually run on the target board.<br>
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link community.md %}" role="button">
                <span class="banner-title" style="line-height:1.0;">
                    Community page
                </span><br>
                <span class="banner-line">
                    List of partner applications and other sample applications.<br>
                </span>
            </a>
            <br>
            <br>
            We also have the list of our partners in <a href="https://www.renesas.com/products/microcontrollers-microprocessors/rz-mpus/rz-partner-solutions?partners-mcu-filter=rz-v">Renesas RZ Partner Ecosystem Solutions</a> page.
            <br>
            <br>
            To make an enquiry regarding AI partner, please use <b>"Support Tickets"</b> > <b>"Submit a Ticket"</b> from following page.<br>
            <a class="btn btn-primary download-button" href="https://www.renesas.com/support" role="button">
                Renesas Technical Support
            </a>
        </div>
    </div>
    <div class="row contents-sw contents-sw-ai tvm" >
        <div class="col-12 contents-sw-title contents-sw-title-ai">
            DRP-AI TVM
        </div>
        <div class="col-12">
            DRP-AI TVM is a Machine Learning Compiler plugin for Apache TVM with AI accelerator DRP-AI, which is a tool to compile your own AI models (including BYOM) to get the executable format on RZ/V series.
            <br>
            <br>
            RZ/V AI Applications (Apps) provide a set of pre-compiled AI models by validated DRP-AI TVM version and the application source code.
            <br>
            In following cases, you need to compile them with DRP-AI TVM.
            <ul>
                <li>
                    To change the AI models of RZ/V AI Apps.
                </li>
                <li>
                    To use completely different models, such as BYOM or OSS, 
                </li>
            </ul>
            DRP-AI TVM is automatically installed in RZ/V AI SDK and users are able to use it on its own.
            <br>
            To see how to use DRP-AI TVM, please refer to the <b>DRP-AI TVM Web</b>.
            <br>
            <br>
            <a class="btn btn-primary download-button" 
                href="https://renesas-rz.github.io/rzv_drp-ai_tvm/" 
                role="button">
                DRP-AI TVM Web
            </a>
            <br>
            <br>
        </div>
        <div class="col-12">
            <h5 class="u_line mb-1">
                Note
            </h5>
        </div>
        <div class="col-12 col-xxl-8 mb-3">
            <div class="ms-3">
                RZ/V AI Apps and RZ/V AI SDK usually use the validated version of DRP-AI TVM, which means that RZ/V AI Apps may not be compatible with the latest version of DRP-AI TVM.<br>
                The version installed in AI SDK can be checked in the following page.
                <br>
                <a class="btn btn-secondary square-button square-button-link-small 
                    mt-2 ms-2 mb-2" 
                    href="{{ site.url }}{{ site.baseurl }}{% link ai-sdk.md %}">
                    RZ/V AI SDK Overview
                </a>
                <br>
                <br>
                To use the <b>latest DRP-AI TVM</b>, please refer to the Getting Started in <b>DRP-AI TVM Web</b> to construct the environment with RZ/V AI SDK and DRP-AI Translator.
            </div>
        </div>
        <div class="col-12 col-xxl-4">
            <a href="img/to_latest_tvm.png" 
                data-lightbox="group" >
                <img src="img/to_latest_tvm.png" 
                    alt="To use latest DRP-AI TVM"
                    width="100%" 
                    style="max-width:500px;">
            </a>
        </div>
    </div>
    <div class="row contents-sw contents-sw-ai tlt" >
        <div class="col-12 contents-sw-title contents-sw-title-ai">
            RZ/V AI Transfer Learning Tool (TLT)
        </div>
        <div class="col-12">
            RZ/V AI Applications (Apps) provide a set of pre-compiled AI models, which are already trained with specific dataset selected for each use-case.
            <br>
            In following cases, you need to re-train the AI model.
            <ul>
                <li>
                    To change the AI target classes.
                </li>
                <li>
                    To improve the accuracy of AI models. 
                </li>
            </ul>
            <b>RZ/V AI TLT</b> is a GUI Tool to re-train the AI models used in RZ/V AI Apps with different datasets.
            <br>
            It requires a <b>Linux PC with GPU</b> that can <b>display the desktop screen</b>.
            <br>
            <br>
            To use RZ/V AI TLT, please refer to following guide.
            <br>
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_retrain.md %}" role="button">
                <span class="banner-title" style="line-height:1.0;">
                    <span style="font-size:70%;">
                        RZ/V AI Transfer Learning Tool
                    </span><br>
                    How to Re-train AI model
                </span><br>
                <span class="banner-line">
                    How to use RZ/V AI TLT?<br>
                </span>
            </a>
            <br>
            <br>
            Please note that it may not support the latest RZ/V AI Apps.<br>
            For more details, please check the guide above.
        </div>
    </div>
    <div class="row contents-sw contents-sw-ai ai-apps">
        <div class="col-12 contents-sw-title contents-sw-title-ai">
            RZ/V AI Applications and RZ/V AI SDK
        </div>
        <div class="col-12">
            <b>RZ/V AI Applications (Apps)</b> provides following set of files that can be used AS IS for each use-case.
            <br>
            <ul class="mb-1">
                <li>
                    Pre-trained AI model objects
                </li>
                <li>
                    Pre-build application binary
                </li>
                <li>
                    Application source code
                </li>
            </ul>
            It is provided on GitHub with free of charge and open-source software licenses.<br>
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}" role="button">
                <span class="banner-title" style="line-height:1.0;">
                    RZ/V AI Applications
                </span><br>
                <span class="banner-line">
                    Check the list of RZ/V AI Applications.
                </span>
            </a>
            <br>
            <br>
            <b>RZ/V AI Software Development Kit (AI SDK)</b> is an AI application development environment for specific Evaluation Bord Kit of RZ/V series.
            <br> 
            It includes the pre-build binary of bootloader, Linux Kernel and cross compiler, which contain a complete set of libraries to run RZ/V AI Apps.
            <br>
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link ai-sdk.md %}" role="button">
                <span class="banner-title" style="line-height:1.0;">
                    RZ/V AI SDK Overview
                </span><br>
                <span class="banner-line">
                    Check the specification of RZ/V AI SDK.
                </span>
            </a>
            <br>
            <br>
            With RZ/V AI Apps and RZ/V AI SDK, users can start their AI development <b>quickly</b> and <b>easily</b>.
            <br>
            First, please follow the <b>Getting Started Guide</b> to run the RZ/V AI Apps on the board with RZ/V AI SDK.
            <br>
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" role="button">
                <span class="banner-title" style="line-height:1.0;">
                    Getting Started
                </span><br>
                <span class="banner-line">
                    How to startup RZ/V board?<br>
                    How to run RZ/V AI Applications?<br>
                </span>
            </a>
            <br>
            <br>
            After the Getting Started, please select and try <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}"><b>RZ/V AI Apps</b></a> to expand your AI development.
            <br>
        </div>
    </div>
    <div class="row contents-sw contents-sw-ai ai-navi">
        <div class="col-12 contents-sw-title contents-sw-title-ai">
            AI Navigator (e<sup>2</sup> studio plugin)
        </div>
        <div class="container mb-2">
            <div class="row">
                <div class="col-12 col-xxl-7">
                    AI Navigator is a set of plugins for Renesas IDE e<sup>2</sup> studio for RZ/V AI.
                    <br>
                    It allows users to run following software on IDE.
                    <br>
                    <ul class="mb-1">
                        <li>
                            RZ/V AI Applications (Apps)
                        </li>
                        <li>
                            RZ/V AI SDK
                        </li>
                        <li>
                            RZ/V AI Transfer Learning Tool (TLT)
                        </li>
                        <li>
                            DRP-AI TVM
                        </li>
                    </ul>
                </div>
                <div class="col-12 col-xxl-5 text-center">
                    <a href="https://www.renesas.com/software-tool/ai-navigator-ide-ai-applications">
                        AI Navigator: IDE for AI Applications
                    </a>
                    <br>
                    <a href="https://www.renesas.com/software-tool/ai-navigator-ide-ai-applications">
                        <img 
                            src="https://www.renesas.com/sites/default/files/media/images/1_navigate_environment.png" 
                            width="100%" 
                            style="max-width:700px;" 
                            alt="AI Navigator: IDE for AI Applications" />
                    </a>
                </div>
            </div>
        </div>
        <div class="col-12">
            To use AI Navigator, users are required to install <b>Renesas e<sup>2</sup> studio for Linux</b>.
            <br>
            Details are explained in the following page.
            <br>
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link ainavi_quick_start_guide.md %}" role="button">
                <span class="banner-title" style="line-height:1.0;">
                    AI Navigator Quick Start Guide
                </span><br>
                <span class="banner-line">
                    How to develop and run RZ/V AI Applications on e<sup>2</sup> studio?<br>
                </span>
            </a>
            <br>
            <br>
            Please note that it may not support the latest RZ/V AI Apps.<br>
            For more details, please check the Quick Start Guide above.
        </div>
    </div>
    <div class="row contents-sw contents-sw-linux ai-sdk-src" >
        <div class="col-12 contents-sw-title contents-sw-title-linux">
            RZ/V AI SDK Source Code
        </div>
        <div class="col-12">
            RZ/V AI SDK is an AI application development environment which is built for specific Evaluation Bord Kit of RZ/V series.
            <br> 
            If you would like to change RZ/V AI SDK, you need to customize and build the AI SDK, which is based on Yocto Project (Linux OS Distribution).
            <br>
            Changing AI SDK includes following examples.
            <ul>
                <li>
                    To change the memory map of the board.
                </li>
                <li>
                    To develop your own board with RZ/V series. 
                </li>
                <li>
                    To add extra camera drivers, graphic libraries, other OSS libraries, etc..
                </li>
            </ul>
            The Linux source code is provided as <b>RZ/V AI SDK Source Code</b>.
            <br>
            <br>
            The instructions to build the RZ/V AI SDK Source Code are provided in each <b>How to Build AI SDK page</b>.
            <br> 
            Please refer to following guides based on your target device.
            <br>
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk.md %}" role="button">
                <span class="banner-title" style="line-height:1.0;">
                    <span style="font-size:70%;">
                        RZ/V2L AI SDK Source Code
                    </span><br>
                    How to Build RZ/V2L AI SDK
                </span>
            </a>
            <br> 
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}" role="button">
                <span class="banner-title" style="line-height:1.0;">
                    <span style="font-size:70%;">
                        RZ/V2H AI SDK Source Code
                    </span><br>
                    How to Build RZ/V2H AI SDK
                </span>
            </a>
            <br> 
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}" role="button">
                <span class="banner-title" style="line-height:1.0;">
                    <span style="font-size:70%;">
                        RZ/V2N AI SDK Source Code
                    </span><br>
                    How to Build RZ/V2N AI SDK
                </span>
            </a>
        </div>
    </div>
    <div class="row contents-sw contents-sw-trial ai-apps-demo">
        <div class="col-12 contents-sw-title contents-sw-title-trial">
            RZ/V AI Applications Demo
        </div>
        <div class="container">
            <div class="row">
                <div class="col-7 col-xxl-12 mb-3">
                    RZ/V AI Applications Demo is a microSD card image that contains the RZ/V AI Applications.
                    <br>
                    Users can try the RZ/V AI Applications without having RZ/V AI SDK environment.
                </div>
                <div class="col-5 col-xxl-12 mb-3">
                    <img src="img/demo_gui.png"
                        style="max-width: 600px; "
                        width="100%" />
                </div>
                <div class="col-12">
                    To use RZ/V AI Applications Demo, please refer to following guides based on your target board.
                    <br>
                    <a class="btn btn-secondary square-button ms-3 mt-1" 
                        style="text-align:left;" 
                        href="{{ site.url }}{{ site.baseurl }}{% link demo.md %}" 
                        role="button">
                        <span class="banner-title" style="line-height:1.0;">
                            <span style="font-size:70%;">
                                RZ/V2L AI Applications Demo
                            </span><br>
                            <span style="font-size:90%;">
                                How to Use Guide
                            </span><br>
                        </span>
                    </a>
                    <br>
                    <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link demo_v2h.md %}" role="button">
                        <span class="banner-title" style="line-height:1.0;">
                            <span style="font-size:70%;">
                                RZ/V2H AI Applications Demo
                            </span><br>
                            <span style="font-size:90%;">
                                How to Use Guide
                            </span><br>
                        </span>
                    </a>
                    <br>
                    <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link demo_v2n.md %}" role="button">
                        <span class="banner-title" style="line-height:1.0;">
                            <span style="font-size:70%;">
                                RZ/V2N AI Applications Demo
                            </span><br>
                            <span style="font-size:90%;">
                                How to Use Guide
                            </span><br>
                        </span>
                    </a>
                </div>
            </div>
        </div>
    </div>
</div>
<br>
<br>
<div class="container">
    <div class="row">
        <div class="col-12">
            <h3 id="deliverables">
                Deliverables
            </h3>
            <h4 id="board" class="u_line">
                Board
            </h4>
            Following evaluation boards are supported.
            <br>
            <br>
            <table class="gstable">
                <tr>
                    <th>Board</th>
                    <th>Details</th>
                    <th>Kit</th>
                    <th>Link</th>
                </tr>
                <tr>
                    <td>
                        RZ/V2L Evaluation Board Kit (EVK)
                    </td>
                    <td>
                        Evaluation Board Kit for RZ/V2L.
                        <br>
                        Includes following items.
                        <ul>
                            <li>
                                MIPI Camera Module(Google Coral Camera)
                                <h6 class="mb-1">
                                    <ul>
                                        <li>
                                            Note that the CMOS sensor (OV5645) in the camera is no longer available, and should not be used for mass production.<br>
                                            Any software support provided is for evaluation purposes only.
                                        </li>
                                    </ul>
                                </h6>
                            </li>
                            <li>
                                MicroUSB to Serial Cable for serial communication.
                            </li>
                        </ul>
                    </td>
                    <td>
                        <img src="img/board.png"   width="100px" alt="board"/>
                    </td>
                    <td rowspan="3">
                        <a class="btn btn-secondary square-button" 
                            style="text-align:left;" 
                            href="{{ site.url }}{{ site.baseurl }}{% link download.md %}" 
                            role="button">
                            <span class="banner-title" style="font-size: 90%;line-height: 1em;">
                                Board and Software
                            </span><br>
                            <span class="banner-line">
                                Get the board and software for RZ/V series.<br>
                            </span>
                        </a>
                    </td>
                </tr>
                <tr>
                    <td>
                        RZ/V2H Evaluation Board Kit (EVK)
                    </td>
                    <td>
                        Evaluation Board Kit for RZ/V2H.
                        <br>
                        <h6 class="mb-1">
                        To use MIPI camera, please refer to e-CAM22_CURZH provided by <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp">e-con Systems</a>.
                        </h6>
                    </td>
                    <td>
                        <img src="img/V2H_EVK_v1.jpg"  width="100px" alt="board"/>
                    </td>
                </tr>
                <tr>
                    <td>
                        RZ/V2N Evaluation Board Kit (EVK)
                    </td>
                    <td>
                        Evaluation Board Kit for RZ/V2N.
                        <br>
                        <h6 class="mb-1">
                        To use MIPI camera, please refer to e-CAM22_CURZH provided by <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp">e-con Systems</a>.
                        </h6>
                    </td>
                    <td>
                        <img src="img/V2N_EVK.jpeg"  width="100px" alt="board"/>
                    </td>
                </tr>
            </table>
            For more details on these devices, please refer to <a href="https://www.renesas.com/products/microcontrollers-microprocessors/rz-mpus/rzv-embedded-ai-mpus">RZ/V series</a>.
            <br>
            <br>
            <h4 id="software" class="u_line">
                Software/Tool
            </h4>
            Followings are list of AI software/tool provided Renesas.<br>
            <br>
                <table class="gstable">
                    <tr>
                        <th>Items</th>
                        <th>Details</th>
                        <th>Link</th>
                    </tr>
                    <tr>
                        <td>
                            RZ/V AI Applications (AI Apps)
                        </td>
                        <td>
                            <h6 class="mb-1">
                                AI Apps are sets of following software that can be used as is for each use-case.
                                <ul class="mb-1">
                                    <li>
                                        Pre-trained AI model objects
                                    </li>
                                    <li>
                                        Pre-build application binary
                                    </li>
                                    <li>
                                        Application source code
                                    </li>
                                </ul>
                                Users can select the category of applications and access the applications provided on GitHub.
                            </h6>
                        </td>
                        <td>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link about-applications.md %}">
                                About AI Applications
                            </a>
                            <br>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}">
                                AI Applications
                            </a>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            RZ/V AI SDK
                        </td>
                        <td>
                            <h6 class="mb-1">
                                Binary development environment for AI Applications that is build for specific RZ/V EVK.
                            </h6>
                        </td>
                        <td>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link ai-sdk.md %}">
                                AI SDK Overview
                            </a>
                            <br>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}">
                                Getting Started
                            </a>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            RZ/V AI SDK Source Code
                        </td>
                        <td>
                            <h6 class="mb-1">
                                Source code of RZ/V AI SDK that user can customize Linux environment.
                            </h6>
                        </td>
                        <td>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk.md %}">
                                How to Build RZ/V2L AI SDK
                            </a>
                            <br>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}">
                                How to Build RZ/V2H AI SDK
                            </a>
                            <br>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}">
                                How to Build RZ/V2N AI SDK
                            </a>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            RZ/V AI Applications Demo
                        </td>
                        <td>
                            <h6 class="mb-1">
                                microSD card image that contains the RZ/V AI Applications.<br>
                                Users can try the AI Applications without having AI SDK environment.
                            </h6>
                        </td>
                        <td>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link demo.md %}">
                                How to Use Guide for RZ/V2L
                            </a>
                            <br>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link demo_v2h.md %}">
                                How to Use Guide for RZ/V2H
                            </a>
                            <br>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link demo_v2n.md %}">
                                How to Use Guide for RZ/V2N
                            </a>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            RZ/V AI Transfer Learning Tool (TLT)
                        </td>
                        <td>
                            <h6 class="mb-1">
                                GUI Tool to re-train the AI models used in RZ/V AI Applications with different datasets.
                            </h6>
                        </td>
                        <td>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link howto_retrain.md %}">
                                How to Re-train AI model
                            </a>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            DRP-AI TVM
                        </td>
                        <td>
                            <h6 class="mb-1">
                                Machine Learning Compiler plugin for Apache TVM with AI accelerator DRP-AI, which is a tool to compile your own AI models (including BYOM) to get the executable format on RZ/V series.<br>
                                <span style="color: red;">
                                    Note: AI SDK also includes DRP-AI TVM. However it is not the <b>latest</b> version.
                                    <br>  
                                    If you would like to use the latest DRP-AI TVM, please follow the guide in DRP-AI TVM Web to construct the environment.  
                                </span>
                            </h6>
                        </td>
                        <td>
                            <a class="btn btn-primary download-button" 
                                href="https://renesas-rz.github.io/rzv_drp-ai_tvm/" 
                                role="button">
                                DRP-AI TVM Web
                            </a>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            AI Navigator (e<sup>2</sup> studio)
                        </td>
                        <td>
                            <h6 class="mb-1">
                                A set of plugins for Renesas IDE, e<sup>2</sup> studio, that allows users to use following software on GUI environment.<br>
                                <ul class="mb-1">
                                    <li>
                                        RZ/V AI Applications
                                    </li>
                                    <li>
                                        RZ/V AI SDK
                                    </li>
                                    <li>
                                        RZ/V AI TLT
                                    </li>
                                    <li>
                                        DRP-AI TVM
                                    </li>
                                </ul>
                            </h6>
                        </td>
                        <td>
                            <a class="btn btn-secondary square-button square-button-link-small mb-2" 
                                style="width:220px;" 
                                href="{{ site.url }}{{ site.baseurl }}{% link ainavi_quick_start_guide.md %}">
                                AI Navigator Quick Start Guide
                            </a>
                        </td>
                    </tr>
                </table>
            <br>
        </div> 
    </div>
</div>
<br>
<br>
<div class="container">
    <div class="row">
        <div class="col-12">
            <h3 id="reference">
                Reference
            </h3>
            Renesas also provides other software packages related to RZ/V AI SDK.
            <br>
            Please refer to the Reference to <a href="{{ site.url }}{{ site.baseurl }}{% link index.md %}#reference">Related Software/Documentation</a>. 
        </div>
    </div>
</div>
<br>
<br>
<div class="container">
    <div class="row">
        <div class="col-12" align="right">
            <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}" role="button">
                Back to Home >
            </a>
        </div>
    </div>
</div>

<style>
.contents-sw{
    padding: 0px 0px 10px 0px;
    display: none;
}
.contents-sw-ai{
    border:1px solid #60a9b4;
    background:rgb(236, 242, 243);
}
.contents-sw-linux{
    border:1px solid #7E8E9A;
    background:rgb(228, 233, 239);
}
.contents-sw-trial{
    border:1px solid #635D89;
    background:rgb(235, 233, 244);
}
.contents-sw-other{
    border:1px solid rgb(235, 98, 9);
    background: #FADCCA;
}
.btn_sw-ai-Active{
    border:1px solid #60a9b4;
    background: #60a9b4;
}
.btn_sw-linux-Active{
    border:1px solid #7E8E9A;
    background: #7E8E9A;
}
.btn_sw-trial-Active{
    border:1px solid #635D89;
    background: #635D89;
}
.btn_sw-other-Active{
    border:1px solid rgb(235, 98, 9);
    background: rgb(235, 98, 9);
}
.contents-sw-title {
  max-width: fit-content;
  top: -2px;
  left: -2px;
  padding: 0 6px;
  height: 23px;
  line-height: 23px;
  font-size: large;
  margin-bottom: 3px;
  font-weight: bold;
  color: #ffffff;
}
.contents-sw-title-ai {
  background: #60a9b4;
}
.contents-sw-title-linux {
  background: #7E8E9A;
}
.contents-sw-title-trial {
  background: #635D89;
}
.contents-sw-title-other {
  background: rgb(235, 98, 9);
}
</style>
<script>
$('.btn_sw').on('click', function(){
    var click =  $(this).data('id');
    let class_name = "."+click;
    let button_name = ".btn_"+click;
    document.querySelectorAll(".contents-sw").forEach(elm => elm.style.display="none");
    document.querySelectorAll(class_name).forEach(elm => elm.style.display="flex"); //For bootstrap responsive design.
    if (click === "partner")
    {
        document.querySelectorAll(".btn_ai").forEach(elm => elm.classList.remove("btn_sw-ai-Active"));
        document.querySelectorAll(".btn_linux").forEach(elm => elm.classList.remove("btn_sw-linux-Active"));
        document.querySelectorAll(".btn_trial").forEach(elm => elm.classList.remove("btn_sw-trial-Active"));
        document.querySelectorAll(".btn_partner").forEach(elm => elm.classList.add("btn_sw-other-Active"));
    }
    else if (click === "ai-sdk-src")
    {
        document.querySelectorAll(".btn_ai").forEach(elm => elm.classList.remove("btn_sw-ai-Active"));
        document.querySelectorAll(".btn_linux").forEach(elm => elm.classList.add("btn_sw-linux-Active"));
        document.querySelectorAll(".btn_trial").forEach(elm => elm.classList.remove("btn_sw-trial-Active"));
        document.querySelectorAll(".btn_partner").forEach(elm => elm.classList.remove("btn_sw-other-Active"));
    }
    else if (click === "ai-apps-demo")
    {
        document.querySelectorAll(".btn_ai").forEach(elm => elm.classList.remove("btn_sw-ai-Active"));
        document.querySelectorAll(".btn_linux").forEach(elm => elm.classList.remove("btn_sw-linux-Active"));
        document.querySelectorAll(".btn_trial").forEach(elm => elm.classList.add("btn_sw-trial-Active"));
        document.querySelectorAll(".btn_partner").forEach(elm => elm.classList.remove("btn_sw-other-Active"));
    }
    else
    {
        document.querySelectorAll(".btn_ai").forEach(elm => elm.classList.remove("btn_sw-ai-Active"));
        document.querySelectorAll(".btn_linux").forEach(elm => elm.classList.remove("btn_sw-linux-Active"));
        document.querySelectorAll(".btn_trial").forEach(elm => elm.classList.remove("btn_sw-trial-Active"));
        document.querySelectorAll(".btn_partner").forEach(elm => elm.classList.remove("btn_sw-other-Active"));
        document.querySelectorAll(button_name).forEach(elm => elm.classList.add("btn_sw-ai-Active"));
    }
});
</script>