#ifndef DEEPSORT_H
#define DEEPSORT_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

void deep_sort(cv::Mat img, cv::Point2d pt1, cv::Point2d pt2, cv::Scalar color);

#endif