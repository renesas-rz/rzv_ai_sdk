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
        <div class="top col-12">
RZ/V2L EVK Getting Started
        </div>
    </div>
</div>
<br>
<br>
<h5>This page explains how to start-up the AI SDK on the <b>RZ/V2L Evaluation Board Kit</b>.</h5>

<h5>Supported version: <b>RZ/V2L AI SDK v2.10</b></h5>

<details class="boxdetails" open>
  <summary>Terminology</summary>
<quotedoc id="reference_terminology"></quotedoc>
</details>
<br>

<h3>Getting Started Flow</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
        This page explains RZ/V2L EVK dependent instructions.<br>
        Common instructions are explained in <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}"> Getting Started</a> page.<br>
        <img src="img/getting_started_flow_v2l.svg" alt="flow" height="400px"/>
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
            Before reading this document, users are required to read <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}">Getting Started</a>.<br>
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" role="button">
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
  </div>
</div>
<br>
<br>

<div class="container">
  <div class="row">
    <div class="col-12">
      <h3 id="step7" >Step 7: Deploy AI Application</h3>
      This section explains how to deploy the AI Application to the RZ/V2L EVK.
      <br>
      <br>
      <div class="note">
        <span class="note-title">Before reading this step</span>
        Users are required to read Step 1~6 of <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}">Getting Started</a>.<br>
        <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}" role="button">
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
      There are two types of bootloader available on RZ/V2L AI SDK.<br>
      <ul>
        <li>
          <b>eSD Bootloader</b>: The board boots up using the bootloader written on microSD card.
        </li>
        <li>
          <b>eMMC Bootloader</b>: The board boots up using the bootloader written in eMMC on the board.
        </li>
      </ul>
      Other necessary files, i.e. Linux kernel and root filesystem, are stored on microSD card.<br>
      You can use Linux PC to format the microSD card and expand the kernel and the root filesystem using SD card reader.<br>
      <img class="procedure2" src="img/esd_emmc.svg" alt="docker" width="90%"/>
      <br>
      <br>
      <h4 id="step7prep" class="u_line" >Preparation</h4>
      <div class="note">
        <span class="note-title">Click the button</span>
        This step contains both eSD and eMMC Bootloader explanation.<br>
        Please click the button below to update the explanation according to your bootloader interface.<br>
        <div class="SelectButton">
          <span class="ButtoneSD">eSD Bootloader</span>
          <span class="ButtoneMMC">eMMC Bootloader</span>
        </div>
        <div class="ContenteSD contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          eSD explanation will be shown in this style if you click "eSD Bootloader" button above.
        </div>
        <div class="ContenteMMC contenteMMC-bg">
          <span class="ContenteMMC-title">For eMMC</span>
          eMMC explanation will be shown in this style if you click "eMMC Bootloader" button above.
        </div>
      </div>
      <br>
      <h4 id="step7-1" class="u_line">1. Setup RZ/V2L EVK </h4>
      <div class="ContenteSD">
        <div class="contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          microSD card needs to contain bootloaders, the Linux kernel and root filesystem to boot-up the board.<br>
          You can use Linux PC to format the microSD card and expand the kernel and the root filesystem using SD card reader.<br>
        </div>
        <div class="note">
          <span class="note-title">Note</span>
          This step is required only when starting the AI SDK or when using the new version of AI SDK.<br>
          If you have already setup the microSD card with the latest bootloader, Linux kernel, Linux device tree file and root filesystem, <span class="skip">skip this step</span> and proceed to <a href="#step7-2">the next procedure (2. Deploy Application to the Board)</a>.
        </div>
      </div>
      <div class="ContenteMMC">
        <div class="contenteMMC-bg">
          <span class="ContenteMMC-title">For eMMC</span>
          microSD card needs to contain the Linux kernel and root filesystem to boot-up the board.<br>
          You can use Linux PC to format the microSD card and expand the kernel and the root filesystem using SD card reader.<br>
          Bootloaders must be written in eMMC on the board.
          You can use Windows PC to write the bootloaders on eMMC.
        </div>
        <div class="note">
          <span class="note-title">Note</span>
          This step is required only when starting the AI SDK or when using the new version of AI SDK.<br>
          If you have already setup the microSD card and the bootloader written in eMMC on the board, <span class="skip">skip this step</span> and proceed to <a href="#step7-2">the next procedure (2. Deploy Application to the Board)</a>. 
        </div>
      </div>
      <ol>
        <h5 id="step7-1a">
          <li type="A">Format SD card<br></li>
        </h5>
        Create the following partitions on microSD card according to <a href="{{ site.url }}{{ site.baseurl }}{% link appendix.md %}#A2">Appendix: A2. Format SD card</a>.<br>
        <div class="ContenteSD contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          <table class="gstable">
            <tr>
              <th>Type/Number</th>
              <th>Size</th>
              <th>Type of Filesystem</th>
              <th>Contents</th>
            </tr>
            <tr>
              <td>Primary #1</td>
              <td>500MB (minimum 128MB)</td>
              <td>Ext4</td>
              <td>Linux kernel<br>Device tree</td>
            </tr>
            <tr>
              <td>Primary #2</td>
              <td>All remaining</td>
              <td>Ext4</td>
              <td>Root filesystem</td>
            </tr>
          </table>
        </div>
        <div class="ContenteMMC contenteMMC-bg">
          <span class="ContenteMMC-title">For eMMC</span>
          <table class="gstable">
            <tr>
              <th>Type/Number</th>
              <th>Size</th>
              <th>Type of Filesystem</th>
              <th>Contents</th>
            </tr>
            <tr>
              <td>Primary #1</td>
              <td>500MB (minimum 128MB)</td>
              <td>FAT32</td>
              <td>Linux kernel<br>Device tree</td>
            </tr>
            <tr>
              <td>Primary #2</td>
              <td>All remaining</td>
              <td>Ext4</td>
              <td>Root filesystem</td>
            </tr>
          </table>
        </div>
        <br>
        <h5 id="step7-1b">
          <li type="A">Write the Linux files to SD card</li>
        </h5>
        <div class="ContenteSD contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
          At first, run the below command to decompress <code>${WORK}/board_setup/eSD.zip</code>.<br>

