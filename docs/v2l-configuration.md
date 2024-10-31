---
layout: default
---
<!-- Title -->
<div class="container">
    <div class="row">
        <div class="top col-12">
            RZ/V2L AI SDK Configuration
        </div>
    </div>
</div>

<br>
<br>
<!-- Brief Explanation -->
This page explains the details of RZ/V2L AI SDK configurations.
<br>
To see the overview of RZ/V2L AI SDK, see <a href="{{ site.url }}{{ site.baseurl }}{% link ai-sdk.md %}">RZ/V AI SDK Overview page</a>.

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
        <!-- Reference to each release note -->
        <div class="note">
            <span class="note-title">Note</span>
            To see Linux driver information and more, please refer to each release note of package listed in <a href="{{ site.url }}{{ site.baseurl }}{% link ai-sdk.md %}#v2l-overview">RZ/V2L AI SDK Specification: Overview</a>.<br>
        </div>
        <div class="col-12">
            <h3 id="v2l-index">
                Index
            </h3>
            <ul>
                <li>
                    <a href="#v2l-component">
                        Linux Components
                    </a>
                </li>
                <li>
                    <a href="#v2l-limit">
                        Limitation
                    </a>
                </li>
            </ul>
        </div>
        <br>
        <div class="col-12">
            <h3 id="v2l-component">
                Linux Components
            </h3>
            The Linux components which are commonly used in RZ/V2L AI SDK is shown below.
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
                        <br>
                        Kernel version: 5.10.201-cip41
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
                    <td rowspan="2">     <!-- Component -->
                        OpenCL
                    </td>
                    <td>                <!-- Version -->
                        1.1, 1.2, 2.0 Full Profile
                    </td>
                    <td>                <!-- Explanation -->
                        <!-- Empty -->
                    </td>
                </tr>
                <tr>
                                        <!-- Component: OpenCL -->
                    <td>                <!-- Version -->
                        3.0 Full Profile
                    </td>
                    <td>                <!-- Explanation -->
                        <h6 class="mb-1">
                            This is not guaranteed to be 
                            backwards compatible with the 
                            previous versions of OpenCL.
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
                            This is used for H.264 decoding and encoding.
                        </h6>
                    </td>
                </tr>
            </table>
            Other linux components installed to the root filesystem are listed in the below manifest file.
            <br>
            <ul>
                <li>
                    <code>references/core-image-weston-smarc-rzv2l.manifest</code> in RZ/V2L AI SDK.
                </li>
            </ul>
        </div>
        <div class="col-12">
            <h3 id="v2l-limit">
                Limitations
            </h3>
            RZ/V2L AI SDK Source Code v5.00 has the following limitation.
            <br>
            <br>
            <ul>
                <li>
                    eSD boot cannot be performed using the WIC image file generated in <a href="{{ site.url }}{{ site.baseurl }}{% link howto_build_aisdk.md %}">How to build RZ/V2L AI SDK source code</a>.
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
