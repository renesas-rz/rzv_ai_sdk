---
layout: default
---

<div class="container">
    <div class="row">
        <div id="page-top" class="top col-12">
RZ/V2H AI Applications Demo<br>
How to Use Guide
        </div>
    </div>
</div>
<br>
<br>

<h5>This page explains how to use RZ/V2H AI Applications Demo on the <b>RZ/V2H Evaluation Board Kit.</b></h5>

 <table class="gstable">
  <tr>
    <td>
      Target version
    </td>
    <td>
      <b>RZ/V2H AI Applications Demo v5.20</b>
    </td>
  </tr>
  <tr>
    <td>
      Target board
    </td>
    <td>
      RZ/V2H Evaluation Board Kit
    </td>
  </tr>
  <tr>
    <td>
      Supported AI SDK
    </td>
    <td>
      RZ/V2H AI SDK v5.20
    </td>
  </tr>
  <tr>
    <td>
      Supported AI Applications
    </td>
    <td>
      RZ/V AI Applications v5.20
    </td>
  </tr>
</table>
<br>

<h2 id="overview">Overview</h2>
<div class="container">
  <div class="row">
    <div class="col-12">
      This page explains how to setup the RZ/V2H Evaluation Board Kit (EVK) using the demo binary file.
      <br>
      Unlike the procedure described in <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" ><b>Getting Started</b></a>, this page does not build the AI Software Development Kit (AI SDK) environment, so you can easily try running the AI Applications.
      <br>
      <br>
      In this guide, you will be able to learn followings.
      <br>
      <br>
      <ul>
        <li>Prepare microSD card to set up operating environment</li>
        <li>Run AI Applications on the board</li>
      </ul>
      <br>
      The goal of this guide is to run the application and display the captured data with AI inference results on an HDMI monitor as shown below.
      <br>
      <br>
      <a href="img/demo_app_example_v2h.jpg" data-lightbox="group">
        <img src="img/demo_app_example_v2h.jpg" alt="demo_example_v2h" width="100%" style="max-width:900px;" >
      </a>
      <br>
      <br>
      To see a list of applications included in this demo, see <a href="#apptable"><b>List of RZ/V2H AI Applications Demo</b></a>.
      <br>
      <br>
      For more information about the RZ/V series, click <a href="https://www.renesas.com/products/microcontrollers-microprocessors/rz-mpus/rzv-embedded-ai-mpus"><b>here</b></a>.
      <br>
      <br>
    </div>
  </div>
</div>
<br>

<h2 id="preparation">Preparation</h2>

This chapter describes the procedures up to the first startup of the RZ/V2H Evaluation Board Kit.

