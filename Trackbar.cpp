#include "Trackbar.h"

Trackbar::Trackbar()
{
}

Trackbar::Trackbar(string _label, double _minValue, double _maxValue, double _step, double _segment, double _currentValue, void(*_pointerfunc)(Frame& frame, double value, int id),int _id)
{
	label = _label;
	minValue = _minValue;
	maxValue = _maxValue;
	step = _step;
	segment = _segment;
	currentValue = _currentValue;
	needRefresh = true;
	pointerfunc = _pointerfunc;
	id = _id;
}


Trackbar::~Trackbar()
{
}

void Trackbar::render(Mat &mat, Rect area)
{
	img = mat;
	pos = area;
	update();
}

// draw the trackbar
void Trackbar::update()
{
	double scale = 0.4;
	int font = cv::FONT_HERSHEY_SIMPLEX;
	int thickness = 1;
	int* baseline = 0;
	Size textSize;
	ostringstream str;

	cv::rectangle(img, pos, Scalar(60, 60, 60), -1, LINE_AA);
	cv::rectangle(img, pos, Scalar(130, 130, 130), 1, LINE_AA);
	int x = pos.x;
	double gapWidth = pos.width / (maxValue - minValue);
	for (double d = 0; d <= maxValue- minValue; d += step) {
		cv::Point aPoint1(pos.x + d * gapWidth, pos.y);
		cv::Point aPoint2(pos.x + d * gapWidth, pos.y - 3);
		cv::line(img, aPoint1, aPoint2, Scalar(130, 130, 130));
	}
	for (double d = 0; d <= maxValue- minValue; d += segment) {
		cv::Point aPoint1(pos.x + d * gapWidth, pos.y);
		cv::Point aPoint2(pos.x + d * gapWidth, pos.y - 8);
		cv::line(img, aPoint1, aPoint2, Scalar(130, 130, 130));
		str.str(string());
		str << (d+minValue);
		putText(img,str.str(), Point(pos.x+d*gapWidth,pos.y-5), font, scale, Scalar(0, 0, 0), thickness);
	}
	int aIndicatorWidth = 3;
	int aIndicatorHeight = 4;
	int aBarHeight = 7;
	double aPixelX = pos.x + (currentValue-minValue) * gapWidth;
	double temp = pos.y + pos.height / 2;
	cv::Point aPoint1(aPixelX - aIndicatorWidth, temp - aIndicatorHeight);
	cv::Point aPoint2(aPixelX + aIndicatorWidth, temp + aBarHeight + aIndicatorHeight);
	cv::Rect aRect(aPoint1, aPoint2);
	str.str(string());
	str << currentValue;
	putText(img, str.str(), Point(aPixelX, pos.y +30), font, scale, Scalar(0, 0, 0), thickness);

	cv::rectangle(img, aRect, Scalar(130, 130, 130), -1, LINE_AA);
	cv::rectangle(img, aRect, Scalar(40, 40, 40), 1, LINE_AA);
	putText(img, label, Point(pos.x,pos.y-20), font, scale, Scalar(0, 0, 0), thickness);

	needRefresh = false;
}

// update the value of the trackbar according to the mouse position
void Trackbar::positionValue(int x, int y)
{
	double a = max(min(((maxValue - minValue) * (x - pos.x)/(pos.width))+minValue,maxValue),minValue);
	for (double b = minValue; b <= maxValue; b += step)
	{
		if ((a >= (b - step * 0.5)) && (a <= (b + step * 0.5)))
		{
			changeValue(b);
			needRefresh = true;
			return;
		}
	}
}

void Trackbar::changeValue(double v)
{
	currentValue = v;
}

double Trackbar::getValue()
{
	return currentValue;
}

// return whether _x,_y is inside the trackbar
bool Trackbar::isInside(int x, int y)
{
	return ((x > pos.x) && (x < pos.x + pos.width) && (y > pos.y-15) && (y < pos.y + pos.height+15));
}

void Trackbar::callfunc(Frame & frame)
{
	(*pointerfunc)(frame, currentValue, id);
}



