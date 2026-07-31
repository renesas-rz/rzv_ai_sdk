---
layout: default
title: Getting Started
redirect_from: 
  - /getting_started_v2l
  - /getting_started_v2h
  - /getting_started_v2n
---
<script type="text/javascript" src="http://code.jquery.com/jquery-3.7.0.min.js"></script>
<script>
  document.querySelector('#gs_details').open=true;
  //For V2L shutdown
  $(function(){
    $("#a3reference").load("{{ site.url }}{{ site.baseurl }}{% link getting_started.md %} a3reference");
  });
</script>
<div class="container">
    <div class="row">
        <div id="page-top" class="top col-12">
Getting Started
        </div>
    </div>
</div>
<br>
<br>
<h5>This page explains how to start-up the AI SDK.<br></h5>
AI SDK is build for specific board.<br>
Its version varies depending on the supported board.
<table class="gstable ms-4 mb-1">
  <tr>
    <th>Supported Board</th>
    <th>Supported AI SDK ver.</th>
    <th>RUHMI (DRP-AI TVM) ver.</th>
    <th>DRP-AI Translator ver.</th>
  </tr>
  <tr>
    <td>RZ/V2L Evaluation Board Kit</td>
    <td>RZ/V2L AI SDK <b>v7.00</b></td>
    <td>v2.6.1</td> <!--RUHMI-->
    <td>v1.90</td>  <!--Translator-->
  </tr>
  <tr>
    <td>RZ/V2H Evaluation Board Kit</td>
    <td>RZ/V2H AI SDK <b>v6.00</b></td>
    <td>v2.5.1</td> <!--RUHMI-->
    <td>i8 v1.04</td> <!--Translator-->
  </tr>
  <tr>
    <td>
      RZ/V2N Evaluation Board Kit<br>
      RZ/V2N Fast Prototyping Board
    </td>
    <td>RZ/V2N AI SDK <b>v6.30</b></td>
    <td>v2.5.1</td> <!--RUHMI-->
    <td>i8 v1.04</td> <!--Translator-->
  </tr>
</table>
<a class="ms-4" href="https://www.renesas.com/products/microcontrollers-microprocessors/rz-mpus/rzv-embedded-ai-mpus" target="_blank" rel="noopener noreferrer">Learn more about the RZ/V series.</a>

<reference_terminology>
<div class="note">
  <span class="note-title">Note</span>
  Hereafter, we use following terminology.<br>
  <ul class="mb-1">
    <li><b>RZ/V AI SDK</b>: Refers RZ/V2L AI SDK, RZ/V2H AI SDK and RZ/V2N AI SDK.</li>
    <li><b>EVK</b>: Refers "Evaluation Board Kit".</li>
    <li><b>FPB or FPB-RZV2N</b>: Refers "RZ/V2N Fast Prototyping Board".</li>
  </ul>
</div>
</reference_terminology>

<div class="note">
  <span class="note-title">Tutorial video</span>
  Tutorial video is available in  <a href="{{ site.url }}{{ site.baseurl }}{% link index.md %}#video" target="_blank" rel="noopener noreferrer">Video section.</a><br>
  <ul class="mb-1">
    <li>For RZ/V2L EVK: RZ/V2L AI SDK v2.10</li>
    <li>For RZ/V2H EVK: RZ/V2H AI SDK v3.00</li>
    <li>For RZ/V2N EVK: RZ/V2N AI SDK v5.00</li>
  </ul>
</div>

<div class="note">
  <span class="note-title">GUI environment</span>
  AI SDK has a CUI environment and a GUI environment.<br>
  For the GUI environment, see <a href="{{ site.url }}{{ site.baseurl }}{% link ainavi_quick_start_guide.md %}" target="_blank" rel="noopener noreferrer">AI Navigator Quick Start Guide</a>.<br>
</div>

<h3>Introduction</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      Getting Started explains the instruction to run AI Applications.<br>
    </div>
  </div>
  <div class="row">
    <div class="col-12">
      <h4 class="u_line">Software</h4>
      Renesas provides following software.
      <br><br>
      <div class="col-12 select_btn select_product">
        <a class="btn_prod 
            btn_V2L
            btn_prod-Active" 
            data-id="V2L">
            RZ/V2L
        </a>
        <a class="
            btn_prod 
            btn_V2H" 
            data-id="V2H">
            RZ/V2H
        </a>
        <a class="
            btn_prod 
            btn_V2N" 
            data-id="V2N">
            RZ/V2N
        </a>
      </div>
      <table class="gstable ms-4">
        <tr>
          <th>Software</th>
          <th>Provided on</th>
          <th>Details</th>
        </tr>
        <tr>
          <td>AI Applications</td>
          <td>GitHub</td>
          <td>
            This software is a set of following files that runs on the evaluation board kit.<br>
            <ul class="mb-1">
              <li>
              Application Source code (C++)
              </li>
              <li>
              Pre-build application binary
              </li>
              <li>
              Other necessary files to run the application
              </li>
              <li>
              Documentation (<code>README.md</code>)
              </li>
            </ul>
            <b>"Getting Started" page (this page)</b> explains how to run the AI Applications.
          </td>
        </tr>
        <tr>
          <td>RZ/V AI SDK</td>
          <td>Renesas Website</td>
          <td>
            This software is a development environment for AI Applications.<br>
            Provided as a zip file.<br>
            <b>"Getting Started" page (this page)</b> explains how to use RZ/V AI SDK to run the AI Applications.
          </td>
        </tr>
        <tr>
          <td>RZ/V AI SDK <br>Source Code</td>
          <td>Renesas Website</td>
          <td>
            This software is the source code of RZ/V AI SDK that includes Yocto Linux recipe.<br>
            Provided as a zip file.<br>
            Details and instructions are explained in the following pages.<br>
            <div class="mb-0 cnt_prod cnt_V2L" >
              <a class="btn btn-secondary square-button-gray ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk.md %}" role="button">
                <span class="banner-title">How to Build RZ/V2L AI SDK</span>
                <span class="banner-line">
                How can I build RZ/V2L AI SDK Source Code?<br>
                </span>
              </a>
            </div>
            <div class="mb-0 cnt_prod cnt_V2H" >
              <a class="btn btn-secondary square-button-gray ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}" role="button">
                <span class="banner-title">How to Build RZ/V2H AI SDK</span>
                <span class="banner-line">
                How can I build RZ/V2H AI SDK Source Code?<br>
                </span>
              </a>
            </div>
            <div class="mb-0 cnt_prod cnt_V2N" >
              <a class="btn btn-secondary square-button-gray ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2n.md %}" role="button">
                <span class="banner-title">How to Build RZ/V2N AI SDK</span>
                <span class="banner-line">
                How can I build RZ/V2N AI SDK Source Code?<br>
                </span>
              </a>
            </div>
          </td>
        </tr>
      </table>
    </div>
  </div>
</div>

<h3 id="step1" >Step 1: Obtain an evaluation board</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      To start using RZ/V AI SDK, we need to get the board.<br>
      Renesas provides ideal board kit for evaluation.<br>
      <br>
      Click the button below to get the board.<br>
      <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link download.md %}" role="button">
        <span class="banner-title">Board and Software </span>
        <span class="banner-line">Get the board and software for RZ/V series.</span>
      </a>
      <br>
      <br>
      <div class="col-12 select_btn select_product">
        <a class="btn_prod 
            btn_V2L
            btn_prod-Active" 
            data-id="V2L">
            RZ/V2L
        </a>
        <a class="btn_prod 
            btn_V2H" 
            data-id="V2H">
            RZ/V2H
        </a>
        <a class="btn_prod 
            btn_V2N" 
            data-id="V2N">
            RZ/V2N
        </a>
      </div>
      <div class="col-12 mb-0 cnt_prod cnt_prod-bg cnt_V2L">
        <h4 class="u_line" >RZ/V2L EVK</h4>
        <div class="container">
          <div class="row">
            <div class="col-9">
              The RZ/V2L EVK is the ideal board kit for RZ/V2L evaluation. 
              <br><br>
              Since MIPI camera module is included, you can start evaluating RZ/V2L immediately by building an environment.  
              <br><br>
            </div>
            <div class="col-3">
              <img src="img/board.png" alt="board"/>
            </div>
          </div>
          <div class="row">
            <div class="col-12">
              Following items are included in the RZ/V2L EVK.
              <br>
              <br>
              <table class="gstable">
                <tr>
                  <th>Equipment</th>
                  <th>Details</th>
                </tr>
                <tr>
                  <td>RZ/V2L Evaluation Board</td>
                  <td>Evaluation board itself.</td>
                </tr>
                <tr>
                  <td>MIPI Camera Module</td>
                  <td>Google Coral Camera.<br>
                  <h6 class="mb-1">Note that the CMOS sensor (OV5645) in the camera is <b>no longer available</b>, and should not be used for mass production. <br>Any software support provided is for evaluation purposes only.</h6></td>
                </tr>
                <tr>
                  <td>MicroUSB to Serial Cable</td>
                  <td>For serial communication between PC and the board.</td>
                </tr>
              </table>
            </div>
          </div>
        </div>
      </div>
      <div class="col-12 mb-0 cnt_prod cnt_prod-bg cnt_V2H" >
        <h4 class="u_line" >RZ/V2H EVK</h4>
        <div class="container">
          <div class="row">
            <div class="col-9">
              The RZ/V2H EVK is the ideal board kit for RZ/V2H evaluation. 
              <br><br>
              MIPI camera module is not included in EVK.
              <br>
              As an input device, AI Applications support USB camera with VGA (640x480) resolution.
              <br>
              To use MIPI camera, please refer to e-CAM22_CURZH camera provided by <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp" target="_blank" rel="noopener noreferrer">e-con Systems</a>. 
              <br>
              e-CAM22_CURZH camera supports FHD (1920x1080) resolution.
              <br><br>
            </div>
            <div class="col-3">
              <img src="img/V2H_EVK_v1.jpg" alt="board"/>
            </div>
          </div>
          <div class="row">
            <div class="col-12">
              Following items are included in the RZ/V2H EVK.
              <br>
              <br>
              <table class="gstable">
                <tr>
                  <th>Equipment</th>
                  <th>Details</th>
                </tr>
                <tr>
                  <td>RZ/V2H Evaluation Board</td>
                  <td>Evaluation board itself.</td>
                </tr>
              </table>
            </div>
          </div>
        </div>
      </div>
      <div class="col-12 mb-0 cnt_prod cnt_prod-bg cnt_V2N" >
        <div class="col-12 select_btn select_board">
          <h6 class="mb-2" style="color: #2a289d;"><b>Click the board name.</b></h6>
          <a class="btn_board 
              btn_V2N_EVK
              btn_board-Active" 
              data-id="V2N_EVK">
              RZ/V2N EVK
          </a>
          <a class="btn_board 
              btn_V2N_FPB" 
              data-id="V2N_FPB">
              FPB-RZV2N
          </a>
        </div>
        <div class="col-12 mb-0 cnt_bd cnt_V2N_EVK" >
          <h4 class="u_line" >RZ/V2N EVK</h4>
          <div class="container mb-4">
            <div class="row">
              <div class="col-9">
                The RZ/V2N EVK is the ideal board kit for RZ/V2N evaluation. 
                <br><br>
                MIPI camera module is not included in EVK.
                <br>
                As an input device, AI Applications support USB camera with VGA (640x480) resolution.
                <br>
                To use MIPI camera, please refer to e-CAM22_CURZH camera provided by <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp" target="_blank" rel="noopener noreferrer">e-con Systems</a>. 
                <br>
                e-CAM22_CURZH camera supports FHD (1920x1080) resolution.
                <br><br>
                Following items are included in the RZ/V2N EVK.
                <br>
                <br>
                <table class="gstable">
                  <tr>
                    <th>Equipment</th>
                    <th>RZ/V2N Evaluation Board (CPU board)<br>Model Number</th>
                    <th>Details</th>
                  </tr>
                  <tr>
                    <td>RZ/V2N Evaluation Board V1.0</td>
                    <td>RTK0EF0186C02000BJ</td>
                    <td>Evaluation board itself.</td>
                  </tr>
                  <tr>
                    <td>RZ/V2N Evaluation Board V2.0</td> 
                    <td>RTK0EF0186C02001BJ</td>
                    <td>Evaluation board itself.</td>
                  </tr>
                </table>
                To check the version of the RZ/V2N EVK, check the model number of the RZ/V2N Evaluation Board (CPU board).<br>
                <img src="img/v2n_evk_v2.png" alt="board" width="70%">
              </div>
              <div class="col-3">
                <img src="img/V2N_EVK.jpeg" alt="board"/>
              </div>
            </div>
          </div>
        </div>
        <div class="col-12 mb-0 cnt_bd cnt_V2N_FPB" >
          <h4 class="u_line" >FPB-RZV2N</h4>
          <div class="container">
            <div class="row">
              <div class="col-9">
                The FPB-RZV2N is the ideal board kit for fast prototyping. 
                <br>
                This board is simple evaluation board that significantly reduces the man-hours required for AI development, allowing easy evaluation.
                <br><br>
                It can be used in the same way as the RZ/V2N EVK, except for cases that depend on hardware differences.<br>
                E.g., Only 1 MIPI camera connector is available on FPB-RZV2N.
                <br><br>
                As well as EVK, MIPI camera module is not included in FPB.
                <br>
                As an input device, AI Applications support USB camera with VGA (640x480) resolution.
                <br>
                To use MIPI camera, please refer to e-CAM22_CURZH camera provided by <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp" target="_blank" rel="noopener noreferrer">e-con Systems</a>. 
                <br>
                e-CAM22_CURZH camera supports FHD (1920x1080) resolution.
                <br><br>
                Following items are included in the FPB-RZV2N.
                <br>
                <br>
                <table class="gstable">
                  <tr>
                    <th>Equipment</th>
                    <th>Details</th>
                  </tr>
                  <tr>
                    <td>RZ/V2N Fast Prototyping Board</td>
                    <td>Evaluation board itself.</td>
                  </tr>
                </table>
              </div>
              <div class="col-3">
                <img src="img/V2N_FPB.JPG" alt="board"/>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>