<h3 id="step1">Step 1: Hardware Preparation</h3>
<div class="container">
  <div class="row">
    <div class="col-8">
      To start using RZ/V2H AI Applications Demo, we need to get the board.<br>
      Renesas provides ideal board kit for RZ/V evaluation.<br>
      <br>
      Click the button below to get the RZ/V2H board.<br>
      <br>
      <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link download.md %}" role="button">
        <span class="banner-title">Board and Software </span>
        <span class="banner-line">Get the board and software for RZ/V series.</span>
      </a>
    </div>
    <div class="col-4">
      <a href="img/V2H_EVK_v1.jpg" data-lightbox="group">
        <img src="img/V2H_EVK_v1.jpg" alt="board"/>
      </a>
    </div>
  </div>
  <br>

  <div class="row">
    <div class="col-12">
      Please prepare the following equipments for your EVK.
      <table class="gstable">
        <tr>
          <th>Equipment</th>
          <th>Details</th>
        </tr>
        <tr>
          <td>
            RZ/V2H EVK
          </td>
          <td>
            Evaluation Board Kit for RZ/V2H.
          </td>
        </tr>
        <tr>
          <td>
            AC Adapter
          </td>
          <td>
            USB Power Delivery adapter for the board power supply.<br>
            100W is required.
          </td>
        </tr>
        <tr>
          <td>
            HDMI Cable
          </td>
          <td>
            Used to connect the HDMI Monitor and the board.<br>
            RZ/V2H EVK has HDMI port.
          </td>
        </tr>
        <tr>
          <td>
            USB Camera
          </td>
          <td>
            Since RZ/V2H EVK does not include camera module, this will be the standard camera input source.<br>
            Some applications allow multiple USB camera inputs.<br> 
            Supported resolution: 640x480<br>
            Supported format: 'YUYV' (YUYV 4:2:2)<br>
          </td>
        </tr>
        <tr>
          <td>
            MIPI Camera
          </td>
          <td>
            <b>Optional.</b> Some applications allow MIPI camera input.<br> 
            Operating Environment:  e-CAM22_CURZH camera.<br>
            <h6 class="mt-1 mb-1">
              To get the e-CAM22_CURZH, please see <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp">e-con Systems</a>.<br>
            </h6>
          </td>
        </tr>
        <tr>
          <td>
            Depth Camera
          </td>
          <td>
            <b>Optional.</b> Some applications allow Depth camera input.<br> 
            Operating Environment:  Intel D435 RealSense TM Depth Camera.<br>
          </td>
        </tr>
        <tr>
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
            Used to display the graphics of the board.<br>
            Supported resolution: 1920x1080
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
            Used for Setup microSD card.<br>
            Operating Environment: Ubuntu 20.04
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
            Used to connect USB Camera and USB Mouse to the board.
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
    </div>
  </div>
</div>
<br>

<h3 id="step2">Step 2: Demo file extraction to microSD card</h3>

