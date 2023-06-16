#include "TesseractEngine.h"

std::mutex TesseractEngine::engineMutex;

TesseractEngine::TesseractEngine() {


    if (tessEngine.Init(NULL, "eng", tesseract::OEM_DEFAULT)) {
        printf("Failed to initialize");
    } else {

       // tessEngine.SetPageSegMode(tesseract::PageSegMode::PSM_SINGLE_LINE);
        // tessEngine.SetPageSegMode(tesseract::PageSegMode::PSM_SINGLE_CHAR);
        printf("Tesseract initialized \n");
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