<br>

<h3 id="step2" >Step 2: Obtain necessary environment</h3>
<h4 class="mt-5 u_line">1. Necessary Equipments</h4>
  Please prepare the following equipments for your board.<br>
  <div class="col-12 select_btn select_product">
    <a class="btn_prod 
        btn_V2L
        btn_prod-Active" 
        data-id="V2L">
        RZ/V2L
    </a>
    <a class="btn_prod 
        btn_V2H" 
        data-id="V2H">
        RZ/V2H
    </a>
    <a class="btn_prod 
        btn_V2N" 
        data-id="V2N">
        RZ/V2N
    </a>
  </div>
  <table class="gstable">
    <tr>
      <th>For</th>
      <th>Equipment</th>
      <th>Details</th>
    </tr>
    <tr class="row_V2L">
      <td rowspan="5">
        RZ/V2L
      </td>
      <td>
        RZ/V2L EVK
      </td>
      <td>
        Evaluation Board Kit for RZ/V2L.<br>Includes followings.
        <ul class="mb-1">
          <li>
            MIPI Camera Module(Google Coral Camera)
            <br>
            <h6 class="mb-1">
              Note that the CMOS sensor (OV5645) in the camera is no longer available, and should not be used for mass production.<br>
              Any software support provided is for evaluation purposes only.
            </h6>
          </li>
          <li>MicroUSB to Serial Cable for serial communication.</li>
        </ul>
      </td>
    </tr>
    <tr class="row_V2L">
      <td>
        AC Adapter
      </td>
      <td>
        USB Power Delivery adapter for the board power supply.
      </td>
    </tr>
    <tr class="row_V2L">
      <td>
        MicroHDMI Cable
      </td>
      <td>
        Used to connect the HDMI Monitor and the board.<br>
        RZ/V2L EVK has microHDMI port.
      </td>
    </tr>
    <tr class="row_V2L">
      <td>
        USB Camera
      </td>
      <td>
        <b>Optional.</b> AI Applications support USB camera input.<br>
        Supported resolution: 640x480<br>
        Supported format: 'YUYV' (YUYV 4:2:2)
      </td>
    </tr>
    <tr class="row_V2L">
      <td>
        Windows PC
      </td>
      <td>
        <b>Optional.</b> Used as the serial communication console for QSPI Bootloader.<br>
        Operating Environment : Windows 11
      </td>
    </tr>
    <tr class="row_V2H">
      <td rowspan="4">
        RZ/V2H
      </td>
      <td>
        RZ/V2H EVK
      </td>
      <td>
        Evaluation Board Kit for RZ/V2H.
      </td>
    </tr>
    <tr class="row_V2H">
      <td>
        AC Adapter
      </td>
      <td>
        USB Power Delivery adapter for the board power supply.<br>
        100W is required.
      </td>
    </tr>
    <tr class="row_V2H">
      <td>
        HDMI Cable
      </td>
      <td>
        Used to connect the HDMI Monitor and the board.<br>
        RZ/V2H EVK has HDMI port.
      </td>
    </tr>
    <tr class="row_V2H">
      <td>
        USB Camera
      </td>
      <td>
        Since RZ/V2H EVK does not include camera module, this will be the standard camera input source.<br>
        Supported resolution: 640x480<br>
        Supported format: 'YUYV' (YUYV 4:2:2)<br>
        <h6 class="mt-3 mb-1">
          To use MIPI camera, please refer to e-CAM22_CURZH provided by <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp" target="_blank" rel="noopener noreferrer">e-con Systems</a>.<br>
          e-CAM22_CURZH camera supports FHD(1920x1080) resolution.
        </h6>
      </td>
    </tr>
    <tr class="row_V2N">
      <td rowspan="4">
        RZ/V2N
      </td>
      <td>
        RZ/V2N EVK<br>
        or FPB-RZV2N
      </td>
      <td>
        Evaluation Board Kit for RZ/V2N.
      </td>
    </tr>
    <tr class="row_V2N">
      <td>
        AC Adapter
      </td>
      <td>
        USB Power Delivery adapter for the board power supply.<br>
        60W is required for EVK.<br>
        45W is required for FPB.
      </td>
    </tr>
    <tr class="row_V2N">
      <td>
        HDMI Cable
      </td>
      <td>
        Used to connect the HDMI Monitor and the board.<br>
        RZ/V2N EVK/FPB has HDMI port.
      </td>
    </tr>
    <tr class="row_V2N">
      <td>
        USB Camera
      </td>
      <td>
        Since RZ/V2N EVK/FPB does not include camera module, this will be the standard camera input source.<br>
        Supported resolution: 640x480<br>
        Supported format: 'YUYV' (YUYV 4:2:2)<br>
        <h6 class="mt-3 mb-1">
          To use MIPI camera, please refer to e-CAM22_CURZH provided by <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp" target="_blank" rel="noopener noreferrer">e-con Systems</a>.<br>
          e-CAM22_CURZH camera supports FHD(1920x1080) resolution.
        </h6>
      </td>
    </tr>
    <tr>
      <td rowspan="8">
        Common
      </td>
      <td>
        USB Cable Type-C
      </td>
      <td>
        Connect AC adapter and the board.
      </td>
    </tr>
    <tr>
      <td>
        HDMI Monitor
      </td>
      <td>
        Used to display the graphics of the board.
      </td>
    </tr>
    <tr>
      <td>
        microSD card
      </td>
      <td>
        Must have over 16GB capacity of blank space.<br>
        Operating Environment: Transcend UHS-I microSD 300S 16GB
      </td>
    </tr>
    <tr>
      <td>
        Linux PC
      </td>
      <td>
        Used for Setup microSD card and RZ/V AI SDK Setup.<br>
        Operating Environment: Ubuntu 22.04
      </td>
    </tr>
    <tr>
      <td>
        SD card reader
      </td>
      <td>
        Used for setting up microSD card.
      </td>
    </tr>
    <tr>
      <td>
        USB Hub
      </td>
      <td>
        Used to connect USB Keyboard and USB Mouse to the board.
      </td>
    </tr>
    <tr>
      <td>
        USB Keyboard
      </td>
      <td>
        Used to type strings on the terminal of board.
      </td>
    </tr>
    <tr>
      <td>
        USB Mouse
      </td>
      <td>
        Used to operate the mouse on the screen of board.
      </td>
    </tr>
  </table>
<div class="note">
  <span class="note-title">Note</span>
  USB camera has different supported resolution and format.<br>
  To check the specification of your USB camera, use <a href="https://www.mankier.com/1/v4l2-ctl" target="_blank" rel="noopener noreferrer"><code>v4l2-ctl</code></a> command.
</div>
<br>
<h4 class="u_line">2. Necessary Software</h4>
<p class="mb-1">Please install following software <b>on Linux PC</b>.</p>
<ul class="mt-1 mb-1">
  <li><a href="https://docs.docker.com/" target="_blank" rel="noopener noreferrer">Docker</a></li>  <!-- Open in new tab -->
  <li>git</li>
  <li>bmap-tools</li>
</ul>
<br>

<h3 id="step3" >Step 3: Obtain RZ/V AI SDK</h3>
RZ/V AI SDK provides following packages for each supported board.

<div class="col-12 select_btn select_product">
  <a class="btn_prod 
      btn_V2L
      btn_prod-Active" 
      data-id="V2L">
      RZ/V2L
  </a>
  <a class="
      btn_prod 
      btn_V2H" 
      data-id="V2H">
      RZ/V2H
  </a>
  <a class="
      btn_prod 
      btn_V2N" 
      data-id="V2N">
      RZ/V2N
  </a>
</div>
<table class="gstable">
  <tr>
    <th>Name</th>
    <th>Package</th>
    <th>Details</th>
  </tr>
  <tr>
    <td><font color="red"><b>
      <!-- RZ/V AI SDK -->
      <span class="cnt_prod cnt_V2L" >
        RZ/V2L AI SDK
      </span>
      <span class="cnt_prod cnt_V2H" >
        RZ/V2H AI SDK
      </span>
      <span class="cnt_prod cnt_V2N" >
        RZ/V2N AI SDK
      </span>
    </b></font></td>
    <td><font color="red"><b>RTK0EF0*SJ.zip</b></font></td>
    <td><font color="red"><b>Package used for AI development.</b></font><br>
      For this Getting Started, please download 
      <font color="red"><b>
        <span class="cnt_prod cnt_V2L">
          RZ/V2L AI SDK
        </span>
        <span class="cnt_prod cnt_V2H">
          RZ/V2H AI SDK
        </span>
        <span class="cnt_prod cnt_V2N">
          RZ/V2N AI SDK
        </span>
      </b></font> 
      <!-- for your preferred device  -->
      from the link below.<br>
      <div class="mb-0 cnt_prod cnt_V2L" >
        <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="https://www.renesas.com/document/sws/rzv2l-ai-sdk-v700" role="button" target="_blank" rel="noopener noreferrer">
            <span class="banner-title">RZ/V2L AI SDK</span>
            <span class="banner-line">Get the RZ/V2L AI Software Development Kit</span>
        </a>
      </div>
      <!-- <br> -->
      <div class="mb-0 cnt_prod cnt_V2H" >
      <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="https://www.renesas.com/document/sws/rzv2h-ai-sdk-v600" role="button" target="_blank" rel="noopener noreferrer">
          <span class="banner-title">RZ/V2H AI SDK</span>
          <span class="banner-line">Get the RZ/V2H AI Software Development Kit</span>
      </a>
      </div>
      <!-- <br> -->
      <div class="mb-0 cnt_prod cnt_V2N" >
      <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="https://www.renesas.com/document/sws/rzv2n-ai-sdk-v630" role="button" target="_blank" rel="noopener noreferrer">
          <span class="banner-title">RZ/V2N AI SDK</span>
          <span class="banner-line">Get the RZ/V2N AI Software Development Kit</span>
      </a>    
      </div>
      <br>
      Once downloaded, please check the Release Note included in the package.
      <br>    
    </td>
  </tr>
  <tr>
    <td>
      <!-- RZ/V AI SDK -->
      <span class="cnt_prod cnt_V2L" >
        RZ/V2L AI SDK
      </span>
      <span class="cnt_prod cnt_V2H" >
        RZ/V2H AI SDK
      </span>
      <span class="cnt_prod cnt_V2N" >
        RZ/V2N AI SDK
      </span>
      <br>Source Code
    </td>
    <td>RTK0EF0*SJ_linux-src.zip</td>
    <td>Package used for Linux development.<br>
      Please refer to following pages for more details on this package.<br>
      <div class="cnt_prod cnt_V2L" >
        <a class="btn btn-secondary square-button-gray ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk.md %}" role="button">
          <span class="banner-title">How to Build RZ/V2L AI SDK</span>
          <span class="banner-line">
          How can I build RZ/V2L AI SDK Source Code?<br>
          </span>
        </a>
      </div>
      <div class="cnt_prod cnt_V2H" >
        <a class="btn btn-secondary square-button-gray ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}" role="button">
          <span class="banner-title">How to Build RZ/V2H AI SDK</span>
          <span class="banner-line">
          How can I build RZ/V2H AI SDK Source Code?<br>
          </span>
        </a>
      </div>
      <div class="cnt_prod cnt_V2N" >
        <a class="btn btn-secondary square-button-gray ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2n.md %}" role="button">
          <span class="banner-title">How to Build RZ/V2N AI SDK</span>
          <span class="banner-line">
          How can I build RZ/V2N AI SDK Source Code?<br>
          </span>
        </a>
      </div>
    </td>
  </tr>
