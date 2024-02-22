---
layout: default
---
<script type="text/javascript" src="http://code.jquery.com/jquery-3.7.0.min.js"></script>
<script>
  $(function(){
    $("#a3reference").load("{{ site.url }}{{ site.baseurl }}{% link appendix.md %} a3reference");
});
</script>


<div class="container">
    <div class="row">
        <div class="top col-12">
Getting Started Appendix
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
<h5>This page explains the additional information of Getting Started.</h5>

<h3 id="A1">A1. Setup for eMMC Bootloader</h3>
This section explains how to setup the board for eMMC Bootloader.
<br>
<div class="note">
  <span class="note-title">Note</span>
  This step is required only when starting the AI SDK or when using the new version of AI SDK.<br>
  If you have already setup the microSD card and the bootloader written in eMMC on the board, <span class="skip">skip this step</span> and proceed to <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started_internal.md %}#step7-2">the next step (Step7:2. Deploy Application to the Board in Getting Started)</a>.
</div>

Follow the instruction below to setup the board.
<div class="note">
  <span class="note-title">Note</span>
  Explanation in this step is for eMMC Bootloader, which requires Windows PC as serial communication console.<br>
</div>
<ul style="list-style:none;">
  <li>
    <h5 id="A1-1">1. Install Terminal Emulator</h5>
    <div class="note">
      <span class="note-title">Note</span>
      If you have already installed terminal emulator, <span class="skip">skip this step</span> and proceed to <a href="{{ site.url }}{{ site.baseurl }}{% link appendix.md %}#A1-2">next procedure</a>.
    </div>
    <ol>
      <li>
        Install following software <b>on Windows PC</b> to be used as serial communication console.
        <ul>
          <li>
            Terminal emulator
            <ul>
              <li>
                Operating Environment: Tera Term
              </li>
            </ul>
          </li>
        </ul>
      </li>
    </ol>
    <br>
  </li>
  <li>
    <h5 id="A1-2">2. Install the serial port driver</h5>
    <div class="note">
      <span class="note-title">Note</span>
      If you have already installed the serial port driver, <span class="skip">skip this step</span> and proceed to <a href="{{ site.url }}{{ site.baseurl }}{% link appendix.md %}#A1-3">next procedure</a>.
    </div>
    The serial communication between Windows PC and RZ/V2L EVK requires following driver.<br>
    <a href="https://ftdichip.com/drivers/vcp-drivers/">https://ftdichip.com/drivers/vcp-drivers/</a>
    <br><br>
    <ol>
      <li>
        Download the software "Virtual COM port (VCP) driver" from the windows version "setup executable" on the download page and extract it.
      </li><br>
      <li>
        Run the <code>*.exe</code> file extracted to install the serial port driver.
      </li><br>
    </ol>
    <br>
  </li>
  <li>
    <h5 id="A1-3">3. Write bootloaders to eMMC on the board</h5>
    <ol>
      <li>Copy following files in <code>${WORK}/board_setup/eMMC/bootloader</code> to your Windows PC.
        <ul>
          <li><code>Flash_Writer_SCIF_RZV2L_SMARC<br clas="br-sp">_PMIC_DDR4_2GB_1PCS.mot</code></li>
          <li><code>bl2_bp-smarc-rzv2l_pmic.srec</code></li>
          <li><code>fip-smarc-rzv2l_pmic.srec</code></li>
        </ul>
      </li><br>
      <li>Connect Windows PC and Board via Serial to MicroUSB Cable.
      </li><br>
      <li>Change SW1 and SW11 setting (see the figure below).
        <br><br>
        <img class="procedure"  src="img/board_bootloader.png" alt="board" width="90%" />
      </li><br>
      <li>Connect the power cable to CN6 on the Board.
      </li><br>
      <li> Press and hold the power button (SW9) for 1 second to turn on the power.
      </li><br>
      <li>On Windows PC, open the terminal emulator.
        Here, we use Tera Term as an example.
      </li><br>
      <li>Select "File" > "New Connection" and select "Serial" port as shown below.
        <br><br>
        <img class="procedure"  src="img/new_connection.png" alt="board" width="90%"/>
      </li><br>
      <li>Open the configuration window from the "Setup">"Terminal" and change the setting as follows.
        <br><br>
        <table>
          <tr>
            <th>Item</th>
            <th>Value</th>
          </tr>
          <tr>
            <td>New-line</td>
            <td>Receive: Auto</td>
          </tr>
          <tr>
            <td></td>
            <td>Transmit: CR</td>
          </tr>
        </table>
      </li><br>
      <li>Open the configuration window from the "Setup">"Serial port" and change the setting as follows.
        <br><br>
        <table>
          <tr>
            <th>Item</th>
            <th>Value</th>
          </tr>
          <tr>
            <td>Baud rate</td>
            <td>115200</td>
          </tr>
          <tr>
            <td>Data</td>
            <td>8bit</td>
          </tr>
          <tr>
            <td>Parity</td>
            <td>none</td>
          </tr>
          <tr>
            <td>Stop</td>
            <td>1bit</td>
          </tr>
          <tr>
            <td>Flow control</td>
            <td>none</td>
          </tr>
          <tr>
            <td>Transmit delay</td>
            <td>0msec/char</td>
          </tr>
        </table>
      </li><br>
      <li>Press the reset button (SW10) and following message will be displayed on the terminal.
{% highlight console %}
  SCIF Download mode
