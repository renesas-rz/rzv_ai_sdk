/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : tvm_drpai_yolo.cpp
 * Version      : 1.0
 * Description  : RZ/V2L DRP-AI TVM[*1] Sample Application for USB Camera HTTP version
 *                *1 DRP-AI TVM is powered by EdgeCortix MERA(TM) Compiler Framework.
 ***********************************************************************************************************************/
/*****************************************
 * Includes
 ******************************************/
#include "opencv2/core.hpp"
#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "boost/program_options.hpp"
#include "tvm_drpai_yolo.h"
#include "boost/filesystem.hpp"
#include "utils.h"
#include "map"
#include "tracker.h"
#include "random"
#include "chrono"
#include "ctime"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace cv;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
Tracker tracker;
int total_count = 0;
int kmin;
float conf;
int crossing_count = 0;
int pointx1, pointy1, pointx2, pointy2, actual_count = 0;
long int start_time, end_time;
bool init = true;
set<int> unique_ids = {};
long int time_one;
long int infer_time_ms;
map<int, int> id_time;
set<int> unique_id_entrance = {};
map<int, int> location_history;
std::unordered_map<std::string, std::unordered_map<std::string, std::string>> ini_values;
std::vector<string> detection_object_vector;
std::vector<cv::Rect> bbox;
vector<cv::Point> polygon;
Mat bgra_image;

/**
 * @brief config_read
 * @details Read configuration from the config.ini file
 */
void config_read()
{
    /*Open config.ini file*/
    std::ifstream ini_file("config.ini");
    std::string line;
    std::string current_section;
    /*parsing ini file*/
    while (std::getline(ini_file, line))
    {
        auto comment_pos = line.find(";");
        if (comment_pos != std::string::npos)
        {
            line.erase(comment_pos);
        }
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        if (line.empty())
        {
            continue;
        }
        else if (line[0] == '[')
        {
            current_section = line.substr(1, line.size() - 2);
        }
        else
        {
            auto delimiter_pos = line.find("=");
            std::string key = line.substr(0, delimiter_pos);
            std::string value = line.substr(delimiter_pos + 1);
            ini_values[current_section][key] = value;
        }
    }
    return;
}
/**
 * @brief TVM_YOLO_DRPAI
 */