</table>
<h3 id="step4" >Step 4: Extract RZ/V AI SDK package</h3>
This step explains how to extract the RZ/V AI SDK zip file.
<ol>
  <li>On your Linux PC, make the working directory.
{% highlight shell %}
mkdir -p ai_sdk_work
{% endhighlight %}
  </li>
  <li>Register the working directory path to an environment variable. 
{% highlight shell%}
export WORK=<path to the working directory>/ai_sdk_work
{% endhighlight %}
  </li>
  <li>Move to the working directory.
{% highlight shell%}
cd ${WORK}
{% endhighlight %}
  </li>
  <li>Extract RZ/V AI SDK zip file under the working directory. 
{% highlight shell%}
unzip <Path to the file>/RTK0EF0*.zip -d ${WORK}
{% endhighlight %}
  </li>
  <li>Check the working directory to confirm the package contents.
{% highlight shell%}
ls ${WORK}/
{% endhighlight %}
    <ul>
      <li>If the above command prints followings, the package is extracted correctly.
{% highlight shell%}
ai_sdk_setup  board_setup  documents  references r11an0*.pdf
{% endhighlight %}
      </li>
    </ul>
  </li>
</ol>
<br>

<h3 id="step5" >Step 5: Setup RZ/V AI SDK</h3>
This step explains how to setup the RZ/V AI SDK environment.
<div class="note">
  <span class="note-title">Note</span>
  Make sure that you have <a href="https://docs.docker.com/" target="_blank" rel="noopener noreferrer">installed Docker</a> on your Linux PC.
</div>

<div class="col-12 select_btn select_product">
  <a class="btn_prod 
      btn_V2L
      btn_prod-Active" 
      data-id="V2L">
      RZ/V2L
  </a>
  <a class="
      btn_prod 
      btn_V2H" 
      data-id="V2H">
      RZ/V2H
  </a>
  <a class="
      btn_prod 
      btn_V2N" 
      data-id="V2N">
      RZ/V2N
  </a>
</div>

<ol>
  <li>On your Linux PC, move to the working directory.
{% highlight shell%}
cd ${WORK}/ai_sdk_setup
{% endhighlight %}
  </li>
  <li>Build docker image.<br>
    <div class="cnt_prod cnt_prod-bg cnt_V2L">
{% highlight shell%}
sudo docker build -t rzv2l_ai_sdk_image --build-arg PRODUCT="V2L" .
{% endhighlight %}
    </div>
    <div class="cnt_prod cnt_prod-bg cnt_V2H">
{% highlight shell%}
sudo docker build -t rzv2h_ai_sdk_image --build-arg PRODUCT="V2H" .
{% endhighlight %}
    </div>
    <div class="cnt_prod cnt_prod-bg cnt_V2N">
{% highlight shell%}
sudo docker build -t rzv2n_ai_sdk_image --build-arg PRODUCT="V2N" .
{% endhighlight %}
      <!-- <div class="note">
        <span class="note-title">Note</span>
        Since RZ/V2N is a brother chip of RZ/V2H, the same commands can be used.
      </div> -->
    </div>
  </li>
  <li>Create new directory to be mounted on Docker container.
{% highlight shell%}
mkdir ${WORK}/ai_sdk_setup/data
{% endhighlight %}
  </li>
  <li>Create docker container. <br>Here, <code>rzv2*_ai_sdk_container</code> is a name of docker container, which can be changed by user.
    <div class="cnt_prod cnt_prod-bg cnt_V2L">
{% highlight shell%}
sudo docker run -it --name rzv2l_ai_sdk_container -v $(pwd)/data:/drp-ai_tvm/data rzv2l_ai_sdk_image
{% endhighlight %}
    </div>
    <div class="cnt_prod cnt_prod-bg cnt_V2H">
{% highlight shell%}
sudo docker run -it --name rzv2h_ai_sdk_container -v $(pwd)/data:/drp-ai_tvm/data rzv2h_ai_sdk_image
{% endhighlight %}
    </div>
    <div class="cnt_prod cnt_prod-bg cnt_V2N">
{% highlight shell%}
sudo docker run -it --name rzv2n_ai_sdk_container -v $(pwd)/data:/drp-ai_tvm/data rzv2n_ai_sdk_image
{% endhighlight %}
      <!-- <div class="note">
        <span class="note-title">Note</span>
        Since RZ/V2N is a brother chip of RZ/V2H, the same commands can be used.
      </div> -->
    </div>
    The local <code>$(pwd)/data</code> is mounted to <code>/drp-ai_tvm/data</code> on the Docker container by the above command option.<br>
    For example, you can use this directory to copy files created on the Docker container to your local environment.<br><br>
    <img class="procedure"  src="img/docker_mount.jpg" alt="docker" width="90%" />
  </li><br>
<!--
  <li>In docker container, run the following command to copy <code>libtvm_runtime.so</code>, which is the necessary file for the board, to host machine.<br>
{% highlight shell%}
cp /drp-ai_tvm/obj/build_runtime/${PRODUCT}/libtvm_runtime.so /drp-ai_tvm/data
{% endhighlight %}
  </li>
-->
  <li>To exit docker, run following commands.<br>
{% highlight shell%}
exit
{% endhighlight %}
  </li>
  <li>To start the docker container again, run the following command.<br>
    <div class="cnt_prod cnt_prod-bg cnt_V2L">
{% highlight shell%}
sudo docker start -i rzv2l_ai_sdk_container
{% endhighlight %}
    </div>
    <div class="cnt_prod cnt_prod-bg cnt_V2H">
{% highlight shell%}
sudo docker start -i rzv2h_ai_sdk_container
{% endhighlight %}
    </div>
    <div class="cnt_prod cnt_prod-bg cnt_V2N">
{% highlight shell%}
sudo docker start -i rzv2n_ai_sdk_container
{% endhighlight %}
    </div>
  </li>
</ol>
<br>
You have finished the RZ/V AI SDK environment setup.<br>
You are ready to build the AI applications!
<br><br>

<h3 id="step6" >Step 6: Build RZ/V AI Application</h3>
This step explains how to build AI application.
<br>
To see the overview about AI Applications, please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link about-applications.md %}" target="_blank" rel="noopener noreferrer">About AI Applications</a> page.<br>
<a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link about-applications.md %}" role="button" target="_blank" rel="noopener noreferrer">
    <span class="banner-title">About AI Applications</span><br>
    <span class="banner-line">
    What is AI Applications?<br>
    How is directory/file structured?<br>
    How can I download the previous version?<br></span>
</a>
<br>
<br>
<div class="note">
  <span class="note-title">Note</span>
  Following procedures are for users who would like to build the application from the source code.<br>
  If you would like to run the application <b>as quickly as possible</b>, you can <span class="skip">skip this step</span> and use pre-build application binary.<br>
  Please clone the application respository of your selection and proceed to the <b><a href="#step7">next step (Step 7: Deploy AI Application)</a></b>.<br>
  E.g., <b>
    <a 
      href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v7.10/R01_object_detection" 
      target="_blank" 
      rel="noopener noreferrer">R01_object_detection</a>
  </b>, 
{% highlight shell%}
git clone https://github.com/renesas-rz/rzv_ai_sdk.git
{% endhighlight %}
</div>
<br>
<h4 id="build-instruction" class="u_line">Building instructions.</h4>
In <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}" target="_blank" rel="noopener noreferrer">AI Applications</a>, there are two types of applications.
  <table class="gstable ms-3">
    <tr>
        <th>Application</th>
        <th>GitHub Repository</th>
        <th>Details</th>
        <th>Example</th>
    </tr>
    <tr>
        <td><Application 1></td>
        <td>
          <h6 class="mb-0 table-small-text">
            <ul class="mb-1 ps-3">
              <li>
                <a href="https://github.com/renesas-rz/rzv_ai_sdk" target="_blank" rel="noopener noreferrer">https://github.com/renesas-rz/rzv_ai_sdk</a><br>
              </li>
              <li>
                <a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps" target="_blank" rel="noopener noreferrer">https://github.com/Ignitarium-Renesas/rzv_ai_apps</a>
              </li>
            </ul>
          </h6>
        </td>
        <td>
          <h6 class="mb-0 table-small-text">
            These repositories provide the complete instruction in each application documentation.
          </h6>
        </td>
        <td>
          <h6 class="mb-0">
            <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v7.10/R01_object_detection" target="_blank" rel="noopener noreferrer">R01_object_detection</a>
          </h6>
        </td>
    </tr>
    <tr>
        <td><Application 2></td>
        <td>
          <h6 class="mb-0 table-small-text">
            <ul class="mb-1 ps-3">
              <li>
                <a href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary" target="_blank" rel="noopener noreferrer">https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary</a>
              </li>
            </ul>
          </h6>
        </td>
        <td>
          <h6 class="mb-0 table-small-text">
            This repository only contains AI Applications for RZ/V2L EVK.<br>
            It does not provide instructions for RZ/V AI SDK.<br>
            Please refer to the instruction provided in this page.
          </h6>
        </td>
        <td>
          <h6 class="mb-0">
            <a href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/01_Head_count" target="_blank" rel="noopener noreferrer">01_Head_count</a>
          </h6>
        </td>
    </tr>
  </table>
<ul style="list-style:none;">
  <li>
    <h5 id="build-option1" class="mb-3">Option 1: For <b>&lt;Application 1&gt;</b></h5>
    <ol>
      <li>
        Check the <code>README.md</code> document provided in application directory and follow the instruction in the chapter called <b>"Application: Build Stage"</b> (or similar) to build the application.<br><br>
        <div class="box1">
          <u><b>Example:</b></u><br>
          For R01_object_detection application, follow the instruction in <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v7.10/R01_object_detection#application-build-stage" target="_blank" rel="noopener noreferrer">README > Application: Build Stage</a> to generate the following application binary.
          <ul>
            <li>object_detection</li>
          </ul>
        </div>
          <!-- From here: Delete when making latest version -->
          <!--
        <div class="note">
          <span class="note-title">Note</span>
          The <code>git clone</code> command shown in the <code>README.md</code> will download the <b style="color: red;">latest</b> source code and related files. <br><br>
          To download the files of AI Applications v{{ site.version }}, please specify the version tag by adding <code>-b v{{ site.version }}</code>  when you running the <code>git clone</code> command as shown below.
{% highlight shell%}
git clone -b v{{ site.version }} https://github.com/renesas-rz/rzv_ai_sdk.git
{% endhighlight %}
        </div>
          -->
          <!-- Until here: Delete when making latest version -->
      </li>
    </ol>
    <br>
    After you generated the application binary, please proceed to <a href="#step7">Step 7</a>
  </li>
  <br><br>
  <li>
  <details close>
    <summary><h5 id="build-option2" style="display: inline;" class="mb-3">Option 2: For <b>&lt;Application 2&gt;</b></h5> &nbsp;&nbsp;
    <b><i>Click to Open</i></b>
    </summary>
    <ol class="border pt-2 pb-2">
      <li>Run (or start) docker container.<br><br>
        <div class="box1">
          <u><b>Example:</b></u><br>
          Run the following command to start the docker container created in <a href="#step5">Step 5</a>.
{% highlight shell%}
sudo docker start -i rzv2l_ai_sdk_container
{% endhighlight %}
        </div>
      </li><br>
      <li>Change the environment variable to use the cross compiler.
{% highlight shell%}
source /opt/rz-vlp/5.0.11/environment-setup-cortexa55-poky-linux
{% endhighlight %}
        <div class="note">
          <span class="note-title">Note</span>
          This command needs to be called everytime user opened the new terminal.
        </div>
      </li><br>
      <li>Move to the mounted point in docker container.
        <br>
{% highlight shell%}
cd /drp-ai_tvm/data
{% endhighlight %}
      </li><br>
      <li>Download the application source code.<br>
        Here, we use <a href="https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary/tree/main/01_Head_count" target="_blank" rel="noopener noreferrer">RZV2L_AiLibrary repository 01_Head_count application</a> as an example.
        <br>
{% highlight shell%}
git clone https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary
{% endhighlight %}
        <!-- From here: Delete when making latest version -->
        <!-- <div class="note">
          <span class="note-title">Note</span>
          The command above will download the <b style="color: red;">latest</b> source code and related files. <br><br>
          To download the files of AI Applications v{{ site.version }}, please specify the version tag by adding <code>-b v{{ site.version }}</code> when you running the <code>git clone</code> command as shown below.
{% highlight shell%}
git clone -b v{{ site.version }} https://github.com/Ignitarium-Renesas/RZV2L_AiLibrary
{% endhighlight %}
        </div> -->
        <!-- Until here: Delete when making latest version -->
      </li><br>
      <li>Move to the application directory.
{% highlight shell%}
cd RZV2L_AiLibrary/01_Head_count/Head_count_cam
{% endhighlight %}
        <div class="note">
          <span class="note-title">Note</span>
          The file configuration depends on each application. Please check the file configuration in the repository carefully.
        </div>
      </li><br>
      <li>Build the application with <code>make</code> command.
        <br>
{% highlight shell%}
make
{% endhighlight %}
      </li><br>
      <li>Check that following application is generated in the <code>RZV2L_AiLibrary/01_Head_count/<br class="br-sp">Head_count_cam/exe</code>.
        <ul>
          <li>head_count_cam_app</li>
        </ul>
      </li><br>
      <li>If you would like to build the other applications of <a href="#build-option1"><Application 1> (Option 1)</a>, please exit and restart the docker container.
      </li>
    </ol>
    <br>
    After you generated the application binary, please proceed to <a href="#step7">Step 7</a>
  </details>
  </li>
