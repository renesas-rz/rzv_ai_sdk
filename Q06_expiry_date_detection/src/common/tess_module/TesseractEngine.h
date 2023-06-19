#pragma once
#ifndef TESSERACT_ENGINE_H
#define TTESSERACT_ENGINE_H


#include <tesseract/baseapi.h>
#include "../define.h"

class TesseractEngine {
    tesseract::TessBaseAPI tessEngine;
    static std::mutex engineMutex;

    TesseractEngine();

public:
    static TesseractEngine& getInstance();
    tesseract::TessBaseAPI& getEngine();
    void clear();
    void end();

    // Delete copy constructor and assignment operator to prevent copying of the class instance
    TesseractEngine(const TesseractEngine&) = delete;
    TesseractEngine& operator=(const TesseractEngine&) = delete;
};

#endif
