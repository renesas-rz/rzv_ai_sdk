#ifndef DEFINE_MACRO_H
#define DEFINE_MACRO_H

/*Image:: Text information to be drawn on image*/
#define CHAR_SCALE_LARGE            (0.8)
#define CHAR_SCALE_SMALL            (0.7)
#define CHAR_SCALE_XS               (0.3)
#define CHAR_THICKNESS              (1)
#define LINE_HEIGHT                 (30) /*in pixel*/
#define LINE_HEIGHT_OFFSET          (20) /*in pixel*/
#define WHITE_DATA                  (0xFFFFFFu) /* in RGB */
#define CV_WHITE                    cv::Scalar(255, 255, 255)
#define CV_BLACK                    cv::Scalar(0, 0, 0)
#define CV_GREEN                    cv::Scalar(0, 255, 0)
#define CV_RED                      cv::Scalar(0, 0, 255)
#define CV_FONT                     cv::FONT_HERSHEY_SIMPLEX

/*DRP-AI Input image information*/
#define IMAGE_WIDTH                 (640)
#define IMAGE_HEIGHT                (480)
#define DRPAI_IN_WIDTH              (IMAGE_WIDTH)
#define DRPAI_IN_HEIGHT             (IMAGE_HEIGHT)
/*Total Display out*/
#define DISP_OUTPUT_WIDTH          (1280)
#define DISP_OUTPUT_HEIGHT         (720)
/*Image display out*/
#define IMAGE_OUTPUT_WIDTH          (960)
#define IMAGE_OUTPUT_HEIGHT         (720)

/*Display out params*/
#define USER_KEY_HIT
#define WAIT_TIME                   (10000) /*in miliseconds */ 

#endif