</ul>
<br><br>

<h3 id="step7" >Step 7: Deploy AI Application</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      This section explains how to deploy the AI Application to the target board.
      <br>
      <br>
      <div class="select_btn select_product">
        <a class="btn_prod 
            btn_V2L
            btn_prod-Active" 
            data-id="V2L">
            RZ/V2L
        </a>
        <a class="
            btn_prod 
            btn_V2H" 
            data-id="V2H">
            RZ/V2H
        </a>
        <a class="
            btn_prod 
            btn_V2N" 
            data-id="V2N">
            RZ/V2N
        </a>
      </div>
      To boot the board, bootloader and other Linux necessary files are required.<br>
      Following bootloader types and their corresponding filesystem are available on 
      <span class="cnt_prod cnt_V2L">
        RZ/V2L AI SDK
      </span>
      <span class="cnt_prod cnt_V2H">
        RZ/V2H AI SDK
      </span>
      <span class="cnt_prod cnt_V2N">
        RZ/V2N AI SDK
      </span>.
      <div class="cnt_prod cnt_prod-bg cnt_V2L">
        <table class="gstable">
          <tr>
            <th>Type</th>
            <th>Description</th>
            <th>RZ/V2L EVK</th>
          </tr>
          <tr>
            <td>eSD Bootloader</td>
            <td>The board boots up using the bootloader written on microSD card.<br>
            Linux kernel and filesystem are also on microSD card.</td>
            <td>&#10004;</td>
          </tr>
          <tr>
            <td>QSPI Bootloader</td>
            <td>The board boots up using the bootloader written in Flash ROM on the board.<br>
            Linux kernel and filesystem are on microSD card.</td>
            <td>&#10004;</td>
          </tr>
        </table>
      </div>
      <div class="cnt_prod cnt_prod-bg cnt_V2H">
        <table class="gstable">
          <tr>
            <th>Type</th>
            <th>Description</th>
            <th>RZ/V2H EVK</th>
          </tr>
          <tr>
            <td>eSD Bootloader</td>
            <td>The board boots up using the bootloader written on microSD card.<br>
            Linux kernel and filesystem are also on microSD card.</td>
            <td>&#10004;</td>
          </tr>
          <tr>
            <td>xSPI Bootloader</td>
            <td>The board boots up using the bootloader written in Flash ROM on the board.<br>
            Linux kernel and filesystem are on microSD card.</td>
            <td>&#10004;</td>
          </tr>
        </table>
      </div>
      <div class="cnt_prod cnt_prod-bg cnt_V2N">
        <table class="gstable">
          <tr>
            <th>Type</th>
            <th>Description</th>
            <th>RZ/V2N EVK-ver1</th>
            <th>RZ/V2N EVK-ver2</th>
            <th>FPB-RZV2N</th>
          </tr>
          <tr>
            <td>eSD Bootloader</td>
            <td>The board boots up using the bootloader written on microSD card.<br>
            Linux kernel and filesystem are also on microSD card.</td>
            <td>&#10004;</td>
            <td>&#10004;</td>
            <td>&#10004;</td>
          </tr>
          <tr>
            <td>xSPI Bootloader</td>
            <td>The board boots up using the bootloader written in Flash ROM on the board.<br>
            Linux kernel and filesystem are on microSD card.</td>
            <td>&#10004;</td>
            <td>&#10004;</td>
            <td>-</td>
          </tr>
          <tr>
            <td>eMMC Bootloader</td>
            <td>The board boots up using the bootloader written in eMMC on the board.<br>
            Linux kernel and filesystem are on microSD card.</td>
            <td>
              &#10004;
              (
              <a href="{{ site.url }}{{ site.baseurl }}{% link dev_guide.md %}#D4" target="_blank" rel="noopener noreferrer">
                Link
              </a>
              )
              </td>
            <td>
              &#10004;
              (
              <a href="{{ site.url }}{{ site.baseurl }}{% link dev_guide.md %}#D4" target="_blank" rel="noopener noreferrer">
                Link
              </a>
              )
              </td>
            <td>-</td>
          </tr>
        </table>
      </div>
      <!-- Other necessary files, i.e. Linux kernel and root filesystem, are stored on microSD card.<br>
      You can use Linux PC to format the microSD card and expand the kernel and the root filesystem using SD card reader.<br> -->
      <br>
      <img class="procedure2" src="img/esd_spi_emmc.svg" alt="docker" style="max-height: 200px" />
      <br>
      <div class="note">
        <span class="note-title">Note</span>
        Regarding the eSD (Embedded SD) booting, please note the following:
        <ul class="mb-1">
          <li>The eSD boot procedure using microSD card described in this guide is for evaluation purposes only.</li>
          <li>If you use the eSD boot, please implement the eSD on your board according to the standard "SD Specification Part 1 eSD Addendum (version 2.10)".</li>
          <div class="cnt_prod cnt_V2H">
          <li>The reboot command cannot be used when using the eSD boot procedure using microSD card described in this guide.</li>
          </div>
          <div class="cnt_prod cnt_V2N">
          <li>The reboot command cannot be used when using the eSD boot procedure using microSD card described in this guide.</li>
          </div>
        </ul>
      </div>
      <br>
      <h4 id="step7prep" class="u_line" >Preparation</h4>
      <div class="note">
        <span class="note-title">Click the button</span>
        This step contains both eSD and 
        <span class="cnt_prod cnt_V2L">
        QSPI Bootloader 
        </span> 
        <span class="cnt_prod cnt_V2H">
        xSPI Bootloader 
        </span> 
        <span class="cnt_prod cnt_V2N">
        xSPI Bootloader 
        </span> 
        explanation.<br>
        Please click the button below to update the explanation according to your bootloader interface.<br>
        <div class="select_btn SelectButton">
          <span class="btn_bl ButtoneSD">eSD Bootloader</span>
          <span class="btn_bl ButtonSPI">
            <span class="cnt_prod cnt_V2L">
            QSPI Bootloader 
            </span> 
            <span class="cnt_prod cnt_V2H">
            xSPI Bootloader 
            </span> 
            <span class="cnt_prod cnt_V2N">
            xSPI Bootloader 
            </span> 
          </span>
        </div>
        <div class="ContenteSD contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          eSD explanation will be shown in this style if you click "eSD Bootloader" button above.
        </div>
        <div class="ContentSPI contentSPI-bg">
          <span class="ContentSPI-title">For 
            <span class="cnt_prod cnt_V2L">
            QSPI 
            </span> 
            <span class="cnt_prod cnt_V2H">
            xSPI 
            </span> 
            <span class="cnt_prod cnt_V2N">
            xSPI 
            </span> 
          </span>
          <span class="cnt_prod cnt_V2L">
            QSPI 
          </span> 
          <span class="cnt_prod cnt_V2H">
            xSPI 
          </span> 
          <span class="cnt_prod cnt_V2N">
            xSPI 
          </span> 
          explanation will be shown in this style if you click 
          <span class="cnt_prod cnt_V2L">
            "QSPI 
          </span> 
          <span class="cnt_prod cnt_V2H">
            "xSPI 
          </span> 
          <span class="cnt_prod cnt_V2N">
            "xSPI 
          </span> 
           Bootloader" button above.
        </div>
      </div>
      <br>
      <h4 id="step7-1" class="u_line">1. Setup the Board</h4>
      <div class="mt-2 select_btn select_product">
        <a class="btn_prod 
            btn_V2L
            btn_prod-Active" 
            data-id="V2L">
            RZ/V2L
        </a>
        <a class="
            btn_prod 
            btn_V2H" 
            data-id="V2H">
            RZ/V2H
        </a>
        <a class="
            btn_prod 
            btn_V2N" 
            data-id="V2N">
            RZ/V2N
        </a>
      </div>
      <div class="ContenteSD">
        <div class="contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          microSD card needs to contain bootloaders, the Linux kernel and root filesystem to boot-up the board.<br>
          <span class="cnt_prod cnt_V2L">
            RZ/V2L AI SDK
          </span>
          <span class="cnt_prod cnt_V2H">
            RZ/V2H AI SDK
          </span>
          <span class="cnt_prod cnt_V2N">
            RZ/V2N AI SDK
          </span>
          supports the WIC format for SD card image.<br>
          You can use Linux PC to write the SD card image into microSD card with SD card reader.<br>
        </div>
        <div class="note">
          <span class="note-title">Note</span>
          This step is required only when starting the AI SDK or when using the new version of AI SDK.<br>
          If you have already setup the microSD card with the latest bootloader, Linux kernel, Linux device tree file and root filesystem, <span class="skip">skip this step</span> and proceed to <a href="#step7-2" target="_blank" rel="noopener noreferrer">the next procedure (2. Deploy Application to the Board)</a>.
        </div>
      </div>
      <div class="ContentSPI">
        <div class="contentSPI-bg">
          <span class="ContentSPI-title">For xSPI</span>
          microSD card needs to contain the Linux kernel and root filesystem to boot-up the board.<br>
          <span class="cnt_prod cnt_V2L">
            RZ/V2L AI SDK
          </span>
          <span class="cnt_prod cnt_V2H">
            RZ/V2H AI SDK
          </span>
          <span class="cnt_prod cnt_V2N">
            RZ/V2N AI SDK
          </span>
          supports the WIC format for SD card image.<br>
          You can use Linux PC to write the SD card image into microSD card with SD card reader.<br>
          Bootloaders must be written in Flash ROM on the board.
          You can use Windows PC to write the bootloaders on Flash ROM.
        </div>
        <div class="note">
          <span class="note-title">Note</span>
          This step is required only when starting the AI SDK or when using the new version of AI SDK.<br>
          If you have already setup the microSD card and the bootloader written in Flash ROM on the board, <span class="skip">skip this step</span> and proceed to <a href="#step7-2" target="_blank" rel="noopener noreferrer">the next procedure (2. Deploy Application to the Board)</a>. 
        </div>
      </div>
      <div class="note">
        <span class="note-title">Note</span>
        The size of WIC format SD card image is 16GB.<br>
        If you would like to expand the SD card image size, 
        <span class="cnt_prod cnt_V2L">
          please build the RZ/V2L AI SDK Source Code according to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk.md %}" target="_blank" rel="noopener noreferrer">How to Build RZ/V2L AI SDK</a>.
        </span>
        <span class="cnt_prod cnt_V2H">
          please build the RZ/V2H AI SDK Source Code according to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}" target="_blank" rel="noopener noreferrer">How to Build RZ/V2H AI SDK</a>.
        </span>
        <span class="cnt_prod cnt_V2N">
          please build the RZ/V2N AI SDK Source Code according to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2n.md %}" target="_blank" rel="noopener noreferrer">How to Build RZ/V2N AI SDK</a>.
        </span>
      </div>
      <ol>
        <h5 id="step7-1a">
          <li type="A">Install Necessary Software<br></li>
        </h5>
        As explained in <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step2" target="_blank" rel="noopener noreferrer">Necessary Software of Getting Started Step 2</a>, make sure that <code>bmap-tools</code> is installed on Linux PC.<br>
        If you have not installed the <code>bmap-tools</code>, install it using following command on Host PC (Not in the docker container).<br>
{% highlight shell %}
sudo apt install bmap-tools
{% endhighlight %}
        <br>
        <h5 id="step7-1b">
          <li type="A">Write the Linux files to SD card</li>
        </h5>
        <div class="ContenteSD contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          Run the below command to decompress <code>${WORK}/board_setup/eSD.zip</code>.<br>
{% highlight shell %}
cd ${WORK}/board_setup
unzip eSD.zip
{% endhighlight %}
        Following files are necessary.<br>
        They are in the <code>${WORK}/board_setup/eSD</code> directory.
        </div>
        <div class="pt-0 ps-0 
          cnt_prod cnt_prod-bg cnt_V2L">
          <div class="ContentSPI contentSPI-bg">
            <span class="ContentSPI-title">For QSPI</span>
            Run the below command to decompress <code>${WORK}/board_setup/QSPI.zip</code>.<br>
{% highlight shell %}
cd ${WORK}/board_setup
unzip QSPI.zip
{% endhighlight %}
            <br>
            Following files are necessary.<br>
            They are in the <code>${WORK}/board_setup/QSPI</code> directory.
          </div>
          <table class="gstable mb-0">
            <tr>
              <th>File</th>
              <th>Description</th>
            </tr>
            <tr>
              <td>core-image-weston-smarc-rzv2l.rootfs.wic.bmap</td>
              <td rowspan="2">SD card image</td>
            </tr>
            <tr>
              <td>core-image-weston-smarc-rzv2l.rootfs.wic.gz</td>
            </tr>
          </table>
        </div>
        <div class="pt-0 ps-0 
          cnt_prod cnt_prod-bg cnt_V2H">
          <div class="ContentSPI contentSPI-bg">
            <span class="ContentSPI-title">For xSPI</span>
            Run the below command to decompress <code>${WORK}/board_setup/xSPI.zip</code>.<br>
{% highlight shell %}
cd ${WORK}/board_setup
unzip xSPI.zip
{% endhighlight %}
            <br>
            Following files are necessary.<br>
            They are in the <code>${WORK}/board_setup/xSPI</code> directory.
          </div>
          <table class="gstable mb-0">
            <tr>
              <th>File</th>
              <th>Description</th>
            </tr>
            <tr>
              <td>core-image-weston-rzv2h-evk.rootfs.wic.bmap</td>
              <td rowspan="2">SD card image</td>
            </tr>
            <tr>
              <td>core-image-weston-rzv2h-evk.rootfs.wic.gz</td>
            </tr>
          </table>
        </div>
        <div class="pt-0 ps-0 
          cnt_prod cnt_prod-bg cnt_V2N">
          <div class="ContentSPI contentSPI-bg">
            <span class="ContentSPI-title">For xSPI</span>
            Run the below command to decompress <code>${WORK}/board_setup/xSPI.zip</code>.<br>
{% highlight shell %}
cd ${WORK}/board_setup
unzip xSPI.zip
{% endhighlight %}
          <br>
          Following files are necessary.<br>
          They are in the <code>${WORK}/board_setup/xSPI</code> directory.
          </div>
          <table class="gstable mb-0">
            <tr>
              <th>File</th>
              <th>Description</th>
            </tr>
            <tr>
              <td>core-image-weston-rzv2n-evk.rootfs.wic.bmap</td>
              <td rowspan="2">SD card image</td>
            </tr>
            <tr>
              <td>core-image-weston-rzv2n-evk.rootfs.wic.gz</td>
            </tr>
          </table>
        </div>
        <!-- <div class="cnt_prod cnt_prod-bg cnt_V2L">
          <table class="gstable mb-0">
            <tr>
              <th>File</th>
              <th>Description</th>
            </tr>
            <tr>
              <td>core-image-weston-smarc-rzv2l.rootfs.wic.bmap</td>
              <td rowspan="2">SD card image</td>
            </tr>
            <tr>
              <td>core-image-weston-smarc-rzv2l.rootfs.wic.gz</td>
            </tr>
          </table>
        </div>
        <div class="cnt_prod cnt_prod-bg cnt_V2H">
          <table class="gstable mb-0">
            <tr>
              <th>File</th>
              <th>Description</th>
            </tr>
            <tr>
              <td>core-image-weston-rzv2h-evk.rootfs.wic.bmap</td>
              <td rowspan="2">SD card image</td>
            </tr>
            <tr>
              <td>core-image-weston-rzv2h-evk.rootfs.wic.gz</td>
            </tr>
          </table>
        </div>
        <div class="cnt_prod cnt_prod-bg cnt_V2N">
          <table class="gstable mb-0">
            <tr>
              <th>File</th>
              <th>Description</th>
            </tr>
            <tr>
              <td>core-image-weston-rzv2n-evk.rootfs.wic.bmap</td>
              <td rowspan="2">SD card image</td>
            </tr>
            <tr>
              <td>core-image-weston-rzv2n-evk.rootfs.wic.gz</td>
            </tr>
          </table>
        </div> -->
        Follow the instruction below to prepare the microSD card.<br>
        <ol>
          <li>Before inserting the microSD card to your Linux PC, open the terminal on Linux PC and run the following command to check the devices without microSD card.<br>
{% highlight shell %}
lsblk
{% endhighlight %}
            Following is the example output.<br>
{% highlight shell %}
NAME MAJ:MIN RM SIZE RO TYPE MOUNTPOINT
sda 8:0 0 30.9G 0 disk
├─sda1 8:1 0 512M 0 part /boot/efi
├─sda2 8:2 0 1K 0 part
└─sda5 8:5 0 30.3G 0 part /
sr0 11:0 1 1024M 0 rom
{% endhighlight %}
          </li><br>
          <li>Insert the microSD card to your Linux PC and run the following command again.<br>
{% highlight shell %}
lsblk
{% endhighlight %}
          </li><br>
          <li>Check the output and confirm the name appeared. This would be your microSD card device name.<br>
            <ul>
              <li>Following is the example output.<br>
{% highlight shell %}
NAME MAJ:MIN RM SIZE RO TYPE MOUNTPOINT
sda 8:0 0 30.9G 0 disk
├─sda1 8:1 0 512M 0 part /boot/efi
├─sda2 8:2 0 1K 0 part
└─sda5 8:5 0 30.3G 0 part /
sdb 8:16 1 29.7G 0 disk
└─sdb1 8:17 1 29.7G 0 part
sr0 11:0 1 1024M 0 rom
{% endhighlight %}
              </li><br>
              <li>In this case, followings are your microSD card configuration.
                <ul>
                  <li><b><code>/dev/sdb</code></b>: The device name for the entire microSD card.
                  </li>
                  <li><b><code>/dev/sdb1</code></b>: The partition name in microSD card.  There may be multiple <code>sdb*</code> depending on the microSD card.
                  </li>
                </ul>
                <div class="warning">
                  <span class="warning-title">Warning</span>
                  Be careful not to use the name of other device since it may destruct your computer filesystem.
                </div>
              </li>
            </ul>
          </li><br>
          <li>To use bmaptools, microSD card partitions must be unmounted.<br>
            Run the following command to check the automatically mounted microSD card partitions.<br>
{% highlight shell %}
df -h
{% endhighlight %}
          </li>
          <li>
            Check the output and find the mount point, which is "<code>/media/user/9016-4EF8</code>" in the following example.
{% highlight shell%}
Filesystem      Size  Used Avail Use% Mounted on
:
snip
:
/dev/sdb1        15G   32K   15G   1% /media/user/9016-4EF8
{% endhighlight %}
            <div class="warning">
              <span class="warning-title">Warning</span>
              Here, we use "<b><code>/dev/sdb</code></b>" as microSD card device name.
            </div>
          </li>
          <li>
            Unmount the automatically mounted partitions.
{% highlight shell%}
sudo umount /media/user/9016-4EF8
{% endhighlight %}
            <div class="note">
              <span class="note-title">Note</span>
              If there are more than one partitions on microSD card, unmount all partitions.
            </div>
          </li>
          <li>Run the following command to write SD card image.<br>
            <div class="cnt_prod cnt_prod-bg cnt_V2L">
              <div class="ContenteSD contenteSD-bg">
                <span class="ContenteSD-title">For eSD</span>
{% highlight shell %}
cd ${WORK}/board_setup/eSD
sudo bmaptool copy --bmap core-image-weston-smarc-rzv2l.rootfs.wic.bmap core-image-weston-smarc-rzv2l.rootfs.wic.gz /dev/sdb
{% endhighlight %}
              </div>
              <div class="ContentSPI contentSPI-bg">
                <span class="ContentSPI-title">For xSPI</span>
{% highlight shell %}
cd ${WORK}/board_setup/QSPI
sudo bmaptool copy --bmap core-image-weston-smarc-rzv2l.rootfs.wic.bmap core-image-weston-smarc-rzv2l.rootfs.wic.gz /dev/sdb
{% endhighlight %}
              </div>
            </div>
            <div class="cnt_prod cnt_prod-bg cnt_V2H">
              <div class="ContenteSD contenteSD-bg">
                <span class="ContenteSD-title">For eSD</span>
{% highlight shell %}
cd ${WORK}/board_setup/eSD
sudo bmaptool copy --bmap core-image-weston-rzv2h-evk.rootfs.wic.bmap core-image-weston-rzv2h-evk.rootfs.wic.gz /dev/sdb
{% endhighlight %}
              </div>
              <div class="ContentSPI contentSPI-bg">
                <span class="ContentSPI-title">For xSPI</span>
{% highlight shell %}
cd ${WORK}/board_setup/xSPI
sudo bmaptool copy --bmap core-image-weston-rzv2h-evk.rootfs.wic.bmap core-image-weston-rzv2h-evk.rootfs.wic.gz /dev/sdb
{% endhighlight %}
              </div>
            </div>
            <div class="cnt_prod cnt_prod-bg cnt_V2N">
              <div class="ContenteSD contenteSD-bg">
                <span class="ContenteSD-title">For eSD</span>
{% highlight shell %}
cd ${WORK}/board_setup/eSD
sudo bmaptool copy --bmap core-image-weston-rzv2n-evk.rootfs.wic.bmap core-image-weston-rzv2n-evk.rootfs.wic.gz /dev/sdb
{% endhighlight %}
              </div>
              <div class="ContentSPI contentSPI-bg">
                <span class="ContentSPI-title">For xSPI</span>
{% highlight shell %}
cd ${WORK}/board_setup/xSPI
sudo bmaptool copy --bmap core-image-weston-rzv2n-evk.rootfs.wic.bmap core-image-weston-rzv2n-evk.rootfs.wic.gz /dev/sdb
{% endhighlight %}
              </div>
            </div>
            <div class="warning">
              <span class="warning-title">Warning</span>
              Change <code>/dev/sdb</code> to your microSD card device name.<br>
            </div>
          </li>
          <li>
            Eject microSD card and insert it again to mount the partitions.<br><br>
          </li>
          <li>
            Run the following command to check two partitions are created on microSD card.<br>
{% highlight shell %}
df -h
{% endhighlight %}
            <ul>
              <li>
                If the command shows following log, two partitions are created on microSD card successfully.<br>
                <div class="cnt_prod cnt_prod-bg cnt_V2L">
{% highlight shell %}
Filesystem      Size  Used Avail Use% Mounted on
:
snip
:
/dev/sdb1        24M  8.2M   16M  35% /media/user/bootloader
/dev/sdb2        12G  2.1G  8.4G  20% /media/user/root
{% endhighlight %}
                </div>
                <div class="cnt_prod cnt_prod-bg cnt_V2H">
{% highlight shell %}
Filesystem      Size  Used Avail Use% Mounted on
:
snip
:
/dev/sdb1        20M  5.5M   15M  28% /media/user/bootloader
/dev/sdb2        11G  2.0G  8.4G  20% /media/user/root
{% endhighlight %}
                </div>
                <div class="cnt_prod cnt_prod-bg cnt_V2N">
{% highlight shell %}
Filesystem      Size  Used Avail Use% Mounted on
:
snip
:
/dev/sdb1        18M  3.9M   15M   22% /media/user/bootloader
/dev/sdb2        12G  2.4G   8.9G  22% /media/user/root
{% endhighlight %}
                </div>
                <div class="warning">
                  <span class="warning-title">Warning</span>
                  Here, we use "<b><code>/dev/sdb</code></b>" as microSD card device name.
                </div>
              </li>
            </ul>
          </li>
          <div class="note">
            <span class="note-title">Note</span>
            If you would like to eject the microSD card, please run following command and remove the microSD card from Linux PC.
            <br>
{% highlight shell %}
sudo eject /dev/sdb
{% endhighlight %}
            <div class="warning">
              <span class="warning-title">Warning</span>
              Change <code>/dev/sdb</code> to your microSD card device name.<br>
            </div>
          </div>
        </ol>
        <h5 id="step7-1c">
          <span class="ContentSPI">
          <li type="A">
            Write the bootloaders to Flash ROM
          </li>
          </span>
        </h5>
        <div class="pt-0 ps-0 
          cnt_prod cnt_prod-bg cnt_V2L">
          <div class="ContentSPI">
            <div class="contentSPI-bg">
            <span class="ContentSPI-title">For QSPI</span>
            Please write the bootloaders to Flash ROM on the board according to <a href="{{ site.url }}{{ site.baseurl }}{% link dev_guide.md %}#D2" target="_blank" rel="noopener noreferrer">D2.How to boot from QSPI</a>.
          </div>
        </div>
        </div>
        <div class="pt-0 ps-0 
          cnt_prod cnt_prod-bg cnt_V2H">
          <div class="ContentSPI">
            <div class="contentSPI-bg">
              <span class="ContentSPI-title">For xSPI</span>
              Please write the bootloaders to Flash ROM on the board according to <a href="{{ site.url }}{{ site.baseurl }}{% link dev_guide.md %}#D3" target="_blank" rel="noopener noreferrer">D3.How to boot from xSPI</a>.
            </div>
          </div>
        </div>
        <div class="pt-0 ps-0 
          cnt_prod cnt_prod-bg cnt_V2N">
          <div class="ContentSPI">
            <div class="contentSPI-bg">
              <span class="ContentSPI-title">For xSPI</span>
              Please write the bootloaders to Flash ROM on the board according to <a href="{{ site.url }}{{ site.baseurl }}{% link dev_guide.md %}#D3" target="_blank" rel="noopener noreferrer">D3.How to boot from xSPI</a>.
            </div>
          </div>
        </div>
      </ol>
      <br>
      <h4 id="step7-2" class="u_line">2. Deploy Application to the Board</h4>
      This section explains how to copy the <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step6" target="_blank" rel="noopener noreferrer">application binary created in Getting Started Step 6</a> to the board.<br>
      Users are expected to have finished the instructions in <a href="#step7" target="_blank" rel="noopener noreferrer"> Setup the Board in Step 7-1</a>.
      <br>
      <br>
      <div class="mt-2 select_btn select_product">
        <a class="btn_prod 
            btn_V2L
            btn_prod-Active" 
            data-id="V2L">
            RZ/V2L
        </a>
        <a class="
            btn_prod 
            btn_V2H" 
            data-id="V2H">
            RZ/V2H
        </a>
        <a class="
            btn_prod 
            btn_V2N" 
            data-id="V2N">
            RZ/V2N
        </a>
      </div>
      <ol>
        <li>
          Insert the microSD card to Linux PC.
        </li><br>
        <li>
          Run the following command to mount the partition 2, which contains the root filesystem.<br>
{% highlight shell %}
sudo mkdir /mnt/sd -p
sudo mount /dev/sdb2 /mnt/sd
{% endhighlight %}
          <div class="warning">
            <span class="warning-title">Warning</span>
            Change <code>/dev/sdb</code> to your microSD card device name.<br>
          </div>
        </li>
        <li>
          Create the application directory on root filesystem.
{% highlight shell %}
sudo mkdir /mnt/sd/home/weston/tvm
{% endhighlight %}
          <div class="note">
            <span class="note-title">Note</span>
            Directory name <code>tvm</code> can be determined by user.<br>
          </div>
        </li>
        <li>
          Copy the necessary files in execution environment.<br>
          <div class="cnt_prod cnt_V2L">
            Select the appropriate option below based on the application type explained in <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#build-instruction" target="_blank" rel="noopener noreferrer"> Getting Started Step 6</a>.
            <br><br>
            <p id="deploy-option1"><b>Option 1: &lt;Application 1&gt;</b></p>
          </div>
          Check the <code>README.md</code> document provided in application directory and follow the instruction in the chapter called <b>"Application: Deploy Stage"</b> (or similar) to deploy the application.
          <br><br>
          <!--
          <div class="cnt_prod cnt_prod-bg cnt_V2N">
           <div class="note">
            <span class="note-title">Note</span>
            Since RZ/V2N is a brother chip of RZ/V2H, users can use the AI Application for RZ/V2H on the RZ/V2N EVK.<br>
            Please use source code and object files for RZ/V2H, and follow the steps <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v7.10/R01_object_detection#application-build-stage" target="_blank" rel="noopener noreferrer">Application: Build Stage</a> to build the application in the RZ/V2N AI SDK environment.
          </div>
          </div> -->
          <div class="box1">
            <u><b>Example:</b></u><br>
            For R01_object_detection application, follow the instruction in <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v7.10/R01_object_detection#application-deploy-stage" target="_blank" rel="noopener noreferrer">README > Application: Deploy Stage</a> to find files to be copied.
          </div>
          <br>
          Use the following command to copy the files to root filesystem.
          <br>
{% highlight shell %}
sudo cp $WORK/ai_sdk_setup/data/<Path to target file>/<filename> /mnt/sd/home/weston/tvm 
{% endhighlight %}
          <br>
          <div class="cnt_prod cnt_prod-bg cnt_V2L">
            <p id="deploy-option2"><b>Option 2: &lt;Application 2&gt;</b></p>
            Run the following command to copy the whole repository to the root filesystem.
            <br>
{% highlight shell %}
sudo cp $WORK/ai_sdk_setup/data/<Path to repository>/RZV2L_AiLibrary /mnt/sd/home/weston/tvm -r
{% endhighlight %}
          </div>
        </li>
        <li>
          Run the following command to sync the data with memory.
          <br>
{% highlight shell %}
sync 
{% endhighlight %}
        </li>
        <li>
          Run the following command to unmount the partition 2.
          <br>
{% highlight shell %}
sudo umount /mnt/sd
{% endhighlight %}
        </li>
        <li>
          Eject the microSD card by running the following command and remove the microSD card from Linux PC.<br>
{% highlight shell %}
sudo eject /dev/sdb
{% endhighlight %}
          <div class="warning">
            <span class="warning-title">Warning</span>
            Change <code>/dev/sdb</code> to your microSD card device name.<br>
          </div>
        </li>
      </ol>
      <br>
      <h4 id="step7-3" class="u_line">3. Boot the Board</h4>
      This section explains how to boot the target board.<br>
      <div class="mt-2 select_btn select_product">
        <a class="btn_prod 
            btn_V2L
            btn_prod-Active" 
            data-id="V2L">
            RZ/V2L
        </a>
        <a class="
            btn_prod 
            btn_V2H" 
            data-id="V2H">
            RZ/V2H
        </a>
        <a class="
            btn_prod 
            btn_V2N" 
            data-id="V2N">
            RZ/V2N
        </a>
      </div>
      <div class="mb-0 cnt_prod cnt_prod-bg cnt_V2N">
        <div class="note mb-0">
          <span class="note-title">Requirement</span>
          The included SD card sub board must be attached on the RZ/V2N EVK.<br>
          For the RZ/V2N EVK, see <a href="https://www.renesas.com/products/microcontrollers-microprocessors/rz-mpus/rzv2n-evk-rzv2n-quad-core-vision-ai-mpu-evaluation-kit" target="_blank" rel="noopener noreferrer">RZ/V2N Evaluation Board Kit Hardware Manual</a>.
        </div>
      </div>
      <br>
      <div class="select_btn SelectButton">
        <a class="btn_bl ButtoneSD">eSD Bootloader</a>
        <a class="btn_bl ButtonSPI">
          <span class="cnt_prod cnt_V2L">
            QSPI 
          </span> 
          <span class="cnt_prod cnt_V2H">
            xSPI 
          </span> 
          <span class="cnt_prod cnt_V2N">
            xSPI 
          </span> 
           Bootloader</a>
      </div>
      <br>
      Follow the instruction below to boot the board.
      <br>
      <div class="cnt_prod cnt_prod-bg cnt_V2L">
        <div class="ContenteSD contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          <reference3>
            <div class="container">
              <div class="row">
                <div class="col-12 col-md-6">
                  <ol>
                    <li>
                      Insert the microSD card to the <b>Board</b>.
                      <div class="note">
                        <span class="note-title">Note</span>
                        Use the microSD card slot <b>CN3</b> as shown in the figure.
                      </div>
                    </li><br>
                    <li>Change SW1 and SW11 setting as shown in the figure.</li><br>
                    <li>Connect the USB mouse and USB keyboard via USB hub.</li><br>
                    <li>Connect the <b>Google Coral camera</b> to the <b>Board</b>.</li><br>
                    <li>Connect the HDMI monitor to the <b>Board</b>.</li><br>
                    <li>Connect the power cable to the <b>Board</b>.</li><br>
                    <li>Press power button for 1 second to turn on the board.</li>
                  </ol>
                </div>
                <div class="col-12 col-md-6">
                  <img class="procedure"  src="img/board_esd.png" alt="boot" width="90%"/>
                </div>
              </div>  
              <div class="row">
                <div class="col-12 col-md-6">
                  <ol>
                    <li value = "8">After the boot-up, following screen will be displayed on HDMI monitor.</li>
                  </ol>
                </div>
                <div class="col-12 col-md-6">
                  <img class="procedure"  src="img/wayland.jpg" alt="wayland" width="90%" />
                </div>
              </div>
              <div class="row">
                <div class=" col-12 col-md-6">
                  <ol>
                    <li value = "9">Click the icon at the top-left corner to open the terminal.</li>
                  </ol>
                </div>
                <div class=" col-12 col-md-6">
                  <img class="procedure"  src="img/wayland_terminal.jpg" alt="wayland" width="90%" />
                </div>
              </div>
            </div>
          </reference3>
        </div>
        <div class="ContentSPI contentSPI-bg">
          <span class="ContentSPI-title">For QSPI</span>
          <div class="note">
            <span class="note-title">Note</span>
            After bootloader is written and U-boot setting is changed, terminal emulator is no longer needed.<br>
            Users can detach the serial port connection.<br>
          </div>
          <div class="container">
            <div class="row">
              <div class="col-12 col-md-6">
                <ol>
                  <li>
                    Insert the microSD card to the <b>Board</b>.
                    <div class="note">
                      <span class="note-title">Note</span>
                      Use the microSD card slot <b>CN10</b> as shown in the figure.
                    </div>
                  </li><br>
                  <li>Change SW1 and SW11 setting as shown in the figure.</li><br>
                  <li>Connect the USB mouse and USB keyboard via USB hub.</li><br>
                  <li>Connect the <b>Google Coral camera</b> to the <b>Board</b>.</li><br>
                  <li>Connect the HDMI monitor to the <b>Board</b>.</li><br>
                  <li>Connect the power cable to the <b>Board</b>.</li><br>
                  <li>Press power button for 1 second to turn on the board.</li>
                </ol>
              </div>
              <div class="col-12 col-md-6">
                <img class="procedure"  src="img/board_boot_emmc.png" alt="boot" width="90%"/>
              </div>
            </div>  
            <div class="row">
              <div class="col-12 col-md-6">
                <ol>
                  <li value = "8">After the boot-up, following screen will be displayed on HDMI monitor.</li>
                </ol>
              </div>
              <div class="col-12 col-md-6">
                <img class="procedure"  src="img/wayland.jpg" alt="wayland" width="90%" />
              </div>
            </div>
            <div class="row">
              <div class=" col-12 col-md-6">
                <ol>
                  <li value = "9">Click the icon at the top-left corner to open the terminal.</li>
                </ol>
              </div>
              <div class=" col-12 col-md-6">
                <img class="procedure"  src="img/wayland_terminal.jpg" alt="wayland" width="90%" />
              </div>
            </div>
          </div>
        </div>
      </div>
      <div class="cnt_prod cnt_prod-bg cnt_V2H">
        <div class="ContenteSD contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          <div class="container">
            <div class="row">
              <div class="col-12 col-md-6">
                <ol>
                  <li>
                    Insert the microSD card to the <b>Board</b>.
                    <div class="note">
                      <span class="note-title">Note</span>
                      Use the microSD card slot <b>SD1</b> on the <b>Board</b> as shown in the figure.
                    </div>
                  </li><br>
                  <li>Change DSW1 and DSW2 setting as shown in the figure.</li><br>
                  <li>Connect the USB mouse and USB keyboard and USB camera via USB hub.<br>
                    <div class="note">
                      <span class="note-title">Note</span>
                      There are USB 2.0 port and USB 3.0 port on RZ/V2H EVK.<br>
                      Please connect your USB camera to appropriate port according to its requirement.<br>
                      Here, USB camera is connected to USB 2.0 via USB hub.<br>
                    </div>
                  </li><br>
                  <li>Connect the HDMI monitor to the <b>Board</b>.</li><br>
                  <li>Connect the power cable to the <b>Board</b>.</li><br>
                  <li>Turn the SW3 to ON.</li><br>
                  <li>Turn the SW2 to ON to power on the <b>Board</b></li>
                </ol>
              </div>
              <div class="col-12 col-md-6">
                <a href="img/v2h_evk_boot.png" data-lightbox="group"><img class="procedure" src="img/v2h_evk_boot.png" alt="boot" width="90%"/></a>
              </div>
            </div>  
            <div class="row">
              <div class="col-12 col-md-6">
                <ol>
                  <li value = "8">After the boot-up, following screen will be displayed on HDMI monitor.</li>
                </ol>
              </div>
              <div class="col-12 col-md-6">
                <img class="procedure"  src="img/wayland.jpg" alt="wayland" width="90%" />
              </div>
            </div>
            <div class="row">
              <div class=" col-12 col-md-6">
                <ol>
                  <li value = "9">Click the icon at the top-left corner to open the terminal.</li>
                </ol>
              </div>
              <div class=" col-12 col-md-6">
                <img class="procedure"  src="img/v2h_evk_wayland.png" alt="wayland" width="90%" />
              </div>
            </div>
          </div>
        </div>
        <div class="ContentSPI contentSPI-bg">
          <span class="ContentSPI-title">For xSPI</span>
          <div class="note">
            <span class="note-title">Note</span>
            After bootloader is written and U-boot setting is changed, terminal emulator is no longer needed.<br>
            Users can detach the serial port connection.<br>
          </div>
          <div class="container">
            <div class="row">
              <div class="col-12 col-md-6">
                <ol>
                  <li>
                    Insert the microSD card to the <b>Board</b>.
                    <div class="note">
                      <span class="note-title">Note</span>
                      Use the microSD card slot <b>SD2</b> on the <b>Board</b> as shown in the figure.
                    </div>
                  </li><br>
                  <li>Change DSW1 and DSW2 setting as shown in the figure.</li><br>
                  <li>Connect the USB mouse and USB keyboard and USB camera via USB hub.<br>
                    <div class="note">
                      <span class="note-title">Note</span>
                      There are USB 2.0 port and USB 3.0 port on RZ/V2H EVK.<br>
                      Please connect your USB camera to appropriate port according to its requirement.<br>
                      Here, USB camera is connected to USB 2.0 via USB hub.<br>
                    </div>
                  </li><br>
                  <li>Connect the HDMI monitor to the <b>Board</b>.</li><br>
                  <li>Connect the power cable to the <b>Board</b>.</li><br>
                  <li>Turn the SW3 to ON.</li><br>
                  <li>Turn the SW2 to ON to power on the <b>Board</b></li>
                </ol>
              </div>
              <div class="col-12 col-md-6">
                <a href="img/v2h_evk_boot_spi.png" data-lightbox="group"><img class="procedure" src="img/v2h_evk_boot_spi.png" alt="boot" width="90%"/></a>
              </div>
            </div>  
            <div class="row">
              <div class="col-12 col-md-6">
                <ol>
                  <li value = "8">After the boot-up, following screen will be displayed on HDMI monitor.</li>
                </ol>
              </div>
              <div class="col-12 col-md-6">
                <img class="procedure"  src="img/wayland.jpg" alt="wayland" width="90%" />
              </div>
            </div>
            <div class="row">
              <div class=" col-12 col-md-6">
                <ol>
                  <li value = "9">Click the icon at the top-left corner to open the terminal.</li>
                </ol>
              </div>
              <div class=" col-12 col-md-6">
                <img class="procedure"  src="img/v2h_evk_wayland.png" alt="wayland" width="90%" />
              </div>
            </div>
          </div>
        </div>
      </div>
      <div class="cnt_prod cnt_prod-bg cnt_V2N">
        <div class="ContenteSD contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          <div class="container">
            <div class="row">
              <div class="col-12 select_btn select_board mb-2">
                <h6 class="mb-2" style="color: #2a289d;"><b>Click the board name.</b></h6>
                <a class="btn_board 
                    btn_V2N_EVK
                    btn_board-Active" 
                    data-id="V2N_EVK">
                    RZ/V2N EVK
                </a>
                <a class="btn_board 
                    btn_V2N_FPB" 
                    data-id="V2N_FPB">
                    FPB-RZV2N
                </a>
              </div>
              <div class="col-12 col-md-6">
                <ol>
                  <li>
                    Insert the microSD card to the <b>Board</b>.
                    <div class="note">
                      <span class="note-title">Note</span>
                      <span class="cnt_bd cnt_V2N_EVK" >
                        Use the microSD card slot <b>SD1</b> on the <b>Board</b> as shown in the figure.
                      </span>
                      <span class="cnt_bd cnt_V2N_FPB" >
                        Use the microSD card slot on the <b>back</b> of the <b>Board</b> as shown in the figure.
                      </span>
                    </div>
                  </li><br>
                  <li><b>[EVK only]</b>Change DSW1 and DSW2 setting as shown in the figure.</li><br>
                  <li>Connect the USB mouse and USB keyboard and USB camera via USB hub.<br>
                    <div class="mb-0 cnt_bd cnt_V2N_EVK" >
                      <div class="note">
                        <span class="note-title">Note</span>
                        There are USB 2.0 port and USB 3.0 port on RZ/V2N EVK.<br>
                        Please connect your USB camera to appropriate port according to its requirement.<br>
                        Here, USB camera is connected to USB 3.0 via USB hub.<br>
                      </div>
                    </div>
                  </li><br>
                  <li>Connect the HDMI monitor to the <b>Board</b>.</li><br>
                  <li>Connect the power cable to the <b>Board</b>.</li><br>
                  <li><b>[EVK only]</b>Turn the SW3 to ON.</li><br>
                  <li>Turn the SW2 to ON to power on the <b>Board</b></li>
                </ol>
              </div>
              <div class="col-12 col-md-6">
                <div class="col-12 mb-0 cnt_bd cnt_V2N_EVK" >
                  <a href="img/v2n_evk_boot_esd.png" data-lightbox="group">
                    <img class="procedure" src="img/v2n_evk_boot_esd.png" alt="boot" width="45%"/>
                  </a>
                  <a href="img/v2n_evkv2_boot_esd.png" data-lightbox="group">
                    <img class="procedure" src="img/v2n_evkv2_boot_esd.png" alt="boot" width="45%"/>
                  </a>
                </div>
                <div class="col-12 mb-0 cnt_bd cnt_V2N_FPB" >
                  <a href="img/v2n_fpb_boot.jpg" data-lightbox="group">
                    <img class="procedure" src="img/v2n_fpb_boot.jpg" alt="boot" width="90%"/>
                  </a>
                </div>
              </div>
            </div>  
            <div class="row">
              <div class="col-12 col-md-6">
                <ol>
                  <li value = "8">After the boot-up, following screen will be displayed on HDMI monitor.</li>
                </ol>
              </div>
              <div class="col-12 col-md-6">
                <img class="procedure"  src="img/wayland.jpg" alt="wayland" width="90%" />
              </div>
            </div>
            <div class="row">
              <div class=" col-12 col-md-6">
                <ol>
                  <li value = "9">Click the icon at the top-left corner to open the terminal.</li>
                </ol>
              </div>
              <div class=" col-12 col-md-6">
                <img class="procedure"  src="img/v2h_evk_wayland.png" alt="wayland" width="90%" />
              </div>
            </div>
          </div>
        </div>
        <div class="ContentSPI contentSPI-bg">
          <span class="ContentSPI-title">For xSPI</span>
          <div class="note">
            <span class="note-title">Note</span>
            After bootloader is written and U-boot setting is changed, terminal emulator is no longer needed.<br>
            Users can detach the serial port connection.<br>
          </div>
          <div class="container">
            <div class="row">
              <div class="col-12 col-md-6">
                <ol>
                  <li>
                    Insert the microSD card to the <b>Board</b>.
                    <div class="note">
                      <span class="note-title">Note</span>
                      Use the microSD card slot <b>SD2</b> on the <b>Board</b> as shown in the figure.
                    </div>
                  </li><br>
                  <li> Change DSW1 and DSW2 setting as shown in the figure.</li><br>
                  <li>Connect the USB mouse and USB keyboard and USB camera via USB hub.<br>
                    <div class="note">
                      <span class="note-title">Note</span>
                      There are USB 2.0 port and USB 3.0 port on RZ/V2N EVK.<br>
                      Please connect your USB camera to appropriate port according to its requirement.<br>
                      Here, USB camera is connected to USB 3.0 via USB hub.<br>
                    </div>
                  </li><br>
                  <li>Connect the HDMI monitor to the <b>Board</b>.</li><br>
                  <li>Connect the power cable to the <b>Board</b>.</li><br>
                  <li>Turn the SW3 to ON.</li><br>
                  <li>Turn the SW2 to ON to power on the <b>Board</b></li>
                </ol>
              </div>
                <div class="col-6" style="margin-top:40px;">
                  <div class="row">
                    <div class="col-6 text-center">
                      <a href="img/v2n_evk_boot_spi.png" data-lightbox="group">
                        <img class="procedure" src="img/v2n_evk_boot_spi.png" alt="Image 1" width="100%" />
                      </a>
                    </div>
                    <div class="col-6 text-center">
                      <a href="img/v2n_evkv2_boot_spi.png" data-lightbox="group">
                        <img class="procedure" src="img/v2n_evkv2_boot_spi.png" alt="Image 2" width="100%" />
                      </a>
                    </div>
                  </div>
                </div>
            </div>  
            <div class="row">
              <div class="col-12 col-md-6">
                <ol>
                  <li value = "8">After the boot-up, following screen will be displayed on HDMI monitor.</li>
                </ol>
              </div>
              <div class="col-12 col-md-6">
                <img class="procedure"  src="img/wayland.jpg" alt="wayland" width="90%" />
              </div>
            </div>
            <div class="row">
              <div class=" col-12 col-md-6">
                <ol>
                  <li value = "9">Click the icon at the top-left corner to open the terminal.</li>
                </ol>
              </div>
              <div class=" col-12 col-md-6">
                <img class="procedure"  src="img/v2h_evk_wayland.png" alt="wayland" width="90%" />
              </div>
            </div>
          </div>
        </div>
      </div>
      <p class="mb-1">After Step 7, users should have completed followings.
      <ul>
        <li>Setup miroSD card.</li>
        <li>Deploy the application on miroSD card.</li>
        <li>Boot the board.</li>
      </ul>
      </p>
    </div>
  </div>