{% highlight shell %}
cd ${WORK}/board_setup
unzip eSD.zip
{% endhighlight %}
          Following three files are necessary, which must be placed on each partitions on microSD card.<br>
          They are in the <code>${WORK}/board_setup/eSD</code> directory.
          <br><br>
          <table class="gstable">
            <tr>
              <th>File</th>
              <th>Description</th>
              <th>microSD card partition</th>
            </tr>
            <tr>
              <td>Image-smarc-rzv2l.bin</td>
              <td>Linux kernel image<br>(The boot program) </td>
              <td>Partition 1</td>
            </tr>
            <tr>
              <td>Image-r9a07g054l2-smarc.dtb </td>
              <td>Linux device tree file<br>(The configuration file for booting) </td>
              <td>Partition 1</td>
            </tr>
            <tr>
              <td>core-image-weston-smarc-rzv2l.tar.bz2</td>
              <td>Linux Root filesystem</td>
              <td>Partition 2</td>
            </tr>
          </table>
          Follow the instruction below to prepare the microSD card.<br>
          <div class="warning">
            <span class="warning-title">Warning</span>
              Here, we use "<b><code>/dev/sdb</code></b>" as microSD card device name.
          </div>
          <ol>
            <li>Check if the two partitions are created successfully by running <code>df</code> command.<br>
{% highlight shell %}
df -h
Filesystem 	Size		Used	Avail	Use %	Mounted on	
…		…		…	…	…	…
/dev/sdb1		…		…	…	…	…	
/dev/sdb2		…		…	…	…	…	
{% endhighlight %}
              <div class="warning">
                  <span class="warning-title">Warning</span>
                  Device name of microSD card, <code>/dev/sdb</code> may differ depending on your environment.<br>
              </div>
            </li>
            <br>
            <li>Run the following commands to setup the partition 1.<br>
{% highlight shell %}
sudo mkdir -p /mnt/sd
sudo mount /dev/sdb1 /mnt/sd
sudo cp $WORK/board_setup/eSD/Image-smarc-rzv2l.bin /mnt/sd
sudo cp $WORK/board_setup/eSD/Image-r9a07g054l2-smarc.dtb /mnt/sd
sync
sudo umount /mnt/sd
{% endhighlight %}
              <div class="warning">
                <span class="warning-title">Warning</span>
                Change <code>/dev/sdb</code> to your microSD card device name.<br>
              </div>
            </li>
            <li>Run the following commands to setup the partition 2, which is the root filesystem of the board.<br>
{% highlight shell %}
sudo mount /dev/sdb2 /mnt/sd
sudo tar xfj $WORK/board_setup/eSD/core-image-weston-smarc-rzv2l.tar.bz2 -C /mnt/sd
sudo cp $WORK/ai_sdk_setup/data/libtvm_runtime.so /mnt/sd/usr/lib64
sync
sudo umount /mnt/sd
{% endhighlight %}
              <div class="warning">
                <span class="warning-title">Warning</span>
                Change <code>/dev/sdb</code> to your microSD card device name.<br>
              </div>
            </li>
          </ol>
        </div>
        <div class="ContenteMMC contenteMMC-bg">
          <span class="ContenteMMC-title">For eMMC</span>
          Following three files are necessary, which must be placed on each partitions on microSD card.<br>
          They are in the <code>${WORK}/board_setup/eMMC</code> directory.
          <br><br>
          <table class="gstable">
            <tr>
              <th>File</th>
              <th>Description</th>
              <th>microSD card partition</th>
            </tr>
            <tr>
              <td>Image-smarc-rzv2l.bin</td>
              <td>Linux kernel image<br>(The boot program) </td>
              <td>Partition 1</td>
            </tr>
            <tr>
              <td>Image-r9a07g054l2-smarc.dtb </td>
              <td>Linux device tree file<br>(The configuration file for booting) </td>
              <td>Partition 1</td>
            </tr>
            <tr>
              <td>core-image-weston-smarc-rzv2l.tar.bz2</td>
              <td>Linux Root filesystem</td>
              <td>Partition 2</td>
            </tr>
          </table>
          <ol>
            <li>Run the below command to decompress <code>${WORK}/board_setup/eMMC.zip</code>.<br>

