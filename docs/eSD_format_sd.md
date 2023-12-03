---
layout: version
---
<h3>Format SD card for eSD Boot</h3>
When writing the necessary files for the board, microSD card needs to have appropriate format.
Note that you need to run this procedure only once as long as you use the same microSD card.<br>
Follow the instruction below to format the microSD card partitions.<br>
<br>

<h4 id="eSD_Format_1">1. Check the SD card connection</h4>
<ol>
  <li>Before inserting the microSD card to your Linux PC, open the terinal on Linux PC and run the following command to check the devices without microSD card.<br>
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
  <li>Run the following command to check the automatically mounted microSD card partitions.<br>
{% highlight shell %}
df
{% endhighlight %}
  </li><br>
  <li>Check the output and find the mount point, which is "<code>/media/user/A8D3-393D</code>" in the following example.<br>
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
      If there are more than one partitions on microSD card, unmount all partitions.<br>
    </li></ul>
  </li>
</ol><br>

<h4 id="eSD_Format_2">2. Create SD card partition</h4>
<ol>
  <li>Run <code>fdisk</code> command as shown below to change the partition table according to the following table.<br>
    <div class="ContenteSD contenteSD-bg">
      <table class="gstable">
        <tr>
          <th width="120">Type/Number</th>
          <th>Size</th>
          <th width="120">Filesystem</th>
          <th width="120">Contents</th>
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
          <td>root filesystem</td>
        </tr>
      </table>
      <div class="note">
        <span class="note-title">Note</span>
        <i><b>"File system"</b></i> of <i><b>"Primary #1</b></i> containing <i><b>Linux kernel and Device tree"</b></i> is <b><i>Ext4</i></b>.<br>
      </div>
    </div>
{% highlight shell %}
sudo fdisk /dev/sdb
{% endhighlight %}
    <div class="warning">
      <span class="warning-title">Warning</span>
      Use device name. Do NOT use partition name such as <code>/dev/sdb1</code>.
    </div>
    <ul>
      <li>Following log will be shown.<br>        
{% highlight shell %}
Welcome to fdisk (util-linux 2.34).
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.

Command (m for help):
{% endhighlight %}
      </li>
      <li>Type "<code>o</code>" to console. The log continues.
{% highlight shell %}
Created a new DOS disklabel with disk identifier 0x6b6aac6e.

Command (m for help):
{% endhighlight %}
      </li>
      <li>Type "<code>n</code>" to console. The log continues.
{% highlight shell %}
Partition type
p primary (0 primary, 0 extended, 4 free)
e extended (container for logical partitions)
Select (default p):
{% endhighlight %}
      </li>
      <li>Type "<code>p</code>" to console. The log continues.
{% highlight shell %}
Partition number (1-4, default 1):
{% endhighlight %}
      </li>
      <li>Press ENTER key. The log continues.
{% highlight shell %}
First sector (2048-62333951, default 2048):
{% endhighlight %}
      </li>
      <li>Press ENTER key. The log continues.
{% highlight shell %}
Last sector, +/-sectors or +/-size{K,M,G,T,P} (2048-62333951,
default 62333951):
{% endhighlight %}
      </li>
      <li>Type "<code>+500M</code>" to console. The log continues.
{% highlight shell %}
Created a new partition 1 of type 'Linux' and of size 500 MiB.
Partition #1 contains a vfat signature.

Do you want to remove the signature? [Y]es/[N]o:
{% endhighlight %}
      </li>
      <li>Type "<code>Y</code>" to console. The log continues.
{% highlight shell %}
The signature will be removed by a write command.

Command (m for help):
{% endhighlight %}
      </li>
      <li>Type "<code>n</code>" to console. The log continues.
{% highlight shell %}
Partition type
p primary (1 primary, 0 extended, 3 free)
e extended (container for logical partitions)
Select (default p):
{% endhighlight %}
      </li>
      <li>Type "<code>p</code>" to console. The log continues.
{% highlight shell %}
Partition number (2-4, default 2):
{% endhighlight %}
      </li>
      <li>Press ENTER key. The log continues.
{% highlight shell %}
First sector (1026048-62333951, default 1026048):
{% endhighlight %}
      </li>
      <li>Press ENTER key. The log continues.
{% highlight shell %}
Last sector, +/-sectors or +/-size{K,M,G,T,P} (1026048-62333951,
default 62333951):
{% endhighlight %}
      </li>
      <li>Press ENTER key. The log continues.
{% highlight shell %}
Created a new partition 2 of type 'Linux' and of size 29.2 GiB.

Command (m for help):
{% endhighlight %}
      </li>
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
      </li><br>
      <li>Type "<code>w</code>" to console. The <code>fdisk</code> interface will end.
{% highlight shell %}
The partition table has been altered.
Syncing disks.
{% endhighlight %}
      </li>
    </ul>
  </li><br>
  <li>Check the partition table with the command below.
  <br>
{% highlight shell %}
partprobe
sudo fdisk -l /dev/sdb
{% endhighlight %}
    Output would be as follows. Note that there are two partitions.
<br>
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
  </li><br>
  <li>Run the command below to format and mount the partitions 1.
    <div class="note">
      <span class="note-title">Note</span>
      If the partitions were automatically mounted after the procedure 6 of "Check the SD card connection", please unmount them again.
    </div>
{% highlight shell %}
sudo mkfs.ext4 -L boot /dev/sdb1
{% endhighlight %}
      Following log will be shown.
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
  </li><br>
  <li>Run the command below to format and mount the partitions 2.
{% highlight shell %}
sudo mkfs.ext4 -L rootfs /dev/sdb2
{% endhighlight %}
    Following log will be shown.
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
  </li><br>
  <li>Eject the microSD card and insert it again to remount the partitions.
  </li>
</ol><br>
After this procedure, you can write the necessary data for the board into microSD card.<br>
Go to  "<a href="{{ site.url }}{{ site.baseurl }}{% link RZV2L_board_setup_e2studio.md%}">Set up RZ/V2L Evaluation Board Kit</a>" to prepare a micro SD card for booting.