TVM_YOLO_DRPAI::TVM_YOLO_DRPAI(uint8_t id) : IRecognizeModel(0, TVM_MODEL_DIR_YOLOV3.data(), MODEL_NAME.data(), TVM_DRPAI_IN_WIDTH, TVM_DRPAI_IN_HEIGHT, TVM_DRPAI_IN_CHANNEL, TVM_MODEL_IN_W, TVM_MODEL_IN_H, TVM_MODEL_IN_C, id)
{
    preruntime.Load(pre_dir);
    /*Define pre-processing parameter*/
    in_param.pre_in_shape_w = TVM_DRPAI_IN_WIDTH;
    in_param.pre_in_shape_h = TVM_DRPAI_IN_HEIGHT;
    in_param.pre_in_format = INPUT_YUYV;
    in_param.resize_w = TVM_MODEL_IN_W;
    in_param.resize_h = TVM_MODEL_IN_H;
    in_param.resize_alg = ALG_BILINEAR;
    /*Compute normalize coefficient, cof_add/cof_mul for DRP-AI from mean/std */
    in_param.cof_add[0] = -255 * mean[0];
    in_param.cof_add[1] = -255 * mean[1];
    in_param.cof_add[2] = -255 * mean[2];
    in_param.cof_mul[0] = 1 / (stdev[0] * 255);
    in_param.cof_mul[1] = 1 / (stdev[1] * 255);
    in_param.cof_mul[2] = 1 / (stdev[2] * 255);
    /*Load label list for YOLOv3/TinyYOLOv3 */
    label_file_map = CommonFunc::load_label_file(LABEL_LIST.data());
    num_class = label_file_map.size();

    if (id == MODE_TVM_TINYYOLOV3_DRPAI)
    {
        model_dir = TVM_MODEL_DIR_TINYYOLOV3;
        std::cout << "DRP-AI TVM TinyYOLOv3 model" << std::endl;
        /* init num_grids*/
        num_grids = {13, 26};
        /*init num_inf_out*/
        num_inf_out = (num_class + 5) * YOLOV3_NUM_BB * num_grids[0] * num_grids[0] + (num_class + 5) * YOLOV3_NUM_BB * num_grids[1] * num_grids[1];
        num_out_layer = TINYYOLOV3_NUM_INF_OUT_LAYER;
        /* init anchors*/
        anchors =
            {
                10, 14,
                23, 27,
                37, 58,
                81, 82,
                135, 169,
                344, 319};
    }
    outBuffSize = num_inf_out;
    /*Initialize tracking/detection paramters*/
    config_read();
    /*set point 1*/
    pointx1 = stoi(ini_values["line"]["x1"]);
    pointy1 = stoi(ini_values["line"]["y1"]);
    /*set point 2*/
    pointx2 = stoi(ini_values["line"]["x2"]);
    pointy2 = stoi(ini_values["line"]["y2"]);
    /*set region of interest*/
    polygon = {
        Point(stoi(ini_values["region"]["x1"]), stoi(ini_values["region"]["y1"])),
        Point(stoi(ini_values["region"]["x2"]), stoi(ini_values["region"]["y2"])),
        Point(stoi(ini_values["region"]["x3"]), stoi(ini_values["region"]["y3"])),
        Point(stoi(ini_values["region"]["x4"]), stoi(ini_values["region"]["y4"]))};
    /*set confidence score*/
    conf = stof(ini_values["tracking"]["conf"]);
    /*set kmin hits for tracking */
    kmin = stoi(ini_values["tracking"]["kmin"]);
    /*objects to be tracked*/
    string detection_object_string = ini_values["tracking"]["objects"];
    stringstream detection_object_ss(detection_object_string);
    string item;
    while (std::getline(detection_object_ss, item, ','))
    {
        detection_object_vector.push_back(item);
    }
    cout << "*******************Tracking/Detection Parameters*******************" << endl;
    cout << "Selected objects to track\n";
    for (const auto &item : detection_object_vector)
        cout << item << endl;
    cout << "Confidence Score : " << conf << endl;
    cout << "KMin Hits : " << kmin << endl;
}

/**
 * @brief inf_pre_process
 * @details Run pre-processing.
 * @details For CPU input, use input_data for input data.
 * @details For DRP-AI input, use addr for input data stored address
 * @param input_data Input data pointer
 * @param width new input data width.
 * @param height new input data width.
 * @param addr Physical address of input data buffer
 * @param out output_buf Output data buffer pointer holder
 * @param out buf_size Output data buffer size holder
 * @return int32_t success:0 error: != 0
 */
int32_t TVM_YOLO_DRPAI::inf_pre_process(uint8_t *input_data, uint32_t width, uint32_t height, uint32_t addr, float **arg, uint32_t *buf_size)
{
    /*Update width and height*/
    if ((width != _capture_w) || (height != _capture_h))
    {
        _capture_w = width;
        _capture_h = height;
        in_param.pre_in_shape_w = _capture_w;
        in_param.pre_in_shape_h = _capture_h;
    }
    cv::Mat yuyv_image(height, width, CV_8UC2, (void *)input_data);
    cv::cvtColor(yuyv_image, bgra_image, cv::COLOR_YUV2BGRA_YUYV);
    cv::line(bgra_image, Point(pointx1, pointy1), Point(pointx2, pointy2), Scalar(0, 0, 255), 4);
    cv::putText(bgra_image, "human count: " + to_string(actual_count), Point(30, 30), FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 0, 0), 2);
    cv::putText(bgra_image, "person in region: " + to_string(crossing_count), Point(30, 50), FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 0, 0), 2);
    cv::putText(bgra_image, "FPS:" + to_string(1000 / infer_time_ms), Point(540, 30), FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 0, 0), 2);
    cv::polylines(bgra_image, polygon, true, Scalar(0, 255, 0), 2);
    cv::imshow("Object Tracker", bgra_image);
    pre_process_drpai(addr, arg, buf_size);
    return 0;
}
/**
 * @brief inf_post_process
 * @details Run post-processing
 * @param arg Inference output data pointer
 * @return int32_t success:0 error: != 0
 */
