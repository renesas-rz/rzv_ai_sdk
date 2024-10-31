/**
 * @desc:   kalmanfilter for boundary box tracking.
 *          opencv kalmanfilter documents:
 *              https://docs.opencv.org/4.x/dd/d6a/classcv_1_1KalmanFilter.html
 * 
 * @author: lst
 * @date:   12/10/2021
 */
#pragma once

#include <opencv2/video/tracking.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <assert.h>
#include <math.h>
#include <memory>

#define KF_DIM_X 7      // xc, yc, s, r, dxc/dt, dyc/dt, ds/dt
#define KF_DIM_Z 4      // xc, yc, s, r

namespace sort
{
    class KalmanBoxTracker
    {
    // variables
    public:
        using Ptr = std::shared_ptr<KalmanBoxTracker>;
    private:
        static int count;
        int id;
        int timeSinceUpdate = 0;
        int hitStreak = 0;
        std::shared_ptr<cv::KalmanFilter> kf = nullptr;
        cv::Mat xPost;
    
    // methods
    public:
        /**
         * @brief Kalman filter for bbox tracking
         * @param bbox bounding box, Mat(1, 4+) [xc, yc, w, h, ...]
         */
        explicit KalmanBoxTracker(const cv::Mat &bbox);

        virtual ~KalmanBoxTracker();
        KalmanBoxTracker(const KalmanBoxTracker&) = delete;
        void operator=(const KalmanBoxTracker&) = delete;

        /**
         * @brief updates the state vector with observed bbox. 
         * @param bbox  boundary box, Mat(1, 4+) [xc, yc, w, h, ...]
         * @return corrected bounding box estimate, Mat(1, 4)
         */
        cv::Mat update(const cv::Mat &bbox);

        /**
         * @brief advances the state vector and returns the predicted bounding box estimate. 
         * @return predicted bounding box, Mat(1, 4)
         */
        cv::Mat predict();

        static inline int getFilterCount()
        {
            return KalmanBoxTracker::count;
        }

        inline int getFilterId()
        {
            return id;
        }

        inline int getTimeSinceUpdate()
        {
            return timeSinceUpdate;
        }

        inline int getHitStreak()
        {
            return hitStreak;
        }

        inline cv::Mat getState()
        {
            return xPost.clone();
        }

    private:
        /**
         * @brief convert boundary box to measurement.
         * @param bbox boundary box (1, 4+) [x center, y center, width, height, ...]
         * @return measurement vector (4, 1) [x center; y center; scale/area; aspect ratio]
         */
        static inline cv::Mat convertBBoxToZ(const cv::Mat &bbox)
        {
            assert(bbox.rows == 1 && bbox.cols >= 4);
            float x = bbox.at<float>(0, 0);
            float y = bbox.at<float>(0, 1);
            float s = bbox.at<float>(0, 2) * bbox.at<float>(0, 3);
            float r = bbox.at<float>(0, 2) / bbox.at<float>(0, 3);

            return (cv::Mat_<float>(KF_DIM_Z, 1) << x, y, s, r);
        }

        /**
         * @brief convert state vector to boundary box.
         * @param state state vector (7, 1) (x center; y center; scale/area; aspect ratio; ...)
         * @return boundary box (1, 4) [x center, y center, width, height]
         */
        static inline cv::Mat convertXToBBox(const cv::Mat &state)
        {
            assert(state.rows == KF_DIM_X && state.cols == 1);
            float x = state.at<float>(0, 0);
            float y = state.at<float>(1, 0);
            float w = sqrt(state.at<float>(2, 0) * state.at<float>(3, 0));
            float h = state.at<float>(2, 0) / w;

            return (cv::Mat_<float>(1, 4) << x, y, w, h);
        }
    };
}

