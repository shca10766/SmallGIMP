#include "imageFunction.h"

#define WINDOW_NAME "ImageEditor"

// to get the image displayed :
//	Mat img;
//	frame.getImage(img);

// to update the view of the image:
// frame.updateBackground();

// to "save" the modification of the image in the program, so that the next getImage will send the modified image:
// frame.modifyImage(img);

Mat img;
Mat imgCopy;
Mat imgSent;

double alpha = 1;
double beta = 0;
void brightnessCallback(Frame &frame,double value, int id)
{
	if (id == 1)
		alpha = value;
	else
		beta = value;
	imgCopy.convertTo(imgSent, img.type(),alpha, beta);
	frame.setTempImage(imgSent);
}

void brightness(Frame &frame)
{
	close(frame);
	alpha = 1;
	beta = 0;
	frame.updateImage();
	frame.getImage(img);
	imgCopy = img.clone();
	imgSent = imgCopy.clone();
	Section* rightColumn0 = new Section(cv::Mat(920, 250, CV_8UC3, Scalar(240, 240, 240)), 3);
	rightColumn0->addTrackbar(new Trackbar("alpha", 0, 2, 0.1, 2, 1,&brightnessCallback,1));
	rightColumn0->addTrackbar(new Trackbar("beta", -100, 100, 5, 50, 0,&brightnessCallback,2));
	rightColumn0->addButton(new Button("save", &saveImage));
	rightColumn0->addButton(new Button("cancel", &close));

	frame.addSection(rightColumn0);
	frame.frameToMat();
}

void saveImage(Frame & frame)
{
	frame.modifyImage(imgSent);
	close(frame);
}

void close(Frame & frame)
{
	frame.updateImage();
	frame.updateBackground();
	while (frame.rightSectionLength() > 0)
		frame.removeLastRightSection();
}

void save(Frame & frame)
{

	Mat img;
	frame.getImage(img);

	char const * lFilterPatterns[2] = { "*.jpeg", "*.jpg" };
	char const * lTheSaveFileName;

	lTheSaveFileName = tinyfd_saveFileDialog(
		"let us save this Image",
		"test.jpg",
		2,
		lFilterPatterns,
		NULL);
	if (!lTheSaveFileName)
	{
		tinyfd_messageBox(
			"Error",
			"Save file name is NULL",
			"ok",
			"error",
			1);
		return;
	}
	imwrite(lTheSaveFileName, img);

}

void switchImage(Frame & frame)
{
	close(frame);
	frame.updateBackground();
}

void openImage(Frame & frame)
{
	close(frame);
	char const * lFilterPatterns[2] = { "*.jpeg", "*.jpg" };

	char const * lTheOpenFileName = tinyfd_openFileDialog(
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
		return;
	}
	string name = "image" + to_string(frame.numberOfImages());
	frame.addImage(name, lTheOpenFileName);

}

//----------------------------------------------CANNY EDGE DETECTION-------------------------------------------------//

/// Global variables

Mat img_edge;
Mat detected_edges;

int edgeThresh = 1;
int const max_lowThreshold = 100;
int r = 3;
int kernel_size = 3;

void cannyEdgeCallBack(Frame &frame, double lowThreshold, int id)
{

	if (lowThreshold == 0) {
		frame.setTempImage(imgCopy);
		return;
	}

	/// Reduce noise with a kernel 3x3
	blur(img_edge, detected_edges, Size(3, 3));

	/// Canny detector
	cout << "bonjour" << lowThreshold << endl;
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*r, kernel_size);

	/// Using Canny's output as a mask, we display our result
	imgSent = Scalar::all(0);

	imgCopy.copyTo(imgSent, detected_edges);
	frame.setTempImage(imgSent);
}

void cannyEdgeDetection(Frame& frame)
{
	close(frame);
	frame.updateImage();
	frame.getImage(img);
	imgCopy = img.clone();
	imgSent = imgCopy.clone();
	/// Convert the image to grayscale
	cvtColor(imgCopy, img_edge, COLOR_BGR2GRAY);
	Section* rightColumn0 = new Section(cv::Mat(920, 250, CV_8UC3, Scalar(240, 240, 240)), 3);
	rightColumn0->addTrackbar(new Trackbar("t", 0, 100, 1, 10, 0, &cannyEdgeCallBack, 1));
	rightColumn0->addButton(new Button("save", &saveImage));
	rightColumn0->addButton(new Button("cancel", &close));

	frame.addSection(rightColumn0);
	frame.frameToMat();
}