(C) Renesas Electronics Corp.
-- Load Program to System RAM ---------------
please send !
{% endhighlight %}
      </li><br>
      <li>
        Open "File" > "Send file..." and send the Flash Writer file (<code>*.mot</code>) as a text.<br>
        If following message is displayed, the file transfer suceeded.
{% highlight console %}
Flash writer for RZ/V2 Series Vx.xx xxx.xx,20xx
Product Code : RZ/V2L
>
{% endhighlight %}
      </li><br>
      <li>Enter "<code>XLS2</code>" on the terminal to get following messages.
{% highlight console %}
> XLS2
===== Qspi writing of RZ/G2 Board Command =============
Load Program to Spiflash
Writes to any of SPI address.
Micron : MT25QU512
Program Top Address & Qspi Save Address
===== Please Input Program Top Address ============
  Please Input : H'
{% endhighlight %}
      </li><br>
      <li>Enter "<code>11E00</code>". The log continues.
{% highlight console %}
  Please Input : H'11E00
===== Please Input Qspi Save Address ===
  Please Input : H'
{% endhighlight %}
      </li><br>
      <li>Enter "<code>00000</code>". The log continues.
{% highlight console %}
  Please Input : H'00000
Work RAM(H'50000000-H'53FFFFFF) Clear....
please send ! ('.' & CR stop load)
{% endhighlight %}
      </li><br>
      <li>After the "please send!" message, open "File" > "Send file..." and <b>send the <code>bl2_bp-smarc-rzv2l_pmic.srec</code> file</b> as a text from the terminal software.
      </li><br>
      <li>In case a message to prompt to clear data like below, please enter "<code>y</code>".
{% highlight console %}
SPI Data Clear(H'FF) Check : H'00000000-0000FFFF,Clear OK?(y/n)
{% endhighlight %}
      </li><br>
      <li>Following log will be displayed.
{% highlight console %}
SAVE SPI-FLASH.......
======= Qspi Save Information =================
SpiFlashMemory Stat Address : H'00000000
SpiFlashMemory End Address : H'00009A80
===========================================================
{% endhighlight %}
      </li><br>
      <li>Enter "<code>XLS2</code>" on the terminal to get following messages.
{% highlight console %}
> XLS2
===== Qspi writing of RZ/G2 Board Command =============
Load Program to Spiflash
Writes to any of SPI address.
Micron : MT25QU512
Program Top Address & Qspi Save Address
===== Please Input Program Top Address ============
  Please Input : H'
{% endhighlight %}
      </li><br>
      <li>Enter "<code>00000</code>". The log continues.
{% highlight console %}
  Please Input : H'00000
===== Please Input Qspi Save Address ===
  Please Input : H'
{% endhighlight %}
      </li><br>
      <li>Enter "<code>1D200</code>". The log continues.
{% highlight console %}
  Please Input : H'1D200
Work RAM(H'50000000-H'53FFFFFF) Clear....
please send ! ('.' & CR stop load)
{% endhighlight %}
      </li><br>
      <li>After the "please send!" message, open "File" > "Send file..." and <b>send the <code>fip-smarc-rzv2l_pmic.srec</code> file</b> as a text from the terminal software.
      </li><br>
      <li>In case a message to prompt to clear data like below, please enter "<code>y</code>".
{% highlight console %}
SPI Data Clear(H'FF) Check : H'00000000-0000FFFF,Clear OK?(y/n)
{% endhighlight %}
      </li><br>
      <li>Following log will be displayed.
{% highlight console %}
SAVE SPI-FLASH.......
======= Qspi Save Information =================
SpiFlashMemory Stat Address : H'0001D200
SpiFlashMemory End Address : H'000CC73F
===========================================================
{% endhighlight %}
      </li><br>
      <li>Power-off the board by pressing the power button (SW9) for 2 seconds to change SW11 for booting the board.
      <br>
      </li>
    </ol>
    <br><br>
  </li>
  <li>
    <h5 id="A1-4">4. Setup U-boot setting</h5>
    Follow the procedure below to set the booting configuration of the board.<br><br>
    <div class="container">
      <div class="row">
        <div class="col-12 col-md-6">
          <ol>
            <li>Insert the microSD card to the <b>Board</b>.
              <div class="note">
                <span class="note-title">Note</span>
                Use the microSD card slot <b>CN10</b> as shown in the figure.
              </div>
            </li><br>
            <li>Change SW1 and SW11 setting as shown in the right figure.
            </li><br>
            <li>Connect the <b>Board</b> and <b>Windows PC</b> by the USB Serial to Micro USB cable.
            </li><br>
            <li>Connect the power cable to the <b>Board</b>.
            </li><br>
            <li>Press power button for 1 second to turn on the board.
            </li><br>
            <li>Open the terminal emulator, i.e., Tera Term, and connect with COMS port.
              <div class="note">
                <span class="note-title">Note</span>
                When using Tera Term, change the configuration as explained in <a href="#A1-3">Write bootloaders to eMMC on the board</a>.
              </div>
            </li><br>
            <li>On the terminal emulator, keep pressing ENTER key and on the board, press reset button.
            </li><br>
          </ol>
        </div>
        <div class="col-12 col-md-6">
          <img class="procedure" src="img/uboot-setting.png" alt="boot" width="90%"/>
          <br>
        </div>
      </div>
      <div class="row">
        <div class="col-12">
          <ol start="8">
            <li>U-boot console will be activated.
            </li><br>
            <li>Run the following commands to set the booting configuration.
{% highlight shell %}
env default -a
setenv bootargs 'root=/dev/mmcblk1p2 rootwait'
setenv bootcmd 'mmc dev 1;fatload mmc 1:1 0x48080000 Image-smarc-rzv2l.bin; fatload mmc 1:1 0x48000000 Image-r9a07g054l2-smarc.dtb; booti 0x48080000 - 0x48000000'
saveenv
boot
{% endhighlight %}
            </li><br>
            <li>After the boot-up, the login message will be shown on the console.
{% highlight shell %}
smarc-rzv2l login:
{% endhighlight %}
            </li><br>
            <li>Log-in to the system using the information below.
              <ul>
                <li>user: <code>root</code>
                </li>
                <li>password: none
                </li>
              </ul>
            </li><br>
            <li>Shutdown the board to finish the U-boot setting.
              <details class="boxdetails" open>
                <summary>Shutdown Procedures</summary>
                <quotedoc id="a3reference"></quotedoc>
              </details>
            </li><br>
          </ol>
        </div>
      </div>
    </div>
  </li>
</ul>
<br>
After this procedure, you can copy the AI Application and boot the board.<br>
Refer to the <a href="">Step 7: 2. Deploy Application to the Board in RZ/V2L EVK Getting Started (Link not available)</a>.
<br><br>

<h3 id="A2">A2. Format SD card</h3>
  When writing the necessary files for the board, microSD card needs to have appropriate format.<br>
  Note that you need to run this procedure only once as long as you use the same microSD card.
  <br><br>
  Follow the instruction below to format the microSD card partitions.<br>
  <h5 id="A2prep">Preparation</h5>
  <div class="note">
    <span class="note-title">Click the button</span>
    This section contains both eSD and eMMC Bootloader explanation.<br>
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
  <h5 id="A2-1">Check the SD card connection</h5>
  <ol>
    <li>Before inserting the microSD card to your Linux PC, open the terinal on Linux PC and run the following command to check the devices without microSD card.
{% highlight shell %}
lsblk
{% endhighlight %}
  Following is the example output.
{% highlight shell %}
NAME MAJ:MIN RM SIZE RO TYPE MOUNTPOINT
sda 8:0 0 30.9G 0 disk
├─sda1 8:1 0 512M 0 part /boot/efi
├─sda2 8:2 0 1K 0 part
└─sda5 8:5 0 30.3G 0 part /
sr0 11:0 1 1024M 0 rom
{% endhighlight %}
    </li><br>
    <li>Insert the microSD card to your Linux PC and run the following command again.
{% highlight shell %}
lsblk
{% endhighlight %}
    </li><br>
    <li>Check the output and confirm the name appeared.<br>
      This would be your microSD card device name.<br>
      <ul>
        <li>Following is the example output.
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
        </li>
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
    <li>Run the following command to check the automatically mounted microSD card partitions.
{% highlight shell %}
df
{% endhighlight %}
    </li><br>
    <li>Check the output and find the mount point, which is "<code>/media/user/A8D3-393D</code>" in the following example.
{% highlight shell %}
Filesystem 1K-blocks Used Available Use% Mounted on
udev 745652 0 745652 0% /dev
:
snip
:
/dev/sdb1 511720 4904 506816 1% /media/user/A8D3-393B
{% endhighlight %}
    </li><br>
    <li>Unmount the automatically mounted partitions.
{% highlight shell %}
sudo umount /media/user/A8D3-393B
{% endhighlight %}
      <ul><li>
        If there are more than one partitions on microSD card, unmount all partitions.
      </li></ul>
    </li>
  </ol>
  <br>
  <h5 id="A2-2">Create SD card partition</h5>
  <ol>
    <li>
      Run <code>fdisk</code> command as shown below to change the partition table according to the following table.
      <br>
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
        <div class="note">
          <span class="note-title">Note</span>
          <i><b>"Type of Filesystem"</b></i> of <i><b>"Primary #1 Linux kernel and Device tree"</b></i> Contents is <b><i>Ext4</i></b>.<br>
        </div>
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
        <div class="note">
          <span class="note-title">Note</span>
          <i><b>"Type of Filesystem"</b></i> of <i><b>"Primary #1 Linux kernel and Device tree"</b></i> Contents is <b><i>FAT32</i></b>.<br>
        </div>
      </div>
      <br>
{% highlight shell %}
sudo fdisk /dev/sdb
{% endhighlight %}
      <div class="warning">
            <span class="warning-title">Warning</span>
          Use device name. Do NOT use partition name such as <code>/dev/sdb1</code>.
      </div>
      <ul>
        <li>Following log will be shown.
{% highlight shell %}
Welcome to fdisk (util-linux 2.34).
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.

Command (m for help):
{% endhighlight %}
        </li><br>
        <li>Type "<code>o</code>" to console. The log continues.
{% highlight shell %}
Created a new DOS disklabel with disk identifier 0x6b6aac6e.

Command (m for help):
{% endhighlight %}
        </li><br>
        <li>Type "<code>n</code>" to console. The log continues.
{% highlight shell %}
Partition type
p primary (0 primary, 0 extended, 4 free)
e extended (container for logical partitions)
Select (default p):
{% endhighlight %}
        </li><br>
        <li>Type "<code>p</code>" to console. The log continues.
{% highlight shell %}
Partition number (1-4, default 1):
{% endhighlight %}
        </li><br>
        <li>Press ENTER key. The log continues.
{% highlight shell %}
First sector (2048-62333951, default 2048):
{% endhighlight %}
        </li><br>
        <li>Press ENTER key. The log continues.
{% highlight shell %}
Last sector, +/-sectors or +/-size{K,M,G,T,P} (2048-62333951,
default 62333951):
{% endhighlight %}
        </li><br>
        <li>Type "<code>+500M</code>" to console. The log continues.
{% highlight shell %}
Created a new partition 1 of type 'Linux' and of size 500 MiB.
Partition #1 contains a vfat signature.

Do you want to remove the signature? [Y]es/[N]o:
{% endhighlight %}
        </li><br>
        <li>Type "<code>Y</code>" to console. The log continues.
{% highlight shell %}
The signature will be removed by a write command.

Command (m for help):
{% endhighlight %}
        </li><br>
        <li>Type "<code>n</code>" to console. The log continues.
{% highlight shell %}
Partition type
p primary (1 primary, 0 extended, 3 free)
e extended (container for logical partitions)
Select (default p):
{% endhighlight %}
        </li><br>
        <li>Type "<code>p</code>" to console. The log continues.
{% highlight shell %}
Partition number (2-4, default 2):
{% endhighlight %}
        </li><br>
        <li>Press ENTER key. The log continues.
{% highlight shell %}
First sector (1026048-62333951, default 1026048):
{% endhighlight %}
        </li><br>
        <li>Press ENTER key. The log continues.
{% highlight shell %}
Last sector, +/-sectors or +/-size{K,M,G,T,P} (1026048-62333951,
default 62333951):
{% endhighlight %}
        </li><br>
        <li>Press ENTER key. The log continues.
{% highlight shell %}
Created a new partition 2 of type 'Linux' and of size 29.2 GiB.

Command (m for help):
{% endhighlight %}
        </li><br>
        <li>Type "<code>p</code>" to console. The log continues.
{% highlight shell %}
Disk /dev/sdb: 29.74 GiB, 31914983424 bytes, 62333952 sectors
Disk model: Transcend
Units: sectors of 1 \* 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes  
 Disklabel type: dos
Disk identifier: 0x6b6aac6e

Device Boot Start End Sectors Size Id Type
/dev/sdb1 2048 1026047 1024000 500M 83 Linux
/dev/sdb2 1026048 62333951 61307904 29.2G 83 Linux

Filesystem/RAID signature on partition 1 will be wiped.

Command (m for help):
{% endhighlight %}
        </li>
      <div class="ContenteMMC contenteMMC-bg">
        <span class="ContenteMMC-title">For eMMC</span>
        Additionally, run the following procedures to set the partition as FAT32.
        <ul>
          <li>Type "<code>t</code>" to console. The log continues.
{% highlight shell %}
Partition number (1,2, default 2):
{% endhighlight %}
          </li><br>
          <li>Type "<code>1</code>" to console. The log continues.
{% highlight shell %}
Hex code (type L to list all codes):
{% endhighlight %}
          </li><br>
          <li>Type "<code>b</code>" to console. The log continues.
{% highlight shell %}
Changed type of partition 'Linux' to 'W95 FAT32'.

Command (m for help):
{% endhighlight %}
          </li>
        </ul>
      </div>
      <br>
      <li>Type "<code>w</code>" to console. The <code>fdisk</code> interface will end.
{% highlight shell %}
The partition table has been altered.
Syncing disks.
{% endhighlight %}
      </li>
    </ul>
  </li><br>
  <li>Check the partition table with the command below.
{% highlight shell %}
partprobe
sudo fdisk -l /dev/sdb
{% endhighlight %}
    <ul><li>Output would be as follows. Note that there are two partitions.
      <div class="ContenteSD contenteSD-bg">
        <span class="ContenteSD-title">For eSD</span>
{% highlight shell %}
Disk /dev/sdb: 29.74 GiB, 31914983424 bytes, 62333952 sectors
Disk model: Maker name etc.
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x6b6aac6e
Device Boot Start End Sectors Size Id Type
/dev/sdb1 2048 1026047 1024000 500M 83 Linux 
/dev/sdb2 1026048 62333951 61307904 29.2G 83 Linux
{% endhighlight %}    
      </div>
      <div class="ContenteMMC contenteMMC-bg">
        <span class="ContenteMMC-title">For eMMC</span>
{% highlight shell %}
Disk /dev/sdb: 29.74 GiB, 31914983424 bytes, 62333952 sectors
Disk model: Maker name etc.
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x6b6aac6e
Device Boot Start End Sectors Size Id Type
/dev/sdb1 2048 1026047 1024000 500M b W95 FAT32
/dev/sdb2 1026048 62333951 61307904 29.2G 83 Linux
{% endhighlight %}
      </div>
    </li></ul>
  </li><br>
  <li>Run the command below to format and mount the partitions 1.
    <div class="note">
      <span class="note-title">Note</span>
      If the partitions were automatically mounted after the procedure 6 of "Check the SD card connection", please unmount them again.
    </div>
    <div class="ContenteSD contenteSD-bg">
      <span class="ContenteSD-title">For eSD</span>
{% highlight shell %}
sudo mkfs.ext4 -L boot /dev/sdb1
{% endhighlight %}
      <ul><li>Following log will be shown.
{% highlight shell %}
mke2fs 1.45.5 (07-Jan-2020)
Creating filesystem with 128000 4k blocks and 128000 inodes
Filesystem UUID: 0d2b995c-dd96-4ff6-953c-66a4701fa034
Superblock backups stored on blocks:
  32768, 98304
Allocating group tables: done
Writing inode tables: done
Creating journal (4096 blocks): done
Writing superblocks and filesystem accounting information: done
{% endhighlight %}
      </li></ul>
    </div>
    <div class="ContenteMMC contenteMMC-bg">
      <span class="ContenteMMC-title">For eMMC</span>
{% highlight shell %}
sudo mkfs.vfat -v -c -F 32 /dev/sdb1
{% endhighlight %}
      <ul><li>Following log will be shown.
{% highlight shell %}
mkfs.fat 4.1 (2017-01-24)
/dev/sdb1 has 64 heads and 32 sectors per track,
hidden sectors 0x0800;
logical sector size is 512,
using 0xf8 media descriptor, with 1024000 sectors;
drive number 0x80;
filesystem has 2 32-bit FATs and 8 sectors per cluster.
FAT size is 1000 sectors, and provides 127746 clusters.
There are 32 reserved sectors.
Volume ID is a299e6a6, no volume label.
Searching for bad blocks 16848... 34256... 51152... 68304... 85072... 10209
6... 119376... 136528... 153552... 170576... 187472... 204624... 221648... 238
928... 256208... 273744... 290768... 308048... 325328... 342480... 359504... 3
76656... 393680... 410576... 427216... 444624... 462032... 479184... 495952...
{% endhighlight %}
      </li></ul>
    </div>
  </li><br>
  <li>Run the command below to format and mount the partitions 2.
{% highlight shell %}
sudo mkfs.ext4 -L rootfs /dev/sdb2
{% endhighlight %}
    <ul><li>Following log will be shown.
{% highlight shell %}
mke2fs 1.45.5 (07-Jan-2020)
Creating filesystem with 7663488 4k blocks and 1916928 inodes
Filesystem UUID: 63dddb3f-e268-4554-af51-1c6e1928d76c
Superblock backups stored on blocks:
32768, 98304, 163840, 229376, 294912, 819200, 884736, 1605632, 2654208,
4096000
Allocating group tables: done
Writing inode tables: done
Creating journal (32768 blocks): done
Writing superblocks and filesystem accounting information: done
{% endhighlight %}
    </li></ul>
  </li><br>
  <li>Eject the microSD card and insert it again to remount the partitions.
  </li>
</ol>
<br>
After this procedure, you can write the necessary data for the board into microSD card.<br>
Refer to the <a href="">Write the Linux files to SD card in RZ/V2L EVK Getting Started (Link not available)</a>.<br>

<br><br>

<h3 id="A3">A3. Shutdown RZ/V2L EVK</h3>
To power-off the RZ/V2L EVK, follow the procedures below.
<br><br>
<a3reference>
  <ol>
    <li>Run the <code>shutdown</code> command on board console.
      <br>
{% highlight shell %}
shutdown -h now
{% endhighlight %}
    </li>
    <li>On board console, check that shutdown procedure runs and ends with following log.
      <br>
{% highlight shell %}
[xxxxx.xxxxxx] reboot: Power down
{% endhighlight %}
    </li>
    <li>Press and hold the power button for 2 seconds.
      <br><br>
      <img src="img/board_power.png" alt="board" width="350px" /><br>
    </li>
  </ol>
</a3reference>
<br><br>
<h3 id="A4">A4. Shutdown RZ/V2H EVK</h3>
To power-off the RZ/V2H EVK, follow the procedures below.
<br><br>
<ol>
  <li>Run the <code>shutdown</code> command on board console.
    <br>
{% highlight shell %}
shutdown -h now
{% endhighlight %}
  </li>
  <li>On board console, check that shutdown procedure runs and ends with following log.
    <br>
{% highlight shell %}
[xxxxx.xxxxxx] reboot: Power down
{% endhighlight %}
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
<br><br>

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