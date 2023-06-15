#ifndef IMG_PROCESSING_H
#define IMG_PROCESSING_H

#include <opencv2/opencv.hpp>
#include "../define.h"

cv::Mat get_crop_gray(cv::Mat& frame, int32_t x_center, int32_t y_center, int32_t width, int32_t height);
cv::Mat resize_gray_image(const cv::Mat &input_img, int32_t resize_height);
cv::Mat processImage(const cv::Mat &inputImg, int resizeHeight, bool gray_rqd);
cv::Mat hwc2chw(const cv::Mat &image);

#endif