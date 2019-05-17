#include "imageFunction.h"

void bright(Frame& frame)
{
	Mat img = frame.getImage();
	img.convertTo(img, img.type(), 1, 20);
}

void dark(Frame& frame)
{
	Mat img = frame.getImage();
	img.convertTo(img, img.type(), 1, -20);
}