int32_t TVM_YOLO_DRPAI::inf_post_process(float *arg)
{
    postproc_data.clear();
    post_process(postproc_data, arg);
    return 0;
}
/**
 * @brief print_result
 * @details Print AI result on console
 * @return int32_t success:0 error: != 0
 */
int32_t TVM_YOLO_DRPAI::print_result()
{
    ObjectDetectionFunc::print_boxes(postproc_data, label_file_map);
    return 0;
}
/**
 * @brief check_above_or_below
 * @details check the given point is above or below the line,
 * @details added a small value of 1e-8 to avoid division by zero
 * @param x x coordinate of the point
 * @param y y coordinate of the point
 * @return int location of the point w.r.t the line
 */
int check_above_or_below(int x, int y)
{
    double m = (pointy2 - pointy1) / ((pointx2 - pointx1) + 0.00000006);
    double yline = m * (x - pointx1) + pointy1;
    if (y > yline)
        return 1;
    else
        return 0;
}
/**
 * @brief check_inside_rectangle
 * @details check the given point is inside the region difined using the polygon,
 * @param x x coordinate of the point
 * @param y y coordinate of the point
 * @return bool location of the point w.r.t the line
 */
bool check_inside_rectangle(int x, int y)
{
    int result = pointPolygonTest(polygon, Point(x, y), false);
    if (result == 1)
        return 1;
    else
        return 0;
}
/**
 * @brief check_inside_rectangle
 * @details check the given point is inside the region difined using the polygon,
 * @param x x coordinate of the point
 * @param y y coordinate of the point
 * @return bool location of the point w.r.t the line
 */
shared_ptr<PredictNotifyBase> TVM_YOLO_DRPAI::track()
{
    /*timer for fps and person time calculation*/
    if (init)
    {
        init = false;
        end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        time_one = end_time - start_time;
        start_time = end_time;
    }
    else
    {
        end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        infer_time_ms = end_time - start_time;
        start_time = end_time;
    }
    bbox.clear();
    /*filter detection based on confidence score and objects selected*/
    ObjectDetection *ret = new ObjectDetection();
    for (detection det : postproc_data)
    {
        bbox_t dat;
        if (det.prob < conf)
            continue;
        dat.name = label_file_map[det.c].c_str();

        if (count(detection_object_vector.begin(), detection_object_vector.end(), dat.name) <= 0)
            continue;
        dat.X = (int32_t)(det.bbox.x - (det.bbox.w / 2));
        dat.Y = (int32_t)(det.bbox.y - (det.bbox.h / 2));
        dat.W = (int32_t)det.bbox.w;
        dat.H = (int32_t)det.bbox.h;
        dat.pred = det.prob * 100.0;
        bbox.emplace_back(dat.X, dat.Y, dat.W, dat.H);
    }
    /*run the tracker with detected bbox*/
    tracker.Run(bbox);
    const auto tracks = tracker.GetTracks();
    crossing_count = 0;
    /* result tracks */
    for (auto &trk : tracks)
    {
        bbox_t dat;
        const auto &bbox_trk = trk.second.GetStateAsBbox();
        /*kmin hit and kmaxcoast cycle*/
        if (trk.second.coast_cycles_ < kMaxCoastCycles && trk.second.hit_streak_ >= kmin)
        {
            if (id_time.find(trk.first) == id_time.end())
                dat.name = "id : " + to_string(trk.first);
            dat.name = "id : " + to_string(trk.first) + "   time : " + to_string(id_time[trk.first] / 1000);
            dat.X = bbox_trk.tl().x;
            dat.Y = bbox_trk.tl().y;
            int s = check_above_or_below((int)(dat.X + dat.W / 2), (int)(dat.Y + dat.H));
            const bool is_in = unique_ids.find(trk.first) != unique_ids.end();
            if (s)
            {
                if (location_history.find(trk.first) == location_history.end())
                    location_history[trk.first] = s;
                else
                {
                    if (!location_history[trk.first])
                    {
                        actual_count++;
                    }
                    location_history[trk.first] = s;
                }
            }
            else
            {
                if (location_history.find(trk.first) == location_history.end())
                    location_history[trk.first] = s;
                else
                {
                    if (location_history[trk.first])
                    {
                        actual_count--;
                    }
                    location_history[trk.first] = s;
                }
            }
            bool is_in_rect = check_inside_rectangle((int)(dat.X + dat.W / 2), (int)(dat.Y + dat.H));
            if (is_in_rect)
            {
                crossing_count++;
                if (id_time.find(trk.first) == id_time.end())
                {
                    id_time[trk.first] = infer_time_ms;
                }
                else
                {
                    id_time[trk.first] += infer_time_ms;
                }
            }
            dat.W = bbox_trk.width;
            dat.H = bbox_trk.height;
            ret->predict.push_back(dat);
            cv::Rect rect(dat.X, dat.Y, dat.W, dat.H);
            for (const auto &x : id_time)
            {
                std::cout << "tracking id : " << x.first << " n_frames detected : " << x.second << "\n";
            }
            if (crossing_count < 0)
            {
                crossing_count = 0;
            }
            cv::rectangle(bgra_image, rect, cv::Scalar(0, 255, 0));
            cv::putText(bgra_image, dat.name, Point(dat.X - 10, dat.Y), FONT_HERSHEY_DUPLEX, 1.0, Scalar(255, 0, 0), 2);
        }
    }
    cv::imshow("Object Tracker", bgra_image);
    cv::waitKey(1);
    return shared_ptr<PredictNotifyBase>(move(ret));
}
/**
 * @brief pre_process_drpai
 * @details implementation pre process using Pre-processing Runtime.
 * @param addr Physical address of input data buffer
 * @param out output_buf Output data buffer pointer holder
 * @param out buf_size Output data buffer size holder
 * @return int8_t success:0 error: != 0
 */
