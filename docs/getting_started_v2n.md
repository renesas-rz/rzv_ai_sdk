---
layout: default
---
<script type="text/javascript" src="http://code.jquery.com/jquery-3.7.0.min.js"></script>
<script>
  $(function(){
    $("#reference_terminology").load("{{ site.url }}{{ site.baseurl }}{% link getting_started.md %} reference_terminology");
  });
</script>
<div class="container">
    <div class="row">
        <div id="page-top" class="top col-12">
RZ/V2N EVK Getting Started
        </div>
    </div>
</div>
<br>
<br>
<h5>This page explains how to start-up the AI SDK on the <b>RZ/V2N Evaluation Board Kit</b>.</h5>

<h5>Supported version: <b>RZ/V2N AI SDK v6.00</b></h5>

<details class="boxdetails" open>
  <summary>Terminology</summary>
  <quotedoc id="reference_terminology"></quotedoc>
</details>
<br>

<h3>Getting Started Flow</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      This page explains RZ/V2N EVK dependent instructions.<br>
      Common instructions are explained in <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" target="_blank" rel="noopener noreferrer"> Getting Started</a> page.<br>
      <img src="img/getting_started_flow_v2n.svg" alt="flow" height="580px"/>
      <br>
    </div>
  </div>
</div>
<h3 id="intro" >Introduction</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      <h4 class="u_line" >Prerequisites</h4>
      <div class="container">
        <div class="row">
          <div class="col-12">
           Before reading this document, users are required to read <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" target="_blank" rel="noopener noreferrer">Getting Started</a>.<br>
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" role="button" target="_blank" rel="noopener noreferrer">
              <span class="banner-title">Getting Started </span>
              <span class="banner-line">
              What kind of equipment is necessary?<br>
              How can I get RZ/V AI SDK?<br>
              How can I setup RZ/V AI SDK?<br>
              How can I build AI Applications source code?<br>
              </span>
            </a>
          </div>
        </div>
      </div>
    </div>
    <div class="col-12">
      <h4 class="u_line" >RZ/V2N EVK</h4>
      <div class="container">
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
          </div>
          <div class="col-3">
            <img src="img/V2N_EVK.jpeg" alt="board"/>
          </div>
        </div>
        <div class="row">
          <div class="col-12">
            Following items are included in the RZ/V2N EVK.
            <br>
            <br>
            <table class="gstable">
              <tr>
                <th>Equipment</th>
                <th>Details</th>
              </tr>
              <tr>
                <td>RZ/V2N Evaluation Board</td>
                <td>Evaluation board itself.</td>
              </tr>
            </table>
          </div>
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
      <h3 id="step7" >Step 7: Deploy AI Application</h3>
      This section explains how to deploy the AI Application to the RZ/V2N EVK.
      <br>
      <br>
      <div class="note">
        <span class="note-title">Before reading this step</span>
        Users are required to read Step 1~6 of <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" target="_blank" rel="noopener noreferrer">Getting Started</a>.<br>
        <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" role="button" target="_blank" rel="noopener noreferrer">
          <span class="banner-title">Getting Started Step 1~6 </span>
          <span class="banner-line">
            What kind of equipment is necessary?<br>
            Where to get RZ/V AI SDK?<br>
            How can I setup RZ/V AI SDK?<br>
            How can I build AI Applications source code?<br>
          </span>
        </a>
      </div>
      <br>
      To boot the board, bootloader and other Linux necessary files are required.<br>
      There are two types of bootloader available on RZ/V2N AI SDK.<br>
      <ul>
        <li>
          <b>eSD Bootloader</b>: The board boots up using the bootloader written on microSD card.
        </li>
        <li>
          <b>xSPI Bootloader</b>: The board boots up using the bootloader written in Flash ROM on the board.
        </li>
      </ul>
      Other necessary files, i.e. Linux kernel and root filesystem, are stored on microSD card.<br>
      You can use Linux PC to format the microSD card and expand the kernel and the root filesystem using SD card reader.<br>
      <br>
      <img class="procedure2" src="img/esd_spi.svg" alt="docker" style="max-height: 200px" />
      <br>
      <div class="note">
        <span class="note-title">Note</span>
        Regarding the eSD (Embedded SD) booting, please note the following:
        <ul class="mb-1">
          <li>The eSD boot procedure using microSD card described in this guide is for evaluation purposes only.</li>
          <li>If you use the eSD boot, please implement the eSD on your board according to the standard "SD Specification Part 1 eSD Addendum (version 2.10)".</li>
          <li>The reboot command cannot be used when using the eSD boot procedure using microSD card described in this guide.</li>
        </ul>
      </div>
      <br>
      <h4 id="step7prep" class="u_line" >Preparation</h4>
      <div class="note">
        <span class="note-title">Click the button</span>
        This step contains both eSD and xSPI Bootloader explanation.<br>
        Please click the button below to update the explanation according to your bootloader interface.<br>
        <div class="SelectButton">
          <span class="ButtoneSD">eSD Bootloader</span>
          <span class="ButtonSPI">xSPI Bootloader</span>
        </div>
        <div class="ContenteSD contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          eSD explanation will be shown in this style if you click "eSD Bootloader" button above.
        </div>
        <div class="ContentSPI contentSPI-bg">
          <span class="ContentSPI-title">For xSPI</span>
          xSPI explanation will be shown in this style if you click "SPI Bootloader" button above.
        </div>
      </div>
      <br>
      <h4 id="step7-1" class="u_line">1. Setup RZ/V2N EVK </h4>
      <div class="ContenteSD">
        <div class="contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          microSD card needs to contain bootloaders, the Linux kernel and root filesystem to boot-up the board.<br>
          RZ/V2N AI SDK supports the WIC format for SD card image.<br>
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
          RZ/V2N AI SDK supports the WIC format for SD card image.<br>
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
        If you would like to expand the SD card image size, please build the RZ/V2N AI SDK Source Code according to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2n.md %}" target="_blank" rel="noopener noreferrer">How to Build RZ/V2N AI SDK</a>.
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
        <br><br>
        </div>
        <div class="ContentSPI contentSPI-bg">
          <span class="ContentSPI-title">For xSPI</span>
          Run the below command to decompress <code>${WORK}/board_setup/xSPI.zip</code>.<br>
{% highlight shell %}
cd ${WORK}/board_setup
unzip xSPI.zip
{% endhighlight %}
        Following files are necessary.<br>
        They are in the <code>${WORK}/board_setup/xSPI</code> directory.
        <br><br>
        </div>
        <table class="gstable">
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
                  <li><b><code>/dev/sdb1</code></b>: The paritition name in microSD card.  There may be multiple <code>sdb*</code> depending on the microSD card.
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
{% highlight shell %}
Filesystem      Size  Used Avail Use% Mounted on
:
snip
:
/dev/sdb1        18M  3.9M   15M   22% /media/user/bootloader
/dev/sdb2        12G  2.4G   8.9G  22% /media/user/root
{% endhighlight %}
                <div class="warning">
                  <span class="warning-title">Warning</span>
                  Here, we use "<b><code>/dev/sdb</code></b>" as microSD card device name.
                </div>
              </li>
            </ul>
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
          </li>
