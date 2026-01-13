#ifndef DEFINE_MACRO_H
#define DEFINE_MACRO_H

/*****************************************
* includes
******************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <float.h>
#include <atomic>
#include <semaphore.h>
#include <math.h>
#include <fstream>
#include <sys/time.h>
#include <climits>
#include <mutex>
#include <condition_variable>
#include <set>
#include <linux/drpai.h>
#include <builtin_fp16.h>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"


/*****************************************
* Macro for YOLOX
******************************************/
/* Number of class to be detected */
#define NUM_CLASS                   (5)
#define YOLOX_MODEL_WIDTH           (640)
#define YOLOX_MODEL_HEIGHT          (640)

/* Thresholds */
#define TH_PROB                     (0.25f)
#define TH_NMS                      (0.5f)
const static std::string yolox_model_dir = "yolox_model";
static std::vector<std::string> label_file_map = {"center", "gauge", "max", "min", "tip"};

/*****************************************
* Macro for Unet
******************************************/
#define UNET_MODEL_WIDTH         (640)
#define UNET_MODEL_HEIGHT        (640)   
const static std::string unet_model_dir = "unet_model";

/*****************************************
* Macro for Application
******************************************/
/*DRP-AI memory area offset for model objects*/
/*Offset value depends on the size of memory area used by DRP-AI Pre-processing Runtime Object files*/
#define DRPAI_MEM_OFFSET            (0x10000000)

#define DEVIATION_THRESHOLD         (30)
#define YOLOX_IF_COUNT              (10)
#define UNET_IF_COUNT               (40)

#define WHITE                       cv::Scalar(255, 255, 255)
#define BLACK                       cv::Scalar(0, 0, 0)
#define BLUE                        cv::Scalar(255, 0, 0)
#define GREEN                       cv::Scalar(0, 255, 0)
#define RED                         cv::Scalar(0, 0, 255)
#define YELLOW                      cv::Scalar(0, 255, 255)

/*Camera Capture Image Information*/
#define CAM_IMAGE_WIDTH             (640)
#define CAM_IMAGE_HEIGHT            (480)

#define DISP_IMAGE_OUTPUT_WIDTH     (1480)
#define DISP_IMAGE_OUTPUT_HEIGHT    (1080)
#define DISP_OUTPUT_WIDTH           (1920)
#define DISP_OUTPUT_HEIGHT          (1080)

/*Waiting Time*/
#define WAIT_TIME                   (1000) /* microseconds */

/*Timer Related*/
#define CAPTURE_TIMEOUT             (20)  /* seconds */
#define AI_THREAD_TIMEOUT           (20)  /* seconds */
#define EXIT_THREAD_TIMEOUT         (10)  /* seconds */

/* DRPAI_FREQ is the frequency settings  */
/* for DRP-AI.                           */
/* Basically use the default values      */
#define DRPAI_FREQ                 (2)
/* DRPAI_FREQ can be set from 1 to 127   */
/* 1,2: 1GHz                             */
/* 3: 630MHz                             */
/* 4: 420MHz                             */
/* 5: 315MHz                             */
/* ...                                   */
/* 127: 10MHz                            */
/* Calculation Formula:                  */
/*     1260MHz /(DRPAI_FREQ - 1)         */
/*     (When DRPAI_FREQ = 3 or more.)    */

#endif
