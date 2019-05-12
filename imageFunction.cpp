#include "imageFunction.h"

void bright(Mat & img)
{
	img.convertTo(img, img.type(), 1, 20);
}

void dark(Mat & img)
{
	img.convertTo(img, img.type(), 1, -20);
}
