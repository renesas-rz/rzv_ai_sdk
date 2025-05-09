---
layout: default
---
<!-- Title -->
<div class="container">
    <div class="row">
        <div class="top col-12">
            RZ/V2N AI SDK Configuration
        </div>
    </div>
</div>

<br>
<br>
<!-- Brief Explanation -->
This page explains the details of RZ/V2N AI SDK configurations.
<br>
To see the overview of RZ/V2N AI SDK, see <a href="{{ site.url }}{{ site.baseurl }}{% link ai-sdk.md %}">RZ/V AI SDK Overview page</a>.

<!-- Contents -->
<div class="container">
    <div class="row">
        <div class="col-12">
            <h5>
                <b>
                    Target Version: 5.00
                </b>
            </h5>
        </div>
        <div class="col-12">
            <h3 id="v2n-index">
                Index
            </h3>
            <ul>
                <li>
                    <a href="#v2n-component">
                        Linux Components
                    </a>
                </li>
                <li>
                    <a href="#v2n-driver">
                        Drivers
                    </a>
                </li>
                <li>
                    <a href="#v2n-limit">
                        Limitation
                    </a>
                </li>
            </ul>
        </div>
        <br>
        <div class="col-12">
            <h3 id="v2n-component">
                Linux Components
            </h3>
            The Linux components which are commonly used in RZ/V2N AI SDK is shown below.
            <br>
            <br>
            <table class="gstable mt-1">
                <tr>
                    <th>
                        Component
                    </th>
                    <th>
                        Version
                    </th>
                    <th>
                        Explanation
                    </th>
                </tr>
                <tr>
                    <td>                <!-- Component -->
                        Yocto Linux
                    </td>
                    <td>                <!-- Version -->
                        Yocto version: 3.1.31 (Dunfell)
                        <a href="#footnote_v2n_linux_components">
                            <sup>
                                *1
                            </sup>
                        </a>
                        <br>
                        Kernel version: 5.10.145-cip17
                    </td>
                    <td>                <!-- Explanation -->
                        <!-- Empty -->
                    </td>
                </tr>
                <tr>
                    <td>                <!-- Component -->
                        OpenCV
                    </td>
                    <td>                <!-- Version -->
                        4.1.0
                    </td>
                    <td>                <!-- Explanation -->
                        <!-- Empty -->
                    </td>
                </tr>
                <tr>
                    <td rowspan="2">    <!-- Component -->
                        OpenCL
                    </td>
                    <td>                <!-- Version -->
                        1.1, 1.2, 2.0 Full Profile.
                    </td>
                    <td>                <!-- Explanation -->
                        <!-- Empty -->
                    </td>
                </tr>
                <tr>
                                        <!-- Component : OpenCL -->
                    <td>                <!-- Version -->
                        3.0 Full Profile
                    </td>
                    <td>                <!-- Explanation -->
                        <h6 class="mb-1">
                            This is not guaranteed to be backwards compatible with the previous versions of OpenCL.
                        </h6>
                    </td>
                </tr>
                <tr>
                    <td>                <!-- Component -->
                        OpenGLES
                    </td>
                    <td>                <!-- Version -->
                        1.1, 2.0, 3.0, 3.1 and 3.2
                    </td>
                    <td>                <!-- Explanation -->
                        <!-- Empty -->
                    </td>
                </tr>
                <tr>
                    <td>                <!-- Component -->
                        OpenMAX IL
                    </td>
                    <td>                <!-- Version -->
                        1.1
                    </td>
                    <td>                <!-- Explanation -->
                        <h6 class="mb-1">
                            This is used for H.264 encoding/decoding and H.265 encoding/decoding.
                        </h6>
                    </td>
                </tr>
            </table>
            Other linux components installed to the root filesystem are listed in the below manifest file.
            <br>
            <ul>
                <li>
                    <code>"references/core-image-weston-rzv2n-evk.manifest"</code> in RZ/V2N AI SDK.
                </li>
            </ul>
            <div class="note">
                <span class="note-title" id="footnote_v2n_linux_components">Note1</span>
                RZ/V2N AI SDK will transition to Yocto version 5.0 (Scarthgap) and Kernel 6.1 in June 2025.<br>
                After June 2025, RZ/V2N AI SDK Dunfell version will not be updated.<br>
            </div>
        </div>
        <div class="col-12">
            <h3 id="v2n-driver">
                Drivers
            </h3>
            Following table shows the list of drivers.<br>
            For more details, see <a href="https://www.renesas.com/document/mas/rzv2h-and-rzv2n-bsp-manual-set-rtk0ef0045z94001azj-v103zip" target="_blank" rel="noopener noreferrer">RZ/V2N BSP Manual Set</a> and <a href="https://www.renesas.com/rzv2n-evkit" target="_blank" rel="noopener noreferrer">RZ/V2N Evaluation Board Kit Hardware Manual</a>. 
            <!-- 
            <div class="note">
                <span class="note-title">Note</span>
                <span class="text-info">&#10004;</span> shows newly supported drivers.
                <br>
            </div>
             -->
            <!-- MEMO: For maintenance
                    When updating the version, follow the rules below
                    - For existing support      &#10004;
                    - For newly support         <span class="text-info">&#10004;</span>
             -->
            <h6>
                <table class="gstable mt-1">
                    <tr>
                        <th>
                            Items
                        </th>
                        <th>
                            IP
                        </th>
                        <th>
                            Support
                        </th>
                        <th>
                            Remarks
                        </th>
                    </tr>
                    <tr>
                        <td>                    <!-- Item -->
                            CPU
                        </td>
                        <td>                    <!-- IP -->
                            CPU/CA55
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            Supports 1.1GHz, 1.5GHz, 1.6GHz and 1.7GHz.<br>
                            If you use CA55 at 1.8GHz, you will need configuration at system startup.<br>
                            For configuration instructions, see <a href="https://www.renesas.com/software-tool/rzv-group-multi-os-package" target="_blank" rel="noopener noreferrer">RZ/V Multi-OS Package</a>.
                        </td>
                    </tr>
                    <tr>
                        <td>                    <!-- Item -->
                            External memory
                        </td>
                        <td>                    <!-- IP -->
                            LPDDR4
                        </td>
                        <td>                    <!-- IP -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td rowspan="3">
                            Graphics
                        </td>
                        <td>                    <!-- IP -->
                            3D GPU
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td>                    <!-- Item -->
                            LCD Controller
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td>                    <!-- Item -->
                            Image Scaling Unit
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>                        <td>
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td>                    <!-- Item -->
                            Camera Input
                        </td>
                        <td>                    <!-- IP -->
                            MIPI-CSI
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                            <!-- 
                                Memo: Do NOT write following statement since this only applies for Linux, which does not consider e-CAM camera.
                                "Operation verified with CoralCamera"
                             -->
                        </td>
                    </tr>
                    <tr>
                        <td>                    <!-- Item -->
                            Display Out
                        </td>
                        <td>                    <!-- IP -->
                            MIPI-DSI
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>
                        </td>
                    </tr>
                    <tr>
                        <td rowspan="2">         <!-- Item -->
                            Video Codec
                        </td>
                        <td>                    <!-- IP -->
                            H.264
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Video Codec -->
                        <td>                    <!-- IP -->
                            H.265
                        </td>
                        <td>                    <!-- Remarks -->
                            &#10004;
                        </td>
                        <td>
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td rowspan="3">         <!-- Item -->
                            Audio
                        </td>
                        <td>                    <!-- IP -->
                            SSIF-2 TDM
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Audio -->
                        <td>                    <!-- IP -->
                            SPDIF
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Audio -->
                        <td>                    <!-- IP -->
                            ASRC(Asynchronous sample rate conversion)
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td rowspan="6">         <!-- Item -->
                            Timers
                        </td>
                        <td>                    <!-- IP -->
                            SYC (SystemCounter)
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Timers-->
                        <td>                    <!-- IP -->
                            GPT
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Timers-->
                        <td>                    <!-- IP -->
                            RTC
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Timers-->
                        <td>                    <!-- IP -->
                            GTM
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Timers-->
                        <td>                    <!-- IP -->
                            CMTW
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Timers-->
                        <td>                    <!-- IP -->
                            WDT
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td rowspan="2">         <!-- Item -->
                            Analog
                        </td>
                        <td>                    <!-- IP -->
                            ADC
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Analog-->
                        <td>                    <!-- IP -->
                            TSU
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td rowspan="17">         <!-- Item -->
                            Connectivity
                        </td>
                        <td>                    <!-- IP -->
                            xSPI
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            SDIO
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            eMMC
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            USB3(Gen2x1)
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            USB2.0
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            Gb Ether
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            PCIe Gen.3 RC
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            PCIe Gen.3 EP
                        </td>
                        <td>N/A</td>
                        <td>The board does not support PCIe EP.</td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            IRQ
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            NMI
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            I3C
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            I2C
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            SCIF
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            RSCI-2
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            RSPI
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            CAN-FD
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            GPIO
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td rowspan="2">         <!-- Item -->
                            System
                        </td>
                        <td>                    <!-- IP -->
                            CPG
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : System -->
                        <td>                    <!-- IP -->
                            DMAC
                        </td>
                        <td>                    <!-- Support -->
                            &#10004;
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                </table>
            </h6>
            <br>
        </div>
        <!-- v2n limitations -->
        <div class="col-12">
            <h3 id="v2n-limit">
                Limitations
            </h3>
            RZ/V2N AI SDK v5.00 has the following limitations.
            <br>
            <br>
            <ul>
                <li>
                    When using DRP-AI, H.264/H.265 Decode, or OpenCV Accelerator, rebooting by command is not supported.<br>
                    To reboot, power off the board and then power on again.
                </li>
            </ul>
            <br>
        </div>
    </div>
<!-- Footer -->
    <div class="row">
        <div class="col-12" align="right">
            <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}" role="button">
                Back to Home >
            </a>
        </div>
    </div>
</div>
