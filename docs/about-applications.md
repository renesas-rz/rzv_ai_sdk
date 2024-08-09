---
layout: default
---

<div class="container" style="max-width:100%;">
    <div class="row">
        <div id="page-top" class="top col-12">
            About AI Applications
        </div>
    </div>
</div>
<br>
<div class="container">
    <div class="row">
        <div class="col-12">
            <h5 align="left">
                This page explains the overview of <a href="{{ site.url }}{{ site.baseurl }}{% link index.md %}#ai-applications">
                AI Applications</a>.
            </h5>
        </div>
    </div>
</div>
<div class="container">
    <div class="row">
        <div class="col-12">
            <h3 align="left"><i>What is AI Applications?</i></h3>
            AI Applications are sets of application source code, pre-build application binary and pre-trained AI model objects, which allow users to run AI Applications easily and quickly.<br>
            Users can select the category of applications and access the applications provided on GitHub.<br>
            <a class="btn btn-secondary square-button ms-3 mt-3" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}#ai-applications" role="button">
            Select category of AI Applications >
            </a>
        </div>
    </div>
    <br>
    <br>
    <div class="row">
        <div class="col-12">
            <h3 align="left" tag="fileconf"><i>File Configuration</i></h3>
            Application directory has the following structure.
            <br>
            <table>
            <tr>
                <th>Directory</th>
                <th>Details</th>
            </tr>
            <tr>
                <td><code>exe_*</code></td>
                <td>Execution environment required when running application on each supported board.</td>
            </tr>
            <tr>
                <td><code>src_*</code></td>
                <td>Application Source Code (C++) for each supported board.</td>
            </tr>
            <tr>
                <td>Other directory</td>
                <td><b>Optional</b>: Extra files that may be required other than above.</td>
            </tr>
            <tr>
                <td><code>Makefile</code></td>
                <td><b>Optional</b>: Configuration to build the application.<br>It may be included in the <code>src_*</code> directory.</td>
            </tr>
            <tr>
                <td><code>README.md</code></td>
                <td><b>Optional</b>: Documentation of the application.</td>
            </tr>
            </table>
        </div>
    </div>
    <br>
    <br>
    <div class="row">
        <div class="col-12">
            <h3 align="left" tag="prerequisite"><i>Prerequisites</i></h3>
            To run AI Applications, users are required to have followings.<br>
            <ul class="mt-2">
                <li>Basic Linux terminal, Linux command and filesystem hierarchy knowledge.<br>
                </li>
                <li><a href="https://git-scm.com/">Git</a> knowledge and skills of followings.
                    <ul>
                        <li>Clone the repository.</li>
                        <li>Checkout the branch.</li>
                        <li>Get access to files from a certain commit ID/tag.</li>
                    </ul>
                </li>
            </ul>
            <div class="note">
            <span class="note-title" tag="ainav">Note</span>
            AI Applications and AI SDK is based on CUI (Linux terminal/command).<br>
            For users who would like to use <b>GUI</b> instead of CUI, please use AI Navigator (Renesas e<sup>2</sup> studio plugin).<br>
            <a class="btn btn-secondary square-button ms-3 mt-1" href="https://www.renesas.com/software-tool/e-studio" role="button">
AI Navigator (e<sup>2</sup> studio plugin) >
            </a>
            </div>
        </div>
    </div>
    <br>
    <br>
    <div class="row">
        <div class="col-12">
            <h3 align="left" tag="tag-rule"><i>Git Tag Rule</i></h3>
            Necessary files for AI Applications are provided on GitHub repository.<br>
            Users can download them using <b><a href="https://git-scm.com/">git</a></b> command on Linux PC.<br>
            <br>
            In GitHub repository, application source code and related files are provided under the following rules.
            <br>
            <div class="ms-3 mt-1">
                Branches
                <ul>
                    <li><b>main</b>
                        <ul>
                            <li>
                            The latest application source code, binary files and documentations.</li>
                        </ul>
                    </li>
                </ul>
                Tags
                <ul>
                    <li><b>v<i>X</i>.<i>XX</i></b>
                        <ul>
                            <li>
                            Application source code, binary files and documentations of each version.</li>
                            <li>The latest version should be the same as the main branch.</li>
                            <li>
                            E.g., To download the files of AI Applications <b>v1.00</b>, users can use following command.<br>
{% highlight shell %}
git clone -b v1.00 <GitHub repository url>
{% endhighlight %}
                            </li>
                        </ul>
                    </li>
                </ul>
            </div>
            <div class="note">
                <span class="note-title">Note</span>
                The link in <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}">AI Applications</a> page guides you to the "main" branch of GitHub repository, which is the latest information.<br>
                Please be aware that latest AI Application requires latest RZ/V AI SDK.<br>
            </div>
            Directory structure of each application in GitHub repository is explained in the <a href="fileconf">File Configuration</a>.
        </div>
    </div>
