---
layout: default
---
<script type="text/javascript" src="http://code.jquery.com/jquery-3.7.0.min.js"></script>
<div class="container">
    <div class="row">
        <div class="top col-12">
        AI Navigator Quick Start Guide<br>
        ~ How to develop and run RZ/V AI applications on e2 studio ~
        </div>
    </div>
</div>
<br>
<br>
<h5 id="ainavi_top">This page explains how to develop and run RZ/V AI applications using a GUI environment.<br>
For this GUI environment, Renesas provides <b>AI Navigator</b>, which is a set of plugins for the Renesas IDE e<sup>2</sup> studio and supports your application development.<br>
<br>
Please read the <a href="https://www.renesas.com/us/en/software-tool/e2studio-information-rz-family#documents">AI Navigator Release Note</a> first. This document describes the changes, restrictions, and some notes.<br>
<br>
<table>
  <tr>
    <th>Target version</th>
    <td>AI Navigator V1.1.0</td>
  </tr>
  <tr>
    <th>Supported environment</th>
    <td>Ubuntu 20.04 LTS, Renesas e<sup>2</sup> studio 2024-04 (or later) for Linux</td>
  </tr>
  <tr>
    <th>Supported Devices</th>
    <td>RZ/V2L, RZ/V2H</td>
  </tr>
  <tr>
    <th>Supported Board</th>
    <td>
        (RZ/V2L) RZ/V2L Evaluation Board Kit<br>
        (RZ/V2H) RZ/V2H Evaluation Board Kit
    </td>
  </tr>
  <tr>
    <th>Supported Functions of AI Applications</th>
    <td>
        (RZ/V2L) Q01-Q11 in RZ/V AI SDK V2.10<br>
        (RZ/V2H) Q01, Q08, 01, 02, 07, 11 in RZ/V AI SDK V3.00
    </td>
  </tr>
</table>

<div class="note">
  <span class="note-title">Recommended</span>
  Please also watch <b>"AI Navigator Tutorial"</b> videos. These videos will help you quickly learn how to use AI Navigator.<br>
  (Link)
  <ul>
    <li><a href="https://www.renesas.com/us/en/video/ai-navigator-tutorial-1-run-ai-application">AI Navigator Tutorial #1 (Run AI Application)</a></li>
    <li><a href="https://www.renesas.com/us/en/video/ai-navigator-tutorial-2-customize-ai-model-transfer-learning-tool">AI Navigator Tutorial #2 (Customize AI model by Transfer Learning Tool)</a></li>
  </ul>
</div>

<div class="note">
  <span class="note-title">Note</span>
  For the users who want to use your own customized environment (Linux, target board, and so on), see <a href="ainavi_appendix.html#ainavi_appendix_d">"Build the Linux and Use your Custom PCB Board or 3rd Party Board"</a>.<br>
</div>
</h5>

<h3 id="ainavi_intro">Introduction</h3>
AI Navigator is a set of plugins for e<sup>2</sup> studio that makes it easy to run AI applications on Renesas devices. <br>
By using AI Navigator, you can try out Renesas AI application from importing to running on the board with just a few clicks.<br>
<br>
In addition, AI Navigator includes some plugins for transfer learning tool (RZ/V AI Transfer Learning Tool) and AI model conversion tool (DRP-AI TVM). That's why you can also develop your AI embedded systems with AI Navigator, such as training and converting AI models and building application source codes on e<sup>2</sup> studio.<br>
<br>
The development steps for RZ/V AI applications are shown below. All steps can be controlled by the AI Navigator. <br>
The tools "RZ/V AI Transfer Learning Tool" and "DRP-AI TVM" are called by AI Transfer Learning Tool Plugin and AI Model Conversion Tool Plugin, respectively.<br>
<br>
<a href="img/ainavi/ainavi_usecases.png" data-lightbox="ainavi_usecases"><img src="img/ainavi/ainavi_usecases.png" alt="AI Navi usecase"></a><br>
<br>
Please follow the steps below to start developing your AI applications with AI Navigator. Note that you can skip some steps depending on your use case.<br>

<h3 id="ainavi_preparation">Preparation</h3>
Before you start using the AI Navigator, prepare the necessary equipment and software as described in <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step1">Step 1</a> and <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step2">Step 2</a> in <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}">Getting Started</a>.<br>
<div class="note">
  <span class="note-title">Note</span>
  You must first install Docker before using AI Navigator. <br>
  To install Docker, see "<b>1. Set up Docker's apt repository</b>" and "<b>2. Install the Docker packages</b>" on the following Docker web page.<br>
  <a href="https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository">Install using the apt repository in Docker docs</a><br>
  <br>
  In  addition, some plugins in AI Navigator run Docker as a non-root user.
  See "<b>Manage Docker as a non-root user</b>" in the following Docker web page to run as a non-root user.<br>
  <a href="https://docs.docker.com/engine/install/linux-postinstall/#manage-docker-as-a-non-root-user">Manage Docker as a non-root user in Docker docs</a>
</div>

<h3 id="ainavi_step1" >Step 1: AI Navigator Installation</h3>
<div class="note">
  <span class="note-title">Note</span>
  AI Navigator V1.1.0 works on e<sup>2</sup> studio <b>Linux Host</b> only.<br>