<ol>
  <li>If you have not yet obtained the demo file, click on the link below to download it.
    <br><br>
    <a class="btn btn-primary download-button" href="https://www.renesas.com/document/sws/rzv2h-ai-applications-demo-sd-image-version-520" role="button">Download Link</a>
    <br><br>
    <div class="note">
        <span class="note-title">Note 1</span>
        If the download link is not available, please refer to link and instruction in the latest documentation.<br>
        <a  href="https://renesas-rz.github.io/rzv_ai_sdk/latest/demo_v2h">
            https://renesas-rz.github.io/rzv_ai_sdk/latest/demo_v2h
        </a>
    </div>
    <div class="note">
      <span class="note-title">Note 2</span>
      In this section, we use a Linux PC to prepare the microSD card. <br>
      If you want to use a Windows PC, we have experience in writing disk images by following steps.
      <ol>
        <li>
          Extract the <code>*.wic.gz</code> compressed file using software such as <a href="https://www.7-zip.org/"><b>7-Zip</b></a>.
        </li>
        <li>
          Write the extracted disk image file to the microSD card using the applications such as:
          <ul>
            <li><a href="https://sourceforge.net/projects/win32diskimager/"><b>Win32 Disk Imager download | SourceForge.net</b></a></li>
            <li><a href="https://www.raspberrypi.com/software/"><b>Raspberry Pi OS - Raspberry Pi</b></a></li>
          </ul>
        </li>
      </ol>
    </div>
  </li><br>
  <li>Place the downloaded Zip file into a Linux PC and unzip it using the following command in a terminal.
  <br><br>
{% highlight shell %}
unzip RTK0EF0197F05200SJ.zip
{% endhighlight %}
    Make sure the following folders and files are generated after unzipping the file.
    <table id="demodirs" class="mytable">
      <caption>Demo File Structure</caption>
      <tr>
        <th>Folder Name</th>
        <th>Folder Content</th>
        <th>Description</th>
      </tr>
      <tr>
        <td rowspan="2">licenses/</td>
        <td>linux_licenses.zip</td>
        <td>Linux license information.</td>
      </tr>
      <tr>
        <td>r11an0940ej0520-rzv2h-ai-apps-demo(Linux License List).pdf</td>
        <td>List of Linux license information included in Demo microSD card image. Copyright information is not included.</td>
      </tr>
      <tr>
        <td rowspan="2">sd_image/</td>
        <td>rzv2h_ai_applications_demo_v5.20.wic.gz</td>
        <td>Gzip file containing the Demo microSD card image.</td>
      </tr>
      <tr>
        <td>rzv2h_ai_applications_demo_v5.20.wic.bmap</td>
        <td>Bmap file for copying the Demo microSD card image.</td>
      </tr>
      <tr>
        <td colspan="2">r11an0884ej0520-rzv2h.pdf</td>
        <td>ReadMe document describing the contents of the Demo zip file.</td>
    </tr>
    </table>
  </li>
  <br>
  <li>
    To write the microSD card image, install <code>bmap-tools</code> on the Linux PC with the following command.
    <br><br>
{% highlight shell %}
sudo apt install bmap-tools
{% endhighlight %}
  </li>
  <br>
  <li>Run the following command to check the device connected to the Linux PC <strong>before</strong> inserting the microSD card.
    <br><br>
{% highlight shell %}
lsblk
{% endhighlight %}
    Then, insert the microSD card into the Linux PC and run the same command (<code>lsblk</code>) again.<br>
    Confirm that the microSD device name (<code>/dev/sdb</code>) has been added to the terminal after inserting the card, as shown in the console window below.
    <br><br>
    <a href="img/demo_lsblk_check.jpg" target="group">
      <img src="img/demo_lsblk_check.jpg" alt="demo_lsblk_check" width="80%">
    </a>
    <br>
    <div class="note">
      <span class="note-title">Note</span>
      The microSD card device name may vary depending on the PC environment.<br>In this manual, we use <code>/dev/sdb</code> as the microSD card device name.
    </div>
  </li><br>
  <li>To use <code>bmap-tools</code>, microSD card partitions must be unmounted. Follow the steps below to unmount.
    <ol type="A">
      <li>Run the following command to check the automatically mounted microSD card partitions.
        <br><br>
{% highlight shell %}
df -h
{% endhighlight %}
      </li><br>
      <li>Check the output and find the mount point from the device name found above (<code>/dev/sdb</code>).<br>
       Here "<code>/media/user/9016-4EF8</code>" is the mount point.
        <br><br>
{% highlight shell %}
Filesystem      Size  Used Avail Use% Mounted on
:
snip
:
/dev/sdb1        15G   32K   15G   1% /media/user/9016-4EF8
{% endhighlight %}
        <div class="warning">
          <span class="warning-title">Warning</span>
            Here, we use <code>/dev/sdb</code> as microSD card device name.<br>
        </div>
      </li>
      <li>Unmount the SD card partition if it is mounted.
        <br><br>
{% highlight shell %}
sudo umount /media/user/9016-4EF8
{% endhighlight %}
        <div class="note">
          <span class="note-title">Note</span>
          If there are more than one partitions on microSD card, unmount all partitions.
        </div>
      </li>
    </ol>
  </li><br>
  <li>Using the device name (<code>/dev/sdb</code>), write the disk image file into the microSD card.
    <br><br>
{% highlight shell %}
cd sd_image
sudo bmaptool copy --bmap rzv2h_ai_applications_demo_v5.20.wic.bmap rzv2h_ai_applications_demo_v5.20.wic.gz /dev/sdb
{% endhighlight %}
    <div class="warning">
      <span class="warning-title">Warning</span>
      Change <code>/dev/sdb</code> to your microSD card device name.<br>
    </div>
    <div class="note">
      <span class="note-title">Note</span>
      Writing the microSD card image takes several minutes.<br>
    </div>
  </li><br>
  <li>Execute the following command to eject the microSD card.
    <br><br>
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

This completes the board setup. Let's move on to the next chapter and run the applications.

<br>

<h2 id="runapp">Running Applications</h2>

This chapter describes how to run the AI Applications in the demo file.

<h3 id="linuxboot">Step 1: Boot process</h3>

