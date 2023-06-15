#pragma once

#include <tesseract/baseapi.h>
#include <mutex>

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

