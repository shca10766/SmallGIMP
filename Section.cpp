#include "Section.h"



Section::Section()
{
	imageBackground = Mat(Size(10,10), CV_8UC1, 0xFF);
	type = 0;
}

Section::Section(Mat _imageBackground, int _type)
{
	_imageBackground.copyTo(imageBackground);
	type = _type;
}

Section::Section(Mat _imageBackground, int _type, bool _containImages)
{
	_imageBackground.copyTo(imageBackground);
	type = _type;
	containImages = _containImages;
}

Section::Section(int _size, int _type, Scalar _color)
{
	imageBackground = Mat(Size(_size,_size),CV_8UC1,_color);
	type = _type;
	containImages = false;
}

Section::Section(Size size, Scalar color, int _type)
{
	imageBackground = Mat(size, CV_8UC1, color); 
	type = _type;
}

Section::Section(string path, int _type)
{
	imageBackground = imread(path);
	type = _type;
}


Section::~Section()
{
}

int Section::addImage(Mat img)
{
	if (containImages)
	{
		imageList.push_back(img.clone());
		return 1;
	}
	return 0;
}

int Section::getCurrentImage(Mat & img)
{
	if (containImages && (imageList.size() >= (currentImage + 1)))
	{
		img = imageList[currentImage];
		return 1;
	}
	return 0;
}

void Section::setCurrentImage(Mat & img)
{
	imageList[currentImage] = img;
}

void Section::addButton(Button * b)
{
	buttonList.push_back(b);
}

void Section::showAllButton(vector<Button*>& frameButtonList,int imageX,int imageY,Size size)
{
	int buttonWidth = min(size.width*0.8, size.height*0.8);
	bool horizontal = (size.width > size.height);
	int x = imageX + 0.1*buttonWidth;
	int y = imageY + 0.1*buttonWidth;

	for (Button* b : buttonList)
	{
		if (b->isAutomatic())
		{
			b->setPosition(x, y, buttonWidth, buttonWidth);
			frameButtonList.push_back(b);
			if (horizontal)
				x += buttonWidth * 1.1;
			else
				y += buttonWidth * 1.1;
		}
		else
		{
			frameButtonList.push_back(b);
		}
	}
}


