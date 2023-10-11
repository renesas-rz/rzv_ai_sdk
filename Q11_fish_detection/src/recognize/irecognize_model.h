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
 * File Name    : irecognize_model.h
 * Version      : 1.0
 * Description  : RZ/V2L SDK AI Application: Fish detection.
 ***********************************************************************************************************************/

#pragma once
#ifndef IRECOGNIZE_MODEL_H
#define IRECOGNIZE_MODEL_H

/*****************************************
 * Includes
 ******************************************/
#include "../includes.h"
#include "../util/recognize_define.h"
#include "../util/box.h"

class IRecognizeModel
{
public:
    IRecognizeModel(string dir, string drpprefix, 
                    int32_t capW, int32_t capH, 
                    int32_t capC, uint8_t id) : model_dir(dir), model_name(drpprefix), 
                    _capture_w(capW), _capture_h(capH), _capture_c(capC), _id(id)
    {
        std::cout << "RecognizeModel created." << model_name << std::endl;
    }

    IRecognizeModel(int32_t outbuffsize, string dir, string drpprefix, 
                    int32_t capW, int32_t capH, int32_t capC, uint8_t id) : model_dir(dir), 
                    model_name(drpprefix), outBuffSize(outbuffsize), _capture_w(capW), 
                    _capture_h(capH), _capture_c(capC), _id(id)
    {
        std::cout << drpprefix << std::endl;
    }
    IRecognizeModel(int32_t outbuffsize, string dir, string drpprefix, 
                    int32_t capW, int32_t capH, int32_t capC, int32_t modelW, 
                    int32_t modelH, int32_t modelC, uint8_t id) : model_dir(dir), 
                    model_name(drpprefix), outBuffSize(outbuffsize), _capture_w(capW), 
                    _capture_h(capH), _capture_c(capC), _model_w(modelW), _model_h(modelH), 
                    _model_c(modelC), _id(id)
    {
        std::cout << drpprefix << std::endl;
    }
    virtual ~IRecognizeModel() {}
    virtual int32_t inf_pre_process(uint8_t *input_data, uint32_t width, uint32_t height, 
                                    uint32_t addr, float **arg, uint32_t *buf_size) { return 0; }
    virtual vector<detection> inf_post_process(float *arg){ return postproc_data; }
    virtual int32_t print_result() { return 0; }

    /* for recognize proc*/
    string model_dir;
    string model_name;
    int32_t outBuffSize;
    int32_t _capture_w;
    int32_t _capture_h;
    int32_t _capture_c;
    int32_t _model_w;
    int32_t _model_h;
    int32_t _model_c;
    uint8_t _id;
    /* Class labels to be classified */
    std::string config_file_path;
    std::string get_anchor;
    std::vector<std::string> label_file_map;

    float conf;
    string detection_object_string;
    /* Post-processing result */
    vector<detection> postproc_data;
};
#endif
