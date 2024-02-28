#include "sort.h"

using namespace sort;

Sort::Sort(int maxAge, int minHits, float iouThresh)
    : maxAge(maxAge), minHits(minHits), iouThresh(iouThresh)
{
    km = std::make_shared<KuhnMunkres>();
}


Sort::~Sort()
{
}


cv::Mat Sort::update(const cv::Mat &bboxesDet)
{
    assert(bboxesDet.rows >= 0 && bboxesDet.cols == 6); // detections, [xc, yc, w, h, score, class_id]

    cv::Mat bboxesPred(0, 6, CV_32F, cv::Scalar(0));  // predictions used in data association, [xc, yc, w, h, ...]
    cv::Mat bboxesPost(0, 9, CV_32F, cv::Scalar(0));  // bounding boxes estimate, [xc, yc, w, h, score, class_id, vx, vy, tracker_id]

    // kalman bbox tracker predict
    for (auto it = trackers.begin(); it != trackers.end();)
    {
        cv::Mat bboxPred = (*it)->predict();   // Mat(1, 4)
        if (isAnyNan<float>(bboxPred))
            trackers.erase(it);     // remove the NAN value and corresponding tracker
        else{
            cv::hconcat(bboxPred, cv::Mat(1, 2, CV_32F,cv::Scalar(0)), bboxPred);   // Mat(1, 6)
            cv::vconcat(bboxesPred, bboxPred, bboxesPred);  // Mat(N, 6)
            ++it;
        }
    }

    TypeAssociate asTuple = dataAssociate(bboxesDet, bboxesPred);
    TypeMatchedPairs matchedDetPred = std::get<0>(asTuple);
    TypeLostDets lostDets = std::get<1>(asTuple);
    TypeLostPreds lostPreds = std::get<2>(asTuple);

    // update matched trackers with assigned detections
    for (auto pair : matchedDetPred)
    {
        int detInd = pair.first;
        int predInd = pair.second;
        cv::Mat bboxPost = trackers[predInd]->update(bboxesDet.rowRange(detInd, detInd + 1));

        if (trackers[predInd]->getHitStreak() >= minHits)
        {
            float score = bboxesDet.at<float>(detInd, 4);
            int classId = bboxesDet.at<float>(detInd, 5);
            float dx = trackers[predInd]->getState().at<float>(4, 0);
            float dy = trackers[predInd]->getState().at<float>(5, 0);
            int trackerId = trackers[predInd]->getFilterId();
            cv::Mat tailData = (cv::Mat_<float>(1, 5) << score, classId, dx, dy, trackerId);
            cv::hconcat(bboxPost, tailData, bboxPost);
            cv::vconcat(bboxesPost, bboxPost, bboxesPost);  // Mat(N, 9)
        }
    }

    // remove dead trackers
    trackers.erase(
        std::remove_if(trackers.begin(), trackers.end(),
            [&](const KalmanBoxTracker::Ptr& kbt)->bool {
                return kbt->getTimeSinceUpdate() > maxAge;
            }),
        trackers.end()
    );

    // create and initialize new trackers for unmatched detections
    for (int lostInd : lostDets)
    {
        cv::Mat lostBbox = bboxesDet.rowRange(lostInd, lostInd + 1);
        trackers.push_back(make_shared<KalmanBoxTracker>(lostBbox));
    }

    return bboxesPost;
}


TypeAssociate Sort::dataAssociate(const cv::Mat& bboxesDet, const cv::Mat& bboxesPred)
{
    TypeMatchedPairs matchedDetPred;
    TypeLostDets lostDets;
    TypeLostPreds lostPreds;

    // initialize
    for (int i = 0; i < bboxesDet.rows; ++i)
        lostDets.push_back(i);  // size M
    for (int j = 0; j < bboxesPred.rows; ++j)
        lostPreds.push_back(j); // size N

    // nothing detected or predicted
    if (bboxesDet.rows == 0 || bboxesPred.rows == 0)
        return make_tuple(matchedDetPred, lostDets, lostPreds);

    // compute IoU matrix
    cv::Mat iouMat = getIouMatrix(bboxesDet, bboxesPred);   // Mat(M, N)

    // Kuhn Munkres assignment algorithm
    Vec2f costMatrix(iouMat.rows, Vec1f(iouMat.cols, 0.0f));
    for (int i = 0; i < iouMat.rows; ++i)
        for (int j = 0; j < iouMat.cols; ++j)
            costMatrix[i][j] = 1.0f - iouMat.at<float>(i, j);
    auto indices = km->compute(costMatrix);

    // find matched pairs and lost detect and predict
    for (auto [detInd, predInd] : indices) {
        matchedDetPred.push_back({detInd, predInd});
        lostDets.erase(remove(lostDets.begin(), lostDets.end(), detInd), lostDets.end());
        lostPreds.erase(remove(lostPreds.begin(), lostPreds.end(), predInd), lostPreds.end());
    }

    return make_tuple(matchedDetPred, lostDets, lostPreds);
}


cv::Mat Sort::getIouMatrix(const cv::Mat& bboxesA, const cv::Mat& bboxesB)
{
    assert(bboxesA.cols >= 4 && bboxesB.cols >= 4);
    int numA = bboxesA.rows;
    int numB = bboxesB.rows;
    cv::Mat iouMat(numA, numB, CV_32F, cv::Scalar(0.0));

    cv::Rect re1, re2;
    for (int i = 0; i < numA; ++i)
    {
        for (int j = 0; j < numB; ++j)
        {
            re1.x = bboxesA.at<float>(i, 0) - bboxesA.at<float>(i, 2) / 2.0;
            re1.y = bboxesA.at<float>(i, 1) - bboxesA.at<float>(i, 3) / 2.0;
            re1.width = bboxesA.at<float>(i, 2);
            re1.height = bboxesA.at<float>(i, 3);
            re2.x = bboxesB.at<float>(j, 0) - bboxesB.at<float>(j, 2) / 2.0;
            re2.y = bboxesB.at<float>(j, 1) - bboxesB.at<float>(j, 3) / 2.0;
            re2.width = bboxesB.at<float>(j, 2);
            re2.height = bboxesB.at<float>(j, 3);

            iouMat.at<float>(i, j) = (re1 & re2).area() / ((re1 | re2).area() + FLT_EPSILON);
        }
    }

    return iouMat;
}