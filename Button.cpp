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
	imgSwitch = false;
	isPressed = false;
}

Button::Button(string _name, void(*_pointerfunc)(Frame& frame))
{
	automatic = true;
	name = _name;
	pointerfunc = _pointerfunc;
	imgSwitch = false;
	isPressed = false;

}

Button::Button(string _name, void(*_pointerfunc)(Frame& frame),bool _imgSwitch)
{
	automatic = true;
	name = _name;
	pointerfunc = _pointerfunc;
	imgSwitch = _imgSwitch;
	isPressed = false;
}


Button::~Button()
{
}

void Button::doFunction(Frame & frame)
{
	if (imgSwitch)
	{
		auto f = frame.getImages();
		for (unsigned i(0);i<frame.numberOfImages();i++)
		{
			if (f[i].first == name)
			{
				frame.setImage(i);
				break;
			}
		}
	}
	isPressed = false;
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

bool Button::isInside(int _x, int _y)
{
	return ((_x > x) && (_x < x + width) && (_y > y) && (_y < y + height));
}

void Button::setState(bool _isPressed)
{
	isPressed = _isPressed;
}

Size Button::getSize()
{
	return Size(width,height);
}

int Button::getX()
{
	return x;
}

int Button::getY()
{
	return y;
}

String Button::getName()
{
	return name;
}
