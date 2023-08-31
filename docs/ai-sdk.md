---
layout: default
---

<div class="container">
    <div class="row">
        <div class="top col-12">
            AI SDK
        </div>
    </div>
</div>

<br>
<br>

<div class="container">
    <div class="row">
        <div class="col-12 col-md-6">
            AI Software Development Kit (AI SDK) is an AI application development environment for RZ/V2L Evaluation Board Kit.
            <br>
            <br>
            Since it contains Yocto Linux with bootloader, Linux Kernel, Cross Compiler and a complete set of libraries for DRP-AI, graphics and codec, users can develop AI Applications <b>easily</b> and <b>quickly</b> with AI SDK.
            <br>
            In the AI Applications, USB/MIPI camera can be used with Video for Linux 2 (V4L2) API.
            <br>
            <br>
            For more information, see <a href="https://www.renesas.com/software-tool/rzv2l-ai-software-development-kit">RZ/V2L AI SDK download page</a>.
            <br>
            <br>
            <br>
        </div>
        <div class="col-12  col-md-6 text-center">
            <a href="img/block.svg" data-lightbox="group"><img src="img/block.svg" alt="AI Application and AI SDK software"></a><br>
        </div>
    </div>
    <div class="row">
        <div class="col-12">
            <h3>Key Features</h3>
            AI SDK provides following components.
            <br>
            <br>
            <h6>
                <!-- Memo: Need to update based on the RZ/V2L AI SDK Release Note. -->
                <table>
                    <tr>
                        <th>Items</th>
                        <th>Details</th>
                    </tr>
                    <tr>
                        <td>Bootloader</td>
                        <td>Files to boot the board.</td>
                    </tr>
                    <tr>
                        <td>Linux Kernel Files</td>
                        <td>Pre-build binary files for RZ/V2L Linux Kernel.</td>
                    </tr>
                    <tr>
                        <td>Root filesystem</td>
                        <td>Filesystem for the RZ/V2L Linux.</td>
                    </tr>
                    <tr>
                        <td>Cross Compiler</td>
                        <td>Compiler for Linux application on RZ/V2L Linux.</td>
                    </tr>
                    <tr>
                        <td>AI SDK Installer</td>
                        <td>Installer for AI application development environment on Docker.</td>
                    </tr>
                </table>
                RZ/V2L Linux contains following packages.
                <ul>
                    <li>DRP-AI Driver</li>
                    <li>Graphics Library Evaluation Version *1</li>
                    <li>Video Codec Library Evaluation Version *1 (H.264)</li>
                    <li>Video for Linux 2 (V4L2)</li>
                    <li>OpenCV</li>
                    <li>Tesseract</li>
                    <li>Other OSS packages</li>
                </ul>
                *1: Note that Graphics Library and Codecs Library Evaluation Version have a limitation that system stops running after around 10 hours.<br>
            </h6>
            <br>
            For more information on AI SDK, see <a href="https://www.renesas.com/software-tool/rzv2l-ai-software-development-kit">RZ/V2L AI SDK Rlease Note</a>.
        </div>
    </div>
    <div class="row">
        <div class="col-12" align="right">
            <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}" role="button">
                Back to Home >
            </a>
        </div>
    </div>
</div>