<!--          <li>Run the following commands to setup the partition 2, which is the root filesystem of the board.<br>
{% highlight shell %}
sudo mkdir /mnt/sd -p
sudo mount /dev/sdb2 /mnt/sd
sudo cp $WORK/ai_sdk_setup/data/libtvm_runtime.so /mnt/sd/usr/lib64
sync
sudo umount /mnt/sd
{% endhighlight %}
            <div class="warning">
              <span class="warning-title">Warning</span>
              Change <code>/dev/sdb</code> to your microSD card device name.<br>
            </div>
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
          </li> -->
        </ol>
        <h5 id="step7-1c">
          <span class="ContentSPI">
          <li type="A">
            Write the bootloaders to Flash ROM
          </li>
          </span>
        </h5>
        <div class="ContentSPI">
          <div class="contentSPI-bg">
            <span class="ContentSPI-title">For xSPI</span>
            Please write the bootloaders to Flash ROM on the board according to <a href="{{ site.url }}{{ site.baseurl }}{% link dev_guide.md %}#D3" target="_blank" rel="noopener noreferrer">D3.How to boot from xSPI</a>.
          </div>
        </div>
      </ol>
      <br>
      <h4 id="step7-2" class="u_line">2. Deploy Application to the Board</h4>
      This section explains how to copy the <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step6" target="_blank" rel="noopener noreferrer">application binary created in Step 6</a> to the board.<br>
      Users are expected to have finished the instructions in <a href="#step7" target="_blank" rel="noopener noreferrer"> Setup RZ/V2N EVK in Step 7-1</a>.
      <br>
      <br>
      <ol>
        <li>
          Insert the microSD card to Linux PC.
        </li><br>
        <li>
          Run the following commands to mount the partition 2, which contains the root filesystem.<br>
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
          Check the <code>README.md</code> document provided in application directory and follow the instruction in the chapter called <b>"Application: Deploy Stage"</b> (or similar) to deploy the application.<br>
          <br>
