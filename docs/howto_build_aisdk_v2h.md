---
layout: default
---
<div class="container">
    <div class="row">
        <div class="top col-12">
          How to build RZ/V2H AI SDK Source Code
        </div>
    </div>
</div>
<br>
<br>
<h5>This page explains how to build Linux with <b>RZ/V2H AI SDK Source Code.</b></h5>

<h5>Supported version: <b>RZ/V2H AI SDK v4.00</b></h5>

<h3 id="intro" >Introduction</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      AI SDK is a quick and easy AI Application development environment.<br>
      It is specifically made for RZ/V2H Evaluation Board Kit with fixed Linux components.<br>
      (For more information, please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}">Getting Started</a> and <a href="{{ site.url }}{{ site.baseurl }}{% link ai-sdk.md %}">AI SDK</a>.)<br>
      <br>
      To modify Linux component, you need to build AI SDK from source code.<br>
      AI SDK Source Code can generate the same Linux environment as AI SDK.<br>
      <br>
    </div>
  </div>
</div>
<div class="col-12  col-md-6 text-center">
  <a href="img/aisdk_sc_v2h.svg" data-lightbox="group"><img src="img/aisdk_sc_v2h.svg" alt="AI Application and AI SDK software"></a><br>
</div>
<div class="container">
  <div class="row">
    <div class="col-12">
      <br>
      This page explains how to build AI SDK Source Code.<br>
      After you have completed this page, you would be able to change the source code and customize Linux environment (i.e., memory map, additional OSS etc...).<br>
      To customize the Linux environment, please refer to <a href="https://www.renesas.com/document/mas/rzv2h-bsp-manual-set-rtk0ef0045z94001azj-v100zip">RZ/V2H BSP Manual Set</a>.<br>
      <br>
      <div class="note">
        <span class="note-title">Requirement</span>
        <ol>
          <li>Users have launched RZ/V2H Evaluation Board Kit according to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}">Getting Started</a>, which means they can run <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}">AI Application</a> on the board.<br>
          </li>
          <li>To build Yocto Linux, the below equipment should be prepared.<br>
            <table class="gstable">
              <tr>
                <th>Equipment</th>
                <th colspan="2">Details</th>
              </tr>
              <tr>
                <td rowspan="2">Linux PC</td>
                <td colspan="2">Approximately <b>120GB free space</b> is necessary.</td>
              </tr>
              <tr>
                <td>OS</td>
                <td><b>Ubuntu 20.04 LTS</b><br>
                    64bit OS must be used.</td>      
              </tr>
            </table>
          </li>
        </ol>
      </div>
      <br>
      Now you are ready to build your Linux development environment.<br>
      <h5><b><i>Let's get started!!</i></b></h5><br>
    </div>
  </div>
</div>
<br>

<h3 id="step1" >Step 1: Obtain RZ/V2H AI SDK Source Code</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      Download the RZ/V2H AI SDK Source Code from the link below.<br><br>
      <a class="btn btn-primary download-button" href="https://www.renesas.com/document/sws/rzv2h-ai-sdk-v400-source-code" role="button">Download Link</a>
      <br><br>
 	    AI SDK Source Code (<b><code>RTK0EF0180F*_linux-src.zip</code></b>) contains following files:<br>
      <table class="mytable">
        <tr>
          <th>File name</th>
          <th>Description</th>
        </tr>
        <tr>
          <td>README.txt</td>
          <td>README file.</td>
        </tr>
        <tr>
          <td>rzv2h_ai-sdk_yocto_recipe_v*.tar.gz</td>
          <td>Yocto recipe.<br>
          Yocto recipes are text files that contains necessary information to build Yocto Linux.</td>
        </tr>
      </table>
    </div>
  </div>
</div>
<br>

