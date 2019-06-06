#include <opencv2/opencv.hpp>

#include "Section.h"
#include "Frame.h"
#include "Button.h"
#include "Trackbar.h"

#include <iostream>

using namespace cv;
using namespace std;

// Name and size of the window
#define WINDOW_NAME "Gimp"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


// some variable used in callBackFunc
Frame h;
bool down = false;
int initialX = 0;
int initialY = 0;
int cX = 0;
int cY = 0;
bool buttonPressed = false;
bool trackBarChanged = false;


// callback fonction to handle mouseEvent
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	// for buttons
	if (h.updateAllButtons(x, y, event))
	{
		buttonPressed = true;
		return;
	}

	// for trackbar
	if (h.updateAllTrackbar(x, y, event))
	{
		trackBarChanged = true;
		return;
	}

	// For the image
	Rect imageArea;
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		imageArea = h.getImageArea();
		if (!((imageArea.x < x) && (x < (imageArea.x + imageArea.width)) && (imageArea.y < y) && (y < (imageArea.y + imageArea.height))))
			return;
		down = true;
		initialX = x;
		initialY = y;
		break;
	case EVENT_LBUTTONUP:
		h.addToBackgroundPos(cX, cY);
		cX = 0;
		cY = 0;
		down = false;
		break;
	case EVENT_MOUSEMOVE:
		if (down)
		{
			cX = initialX - x;
			cY = initialY - y;
		}
		break;
	case EVENT_MOUSEWHEEL:
		imageArea = h.getImageArea();
		if (!((imageArea.x < x) && (x < (imageArea.x + imageArea.width)) && (imageArea.y < y) && (y < (imageArea.y + imageArea.height))))
			return;
		Size imgSize;
		if (getMouseWheelDelta(flags) > 0)
		{
			h.resizeImagef(1.05f);
		}
		else
		{
			h.resizeImagef(0.95f);
		}
		break;
	}
}


/// For the section:
/// 0: header
/// 1: footer
/// 2: leftColumn
/// 3: rightColumn
/// 4: contentHeader
/// 5: contentFooter
// Initialisation of the frame and the window
void init(Frame& h)
{
	// header
	Section* header0 = new Section(cv::Mat(40, 1000, CV_8UC3, Scalar(80, 80, 80)), 0);
	header0->addButton(new Button("save", &save));
	header0->addButton(new Button("open", &openImage));
	h.addSection(header0);

	// leftColumn
	Section* left0 = new Section(cv::Mat(920, 150, CV_8UC3, Scalar(150, 150, 150)), 2);
	left0->addButton(new Button("brightness", &brightness));
	left0->addButton(new Button("cannyEdge", &cannyEdgeDetection));
	left0->addButton(new Button("Dila/Ero", &dila_Ero));
	left0->addButton(new Button("Face Recognition", &faceDetection));
	left0->addButton(new Button("Resize", &resize));
	left0->addButton(new Button("sticthing", &Stitch));
	h.addSection(left0);

	// contentHeader
	Section* contentHeader0 = new Section(cv::Mat(20, 920, CV_8UC3, Scalar(180, 180, 180)), 4);
	h.addSection(contentHeader0);

	h.addImage("image0", "img/van_gogh.jpg");
	h.frameToMat();

	// creating the window
	namedWindow(WINDOW_NAME);
	imshow(WINDOW_NAME, h.getFrame());
	resizeWindow(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
	setMouseCallback(WINDOW_NAME, CallBackFunc, NULL);
}


void GIMP()
{
	h = Frame(WINDOW_WIDTH, WINDOW_HEIGHT);
	init(h);

	int key;
	while (true)
	{
		// if a button was pressed, we do it's corresponding function
		if (buttonPressed)
		{
			buttonPressed = false;
			h.doPressedButton();
		}

		// if a trackbar was moved, we do it's corresponding function
		if (trackBarChanged)
		{
			trackBarChanged = false;
			h.updateTrackbar();
		}

		// we up
		if (down)
			h.update(cX, cY);

		imshow(WINDOW_NAME, h.getFrame());

		key = waitKey(16);
		if (key != -1)
		{
			// escape to close the application
			if (key == 27) {
				break;
			}
			// space to center the image
			if (key == 32) {
				h.centerImage();
			}
			// Z to cancel the last modification on the current image
			if (key == 122) {
				h.undo();
			}
			//cout << key << endl;
		}
	}
}

int main(int argc, const char *argv[])
{
	GIMP();
}
