#pragma once

#include <opencv2/opencv.hpp>

#include <iostream>
#include "Section.h"
#include "Frame.h"
#include "Button.h"
#include "MouseHandler.h"

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

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (h.updateAllbuttons(x, y, event))
		return;
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
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
	header0->addButton(new Button("save", &save));
	h.addSection(header0);

	// Création du footer
	Section* footer0 = new Section(cv::Mat(40, 1000, CV_8UC3, Scalar(100, 100, 100)), 1);
	h.addSection(footer0);

	// Création de la colonne de gauche
	Section* left0 = new Section(cv::Mat(920, 50, CV_8UC3, Scalar(150, 150, 150)), 2);
	left0->addButton(new Button("b", &bright));
	left0->addButton(new Button("d", &dark));
	h.addSection(left0);

	// Création de la colonne de droite
	Section* leftColumn0 = new Section(cv::Mat(920, 50, CV_8UC3, Scalar(130, 130, 130)), 3);
	h.addSection(leftColumn0);


	// Création du header du content
	Section* contentHeader0 = new Section(cv::Mat(20, 920, CV_8UC3, Scalar(180, 180, 180)), 4);
	h.addSection(contentHeader0);

	// Création du footer du content
	Section* contentFooter0 = new Section(cv::Mat(20, 920, CV_8UC3, Scalar(220, 220, 220)), 5);
	h.addSection(contentFooter0);

	h.addImage("left", "img/left.jpeg");

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
	int alpha;
	int alphaMax = 10;
	createTrackbar("Feature:\n 0: Erosion \n 1: Dilation", WINDOW_NAME, &alpha, alphaMax);
	while (true)
	{
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

int main(int argc, const char *argv[])
{
	GIMP();
}
