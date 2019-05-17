#include "Button.h"


Button::Button()
{

}

Button::Button(int _x, int _y, int _width, int _height, string _name, void(*_pointerfunc)(Frame& frame))
{
	automatic = false;
	name = _name;
	pointerfunc = _pointerfunc;

	x = _x;
	y = _y;
	width = _width;
	height = _height;
}

Button::Button(string _name, void(*_pointerfunc)(Frame& frame))
{
	automatic = true;
	name = _name;
	pointerfunc = _pointerfunc;
	

}


Button::~Button()
{
}

void Button::doFunction(Frame & frame)
{
	(*pointerfunc)(frame);
}

void Button::setPosition(int _x, int _y, int _width, int _height)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
}

bool Button::isAutomatic()
{
	return automatic;
}