<h3 id="step2" >Step 2: Extract RZ/V2H AI SDK Source Code</h3>
<br>
This step explains how to extract RZ/V2H AI SDK Source Code zip file.
<br>
<ol>
  <li>On your Linux PC, check you have already registered the environment variable <b><code>WORK</code></b> with the below command.
{% highlight shell %}
printenv WORK
{% endhighlight %}
    <ul>
      <li>
      If the above command prints followings, proceed next step. <br>
{% highlight plaintext %}
<path to the working directory>/ai_sdk_work
{% endhighlight %}
      If not, please register the working directory path to an environment variable according to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step4">Step4: Extract RZ/V AI SDK package in Getting Started</a>.
      </li>
    </ul>
  </li>
  <br>
  <li>Make the working directory on your Linux PC.
{% highlight shell %}
mkdir -p ${WORK}/src_setup
{% endhighlight %}
  </li>
  <li>Move to the working directory.
{% highlight shell %}
cd ${WORK}/src_setup
{% endhighlight %}
  </li>
  <li>Extract RZ/V2H AI SDK Sorce Code zip file.
{% highlight shell %}
unzip <Path to the file>/RTK0EF0180F*_linux-src.zip -d ${WORK}/src_setup
{% endhighlight %}
  </li>
  <li>Check the working directory to confirm the package contents.
{% highlight shell %}
ls -1 ${WORK}/src_setup
{% endhighlight %}
    <ul>
      <li>If the above command prints followings, the package is extracted correctly.
{% highlight shell %}
README.txt
rzv2h_ai-sdk_yocto_recipe_v*.tar.gz
{% endhighlight %}
      </li>
    </ul>
  </li>
</ol>
<br>

