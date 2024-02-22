---
layout: default
---
<script type="text/javascript" src="http://code.jquery.com/jquery-3.7.0.min.js"></script>
<script>
  $(function(){
    $("#reference_terminology").load("{{ site.url }}{{ site.baseurl }}{% link getting_started_internal.md %} reference_terminology");
  });
</script>
<div class="container">
    <div class="row">
        <div class="top col-12">
RZ/V2H EVK Getting Started
        </div>
    </div>
</div>
<div class="warning">
  <span class="warning-title">WARNING</span>
  <span style="color:red;">
  <b>
  This page is published for Renesas internal purpose only.<br>
  Do NOT distribute/share this page to external parties.<br>
  Since this page is still under the review process, the content may change in the official release.<br>
    <br>
  Due to the necessary software unavailability (i.e., DRP-AI TVM, AI Applications), <br>
  you can only run following steps with this internal release. 
  <ul>
    <li>
      Step 2: Obtain necessary environment
    </li>
    <li>
      Step 4: Extract RZ/V AI SDK package
    </li>
    <li>
      Step 7: Deploy AI Application.
        <ul>
          <li>
            1. Setup RZ/V2H EVK
          </li>
          <li>
            3. Boot RZ/V2H EVK
          </li>
        </ul>
    </li>
    <li>
      A4. Shutdown RZ/V2H EVK
    </li>
  </ul>
  </b>
  </span>
</div>
<br>
<br>

<h5>This page explains how to start-up the AI SDK on the <b>RZ/V2H Evaluation Board Kit</b>.</h5>

<h5>Supported version: <b>RZ/V2H AI SDK v3.00</b></h5>

<details class="boxdetails" open>
  <summary>Terminology</summary>
  <quotedoc id="reference_terminology"></quotedoc>
</details>
<br>

<h3>Getting Started Flow</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      This page explains RZ/V2H EVK dependent instructions.<br>
      Common instructions are explained in <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started_internal.md %}"> Getting Started</a> page.<br>
      <img src="img/getting_started_flow_v2h.svg" alt="flow" height="400px"/>
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
            Before reading this document, users are required to read <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started_internal.md %}">Getting Started</a>.<br>
            <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link getting_started_internal.md %}" role="button">
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
            To use MIPI camera, please refer to e-CAM22_CURZH camera provided by <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp">e-con Systems</a>. 
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
  </div>
</div>
<br>
<br>