</div>
<br>
<br>
<div class="container">
  <div class="row">
    <div class="col-12">
      <h3 id="step8" >Step 8: Run AI Application</h3>
      This section explains how to run the AI Application.
      <br>
      <br>
      <div class="select_btn select_product">
        <a class="btn_prod 
            btn_V2L
            btn_prod-Active" 
            data-id="V2L">
            RZ/V2L
        </a>
        <a class="
            btn_prod 
            btn_V2H" 
            data-id="V2H">
            RZ/V2H
        </a>
        <a class="
            btn_prod 
            btn_V2N" 
            data-id="V2N">
            RZ/V2N
        </a>
      </div>
      <ol>
        <li>
          Follow the instructions explained in the document (<code>README.md</code>) of applications on GitHub.
          <br><br>
          <div class="box1">
            <u><b>Example:</b></u><br>
            For R01_object_detection application, follow the instruction in <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v7.10/R01_object_detection#application-run-stage" target="_blank" rel="noopener noreferrer">README > Application: Run Stage</a> to run the application.
            <br>
            <!-- <span class="cnt_prod cnt_V2N">
              Users can use the AI Application for RZ/V2H on the RZ/V2N Board.<br>
              Please use source code and object files for RZ/V2H, and follow the steps <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v7.10/R01_object_detection#application-build-stage" target="_blank" rel="noopener noreferrer">Application: Build Stage</a> to build the application in the RZ/V2N AI SDK environment.
              <br>
            </span> -->
            If you have successfully run the application, you will see following window on HDMI screen.
            <br><br>
            <div class="cnt_prod cnt_prod-bg cnt_V2L">
              <img src="img/objectdetection.png" alt="object_detection" width="90%"/>
            </div>
            <div class="cnt_prod cnt_prod-bg cnt_V2H">
              <img src="img/objectdetection_v2h.png" alt="object_detection" width="90%"/>
            </div>
            <div class="cnt_prod cnt_prod-bg cnt_V2N">
              <img src="img/objectdetection_v2n.png" alt="object_detection" width="90%"/>
            </div>
          </div>
          <br>
        </li>
      </ol>
      <div class="note">
        <!-- <span class="note-title">Note2</span> -->
        <span class="note-title">Note1</span>
        When running an AI Application, the following warning may be shown. It does not affect the operation.<br>
        <h6 class="mb-1">
{% highlight shell %}
[ WARN:0@xx.xxx] global cap_gstreamer.cpp:1777 open OpenCV | GStreamer warning: Cannot query video position: status=0, value=-1, duration=-1
{% endhighlight %}
        </h6>
      </div>
    </div>