{% highlight shell %}
cd ${WORK}/board_setup
unzip eMMC.zip
{% endhighlight %}
            </li>
            <li>Insert the microSD card to Linux PC.
            </li><br>
            <li>
              Check if the two partitions are created successfully by running <code>df</code> command.<br>
{% highlight shell %}
df -h
Filesystem 	Size		Used	Avail	Use %	Mounted on	
…		…		…	…	…	…
/dev/sdb1		…		…	…	…	…	
/dev/sdb2		…		…	…	…	…	
{% endhighlight %}
              <div class="warning">
                <span class="warning-title">Warning</span>
                Device name of microSD card, <code>/dev/sdb</code>, may differ depending on your environment.
              </div>
            </li><br>
            <li>
              Run the following commands to setup the partition 1.<br>
{% highlight shell %}
sudo mkdir -p /mnt/sd
sudo mount /dev/sdb1 /mnt/sd
sudo cp $WORK/board_setup/eMMC/Image-smarc-rzv2l.bin /mnt/sd
sudo cp $WORK/board_setup/eMMC/Image-r9a07g054l2-smarc.dtb /mnt/sd
sync
sudo umount /mnt/sd
{% endhighlight %}
              <div class="warning">
                <span class="warning-title">Warning</span>
                Change <code>/dev/sdb</code>, to your microSD card device name.
              </div>
            </li><br>
            <li>Run the following commands to setup the partition 2, which is the root filesystem of the board.
{% highlight shell %}
sudo mount /dev/sdb2 /mnt/sd
sudo tar xfj $WORK/board_setup/eMMC/core-image-weston-smarc-rzv2l.tar.bz2 -C /mnt/sd
sudo cp $WORK/ai_sdk_setup/data/libtvm_runtime.so /mnt/sd/usr/lib64
sync
sudo umount /mnt/sd
{% endhighlight %}
              <div class="warning">
                <span class="warning-title">Warning</span>
                Change <code>/dev/sdb</code>, to your microSD card device name.
              </div>
              <br>
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
          </ol>
        </div>
      <h5 id="step7-1c">
        <li type="A">
          <span class="ContenteSD">
          Write the bootloaders to SD card
          </span>
          <span class="ContenteMMC">
          Write the bootloaders to eMMC
          </span>
        </li>
      </h5>
      <div class="ContenteSD">
        <div class="contenteSD-bg">
          <span class="ContenteSD-title">For eSD</span>
            Before booting up the board, you must write the latest bootloaders to microSD card.<br>
            This procedures needs to be done only once as long as you use the same version of AI SDK.<br>
            <br>
            There are three files in <code>${WORK}/board_setup/eSD/bootloader</code> to boot up the board.<br>
            <ul>
              <li><code>bl2_bp_esd-smarc-rzv2l_pmic.bin</code></li>
              <li><code>bl2_bp-smarc-rzv2l_pmic.srec</code></li>
              <li><code>fip-smarc-rzv2l_pmic.srec</code></li>
            </ul>
            <br>
            Run the following commands to write these files to the microSD card to boot for eSD.<br>
{% highlight shell %}
cd ${WORK}/board_setup/eSD/bootloader
sudo dd if=bl2_bp_esd-smarc-rzv2l_pmic.bin of=/dev/sdb seek=1 count=1
sudo dd if=bl2-smarc-rzv2l_pmic.bin of=/dev/sdb seek=8
sudo dd if=fip-smarc-rzv2l_pmic.bin of=/dev/sdb seek=128
sync
{% endhighlight %}
            <div class="warning">
              <span class="warning-title">Warning</span>
              Change <code>/dev/sdb</code>, to your microSD card device name.<br>
            </div>
            <br>
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
          </div>
        </div>
        <div class="ContenteMMC">
          <div class="contenteMMC-bg">
            <span class="ContenteMMC-title">For eMMC</span>
            Please write the bootloaders to eMMC on the board according to <a href="{{ site.url }}{{ site.baseurl }}{% link appendix.md %}#A1">Appendix: A1.Setup for eMMC Bootloader</a>.
          </div>
        </div>
      </ol>
      <br>
      <h4 id="step7-2" class="u_line">2. Deploy Application to the Board</h4>
        This section explains how to copy the <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step6">application binary created in Getting Started Step 6</a> to the board.<br>
        Users are expected to have finished the instructions in <a href="#step7"> Setup RZ/V2L EVK in Step 7-1</a>.
        <br>
        <br>
        <ol>
          <li>Insert the microSD card to Linux PC.
          </li><br>
          <li>Run the following command to mount the partition 2, which contains the root filesystem.<br>
{% highlight shell %}
sudo mount /dev/sdb2 /mnt/sd
{% endhighlight %}
            <div class="warning">
              <span class="warning-title">Warning</span>
              Change <code>/dev/sdb</code> to your microSD card device name.<br>
            </div>
          </li>
          <li>Create the application directory on root filesystem.
{% highlight shell %}
sudo mkdir /mnt/sd/home/root/tvm
{% endhighlight %}
            <div class="note">
              <span class="note-title">Note</span>
              Directory name <code>tvm</code> can be determined by user.<br>
            </div>
          </li>
          <li>Copy the necessary files in execution environment.<br>
            Select the appropriate option below based on the application type explained in <a href="#build-instruction">Building instructions in Step 6</a>.
            <br><br>
            <p id="deploy-option1"><b>Option 1: &lt;Application 1&gt;</b></p>
            Check the <code>README.md</code> document provided in application directory and follow the instruction in the chapter called <b>"Application: Deploy Stage"</b> (or similar) to deploy the application.
            <br><br>
            <div class="box1">
              <u><b>Example:</b></u><br>
              In <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v5.00pre/R01_object_detection">R01_object_detection</a> application, follow the instruction in <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v5.00pre/R01_object_detection#application-deploy-stage">here</a> to find files to be copied.
            </div>
            <br>
            Use the following command to copy the files to root filesystem.
            <br><br>
{% highlight shell %}
sudo cp $WORK/ai_sdk_setup/data/<Path to target file>/<filename> /mnt/sd/home/root/tvm 
{% endhighlight %}
            <br>
            <p id="deploy-option2"><b>Option 2: &lt;Application 2&gt;</b></p>
            Run the following command to copy the whole repository to the root filesystem.
            <br><br>
{% highlight shell %}
sudo cp $WORK/ai_sdk_setup/data/<Path to repository>/RZV2L_AiLibrary /mnt/sd/home/root/tvm -r
{% endhighlight %}
          </li>
          <li>Run the following command to sync the data with memory.
            <br>
{% highlight shell %}
sync 
{% endhighlight %}
          </li>
          <li>Run the following command to unmount the partition 2.
            <br>
{% highlight shell %}
sudo umount /mnt/sd
{% endhighlight %}
          </li>
          <li>Eject the microSD card by running the following command and remove the microSD card from Linux PC.<br>
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
      <h4 id="step7-3" class="u_line">3. Boot RZ/V2L EVK</h4>
      This section explains how to boot the RZ/V2L EVK.<br>
      <div class="SelectButton">
        <span class="ButtoneSD">eSD Bootloader</span>
        <span class="ButtoneMMC">eMMC Bootloader</span>
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
      <div class="ContenteMMC contenteMMC-bg">
        <span class="ContenteMMC-title">For eMMC</span>
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
      After the boot up, please go back to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step8">Getting Started Step 8</a> or proceed directly to <a href="#step8">RZ/V2L EVK Getting Started Step 8</a>.
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
        Users are required to read Step 7 of <a href="#step7">RZ/V2L EVK Getting Started</a>.<br>
        <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="#step7" role="button">
          <span class="banner-title">RZ/V2L EVK Getting Started Step 7 </span>
          <span class="banner-line">
          How can I setup microSD card for eSD/eMMC Bootloader?<br>
          How can I deploy applications to the board?<br>
          How can I write eMMC Bootloader to the board?<br>
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
            For <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v5.00pre/R01_object_detection">R01_object_detection</a> application, follow the instruction <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v5.00pre/R01_object_detection#application-run-stage">here</a> to run the application.
            <br>
            If you have successfully run the application, you will see following window on HDMI screen.
            <br><br>
            <img src="img/objectdetection.png" alt="object_detection" width="90%"/>
          </div>
          <br>
        </li>
      </ol>
      <div class="note">
        <span class="note-title">Note</span>
        To shutdown the board safely, please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link appendix.md %}#A3">A3. Shutdown RZ/V2L EVK</a>
      </div>
    </div>
  </div>