Once the <a href="#preparation"><b>Preparation</b></a> chapter is complete, you can boot the board in the following way.
<br><br>
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
        <li>Connect equipments to USB ports.<br>
          <ol>
            <li>
              Connect the USB mouse and USB camera(s) via USB hub.<br>
              <div class="note">
                <span class="note-title">Note 1</span>
                Up to 3 USB camera inputs are supported.
              </div>
              <div class="note">
                <span class="note-title">Note 2</span>
                There are USB 2.0 port and USB 3.0 port on RZ/V2H EVK.<br>
                Please connect your USB camera to appropriate port according to its requirement.<br>
                Here, USB camera is connected to USB 2.0 via USB hub.<br>
              </div>
            </li>
            <li>
              <b>[Optional]</b> Connect the Depth camera to the USB 3.0 port.<br>
            </li>
          </ol>
        </li><br>
        <li>
          <b>[Optional]</b> Connect the MIPI camera to the CN7 on the <b>Board</b>.<br>
          <ol>
            <li>Pull up the edge of CN7.</li>
            <li>Insert the cable.</li>
            <li>Push down the edge of CN7.</li>
          </ol>
        </li>
        <br>
        <li>Connect the HDMI monitor to the <b>Board</b>.</li><br>
        <li>Connect the power cable to the <b>Board</b>.</li><br>
        <li>Turn the SW3 to ON.</li><br>
        <li>Turn the SW2 to ON to power on the <b>Board</b></li>
      </ol>
    </div>
    <div class="col-12 col-md-6">
      <a href="img/v2h_evk_boot_demo.png" data-lightbox="group"><img class="procedure" src="img/v2h_evk_boot_demo.png" alt="boot" width="90%"/></a>
    </div>
  </div>
  <div class="row">
    <div class="col-12">
      <ol>
        <li id="gui_home" value="9">
          The GUI home screen appears on the HDMI monitor.
          <br>
          See the figure below for window layout.
          <br>
          <br>
          <big><b>GUI Home Screen</b></big><br>
          <a href="img/demo_gui_home_v2h.jpg" data-lightbox="group">
            <img src="img/demo_gui_home_v2h.jpg" alt="demo_gui_home" width="100%" style="max-width:900px;" >
          </a>
        </li>
      </ol>
    </div>
  </div>
</div>
<br>