<br>
<br>
<br>
<div class="container">
  <div class="row">
    <div class="col-12">
      <h3 id="step9" >Step 9: Shutdown the Board</h3>
      This section explains how to shutdown the target board.
      <br>
      <br>
      <div class="select_btn select_product">
        <a class="btn_prod 
            btn_V2L
            btn_prod-Active" 
            data-id="V2L">
            RZ/V2L
        </a>
        <a class="
            btn_prod 
            btn_V2H" 
            data-id="V2H">
            RZ/V2H
        </a>
        <a class="
            btn_prod 
            btn_V2N" 
            data-id="V2N">
            RZ/V2N
        </a>
      </div>
      <div class="cnt_prod cnt_prod-bg cnt_V2L">
        To power-off the RZ/V2L EVK, follow the procedures below.
        <br><br>
        <a3reference>
          <ol>
            <li>Run the <code>shutdown</code> command on board console.
              <br>
{% highlight shell %}
sudo -i shutdown -h now
{% endhighlight %}
            <br>
            </li>
            <li>On the screen, check that shutdown procedure runs and the HDMI display is blacked out.
              <br><br>
            </li>
            <li>Press and hold the power button for 2 seconds.
              <br><br>
              <img src="img/board_power.png" alt="board" width="350px" /><br>
            </li>
          </ol>
        </a3reference>
      </div>
      <div class="cnt_prod cnt_prod-bg cnt_V2H">
        To power-off the RZ/V2H EVK, follow the procedures below.
        <br><br>
        <a4reference>
        <ol>
          <li>Run the <code>shutdown</code> command on board console.
            <br>
{% highlight shell %}
sudo -i shutdown -h now
{% endhighlight %}
            <br>
          </li>
          <li>
            On the screen, check that shutdown procedure runs and the HDMI display is blacked out.
            <br><br>
          </li>
          <li>
            Turn SW2 to OFF.
            <br><br>
          </li>
          <li>
            Turn SW3 to OFF.
            <br><br>
            <img src="img/v2h_evk_shutdown.png" alt="board" width="350px" /><br>
          </li>
        </ol>
        </a4reference>
      </div>
      <div class="cnt_prod cnt_prod-bg cnt_V2N">
        To power-off the RZ/V2N Board, follow the procedures below.
        <br>
        <div class="col-12 select_btn select_board mb-2">
          <h6 class="mb-2" style="color: #2a289d;"><b>Click the board name.</b></h6>
          <a class="btn_board 
              btn_V2N_EVK
              btn_board-Active" 
              data-id="V2N_EVK">
              RZ/V2N EVK
          </a>
          <a class="btn_board 
              btn_V2N_FPB" 
              data-id="V2N_FPB">
              FPB-RZV2N
          </a>
        </div>
        <br>
        <ol>
          <li>Run the <code>shutdown</code> command on board console.
            <br>
{% highlight shell %}
sudo -i shutdown -h now
{% endhighlight %}
            <br>
          </li>
          <li>
            On the screen, check that shutdown procedure runs and the HDMI display is blacked out.
            <br><br>
          </li>
          <li>
            Turn SW2 to OFF.
            <br><br>
          </li>
          <div class="col-12 mb-0 cnt_bd cnt_V2N_EVK" >
          <li>
            <b>[EVK only]</b> Turn SW3 to OFF.
            <br><br>
          </li>
          </div>
        </ol>
        <div class="col-12 mb-0 cnt_bd cnt_V2N_EVK" >
          <img src="img/v2n_evk_shutdown.png" alt="board" width="350px" />
        </div>
        <div class="col-12 mb-0 cnt_bd cnt_V2N_FPB" >
          <img src="img/v2n_fpb_shutdown.jpg" alt="board" width="350px" />
        </div>
      </div>
      <br><br>
    </div>
  </div>