</div>
<div class="note">
  <span class="note-title">Note</span>
  If you want to update AI Navigator from the previous version, you can follow the same procedures below.
</div>
<br>
<ul>
  <li><h5>Non-users of e<sup>2</sup> studio</h5></li>
  Download <b>e<sup>2</sup> studio <u>Linux Host</u></b> from the Renesas website.
  <br><br>
  <a class="btn btn-primary download-button" href="https://www.renesas.com/us/en/software-tool/e2studio-information-rz-family#downloads" role="button">Get e<sup>2</sup> studio</a>
  <br><br>
  <div class="note">
    <span class="note-title">Note</span>
    MyRenesas account is required to download e<sup>2</sup> studio.<br>
  </div>
  After downloading, install e<sup>2</sup> studio. Read the <a href ="https://www.renesas.com/us/en/software-tool/e2studio-information-rz-family#documents">e<sup>2</sup> studio Release Note</a> for the installation.<br>
  Select the following each item when installing.<br>
  <ul>
    <li><b>Device Families</b>: Linux on Renesas RZ</li>
    <li><b>Additional Software</b>: Renesas AI Navigator, AI Transfer Learning Tool Plugin, AI Model Conversion Tool Plugin</li>
  </ul>
  <br><br>
  <li><h5>Users of e<sup>2</sup> studio</h5></li>
  Add the necessary plugins by following the steps below.<br>
  <ol>
    <li>Launch e<sup>2</sup> studio.</li>
    <li>Click <b>[Help] > [Install Renesas IDE Features...]</b>.</li>
    <li>Select <b>[Renesas AI Navigator]</b>, <b>[AI Transfer Learning Tool Plugin]</b>, <b>[AI Model Conversion Tool Plugin]</b> and click <b>[Finish]</b>.</li>
    <li>Confirm that these plugins are selected in the "install" dialog box and click <b>[Next]</b>.</li>
    <li>Confirm these plugins are selected as the installation target and click <b>[Next]</b>.</li>
    <li>Read the license agreements and select "I accept the terms of the license agreement" if you agree.
        Then, click <b>[Finish]</b> to start the plugins installation.</li>
    <li>If the dialog of the trust certificate dialog appears during the installation, check the certificate and click <b>[OK]</b>.</li>
    <li>After the installation is finished, e<sup>2</sup> studio will prompt you to restart. Click <b>[Restart Now]</b>.</li>
  </ol>
  <div class="note">
    <span class="note-title">Note</span>
    The device family "Linux on Renesas RZ" must be available on your e<sup>2</sup> studio environment. Otherwise, you may not be able to build your AI application.<br>
  </div>
  <div class="note">
    <span class="note-title">Note</span>
    If you want to uninstall these plugins, see <a href="ainavi_appendix.html#ainavi_appendix_a">"AI Navigator Uninstallation"</a>.<br>
  </div>
  <br>
</ul>

<h3 id="ainavi_step2" >Step 2: Start AI Navigator</h3>
<div class="container">
  <div class="row">
    <div class="col-6">
      Click <b>[Renesas Views] > [Renesas AI] > [AI Navi]</b> and the AI Navigator will launch.  
      <br>
      <div class="note">
        <span class="note-title">Note</span>
        For each view and button in the AI Navigator, see the help page for AI Navigator. You can access it by clicking the <b>[Learn more...]</b> in the start view (on the top page of AI Navigator) or by selecting <b>[Help] > [Help Contents] > [Renesas AI Navigator]</b>.
      </div>
      <div class="note">
        <span class="note-title">Note</span>
        If you want to restart the project, select it from the pull-down menu in the start view and click <b>[Continue]</b> in the start view.
      </div>
    </div>
    <div class="col-6">
      <a href="img/ainavi/ainavi_top_view.png" data-lightbox="ainavi_top"><img src="img/ainavi/ainavi_top_view.png" alt="AI Navigator top" width="90%" /></a>
    </div>
  </div>
</div>
<br>

