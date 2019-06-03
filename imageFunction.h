#pragma once

#include <opencv2/opencv.hpp>
#include "Frame.h"
//#include "tinyfiledialogs.h"
#include <string>



using namespace cv;

class Frame;

void brightness(Frame& frame);

void save(Frame& frame);

void saveImage(Frame& frame);



void close(Frame& frame);
void tempCallback(Frame& frame,double value, int id);
void temp(Frame& frame);

void detectAndDisplay(Frame & frame);
void faceDetection(Frame & src);
bool compareY(cv::Point a, cv::Point b);
bool compareX(cv::Point a, cv::Point b);
bool checkInteriorExterior(const cv::Mat &mask, const cv::Rect &croppingMask, int &top, int &bottom, int &left, int &right);

void Stitch(Frame & frame);
void crop(cv::Mat &source);


void dila_Ero(Frame& frame);
void DilaCallBack(Frame &frame, double value, int id);

void switchImage(Frame& frame);

//void openImage(Frame& frame);

void cannyEdgeDetection(Frame & frame);