<h3 id="executedemo">Step 2: Demo execution</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      <ol>
        <li>The list of AI applications included in the Demo is shown below.
          Select the application you want to run from the list.
          <table id="apptable" class="mytable">
            <caption>List of RZ/V2H AI Applications Demo</caption>
            <tr>
              <th>Category</th>
              <th>Application Name</th>
              <th>Details</th>
              <th>Supported<br>Camera Devices</th>
              <th>User Interface</th>
            </tr>
            <tr>
              <td rowspan="3">Agriculture</td>
              <td>Defense wild animals for crop</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/07_Animal_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Fruit and Vegetable Plant Disease Check</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q07_plant_disease_classification"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q07_plant_disease_classification#application-run-stage"><b>GUI</b></a></td>
            </tr>
            <tr>
              <td>Ranch Livestock Management</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td rowspan="8">Smart Building</td>
              <td>Elevator passengers Counting</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/01_Head_count"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Conference Room Usage Monitor</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Lighting Control</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Security Area Intrusion Detection</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/02_Line_crossing_object_counting"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Wear management at construction sites</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/04_Safety_helmet_vest_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Touchless Controller for elevator</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/12_Hand_gesture_recognition_v2"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Employee ID check for Restricted Area</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication#gui-for-running-the-application"><b>GUI</b></a></td>
            </tr>
            <tr>
              <td>Multi-Camera Parking Lot Management <a href="#footnote_multi"><sup>*1</sup></a></td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/14_Multi_camera_vehicle_detection"><b>GitHub Link</b></a></td>
              <td>USB / USBx2 / USBx3 / MIPI</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td rowspan="22">Smart City</td>
              <td>Congestion Detection in Railway Station</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Prohibited Area Management</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/02_Line_crossing_object_counting"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Distracted driving detection</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/09_Human_gaze_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Duration monitoring for surveillance camera</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter#instruction-1"><b>GUI</b></a></td>
            </tr>
            <tr>
              <td>Passport check support</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q02_face_authentication#gui-for-running-the-application"><b>GUI</b></a></td>
            </tr>
            <tr>
              <td>Bus passenger counting</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Backtravel Detection</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/02_Line_crossing_object_counting"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Violence Activity Check in Surveillance Camera</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q05_suspicious_activity"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Bird Damage Prevention</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Blind Spot Monitor</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Preceding Vehicle Movement Alert</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/13_Car_ahead_departure_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Emergency Vehicles Detector</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Illegal Bicycle Approach Detection</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Bicycle Rental Stock Management</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Illegal Bicycle Parking Monitor Support</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q08_object_counter"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Infrastructure Defect Prevention</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q09_crack_segmentation"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Crime Prevention Support for School</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q10_suspicious_person_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Multi-Camera Vehicle Detector <a href="#footnote_multi"><sup>*1</sup></a></td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/14_Multi_camera_vehicle_detection"><b>GitHub Link</b></a></td>
              <td>USB / USBx2 / USBx3 / MIPI</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Car Accident Prevention Alert <a href="#footnote_multi"><sup>*1</sup></a></td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/14_Multi_camera_vehicle_detection"><b>GitHub Link</b></a></td>
              <td>USB / USBx2 / USBx3 / MIPI</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Driving Support with Road Lane Segmentation</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/15_Road_lane_segmentation"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Visual Walking Support</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/15_Road_lane_segmentation"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>River water level monitoring system</td>
              <td><a href="https://github.com/ComputermindCorp/drp-ai-demo-app/tree/main/C01_river_area_monitoring"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td rowspan="3">Healthcare</td>
              <td>Physical Condition Monitor</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/03_Elderly_fall_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Yoga Pose Monitor</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q12_yoga_pose_estimation"><b>GitHub Link</b></a></td>
              <td> USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Body size measurement</td>
              <td><a href="https://github.com/ComputermindCorp/drp-ai-demo-app/tree/main/C02_depth_cam_human_body_estimation"><b>GitHub Link</b></a></td>
              <td>Depth</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td rowspan="4">Smart Home</td>
              <td>Air Conditioner Control</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Pet Detection in Kitchen and Child's Room</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/07_Animal_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Touchless Controller for Kitchen Appliance</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/12_Hand_gesture_recognition_v2"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Food Package Expiry Date Check</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q06_expiry_date_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td rowspan="9">Industrial</td>
              <td>Work Area Personnel Management</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/01_Head_count"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Access Control</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/02_Line_crossing_object_counting"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Helmet and safety vest wearing monitor</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/04_Safety_helmet_vest_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Touchless Controller for Industrial machine</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/12_Hand_gesture_recognition_v2"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Driver Monitoring System</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/10_Driver_monitoring_system"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Species check support in Fish Factory</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q04_fish_classification"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Defect Inspection Support</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q09_crack_segmentation"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Aquaculture Industrial Support</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q11_fish_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Lumber visual inspection</td>
              <td><a href="https://github.com/ComputermindCorp/drp-ai-demo-app/tree/main/C03_surface_anomaly_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td><a href="https://github.com/ComputermindCorp/drp-ai-demo-app/tree/main/C03_surface_anomaly_detection#instruction-1"><b>GUI</b></a></td>
            </tr>
            <tr>
              <td rowspan="6">Retail</td>
              <td>Congestion Detection</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Smart POS</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/05_Age_gender_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Marketing Interest Analysis</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/09_Human_gaze_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Staying and flow line monitoring</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q01_footfall_counter#instruction-1"><b>GUI</b></a></td>
            </tr>
            <tr>
              <td>Exhibition Participants Monitoring</td>
              <td><a href="https://github.com/Ignitarium-Renesas/rzv_ai_apps/tree/main/11_Head_count_topview"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
            <tr>
              <td>Store Crime Prevention</td>
              <td><a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/main/Q10_suspicious_person_detection"><b>GitHub Link</b></a></td>
              <td>USB</td>
              <td>CUI</td>
            </tr>
          </table>
          <h6>
            <span id="footnote_multi">*1: The error may occur when depth camera and USB cameras are connected. See <a href="#note-multi">Note 1</a>.</span>
          </h6>
        </li><br>
        <li>
          After following the boot procedure in the <a href="#linuxboot"><b>previous section</b></a>, you can start the application using the GUI.<br><br>
          <div class="row">
            <div class="col-12 col-md-6">
              <ol type="A">
                <li>
                  Scroll the application list on the left of the screen and click the application name.
                </li><br>
                <li>
                  The application panel page on the right automatically shows the application that you clicked.<br>
                  You can also scroll the panel page manually.
                  <div class="note">
                    <span class="note-title">Note</span>
                    If you are using a USB mouse, please drag to scroll the pages as the mouse wheel is not available.
                  </div>
                </li><br>
                <li>
                  Press the "Start" button in the panel to run the application.
                </li>
              </ol>
            </div>
            <div class="col-12 col-md-6">
              <a href="img/demo_gui_start_v2n.jpg" data-lightbox="group">
                <img src="img/demo_gui_start_v2n.jpg" alt="demo_gui_start_v2h" width="100%">
              </a>
            </div>
          </div>
        </li><br>
        <li>
          On monitor, the application will automatically start.
          <div class="row">
            <div class="col-12 col-md-6">
              <div class="note">
                <span class="note-title">Note 1</span>
                Some applications require GUI control. <br>
                See the link in the User Interface column of <a href="#apptable"><b>List of RZ/V2H AI Applications Demo</b></a>.
              </div>
              <div class="note">
                <span class="note-title">Note 2</span>
                The termination button on application window may temporarily disappear. <br>
                Please wait a few seconds until the screen display gets stable.
              </div>
              <div class="note">
                <span class="note-title">Note 3</span>
                If the running application encounters any errors (e.g. the camera is not connected), the application will automatically exit and return to the <a href="#gui_home"><b>home screen</b></a>.<br>
                You can check the error log by clicking <b>Check Previous Log</b> button.
              </div>
            </div>
            <div class="col-12 col-md-6">
              <a href="img/demo_gui_run_v2h.jpg" data-lightbox="group">
                <img src="img/demo_gui_run_v2h.jpg" alt="demo_gui_run_v2h" width="100%">
              </a>
            </div>
          </div>
        </li><br>
        <li>
          To terminate the application, follow the instruction below.
          <ul>
            <li>
              For <b>CUI</b> application, <b>press the blue Termination Button</b> in the bottom right-hand corner.
            </li>
            <li>
              For <b>GUI</b> application, <b>double click</b> the application window.
            </li>
          </ul>
        </li>
        <br>
        <li>
          After the application termination, users can check the console log from the application.<br>
          <div class="row">
            <div class="col-12">
              <ol>
                <li>
                  Click <b>Check Previous Log</b> button on the <a href="#gui_home"><b>home screen</b></a>.
                  <br>
                  <a href="img/demo_gui_log_1.jpg" data-lightbox="group">
                    <img  
                      class="mt-1"
                      src="img/demo_gui_log_1.jpg" 
                      alt="Click to see the log" 
                      width="100%" style="max-width: 500px;">
                  </a>
                </li>
                <br>
                <li>
                  <b>Application Log</b> window appears and shows the console log of previously executed AI Application.
                  <br>
                  <a href="img/demo_gui_log_2.jpg" data-lightbox="group">
                    <img 
                      class="mt-1"
                      src="img/demo_gui_log_2.jpg" 
                      alt="Bottom max. 500 lines will be shown" 
                      width="100%" style="max-width: 500px;">
                  </a>
                  <br>
                  <div class="note">
                    <span class="note-title">Note</span>
                    The Application Log windows shows the <b>bottom 500 lines</b> of console log.
                  </div>
                </li>
                <br>
                <li>
                  Click <b>Back</b> button to go back to the <a href="#gui_home"><b>home screen</b></a>.
                  <br>
                  <a href="img/demo_gui_log_3.jpg" data-lightbox="group">
                    <img 
                      class="mt-1"
                      src="img/demo_gui_log_3.jpg" 
                      alt="Click Back" 
                      width="100%" style="max-width: 500px;">
                  </a>
                </li>
              </ol>
            </div>
          </div>
        </li>
      </ol>
    </div>
  </div>
