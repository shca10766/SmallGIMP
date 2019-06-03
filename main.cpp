#include <opencv2/opencv.hpp>

#include <iostream>
#include "Section.h"
#include "Frame.h"
#include "Button.h"
#include "MouseHandler.h"
#include "Trackbar.h"

using namespace cv;
using namespace std;

#define WINDOW_NAME "Gimp"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


/// For the section:
/// 0: header
/// 1:footer
/// 2: leftColumn
/// 3: rightColumn
/// 4:contentHeader
/// 5: contentFooter
Frame h;

bool down = false;
int initialX = 0;
int initialY = 0;
int cX = 0;
int cY = 0;
bool buttonPressed = false;
bool trackBarChanged = false;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (h.updateAllbuttons(x, y, event))
	{
		buttonPressed = true;
		return;
	}
	if (h.updateAllTrackbar(x, y, event))
	{
		trackBarChanged = true;
		return;
	}
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		cout << "1";
		down = true;
		initialX = x;
		initialY = y;
		break;
	case EVENT_LBUTTONUP:
		cout << "2";

		h.addToBackgroundPos(cX, cY);
		cX = 0;
		cY = 0;
		down = false;
		break;
	case EVENT_MOUSEMOVE:
		cout << "3";

		if (down)
		{
			cX = initialX - x;
			cY = initialY - y;
		}
		break;
	case EVENT_MOUSEWHEEL:
		Size imgSize;
		if (getMouseWheelDelta(flags) > 0)
		{
			h.resizeImagef(1.05);
		}
		else
		{
			h.resizeImagef(0.95);
		}
		break;
	}
}

