#pragma once
#include <string>
#include <opencv2/opencv.hpp>
#include "Frame.h"

using namespace std;
using namespace cv;

class Frame;

// Trackbar class
class Trackbar
{
public:
	double minValue;
	double maxValue;
	double step;
	double segment;
	string label;

	void(*pointerfunc)(Frame& frame,double value,int id);
	int id;


	double currentValue;
	
	Rect pos;
	Mat img;

	bool needRefresh;

	Trackbar();
	Trackbar(string _label,double _minValue,double _maxValue,double _step,double _segment,double _currentValue, void(*_pointerfunc)(Frame& frame, double value, int id),int _id);
	~Trackbar();

	void render(Mat &mat,Rect area);

	void update();

	void positionValue(int x, int y);

	void changeValue(double v);

	double getValue();

	bool isInside(int x, int y);

	void callfunc(Frame& frame);


};

