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

// Gives each button their position and size
void Section::showAllButton(vector<Button*>& frameButtonList,int imageX,int imageY,Size size,int s=0)
{
	int buttonWidthX = min(size.width*0.8, size.height*0.8);
	int buttonWidthY = buttonWidthX;
	int d = 1;
	bool horizontal = (size.width > size.height);
	if (s == 1)
	{
		buttonWidthY /= 4;
	}
	else if (s == 2)
		buttonWidthX *= 4;
	else if (s == 3)
	{
		buttonWidthX = 70;
		buttonWidthY = 30;
		horizontal = true;
		d = -1;
		imageY += size.height*0.9;
	}
	int x = imageX + 0.1*buttonWidthX;
	int y = imageY + 0.1*buttonWidthY*d;
	for (Button* b : buttonList)
	{
		if (b->isAutomatic())
		{
			b->setPosition(x, y, buttonWidthX, buttonWidthY);
			frameButtonList.push_back(b);
			if (horizontal)
				x += buttonWidthX * 1.1;
			else
				y += buttonWidthY * 1.1;
		}
		else
		{
			frameButtonList.push_back(b);
		}
	}
}

void Section::addTrackbar(Trackbar * t)
{
	trackbarList.push_back(t);
}

// gives each trackbar their position and size
void Section::renderAllTracbar(Mat & mat, vector<Trackbar*>& frameTrackbarList, Rect pos)
{
	Rect tpos = pos;
	tpos = Rect(pos.x+20, pos.y+20, pos.width*0.8, 7);

	for (Trackbar* t : trackbarList)
	{
		tpos = Rect(tpos.x,tpos.y+pos.height/5,tpos.width,tpos.height);
		t->render(mat,tpos);
		frameTrackbarList.push_back(t);
	}
}



