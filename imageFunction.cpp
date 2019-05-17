#include "imageFunction.h"

void bright(Frame& frame)
{
	frame.updateImage();
	Mat img;
	frame.getImage(img);
	img.convertTo(img, img.type(), 1, 20);
	frame.updateBackground();
}

void dark(Frame& frame)
{
	frame.updateImage();
	Mat img;
	frame.getImage(img);
	img.convertTo(img, img.type(), 1, -20);
	frame.updateBackground();
}

void save(Frame & frame)
{
	Mat img;
	frame.getImage(img);
	frame.modifyImage(img);
}