<div class="container">
  <div class="row">
    <div class="col-12">
      <h3 id="step7" >Step 7: Deploy AI Application</h3>
      This section explains how to deploy the AI Application to the RZ/V2H EVK.
      <br>
      <br>
      <div class="note">
        <span class="note-title">Before reading this step</span>
        Users are required to read Step 1~6 of <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started_internal.md %}">Getting Started</a>.<br>
        <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link getting_started_internal.md %}" role="button">
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
      Following bootloader is available on RZ/V2H AI SDK.<br>
      <ul>
        <li>
          <b>eSD Bootloader</b>: The board boots up using the bootloader written on microSD card.
        </li>
      </ul>
      Other necessary files, i.e. Linux kernel and root filesystem, are stored on microSD card.<br>
      You can use Linux PC to format the microSD card and expand the kernel and the root filesystem using SD card reader.<br>
      <img class="procedure2" src="img/esd.svg" alt="docker" style="max-height: 200px" />
      <br>
      <br>
      <h4 id="step7-1" class="u_line">1. Setup RZ/V2H EVK </h4>
      microSD card needs to contain bootloaders, the Linux kernel and root filesystem to boot-up the board.<br>
      RZ/V2H AI SDK supports the WIC format for SD card image.<br>
      You can use Linux PC to write the SD card image into microSD card with SD card reader.<br>
      <div class="note">
        <span class="note-title">Note</span>
        This step is required only when starting the AI SDK or when using the new version of AI SDK.<br>
        If you have already setup the microSD card with the latest bootloader, Linux kernel, Linux device tree file and root filesystem, <span class="skip">skip this step</span> and proceed to <a href="#step7-2">the next procedure (2. Deploy Application to the Board)</a>.
      </div>
      <div class="note">
        <span class="note-title">Note</span>
        The size of WIC format SD card image is 4GB.<br>
        If you would like to expand the SD card image size, please build the RZ/V2H AI SDK Source Code according to <a href="">Appendix 2 in How to Build RZ/V2H AI SDK (Link not available)</a>.
      </div>
      <ol>
        <h5 id="step7-1a">
          <li type="A">Install Necessary Software<br></li>
        </h5>
        As explained in <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started_internal.md %}#step2">Necessary Software of Getting Started Step 2</a>, make sure that <code>bmap-tools</code> is installed on Linux PC.<br>
        If you have not installed the <code>bmap-tools</code>, install it using following command on Host PC (Not in the docker container).<br>
{% highlight shell %}
sudo apt install bmap-tools
{% endhighlight %}
        <br>
        <h5 id="step7-1b">
          <li type="A">Write the Linux files to SD card</li>
        </h5>
        Run the below command to decompress <code>${WORK}/board_setup/eSD.zip</code>.<br>
{% highlight shell %}
cd ${WORK}/board_setup
unzip eSD.zip
{% endhighlight %}
        Following files are necessary.<br>
        They are in the <code>${WORK}/board_setup/eSD</code> directory.
        <br><br>
        <table class="gstable">
          <tr>
            <th>File</th>
            <th>Description</th>
          </tr>
          <tr>
            <td>core-image-weston-rzv2h-evk-ver1.wic.bmap</td>
            <td rowspan="2">SD card image</td>
          </tr>
          <tr>
            <td>core-image-weston-rzv2h-evk-ver1.wic.gz</td>
          </tr>
        </table>
        Follow the instruction below to prepare the microSD card.<br>
        <div class="warning">
          <span class="warning-title">Warning</span>
            Here, we use "<b><code>/dev/sdb</code></b>" as microSD card device name.
        </div>
        <ol>
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
{% highlight shell %}
cd ${WORK}/board_setup/eSD
sudo bmaptool copy --bmap core-image-weston-rzv2h-evk-ver1.wic.bmap core-image-weston-rzv2h-evk-ver1.wic.gz /dev/sdb
{% endhighlight %}
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
/dev/sdb1        17M  3.0M   14M  18% /media/user/bootloaderf
/dev/sdb2       3.8G  1.6G  2.0G  45% /media/user/root
{% endhighlight %}
                <div class="warning">
                  <span class="warning-title">Warning</span>
                  Here, we use "<b><code>/dev/sdb</code></b>" as microSD card device name.
                </div>
              </li>
            </ul>
          </li>
          <li>Run the following commands to setup the partition 2, which is the root filesystem of the board.<br>
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
          </li>
        </ol>
      </ol>
      <br>
      <h4 id="step7-2" class="u_line">2. Deploy Application to the Board</h4>
      This section explains how to copy the <a href="#step6">application binary created in Step 6</a> to the board.<br>
      Users are expected to have finished the instructions in <a href="#step7"> Setup RZ/V2H EVK in Step 7-1</a>.
      <br>
      <br>
      <ol>
        <li>
          Insert the microSD card to Linux PC.
        </li><br>
        <li>
          Run the following command to mount the partition 2, which contains the root filesystem.<br>
{% highlight shell %}
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
sudo mkdir /mnt/sd/home/root/tvm
{% endhighlight %}
          <div class="note">
            <span class="note-title">Note</span>
            Directory name <code>tvm</code> can be determined by user.<br>
          </div>
        </li>
        <li>
          Copy the necessary files in execution environment.<br>
          Check the <code>README.md</code> document provided in application directory and follow the instruction in the chapter called <b>"Application: Deploy Stage"</b> (or similar) to deploy the application.
          <br><br>
          <div class="box1">
            <u><b>Example:</b></u><br>
            In <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v{{ site.version }}/R01_object_detection">R01_object_detection</a> application, follow the instruction in <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v{{ site.version }}/R01_object_detection#application-deploy-stage">here</a> to find files to be copied.
          </div>
          <br>
          Use the following command to copy the files to root filesystem.
          <br><br>
{% highlight shell %}
sudo cp $WORK/ai_sdk_setup/data/<Path to target file>/<filename> /mnt/sd/home/root/tvm 
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
      <h4 id="step7-3" class="u_line">3. Boot RZ/V2H EVK</h4>
      This section explains how to boot the RZ/V2H EVK.<br>
      <br>
      Follow the instruction below to boot the board.
      <br>
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
        <br>
        After the boot up, please go back to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started_internal.md %}#step8">Getting Started Step 8</a> or proceed directly to <a href="#step8">RZ/V2H EVK Getting Started Step 8</a>.
        <br><br>
      </div>
    </div>
  </div>
</div>

<div class="container">
  <div class="row">
    <div class="col-12">
      <h3 id="step8" >Step 8: Run AI Application</h3>
      <div class="note">
        <span class="note-title">Before reading this step</span>
        Users are required to read Step 7 of <a href="#step7">RZ/V2H EVK Getting Started</a>.<br>
        <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="#step7" role="button">
          <span class="banner-title">RZ/V2H EVK Getting Started Step 7 </span>
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
            For <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v{{ site.version }}/R01_object_detection">R01_object_detection</a> application, follow the instruction <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v{{ site.version }}/R01_object_detection#application-run-stage">here</a> to run the application.
            <br>
            If you have successfully run the application, you will see following window on HDMI screen.
            <br><br>
            <img src="img/objectdetection_v2h.png" alt="object_detection" width="90%"/>
          </div>
          <br>
        </li>
      </ol>
      <div class="note">
        <span class="note-title">Note</span>
        To shutdown the board safely, please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link appendix_internal.md %}#A4">A4. Shutdown RZ/V2H EVK</a>
      </div>
    </div>
  </div>
</div>
<br><br>

<div class="container">
  <div class="row">
    <div class="col-12">
      <h4 class="u_line">This is the end of RZ/V2H EVK Getting Started.</h4>
      To see what comes next, please refer to the Getting Started Ending.<br>
      <a class="btn btn-secondary square-button ms-3 mt-1" style="text-align:left;" href="{{ site.url }}{{ site.baseurl }}{% link getting_started_internal.md %}#ending" role="button">
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