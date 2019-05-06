#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

#include "Section.h"


using namespace std;
using namespace cv;


class Frame
{
private:

	vector<Section*> header;
	vector<Section*> leftColumn;
	vector<Section*> content;
	vector<Section*> rightColumn;
	vector<Section*> footer;

	Size windowSize;

public:

	Mat image;

	Frame();
	Frame(Size _windowSize);
	~Frame();

	void addSection(Section* section);

	void frameToMat(Mat& dest);



};

