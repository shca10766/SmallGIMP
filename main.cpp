#pragma once

#include <opencv2/opencv.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"


#include <iostream>
#include "Section.h"
#include "Frame.h"
#include "Button.h"

using namespace cv;
using namespace std;

#define WINDOW_NAME "Gimp"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void init(Frame& h)
{
	// Création de la section qui sera en haut de l'écran
	Section* top = new Section(cv::Mat(40, 1000, CV_8UC3, Scalar(100, 100, 100)), 1);
	h.addSection(top);

	// Création de la section qui sera a gauche de l'écran
	Section* left = new Section(cv::Mat(920, 40, CV_8UC3, Scalar(150, 150, 150)), 2);
	left->addButton(new Button("b", &bright));
	left->addButton(new Button("d", &dark));
	h.addSection(left);

	// Création de la section qui sera au dessus de la section avec l'image
	Section* contentTop = new Section(cv::Mat(20, 920, CV_8UC3, Scalar(180, 180, 180)), 0);
	h.addSection(contentTop);

	// Création de la section qui va contenir notre image
	Section* mainSection = new Section(cv::Mat(900, 920, CV_8UC3, Scalar(200, 200, 200)), 0, true);
	mainSection->addImage(imread("img/left.jpeg"));
	h.addSection(mainSection);

	// Création du Mat qui va contenir l'image représentant la fenêtre
	Mat source = cv::Mat(WINDOW_HEIGHT, WINDOW_WIDTH, CV_8UC3);
	h.frameToMat(source);

	// Création de la fenêtre
	namedWindow(WINDOW_NAME);
	imshow(WINDOW_NAME, source);
	resizeWindow(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
	cvui::init(WINDOW_NAME);
}

void GIMP()
{
	// Création de la frame qui va contenir l'ensemble de la fenêtre
	Frame h = Frame(Size(WINDOW_WIDTH, WINDOW_HEIGHT));

	// Initialisation de l'interface
	init(h);

	// Boucle principale
	while (true)
	{
		h.updateAllbuttons();

		cvui::update();
		imshow(WINDOW_NAME, h.screen);

		if (waitKey(20) == 27) {
			break;
		}
	}
}

int main(int argc, const char *argv[])
{
	GIMP();
}