<h3 id="ainavi_step3">Step 3: Import AI Applications Project</h3>
Import an AI application project from Renesas AI server by the following steps.
<div class="container">
  <div class="row">
    <div class="col-6">
      <p>1. Click <b>[Create New AI]</b> in the start view.</p><br>
    </div>
    <div class="col-6">
      <a href="img/ainavi/ainavi_import_app_1.png" data-lightbox="ainavi_import_app_1"><img src="img/ainavi/ainavi_import_app_1.png" alt="ainavi" width="90%"/></a>
    </div>
  </div>
  <br>
  <div class="row">
    <div class="col-6">
      <p>2. Select a category of AI application based on your case. You can search the proper category if you enter keywords in Filter.</p><br>
      <div class="note">
        <span class="note-title">Note</span>
        "Bring Your Own Model" is an empty project for utilizing your own AI models and applications. To understand its usage, see this importing step, and then see <a href="ainavi_appendix.html#ainavi_appendix_b"> B. How to use Bring Your Own Model Project</a>.
      </div>
    </div>
    <div class="col-6">
      <a href="img/ainavi/ainavi_import_app_2.png" data-lightbox="ainavi_import_app_2"><img src="img/ainavi/ainavi_import_app_2.png" alt="ainavi app importing step2" width="90%" /></a>
    </div>
  </div>
  <br>
  <div class="row">
    <div class="col-6">
      <p>3. Select an AI application.</p><br>
    </div>
    <div class="col-6">
      <a href="img/ainavi/ainavi_import_app_3.png" data-lightbox="ainavi_import_app_3"><img src="img/ainavi/ainavi_import_app_3.png" alt="ainavi app importing step3" width="90%" /></a>
    </div>
  </div>
  <br>
  <div class="row">
    <div class="col-6">
      <p id="ainavi_step1-4">4. Click <b>[Import]</b> and import an AI application.</p><br>
      <div class="note">
        <span class="note-title">Note</span>
        Once you import an AI application, you cannot import an AI application which has the same function (same number like "Qxx") in the same work space.
      </div>
    </div>
    <div class="col-6">
      <a href="img/ainavi/ainavi_import_app_4.png" data-lightbox="ainavi_import_app_4"><img src="img/ainavi/ainavi_import_app_4.png" alt="ainavi app importing step4" width="90%" /></a>
    </div>
  </div>
    <br>
  <div class="row">
    <div class="col-6">
      <p>5. The Project and AI information view will appear if the import is successful.  </p>
      From this view, you should specify the location of the downloaded and extracted RZ/V AI SDK directory.<br>
      <u>If you haven't downloaded the RZ/V AI SDK</u>, which is the environment for the imported AI application, click <b>[Download...]</b> to download and extract it. And then, specify the directory path.<br>
      <u>If you've already downloaded and extracted the RZ/V AI SDK</u>, click <b>[Set the download folder...]</b> and specify the directory.<br>
    </div>
    <div class="col-6">
      <a href="img/ainavi/ainavi_import_app_5.png" data-lightbox="ainavi_import_app_5"><img src="img/ainavi/ainavi_import_app_5.png" alt="ainavi app importing step5" /></a>
    </div>
  </div>
</div>
<br>
<br>
That's it for the steps to import an AI application project.<br>
Please proceed to each step according to your requirements.<br>
<ul>
  <li><b>For the users who just want to run an AI application: go to <u>Step 4: Run on the Board</u></b></li>
  <li><b>For the users who want to customize AI models: go to <u>Option 1: Train AI model -> Option 2: Convert AI model -> Option3: Edit Application -> Step 4: Run on the Board</u></b></li>
  <li><b>For the users who want to use AI models without any changes, but want to edit AI application source code: go to  <u>Option3: Edit Application -> Step 4: Run on the Board</u></b></li>
</ul>
<div class="note">
  <span class="note-title">Click the button</span>
  As you click each button, the guides for that option appear and the color of the button changes to gray. Click them as needed.<br>
  When you click a button again, the option guides close and the button returns to its default color.<br>
  <br>
  <div class="ButtonTLT">Option1: Train AI Model</div>
  <div class="ButtonTVM">Option2: Convert AI Model</div>
  <div class="ButtonAppBuild">Option3: Edit Application</div>
