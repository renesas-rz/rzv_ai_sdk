---
layout: default
---
<!-- Title -->
<div class="container">
    <div class="row">
        <div class="top col-12">
            RZ/V2H AI SDK Configuration
        </div>
    </div>
</div>

<br>
<br>
<!-- Brief Explanation -->
This page explains the details of RZ/V2H AI SDK configurations.
<br>
To see the overview of RZ/V2H AI SDK, see <a href="{{ site.url }}{{ site.baseurl }}{% link ai-sdk.md %}">RZ/V AI SDK Overview page</a>.

<!-- Contents -->
<div class="container">
    <div class="row">
        <div class="col-12">
            <h5>
                <b>
                    Target Version: 4.00
                </b>
            </h5>
        </div>
        <div class="col-12">
            <h3 id="v2h-index">
                Index
            </h3>
            <ul>
                <li>
                    <a href="#v2h-component">
                        Linux Components
                    </a>
                </li>
                <li>
                    <a href="#v2h-driver">
                        Drivers
                    </a>
                </li>
                <li>
                    <a href="#v2h-limit">
                        Limitation
                    </a>
                </li>
            </ul>
        </div>
        <br>
        <div class="col-12">
            <h3 id="v2h-component">
                Linux Components
            </h3>
            The Linux components which are commonly used in RZ/V2H AI SDK is shown below.
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
                        Yocto version: 3.1.26 (Dunfell)
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
                            This is used for H.264 encoding.
                        </h6>
                    </td>
                </tr>
            </table>
            Other linux components installed to the root filesystem are listed in the below manifest file.
            <br>
            <ul>
                <li>
                    <code>"references/core-image-weston-rzv2h-evk-ver1.manifest"</code> in RZ/V2H AI SDK.
                </li>
            </ul>
        </div>
        <div class="col-12">
            <h3 id="v2h-driver">
                Drivers
            </h3>
            Following table shows the list of drivers. 
            <!-- UNCOMMENT following for v5.00 release. -->
            <!-- 
            <div class="note">
                <span class="note-title">Note</span>
                <span class="text-info">&#10004;</span> shows newly supported drivers.
                <br>
            </div> -->
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
                            Supports 1.1GHz, 1.5GHz, 1.6GHz and 1.7GHz.
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
                            <!-- Not supported-->
                        </td>                        <td>
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td>                    <!-- Item -->
                            Camera Input
                        </td>
                        <td>                    <!-- IP -->
                            MIPI-CSI/4lane x4
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
                            MIPI-DSI/4lane x1
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
                        <td>&#10004;<br>Encoder only</td>
                        <td rowspan="2">
                            Has released as an indivisual package
                            work for AI SDK v4.00 (codec H.264/H.265).<br>
                            See <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk_v2h.md %}#A3">How to Build RZ/V2H AI SDK Appendix 3</a>.
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Video Codec -->
                        <td>                    <!-- IP -->
                            H.265
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td rowspan="3">         <!-- Item -->
                            Audio
                        </td>
                        <td>                    <!-- IP -->
                            SSIF-2 TDM x8
                        </td>
                        <td>                    <!-- Support -->
                            <!-- Not supported-->
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Audio -->
                        <td>                    <!-- IP -->
                            SPDIF x3
                        </td>
                        <td>                    <!-- Support -->
                            <!-- Not supported-->
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
                            <!-- Not supported-->
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td rowspan="4">         <!-- Item -->
                            Timers
                        </td>
                        <td>                    <!-- IP -->
                            OSTM/6ch
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
                            WDT/4ch
                        </td>
                        <td>                    <!-- Support -->
                            <!-- Not supported-->
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
                            <!-- Not supported-->
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
                            ADC 12bitx8
                        </td>
                        <td>                    <!-- Support -->
                            <!-- Not supported-->
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
                            <!-- Not supported-->
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                        <td rowspan="15">         <!-- Item -->
                            Connectivity
                        </td>
                        <td>                    <!-- IP -->
                            USB3(Gen2x1) hostx2
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
                            USB2.0 host/func x1 host x1
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
                            SDHI(UHS-I)
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
                        <td>N/A</td>
                        <td>The board does not support eMMC.</td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            Gb Ether x2
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
                            PCIe Gen.3 4Lane x1 or 2Lane x2 RC
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
                            PCIe Gen.3 4Lane x1 or 2Lane x2 EP
                        </td>
                        <td>N/A</td>
                        <td>The board does not support PCIe EP.</td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            CANFD
                        </td>
                        <td>                    <!-- Support -->
                            <!-- Not supported-->
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            RSCI-2 x10
                        </td>
                        <td>                    <!-- Support -->
                            <!-- Not supported-->
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            SCIF x1
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
                            I2C x9
                        </td>
                        <td>                    <!-- Support -->
                            <!-- Not supported-->
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            I3C x1
                        </td>
                        <td>                    <!-- Support -->
                            <!-- Not supported-->
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : Connectivity-->
                        <td>                    <!-- IP -->
                            IRQ
                        </td>
                        <td>                    <!-- Support -->
                            <!-- Not supported-->
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
                            <!-- Not supported-->
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
                            <!-- Not supported-->
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
                            <!-- Not supported-->
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                    <tr>
                                                <!-- Item : System -->
                        <td>                    <!-- IP -->
                            DMAC/80ch (16ch/unit * 5unit)
                        </td>
                        <td>                    <!-- Support -->
                            <!-- Not supported-->
                        </td>
                        <td>                    <!-- Remarks -->
                            <!-- Empty -->
                        </td>
                    </tr>
                </table>
            </h6>
            <br>
        </div>
        <div class="col-12">
            <h3 id="v2h-limit">
                Limitations
            </h3>
            Following functionalities are not supported in RZ/V2H AI SDK v4.00.
            <br>
            <br>
            <ul>
                <li>
                    Reboot command *related to WDT in <a href="#v2h-driver">Driver list</a>
                </li>
                <li>
                    CPU 1.8GHz
                </li>
                <li>
                    CPU Shutdown
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