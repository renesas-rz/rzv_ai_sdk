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
<br>
<br>
<h5>This page explains the additional information of Getting Started.</h5>

<h3 id="A2">A1. Format SD card</h3>
  When writing the necessary files for the board, microSD card needs to have appropriate format.<br>
  Note that you need to run this procedure only once as long as you use the same microSD card.
  <br><br>
  Follow the instruction below to format the microSD card partitions.<br>
  <h5 id="A2prep">Preparation</h5>
  <div class="note">
    <span class="note-title">Click the button</span>
    This section contains both eSD and QSPI Bootloader explanation.<br>
    Please click the button below to update the explanation according to your bootloader interface.<br>
    <div class="SelectButton">
      <span class="ButtoneSD">eSD Bootloader</span>
      <span class="ButtoneMMC">QSPI Bootloader</span>
    </div>
    <div class="ContenteSD contenteSD-bg">
      <span class="ContenteSD-title">For eSD</span>
      eSD explanation will be shown in this style if you click "eSD Bootloader" button above.
    </div>
    <div class="ContenteMMC contenteMMC-bg">
      <span class="ContenteMMC-title">For QSPI</span>
      QSPI explanation will be shown in this style if you click "QSPI Bootloader" button above.
    </div>
  </div>
  <br>
  <h5 id="A2-1">Check the SD card connection</h5>
  <ol>
    <li>Before inserting the microSD card to your Linux PC, open the terminal on Linux PC and run the following command to check the devices without microSD card.
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
        <span class="ContenteMMC-title">For QSPI</span>
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
        <span class="ContenteMMC-title">For QSPI</span>
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
        <span class="ContenteMMC-title">For QSPI</span>
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
      <span class="ContenteMMC-title">For QSPI</span>
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
Refer to the <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started_v2l.md %}#step7-1b">Write the Linux files to SD card in RZ/V2L EVK Getting Started</a>.<br>

<br><br>

<h3 id="A3">A2. Shutdown RZ/V2L EVK</h3>
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
<h3 id="A4">A3. Shutdown RZ/V2H EVK</h3>
To power-off the RZ/V2H EVK, follow the procedures below.
<br><br>
<a4reference>
<ol>
  <li>Run the <code>shutdown</code> command on board console.
    <br>
{% highlight shell %}
shutdown -h now
{% endhighlight %}
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
<br><br>
<h3 id="A5">A4. Shutdown RZ/V2N EVK</h3>
To power-off the RZ/V2N EVK, follow the procedures below.
<br><br>
<a5reference>
<ol>
  <li>Run the <code>shutdown</code> command on board console.
    <br>
{% highlight shell %}
sudo -i shutdown -h now
{% endhighlight %}
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
    <img src="img/v2n_evk_shutdown.png" alt="board" width="350px" /><br>
  </li>
</ol>
</a5reference>
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
