#pragma once

#include <opencv2/opencv.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include <stdio.h>
#include <string.h>
#include "tinyfiledialogs.h"
#include <string>
#include <iostream>
#include "Section.h"
#include "Frame.h"
#include "Button.h"

using namespace cv;
using namespace std;

#define WINDOW_NAME "Gimp"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

char const * lTmp;
char const * lTheSaveFileName;
char const * lTheOpenFileName;
char const * lTheSelectFolderName;
char const * lTheHexColor;
char const * lWillBeGraphicMode;
unsigned char lRgbColor[3];
FILE * lIn;
char lBuffer[1024];
char lThePassword[1024];
char const * lFilterPatterns[2] = { "*.jpeg", "*.jpg" };

void init(Frame& h)
{
	// Cr�ation de la section qui sera en haut de l'�cran
	Section* top = new Section(cv::Mat(40, 1000, CV_8UC3, Scalar(100, 100, 100)), 1);
	top->addButton(new Button("export", &exportImg));
	h.addSection(top);

	// Cr�ation de la section qui sera a gauche de l'�cran
	Section* left = new Section(cv::Mat(920, 40, CV_8UC3, Scalar(150, 150, 150)), 2);
	left->addButton(new Button("b", &bright));
	left->addButton(new Button("d", &dark));
	h.addSection(left);

	// Cr�ation de la section qui sera au dessus de la section avec l'image
	Section* contentTop = new Section(cv::Mat(20, 920, CV_8UC3, Scalar(180, 180, 180)), 0);
	h.addSection(contentTop);

	// Cr�ation de la section qui va contenir notre image
	Section* mainSection = new Section(cv::Mat(900, 920, CV_8UC3, Scalar(200, 200, 200)), 0, true);
	mainSection->addImage(imread("img/left.jpeg"));
	h.addSection(mainSection);

	// Cr�ation du Mat qui va contenir l'image repr�sentant la fen�tre
	Mat source = cv::Mat(WINDOW_HEIGHT, WINDOW_WIDTH, CV_8UC3);
	h.frameToMat(source);

	// Cr�ation de la fen�tre
	namedWindow(WINDOW_NAME);
	imshow(WINDOW_NAME, source);
	resizeWindow(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
	cvui::init(WINDOW_NAME);
}

void GIMP()
{
	// Cr�ation de la frame qui va contenir l'ensemble de la fen�tre
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
	//GIMP();
	lTheOpenFileName = tinyfd_openFileDialog(
		"let us read the password back",
		"",
		2,
		lFilterPatterns,
		NULL,
		0);

	if (!lTheOpenFileName)
	{
		tinyfd_messageBox(
			"Error",
			"Open file name is NULL",
			"ok",
			"error",
			1);
		return 1;
	}
	Mat image = imread(lTheOpenFileName, IMREAD_COLOR);

	namedWindow("test", WINDOW_AUTOSIZE);

	// Show our images inside the created windows.
	imshow("test", image);

	// Wait for any keystroke in the window
	waitKey(0);

	//destroy all opened
}
