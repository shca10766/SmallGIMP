#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void ResizeFunction(Mat img, int ColumnOfNewImage, int RowsOfNewImage) {
	Mat Resized;
	resize(img, Resized, Size(ColumnOfNewImage, RowsOfNewImage));
}