void init(Frame& h)
{
	// Création du header
	Section* header0 = new Section(cv::Mat(40, 1000, CV_8UC3, Scalar(80, 80, 80)), 0);
	//header0->addButton(new Button("open", &openImage));
	h.addSection(header0);

	// Création du footer
	//Section* footer0 = new Section(cv::Mat(40, 1000, CV_8UC3, Scalar(100, 100, 100)), 1);
	//h.addSection(footer0);

	// Création de la colonne de gauche
	Section* left0 = new Section(cv::Mat(920, 50, CV_8UC3, Scalar(150, 150, 150)), 2);
	left0->addButton(new Button("brightness", &brightness));
	left0->addButton(new Button("Dila/Ero", &dila_Ero));
	left0->addButton(new Button("Face Recognition", &faceDetection));
	left0->addButton(new Button("sticthing", &Stitch));
	h.addSection(left0);

	// Création de la colonne de droite
	//Section* right0 = new Section(cv::Mat(920, 250, CV_8UC3, Scalar(200, 200, 200)), 3);
	//right0->addTrackbar(new Trackbar("t", 0, 10, 1, 5, 5));
	//h.addSection(right0);


	// Création du header du content
	Section* contentHeader0 = new Section(cv::Mat(20, 920, CV_8UC3, Scalar(180, 180, 180)), 4);

	h.addSection(contentHeader0);

	// Création du footer du content
	//Section* contentFooter0 = new Section(cv::Mat(20, 920, CV_8UC3, Scalar(220, 220, 220)), 5);
	//h.addSection(contentFooter0);

	h.addImage("image0", "img/face.jpg");

	// Création de la fenêtre
	h.frameToMat();

	// Création de la fenêtre
	namedWindow(WINDOW_NAME);
	imshow(WINDOW_NAME, h.getFrame());
	resizeWindow(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
	setMouseCallback(WINDOW_NAME, CallBackFunc, NULL);
}

void GIMP()
{
	// Création de la frame qui va contenir l'ensemble de la fenêtre
	h = Frame(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Initialisation de l'interface
	init(h);

	int key;
	// Boucle principale
	while (true)
	{
		if (buttonPressed)
		{
			buttonPressed = false;
			h.doPressedButton();
		}
		if (trackBarChanged)
		{
			trackBarChanged = false;
			h.updateTrackbar();
		}

		h.update(cX, cY);

		imshow(WINDOW_NAME, h.getFrame());

		key = waitKey(10);
		if (key != -1)
		{
			if (key == 27) {
				break;
			}
			if (key == 32) {
				h.centerImage();
			}
			if (key == 122) {
				h.undo();
			}
			//cout << key << endl;
		}
	}
}
//#define CVUI_FILLED -1
//#define CVUI_ANTIALISED cv::LINE_AA
//
//const int OVER = 4;
//const unsigned int TRACKBAR_DISCRETE = 4;
//static const int gTrackbarMarginX = 14;
//
//const unsigned int TRACKBAR_HIDE_SEGMENT_LABELS = 1;
//const unsigned int TRACKBAR_HIDE_STEP_SCALE = 2;
//const unsigned int TRACKBAR_HIDE_MIN_MAX_LABELS = 8;
//const unsigned int TRACKBAR_HIDE_VALUE_LABEL = 16;
//const unsigned int TRACKBAR_HIDE_LABELS = 32;
//
//typedef struct {
//	cv::Mat where;			// where the block should be rendered to.
//	cv::Rect rect;			// the size and position of the block.
//	cv::Rect fill;			// the filled area occuppied by the block as it gets modified by its inner components.
//	cv::Point anchor;		// the point where the next component of the block should be rendered.
//	int padding;			// padding among components within this block.
//	int type;				// type of the block, e.g. ROW or COLUMN.
//} cvui_block_t;
//
//struct TrackbarParams {
//	long double min;
//	long double max;
//	long double step;
//	int segments;
//	unsigned int options;
//	std::string labelFormat;
//
//	inline TrackbarParams()
//		: min(0.)
//		, max(25.)
//		, step(1.)
//		, segments(0)
//		, options(0)
//		, labelFormat("%.0Lf")
//	{}
//};
//static char gBuffer[1024];
//
//
//cv::Scalar hexToScalar(unsigned int theColor);
//
//void trackbarHandle(cvui_block_t& theBlock, int theState, cv::Rect& theShape, double theValue, const TrackbarParams &theParams, cv::Rect& theWorkingArea);
//void trackbarPath(cvui_block_t& theBlock, int theState, cv::Rect& theShape, double theValue, const TrackbarParams &theParams, cv::Rect& theWorkingArea);
//void trackbarSteps(cvui_block_t& theBlock, int theState, cv::Rect& theShape, double theValue, const TrackbarParams &theParams, cv::Rect& theWorkingArea);
//void trackbarSegmentLabel(cvui_block_t& theBlock, cv::Rect& theShape, const TrackbarParams &theParams, long double theValue, cv::Rect& theWorkingArea, bool theShowLabel);
//void trackbarSegments(cvui_block_t& theBlock, int theState, cv::Rect& theShape, double theValue, const TrackbarParams &theParams, cv::Rect& theWorkingArea);
//void trackbar(cvui_block_t& theBlock, int theState, cv::Rect& theShape, double theValue, const TrackbarParams &theParams);
//void rect(cvui_block_t& theBlock, cv::Rect& thePos, unsigned int theBorderColor, unsigned int theFillingColor);
//bool bitsetHas(unsigned int theBitset, unsigned int theValue);
//
//int putTextCentered(cvui_block_t& theBlock, const cv::Point & position, const std::string &text) {
//	double aFontScale = 0.3;
//
//	auto size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, aFontScale, 1, nullptr);
//	cv::Point positionDecentered(position.x - size.width / 2, position.y);
//	cv::putText(theBlock.where, text, positionDecentered, cv::FONT_HERSHEY_SIMPLEX, aFontScale, cv::Scalar(0xCE, 0xCE, 0xCE), 1, CVUI_ANTIALISED);
//
//	return size.width;
//};
//
//inline double clamp01(double value)
//{
//	value = value > 1. ? 1. : value;
//	value = value < 0. ? 0. : value;
//	return value;
//}
//
//inline int trackbarValueToXPixel(const TrackbarParams & theParams, cv::Rect & theBounding, long double theValue)
//{
//	long double aRatio = (theValue - theParams.min) / (theParams.max - theParams.min);
//	aRatio = clamp01(aRatio);
//	long double thePixelsX = (long double)theBounding.x + gTrackbarMarginX + aRatio * (long double)(theBounding.width - 2 * gTrackbarMarginX);
//	return (int)thePixelsX;
//}
//
//cv::Scalar hexToScalar(unsigned int theColor) {
//	int aAlpha = (theColor >> 24) & 0xff;
//	int aRed = (theColor >> 16) & 0xff;
//	int aGreen = (theColor >> 8) & 0xff;
//	int aBlue = theColor & 0xff;
//
//	return cv::Scalar(aBlue, aGreen, aRed, aAlpha);
//}
//
//void rect(cvui_block_t& theBlock, cv::Rect& thePos, unsigned int theBorderColor, unsigned int theFillingColor) {
//	cv::Scalar aBorder = hexToScalar(theBorderColor);
//	cv::Scalar aFilling = hexToScalar(theFillingColor);
//
//	bool aHasFilling = aFilling[3] != 0xff;
//
//	if (aHasFilling) {
//		if (aFilling[3] == 0x00) {
//			// full opacity
//			cv::rectangle(theBlock.where, thePos, aFilling, CVUI_FILLED, CVUI_ANTIALISED);
//		}
//		else {
//			cv::Rect aClippedRect = thePos & cv::Rect(cv::Point(0, 0), theBlock.where.size());
//			double aAlpha = 1.00 - static_cast<double>(aFilling[3]) / 255;
//			cv::Mat aOverlay(aClippedRect.size(), theBlock.where.type(), aFilling);
//			cv::addWeighted(aOverlay, aAlpha, theBlock.where(aClippedRect), 1.00 - aAlpha, 0.0, theBlock.where(aClippedRect));
//		}
//	}
//
//	// Render the border
//	cv::rectangle(theBlock.where, thePos, aBorder, 1, CVUI_ANTIALISED);
//}
//
//bool bitsetHas(unsigned int theBitset, unsigned int theValue) {
//	return (theBitset & theValue) != 0;
//}
//
//void trackbarPath(cvui_block_t& theBlock, int theState, cv::Rect& theShape, double theValue, const TrackbarParams &theParams, cv::Rect& theWorkingArea) {
//	int aBarHeight = 7;
//	cv::Point aBarTopLeft(theWorkingArea.x, theWorkingArea.y + theWorkingArea.height / 2);
//	cv::Rect aRect(aBarTopLeft, cv::Size(theWorkingArea.width, aBarHeight));
//
//	int aBorderColor = theState == OVER ? 0x4e4e4e : 0x3e3e3e;
//
//	rect(theBlock, aRect, aBorderColor, 0x292929);
//	cv::line(theBlock.where, cv::Point(aRect.x + 1, aRect.y + aBarHeight - 2), cv::Point(aRect.x + aRect.width - 2, aRect.y + aBarHeight - 2), cv::Scalar(0x0e, 0x0e, 0x0e));
//}
//
//void trackbarSteps(cvui_block_t& theBlock, int theState, cv::Rect& theShape, double theValue, const TrackbarParams &theParams, cv::Rect& theWorkingArea) {
//	cv::Point aBarTopLeft(theWorkingArea.x, theWorkingArea.y + theWorkingArea.height / 2);
//	cv::Scalar aColor(0x51, 0x51, 0x51);
//
//	bool aDiscrete = bitsetHas(theParams.options, TRACKBAR_DISCRETE);
//	long double aFixedStep = aDiscrete ? theParams.step : (theParams.max - theParams.min) / 20;
//
//	// TODO: check min, max and step to prevent infinite loop.
//	for (long double aValue = theParams.min; aValue <= theParams.max; aValue += aFixedStep) {
//		int aPixelX = trackbarValueToXPixel(theParams, theShape, aValue);
//		cv::Point aPoint1(aPixelX, aBarTopLeft.y);
//		cv::Point aPoint2(aPixelX, aBarTopLeft.y - 3);
//		cv::line(theBlock.where, aPoint1, aPoint2, aColor);
//	}
//}
//
//void trackbarSegmentLabel(cvui_block_t& theBlock, cv::Rect& theShape, const TrackbarParams &theParams, long double theValue, cv::Rect& theWorkingArea, bool theShowLabel) {
//	cv::Scalar aColor(0x51, 0x51, 0x51);
//	cv::Point aBarTopLeft(theWorkingArea.x, theWorkingArea.y + theWorkingArea.height / 2);
//
//	int aPixelX = trackbarValueToXPixel(theParams, theShape, theValue);
//
//	cv::Point aPoint1(aPixelX, aBarTopLeft.y);
//	cv::Point aPoint2(aPixelX, aBarTopLeft.y - 8);
//	cv::line(theBlock.where, aPoint1, aPoint2, aColor);
//
//	if (theShowLabel)
//	{
//		//sprintf_s(gBuffer, theParams.labelFormat.c_str(), theValue);
//		String t = "test";
//		cv::Point aTextPos(aPixelX, aBarTopLeft.y - 11);
//		putTextCentered(theBlock, aTextPos, t);
//	}
//}
//
//void trackbarSegments(cvui_block_t& theBlock, int theState, cv::Rect& theShape, double theValue, const TrackbarParams &theParams, cv::Rect& theWorkingArea) {
//	int aSegments = theParams.segments < 1 ? 1 : theParams.segments;
//	long double aSegmentLength = (long double)(theParams.max - theParams.min) / (long double)aSegments;
//
//	bool aHasMinMaxLabels = bitsetHas(theParams.options, TRACKBAR_HIDE_MIN_MAX_LABELS) == false;
//
//	// Render the min value label
//	trackbarSegmentLabel(theBlock, theShape, theParams, theParams.min, theWorkingArea, aHasMinMaxLabels);
//
//	//Draw large steps and labels
//	bool aHasSegmentLabels = bitsetHas(theParams.options, TRACKBAR_HIDE_SEGMENT_LABELS) == false;
//	// TODO: check min, max and step to prevent infinite loop.
//	for (long double aValue = theParams.min; aValue <= theParams.max; aValue += aSegmentLength) {
//		trackbarSegmentLabel(theBlock, theShape, theParams, aValue, theWorkingArea, aHasSegmentLabels);
//	}
//
//	// Render the max value label
//	trackbarSegmentLabel(theBlock, theShape, theParams, theParams.max, theWorkingArea, aHasMinMaxLabels);
//}
//
//void trackbarHandle(cvui_block_t& theBlock, int theState, cv::Rect& theShape, double theValue, const TrackbarParams &theParams, cv::Rect& theWorkingArea) {
//	cv::Point aBarTopLeft(theWorkingArea.x, theWorkingArea.y + theWorkingArea.height / 2);
//	int aBarHeight = 7;
//
//	// Draw the rectangle representing the handle
//	int aPixelX = trackbarValueToXPixel(theParams, theShape, theValue);
//	int aIndicatorWidth = 3;
//	int aIndicatorHeight = 4;
//	cv::Point aPoint1(aPixelX - aIndicatorWidth, aBarTopLeft.y - aIndicatorHeight);
//	cv::Point aPoint2(aPixelX + aIndicatorWidth, aBarTopLeft.y + aBarHeight + aIndicatorHeight);
//	cv::Rect aRect(aPoint1, aPoint2);
//
//	int aFillColor = theState == OVER ? 0x525252 : 0x424242;
//
//	rect(theBlock, aRect, 0x212121, 0x212121);
//	aRect.x += 1; aRect.y += 1; aRect.width -= 2; aRect.height -= 2;
//	rect(theBlock, aRect, 0x515151, aFillColor);
//
//	bool aShowLabel = bitsetHas(theParams.options, TRACKBAR_HIDE_VALUE_LABEL) == false;
//
//	// Draw the handle label
//	if (aShowLabel) {
//		cv::Point aTextPos(aPixelX, aPoint2.y + 11);
//		//sprintf_s(internal::gBuffer, theParams.labelFormat.c_str(), static_cast<long double>(theValue));
//		String t = "test";
//		putTextCentered(theBlock, aTextPos, t);
//	}
//}
//
//void test()
//{
//	Mat test = Mat(1000, 1000, CV_8UC3, Scalar(120, 120, 120));
//	Rect r1 = Rect(130, 130, 200, 200);
//	Rect r2 = Rect(131, 131, 180, 180);
//	Point p = Point(10,10);
//	int a0 = 1;
//	int a1 = 0;
//	cvui_block_t temp = { test,r1,r2,p,a0,a1 };
//	cvui_block_t& theBlock = temp;
//	int theState = 4;
//	cv::Rect& theShape = r1;
//	double theValue = 5;
//	const TrackbarParams &theParams = TrackbarParams();
//
//	cv::Rect aWorkingArea(theShape.x + gTrackbarMarginX, theShape.y, theShape.width - 2 * gTrackbarMarginX, theShape.height);
//
//	trackbarPath(theBlock, theState, theShape, theValue, theParams, aWorkingArea);
//
//	bool aHideAllLabels = bitsetHas(theParams.options, TRACKBAR_HIDE_LABELS);
//	bool aShowSteps = bitsetHas(theParams.options, TRACKBAR_HIDE_STEP_SCALE) == false;
//
//	if (aShowSteps && !aHideAllLabels) {
//		trackbarSteps(theBlock, theState, theShape, theValue, theParams, aWorkingArea);
//	}
//
//	if (!aHideAllLabels) {
//		trackbarSegments(theBlock, theState, theShape, theValue, theParams, aWorkingArea);
//	}
//
//
//
//	trackbarHandle(theBlock, theState, theShape, theValue, theParams, aWorkingArea);
//	imshow("test", test);
//	waitKey(0);
//}
//
//void test2()
//{
//	Mat test = Mat(1000, 1000, CV_8UC3, Scalar(220, 200, 200));
//	Rect pos(100,100,300,7);
//
//	double minvalue = 0;
//	double maxvalue = 30;
//	double step = 1;
//	int value = 30;
//	double segmentLength = 10;
//	string label = "test";
//
//	Trackbar t(label, minvalue, maxvalue, step, segmentLength, value);
//	t.render(test, pos);
//
//	imshow("test", test);
//	waitKey(0);
//}

int main(int argc, const char *argv[])
{
	GIMP();
	//test2();
}
