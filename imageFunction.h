#pragma once

#include <opencv2/opencv.hpp>
#include "Frame.h"
#include "tinyfiledialogs.h"
#include <string>


using namespace cv;

class Frame;

// interface
void saveImage(Frame& frame);
void save(Frame & frame);
void close(Frame& frame);
void switchImage(Frame& frame);
void openImage(Frame& frame);
Mat getImage();

// brightness
void brightnessCallback(Frame& frame,double value, int id);
void brightness(Frame& frame);

// canny edge
void cannyEdgeCallBack(Frame &frame, double lowThreshold, int id);
void cannyEdgeDetection(Frame & frame);

//resizing
void resizeCallBack(Frame &frame, double value, int id);
void resize(Frame & frame);

//dilatation & erosion
void DilaCallBack(Frame &frame, double value, int id);
void dila_Ero(Frame& frame);

// face detection
void faceDetection(Frame & src);
void detectAndDisplay(Frame & frame);

// stitching
bool compareY(cv::Point a, cv::Point b);
bool compareX(cv::Point a, cv::Point b);
bool checkInteriorExterior(const cv::Mat &mask, const cv::Rect &croppingMask, int &top, int &bottom, int &left, int &right);
void Stitch(Frame & frame);
void crop(cv::Mat &source);