</div>
<div class="ContentsTLT">
  <h3 id="ainavi_option1" >Option1: Train AI Model</h3>
  For RZ/V, you can train any AI models provided in any Renesas AI application using the <b>RZ/V AI Transfer Learning Tool</b> (hereinafter referred to as RZ/V AI TLT).
  <div class="note">
    <span class="note-title">Note</span>
    Refer to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_retrain.md %}">RZ/V AI Transfer Learning Tool How to Re-train AI model</a> to know the supported AI applications and how to use RZ/V AI TLT. This section just explains launching RZ/V AI TLT from AI Navigator.
  </div>
  <div class="note">
    <span class="note-title">Note</span>
    RZ/V AI TLT launched by AI Navigator V1.1.0 only supports <b>RZ/V2L AI Applications v2.10</b>.
  </div>
  <br>
  <h5 id="ainavi_option1-1">1. Configure the environment for the transfer learning tool</h5>
  <div class="note">
    <span class="note-title">Note</span>
    This is mandatory only for the first time. If you have already completed this step, you can pass to the next <a href="#ainavi_option1-2">2. Launch the transfer learning tool</a>.
  </div>
  <div class="container">
    <div class="row">
      <div class="col-6">
        (1) Click <b>[Start Setting...]</b> to configure the environments for RZ/V AI TLT.<br>
        At this time, the download page for RZ/V AI Transfer Learning Tool on the Renesas website will open automatically. Read the "SOFTWARE LICENSE AGREEMENT" and click "Accept and download" if you agree. <br>
        After the download is completed, select the downloaded file.<br>
        <br>
      </div>
      <div class="col-6">
        <a href="img/ainavi/ainavi_tlt_step1-1.png" data-lightbox="ainavi_tlt_step1-1"><img src="img/ainavi/ainavi_tlt_step1-1.png" alt="ainavi TLT install 1" width="90%" /></a>
      </div>
    </div>
  </div>
  <br>
  <div class="container">
    <div class="row">
      <div class="col-6">
        (2) The confirmation window appears indicating that it may take a long time to complete, then click <b>[OK]</b>.<br>
        <br>
      </div>
      <div class="col-6">
        <a href="img/ainavi/ainavi_tlt_step1-2.png" data-lightbox="ainavi_tlt_step1-2"><img src="img/ainavi/ainavi_tlt_step1-2.png" alt="ainavi TLT install 2" /></a>
      </div>
    </div>
  </div>
  <br>
  <div class="container">
    <div class="row">
      <div class="col-6">
        (3) The RZ/V AI TLT setup process begins. During the setup, a window appears prompting you to enter the root password. Enter your root password and the process will continue.<br>
        <br>
      </div>
      <div class="col-6">
        <a href="img/ainavi/ainavi_tlt_step1-3.png" data-lightbox="ainavi_tlt_step1-3"><img src="img/ainavi/ainavi_tlt_step1-3.png" alt="ainavi TLT install 3" width="90%" /></a>
      </div>
    </div>
  </div>
  <br>
  (4) When the setup process is complete, the installation window will close automatically. <br>
  At this point, please confirm the console on e<sup>2</sup> studio and logged as below. If it is the same, the setup process has completed successfully. <br>
{% highlight shell %}
Finished at exit code 0
Please confirm the console log.
{% endhighlight %}
  <div class="note">
    <span class="note-title">Note</span>
    The RZ/V AI TLT is installed as below:<br>
    (e.g.) If e<sup>2</sup> studio is installed in ~/.local/share/renesas/<b>e2_studio</b>, RZ/V AI TLT is  installed in ~/.local/share/renesas/<b>rzv_ai_tlt</b>.<br>
    <br>
    In addition, RZ/V AI TLT provides this user's manual (r21ut0254ej0210-rzv-ai-tlt.pdf), which is stored in rzv_ai_tlt/2.10/docs.<br>
  </div>
  <br>
  <h5 id="ainavi_option1-2">2. Launch the transfer learning tool</h5>
  <div class="container">
    <div class="row">
      <div class="col-6">
        Click <b>[Transfer Learning...]</b> and open RZ/V AI TLT.<br>
      </div>
      <div class="col-6">
        <a href="img/ainavi/ainavi_tlt_step2.png" data-lightbox="ainavi_tlt_step2"><img src="img/ainavi/ainavi_tlt_step2.png" alt="ainavi" width="90%" /></a>
      </div>
    </div>
  </div>
  <br>
  After finishing the transfer learning, you need to convert the trained AI model with DRP-AI TVM to run it on the target board. <br>
  Click the above button on this page <b>[Option2: Convert AI Model]</b> and see the procedures. <br>
  <br>
</div>

