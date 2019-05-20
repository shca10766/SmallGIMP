/*
#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp" 
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp" 
#include "opencv2/stitching.hpp" 

using namespace cv;
using namespace std;

void detectAndDisplay(Mat& frame);

bool checkInteriorExterior(const cv::Mat &mask, const cv::Rect &croppingMask, int &top, int &bottom, int &left, int &right);

bool compareX(cv::Point a, cv::Point b);

bool compareY(cv::Point a, cv::Point b);

void crop(cv::Mat &source);

void dila_Ero(Mat &src);

void bright(Mat & img);

void Stitch(vector<Mat> &images, Mat &src);

void detectAndDisplay(Mat& frame);

void faceDetection(Mat& src);

void dark(Mat & img);
*/
#pragma once

#include <opencv2/opencv.hpp>
#include "Frame.h"


using namespace cv;

class Frame;

void bright(Frame& frame);
void dark(Frame& frame);
void save(Frame& frame);