<h3 id="step3" >Step 3: Build RZ/V2H AI SDK Source Code</h3>
This step explains how to build Linux environment with RZ/V2H AI SDK Source Code
<ol>
  <li> To install necessary sofware, run the following commands on your Linux PC.
{% highlight shell%}
sudo apt-get update
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
build-essential chrpath socat cpio python python3 python3-pip python3-pexpect \
xz-utils debianutils iputils-ping libsdl1.2-dev xterm p7zip-full libyaml-dev \
libssl-dev 
{% endhighlight %}
  </li>
  <li>Run the following commands and set the user name and email address before starting the build procedure.<br>
    It is needed to avoid errors when using git command to apply patches.
{% highlight shell%}
git config --global user.email "you@example.com"
git config --global user.name "Your Name"
{% endhighlight %}
  </li>
  <li>Register the working directory path to an environment variable.
{% highlight shell%}
export YOCTO_WORK=${WORK}/src_setup/yocto
mkdir -p ${YOCTO_WORK}
{% endhighlight %}
  </li>
  <li>Extract Yocto recipe package.
{% highlight shell%}
cd ${YOCTO_WORK}
tar zxvf ${WORK}/src_setup/rzv2h_ai-sdk_yocto_recipe_v*.tar.gz
{% endhighlight %}
  </li>
  <li>Get e-CAM22_CURZH camera driver (MIPI) from <i>e-con Systems</i>.<br>
    The e-CAM22_CURZH camera driver (MIPI) used in AI SDK is not included in the RZ/V2H AI SDK Source Code. The required driver needs to be obtained through the following procedure.
    <ol type="A">
      <li>To build the e-CAM22_CURZH camera driver (MIPI) for RZ/V2H Evaluation Board Kit, contact <i>e-con Systems</i> at <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp">this link</a> to obtain the patch file below.
        <table class="mytable">
          <tr>
            <th>File name</th>
            <th>Description</th>
          </tr>
          <tr>
            <td>e-CAM22_CURZ*.patch</td>
            <td>e-CAM22_CURZH camera driver (MIPI) Yocto patch file for RZ/V2H</td>
          </tr>
        </table>
      </li>
      <li>Copy and apply the patch file.
{% highlight shell%}
cp <Path to the file>/e-CAM22_CURZ*.patch ${YOCTO_WORK}
cd ${YOCTO_WORK}
patch -p1 -i e-CAM22_CURZ*.patch
{% endhighlight %}
      </li>
    </ol>
  </li>
  <li id="step3-6">Check the working directory to confirm Yocto recipes content.
{% highlight shell%}
ls -1 ${YOCTO_WORK}
{% endhighlight %}
    <ul>
      <li>If the above command prints followings, Yocto recipes are extracted correctly.
{% highlight shell%}
0001-tesseract.patch
0002-sd-image-size-16gb.patch
e-CAM22_CURZ*.patch
meta-econsys
meta-gplv2
meta-openembedded
meta-renesas
meta-rz-features
meta-virtualization
poky
{% endhighlight %}
      </li>
    </ul>
    <div class="note">
      <span class="note-title">Note 1</span>
      Evaluation version of Graphics Library has restriction on their running time.<br>
      If you would like to use unrestricted version of Graphics Library,
	    please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}#A1">Appendix 1: Build Graphics Library for Unrestricted Version</a>.<br>
    </div>
    <div class="note">
      <span class="note-title">Note 2</span>
      Video Codec Library supports only H.264 Enc in AI SDK v4.00.<br>
      If you would like to use H.264 Dec and H.265 Enc/Dec function,
	    please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}#A3">Appendix 3: Prepare Video Codec Library for H.264 Enc/Dec and H.265 Enc/Dec function</a>.<br>
    </div>
  </li>
  <li id="step3-7">Initialize a build using the <b><code>oe-init-build-env</code></b> script in Poky and set   environment variable <b><code>TEMPLATECONF</code></b> to the below path.
{% highlight shell%}
cd ${YOCTO_WORK}
TEMPLATECONF=${PWD}/meta-renesas/meta-rzv2h/docs/template/conf/ source poky/oe-init-build-env
{% endhighlight %}
  </li>
  <li id="step3-8">Run the following commands to add necessary layers for AI application to <b><code>${YOCTO_WORK}/build/conf/bblayers.conf</code></b> (configration file for layers).
{% highlight shell%}
bitbake-layers add-layer ../meta-rz-features/meta-rz-graphics
bitbake-layers add-layer ../meta-rz-features/meta-rz-drpai
bitbake-layers add-layer ../meta-rz-features/meta-rz-opencva
bitbake-layers add-layer ../meta-rz-features/meta-rz-codecs
bitbake-layers add-layer ../meta-econsys
{% endhighlight %}
  </li>
  <li>Apply a patch file to add Tesseract Open Source OCR Engine for AI applications.
{% highlight shell%}
patch -p1 < ../0001-tesseract.patch
{% endhighlight %}
  </li>
  <li id="step3-10">Apply a patch file to change SD card image size.
{% highlight shell%}
patch -p1 < ../0002-sd-image-size-16gb.patch
{% endhighlight %}
    <div class="note">
      <span class="note-title">Note</span>
      The default size of the microSD card image created in this guide is approximately 16 GB.<br>
      If you would like to change the microSD card image size, please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}#A2">Appendix 2: Change the size of the microSD card image in WIC format</a>.<br>
    </div>
  </li>
  <li id="step3-11">Run the following command to build the <b>Linux kernel files.</b><br>
    (It takes a few hours to finish building depending on the user's host PC performance)
{% highlight shell%}
MACHINE=rzv2h-evk-ver1 bitbake core-image-weston
{% endhighlight %}
    All necessary files listed below will be generated by the build command and 
	  they will be located in <b><code>${YOCTO_WORK}/build/tmp/deploy/images/rzv2h-evk-ver1</code></b> directory.<br>
    <table class="mytable">
      <tr>
        <th>File name</th>
        <th>Description</th>
      </tr>
      <tr>
        <td>
          core-image-weston-rzv2h-evk-ver1.wic.bmap<br>
          core-image-weston-rzv2h-evk-ver1.wic.gz
        </td>
        <td>WIC format SD card image</td>
      </tr>
    </table>
  </li>
  <li>Run the following command to build <b>cross compiler installer</b>.<br>
{% highlight shell%}
MACHINE=rzv2h-evk-ver1 bitbake core-image-weston -c populate_sdk
{% endhighlight %}
    A necessary file listed below will be generated by the build command and the cross compiler installer will be located in <b><code>${YOCTO_WORK}/build/tmp/deploy/sdk/poky-glibc-x86_64-core-image-weston-aarch64-rzv2h-evk-ver1-toolchain-*.sh</code></b>.<br>
    <table class="mytable">
      <tr>
        <th>File name</th>
        <th>Description</th>
      </tr>
      <tr>
        <td>poky-glibc-x86_64-core-image-weston-aarch64-rzv2h-evk-ver1-toolchain-*.sh</td>
        <td>Cross compiler installer</td>
      </tr>
    </table>
    <div class="note">
      <span class="note-title">Note</span>
      If some errors occurred during the build, 
      please clean the directory and rebuild it after a period of time according to the below commands.
{% highlight shell%}
cd ${YOCTO_WORK}/build
MACHINE=rzv2h-evk-ver1 bitbake core-image-weston -c cleanall
{% endhighlight %}
      And run the build command again.
      <ul>
        <li>For Linux kernel files
{% highlight shell%}
MACHINE=rzv2h-evk-ver1 bitbake core-image-weston
{% endhighlight %}  
        </li>
        <li>For cross compiler installer
{% highlight shell%}
MACHINE=rzv2h-evk-ver1 bitbake core-image-weston -c populate_sdk
{% endhighlight %}
        </li>
      </ul>
    </div>
  </li>
</ol>
<br>
 
<h4>
This is the end of how to build AI SDK Source Code.
</h4>
You have prepared following files, which is same as the one provided in <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step3">Step 3: Obtain RZ/V2H AI SDK in Getting Started</a>, and you can run <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}">AI Applications</a> according to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}">Getting Started</a>.
<br>
<table class="mytable">
  <tr>
    <th>Path</th>
    <th>File name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>${YOCTO_WORK}/build/tmp/deploy/images/rzv2h-evk-ver1</td>
    <td>
      core-image-weston-rzv2h-evk-ver1.wic.bmap<br>
      core-image-weston-rzv2h-evk-ver1.wic.gz
    </td>
    <td>WIC format SD card image</td>
  </tr>
  <tr>
    <td>${YOCTO_WORK}/build/tmp/deploy/sdk</td>
    <td>poky-glibc-x86_64-core-image-weston-aarch64-rzv2h-evk-ver1-toolchain-*.sh</td>
    <td>Cross compiler installer</td>
  </tr>
