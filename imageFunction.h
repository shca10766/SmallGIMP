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
