#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

double contrast = 1.0;
Mat src, imBright;
int maxBright = 200;
int brightValue = 100;  

void Bright(int , void*);

int main(int argc, char** argv)
{
    // Read the image file
    src = imread("van_gogh.jpg");
    //image = imread("van_gogh.jpg");
    
    // Check for failure
    if( argc == 2 || !src.data ) {
		printf( " No image data \n " );
		return -1;
	}
    
    //Create and open windows for above images
    namedWindow("Bright", WINDOW_AUTOSIZE);
    
    
    //create track bar
    createTrackbar("Brightness", "Bright", &brightValue, maxBright, Bright);

	Bright(0,0);
   	
    // Wait for any key stroke
	waitKey(0);
	
    return 0;
}

void Bright(int , void*){
	src.convertTo(imBright, src.type(), contrast, brightValue - 100);
    imshow("Bright", imBright);
}
