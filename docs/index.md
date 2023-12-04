---
layout: default
---

<div class="container">
    <div class="row">
        <div id="page-top" class="top col-12">
            AI Applications and AI SDK<br>
            on RZ/V series
        </div>
    </div>
</div>
<div class="container">
    <div class="row">
        <div class="col-12 text-center">
            <br>
            <br>
            <i>
                <h1 class="sub">The best solution for starting your AI applications.</h1>
                <h5 class="sub">AI Applications and AI SDK are quick and easy solutions for starting AI.  <br>
                    It provides various AI applications for free.</h5>
            </i>
        </div>
        <br>
        <div class="col-12 text-center">
            <br>
            <a href="img/top.svg" data-lightbox="group"><img src="img/top.svg" alt="AI Application and AI SDK overview"></a><br>
        </div>
        <div class="col-12"  align="right">
            <br>
            <a class=" text-right btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}">View AI Applications ></a>
            <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link ai-sdk.md %}" role="button">View AI SDK ></a>
        </div>
    </div>
</div>
<br>
<br>
<br>
<h3 id="new" >
    What's new
</h3>
<div class="container">
    <div class="row">
        <div class="col-12">
            <h6 align="right" >
<<<<<<< HEAD
                2023.12.4
            </h6>
            <ul>
                <li>
                    <b>Tutorial Video - Getting Started v2.10</b> is now available.<br>
                    <ul>
                        <li> 
                            Users can learn the content of Getting Started in the video.<br>
                            It contains the boot demonstration using eSD bootloader.
                        </li>
                        <li>
                            Based on RZ/V2L AI SDK v2.10.
                        </li>
                    </ul>
                </li>
            </ul>
            For more details, see <a href="{{ site.url }}{{ site.baseurl }}{% link index.md %}#video">Video</a>.
            <!-- For more details, see <a href="https://github.com/renesas-rz/rzv_ai_sdk/releases">GitHub Release Note</a>. -->
            <br>
        </div>
        <div class="col-12">
            <h6 align="right" >
                2023.11.30
            </h6>
            <ul>
                <li>
                    <b>AI Applications Demo v2.10</b> is now available.<br>
                    <ul>
                        <li> 
=======
                2023.11.30
            </h6>
            <ul>
                <li>
                    <b>AI Applications Demo v2.10</b> is now available.<br>
                    <ul>
                        <li> 
>>>>>>> 39d4462e29b9e5a11df8378721f899d96e1b917b
                            Supported RZ/V2L AI SDK v2.10.<br>
                            The file size is decreased to around 3.4GB since the OSS package is deleted and provided in AI SDK Source Code.
                        </li>
                        <li>
                            Added 13 AI Applications.
                        </li>
                    </ul>
                </li>
            </ul>
            For more details, see <a href="{{ site.url }}{{ site.baseurl }}{% link index.md %}#demo">Demo</a>.
            <!-- For more details, see <a href="https://github.com/renesas-rz/rzv_ai_sdk/releases">GitHub Release Note</a>. -->
            <br>
        </div>
        <div class="col-12" align="right">
            <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link history.md %}" role="button">
                View Version History >
            </a>
        </div>
    </div>
</div>
<br>
<br>
<br>
<h3 id="getting-started" >Getting Started</h3>
<div class="container">
    <div class="row">
        <div class="col-12 col-sm-8">
            Renesas RZ/V AI Software Development Kit (AI SDK) is the most comprehensive solution for building end-to-end accelerated AI applications.  AI SDK includes Yocto Linux with bootloader, Linux Kernel, Cross Compiler and a complete set of libraries for DRP-AI, graphics and codec.  
            <br>
            <br>
            <i>Getting Started</i> is a complete guide to learn <b>how to run AI Applications</b>, which explains the procedure for setting up the development environment, compiling AI Applications, setting up the board and running AI Applications.
            <br><br>
            <h5>Get your target board now and <a href="{{ site.url }}{{ site.baseurl }}{% link getting_started.md %}">GET STARTED.</a></h5>
            <a href="#video">Tutorial video</a> will help you understand better. <br>
        </div>
        <div class="start col-12 col-sm-4">
            <img  src="img/get_started.svg" alt="Get Started"/>
        </div>
    </div>
</div>
 
<br>
<br>
<br>

<h3 id="ai-applications" align="center">AI Applications</h3>
<p align="center">AI Applications provides the source code, pre-build application binary and pre-trained AI model objects,<br>
    which allow you to select the application from various use cases, and run it on the board immediately.</p>
<p align="center">Choose the category of applications.</p>