<div class="ContentsTVM">
  <h3 id="ainavi_option2" >Option2: Convert AI Model</h3>
  After training an AI model, convert an AI model to generate an executable runtime on the target device. For RZ/V, DRP-AI TVM is used, which is a machine learning compiler plugin for Apache TVM with AI accelerator DRP-AI.<br>
  <b>AI Model Conversion Tool Plugin</b> (hereafter referred to as "<b>TVM Plugin</b>") is a plugin for DRP-AI TVM and enables it to run on e<sup>2</sup> studio.<br>
  <br>
  For DRP-AI TVM, please refer to the following website and GitHub page.<br>
  <ul>
    <li><a href="https://www.renesas.com/us/en/key-technologies/artificial-intelligence/ai-tool-drp-ai-tvm">AI Tool: DRP-AI TVM (Renesas website)</a></li>
    <li><a href="https://github.com/renesas-rz/rzv_drp-ai_tvm">DRP-AI TVM (GitHub)</a></li>
  </ul>
  <div class="note">
    <span class="note-title">Note</span>
    See the AI Model Conversion Tool Plugin help page for details on how to use it. You can view it by selecting <b>[Help] > [Help Contents] > [AI Model Conversion Tool]</b>.<br>
    This section briefly describes the steps in the AI model conversion procedure usingy DRP-AI TVM on e<sup>2</sup> studio.
  </div>
  <div class="note">
    <span class="note-title">Note</span>
    Some AI models available in Renesas AI application need to skip the preprocessing setting. Refer to the <a href="https://www.renesas.com/us/en/software-tool/e2studio-information-rz-family#documents">AI Navigator Release Note</a> for the status of support.<br>
  </div>
  <br>
  <h5 id="ainavi_option2-1">1. Configure the environment for DRP-AI TVM on e<sup>2</sup> studio</h5>
  <div class="container">
    <div class="row">
      <div class="col-6">
        (1) Click <b>[Convert AI model]</b> on AI Navigator menu and open the "Convert AI Model" view.<br>
        <br>
        (2) Click <b>[Start Settings...]</b> and open the DRP-AI TVM.<br>
      </div>
      <div class="col-6">
        <a href="img/ainavi/ainavi_tvm_step1-1-2.png" data-lightbox="ainavi_tvm_step1-1-2"><img src="img/ainavi/ainavi_tvm_step1-1-2.png" alt="ainavi tvm_step1-1,2" width="90%" /></a>
      </div>
    </div>
    <br><br>
  </div>
  <br>
  <div class="container">
    <div class="row">
      <div class="col-6">
        (3) Confirm that the directory path has set and click <b>[Setup now]</b> if there is no problem.<br>
        <div class="note">
          <span class="note-title">Note</span>
          The directory path is set automatically when you specified the directory path in <a href="#ainavi_step1-4">Step 3-4</a>. If the path is not set, click <b>[Browse]</b> and set the path manually.
        </div>
        When the setup is completed, the Installation Success screen appears. Click <b>[Close]</b> to close the window.<br>
        <br>
      </div>
      <div class="col-6">
        <a href="img/ainavi/ainavi_tvm_step1-4.png" data-lightbox="ainavi_tvm_step1-4"><img src="img/ainavi/ainavi_tvm_step1-4.png" alt="ainavi tvm_step1-4" /></a>
      </div>
    </div>
  </div>
  <br>
  <h5 id="ainavi_option2-2">2. Input File Setting</h5>
  <div class="container">
    <div class="row">
      <div class="col-6">
        You need to set up the target project for DRP-AI TVM first. Specify the following items.<br>
        <br>
        <ul>
          <li><b>Project name</b></li>
          Select your target AI application project.
          <li><b>Device</b></li>
          Select your target device.
          <li><b>AI SDK Docker image name</b></li>
          Select the RZ/V AI SDK that you have set up to convert your AI model.
          <li><b>Select framework</b></li>f
          Select an AI framework that the input AI model file uses.
          <li><b>Input model file</b></li>
          The file path of your AI model is automatically set by RZ/V AI TLT. It is not necessary to specify this field.
          <li><b>Output directory</b></li>
          Specify the output directory after conversion.
        </ul>
      </div>
      <div class="col-6">
        <a href="img/ainavi/ainavi_tvm_pjsetting.png" data-lightbox="ainavi_tvm_pjsetting"><img src="img/ainavi/ainavi_tvm_pjsetting.png" alt="ainavi" weight="90%" /></a>
      </div>
    </div>
    After setting, click <b>[Next]</b>.
    <div class="note">
      <span class="note-title">Note</span>
      <b>[Setup environment]</b> on this view has the same function as <a href="#ainavi_option2-1">1. Configure the environment for DRP-AI TVM on e<sup>2</sup> studio</a>.<br>
      If you have already set up the DRP-AI TVM environment for your application, you do not need to click this button.
    </div>
  </div>
  <br>
  <h5 id="ainavi_option2-3">3. Preprocess Setting</h5>
  <div class="container">
    <div class="row">
      <div class="col-6">
        The pre-processing parameters are already set by default and do not need to be changed. Click <b>[Next]</b> on this Preprocessing Settings screen to proceed to the next step, <a href="#ainavi_option2-4">AI model conversion</a>. <br>
        However, if you want to use another input, such as using another camera, etc, configure the preprocessing parameters by following the steps below.<br>
        <br>
        (1) Select the target input node.<br>
        <br>
        (2) Confirm the <b>"Preprocessing output directory"</b> and change it if necessary.<br>
        By default, <b>"Use DRP-AI to speed up preprocessing"</b> is checked. If you want to skip preprocessing, clear the check box and click <b>[Next]</b> to go to the next step <a href="#ainavi_option2-4">AI model conversion</a>.<br>
        <br>
        (3) Set the input data parameters for preprocessing.<br>
      </div>
      <div class="col-6">
        <a href="img/ainavi/ainavi_tvm_preprocessing_1-3.png" data-lightbox="ainavi_tvm_preprocessing_1-3"><img src="img/ainavi/ainavi_tvm_preprocessing_1-3.png" alt="ainavi tvm preprocessing setting 1-3" weight="90%" /></a>
      </div>
    </div>
    <br><br>
    <div class="row">
      <div class="col-6">
        (4) Select the preprocessing operator parameters and enter each setting value.<br>
      </div>
      <div class="col-6">
        <a href="img/ainavi/ainavi_tvm_preprocessing_4.png" data-lightbox="ainavi_tvm_preprocessing_4"><img src="img/ainavi/ainavi_tvm_preprocessing_4.png" alt="ainavi tvm preprocessing setting 4" weight="90%" /></a>
      </div>
    </div>
    <br><br>
    <div class="row">
      <div class="col-6">
        (5) Specify the preprocessing output data format. These parameters are passed to the AI model.<br>
      </div>
      <div class="col-6">
        <a href="img/ainavi/ainavi_tvm_preprocessing_5.png" data-lightbox="ainavi_tvm_preprocessing_5"><img src="img/ainavi/ainavi_tvm_preprocessing_5.png" alt="ainavi tvm preprocessing setting 5" weight="90%" /></a>
      </div>
    </div>
  </div>
  <br>
  <h5 id="ainavi_option2-4">4. AI model conversion</h5>
  <div class="note">
    <span class="note-title">Click the button</span>
    The AI model conversion procedure is different for each device.<br>
    Click the button below that corresponds to your target device and the appropriate conversion procedure will appear.<br>
    <br>
    <div class="ButtonTVM_V2L">RZ/V2L</div>
    <div class="ButtonTVM_V2H">RZ/V2H</div>
    <br>
  </div>
  <div class="ContentsTVM_V2L">
    <div class="container">
      <div class="row">
        <div class="col-6">
          Start the AI model conversion to generate its runtime for <b>RZ/V2L</b> by following the steps below.<br>
          <br>
          (1) Configure the option setting.<br>
          Select "Optimization level".<br>
          If you want to check edit a conversion script here uses this conversion, click <b>[Check conversion script]</b>.<br>
          <br>
          (2)Click <b>[Start conversion]</b> and the conversion process will start. At this time, the console on e<sup>2</sup> studio will appear and display logs.<br>
          <br>
        </div>
        <div class="col-6">
          <a href="img/ainavi/ainavi_tvm_conversion_1-2.png" data-lightbox="ainavi_tvm_conversion_1-2"><img src="img/ainavi/ainavi_tvm_conversion_1-2.png" alt="ainavi ai model conversion start" weight="90%" /></a>
        </div>
      </div>
      <br><br>
      <div class="row">
        <div class="col-6">
          (3) When finishing the conversion, the result will be shown in the <b>"Conversion result"</b> area.<br>
        </div>
        <div class="col-6">
          <a href="img/ainavi/ainavi_tvm_conversion_3.png" data-lightbox="ainavi_tvm_conversion_3"><img src="img/ainavi/ainavi_tvm_conversion_3.png" alt="ainavi ai model conversion complete" weight="90%" /></a>
        </div>
      </div>
    </div>
    <br>
    <br>
    After the conversion is finished, you need to edit and build your AI application. <br>
    Click the above button on this page <b>[Option3: Edit Application]</b> and see the procedures. <br>
    <br>
    <div class="note">
      <span class="note-title">Note</span>
      Before moving to the next step, close the AI Model Conversion Tool.
    </div>
  <br>
  </div>
  <div class="ContentsTVM_V2H">
    <div class="container">
      <div class="row">
        <div class="col-6">
          Start the AI model conversion to generate its runtime for <b>RZ/V2H</b> by following the steps below.<br>
          <br>
          (1) Configure the option setting.Select "Optimization level".<br>
          If you want to check edit a conversion script here uses this conversion, click <b>[Check conversion script]</b>.<br>
          <br>
        </div>
        <div class="col-6">
          <a href="img/ainavi/ainavi_tvm_conversion_v2h_1-2.png" data-lightbox="/ainavi_tvm_conversion_v2h_1-2"><img src="img/ainavi//ainavi_tvm_conversion_v2h_1-2.png" alt="ainavi ai model conversion start(v2h)" weight="90%" /></a>
        </div>
      </div>
      (2) Configure the quantization setting.<br>
      <ol type="a">
        <li>Select the target input node.</li>
        <li>Specify the calibration data directory containing data to be used during the quantization process.</li>
        <div class="note">
          <span class="note-title">Note</span>
          For the calibration data directory, specify the directory where the data is stored.
          TVM Plugin supports the following extensions.<br>
          <i>.jpg .jpeg .png .bmp .gif .tif .tiff .npy</i>
        </div>
        <li>The Mean and Standard deviation parameters are already set by default and do not need to be changed.</li>
        <div class="note">
          <span class="note-title">Note</span>
          The Mean and Standard deviation parameters are the most important parameters for maintaining the model's accuracy.<br>
          If you want to change these parameters, make sure that the specified parameters match the normalization parameters used during training.<br>
          <br>
          For more details on how to change the Mean and Standard deviation, please see the TVM Plugin Help.(Click [Help]-[Help Contents] - [AI Model Conversion Tool].)
        </div>
      </ol>
      (3)Click <b>[Start conversion]</b> and the conversion process will start. At this time, the console on e<sup>2</sup> studio will appear and display logs.<br>
      <br>
      <div class="row">
        <div class="col-6">
          (4) When finishing the conversion, the result will be shown in the <b>"Conversion result"</b> area.<br>
        </div>
        <div class="col-6">
          <a href="img/ainavi/ainavi_tvm_conversion_v2h_4.png" data-lightbox="ainavi_tvm_conversion_v2h_4"><img src="img/ainavi/ainavi_tvm_conversion_v2h_4.png" alt="ainavi ai model conversion complete (v2h)" weight="90%" /></a>
        </div>
      </div>
    </div>
    <br>
    <br>
    After the conversion is finished, you need to edit and build your AI application. <br>
    Click the above button on this page <b>[Option3: Edit Application]</b> and see the procedures. <br>
    <br>
    <div class="note">
      <span class="note-title">Note</span>
      Before moving to the next step, close the AI Model Conversion Tool.
    </div>
  <br>
  </div>
  <br>