<!--          <div class="note">
            <span class="note-title">Note</span>
            Since RZ/V2N is a brother chip of RZ/V2H, users can use the AI Application for RZ/V2H on the RZ/V2N EVK.<br>
            Please use source code and object files for RZ/V2H, and follow the steps <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v6.00/R01_object_detection#application-build-stage" target="_blank" rel="noopener noreferrer">Application: Build Stage</a> to build the application in the RZ/V2N AI SDK environment.
          </div> -->
          <div class="box1">
            <u><b>Example:</b></u><br>
            In <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v6.00/R01_object_detection" target="_blank" rel="noopener noreferrer">R01_object_detection</a> application, follow the instruction in <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v6.00/R01_object_detection#application-deploy-stage" target="_blank" rel="noopener noreferrer">here</a> to find files to be copied.
          </div>
          Use the following command to copy the files to root filesystem.
          <br><br>
{% highlight shell %}
sudo cp $WORK/ai_sdk_setup/data/<Path to target file>/<filename> /mnt/sd/home/weston/tvm 
{% endhighlight %}
          <br>
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
      <h4 id="step7-3" class="u_line">3. Boot RZ/V2N EVK</h4>
      This section explains how to boot the RZ/V2N EVK.<br>
      <br>
      <div class="note">
        <span class="note-title">Requirement</span>
        The included SD card sub board must be attached on the RZ/V2N EVK.<br>
        For the RZ/V2N EVK, see <a href="https://www.renesas.com/products/microcontrollers-microprocessors/rz-mpus/rzv2n-evk-rzv2n-quad-core-vision-ai-mpu-evaluation-kit" target="_blank" rel="noopener noreferrer">RZ/V2N Evaluation Board Kit Hardware Manual</a>.
      </div>
      <br>
      <div class="SelectButton">
        <span class="ButtoneSD">eSD Bootloader</span>
        <span class="ButtonSPI">xSPI Bootloader</span>
      </div>
      <br>
      Follow the instruction below to boot the board.
      <br>
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
                      Use the microSD card slot <b>SD1</b> on the <b>Board</b> as shown in the figure.
                    </div>
                  </li><br>
                  <li>Change DSW1 and DSW2 setting as shown in the figure.</li><br>
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
              <div class="col-12 col-md-6">
                <a href="img/v2n_evk_boot_esd.png" data-lightbox="group"><img class="procedure" src="img/v2n_evk_boot_esd.png" alt="boot" width="90%"/></a>
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
            <br><br>
          </div>
        </reference3>
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
            <div class="col-12 col-md-6">
              <a href="img/v2n_evk_boot_spi.png" data-lightbox="group"><img class="procedure" src="img/v2n_evk_boot_spi.png" alt="boot" width="90%"/></a>
            </div>
          </div>  
          <br>
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
          <br><br>
        </div>
      </div>
      <br>
      After the boot up, please go back to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step8" target="_blank" rel="noopener noreferrer">Getting Started Step 8</a> or proceed directly to <a href="#step8" target="_blank" rel="noopener noreferrer">RZ/V2N EVK Getting Started Step 8</a>.
      <br><br>
    </div>
  </div>
