---
layout: default
---
<script type="text/javascript" src="http://code.jquery.com/jquery-3.7.0.min.js"></script>
<script>
  $(function(){
    $("#a3reference").load("{{ site.url }}{{ site.baseurl }}{% link ainavi_appendix.md %} a3reference");
});
</script>


<div class="container">
    <div class="row">
        <div class="top col-12">
AI Navigator Quick Start Guide Appendix
        </div>
    </div>
</div>

<h3 id="ainavi_appendix_a">A. AI Navigator Uninstallation</h3>
Follow the steps below to uninstall the plugins, AI Navigator, AI Transfer Learning Tool Plugin, and AI Model Conversion Tool Plugin.<br>
<br>
<ol>
  <li>Launch e<sup>2</sup> studio.</li>
  <li>Click <b>[Help] > [About e<sup>2</sup> studio]</b> and <b>"About e<sup>2</sup> studio"</b> will appear.</li>
  <li>Click <b>[Installation Details]</b>.</li>
  <li>Click the <b>[Installed Software]</b> tab and select <b>"Renesas AI Framework"</b>/<b>"RZ/V AI TLT"</b>/<b>"AI Model Conversion Tool"</b>.
    <div class="note">
    <span class="note-title">Note</span>
    You can select only one plugin at this time. Repeat this procedure for other plugins if you have finished uninstalling one.
    </div>
  </li>
  <li>Click <b>[Uninstall...]</b>.</li>
  <li>Click <b>[Finish]</b> when the uninstallation is complete.</li>
  <li>The "Software Updates" appears prompting you to restart. Click <b>[Restart Now]</b> to restart e<sup>2</sup> studio.</li>
</ol>
<br>
<div class="note">
  <span class="note-title">Note</span>
  The Docker containers and the directory that AI Transfer Learning Tool Plugin and AI Model Conversion Tool Plugin installed remains when uninstalling.<br> 
  If you never use these Docker containers and directories, run the following commands to remove them.<br>
  <br>
  <ul>
    <li><b>For AI Transfer Learning Tool Plugin</b>
{% highlight shell%}
#Delete docker container and image AI Transfer Learning Tool Plugin installed.
docker stop tltdoc
docker rm tltdoc
docker rmi tlt_backend:latest
#Delete the installed AI Transfer Learning Tool Plugin directory as shown below.
#e.g. if e2 studio is installed in ~/.local/share/renesas/e2_studio
sudo rm -rf ~/.local/share/renesas/rzv_ai_tlt
{% endhighlight %}
    </li>
    <li><b>For AI Model Conversion Tool Plugin</b>
{% highlight shell%}
#Delete docker image AI Model Conversion Tool Plugin installed.
docker rmi rzv2l_ai_sdk_image:latest
#Delete the installed RZ/V AI TVM Plugin directory as shown below.
#e.g. if e2 studio is installed in ~/.local/share/renesas/e2_studio
rm -rf ~/.local/share/renesas/v2l/drp-ai_tvm
{% endhighlight %}
    </li>
  </ul>
</div>
<br>

<h3 id="ainavi_appendix_b">B. How to use Bring Your Own Model Project</h3>
Bring Your Own Model (hereafter, BYOM) project is an empty project to develop an AI application with own AI models on e<sup>2</sup> studio.<br>
Please follow the steps if you develop your AI applications with BYOM project.<br>
<div class="note">
  <span class="note-title">Note</span>
  Bring Your Own Model project does not support RZ/V AI TLT.
</div>
<h5 id="appendix_b_1">1. Import an Bring Your Own Model project</h5>
Importing this project is the same as importing other AI application projects. For details, see <a href="ainavi_quick_start_guide.html#ainavi_step3" target="_blank">Step 3: Import an AI Application Project</a> in AI Navigator Quick Start Guide for the details.<br>
In order to import an BYOM project, click <b>[Bring Your Own Model]</b> on the category selection view > <b>[Bring Your Own Model]</b> on the AI application selection view > <b>[Import]</b> on the AI application import view. Be sure to set the directory path of the downloaded and extracted zip file in the Project and AI information view.<br> 
<br>
<h5 id="appendix_b_2">2. Convert AI model</h5>
This method is the same as for other AI applications. See <a href="ainavi_quick_start_guide.html#ainavi_option2" target="_blank">Option2: Convert AI Model</a> in AI Navigator Quick Start Guide for the details.<br>
<br>
<h5 id="appendix_b_3">3. Edit AI application</h5>
To build your AI application source code, you should first import your code into your project as shown below.<br>
<ul style="list-style: none;">
  <li>(1) Open Project Explorer, right-click on <b>"src"</b> directory, and click <b>"Import"</b>.</li>
  <li>(2) Select <b>"File System"</b>.</li>
  <li>(3) Click <b>"Browse"</b> and select the soure directory you want to import.</li>
  <li>(4) Select files you want to import.</li>
  <li>(5) Click <b>[Finish]</b>.</li>