</table>
<div class="note">
  <span class="note-title">Note 1</span>
  For more Yocto Project information, please refer the link below:<br>
  <a href="https://docs.yoctoproject.org/3.1.26/brief-yoctoprojectqs/brief-yoctoprojectqs.html">https://docs.yoctoproject.org/3.1.26/brief-yoctoprojectqs/brief-yoctoprojectqs.html</a>
</div>
<div class="note">
  <span class="note-title">Note 2</span>
  When customizing Linux development environment, following information may help.<br>
  <ul>
    <li>
      <a href="https://docs.yoctoproject.org/">https://docs.yoctoproject.org/</a>
    </li>
    <li>
      <a href="https://www.renesas.com/document/mas/rzv2h-bsp-manual-set-rtk0ef0045z94001azj-v100zip">RZ/V2H BSP Manual Set</a>
    </li>
  </ul>
</div>
<div class="note">
  <span class="note-title">Note 3</span>
  To add more functionality to AI SDK, please refer to following URL.
  <ul>
    <li>
      <a href="https://www.renesas.com/us/en/software-tool/rzv2h-ros2-package">RZ/V2H ROS2 Package</a>
    </li>
    <li>
      <a href="https://www.renesas.com/software-tool/rzv-group-multi-os-package">RZ/V Multi-OS Package</a>
    </li>
  </ul>
