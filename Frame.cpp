#include "Frame.h"



Frame::Frame()
{
}

Frame::Frame(int _width,int _height)
{
	windowSize = Size(_width, _height);
	screen = cv::Mat(_height, _width, CV_8UC3);
	background = cv::Mat(10000, 10000, CV_8UC3, Scalar(255, 255, 255));
}


Frame::~Frame()
{
}

void Frame::addSection(Section* section)
{
	switch (section->type)
	{
		case 0:
			header.push_back(section);
			return;
		case 1:
			footer.push_back(section);
			return;
		case 2:
			leftColumn.push_back(section);
			return;
		case 3:
			rightColumn.push_back(section);
			return;
		case 4:
			contentHeader.push_back(section);
			return;
		case 5:
			contentFooter.push_back(section);
			return;

	}
}

void Frame::frameToMat()
{
	frameButtonList.clear();
	x = 0;
	y = 0;
	x2 = 0;
	y2 = 0;
	background(Rect(0.5*background.cols - 0.5*windowSize.width, 0.5*background.rows - 0.5*windowSize.height, windowSize.width, windowSize.height))
		.copyTo(screen(Rect(0, 0, windowSize.width, windowSize.height)));
	for(auto s : header)
	{
		resize(s->imageBackground, s->imageBackground, Size(windowSize.width, s->imageBackground.rows));
		s->imageBackground.copyTo(screen(Rect(0, y, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, 0, y, s->imageBackground.size());
		y += s->imageBackground.rows;
	}
	for (auto s : footer)
	{
		resize(s->imageBackground, s->imageBackground, Size(windowSize.width, s->imageBackground.rows));
		s->imageBackground.copyTo(screen(Rect(0, windowSize.height - y2 - s->imageBackground.rows, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, 0, windowSize.height - y2 - s->imageBackground.rows, s->imageBackground.size());
		y2 += s->imageBackground.rows;
	}
	for(auto s : leftColumn)
	{
		resize(s->imageBackground, s->imageBackground, Size(s->imageBackground.cols, windowSize.height-y-y2));
		s->imageBackground.copyTo(screen(Rect(x, y, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, x, y, s->imageBackground.size());
		x += s->imageBackground.cols;
	}
	for(auto s : rightColumn)
	{
		resize(s->imageBackground, s->imageBackground, Size(s->imageBackground.cols, windowSize.height - y - y2));
		s->imageBackground.copyTo(screen(Rect(windowSize.width - x2 - s->imageBackground.cols, y, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, x, y, s->imageBackground.size());
		x2 += s->imageBackground.cols;
	}
	for(auto s : contentHeader)
	{
		resize(s->imageBackground, s->imageBackground, Size(windowSize.width-x-x2, s->imageBackground.rows));
		s->imageBackground.copyTo(screen(Rect(x, y, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, x, y, s->imageBackground.size());
		y += s->imageBackground.rows;
	}
	for (auto s : contentFooter)
	{
		resize(s->imageBackground, s->imageBackground, Size(windowSize.width - x - x2, s->imageBackground.rows));
		s->imageBackground.copyTo(screen(Rect(x, windowSize.height - y2 - s->imageBackground.rows, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, x, windowSize.height - y2 - s->imageBackground.rows, s->imageBackground.size());
		y += s->imageBackground.rows;
	}

	if (images.size() != 0)
	{
		image.copyTo(background(Rect(imageX + backgroundX, imageY + backgroundY, imageSize.width, imageSize.height)));
		background(Rect(backgroundX, backgroundY, windowSize.width - x - x2, windowSize.height - y - y2)).copyTo(screen(Rect(x, y, windowSize.width - x - x2, windowSize.height - y - y2)));
	}

	//images[currentImage].second[0](Rect(x, y2, windowSize.width, windowSize.height)).copyTo(screen(Rect(0, 0, windowSize.width, windowSize.height)));
}

void Frame::updateAllbuttons()
{
	for (auto b : frameButtonList)
	{
		if (cvui::button(screen, b->x, b->y, b->width, b->height, b->name))
		{
			b->doFunction(*this);
		}
	}
}

void Frame::addImage(String name, String path)
{
	vector<Mat> temp;
	temp.push_back(imread(path));
	images.push_back(make_pair("image0", temp));
	setImage(images.size() - 1);
}

Mat Frame::getFrame()
{
	return screen;
}


Mat Frame::getImage()
{
	return image;
}

void Frame::setImage(int i)
{
	currentImage = i;
	image = images[currentImage].second[0].clone();
	imageSize = Size(image.cols, image.rows);
}

int Frame::getBackgroundX()
{
	return backgroundX;
}

int Frame::getBackgroundY()
{
	return backgroundY;
}

void Frame::addToBackgroundPos(int x, int y)
{
	backgroundX += x;
	backgroundY += y;
}

void Frame::update(int cX,int cY)
{
	//imshow("t", background);
	//waitKey(0);
	background(Rect(backgroundX + cX, backgroundY + cY, windowSize.width - x - x2, windowSize.height - y - y2)).copyTo(screen(Rect(x, y, windowSize.width - x - x2, windowSize.height - y - y2)));

}

void Frame::updateBackground()
{
	background.setTo(Scalar(255, 255, 255));
	image.copyTo(background(Rect(imageX + backgroundX, imageY + backgroundY, imageSize.width, imageSize.height)));

}

void Frame::resizeImagef(float f)
{
	imageSize.width *= f;
	imageSize.height *= f;
	resize(images[currentImage].second[0].clone(), image, imageSize);
	updateBackground();
}



