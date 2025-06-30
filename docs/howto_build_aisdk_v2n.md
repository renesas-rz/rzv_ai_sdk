---
layout: default
---
<div class="container">
    <div class="row">
        <div class="top col-12">
          How to build RZ/V2N AI SDK Source Code
        </div>
    </div>
</div>
<br>
<br>
<h5>This page explains how to build Linux with <b>RZ/V2N AI SDK Source Code.</b></h5>

<h5>Supported version: <b>RZ/V2N AI SDK v6.00</b></h5>

<h3 id="intro" >Introduction</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      AI SDK is a quick and easy AI Application development environment.<br>
      It is specifically made for RZ/V2N Evaluation Board Kit with fixed Linux components.<br>
      (For more information, please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" target="_blank" rel="noopener noreferrer">Getting Started</a> and <a href="{{ site.url }}{{ site.baseurl }}{% link ai-sdk.md %}" target="_blank" rel="noopener noreferrer">AI SDK</a>.)<br>
      <br>
      To modify Linux component, you need to build AI SDK from source code.<br>
      AI SDK Source Code can generate the same Linux environment as AI SDK.<br>
      <br>
    </div>
  </div>
</div>
<div class="col-12  col-md-6 text-center">
  <a href="img/aisdk_sc_v2n.svg" data-lightbox="group"><img src="img/aisdk_sc_v2n.svg" alt="AI Application and AI SDK software"></a><br>
</div>
<div class="container">
  <div class="row">
    <div class="col-12">
      <br>
      This page explains how to build AI SDK Source Code.<br>
      After you have completed this page, you would be able to change the source code and customize Linux environment (i.e., memory map, additional OSS etc...).<br>
      To customize the Linux environment, please refer to <a href="https://www.renesas.com/document/mas/bsp-manual-set-rzg2l-rzfive-rzv2l-and-rzv2n-group-rtk0ef0045z9006azj-v401zip">RZ/V2N BSP Manual Set</a>.<br>
      <br>
      <div class="note">
        <span class="note-title">Requirement</span>
        <ol>
          <li>Users have launched RZ/V2N Evaluation Board Kit according to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" target="_blank" rel="noopener noreferrer">Getting Started</a>, which means they can run <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}" target="_blank" rel="noopener noreferrer">AI Application</a> on the board.<br>
          </li>
          <li>To build Yocto Linux, the below equipment should be prepared.<br>
            <table class="gstable">
              <tr>
                <th>Equipment</th>
                <th colspan="2">Details</th>
              </tr>
              <tr>
                <td rowspan="2">Linux PC</td>
                <td colspan="2">Approximately <b>200GB free space</b> is necessary.</td>
              </tr>
              <tr>
                <td>OS</td>
                <td><b>Ubuntu 22.04 LTS</b><br>
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

<h3 id="step1" >Step 1: Obtain RZ/V2N AI SDK Source Code</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      Download the RZ/V2N AI SDK Source Code from the link below.<br><br>
      <a class="btn btn-primary download-button" href="https://www.renesas.com/document/sws/rzv2n-ai-sdk-v600-source-code" role="button" target="_blank" rel="noopener noreferrer">Download Link</a>
      <br><br>
 	    AI SDK Source Code (<b><code>RTK0EF0189F*_linux-src.zip</code></b>) contains following files:<br>
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
          <td>rzv2n_ai-sdk_yocto_recipe_*.tar.gz</td>
          <td>Yocto recipe.<br>
          Yocto recipes are text files that contains necessary information to build Yocto Linux.</td>
        </tr>
        <tr>
          <td>oss_pkg_rzv_v*.7z</td>
          <td>OSS package.<br>
            OSS package is a set of Open Source Software source code used when building the Yocto Linux.<br>
            AI SDK Source Code provides this file to reproduce the same Linux environment provided in RZ/V2N AI SDK.
          </td>
        </tr>
      </table>
    </div>
  </div>
</div>
<br>

<h3 id="step2" >Step 2: Extract RZ/V2N AI SDK Source Code</h3>
<br>
This step explains how to extract RZ/V2N AI SDK Source Code zip file.
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
      If not, please register the working directory path to an environment variable according to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step4" target="_blank" rel="noopener noreferrer">Step4: Extract RZ/V AI SDK package in Getting Started</a>.
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
  <li>Extract RZ/V2N AI SDK Sorce Code zip file.
{% highlight shell %}
unzip <Path to the file>/RTK0EF0189F*_linux-src.zip -d ${WORK}/src_setup
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
oss_pkg_rzv_v*.7z 
rzv2n_ai-sdk_yocto_recipe_*.tar.gz
{% endhighlight %}
      </li>
    </ul>
  </li>
</ol>
<br>

<h3 id="step3" >Step 3: Build RZ/V2N AI SDK Source Code</h3>
This step explains how to build Linux environment with RZ/V2N AI SDK Source Code.
<ol>
  <li id="step3-1"> To install necessary sofware, run the following commands on your Linux PC.
{% highlight shell%}
sudo apt-get update
sudo apt-get install gawk wget git diffstat unzip texinfo gcc build-essential \
chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils \
iputils-ping python3-git python3-jinja2 python3-subunit zstd liblz4-tool file \
locales libacl1 bmap-tools
{% endhighlight %}
  </li>
  <li id="step3-2">Run the following commands and set the user name and email address before starting the build procedure.<br>
    It is needed to avoid errors when using git command to apply patches.
{% highlight shell%}
git config --global user.email "you@example.com"
git config --global user.name "Your Name"
{% endhighlight %}
  </li>
  <li id="step3-3">Register the working directory path to an environment variable.
{% highlight shell%}
export YOCTO_WORK=${WORK}/src_setup/yocto
mkdir -p ${YOCTO_WORK}
{% endhighlight %}
  </li>
  <li id="step3-4">Extract Yocto recipe package.
{% highlight shell%}
cd ${YOCTO_WORK}
tar zxvf ${WORK}/src_setup/rzv2n_ai-sdk_yocto_recipe_*.tar.gz
{% endhighlight %}
  </li>
  <li id="step3-5">Run the following procedures to apply the patch file.<br>
    <ol>
  <!-- MEMO:: Uncomment when patch file is necessary. -->
  <!-- 
      <li>Apply patch files to fix link error.<br>
        <ol type="A">
          <li>
            Obtain the patch file from the link below.
            <table class="mytable">
              <tr>
                <th>Patch file link</th>
                <th>Description</th>
              </tr>
              <tr>
                <td>
                  <a href="https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v4.00/PATCH_FILENAME.patch">
                    PATCH_FILENAME.patch
                  </a>
                </td>
                <td>
                  Write description of patch file.<br>
                  e.g., patch file for fixing glibc link error
                </td>
              </tr>
            </table>
          </li>
          <li>
            Copy and apply the patch file.
{% highlight shell%}
cp <Path to the file>/PATCH_FILENAME.patch ${YOCTO_WORK}
cd ${YOCTO_WORK}/meta-renesas
patch -p1 < ${YOCTO_WORK}/PATCH_FILENAME.patch
{% endhighlight %}
          </li>
        </ol>
      </li>
  -->
      <!-- Release patch file for bus setting -->
      <li id="bus_patch"><b>Optional</b>: Apply patch file for bus setting release.<br>
        If you want to maximize the performance of DRP-AI, please apply the bus setting release patch.<br>
        This patch disables the control that minimizes the impact on operation when each RZ/V2N unit accesses DDR.<br>
        Applying this patch will improve the performance of single functions such as DRP-AI and Codec.<br>
        However, when combining various functions for compound control, the compound operation may not be executed correctly.<br>
        (Streaming stops, problems with the HDMI output screen, etc.)<br>
        such as the stream stopping. Please apply this patch at your own risk.<br>
        <br>
        <ol type="A">
          <li>
            Obtain the patch file from the link below.
            <table class="mytable">
              <tr>
                <th>Patch file link</th>
                <th>Description</th>
              </tr>
              <tr>
                <td>
                  <a href="https://github.com/renesas-rz/rzv_ai_sdk/releases/download/v6.00/0001-system-setting-for-RZV2N-AI_SDK-v6.00.patch">
                    0001-system-setting-for-RZV2N-AI_SDK-v6.00.patch
                  </a>
                </td>
                <td>
                  patch file for bus setting release
                </td>
              </tr>
            </table>
          </li>
          <li>
            Copy and apply the patch file.
{% highlight shell%}
cp <Path to the file>/0001-system-setting-for-RZV2N-AI_SDK-v6.00.patch ${YOCTO_WORK}
cd ${YOCTO_WORK}
patch -p1 -R < 0001-system-setting-for-RZV2N-AI_SDK-v6.00.patch
{% endhighlight %}
          </li>
        </ol>
      </li>
      <!-- e-CAM22 patch file -->
      <li>Get e-CAM22_CURZH camera driver (MIPI) from <i>e-con Systems</i>.<br>
        The e-CAM22_CURZH camera driver (MIPI) used in AI SDK is not included in the RZ/V2N AI SDK Source Code.<br>
        The required driver needs to be obtained through the following procedure.<br>
        <br>
        <ol type="A">
          <li>To build the e-CAM22_CURZH camera driver (MIPI) for RZ/V2N Evaluation Board Kit, contact <i>e-con Systems</i> at <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp" target="_blank" rel="noopener noreferrer">this link</a> to obtain the patch file below.
            <table class="mytable">
              <tr>
                <th>File name</th>
                <th>Description</th>
              </tr>
              <tr>
                <td>e-CAM22_CURZ*.patch</td>
                <td>e-CAM22_CURZH camera driver (MIPI) Yocto patch file for RZ/V2N</td>
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
    </ol>
  </li>
  <li id="step3-6">Check the working directory to confirm Yocto recipes content.
{% highlight shell%}
ls -1 ${YOCTO_WORK}
{% endhighlight %}
    <ul>
      <li>If the above command prints followings, Yocto recipes are extracted correctly.
<!-- MEMO:: Add the patch file if necessary. -->
{% highlight shell%}
0001-system-setting-for-RZV2N-AI_SDK-v6.00.patch  # optional
e-CAM22_CURZ*.patch
meta-arm
meta-econsys
meta-openembedded
meta-renesas
meta-rz-features
patch
poky
{% endhighlight %}
      </li>
    </ul>
  </li>
  <li id="step3-7">Initialize a build using the <b><code>oe-init-build-env</code></b> script in Poky and set   environment variable <b><code>TEMPLATECONF</code></b> to the below path.
{% highlight shell%}
cd ${YOCTO_WORK}
TEMPLATECONF=$PWD/meta-renesas/meta-rz-boards/conf/templates/rz-conf/ source poky/oe-init-build-env build
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
  <li id="step3-9">Run the following procedures to apply the patch files.<br>
    <ol>
      <!-- Settings for AI SDK (offline build settings, 16GB SD card, settings for eSD boot, Cross Compiler settings, startup screen settings) -->
      <li>Apply a patch file for AI SDK settings.<br>
        This patch file applies offline build setting, SD card image size setting, eSD boot setting, Cross Compiler setting, and startup screen setting.
{% highlight shell%}
patch -p1 < ../patch/0000-AI_SDK-settings.patch
{% endhighlight %}
    <div class="note">
      <span class="note-title">Note</span>
      The default size of the microSD card image created in this guide is approximately 16 GB.<br>
      If you would like to change the microSD card image size, please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link dev_guide.md %}#D1" target="_blank" rel="noopener noreferrer">D1: Change the size of the microSD card image in WIC format</a>.<br>
    </div>
  </li>
      <!-- Add Tesseract -->
      <li>Apply a patch file to add Tesseract Open Source OCR Engine for AI applications.
{% highlight shell%}
patch -p1 < ../patch/0001-tesseract.patch
{% endhighlight %}
  </li>
      <!-- Add OpenMP -->
      <li>Apply a patch file to add OpenMP for AI applications.
{% highlight shell%}
patch -p1 < ../patch/0002-openmp.patch
{% endhighlight %}
      </li>
    </ol>
  </li>
  <li id="step3-10">Run the following procedures to extract the OSS package.
    <ol>
      <li>Run the following commands to extract the OSS package to the <b><code>${YOCTO_WORK}/build</code></b> directory. 
{% highlight shell%}
cp ${WORK}/src_setup/oss_pkg_rzv_*.7z ${YOCTO_WORK}
7z x ${YOCTO_WORK}/oss_pkg_rzv_*.7z -o${YOCTO_WORK}/build
{% endhighlight %}
      </li>
      <li>Check the working directory to confirm the package contents.
{% highlight shell%}
ls -1 ${YOCTO_WORK}/build
{% endhighlight %} 
        <ul>
          <li>If the above command prints followings, the package is extracted correctly.
{% highlight shell%}
conf
downloads
{% endhighlight %}
          </li>
        </ul>
      </li><br>
    </ol>
  </li>
  <li id="step3-11">Run the following command to build the <b>Linux kernel files.</b><br>
    (It takes a few hours to finish building depending on the user's host PC performance)
{% highlight shell%}
MACHINE=rzv2n-evk bitbake core-image-weston
{% endhighlight %}
    All necessary files listed below will be generated by the build command and 
	  they will be located in <b><code>${YOCTO_WORK}/build/tmp/deploy/images/rzv2n-evk</code></b> directory.<br>
    <table class="mytable">
      <tr>
        <th>Boot mode</th>
        <th>File name</th>
        <th>Description</th>
      </tr>
      <tr>
        <td>eSD</td>
        <td>
          core-image-weston-rzv2n-evk.rootfs.wic.bmap<br>
          core-image-weston-rzv2n-evk.rootfs.wic.gz
        </td>
        <td>WIC format SD card image</td>
      </tr>
      <tr>
        <td>xSPI</td>
        <td>
          core-image-weston-rzv2n-evk.rootfs.wic.bmap<br>
          core-image-weston-rzv2n-evk.rootfs.wic.gz<br>
          Flash_Writer_SCIF_RZV2N_DEV_LPDDR4X.mot<br>
          bl2_bp_spi-rzv2n-evk.srec<br>
          fip-rzv2n-evk.srec
        </td>
        <td>Boot loader and WIC format SD card image</td>
      </tr>
      <tr>
        <td>eMMC</td>
        <td>
          core-image-weston-rzv2n-evk.rootfs.wic.bmap<br>
          core-image-weston-rzv2n-evk.rootfs.wic.gz<br>
          Flash_Writer_SCIF_RZV2N_DEV_LPDDR4X.mot<br>
          bl2_bp_mmc-rzv2n-evk.srec<br>
          bl2_bp_spi-rzv2n-evk.srec<br>
          fip-rzv2n-evk.srec<br>
          core-image-weston-rzv2n-evk.rootfs.tar.bz2
        </td>
        <td>Boot loader, Root filesystem and WIC format SD card image</td>
      </tr>
    </table>
  </li>
  <li id="step3-12">Run the following command to build <b>cross compiler installer</b>.<br>
{% highlight shell%}
MACHINE=rzv2n-evk bitbake core-image-weston -c populate_sdk
{% endhighlight %}
    A necessary file listed below will be generated by the build command and the cross compiler installer will be located in <b><code>${YOCTO_WORK}/build/tmp/deploy/sdk/rz-vlp-glibc-x86_64-core-image-weston-cortexa55-rzv2n-evk-toolchain-*.sh</code></b>.<br>
    <table class="mytable">
      <tr>
        <th>File name</th>
        <th>Description</th>
      </tr>
      <tr>
        <td>rz-vlp-glibc-x86_64-core-image-weston-cortexa55-rzv2n-evk-toolchain-*.sh</td>
        <td>Cross compiler installer</td>
      </tr>
    </table>
    <div class="note">
      <span class="note-title">Note</span>
      If some errors occurred during the build, 
      please clean the directory and rebuild it after a period of time according to the below commands.
{% highlight shell%}
cd ${YOCTO_WORK}/build
MACHINE=rzv2n-evk bitbake core-image-weston -c cleanall
{% endhighlight %}
      And run the build command again.
      <ul>
        <li>For Linux kernel files
{% highlight shell%}
MACHINE=rzv2n-evk bitbake core-image-weston
{% endhighlight %}  
        </li>
        <li>For cross compiler installer
{% highlight shell%}
MACHINE=rzv2n-evk bitbake core-image-weston -c populate_sdk
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
You have prepared following files, which is same as the one provided in <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step3" target="_blank" rel="noopener noreferrer">Step 3: Obtain RZ/V2N AI SDK in Getting Started</a>, and you can run <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}" target="_blank" rel="noopener noreferrer">AI Applications</a> according to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" target="_blank" rel="noopener noreferrer">Getting Started</a>.<br>
For more information on how to use each files, see the link in the How to use column.
<br>
<table class="mytable">
  <tr>
    <th>Path</th>
    <th>File name</th>
    <th>Description</th>
    <th>How to use</th>
  </tr>
  <tr>
    <td rowspan="3">${YOCTO_WORK}/build/tmp/deploy/images/rzv2n-evk</td>
    <td>
      core-image-weston-rzv2n-evk.rootfs.wic.bmap<br>
      core-image-weston-rzv2n-evk.rootfs.wic.gz
    </td>
    <td>WIC format SD card image</td>
    <td>
      <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started_v2n.md %}#step7-1" target="_blank" rel="noopener noreferrer">Step 7-1: Setup RZ/V2N EVK in RZ/V2N EVK Getting Started</a>
    </td>
  </tr>
  <tr>
    <td>
      Flash_Writer_SCIF_RZV2N_DEV_LPDDR4X.mot<br>
      bl2_bp_spi-rzv2n-evk.srec<br>
      fip-rzv2n-evk.srec
    </td>
    <td>Boot loader used when booting from xSPI</td>
    <td>
      <a href="{{ site.url }}{{ site.baseurl }}{% link dev_guide.md %}#D3" target="_blank" rel="noopener noreferrer">D3.How to boot from xSPI in Developer's Guide</a>
    </td>
  </tr>
  <tr>
    <td>
      Flash_Writer_SCIF_RZV2N_DEV_LPDDR4X.mot<br>
      bl2_bp_mmc-rzv2n-evk.srec<br>
      bl2_bp_spi-rzv2n-evk.srec<br>
      fip-rzv2n-evk.srec<br>
      core-image-weston-rzv2n-evk.rootfs.tar.bz2
    </td>
    <td>Boot loader and Root filesystem used when booting from eMMC</td>
    <td>
      <a href="{{ site.url }}{{ site.baseurl }}{% link dev_guide.md %}#D4" target="_blank" rel="noopener noreferrer">D4.How to boot from eMMC in Developer's Guide</a>
    </td>
  </tr>
  <tr>
    <td>${YOCTO_WORK}/build/tmp/deploy/sdk</td>
    <td>rz-vlp-glibc-x86_64-core-image-weston-cortexa55-rzv2n-evk-toolchain-*.sh</td>
    <td>Cross compiler installer</td>
    <td>
      After replacing the file in <b><code>${WORK}/ai_sdk_setup</code></b> directory with this file, follow the steps below to setup RZ/V AI SDK.<br>
      <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step5" target="_blank" rel="noopener noreferrer">Step 5: Setup RZ/V AI SDK in Getting Started</a>
    </td>
  </tr>
