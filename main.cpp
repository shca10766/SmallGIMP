#include <opencv2/opencv.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#include <iostream>

#include "Section.h"
#include "Frame.h"

using namespace cv;
using namespace std;

#define WINDOW_NAME "Gimp"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080


//void someFunction(Mat & image)
//{
//	for (int y = 0; y < image.rows; y++)
//	{
//		for (int x = 0; x < image.cols; x++)
//		{
//			image.at<Vec3b>(Point(x, y)) = image.at<Vec3b>(Point(x, y)) * 2;
//		}
//	}
//}
//
//void merge(Mat & image, Mat& image2, Mat & outputImage)
//{
//	for (int y = 0; y < image.rows; y++)
//	{
//		for (int x = 0; x < image.cols; x++)
//		{
//			outputImage.at<Vec3b>(Point(x, y)) = image.at<Vec3b>(Point(x, y));
//			outputImage.at<Vec3b>(Point(x + image.cols, y)) = image2.at<Vec3b>(Point(x, y));
//		}
//	}
//}
//
//void mainFunction()
//{
//
//	Mat myImage = imread("img/left.jpeg");
//	Mat myImageCopy = myImage;
//
//
//	Mat concat(myImage.rows, myImage.cols*2, CV_8UC3,Scalar(0,0,0));
//
//	merge(myImage , myImage.clone(), concat);
//	myImage = concat(cv::Rect(0, 0, myImage.cols, myImage.rows));
//	myImageCopy = concat(cv::Rect(myImage.cols, 0, myImage.cols, myImage.rows));
//
//	imshow("myImage", myImage);
//	imshow("myImageCopy", myImageCopy);
//	imshow("concat", concat);
//
//	someFunction(myImage);
//
//	imshow("myImageAfter", myImage);
//	imshow("myImageCopyAfter", myImageCopy);
//	imshow("concatAfter", concat);
//	waitKey(0);
//}


int main(int argc, const char *argv[])
{
	Frame h = Frame(Size(WINDOW_WIDTH,WINDOW_HEIGHT));

	h.addSection(new Section(cv::Mat(40, 1000, CV_8UC3, Scalar(100, 0, 0)), 1));
	h.addSection(new Section(cv::Mat(10, 1000, CV_8UC3, Scalar(200, 0, 0)), 1));
	h.addSection(new Section(cv::Mat(920, 40, CV_8UC3, Scalar(0, 100, 0)), 2));
	h.addSection(new Section(cv::Mat(920, 20, CV_8UC3, Scalar(100, 100, 0)), 2));
	h.addSection(new Section(cv::Mat(20, 920, CV_8UC3, Scalar(100, 200, 0)), 0));

	Section* mainSection =new Section(cv::Mat(900, 920, CV_8UC3, Scalar(200, 200, 200)), 0, true);
	mainSection->addImage(imread("img/left.jpeg"));
	h.addSection(mainSection);

	h.addSection(new Section(cv::Mat(920, 20, CV_8UC3, Scalar(100, 100, 150)), 3));

	Mat source = cv::Mat(WINDOW_HEIGHT, WINDOW_WIDTH, CV_8UC3);
	h.frameToMat(source);

	namedWindow(WINDOW_NAME);
	imshow(WINDOW_NAME, source);
	resizeWindow(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
	cvui::init(WINDOW_NAME);

	Mat image = h.image;
	while (true)
	{
		if (cvui::button(source, 110, 80, "")) {
			image.convertTo(image, image.type(), 1.25, 20);
		}

		if (cvui::button(source, 210, 80, "Darken")) {
			image.convertTo(image, image.type(), 0.8, -20);
		}

		cvui::update();
		imshow(WINDOW_NAME, source);

		if (waitKey(20) == 27) {
			break;
		}
	}
}