</div>

<div class="container">
  <div class="row">
    <div class="col-12">
      <h3 id="step8" >Step 8: Run AI Application</h3>
      <div class="note">
        <span class="note-title">Before reading this step</span>
        Users are required to read Step 7 of <a href="#step7" target="_blank" rel="noopener noreferrer">RZ/V2N EVK Getting Started</a>.<br>
        <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="#step7" role="button" target="_blank" rel="noopener noreferrer">
          <span class="banner-title">RZ/V2N EVK Getting Started Step 7 </span>
          <span class="banner-line">
          How can I setup microSD card for eSD Bootloader?<br>
          How can I deploy applications to the board?<br>
          How can I boot the board?<br>
          </span>
        </a>
      </div>
      <ol>
        <li>
          Follow the instructions explained in the document (<code>README.md</code>) of applications on GitHub.
          <br><br>
          <div class="box1">
            <u><b>Example:</b></u><br>
            For <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v6.00/R01_object_detection" target="_blank" rel="noopener noreferrer">R01_object_detection</a> application, follow the instruction <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v6.00/R01_object_detection#application-run-stage" target="_blank" rel="noopener noreferrer">here</a> to run the application.<br>
            <!-- Users can use the AI Application for RZ/V2H on the RZ/V2N EVK.<br>
            Please use source code and object files for RZ/V2H, and follow the steps <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v6.00/R01_object_detection#application-build-stage" target="_blank" rel="noopener noreferrer">Application: Build Stage</a> to build the application in the RZ/V2N AI SDK environment.
            <br> -->
            If you have successfully run the application, you will see following window on HDMI screen.
            <br><br>
            <img src="img/objectdetection_v2n.png" alt="object_detection" width="90%"/>
          </div>
          <br>
        </li>
      </ol>
      <div class="note">
        <span class="note-title">Note1</span>
        To shutdown the board safely, please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link appendix.md %}#A5" target="_blank" rel="noopener noreferrer">A4. Shutdown RZ/V2N EVK</a>.
      </div>
      <div class="note">
        <span class="note-title">Note2</span>
        When running an AI Application, the following warning may be shown. It does not affect the operation.<br>
        <h6 class="mb-1">
{% highlight shell %}
[ WARN:0@xx.xxx] global cap_gstreamer.cpp:1777 open OpenCV | GStreamer warning: Cannot query video position: status=0, value=-1, duration=-1
{% endhighlight %}
        </h6>
      </div>
    </div>
  </div>
</div>
<br><br>

<div class="container">
  <div class="row">
    <div class="col-12">
      <h4 class="u_line">This is the end of RZ/V2N EVK Getting Started.</h4>
      To see what comes next, please refer to the Getting Started Ending.<br>
      <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#ending" role="button" target="_blank" rel="noopener noreferrer">
        <span class="banner-title">Getting Started Ending </span>
        <span class="banner-line">
        What is the next step of Getting Started?<br>
        </span>
      </a>
    </div>
  </div>
</div>
<br>
<div class="container">
  <div class="row">
    <div class="col-12" align="right">
      <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link getting_started_v2n.md %}#page-top" role="button">
Back to Top >
      </a>
    </div>
  </div>
</div>
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
  elm.addEventListener("click", ()=>{
    BootType = (BootType === "eSD") ? "SPI": "eSD";
    // document.cookie = `BootType=${BootType};max-age=86400;path=/`;
    dispBootType();
  });
})
dispBootType();
</script>
