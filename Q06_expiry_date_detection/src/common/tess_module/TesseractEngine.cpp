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
* File Name    : TesseractEngine.cpp
* Version      : v1.00
* Description  : RZ/V2L AI SDK Sample Application: Expiry Date Extraction
***********************************************************************************************************************/

/*****************************************
* Includes
******************************************/
#include "TesseractEngine.h"

#define PAGE_SEGMENT_MODE  (7)

std::mutex TesseractEngine::engineMutex;

/**
 * @brief Construct a new Tesseract Engine:: Tesseract Engine object
 * 
 */
TesseractEngine::TesseractEngine() {

    /* Initialized tesseract with lang: eng, OCR engine: default */

    // tesseract::PageSegMode::PSM_SINGLE_LINE

    if (tessEngine.Init(NULL, "eng", tesseract::OEM_DEFAULT)) {
        printf("Failed to initialize");
    } else {
        printf("Tesseract initialized \n");
        tessEngine.SetPageSegMode(static_cast<tesseract::PageSegMode>(PAGE_SEGMENT_MODE));

        
    }

    
}

/**
 * @brief Get the instance of the singleton class
 * 
 * @return TesseractEngine& 
 */
TesseractEngine& TesseractEngine::getInstance() {
    static TesseractEngine instance;
    return instance;
}

/**
 * @brief Return the tesseract engine 
 * 
 * @return tesseract::TessBaseAPI& 
 */
tesseract::TessBaseAPI& TesseractEngine::getEngine() {
    return tessEngine;
}

/**
 * @brief clear the tesseract engine
 * 
 */
void TesseractEngine::clear() {
    tessEngine.Clear();
}

/**
 * @brief close the tesseract engine
 * 
 */
void TesseractEngine::end() {
    tessEngine.End();
}