<div class="container">
    <div class="row">
        <div class="col-lg-6 col-xxl-3">
            <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#agriculture"><img width="100%" src="img/agriculture.jpg" alt="category"/></a> <br>
            <ul class="category">
                <li id="agriculture">
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#agriculture">Agriculture</a> 
                </li>
            </ul>
        </div>
        <div class="col-lg-6 col-xxl-3">
            <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#healthcare"><img width="100%" src="img/healthcare.jpg" alt="category"/> </a> <br>
            <ul class="category">
                <li id="healthcare">       
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#healthcare">Healthcare</a>
                </li>
            </ul>
        </div>
        <div class="col-lg-6 col-xxl-3">
            <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#industrial"><img width="100%" src="img/industry.jpg" alt="category"/></a> <br>
            <ul class="category">
                <li id="industrial">
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#industrial">Industrial</a>
                </li>
            </ul>
        </div>
        <div class="col-lg-6 col-xxl-3">
            <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#building"><img width="100%" src="img/building.jpg" alt="category"/></a> <br>
            <ul class="category">
                <li id="building">       
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#building">Smart Building</a>
                </li>
            </ul>
        </div>
        <div class="col-lg-6 col-xxl-3">
            <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#city"><img width="100%" src="img/city.jpg" alt="category"/></a> <br>
            <ul class="category">
                <li id="city">       
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#city">Smart City</a>
                </li>
            </ul>
        </div>
        <div class="col-lg-6 col-xxl-3">
            <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#home"><img width="100%" src="img/home.jpg" alt="category"/></a> <br>
            <ul class="category">
                <li id="home">
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#home">Smart Home</a>
                </li>
            </ul>
        </div>
        <div class="col-lg-6 col-xxl-3">
            <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#retail"><img width="100%" src="img/retail.jpg" alt="category"/> </a> <br>
            <ul class="category">
                <li id="retail">
                    <a href="{{ site.url }}{{ site.baseurl }}{% link applications.md %}#retail">Retail</a>
                </li>
            </ul>
        </div>
    </div>
</div>

<br>
<br>
<h3 id="demo">Demo</h3>
<div class="container">
    <div class="row">
        <div class="col-12">
            With the demo binary, users can try the AI Applications without having AI SDK environment.<br>
            Download the Demo and refer to <a href= "{{ site.url }}{{ site.baseurl }}{% link demo.md %}">How to Use Guide</a> for more details.
            <br>
            <br>
            <a class="btn btn-primary download-button" href="https://www.renesas.com/document/sws/rzv2l-ai-applications-demo-sd-image-version-210" role="button">
                Download Demo
            </a>
            <br>
            <br>
            <h6>
                <b>Notes:
                    <ol>
                        <li>Demo is based on AI Applications v2.10 and AI SDK v2.10.</li>
                        <li>Demo zip filesize is around 3.4GB.</li>
                        <li>Demo zip file is created using the evaluation version of RZ/V2L Graphics Library and Codecs Library, which has a limitation that system stops runinng after around 10 hours.</li>
                    </ol>
                </b>
            </h6>
            <br>
        </div>
    </div>
</div>

<br>
<br>
<h3 id="video">Video</h3>
<br>
<h5 id="training-video"><b>Training video</b></h5>
<div class="container">
    <div class="row">
        <div class="col-lg-6 col-xl-4">
            <iframe width="100%" height="55%" src="https://www.youtube.com/embed/CPeE2q3TdOY" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen>
            </iframe>
            <ul class="videodetails">
                <li>
                    <a href="https://youtu.be/CPeE2q3TdOY">RZ/V2L AI Applications Tutorial - Getting Started v2.10 (Youtube) </a>
                    <br><br>
                    This is a tutorial video explaining the content of getting started.<br>
                    This tutorial is based on RZ/V2L AI SDK version <b>2.10</b>, which supports both eSD bootloder and eMMC bootloader.<br>
                    In this video, eSD bootloader is used.<br>
                </li>
            </ul>
        </div>
        <div class="col-lg-6 col-xl-4">
            <iframe width="100%" height="55%" src="https://www.youtube.com/embed/wFbTomH8oPs" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen>
            </iframe>
            <ul class="videodetails">
                <li>
                    <a href="https://youtu.be/wFbTomH8oPs">RZ/V2L AI Applications Tutorial - Getting Started v1.00 (Youtube) </a>
                    <br><br>
                    This is a tutorial video explaining the content of getting started.<br>
                    This tutorial is based on RZ/V2L AI SDK version <b>1.00</b>, which only supports eMMC bootloader.<br>
                </li>
            </ul>
        </div>
    </div>
</div>
<br>
<br>
<div class="container">
    <div class="row">
        <div class="col-12" align="right">
            <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}#page-top" role="button">
                Back to Top >
            </a>
        </div>
    </div>
</div>