</div>

<div class="ContentsAppBuild">
  <h3 id="ainavi_option3" >Option3: Edit Application</h3>
  You can modify your AI application source codes and build them on e<sup>2</sup> studio.<br>
  Click <b>[Edit Application]</b> on the AI Navigator menu and follow the instructions below. <br>
  <br>
  <div class="container">
    <div class="row">
      <div class="col-2">
      </div>
      <div class="col-8">
        <a href="img/ainavi/ainavi_build.png" data-lightbox="ainavi_build"><img src="img/ainavi/ainavi_build.png" alt="ainavi build" weight="90%" /></a><br>
      </div>
      <div class="col-2">
      </div>
    </div>
  </div>
  <br>
  <h5 id=build_setup>1. Configure the build environment</h5>
  Click <b>[Start Settings...]</b>, and then start configuring the build environment for the AI application. <br>
  Once the setup process is complete, the appropriate toolchain for the target e<sup>2</sup> studio project is automatically registered.<br>
  <div class="container">
    <div class="row">
      <div class="col-6">
        <div class="note">
          <span class="note-title">Note</span>
          After registering the toolchain, you need to specify the toolchain version for your AI application.<br>
          Click <b>[Project] -> [Properties] -> [C/C++ Build] -> [Settings]</b>, and click the <b>"Toolchain"</b> tab.<br>
          Then, select the toolchain version in <b>"Use integrated tool chain version"</b> as shown in the figure, and click <b>[Apply and Close]</b>. <br>
          *The toolchain version is (RZ/V2L) 3.1.21, (RZ/V2H) 3.1.26 in AI Navigator 1.1.0.
        </div>
      </div>
      <div class="col-6">
        <a href="img/ainavi/ainavi_build_set_toolchain_ver.png" data-lightbox="ainavi_build_set_toolchain_ver"><img src="img/ainavi/ainavi_build_set_toolchain_ver.png" alt="ainavi build set toolchain version" width="90%" /></a>
      </div>
    </div>
  </div>
  <br>
  <h5 id=build_edit_source>2. Edit Source codes</h5>
  Click <b>[Edit...]</b> and edit a source code.<br>
  <div class="note">
    <span class="note-title">Note</span>
    When you click <b>[Edit...]</b>, a main source file of the target AI application appears.<br>
    If you want to edit another source file, select it in the src directory on the project explorer.
  </div>
  <br>
  <h5 id=build_source>3. Build</h5>
  Click <b>[Build]</b> and start building. The build result will be shown in the console on the e<sup>2</sup> studio.<br>
  <br>
