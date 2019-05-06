#include "Frame.h"



Frame::Frame()
{
}

Frame::Frame(Size _windowSize)
{
	windowSize = _windowSize;
}


Frame::~Frame()
{
}

void Frame::addSection(Section* section)
{
	switch (section->type)
	{
		case 0:
			content.push_back(section);
			return;
		case 1:
			header.push_back(section);
			return;
		case 2:
			leftColumn.push_back(section);
			return;
		case 3:
			rightColumn.push_back(section);
			return;
		case 4:
			footer.push_back(section);
			return;

	}
}

void Frame::frameToMat(Mat& dest)
{
	Mat img;
	Mat centerImage;
	int x = 0;
	int y = 0;
	int x2 = 0;
	int y2 = 0;
	for(auto s : header)
	{
		resize(s->imageBackground, s->imageBackground, Size(windowSize.width, s->imageBackground.rows));
		s->imageBackground.copyTo(dest(Rect(x, y, s->imageBackground.cols, s->imageBackground.rows)));
		y += s->imageBackground.rows;
	}
	for(auto s : leftColumn)
	{
		resize(s->imageBackground, s->imageBackground, Size(s->imageBackground.cols, windowSize.height-y));
		s->imageBackground.copyTo(dest(Rect(x, y, s->imageBackground.cols, s->imageBackground.rows)));
		x += s->imageBackground.cols;
	}
	for(auto s : rightColumn)
	{
		resize(s->imageBackground, s->imageBackground, Size(s->imageBackground.cols, windowSize.height - y));
		s->imageBackground.copyTo(dest(Rect(windowSize.width - x2 - s->imageBackground.cols, y, s->imageBackground.cols, s->imageBackground.rows)));
		x2 += s->imageBackground.cols;
	}
	y2 = y;
	for(auto s : content)
	{
		if (!s->containImages)
		{
			resize(s->imageBackground, s->imageBackground, Size(windowSize.width-x-x2, s->imageBackground.rows));
			s->imageBackground.copyTo(dest(Rect(x, y2, s->imageBackground.cols, s->imageBackground.rows)));
		}
		else
		{
			resize(s->imageBackground, s->imageBackground, Size(windowSize.width - x - x2, windowSize.height-y-y2));
			s->imageBackground.copyTo(dest(Rect(x, y2, s->imageBackground.cols, s->imageBackground.rows)));
			s->getCurrentImage(centerImage);
			resize(centerImage, centerImage, Size(s->imageBackground.cols * 0.75, s->imageBackground.rows *0.75));
			centerImage.copyTo(dest(Rect(x + 0.125*s->imageBackground.cols, y2 + 0.125*s->imageBackground.rows, centerImage.cols, centerImage.rows)));
			image = dest(Rect(x + 0.125*s->imageBackground.cols, y2 + 0.125*s->imageBackground.rows, centerImage.cols, centerImage.rows));
			s->setCurrentImage(image);
		}
		y2 += s->imageBackground.rows;
	}
	//for each (Section s in footer)
	//{
	//	s->imageBackground.copyTo(dest(Rect(0, y, s->imageBackground.cols, s->imageBackground.rows)));
	//	y += s->imageBackground.rows;
	//}
	return;
}

