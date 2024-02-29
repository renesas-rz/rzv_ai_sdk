---
layout: default
---
<script type="text/javascript" src="http://code.jquery.com/jquery-3.7.0.min.js"></script>
<style>
  /**
   * This <style> tag is used to hide some rows of the table in the "Hardware Preparation" section.
   * This style applies only to this demo.md file, so do not put it in assets/css/style.scss file.
   */
  .forV2LDemo{
    display:none;
  }
</style>
<div class="container">
    <div class="row">
        <div class="top col-12">
How to Re-train AI model
        </div>
    </div>
</div>
<br>
<br>
<h5>
  This page explains how to re-train the AI model of AI Applications using <b>RZ/V AI Transfer Learning Tool</b>.
  <br><br>
  Supported version: <b>RZ/V2L AI Applications v2.10</b><br>
</h5>

<br>

<h3 id="intro">Introduction</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      RZ/V AI Transfer Learning Tool can re-train AI model used in AI Applications with different datasets.
    </div>
    <div class="col-12 text-center">
      <a href="img/tlt_overview.svg" data-lightbox="group"><img src="img/tlt_overview.svg" alt="RZ/V TLT overview"></a><br>
    </div>
  </div>
</div>

<br>

<h3 id="obtain">Obtain RZ/V AI Transfer Learning Tool</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      RZ/V AI Transfer Learning Tool is recommended to be linked with e<sup>2</sup> studio for RZ Family.<br>
      To download and install the tool, see <a href="{{ site.url }}{{ site.baseurl }}{% link ainavi_quick_start_guide.md %}">AI Navigator Quick Start Guide</a>.
    </div>
  </div>
</div>

<br>

<h3 id="restriction">Restrictions</h3>
<div class="container">
  <div class="row">
    <div class="col-12">
      RZ/V AI Transfer Learning Tool supports the following Functions of AI Applications.<br>
      <ul>
        <li>
          Q01_footfall_counter
        </li>
        <li>
          Q03_smart_parking
        </li>
        <li>
          Q04_fish_classification
        </li>
        <li>
          Q06_expiry_date_detection
        </li>
        <li>
          Q07_plant_disease_classification
        </li>
        <li>
          Q08_object_counter
        </li>
        <li>
          Q09_crack_segmentation
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
          <a class="btn btn-secondary square-button" href="{{ site.url }}{{ site.baseurl }}{% link index.md %}" role="button">
              Back to Home >
          </a>
      </div>
  </div>
</div>