</div>
<br>
<br>
<div class="container">
    <div class="row">
        <div class="col-12" align="left">
            <h3 align="left" tag="camera"><i>Camera input information</i></h3>
            <h4 class="u_line" align="left" tag="mipi">MIPI camera</h4>
            <h5 class="mt-3 ms-3 mb-2">RZ/V2L EVK</h5>
            <ul>
                <li>
                    Google Coral Camera is included in the Evaluation Board Kit.
                    <br>
                    <br>
                </li>
            </ul>
            <h5 class="mt-3 ms-3 mb-2">RZ/V2H EVK</h5>
            <ul>
                <li>
                    Use the e-CAM22_CURZH camera, which supports FHD (1920x1080) resolution, provided by <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp">e-con Systems</a>.<br>
                    <ul>
                        <li>
                            To use e-CAM22_CURZH camera in AI Applications, users are required to change the source code.<br>
                            Please contact <a href="https://www.e-consystems.com/renesas/sony-starvis-imx462-ultra-low-light-camera-for-renesas-rz-v2h.asp">e-con Systems</a> for more details.
                            <br>
                            <br>
                        </li>
                        <li>
                            To use camera input resolution from VGA (640x480) to FHD (1920x1080), users are required to apply followng changes.
                            <ol>
                                <li>
                                    Change camera input size in <code>define.h</code> and other files.<br>
                                    <br>
                                    <div class="box1">
                                        <u><b>Example:</b></u><br>
                                        In <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v5.00pre/R01_object_detection">R01_object_detection</a>, change the <a herf="https://github.com/renesas-rz/rzv_ai_sdk/tree/v{{ site.version }}/R01_object_detection/src/define.h"><code>define.h</code></a> as shown below.<br>
                                        <b>Before</b>
{% highlight cpp %}
#define CAM_IMAGE_WIDTH             (640)
#define CAM_IMAGE_HEIGHT            (480)
{% endhighlight %}
                                        <b>After</b>
{% highlight cpp %}
#define CAM_IMAGE_WIDTH             (1920)
#define CAM_IMAGE_HEIGHT            (1080)
{% endhighlight %}
                                    </div>
                                    <br>
                                </li>
                                <li>
                                    Change the AI model object directory name in <code>define.h</code>.<br>
                                    AI model object for FHD input size is provided in the <code>*_fhd</code> directory.<br>
                                    <br>
                                    <div class="box1">
                                        <u><b>Example:</b></u><br>
                                        In <a href="https://github.com/renesas-rz/rzv_ai_sdk/tree/v5.00pre/R01_object_detection">R01_object_detection</a>, change the <a herf="https://github.com/renesas-rz/rzv_ai_sdk/tree/v{{ site.version }}/R01_object_detection/src/define.h"><code>define.h</code></a> as shown below.<br>
                                        <b>Before</b>
{% highlight cpp %}
const static std::string model_dir = "yolov3_onnx";
{% endhighlight %}
                                        <b>After</b>
{% highlight cpp %}
const static std::string model_dir = "yolov3_onnx_fhd";
{% endhighlight %}
                                    </div>
                                    <div class="note">
                                        <span class="note-title">Note 1</span>
                                        Some applications may require users to download the <code>*_deploy.so</code> (one of AI Model object files) from the <a href="https://github.com/renesas-rz/rzv_ai_sdk/releases/">Release page</a> due to its filesize.<br>
                                        Download the corresponding file  into <code>exe_v2h</code> according to each <code>README.md</code> and rename it to <code>deploy.so</code>.
                                    </div>
                                    <div class="note">
                                        <span class="note-title">Note 2</span>
                                        If the application does not provide the AI model object for FHD input size (<code>*_fhd</code> directory), you can use the same AI model object as for VGA input size.
                                    </div>
                                    <br>
                                </li>
                                <li>
                                    Other camera input size information when applying e-CAM22_CURZH camera change.
                                </li>
                            </ol>
                        </li>
                    </ul>
                </li>
            </ul>
            <h4 class="u_line" align="left" tag="usb">USB camera</h4>
            For both RZ/V2L EVK and RZ/V2H EVK, AI Applications support USB camera with VGA (640x480) resolution in 'YUYV' (YUYV 4:2:2) format.<br>
        </div>
    </div>
</div>
<br>
<br>
<div class="container">
    <div class="row">
        <div class="col-12" align="left">
            <h3 align="left" tag="ending"><i>Licenses</i></h3>
            <h4 class="u_line" align="left" tag="usb">AI models</h4>
            <p class="ms-3">
                See <code>README.md</code> provided in each AI Applications.<br>
            </p>
            <h4 class="u_line" align="left" tag="usb">AI Applications Image</h4>
            <p class="ms-3">
                All images listed in <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}">AI Applications page</a> are proprietary files owned exclusively by Renesas Electronics Corporation.<br>
            </p>
        </div>
    </div>
</div>
<br>
<br>
<div class="container">
    <div class="row">
        <div class="col-12" align="left">
            <h3 align="left" tag="ending"><i>Reference</i></h3>
            To select the AI Application, choose the category from AI Applications section of the top page.<br>
            <a class="btn btn-secondary square-button mt-1 ms-3" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}#ai-applications" role="button">
Go to Home to select category >
            </a>
            <br>
            <br>
            Getting Started explains the whole procedure to build/run the AI Applications.<br>
            To build the application, see Step 6 of Getting Started.<br>
            <a class="btn btn-secondary square-button-gray mt-1 ms-3" href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step6" role="button">
Go to Getting Started Step 6 >
            </a>
            <br>
            <br>
            To run the application, see Step 7~8 of Getting Started.<br>
            <a class="btn btn-secondary square-button-gray mt-1 ms-3" href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}#step7" role="button">
Go to Getting Started Step 7 >
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
<br>
<br>
    