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
	frameTrackbarList.clear();
	x = 0;
	y = 0;
	x2 = 0;
	y2 = 0;
	//background(Rect(0.5*background.cols - 0.5*windowSize.width, 0.5*background.rows - 0.5*windowSize.height, windowSize.width, windowSize.height))
	//	.copyTo(screen(Rect(0, 0, windowSize.width, windowSize.height)));
	for(auto s : header)
	{
		resize(s->imageBackground, s->imageBackground, Size(windowSize.width, s->imageBackground.rows));
		s->imageBackground.copyTo(screen(Rect(0, y, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, 0, y, s->imageBackground.size(),0);
		y += s->imageBackground.rows;
	}
	for (auto s : footer)
	{
		resize(s->imageBackground, s->imageBackground, Size(windowSize.width, s->imageBackground.rows));
		s->imageBackground.copyTo(screen(Rect(0, windowSize.height - y2 - s->imageBackground.rows, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, 0, windowSize.height - y2 - s->imageBackground.rows, s->imageBackground.size(),0);
		y2 += s->imageBackground.rows;
	}
	for(auto s : leftColumn)
	{
		resize(s->imageBackground, s->imageBackground, Size(s->imageBackground.cols, windowSize.height-y-y2));
		s->imageBackground.copyTo(screen(Rect(x, y, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, x, y, s->imageBackground.size(),0);
		x += s->imageBackground.cols;
	}
	for(auto s : rightColumn)
	{
		resize(s->imageBackground, s->imageBackground, Size(s->imageBackground.cols, windowSize.height - y - y2));
		s->imageBackground.copyTo(screen(Rect(windowSize.width - x2 - s->imageBackground.cols, y, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, windowSize.width - x2 - s->imageBackground.cols, y, s->imageBackground.size(),3);
		s->renderAllTracbar(screen, frameTrackbarList, Rect(windowSize.width - x2 - s->imageBackground.cols, y, s->imageBackground.cols,s->imageBackground.rows));
		x2 += s->imageBackground.cols;
	}
	for(auto s : contentHeader)
	{
		resize(s->imageBackground, s->imageBackground, Size(windowSize.width-x-x2, s->imageBackground.rows));
		s->imageBackground.copyTo(screen(Rect(x, y, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, x, y, s->imageBackground.size(),2);
		y += s->imageBackground.rows;
	}
	for (auto s : contentFooter)
	{
		resize(s->imageBackground, s->imageBackground, Size(windowSize.width - x - x2, s->imageBackground.rows));
		s->imageBackground.copyTo(screen(Rect(x, windowSize.height - y2 - s->imageBackground.rows, s->imageBackground.cols, s->imageBackground.rows)));
		s->showAllButton(frameButtonList, x, windowSize.height - y2 - s->imageBackground.rows, s->imageBackground.size(),0);
		y2 += s->imageBackground.rows;
	}

	Mat buttonMat = Mat(100, 100, CV_8UC3, Scalar(120, 120, 120));
	copyMakeBorder(buttonMat, buttonMat, 5, 5, 5, 5, BORDER_CONSTANT, Scalar(10, 10, 10));

	double scale = 0.4;
	int font = cv::FONT_HERSHEY_SIMPLEX;
	int thickness = 1.5;
	int* baseline=0;
	Size textSize;
	for (auto b : frameButtonList)
	{
		resize(buttonMat,buttonMat,b->getSize());
		buttonMat.copyTo(screen(Rect(b->getX(), b->getY(), buttonMat.cols, buttonMat.rows)));
		textSize = getTextSize(b->getName(), font, scale, thickness, baseline);
		putText(screen, b->getName(),Point(b->getX()+0.5*b->getSize().width-0.5*textSize.width, b->getY() + 0.6*b->getSize().height),font, scale, Scalar(0, 0, 0), thickness);
	}
	imageArea = Rect(x, y, windowSize.width - x - x2, windowSize.height - y - y2);
	if (images.size() != 0)
	{
		updateBackground();
		background(Rect(backgroundX, backgroundY, windowSize.width - x - x2, windowSize.height - y - y2)).copyTo(screen(imageArea));
	}

	//images[currentImage].second[0](Rect(x, y2, windowSize.width, windowSize.height)).copyTo(screen(Rect(0, 0, windowSize.width, windowSize.height)));
}

bool Frame::updateAllbuttons(int _x,int _y,int eventType)
{
	Mat buttonMat;
	double scale = 0.4;
	int font = cv::FONT_HERSHEY_SIMPLEX;
	int thickness = 1.5;
	int* baseline = 0;
	Size textSize;
	for (auto b : frameButtonList)
	{
		if (b->isInside(_x,_y))
		{
			if ((currentButton) && (b != currentButton))
			{
				buttonMat = Mat(100, 100, CV_8UC3, Scalar(120, 120, 120));
				copyMakeBorder(buttonMat, buttonMat, 5, 5, 5, 5, BORDER_CONSTANT, Scalar(10, 10, 10));
				resize(buttonMat, buttonMat, currentButton->getSize());
				buttonMat.copyTo(screen(Rect(currentButton->getX(), currentButton->getY(), buttonMat.cols, buttonMat.rows)));
				textSize = getTextSize(currentButton->getName(), font, scale, thickness, baseline);
				putText(screen, currentButton->getName(), Point(currentButton->getX() + 0.5*currentButton->getSize().width - 0.5*textSize.width, currentButton->getY() + 0.6*currentButton->getSize().height), font, scale, Scalar(0, 0, 0), thickness);

				currentButton = nullptr;
			}
			if (eventType == EVENT_LBUTTONDOWN)
			{
				buttonMat = Mat(100, 100, CV_8UC3, Scalar(60, 60, 60));
				copyMakeBorder(buttonMat, buttonMat, 5, 5, 5, 5, BORDER_CONSTANT, Scalar(10, 10, 10));
				resize(buttonMat, buttonMat, b->getSize());
				buttonMat.copyTo(screen(Rect(b->getX(), b->getY(), buttonMat.cols, buttonMat.rows)));
				textSize = getTextSize(b->getName(), font, scale, thickness, baseline);
				putText(screen, b->getName(), Point(b->getX() + 0.5*b->getSize().width - 0.5*textSize.width, b->getY() + 0.6*b->getSize().height), font, scale, Scalar(0, 0, 0), thickness);

				currentButton = b;
			}
			else if (eventType == EVENT_LBUTTONUP)
			{
				b->setState(true);
			}
			else if (eventType == EVENT_MOUSEMOVE)
			{
				buttonMat = Mat(100, 100, CV_8UC3, Scalar(180, 180, 180));
				copyMakeBorder(buttonMat, buttonMat, 5, 5, 5, 5, BORDER_CONSTANT, Scalar(10, 10, 10));
				resize(buttonMat, buttonMat, b->getSize());
				buttonMat.copyTo(screen(Rect(b->getX(), b->getY(), buttonMat.cols, buttonMat.rows)));
				textSize = getTextSize(b->getName(), font, scale, thickness, baseline);
				putText(screen, b->getName(), Point(b->getX() + 0.5*b->getSize().width - 0.5*textSize.width, b->getY() + 0.6*b->getSize().height), font, scale, Scalar(0, 0, 0), thickness);

				currentButton = b;
			}
			return true;
		}
		if ((currentButton))
		{
			buttonMat = Mat(100, 100, CV_8UC3, Scalar(120, 120, 120));
			copyMakeBorder(buttonMat, buttonMat, 5, 5, 5, 5, BORDER_CONSTANT, Scalar(10, 10, 10));
			resize(buttonMat, buttonMat, currentButton->getSize());
			buttonMat.copyTo(screen(Rect(currentButton->getX(), currentButton->getY(), buttonMat.cols, buttonMat.rows)));
			textSize = getTextSize(currentButton->getName(), font, scale, thickness, baseline);
			putText(screen, currentButton->getName(), Point(currentButton->getX() + 0.5*currentButton->getSize().width - 0.5*textSize.width, currentButton->getY() + 0.6*currentButton->getSize().height), font, scale, Scalar(0, 0, 0), thickness);
			currentButton = nullptr;
		}
	}
	return false;
}

bool Frame::updateAllTrackbar(int _x, int _y, int eventType)
{
	if (eventType == EVENT_LBUTTONDOWN)
	{
		for (auto t : frameTrackbarList)
		{
			if (t->isInside(_x, _y))
			{
				currentTrackbar = t;
				return true;
			}
		}
	}
	else if (!currentTrackbar)
	{
		return false;
	}
	else if (eventType == EVENT_LBUTTONUP)
	{
		currentTrackbar = nullptr;
		return true;

	}
	else if (eventType == EVENT_MOUSEMOVE)
	{
		int a;
		currentTrackbar->positionValue(_x, _y);
		return true;
	}
	return false;
}

void Frame::addImage(String name, String path)
{
	contentHeader[0]->addButton(new Button(name, &switchImage,true));
	vector<Mat> temp;
	temp.push_back(imread(path));
	images.push_back(make_pair(name, temp));
	setImage(images.size() - 1);
	updateBackground();
	frameToMat();
}

Mat Frame::getFrame()
{
	return screen;
}

void Frame::getImage(Mat& img)
{
	img = image;
}

void Frame::setImage(int i)
{
	currentImage = i;
	image = images[currentImage].second[images[currentImage].second.size() - 1].clone();
	imageSize = Size(image.cols, image.rows);
}

void Frame::setTempImage(Mat & img)
{
	image = img;
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
	resize(images[currentImage].second[images[currentImage].second.size()-1].clone(), image, imageSize);
	updateBackground();
}

void Frame::updateImage()
{
	setImage(currentImage);
}

void Frame::modifyImage(Mat img)
{
	images[currentImage].second.push_back(img);
	updateImage();
}

void Frame::centerImage()
{
	backgroundX = BX;
	backgroundY = BY;
}

void Frame::doPressedButton()
{
	for (auto b : frameButtonList)
	{
		if (b->isPressed)
		{
			b->doFunction(*this);
			return;
		}
	}
}

void Frame::updateTrackbar()
{
	if (!currentTrackbar)
		return;
	currentTrackbar->callfunc(*this);
	frameToMat();
}

void Frame::undo()
{
	if (images[currentImage].second.size() < 2)
		return;
	images[currentImage].second.erase(images[currentImage].second.end() - 1);
	updateImage();
	updateBackground();
}

vector<pair<String, vector<Mat>>> Frame::getImages()
{
	return images;
}

int Frame::numberOfImages()
{
	return images.size();
}

void Frame::removeLastRightSection()
{
	Section* del;
	if (rightColumn.size() == 0)
		return;
	
	rightColumn.pop_back();
	frameToMat();
	return;
}

int Frame::rightSectionLength()
{
	return rightColumn.size();
}





