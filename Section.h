#pragma once

#include "opencv2/opencv.hpp"
#include <string>
#include <vector>
#include "Button.h"
#include "Trackbar.h"

using namespace cv;
using namespace std;

class Button;
class Trackbar;

class Section
{
public:
	Mat imageBackground;
	int type; // 0: header, 1: footer, 2: leftColumn, 3: rightColumn, 4:contentHeader, 5: contentFooter
	Size size;
	bool scalable;
	vector<Button*> buttonList;
	vector<Trackbar*> trackbarList;

	bool containImages = false;
	vector<Mat> imageList;
	int currentImage = 0;

	Section();
	Section(Mat _imageBackground, int _type);
	Section(Mat _imageBackground, int _type,bool _containImages);
	Section(int _size, int _type, Scalar _color);
	Section(Size size,Scalar color, int _type);
	Section(string path, int _type);
	~Section();

	int addImage(Mat img);

	int getCurrentImage(Mat& img);

	void setCurrentImage(Mat& img);

	void addButton(Button * b);

	void showAllButton(vector<Button*>& buttonList, int imageX, int imageY, Size size,int s);

	void addTrackbar(Trackbar * t);

	void renderAllTracbar(Mat& mat, vector<Trackbar*>& frameTrackbarList,Rect pos);

};	

