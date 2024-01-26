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
            AI SDK is specifically made for RZ/V2L Evaluation Board Kit with fixed Linux components.
            For those of you who would like to customize Linux environment, i.e., change memory map or develop your own board, you need to build the Yocto Linux source code.
            <br>
            Yocto Linux source code is provided as AI SDK Source Code.
            <br>
            Please refer to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk.md %}">How to Build AI SDK</a> for more details.
            <br>
            <br>
            AI SDK has a CUI enviroment and a GUI environment.<br>
            Each has the following functions.<br><br>
            <table class="gstable">
                <tr>
                    <th>Functions</th>
                    <th>CUI env.</th>
                    <th>GUI env. (e<sup>2</sup>studio)</th>
                </tr>
                <tr>
                    <td>Install AI SDK</td>
                    <td>&#10004;</td>
                    <td>&#10004;</td>
                </tr>
                <tr>
                    <td>Build AI Applications</td>
                    <td>&#10004;</td>
                    <td>&#10004;<a href="#footnote_gui"><sup>*1</sup></a></td>
                </tr>
                <tr>
                    <td>Build AI SDK</td>
                    <td>&#10004;</td>
                    <td>-</td>
                </tr>
                <tr>
                    <td>Transfer Learning</td>
                    <td>-</td>
                    <td>&#10004;<a href="#footnote_gui"><sup>*1</sup></a></td>
                </tr>
            </table>
            <span id="footnote_gui">*1: There is a limit to the number of AI Applications supported.</span>
            <br>
            <br>
            To use the CUI environment, see <a href="https://www.renesas.com/software-tool/rzv2l-ai-software-development-kit">RZ/V2L AI SDK download page</a>.<br>
            To use the GUI environment (e<sup>2</sup>studio), see <a href="https://www.renesas.com/software-tool/e2studio-information-rz-family">e<sup>2</sup>studio for RZ Family download page</a>.<br>
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
                    <li>Graphics Library Evaluation Version <a href="#footnote_eval"><sup>*2</sup></a></li>
                    <li>Video Codec Library Evaluation Version <a href="#footnote_eval"><sup>*2</sup></a> (H.264)</li>
                    <li>Video for Linux 2 (V4L2)</li>
                    <li>OpenCV</li>
                    <li>Tesseract</li>
                    <li>Other OSS packages</li>
                </ul>
                <span id="footnote_eval">
                *2: Note that Graphics Library and Video Codecs Library Evaluation Version have a limitation that system stops running after around 10 hours.<br>
                If you would like to use unristricted version, please build AI SDK with Graphics Library Unristrictd Version and Video Codecs Library Unristricted Version according to <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk.md %}" role="button">How to Build AI SDK</a>.<br>
                </span>
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
