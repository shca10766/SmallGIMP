#pragma once
#include "opencv2/core.hpp"
#include <string>
#include "imageFunction.h"
#include "Frame.h"

using namespace std;
using namespace cv;

class Frame;


class Button
{
private:
	static Mat* const buttonMat;
	static Mat* const pressedButtonMat;
	bool automatic;
	void(*pointerfunc)(Frame& frame);


public:

	int x;
	int y;
	int width;
	int height;
	string name;
	bool imgSwitch;
	bool isPressed;

	Button();
	Button(int _x, int _y, int _width, int _height, string _name,void(*_pointerfunc)(Frame& frame));
	Button(string name,void(*_pointerfunc)(Frame& frame));
	Button(string name, void(*_pointerfunc)(Frame& frame),bool _imgSwitch);
	~Button();

	void doFunction(Frame& frame);

	void setPosition(int _x, int _y, int _width, int _height);

	bool isAutomatic();

	bool isInside(int x, int y);
	void setState(bool _isPressed);

	Size getSize();
	int getX();
	int getY();
	String getName();
};

