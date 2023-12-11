---
layout: version
---
<script type="text/javascript" src="http://code.jquery.com/jquery-3.7.0.min.js"></script>
<script>
  $(function(){
    $("#reference3").load("{{ site.url }}{{ site.baseurl }}{% link getting_started.md %} reference3");
  });
</script>

<h3>Set up RZ/V2L Evaluation Board Kit</h3>
To boot the RZ/V2L Evaluation Board, follow the two steps below.<br>
<div class="note">
  <span class="note-title">Note</span>
  This guide uses the following environment:
  <ul>
      <li><b>Target board</b>: <br>RZ/V2L Evaluation Board Kit</li>
      <li><b>Boot loader</b>: <br>eSD Boot loader, the board boots up using the bootloader written on microSD card.</li>
      <li><b>Working directory(${WORK})</b>: <br>The directory where the downloaded RZ/V2L AI SDK zip file is expanded. Assume that you have already unzipped to /home/{user}/ai_sdk_work and that you have run "$export WORK=/home/{user}/ai_sdk_work".</li>
  </ul>
</div>
<br>

<h4 id="step1_setup_V2Lboard" >Step 1: Setup RZ/V2L Evaluation Board Kit</h4>
You need to prepare a microSD card containing the boot loaders, the Linux kernel, and the root filesystem to boot the board.<br>
You can use a Linux PC to format the microSD card and expand the kernel and the root filesystem using an SD card reader.<br>
<div class="note">
  <span class="note-title">Note</span>
  This step is required only when starting the AI SDK or when using the new version of AI SDK.<br>
  If you have already setup the microSD card with the latest boot loader, Linux kernel, Linux device tree file and root filesystem, <span class="skip">skip this step</span> and proceed to <a href="#step2_boot_V2Lboard">the next procedure (2. Boot RZ/V2L Evaluation Board Kit)</a>.
</div>
<ol>
  <h5 id="stepa">
    <li type="A">Format SD card<br></li>
  </h5>
  Create the following partitions on microSD card according to "<a href="{{ site.url }}{{ site.baseurl }}{% link eSD_format_sd.md %}">Format SD card for eSD Boot</a>".<br>
  <br>
  <table class="gstable">
    <tr>
      <th width=120>Type/Number</th>
      <th>Size</th>
      <th width=120>Filesystem</th>
      <th width=120>Contents</th>
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

  <h5 id="stepb">
    <li type="A">Write the Linux files to SD card</li>
  </h5>
  At first, run the below command to decompress <code>${WORK}/board_setup/eSD.zip</code>.<br>
{% highlight shell %}
cd ${WORK}/board_setup
unzip eSD.zip
{% endhighlight %}
  Following three files are necessary, which must be placed on each partitions on microSD card.<br>
  They are in the <code>${WORK}/board_setup/eSD</code> directory.<br>
  <br>
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
...		…		…	…	…	…
/dev/sdb1		…		…	…	…	…	
/dev/sdb2		…		…	…	…	…	
{% endhighlight %}
      <div class="warning">
          <span class="warning-title">Warning</span>
          Device name of microSD card, <code>/dev/sdb</code> may differ depending on your environment.<br>
      </div>
    </li>
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
sync
sudo umount /mnt/sd
{% endhighlight %}
      <div class="warning">
        <span class="warning-title">Warning</span>
        Change <code>/dev/sdb</code> to your microSD card device name.<br>
      </div>
    </li>
  </ol>
  
  <h5 id="stepc">
    <li type="A">Write the bootloaders to SD card
    </li>
  </h5>
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
<br>
<h4 id="step2_boot_V2Lboard" >Step 2: Boot RZ/V2L Evaluation Board Kit</h4>
Once the <a href="#step1_setup_V2Lboard"><b>Setup RZ/V2L Evaluation Board Kit</b></a> chapter has been completed, you can boot the board in the following way.
<div class="container">
  <div class="row">
    <div class="col-12 col-md-6">
      <ol>
        <li>
          Insert the microSD card to the Board.
          <div class="note">
            <span class="note-title">Note</span>
            Use the microSD card slot <b>CN3</b> as shown in the figure.
          </div>
        </li><br>
        <li>Change SW1 and SW11 setting as shown in the figure.</li><br>
        <li>Connect an Ethernet cable between the board and Linux PC.
          <div class="note">
            <span class="note-title">Note</span>
            Use the Ethernet connector <b>Ethernet 0</b> as shown in the figure.
          </div>
        </li>
        <li>Connect the USB mouse and USB keyboard via USB hub.</li><br>
        <li>Connect the Google Coral camera to the Board.</li><br>
        <li>Connect the HDMI monitor to the Board.</li><br>
        <li>Connect the power cable to the Board.</li><br>
        <li>Press power button for 1 second to turn on the board.</li>
      </ol>
    </div>
    <div class="col-12 col-md-6">
      <img class="procedure"  src="img/aitool_howto_v2l_boot.png" alt="boot" width="90%"/>
    </div>
  </div>  
  <div class="row">
    <div class="col-12 col-md-6">
      <ol>
        <li value = "9">After the boot-up, following screen will be displayed on HDMI monitor.</li>
      </ol>
    </div>
    <div class="col-12 col-md-6">
      <img class="procedure"  src="img/wayland.jpg" alt="wayland" width="90%" />
    </div>
  </div>
  <div class="row">
    <div class=" col-12 col-md-6">
      <ol>
        <li value = "10">Click the icon at the top-left corner to open the terminal.</li>
      </ol>
    </div>
    <div class=" col-12 col-md-6">
      <img class="procedure"  src="img/aitool_wayland_terminal.jpg" alt="wayland" width="90%" />
    </div>
  </div>
  <div class="row">
    <div class=" col-12 col-md-6">
      <ol>
        <li value = "11">To communicate between your Linux PC and the target board via Ethernet, configure their respective IP addresses.<br>
        <ul>
          <li><b>Linux PC</b>:<br>
          This uses the device name of the Ethernet interface "enp2s1" as an example and sets its IP address to <b>192.168.1.10.</b>.<br>
{% highlight shell %}
ifconfig enp2s1 192.168.1.10
{% endhighlight %}
          </li>
          <li><b>Target board</b>:<br>
          Use <b>eth0</b> and set its IP address to <b>192.168.1.11</b>.<br>
{% highlight shell %}
ifconfig eth0 192.168.1.11
{% endhighlight %}
          </li><br>
        </ul>
        </li>
      </ol>
    </div>
    <div class=" col-12 col-md-6">       
    </div>
  </div>
</div>