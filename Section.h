#pragma once

#include "opencv2/opencv.hpp"
#include <string>;
#include <vector>

using namespace cv;
using namespace std;

class Section
{
public:
	Mat imageBackground;
	int type; // 0: image, 1: header, 2: leftColumn, 3: nav, 4:rightColumn, 5: footer
	Size size;
	bool scalable;

	bool containImages = false;
	vector<Mat> imageList;
	int currentImage = 0;

	Section();
	Section(Mat _imageBackground, int _type);
	Section(Mat _imageBackground, int _type,bool _containImages);
	Section(Size size,Scalar color, int _type);
	Section(string path, int _type);
	~Section();

	int addImage(Mat img);

	int getCurrentImage(Mat& img);

	void setCurrentImage(Mat& img);

};

