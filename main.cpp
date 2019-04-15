#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img = imread("lenna.jpg");
	namedWindow("Original");
	imshow("Original", img);
}