</ul>
Also, change an execution file name to an appropriate one as shown below.<br>
<ul style="list-style: none;">
  <li>(1) Right click on the target project in Project Explorer and open <b>"Properties</b>.</li>
  <li>(2) Click <b> [C/C++ Build] -> [Settings] -> [Build Artifact]</b>.</li>
  <li>(3) Enter a file name in <b>“Artifact name:”</b> and click [Apply].</li>
  <li>(4) Click <b> [C/C++ Build] -> [Settings] -> [Toolchain]</b>.</li>
  <li>(5) Check out the box <b>"Use integrated toolchai nverion"</b> and <b>select the appropriate toolchain version.</b></li>
  <li>(6) Click <b>[Apply and Close]</b>.</li>
</ul>
After that, you can build as in <a href="ainavi_quick_start_guide.html#ainavi_option3">Option3: Edit Application</a> in AI Navigator Quick Start Guide.<br>
<br>
<h5 id="appendix_b_3">4. Run on the board</h5>
Before running on the board, you have to change some configuration to run your AI application.<br>
<ul style="list-style: none;">
  <li>(1) Edit the copy AI model/application script file<br>
  You need to edit debugCopyFiles.sh in (the path of your project)/ai-navi, which is the script for copying your AI models and applications to the target board.<br>
  Open debugCopyFiles.sh and edit the following definition in lines around 50-55 .<br>
    <ul>
      <li><b>TVM_HOME</b>: The path to your application directory.</li>
      <li><b>MODEL_PATH[]</b>: The path to your model directory on e<sup>2</sup> studio.</li>
      <li><b>TARGET_MODEL_PATH</b>: The path to your model directory on the target board. </li>
      <li><b>EXE_FILE</b>: Your application file on the target board.</li>
    </ul>
  </li>
  <br>
  <li>(2) Change debug configurations<br>
  Select <b>[Debug] > [Debug Configurations...] > [Target Communication Framework] > target project</b> and click <b>[Application]</b> tab. Change the file name specified in <b>“Local File Path:”</b> and <b>“Remote File Path:”</b>.</li>
</ul>
After that, you can run as in <a href="ainavi_quick_start_guide.html#ainavi_step4">Step 4: Run on the Board</a> in AI Navigator Quick Start Guide.<br>
<br>

<h3 id="ainavi_appendix_c">C. Settings required when using other IP addresses of target board</h3>
In AI Navigator, the IP addresses of the target board are set to 192.168.1.11 respectively by default.<br>
If you are using other IP address, you will need to reconfigure some settings as shown below.<br>
<ul style="list-style: none;">
  <li>(1) Change the target board IP address setting in the copy process of AI models and AI applications.<br>
  Open <b>/ai-navi/debugCopyFiles.sh</b> in your project directory and set the appropriate target board IP address.<br><br>
{% highlight shell%}
IP_ADDRESS="192.168.1.11"
{% endhighlight %}
  </li>
  <li>(2) Reconfigure the debug setting.<br>
  Connect your Linux host PC and the target board.<br>
  Then, click <b>[Run] > [Debug Configurations...] > [Target Communication Framework] > target project</b> and select the <b>[Target]</b> tab.<br>
  In Available targets, select "TFC Agent" whose Host IP address is the target board, and click [Apply] and [Close].<br>
  At this point, check that the Target ID value includes the IP addresses of the target boards.</li>
</ul>

<h3 id="ainavi_appendix_d">D. How to install customized RZ/V Linux into AI Navigator</h3>
To set up your Linux environment on your target board using AI Navigator, click the <b>Information icon</b> next to the [Download...] button in the Project Information view. The <a href="https://Tool-support.renesas.com/tool-support/Zoo/guides/RZV/RZV_custom_framework_guide.html" target="_blank">implementation guide</a> will be displayed. Follow the steps provided in the guide.<br>

In order to build the Linux (AI SDK) or develop with your custom board or 3rd party board, please refer to the following pages.<br>
<ul>
  <li><a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk.md %}">How to build RZ/V2L AI SDK Source Code</a><br>
  The build step of RZ/V2L AI SDK environment.</li>
  <li><a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}">How to build RZ/V2H AI SDK Source Code</a><br>
  The build step of RZ/V2H AI SDK environment.</li>
  <li><a href="https://jira-gasg.renesas.eu/confluence/display/REN/Renesas+Wiki" target="_blank">RZ/G and RZ/V BSP Porting</a><br>
  The information in order to port RZ/V Linux environment (includes kernel, u-boot, and so on) into your custom board.</li>
</ul>