/*

#include "imageFunction.h"
/// -----------------------------------Global variables------------------------------------------

Mat originImage;

int elem = 0;
int sizeF = 0;
int feature = 0;
int const max_feature = 1;
int const max_elem = 2;
int const max_kernel_size = 21;
Stitcher::Mode mode = Stitcher::PANORAMA;
vector<Mat> imgs;
String face_cascade_name = "haarcascade_frontalface_alt2.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
string window_name = "Capture - Face detection";
RNG rng(12345);



/// -------------------------------------------BRIGHTNESS FUNCTIONS-------------------------------------------

void bright(Mat & img)
{
	img.convertTo(img, img.type(), 1, 20);
}



void dark(Mat & img)
{
	img.convertTo(img, img.type(), 1, -20);
}




//------------------------------------------DILATATION EROSION-------------------------------------------------//

void dila_Ero(Mat &src)

{
	/// Create windows

	//namedWindow("Demo");
createTrackbar("Feature:\n 0: Erosion \n 1: Dilation", "Demo", &feature, max_feature);
createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Demo", &elem, max_elem);
createTrackbar("Kernel size:\n 2n +1", "Demo", &sizeF, max_kernel_size);

	while (true)
	{
		int type;

		if (elem == 0) { type = MORPH_RECT; }

		else if (elem == 1) { type = MORPH_CROSS; }

		else if (elem == 2) { type = MORPH_ELLIPSE; }



		Mat element = getStructuringElement(type,Size(2 * sizeF + 1, 2 * sizeF + 1),Point(sizeF, sizeF));

		if (feature == 0) {

			erode(originImage, src, element);


		} else if (feature == 1) {

			dilate(originImage, src, element);


		}
		

	}

}
#include <iostream> 

#include <fstream> 



//----------------------------------------PANORAMA-------------------------------------------------//





bool checkInteriorExterior(const cv::Mat &mask, const cv::Rect &croppingMask,int &top, int &bottom, int &left, int &right)
{
	// Return true if the rectangle is fine as it is
	bool result = true;
	cv::Mat sub = mask(croppingMask);
	int x = 0;
	int y = 0;
	// Count how many exterior pixels are, and choose that side for
	// reduction where mose exterior pixels occurred
	int top_row = 0;
	int bottom_row = 0;
	int left_column = 0;
	int right_column = 0;
	for (y = 0, x = 0; x < sub.cols; ++x)
	{
		// If there is an exterior part in the interior we have
		// to move the top side of the rect a bit to the bottom
		if (sub.at<char>(y, x) == 0)
		{
			result = false;
			++top_row;
		}
	}

	for (y = (sub.rows - 1), x = 0; x < sub.cols; ++x)
	{
		// If there is an exterior part in the interior we have
		// to move the bottom side of the rect a bit to the top
		if (sub.at<char>(y, x) == 0)
		{
			result = false;
			++bottom_row;
		}
	}

	for (y = 0, x = 0; y < sub.rows; ++y)
	{
		// If there is an exterior part in the interior
		if (sub.at<char>(y, x) == 0)
		{
			result = false;
			++left_column;
		}
	}

	for (x = (sub.cols - 1), y = 0; y < sub.rows; ++y)
	{
		// If there is an exterior part in the interior
		if (sub.at<char>(y, x) == 0)
		{
			result = false;
			++right_column;
		}
	}

	// The idea is to set `top = 1` if it's better to reduce
	// the rect at the top than anywhere else.
	if (top_row > bottom_row)
	{
		if (top_row > left_column)
		{
			if (top_row > right_column)
			{
				top = 1;
			}
		}
	}
	else if (bottom_row > left_column)
	{
		if (bottom_row > right_column)
		{
			bottom = 1;
		}
	}

	if (left_column >= right_column)
	{
		if (left_column >= bottom_row)
		{
			if (left_column >= top_row)
			{
				left = 1;
			}
		}
	}

	else if (right_column >= top_row)
	{
		if (right_column >= bottom_row)
		{
			right = 1;
		}
	}
	return result;
}



bool compareX(cv::Point a, cv::Point b)
{
	return a.x < b.x;
}



bool compareY(cv::Point a, cv::Point b)
{
	return a.y < b.y;
}



void crop(cv::Mat &source)
{
	cv::Mat gray;
	source.convertTo(source, CV_8U);
	cvtColor(source, gray, cv::COLOR_RGB2GRAY);

	// Extract all the black background (and some interior parts maybe)
	cv::Mat mask = gray > 0;

	// now extract the outer contour
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, cv::Point(0, 0));
	cv::Mat contourImage = cv::Mat::zeros(source.size(), CV_8UC3);;

	// Find contour with max elements
	int maxSize = 0;
	int id = 0;

	for (int i = 0; i < contours.size(); ++i)
	{
		if (contours.at((unsigned long)i).size() > maxSize)
		{
			maxSize = (int)contours.at((unsigned long)i).size();
			id = i;
		}
	}



	// Draw filled contour to obtain a mask with interior parts
	cv::Mat contourMask = cv::Mat::zeros(source.size(), CV_8UC1);
	drawContours(contourMask, contours, id, cv::Scalar(255), -1, 8, hierarchy, 0, cv::Point());



	// Sort contour in x/y directions to easily find min/max and next

	std::vector<cv::Point> cSortedX = contours.at((unsigned long)id);
	std::sort(cSortedX.begin(), cSortedX.end(), compareX);
	std::vector<cv::Point> cSortedY = contours.at((unsigned long)id);
	std::sort(cSortedY.begin(), cSortedY.end(), compareY);


	int minXId = 0;
	int maxXId = (int)(cSortedX.size() - 1);
	int minYId = 0;
	int maxYId = (int)(cSortedY.size() - 1);

	cv::Rect croppingMask;



	while ((minXId < maxXId) && (minYId < maxYId))

	{
		cv::Point min(cSortedX[minXId].x, cSortedY[minYId].y);
		cv::Point max(cSortedX[maxXId].x, cSortedY[maxYId].y);
		croppingMask = cv::Rect(min.x, min.y, max.x - min.x, max.y - min.y);
		// Out-codes: if one of them is set, the rectangle size has to be reduced at that border

		int ocTop = 0;
		int ocBottom = 0;
		int ocLeft = 0;
		int ocRight = 0;
		bool finished = checkInteriorExterior(contourMask, croppingMask, ocTop, ocBottom, ocLeft, ocRight);

		if (finished == true)
		{
			break;
		}

		// Reduce rectangle at border if necessary

		if (ocLeft)
		{
			++minXId;
		}

		if (ocRight)
		{
			--maxXId;
		}

		if (ocTop)
		{
			++minYId;
		}

		if (ocBottom)
		{
			--maxYId;
		}

	}

// Crop image with created mask

source = source(croppingMask);


}



void Stitch(vector<Mat> &images, Mat &src)
{
	// Get all the images that need to be  
	// stitched as arguments from command line  
	for (int i = 0; i < images.size(); i++) {
		if (images[i].empty())
		{
			// Exit if image is not present 
			cout << "Can't read image '" << "'\n";
			return;
		}
		imgs.push_back(images[i]);;
	}

	// Define object to store the stitched image 
	Mat pano;

	// Create a Stitcher class object with mode panoroma 
	Ptr<Stitcher> stitcher = Stitcher::create(mode);

	// Command to stitch all the images present in the image array 
	Stitcher::Status status = stitcher->stitch(imgs, pano);

	if (status != Stitcher::OK)
	{
		// Check if images could not be stiched 
		// status is OK if images are stiched successfully 
		cout << "Can't stitch images\n";
		return;
	}

	// Store a new image stiched from the given  
	//set of images as "result.jpg" 
	imwrite("result.jpg", pano);
	src = pano;
	// Show the result 
	//imshow("Result", pano);
	crop(pano);

}




//----------------------------------------------FACE RECOGNITION-------------------------------------------------//



void detectAndDisplay(Mat& frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));


	for (size_t i = 0; i < faces.size(); i++)

	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(frame, center, radius, Scalar(255, 0, 0), 4, 8, 0);
		}
	}
}


void faceDetection(Mat& src)
{
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading\n"); return; };
	if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)Error loading\n"); return; };
	detectAndDisplay(src);
}

*/