</div>
<br><br>

<div class="container">
  <div class="row">
    <div class="col-12">
      <h4 class="u_line">This is the end of RZ/V2L EVK Getting Started.</h4>
      To see what comes next, please refer to the Getting Started Ending.<br>
      <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#ending" role="button">
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
      <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#page-top" role="button">
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
    document.querySelectorAll(".ContenteMMC").forEach(elm => elm.style.display="none");
    document.querySelectorAll(".ButtoneSD").forEach(elm => elm.classList.add("ButtoneSD-Active"));
    document.querySelectorAll(".ButtoneMMC").forEach(elm => elm.classList.remove("ButtoneMMC-Active"));
  } else {
    document.querySelectorAll(".ContenteSD").forEach(elm => elm.style.display="none");
    document.querySelectorAll(".ContenteMMC").forEach(elm => elm.style.display="block");
    document.querySelectorAll(".ButtoneSD").forEach(elm => elm.classList.remove("ButtoneSD-Active"));
    document.querySelectorAll(".ButtoneMMC").forEach(elm => elm.classList.add("ButtoneMMC-Active"));
  }
}
document.querySelectorAll(".SelectButton").forEach(elm => {
  elm.addEventListener("click", ()=>{
    BootType = (BootType === "eSD") ? "eMMC": "eSD";
    // document.cookie = `BootType=${BootType};max-age=86400;path=/`;
    dispBootType();
  });
})
dispBootType();
</script>