</div>
<br>
If you have any questions about AI SDK Source Code,<br>
please add new issues to AI SDK GitHub issues.<br>
<br>
<a class="btn btn-primary download-button" href="https://github.com/renesas-rz/rzv_ai_sdk/issues" role="button">Go to GitHub issues</a>

<div class="row">
  <div class="col-12" align="right">
    <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}" role="button">
      Back to Home >
    </a>
  </div>
</div>
<br><br>

<h3 id="A1">Appendix 1: Prepare Graphics Library for Unrestricted Version</h3>
This section explains how to prepare Graphics Library for unrestricted version, intead of evaluation version.<br>
<div class="note">
  <span class="note-title">Note</span>
  Following instruction assumes that you have completed <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}#step3-6">Step 3-6 in How to build RZ/V2H AI SDK Source Code</a>.
</div>
  <ol>
    <li>Download zip files from the link below.
      <br>
      <div class="note">
        <span class="note-title">Note</span>
        It may take much time to obtain Graphics Library for unrestricted version due to necessary examinations on your business purpose. 
      </div>
      <br>
      <a class="btn btn-primary download-button" href="https://www.renesas.com/secure/rzv2-graphics-library-secure-content" role="button">Download Link</a>
    </li>
    <br>
    <li>After you downloaded the zip files, please move the zip files to "<b><code>${WORK}/src_setup</code></b>" on your Linux PC.
    <br>
    </li>
    <br>
    <li>Check that zip files are moved to appropriate location.
{% highlight shell %}
cd ${WORK}/src_setup
ls -1 
{% endhighlight %}
      <ul>
        <li>If the above command prints followings, the package is extracted correctly.
{% highlight shell %}
README.txt
RTK0EF0*ZJ-v*_rzv_*.zip
rzv2h_ai-sdk_yocto_recipe_v*.tar.gz
yocto
{% endhighlight %}
        </li>
      </ul>
    </li>
    <li>Run the below command to delete evaluation version.<br>
{% highlight shell %}
rm -rf ${YOCTO_WORK}/meta-rz-features/meta-rz-graphics
{% endhighlight %}
    </li>
    <li>Run the below command to extract the unristricted version.<br>
{% highlight shell %}
unzip RTK0EF0045Z14001ZJ*.zip
tar zxvf RTK0EF0045Z14001ZJ*/meta-rz-features_graphics_*.tar.gz -C ${YOCTO_WORK}
{% endhighlight %}
    </li>
  </ol>
After this procedure, please proceed to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}#step3-7"> Step 3-7 in How to build RZ/V2H AI SDK Source Code</a> to start building Linux kernel files.
<br><br>

<h3 id="A2">Appendix 2: Change the size of the microSD card image in WIC format</h3>
This section explains how to change the microSD card image size by changing the build settings of the WIC file.<br>
<div class="note">
  <span class="note-title">Note</span>
  Following instruction assumes that you have completed <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}#step3-10">Step 3-10 in How to build RZ/V2H AI SDK Source Code</a>.
</div>
  <ol>
    <li>Open <b><code>${YOCTO_WORK}/build/conf/local.conf</code></b> file in a text editor.
    </li>
    <li>Find the following text in the file and edit the highlighted value to define the disk space of the image in Kbytes.