</div>
<br>

<h3 id="ainavi_step4" >Step 4: Run on the Board</h3>
It's time to run your AI application on the target board.<br>
Click <b>[Run on the Board]</b> on the AI Navigator menu and follow the steps below. <br>
<div class="container">
  <div class="row">
    <div class="col-2">
    </div>
    <div class="col-8">
      <a href="img/ainavi/ainavi_run_the_ai.png" data-lightbox="ainavi_run_ai"><img src="img/ainavi/ainavi_run_the_ai.png" alt="ainavi run ai" weight="90%" /></a><br>
    </div>
    <div class="col-2">
    </div>
  </div>
</div>
<br>
<h5 id=ainavi_format_sd>1. Format SD card</h5>
Insert your micro SD card into your Linux host PC.<br>
Click on <b>[Create a bootable disk...]</b> and you can automatically format your SD for booting the board.<br>

<div class="note">
  <span class="note-title">Note</span>
  For formatting procedure on Linux console, please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link appendix.md %}#A2">A2. Format SD card</a>, <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started_v2l.md %}#step7-1">1. Setup RZ/V2L EVK</a> or <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started_v2h.md %}#step7-1">1. Setup RZ/V2H EVK</a>, and click on <b>eSD Bootloader</b>.
</div>
<div class="note">
  <span class="note-title">Note for RZ/V2H users</span>
  <b>bmap-tools</b> is used to set up the RZ/V2H EVK. If you do not have it installed, the following message will appear when creating a bootable disk.<br>
  <i>"bmaptool is required for this setup program. Do you want to install it now?"</i><br>
  If you accept it, type "yes" and the creation process will continue.
</div>
<br>
<h5 id=ainavi_boot_board>2. Boot the board</h5>
Start booting the board with the formatted SD card. 
If you are not sure how to boot the target board, click on <b>[Boot instruction...]</b> and the instructions for <a href="https://Tool-support.renesas.com/tool-support/Zoo/boot_boad_guide/RZV2L_board_setup_e2studio.html" target="_blank" rel="noopener noreferrer">Boot RZ/V2L Evaluation Board Kit</a> or <a href="https://Tool-support.renesas.com/tool-support/Zoo/boot_boad_guide/RZV2H_board_setup_e2studio.html" target="_blank" rel="noopener noreferrer">Boot RZ/V2H Evaluation Board Kit</a> will appear.<br>
<div class="note">
  <span class="note-title">Note</span>
  At this point, be sure to configure each IP address for the connection between your Linux host PC and the target board.<br>
  This may cause the later process (copying AI models and applications, and running the AI application) to fail if you have not configured it.<br>
  <br>
  In addition, if you want to use IP addresses other than those set by default in AI Navigator, please see <a href="ainavi_appendix.html#ainavi_appendix_c">Settings required when using other IP addresses of target board</a>.
</div>
<br>
<h5 id=ai_navi_copy_ai>3. Copy AI model and Application to the board</h5>
Once the board is configured, you are ready to transfer your AI models and AI applications to the board.<br>
<br>
Click <b>[Copy AI]</b> to copy your AI models to the board.<br>
Then, click <b>[Copy App]</b> to copy your AI applications to the board.<br>
<br>
<h5 id=build_source>4. Run AI application</h5>
Click <b>[Run the AI]</b> and start running your AI application on the board.<br>
<div class="note">
  <span class="note-title">Note</span>
  Please read the readme.md in each AI application project before using it. Each readme.md describes the specification, such as which input mode (such as MIPI or USB camera) is supported, how to run the application, and so on.<br>
  <br>
  Also, read "RZV_AI_App_mode_switching_guide_en.pdf" in your imported AI application project. This document describes how to change some configurations when changing the input mode of AI application.<br>
