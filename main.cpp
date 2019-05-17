#pragma once

#include <opencv2/opencv.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"

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
	h.addSection(header0);

	// Création du footer
	Section* footer0 = new Section(cv::Mat(40, 1000, CV_8UC3, Scalar(100, 100, 100)), 1);
	h.addSection(footer0);

	// Création de la colonne de gauche
	Section* left = new Section(cv::Mat(920, 50, CV_8UC3, Scalar(150, 150, 150)), 2);
	//left->addButton(new Button("b", &bright));
	//left->addButton(new Button("d", &dark));
	h.addSection(left);

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
	//cvui::init(WINDOW_NAME);
}

void GIMP()
{
	// Création de la frame qui va contenir l'ensemble de la fenêtre
	h = Frame(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Initialisation de l'interface
	init(h);

	// Boucle principale
	while (true)
	{
		//h.updateAllbuttons();
		//background(Rect(imageX + cX, imageY + cY, WINDOW_WIDTH - x - x2, WINDOW_HEIGHT - y - y2)).copyTo(finalImage(Rect(x, y, WINDOW_WIDTH - x - x2, WINDOW_HEIGHT - y - y2)));
		h.update(cX, cY);

		//cvui::update();
		imshow(WINDOW_NAME, h.getFrame());

		if (waitKey(20) == 27) {
			break;
		}
	}
}

//bool down = false;
//int baseX = 0;
//int baseY = 0;
//int cX = 0;
//int cY = 0;
//int baseImageX = 5000;
//int baseImageY = 5000;
//int imageX = baseImageX;
//int imageY = baseImageY;
//Mat img = imread("img/left.jpeg");
//Mat imageTemp = img.clone();
//Mat background = cv::Mat(10000, 10000, CV_8UC3, Scalar(255, 255, 255));
//Mat finalImage = cv::Mat(WINDOW_HEIGHT, WINDOW_WIDTH, CV_8UC3, Scalar(0, 0, 0));
//
//int x = 20;
//int y = 30;
//int x2 = 35;
//int y2 = 40;
//
//int ix = 50;
//int iy = 50;
//
//
//Size imgSize = Size(img.cols, img.rows);
//
//Size contentSize = Size(WINDOW_WIDTH - x - x2, WINDOW_HEIGHT - y - y2);


//void test()
//{
//
//	img.copyTo(background(Rect(ix+ imageX, iy+ imageY, imgSize.width, imgSize.height )));
//	background(Rect(imageX+cX,imageY+cY, WINDOW_WIDTH - x - x2, WINDOW_HEIGHT - y - y2)).copyTo(finalImage(Rect(x, y, WINDOW_WIDTH - x - x2, WINDOW_HEIGHT - y - y2)));
//	
//	namedWindow(WINDOW_NAME);
//	imshow(WINDOW_NAME, finalImage);
//	resizeWindow(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
//	setMouseCallback(WINDOW_NAME, CallBackFunc, NULL);
//	//cvui::init(WINDOW_NAME);
//	int key;
//
//	while (true)
//	{
//		
//		background(Rect(imageX + cX, imageY + cY, WINDOW_WIDTH - x - x2, WINDOW_HEIGHT - y - y2)).copyTo(finalImage(Rect(x, y, WINDOW_WIDTH - x - x2, WINDOW_HEIGHT - y - y2)));
//
//		imshow(WINDOW_NAME, finalImage);
//		key = waitKey(10);
//		if (key == 27) {
//			break;
//		}
//		if (key == 32) {
//			imageX = baseImageX;
//			imageY = baseImageY;
//		}
//
//	}
//}

int main(int argc, const char *argv[])
{
	GIMP();
	//test();
}