</div>

<div class="container">
  <div class="row">
    <div class="col-12">
      <h4 id="ending" class="u_line">
        This is the end of Getting Started.
      </h4>
      You have experienced the AI Application development procedures.<br>
      Next step is to change the application to create your own AI Application.<br>
      You can use the applications listed in <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}" target="_blank" rel="noopener noreferrer">AI Applications</a> to expand your ideas!
      <br><br>
      If you would like to customize Yocto Linux or develop your own board, please change and build the AI SDK Source Code based on your environment.
      <br>
      Please refer to How to Build AI SDK page shown below for more details.<br>
      <div class="cnt_prod cnt_V2L">
        <a class="btn btn-secondary square-button-gray ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk.md %}" role="button" target="_blank" rel="noopener noreferrer">
          <span class="banner-title">How to Build RZ/V2L AI SDK</span>
          <span class="banner-line">
          How can I build RZ/V2L AI SDK Source Code?<br>
          </span>
        </a>
      </div>
      <div class="cnt_prod cnt_V2H">
        <a class="btn btn-secondary square-button-gray ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}" role="button" target="_blank" rel="noopener noreferrer">
          <span class="banner-title">How to Build RZ/V2H AI SDK</span>
          <span class="banner-line">
          How can I build RZ/V2H AI SDK Source Code?<br>
          </span>
        </a>
      </div>
      <div class="cnt_prod cnt_V2N">
        <a class="btn btn-secondary square-button-gray ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2n.md %}" role="button" target="_blank" rel="noopener noreferrer">
          <span class="banner-title">How to Build RZ/V2N AI SDK</span>
          <span class="banner-line">
          How can I build RZ/V2N AI SDK Source Code?<br>
          </span>
        </a>
      </div>
    </div>
  </div>