</div>
<br>
<h4>
  This is the end of AI Navigator Quick Start Guide.
</h4>
Please refer to <a href="ainavi_appendix.html">AI Navigator Quick Start Guide Appendix</a> for the additional information.<br>
<br><br>

<script>
$(function() {
    $(".ButtonTLT").click(function() {
        $(".ContentsTLT").toggleClass("DisplayTLT");
        $(".ButtonTLT").toggleClass("clicked");
        $(".ButtonTVM").removeClass("clicked");
        $(".ButtonAppBuild").removeClass("clicked");
        $(".ContentsTVM").removeClass("DisplayTVM");
        $(".ContentsAppBuild").removeClass("DisplayAppBuild");
    });
    $(".ButtonTVM").click(function() {
        $(".ContentsTVM").toggleClass("DisplayTVM");
        $(".ButtonTVM").toggleClass("clicked");
        $(".ButtonTLT").removeClass("clicked");
        $(".ButtonAppBuild").removeClass("clicked");
        $(".ContentsTLT").removeClass("DisplayTLT");
        $(".ContentsAppBuild").removeClass("DisplayAppBuild");
    });
    $(".ButtonAppBuild").click(function() {
        $(".ContentsAppBuild").toggleClass("DisplayAppBuild");
        $(".ButtonAppBuild").toggleClass("clicked");
        $(".ButtonTLT").removeClass("clicked");
        $(".ButtonTVM").removeClass("clicked");
        $(".ContentsTLT").removeClass("DisplayTLT");
        $(".ContentsTVM").removeClass("DisplayTVM");
    });
    $(".ButtonTVM_V2L").click(function() {
        $(".ContentsTVM_V2L").toggleClass("DisplayTVM_V2L");
        $(".ButtonTVM_V2L").toggleClass("clicked");
        $(".ButtonTVM_V2H").removeClass("clicked");
        $(".ContentsTVM_V2H").removeClass("DisplayTVM_V2H");
    });
    $(".ButtonTVM_V2H").click(function() {
        $(".ContentsTVM_V2H").toggleClass("DisplayTVM_V2H");
        $(".ButtonTVM_V2H").toggleClass("clicked");
        $(".ButtonTVM_V2L").removeClass("clicked");
        $(".ContentsTVM_V2L").removeClass("DisplayTVM_V2L");
    });
});
</script>
<style>
  .ButtonTLT{
      display: inline-block;
      background: #4471A9;
      color: #FFFFFF;
      font-weight: bold;
      min-width: max-content;
      padding: 5px 20px 5px;
      cursor: pointer;
  }
  .ButtonTLT.clicked{
      background: #797979;
  }
  .ContentsTLT{
    display: none;
    background: #FFFFFF;
    border: 1px dotted #B1C6E0;
    margin-top: 20px; 
  }
  .DisplayTLT{
    display: block;
  }
  .ButtonTVM{
      display: inline-block;
      background: #669933;
      color: #FFFFFF;
      font-weight: bold;
      min-width: max-content;
      padding: 5px 20px 5px;
      cursor: pointer;
  }
  .ButtonTVM.clicked{
      background: #797979;
  }
  .ContentsTVM{
    display: none;
    background: #FFFFFF;
    border: 1px dotted #B1C6E0;
    margin-top: 20px; 
  }
  .DisplayTVM{
    display: block;
  }
  .ButtonAppBuild{
      display: inline-block;
      background: #993399;
      color: #FFFFFF;
      font-weight: bold;
      min-width: max-content;
      padding: 5px 20px 5px;
      cursor: pointer;
  }
  .ButtonAppBuild.clicked{
      background: #797979;
  }
  .ContentsAppBuild{
    display: none;
    background: #FFFFFF;
    border: 1px dotted #B1C6E0;
    margin-top: 20px; 
  }
  .DisplayAppBuild{
    display: block;
  }
    .ButtonTVM_V2L{
      display: inline-block;
      background: #2a289d;
      color: #FFFFFF;
      font-weight: bold;
      min-width: max-content;
      padding: 5px 20px 5px;
      cursor: pointer;
  }
  .ButtonTVM_V2L.clicked{
      background: #797979;
  }
  .ContentsTVM_V2L{
    display: none;
    background: #FFFFFF;
    border: 0px;
    margin-top: 20px; 
  }
  .DisplayTVM_V2L{
    display: block;
  }
  .ButtonTVM_V2H{
      display: inline-block;
      background: #2a289d;
      color: #FFFFFF;
      font-weight: bold;
      min-width: max-content;
      padding: 5px 20px 5px;
      cursor: pointer;
  }
  .ButtonTVM_V2H.clicked{
      background: #797979;
  }
  .ContentsTVM_V2H{
    display: none;
    background: #FFFFFF;
    border: 0px;
    margin-top: 20px; 
  }
  .DisplayTVM_V2H{
    display: block;
  }
</style>