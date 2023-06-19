#ifndef UTILS_H
#define UTILS_H
#include "../define.h"
using namespace std; 

float float16_to_float32(uint16_t a);
vector<string> load_label_file(string label_file_name);
double sigmoid(double x);
int32_t yolo_index(uint8_t n, int32_t offs, int32_t channel);
int32_t yolo_offset(uint8_t n, int32_t b, int32_t y, int32_t x);

#endif