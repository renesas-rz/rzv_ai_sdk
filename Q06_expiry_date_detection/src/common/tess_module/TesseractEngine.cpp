#include "TesseractEngine.h"

#define PAGE_SEGMENT_MODE  (7)

std::mutex TesseractEngine::engineMutex;

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

TesseractEngine& TesseractEngine::getInstance() {
    static TesseractEngine instance;
    return instance;
}

tesseract::TessBaseAPI& TesseractEngine::getEngine() {
    return tessEngine;
}

void TesseractEngine::clear() {
    tessEngine.Clear();
}

void TesseractEngine::end() {
    tessEngine.End();
}