int8_t TVM_YOLO_DRPAI::pre_process_drpai(uint32_t addr, float **output_buf, uint32_t *buf_size)
{
    in_param.pre_in_addr = (uintptr_t)addr;
    /*Run pre-processing*/
    preruntime.Pre(&in_param, output_buf, buf_size);
    start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return 0;
}
/**
 * @brief post_process
 * @details implementation post process
 * @param det reference to store bounding box
 * @param floatarr DRP-AI result
 * @return int8_t success:0 error: != 0
 */
int8_t TVM_YOLO_DRPAI::post_process(std::vector<detection> &det, float *floatarr)
{
    /* Following variables are required for correct_yolo/region_boxes in Darknet implementation*/
    /* Note: This implementation refers to the "darknet detector test" */
    float new_w, new_h;
    float correct_w = 1.;
    float correct_h = 1.;
    if ((float)(TVM_MODEL_IN_W / correct_w) < (float)(TVM_MODEL_IN_H / correct_h))
    {
        new_w = (float)TVM_MODEL_IN_W;
        new_h = correct_h * TVM_MODEL_IN_W / correct_w;
    }
    else
    {
        new_w = correct_w * TVM_MODEL_IN_H / correct_h;
        new_h = TVM_MODEL_IN_H;
    }
    int32_t n = 0;
    int32_t b = 0;
    int32_t y = 0;
    int32_t x = 0;
    int32_t offs = 0;
    int32_t i = 0;
    float tx = 0;
    float ty = 0;
    float tw = 0;
    float th = 0;
    float tc = 0;
    float center_x = 0;
    float center_y = 0;
    float box_w = 0;
    float box_h = 0;
    float objectness = 0;
    uint8_t num_grid = 0;
    uint8_t anchor_offset = 0;
    float classes[num_class];
    float max_pred = 0;
    int32_t pred_class = -1;
    float probability = 0;
    detection d;
    /*Number of bounding box for each grid. Default is YOLOv3 values.*/
    uint8_t num_bb = YOLOV3_NUM_BB;
    /*If YOLOv2/TinyYOLOv2, update the number of bounding box for each grid. */
    if (_id == MODE_TVM_YOLOV2_DRPAI || _id == MODE_TVM_TINYYOLOV2_DRPAI)
    {
        num_bb = YOLOV2_NUM_BB;
    }
    for (n = 0; n < num_out_layer; n++)
    {
        num_grid = num_grids[n];
        anchor_offset = 2 * num_bb * (num_out_layer - (n + 1));
        for (b = 0; b < num_bb; b++)
        {
            for (y = 0; y < num_grid; y++)
            {
                for (x = 0; x < num_grid; x++)
                {
                    offs = ObjectDetectionFunc::yolo_offset(n, b, y, x, num_grids.data(), num_bb, label_file_map.size());
                    tx = floatarr[offs];
                    ty = floatarr[ObjectDetectionFunc::yolo_index(num_grid, offs, 1)];
                    tw = floatarr[ObjectDetectionFunc::yolo_index(num_grid, offs, 2)];
                    th = floatarr[ObjectDetectionFunc::yolo_index(num_grid, offs, 3)];
                    tc = floatarr[ObjectDetectionFunc::yolo_index(num_grid, offs, 4)];
                    /* Compute the bounding box */
                    /*get_yolo_box/get_region_box in paper implementation*/
                    center_x = ((float)x + CommonFunc::sigmoid(tx)) / (float)num_grid;
                    center_y = ((float)y + CommonFunc::sigmoid(ty)) / (float)num_grid;
                    if (_id == MODE_TVM_YOLOV3_DRPAI || _id == MODE_TVM_TINYYOLOV3_DRPAI)
                    {
                        box_w = (float)exp(tw) * anchors[anchor_offset + 2 * b + 0] / (float)TVM_MODEL_IN_W;
                        box_h = (float)exp(th) * anchors[anchor_offset + 2 * b + 1] / (float)TVM_MODEL_IN_W;
                    }
                    else // For YOLOv2/TinyYOLOv2
                    {
                        box_w = (float)exp(tw) * anchors[anchor_offset + 2 * b + 0] / (float)num_grid;
                        box_h = (float)exp(th) * anchors[anchor_offset + 2 * b + 1] / (float)num_grid;
                    }
                    /* Adjustment for VGA size */
                    /* correct_yolo/region_boxes */
                    center_x = (center_x - (TVM_MODEL_IN_W - new_w) / 2. / TVM_MODEL_IN_W) / ((float)new_w / TVM_MODEL_IN_W);
                    center_y = (center_y - (TVM_MODEL_IN_H - new_h) / 2. / TVM_MODEL_IN_H) / ((float)new_h / TVM_MODEL_IN_H);
                    box_w *= (float)(TVM_MODEL_IN_W / new_w);
                    box_h *= (float)(TVM_MODEL_IN_H / new_h);
                    center_x = round(center_x * TVM_DRPAI_IN_WIDTH);
                    center_y = round(center_y * TVM_DRPAI_IN_HEIGHT);
                    box_w = round(box_w * TVM_DRPAI_IN_WIDTH);
                    box_h = round(box_h * TVM_DRPAI_IN_HEIGHT);
                    objectness = CommonFunc::sigmoid(tc);
                    Box bb = {center_x, center_y, box_w, box_h};
                    /* Get the class prediction */
                    {
                        for (i = 0; i < num_class; i++)
                        {
                            if (_id == MODE_TVM_YOLOV3_DRPAI || _id == MODE_TVM_TINYYOLOV3_DRPAI)
                            {
                                classes[i] = CommonFunc::sigmoid(floatarr[ObjectDetectionFunc::yolo_index(num_grid, offs, 5 + i)]);
                            }
                            else // For YOLOv2/TinyYOLOv2
                            {
                                classes[i] = floatarr[ObjectDetectionFunc::yolo_index(num_grid, offs, 5 + i)];
                            }
                        }
                    }
                    if (_id == MODE_TVM_YOLOV2_DRPAI || _id == MODE_TVM_TINYYOLOV2_DRPAI)
                    {
                        CommonFunc::softmax(classes, num_class);
                    }
                    max_pred = 0;
                    pred_class = -1;
                    for (i = 0; i < num_class; i++)
                    {
                        if (classes[i] > max_pred)
                        {
                            pred_class = i;
                            max_pred = classes[i];
                        }
                    }
                    /* Store the result into the list if the probability is more than the threshold */
                    probability = max_pred * objectness;
                    if (probability > YOLO_TH_PROB)
                    {
                        d = {bb, pred_class, probability};
                        det.push_back(d);
                    }
                }
            }
        }
    }
    /* Non-Maximum Supression filter */
    filter_boxes_nms(det, det.size(), YOLO_TH_NMS);
    return 0;
}
