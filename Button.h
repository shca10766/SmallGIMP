#pragma once
#include "opencv2/core.hpp"
#include <string>
#include "imageFunction.h"
#include "frame.h"

using namespace std;
using namespace cv;

class Frame;

class Button
{
private:
	bool automatic;
	void(*pointerfunc)(Frame& frame);


public:

	int x;
	int y;
	int width;
	int height;
	string name;

	Button();
	Button(int _x, int _y, int _width, int _height, string _name,void(*_pointerfunc)(Frame& frame));
	Button(string name,void(*_pointerfunc)(Frame& frame));
	~Button();

	void doFunction(Frame& frame);

	void setPosition(int _x, int _y, int _width, int _height);

	bool isAutomatic();
};

