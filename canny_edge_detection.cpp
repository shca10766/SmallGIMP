#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat src, src_gray;
Mat dst, detected_edges;

int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";

static void CannyThreshold(int, void*) {
    blur( src_gray, detected_edges, Size(3,3) );
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
    dst = Scalar::all(0);
    src.copyTo( dst, detected_edges);
    imshow( window_name, dst );
}

int main( int argc, char** argv ) {
  src = imread( "img/van_gogh.jpg", IMREAD_COLOR );
  if( src.empty() ) {
    std::cout << "Could not open or find the image!\n" << std::endl;
    return -1;
  }
  
  dst.create( src.size(), src.type() );
  cvtColor( src, src_gray, COLOR_BGR2GRAY );
  namedWindow( window_name);
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
  CannyThreshold(0, 0);
  waitKey(0);
  return 0;
}
