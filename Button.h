#pragma once
#include "opencv2/core.hpp"
#include <string>
#include "imageFunction.h"

using namespace std;
using namespace cv;

class Button
{
private:
	bool automatic;
	void(*pointerfunc)(Mat& img);


public:

	int x;
	int y;
	int width;
	int height;
	string name;

	Button();
	Button(int _x, int _y, int _width, int _height, string _name,void(*_pointerfunc)(Mat& img));
	Button(string name,void(*_pointerfunc)(Mat& img));
	~Button();

	void doFunction(Mat& img);

	void setPosition(int _x, int _y, int _width, int _height);

	bool isAutomatic();
};

