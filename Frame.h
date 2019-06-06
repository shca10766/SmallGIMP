#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

#include "Section.h"

#define BX 5000
#define BY 5000

using namespace std;
using namespace cv;

class Section;
class Button;
class Trackbar;


// handle the content of the window
class Frame
{
private:

	// each vector<Section*> contain sections for a different part of the window
	vector<Section*> header;
	vector<Section*> footer;
	vector<Section*> leftColumn;
	vector<Section*> rightColumn;
	vector<Section*> contentHeader;
	vector<Section*> contentFooter;
	
	// contain all buttons and trackbar contained in the window
	vector<Button*> frameButtonList;
	vector<Trackbar*> frameTrackbarList;
	Button* currentButton = nullptr;
	Trackbar* currentTrackbar = nullptr;

	// contains all the images
	vector<pair<String,vector<Mat>>> images;
	int currentImage = 0;
	Mat image;
	Size imageSize;
	Rect imageArea;

	// data for the background
	Mat background = cv::Mat(10000, 10000, CV_8UC3, Scalar(255, 255, 255));
	int backgroundX = BX;
	int backgroundY = BY;
	int imageX = 50;
	int imageY = 50;

	// contain the screen that will be displayed
	Mat screen;
	Size windowSize;

public:

	Frame();
	Frame(int width,int height);
	~Frame();

	void frameToMat();

	void addSection(Section* section);
	void addImage(String name, String path);
	Mat getFrame();

	void update(int cX=0,int cY=0);
	void updateImage();
	void updateBackground();
	bool updateAllButtons(int _x,int _y,int eventType);
	bool updateAllTrackbar(int _x, int _y, int eventType);

	void setImage(int i);
	void setTempImage(Mat& img);
	void centerImage();
	void modifyImage(Mat img);
	void addToBackgroundPos(int x, int y);
	void resizeImagef(float f);
	void undo();

	void doPressedButton();
	void updateTrackbar();

	void removeLastRightSection();
	int rightSectionLength();

	void getImage(Mat& img);
	int getBackgroundX();
	int getBackgroundY();
	vector<pair<String, vector<Mat>>> getImages();
	int getNumberOfImages();
	Size getSize();
	Rect getImageArea();

};

