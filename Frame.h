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

class Frame
{
private:

	vector<Section*> header;
	vector<Section*> footer;
	vector<Section*> leftColumn;
	vector<Section*> rightColumn;
	vector<Section*> contentHeader;
	vector<Section*> contentFooter;
	
	vector<Button*> frameButtonList;
	vector<Trackbar*> frameTrackbarList;
	Button* currentButton = nullptr;
	Trackbar* currentTrackbar = nullptr;

	vector<pair<String,vector<Mat>>> images;
	int currentImage = 0;
	Rect imageArea;

	Mat background = cv::Mat(10000, 10000, CV_8UC3, Scalar(255, 255, 255));
	Mat image;
	Size imageSize;

	int backgroundX = BX;
	int backgroundY = BY;
	int imageX = 50;
	int imageY = 50;

	Size windowSize;

	Mat screen;

	int x;
	int y;
	int x2;
	int y2;

public:

	Frame();
	Frame(int width,int height);
	~Frame();

	void addSection(Section* section);

	void frameToMat();

	bool updateAllbuttons(int _x,int _y,int eventType);

	bool updateAllTrackbar(int _x, int _y, int eventType);

	void addImage(String name, String path);

	Mat getFrame();

	void getImage(Mat& img);

	void setImage(int i);

	void setTempImage(Mat& img);

	int getBackgroundX();
	int getBackgroundY();
	void addToBackgroundPos(int x, int y);
	void update(int cX=0,int cY=0);
	void updateBackground();
	void resizeImagef(float f);
	void updateImage();

	void modifyImage(Mat img);
	void doPressedButton();
	void updateTrackbar();

	void centerImage();
	void undo();

	vector<pair<String, vector<Mat>>> getImages();

	int numberOfImages();

	void removeLastRightSection();

	int rightSectionLength();
	
	Size getSize();

	Rect getImageArea();
};