</div>
<br>

<h3 id="shutdown">Step 3: Shutdown process</h3>

<div class="container">
  <div class="row">
    <div class="col-12">
      To power-off the RZ/V2H EVK, follow the procedures below.<br><br>
      <ol>
        <li>
          On the <a href="#gui_home"><b>home screen</b></a>, click the X button at the top right-hand corner.<br><br>
          <a href="img/demo_gui_shutdown_btn_v2h.jpg" data-lightbox="group">
            <img src="img/demo_gui_shutdown_btn_v2h.jpg" alt="demo_gui_shutdown_btn_v2h" width="350px">
          </a>
          <br><br>
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
      <br>
    </div>
  </div>
</div>


<h2 id="note">Notes</h2>

This chapter describes the application behaviors confirmed by Renesas.

<!-- <h3 id="note-index">Index</h3>
<ul>
  <li>
    <a href="#note-multi">Note 1: Multi-camera application shows black screen</a>
  </li>
</ul>
<br> -->
<h3 id="note-multi">Note 1: Multi-camera application shows black screen</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      Some applications show only black screen with termiation button.
      <h4 class="mt-1 mb-1 u_line">Target application</h4>
      <ul>
        <li>
          Smart Building: Multi-Camera Parking Lot Management
        </li>
        <li>
          Smart City: Multi-Camera Vehicle Detector
        </li>
        <li>
          Smart City: Car Accident Prevention Alert
        </li>
      </ul>
      <h4 class="mb-1 u_line">Details</h4>
      When clicking "Start (USB CameraxN)" with following cameras connected, the target application shows black screen.
      <ul>
        <li>
          A depth camera
        </li>
        <li>
          Less than N USB cameras
        </li>
      </ul>
      For example, <b>1 Depth Camera</b> and <b>1 USB Camera</b> are connected to the board and a user clicks <b>"Start (USB Camerax2)"</b>. 
      <br>
      <a href="img/demo-note/1_click.png" data-lightbox="group">
        <img class="mt-1" src="img/demo-note/1_click.png" alt="note1 blackscreen" width="600px">
      </a>
      <br>
      <br>
      Then, following black screen is kept showing.
      <br>
      <a href="img/demo-note/1_blackscreen.png" data-lightbox="group">
        <img class="mt-1" src="img/demo-note/1_blackscreen.png" alt="note1 blackscreen" width="600px">
      </a>
      <br>
      <br>
      User can go back to home screen with termination button.
      <br>
      The "Check Previous Log" button shows <b>"[ERROR] Error opening video stream or camera!"</b> as shown below.
      <br>
      <a href="img/demo-note/1_error_log.png" data-lightbox="group">
        <img class="mt-1" src="img/demo-note/1_error_log.png" alt="note1 log" width="600px">
      </a>
      <br>
      <h4 class="mb-1 u_line">Cause</h4>
      It occurs since the depth camera is recognized as USB camera, but could not be opened as "USB camera".
      <br>
      <h4 class="mb-1 u_line">Workaround</h4>
      Connect the appropriate number of USB cameras and run the target application again.
    </div>
  </div>
</div>
<br>
<br>
<div class="container">
  <div class="row">
    <div class="col-12" align="right">
      <a class="btn btn-secondary square-button" href="#page-top" role="button">
Back to Top >
      </a>
    </div>
  </div>
</div>