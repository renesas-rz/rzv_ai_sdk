#include "image_processing.h"

/**
 * @brief Get the cropped gray object
 * 
 * @param frame 
 * @param x_center 
 * @param y_center 
 * @param width 
 * @param height 
 * @return cv::Mat 
 */
cv::Mat get_crop_gray(cv::Mat& frame, int32_t x_center, int32_t y_center, int32_t width, int32_t height)
{
    
    /* xmin, ymin extraction and stretching */
    int32_t x_min = x_center - round(width / 2.) - CROP_IMG_STRETCH;
    int32_t y_min = y_center - round(height / 2.) - CROP_IMG_STRETCH;

    width = width + (CROP_IMG_STRETCH)*2; 
    height = height + (CROP_IMG_STRETCH)*2; 

    /* Check the rectangle box is in the image range */
    x_min = x_min < 0 ? 0 : x_min;
    y_min = y_min < 0 ? 0 : y_min;
    width = x_min + width  < (DRPAI_IN_WIDTH ) ? width   : DRPAI_IN_WIDTH ;
    height = y_min + height < (DRPAI_IN_HEIGHT ) ? height : DRPAI_IN_HEIGHT;

    /*Define the region of interest (ROI) using a rectangle */
    cv::Rect roi(x_min, y_min, width, height);

    /*Extract the cropped region from the color image */
    cv::Mat cropped_image = frame(roi);

    /*Convert BGRA image to grayscale */
    cv::Mat grayscale_image;
    cv::cvtColor(cropped_image, grayscale_image, cv::COLOR_BGRA2GRAY);

    return grayscale_image;
}

/**
 * @brief Resize the image with aspect ratio 
 * 
 * @param input_img 
 * @param resize_height 
 * @return cv::Mat 
 */
cv::Mat resize_gray_image(const cv::Mat &input_img, int32_t resize_height)
{
    cv::Mat resized_img;

    // Resize to specified height while maintaining aspect ratio
    if (input_img.rows < resize_height)
    {

        double aspect_ratio = (double)input_img.cols / (double)input_img.rows;
        int resize_width = (int)(resize_height * aspect_ratio);
        cv::resize(input_img, resized_img, cv::Size(resize_width, resize_height), 0, 0, cv::INTER_CUBIC);

        return resized_img;
    }
    else
    {
        return input_img;
    }
}

/**
 * @brief Convert HWC format to CHW 
 * 
 * @param image 
 * @return cv::Mat 
 */
cv::Mat hwc2chw(const cv::Mat &image)
{
    std::vector<cv::Mat> rgb_images;
    cv::split(image, rgb_images);
    cv::Mat m_flat_r = rgb_images[0].reshape(1, 1);
    cv::Mat m_flat_g = rgb_images[1].reshape(1, 1);
    cv::Mat m_flat_b = rgb_images[2].reshape(1, 1);
    cv::Mat matArray[] = {m_flat_r, m_flat_g, m_flat_b};
    cv::Mat flat_image;
    cv::hconcat(matArray, 3, flat_image);
    return flat_image;
}

/**
 * @brief Image-Processing 
 * Currently not used 
 * 
 * @param inputImg 
 * @param resizeHeight 
 * @param gray_rqd 
 * @return cv::Mat 
 */
cv::Mat processImage(const cv::Mat &inputImg, int resizeHeight, bool gray_rqd)
{
    cv::Mat grayImg, resizedImg, claheThreshImg, filteredImg, thresholdImg;

    // Convert to grayscale
    if (gray_rqd)
    {
        cv::cvtColor(inputImg, grayImg, cv::COLOR_BGR2GRAY);
    }
    else
    {
        grayImg = inputImg;
    }

    if (inputImg.rows < resizeHeight)
    {
        // Resize to specified height while maintaining aspect ratio
        double aspectRatio = (double)inputImg.cols / (double)inputImg.rows;
        int resizeWidth = (int)(resizeHeight * aspectRatio);
        cv::resize(grayImg, resizedImg, cv::Size(resizeWidth, resizeHeight), 0, 0, cv::INTER_CUBIC);
    }
    else
    {
        resizedImg = grayImg;
    }

    // Apply CLAHE (Adaptive Histogram Equalzn)to enhance contrast
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    clahe->setClipLimit(1);
    clahe->setTilesGridSize(cv::Size(4, 2));
    clahe->apply(resizedImg, claheThreshImg);

    // Apply median blur with filter size 3
    cv::medianBlur(claheThreshImg, filteredImg, 3);

    /* Apply adaptive threshold */
    cv::adaptiveThreshold(filteredImg, thresholdImg, 255,
                          cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, resizeHeight - 1, 7);


    return thresholdImg;

}