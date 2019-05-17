#pragma once

#include <opencv2/opencv.hpp>
#include "Frame.h"


using namespace cv;

class Frame;

void bright(Frame& frame);
void dark(Frame& frame);


