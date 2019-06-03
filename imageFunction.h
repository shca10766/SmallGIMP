#pragma once

#include <opencv2/opencv.hpp>
#include "Frame.h"
#include "tinyfiledialogs.h"
#include <string>


using namespace cv;

class Frame;

void brightness(Frame& frame);

void save(Frame& frame);

void saveImage(Frame& frame);

void save(Frame & frame);


void close(Frame& frame);
void brightnessCallback(Frame& frame,double value, int id);

void switchImage(Frame& frame);

void openImage(Frame& frame);

void cannyEdgeDetection(Frame & frame);

void resize(Frame & frame);

void detectAndDisplay(Frame & frame);
void faceDetection(Frame & src);

void dila_Ero(Frame& frame);
void DilaCallBack(Frame &frame, double value, int id);

bool compareY(cv::Point a, cv::Point b);
bool compareX(cv::Point a, cv::Point b);
bool checkInteriorExterior(const cv::Mat &mask, const cv::Rect &croppingMask, int &top, int &bottom, int &left, int &right);

void Stitch(Frame & frame);
void crop(cv::Mat &source);
