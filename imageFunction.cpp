#include "imageFunction.h"

// to get the image displayed :
//	Mat img;
//	frame.getImage(img);

// to update the view of the image:
// frame.updateBackground();

// to "save" the modification of the image in the program, so that the next getImage will send the modified image:
// frame.modifyImage(img);


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