</div>
<div class="container">
  <div class="row">
    <div class="col-12" align="right">
      <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#page-top" role="button">
Back to Top >
      </a>
    </div>
  </div>
</div>

<style>
</style>
<script>
/************ Read Cookie **************/
/************ Disabled since Cookie support will be considered after Jan, 2024. **************/
/*function GetCookie(key) {
    let value = document.cookie.match(new RegExp(key+'\=([^\;]*)\;*'));
    return value ? value[1] : null;
  }
  let BootType = GetCookie("BootType") || "eSD";
  console.log()*/
let BootType = "eSD";

/************ Select BootType **************/
// function dispBootType() {
//   if(BootType === "eSD") {
//     document.querySelectorAll(".ContenteSD").forEach(elm => elm.style.display="block");
//     document.querySelectorAll(".ContenteMMC").forEach(elm => elm.style.display="none");
//     document.querySelectorAll(".ButtoneSD").forEach(elm => elm.classList.add("ButtoneSD-Active"));
//     document.querySelectorAll(".ButtoneMMC").forEach(elm => elm.classList.remove("ButtoneMMC-Active"));
//   } else {
//     document.querySelectorAll(".ContenteSD").forEach(elm => elm.style.display="none");
//     document.querySelectorAll(".ContenteMMC").forEach(elm => elm.style.display="block");
//     document.querySelectorAll(".ButtoneSD").forEach(elm => elm.classList.remove("ButtoneSD-Active"));
//     document.querySelectorAll(".ButtoneMMC").forEach(elm => elm.classList.add("ButtoneMMC-Active"));
//   }
// }
// document.querySelectorAll(".SelectButton").forEach(elm => {
//   elm.addEventListener("click", ()=>{
//     BootType = (BootType === "eSD") ? "eMMC": "eSD";
//     // document.cookie = `BootType=${BootType};max-age=86400;path=/`;
//     dispBootType();
//   });
// })

/************ Select BootType **************/
function dispBootType() {
  if(BootType === "eSD") {
    document.querySelectorAll(".ContenteSD").forEach(elm => elm.style.display="block");
    document.querySelectorAll(".ContentSPI").forEach(elm => elm.style.display="none");
    document.querySelectorAll(".ButtoneSD").forEach(elm => elm.classList.add("ButtoneSD-Active"));
    document.querySelectorAll(".ButtonSPI").forEach(elm => elm.classList.remove("ButtonSPI-Active"));
  } else {
    document.querySelectorAll(".ContenteSD").forEach(elm => elm.style.display="none");
    document.querySelectorAll(".ContentSPI").forEach(elm => elm.style.display="block");
    document.querySelectorAll(".ButtoneSD").forEach(elm => elm.classList.remove("ButtoneSD-Active"));
    document.querySelectorAll(".ButtonSPI").forEach(elm => elm.classList.add("ButtonSPI-Active"));
  }
}

document.querySelectorAll(".SelectButton").forEach(elm => {
  elm.addEventListener("click", function(){
    save_scroll(this);
    BootType = (BootType === "eSD") ? "SPI": "eSD";
    // document.cookie = `BootType=${BootType};max-age=86400;path=/`;
    dispBootType();
    load_scroll();
  });
})
dispBootType();

function switch_prod(id){
    let class_name = "."+id;
    let button_name = ".btn_"+id;
    let content_name = ".cnt_"+id;
    /*Contents display*/
    document.querySelectorAll(".cnt_prod").forEach(elm => elm.style.display="none");
    document.querySelectorAll(content_name).forEach(elm => 
    {
      if (elm.tagName === 'SPAN') {
        elm.style.display="inline"; 
      } else {
        elm.style.display="block"; 
      }
    });
    /*Button display*/
    document.querySelectorAll(".btn_prod").forEach(elm => elm.classList.remove("btn_prod-Active"));
    document.querySelectorAll(button_name).forEach(elm => elm.classList.add("btn_prod-Active"));
  
    /*table display*/
    document.querySelectorAll('tr[class^="row_"]').forEach(tr => {
    tr.classList.add('hidden');
    });
    let row_name = ".row_"+id;
    document.querySelectorAll(row_name).forEach(tr => {
      tr.classList.remove('hidden');
    });

    sessionStorage.setItem("active-prod", id);
}

function switch_bd(id) {
    let class_name = "."+id;
    let button_name = ".btn_"+id;
    let content_name = ".cnt_"+id;
    document.querySelectorAll(".cnt_bd").forEach(elm => elm.style.display="none");
    document.querySelectorAll(content_name).forEach(elm => 
    {
      if (elm.tagName === 'SPAN') {
        elm.style.display="inline"; 
      } else {
        elm.style.display="block"; 
      }
    });
    document.querySelectorAll(".btn_board").forEach(elm => elm.classList.remove("btn_board-Active"));
    document.querySelectorAll(button_name).forEach(elm => elm.classList.add("btn_board-Active"));

    sessionStorage.setItem("active-v2n-bd", id);
}

/*Scroll variables*/
const select_btn = ".select_btn";
const scroller = document.querySelector("section");

function save_scroll(btn){
  const $btn = $(btn);
  /*Get closest "select_btn" */
  const $container = $btn.closest(select_btn);
  if ($container.length === 0) return;

  /*Find the index number of target select_btn among multiple select_btns. */
  const container = $container[0];
  const containerIndex = $(select_btn).index($container);

  const scrollerRect = scroller.getBoundingClientRect();
  const containerRect = container.getBoundingClientRect();

  // Offset for section_btn in section
  const containerOffset = containerRect.top - scrollerRect.top;

  /*Store current scroll information*/
  sessionStorage.setItem("scrollTop", scroller.scrollTop);
  sessionStorage.setItem("containerIndex", containerIndex);
  sessionStorage.setItem("containerOffset", containerOffset);
}

function load_scroll(){
  /*Restore current old information*/
  const oldScrollTop = sessionStorage.getItem("scrollTop");
  const containerIndex = sessionStorage.getItem("containerIndex");
  const oldContainerOffset = sessionStorage.getItem("containerOffset");

  if (
    oldScrollTop === null ||
    containerIndex === null ||
    oldContainerOffset === null
  ) {
    return;
  }

  const $container = $(select_btn).eq(parseInt(containerIndex, 10));
  if ($container.length === 0) return;

  const container = $container[0];

  // Revert to original scrollTop
  scroller.scrollTop = parseFloat(oldScrollTop);

  requestAnimationFrame(() => {
    const scrollerRect = scroller.getBoundingClientRect();
    const newContainerOffset = container.getBoundingClientRect().top - scrollerRect.top;

    // Scroll adjustment for position dif of select_btn
    const diff = newContainerOffset - parseFloat(oldContainerOffset);
    scroller.scrollTop += diff;
  });
}

/* Switching product button/contents */
$('.btn_prod').on('click', function(e){
    e.preventDefault();
    var click =  $(this).data('id');
    
    save_scroll(this);

    switch_prod(click);
    
    load_scroll();
});

/* Switching board button/contents */
$('.btn_board').on('click', function(e){
    e.preventDefault();
    var click =  $(this).data('id');
    
    save_scroll(this);

    switch_bd(click);
    
    load_scroll();
});

/*Store user selection to storage*/
window.addEventListener('DOMContentLoaded', () => {
  const saved_prod = sessionStorage.getItem('active-prod');
  if (saved_prod) {
    switch_prod(saved_prod);
  } else {
    switch_prod('V2L'); // Default
  }

  const saved_bd = sessionStorage.getItem('active-v2n-bd');
  if (saved_bd) {
    switch_bd(saved_bd);
  } else {
    switch_bd('V2N_EVK'); // Default
  }
  
  // Save scroll (currently user will see the pagetop for a sec.)
  // const scrollY = sessionStorage.getItem('pagescrollTop');
  // if (scrollY) {
  //     scroller.scrollTop = parseFloat(scrollY);
  // }
});

// window.addEventListener('beforeunload', () => {
//     sessionStorage.setItem("pagescrollTop", scroller.scrollTop);
// });
</script>
