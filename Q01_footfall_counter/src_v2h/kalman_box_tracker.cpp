#include "kalman_box_tracker.h"

using namespace sort;

int KalmanBoxTracker::count = 0;

KalmanBoxTracker::KalmanBoxTracker(const cv::Mat &bbox)
{   
    id = KalmanBoxTracker::count;
    KalmanBoxTracker::count++;

    kf = std::make_shared<cv::KalmanFilter>(KF_DIM_X, KF_DIM_Z);  // no control vector
    // state transition matrix (A), x(k) = A*x(k-1) + B*u(k) + w(k)
    kf->transitionMatrix = (cv::Mat_<float>(KF_DIM_X, KF_DIM_X) <<
                                1, 0, 0, 0, 1, 0, 0,
                                0, 1, 0, 0, 0, 1, 0,
                                0, 0, 1, 0, 0, 0, 1,
                                0, 0, 0, 1, 0, 0, 0,
                                0, 0, 0, 0, 1, 0, 0,
                                0, 0, 0, 0, 0, 1, 0,
                                0, 0, 0, 0, 0, 0, 1);
    // measurement matrix (H), z(k) = H*x(k) + v(k)
    kf->measurementMatrix = (cv::Mat_<float>(KF_DIM_Z, KF_DIM_X) <<
                                1, 0, 0, 0, 0, 0, 0,
                                0, 1, 0, 0, 0, 0, 0,
                                0, 0, 1, 0, 0, 0, 0,
                                0, 0, 0, 1, 0, 0, 0);
    // measurement noise covariance matrix (R), K(k) = P`(k)*Ct*inv(C*P`(k)*Ct + R)
    kf->measurementNoiseCov = (cv::Mat_<float>(KF_DIM_Z, KF_DIM_Z) <<
                                1,  0,  0,  0,
                                0,  1,  0,  0,
                                0,  0,  10, 0,
                                0,  0,  0,  10);
    // posteriori error estimate covariance matrix (P(k)): P(k)=(I-K(k)*H)*P'(k)
    kf->errorCovPost = (cv::Mat_<float>(KF_DIM_X, KF_DIM_X) <<
                                10, 0,  0,  0,  0,   0,   0,
                                0,  10, 0,  0,  0,   0,   0,
                                0,  0,  10, 0,  0,   0,   0,
                                0,  0,  0,  10, 0,   0,   0,
                                0,  0,  0,  0,  1e4, 0,   0,
                                0,  0,  0,  0,  0,   1e4, 0,
                                0,  0,  0,  0,  0,   0,   1e4);
    // process noise covariance matrix (Q), P'(k) = A*P(k-1)*At + Q
    kf->processNoiseCov = (cv::Mat_<float>(KF_DIM_X, KF_DIM_X) <<
                                1, 0, 0, 0, 0,    0,    0,
                                0, 1, 0, 0, 0,    0,    0,
                                0, 0, 1, 0, 0,    0,    0,
                                0, 0, 0, 1, 0,    0,    0,
                                0, 0, 0, 0, 1e-2, 0,    0,
                                0, 0, 0, 0, 0,    1e-2, 0,
                                0, 0, 0, 0, 0,    0,    1e-4);
    // corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
    cv::vconcat(convertBBoxToZ(bbox),
                cv::Mat(KF_DIM_X - KF_DIM_Z, 1, CV_32F, cv::Scalar(0)),
                kf->statePost);
}


KalmanBoxTracker::~KalmanBoxTracker()
{
}


cv::Mat KalmanBoxTracker::update(const cv::Mat &bbox)
{
    timeSinceUpdate = 0;
    hitStreak += 1;
    xPost = kf->correct(convertBBoxToZ(bbox));
    cv::Mat bboxPost = convertXToBBox(xPost);
    return bboxPost;
}


cv::Mat KalmanBoxTracker::predict()
{
    // bbox area (ds/dt + s) shouldn't be negtive
    if (kf->statePost.at<float>(6, 0) + kf->statePost.at<float>(2, 0) <= 0)
        kf->statePost.at<float>(6, 0) *= 0;

    cv::Mat xPred = kf->predict();
    cv::Mat bboxPred = convertXToBBox(xPred);

    hitStreak = timeSinceUpdate > 0 ? 0 : hitStreak;
    timeSinceUpdate++;

    return bboxPred;
}