<pre><code>...
# Support WIC images with default wks from WKS_DEFAULT_FILE
# Reupdate WKS_DEFAULT_FILE if want to support another wks file.
WKS_SUPPORT ?= "1"
WKS_DEFAULT_FILE_rzv2h-dev = "rz-image-bootpart-mmc.wks"
WKS_DEFAULT_FILE_rzv2h-evk-alpha = "rz-image-bootpart-esd_rzv2h.wks"
WKS_DEFAULT_FILE_rzv2h-evk-ver1 = "rz-image-bootpart-esd_rzv2h.wks"
# Defines additional free disk space created in the image in Kbytes.
IMAGE_ROOTFS_EXTRA_SPACE = "<mark style="background: #ffff00">8388608</mark>"
...
</code></pre>
      The table below shows examples of setting values written in <b><code>local.conf</code></b> file.<br>
      <div class="note">
        <span class="note-title">Note</span>
        If you have customized Linux, the disk image size may differ from the table.
      </div>
      <table class="mytable">
        <tr>
          <th>SD card image size<br>(Gbytes)</th>
          <th>Setting values in the "local.conf" file<br>(Kbytes)</th>
        </tr>
        <tr>
          <td>4</td>
          <td>1048576</td>
        </tr>
        <tr>
          <td>8</td>
          <td>4194304</td>
        </tr>
        <tr>
          <td>16</td>
          <td>8388608 (default)</td>
        </tr>
      </table>
    </li>
  </ol>
After this procedure, please proceed to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}#step3-8"> Step 3-8 in How to build RZ/V2H AI SDK Source Code</a> to build the Linux kernel files.
<br><br>

<h3 id="A3">Appendix 3: Prepare Video Codec Library for H.264 Enc/Dec and H.265 Enc/Dec function</h3>
This section explains how to prepare Video Codec Library for H.264 Enc/Dec and H.265 Enc/Dec function.<br>
<div class="note">
  <span class="note-title">Note</span>
  Following instruction assumes that you have completed <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}#step3-6">Step 3-6 in How to build RZ/V2H AI SDK Source Code</a>.
</div>
  <ol>
    <li>Download zip file from the link below.
      <br><br>
      <a class="btn btn-primary download-button" href="https://www.renesas.com/document/swo/rzv2h-linux-video-codecs-library-package-rtk0ef0192z00001zjzip" role="button">Download Link</a>
    </li>
    <br>
    <li>After you downloaded the zip file, please move the zip file to "<b><code>${WORK}/src_setup</code></b>" on your Linux PC.
    <br>
    </li>
    <br>
    <li>Check that zip file are moved to appropriate location.
{% highlight shell %}
cd ${WORK}/src_setup
ls -1 
{% endhighlight %}
      <ul>
        <li>If the above command prints followings, the package is extracted correctly.
{% highlight shell %}
README.txt
RTK0EF0192Z00001ZJ.zip
rzv2h_ai-sdk_yocto_recipe_v4.00.tar.gz
yocto
{% endhighlight %}
        </li>
      </ul>
    </li>
    <li>Run the below command to delete current Video Codec Library and OpenCVA directories.<br>
{% highlight shell %}
rm -rf ${YOCTO_WORK}/meta-rz-features/meta-rz-codecs
rm -rf ${YOCTO_WORK}/meta-rz-features/meta-rz-opencva
{% endhighlight %}
    </li>
    <li>Run the below command to extract the Video Codec Library for H.264 Enc/Dec and H.265 Enc/Dec function.<br>
{% highlight shell %}
unzip RTK0EF0192Z00001ZJ.zip
tar xvf RTK0EF0192Z00001ZJ/meta-rz-features.tar.gz -C ${YOCTO_WORK}
{% endhighlight %}
    </li>
    <li>Run the below command to apply a patch file to add Video Codec Library.<br>
{% highlight shell %}
cd ${YOCTO_WORK}
patch -p1 -d meta-renesas < ${WORK}/src_setup/RTK0EF0192Z00001ZJ/0001-rzv2h-conf-r9a09g057-Add-hwcodec-to-MACHINE_FEATURE.patch
{% endhighlight %}
    </li>
  </ol>
After this procedure, please proceed to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}#step3-7"> Step 3-7 in How to build RZ/V2H AI SDK Source Code</a> to start building Linux kernel files.
<br><br>

<div class="row">
  <div class="col-12" align="right">
    <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}" role="button">
      Back to Home >
    </a>
  </div>
</div>