</table>
<div class="note">
  <span class="note-title">Note 1</span>
  For more Yocto Project information, please refer the link below:<br>
  <a href="https://docs.yoctoproject.org/5.0.6/brief-yoctoprojectqs/index.html" target="_blank" rel="noopener noreferrer">https://docs.yoctoproject.org/5.0.6/brief-yoctoprojectqs/index.html</a>
</div>
<div class="note">
  <span class="note-title">Note 2</span>
  When customizing Linux development environment, following information may help.<br>
  <ul>
    <li>
      <a href="https://docs.yoctoproject.org/" target="_blank" rel="noopener noreferrer">https://docs.yoctoproject.org/</a>
    </li>
    <li>
      <a href="https://www.renesas.com/document/mas/bsp-manual-set-rzg2l-rzfive-rzv2l-and-rzv2n-group-rtk0ef0045z9006azj-v401zip" target="_blank" rel="noopener noreferrer">RZ/V2N BSP Manual Set</a>
    </li>
  </ul>
</div>
<div class="note">
  <span class="note-title">Note 3</span>
  To add more functionality to AI SDK, please refer to following URL.
  <ul>
<!--    <li>
      <a href="https://www.renesas.com/software-tool/rzv2n-ros2-package" target="_blank" rel="noopener noreferrer">RZ/V2N ROS2 Package</a>
    </li> -->
    <li>
      <a href="https://www.renesas.com/software-tool/rzv-group-multi-os-package" target="_blank" rel="noopener noreferrer">RZ/V Multi-OS Package</a>
    </li>
    <li>
      <a href="https://www.renesas.com/software-tool/rz-mpu-security-package" target="_blank" rel="noopener noreferrer">RZ MPU Security Package</a>
    </li>
    <li>
      <a href="https://www.renesas.com/software-tool/rzv2n-isp-support-package" target="_blank" rel="noopener noreferrer">RZ/V2N ISP Support Package</a>
    </li>
  </ul>
</div>
<div class="note">
  <span class="note-title">Note 4</span>
    Regarding the eSD (Embedded SD) booting, please note the following:
    <ul class="mb-1">
      <li>The eSD boot procedure using microSD card described in this guide is for evaluation purposes only.</li>
      <li>If you use the eSD boot, please implement the eSD on your board according to the standard "SD Specification Part 1 eSD Addendum (version 2.10)".</li>
      <li>The reboot command cannot be used when using the eSD boot procedure using microSD card described in this guide.</li>
    </ul>
</div>
<br>
If you have any questions about AI SDK Source Code,<br>
please add new issues to AI SDK GitHub issues.<br>
<br>
<a class="btn btn-primary download-button" href="https://github.com/renesas-rz/rzv_ai_sdk/issues" role="button" target="_blank" rel="noopener noreferrer">Go to GitHub issues</a>

<div class="row">
  <div class="col-12" align="right">
    <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}" role="button">
      Back to Home >
    </a>
  </div>
</div>
<br><br>