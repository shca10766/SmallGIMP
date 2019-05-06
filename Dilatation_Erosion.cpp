#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/// Global variables
Mat erosion_dst, dilation_dst;

int elem = 0;
int sizeF = 0;
int feature = 0;
int const max_feature = 1;
int const max_elem = 2;
int const max_kernel_size = 21; 

/** Function Headers */
void Erosion( int, void* );
void Dilation( int, void* );

/** @function main */
void dila_Ero(Mat &src)
{

  if( !src.data )
  { return -1; }

  /// Create windows
  namedWindow( "Demo");

  createTrackbar( "Feature:\n 0: Erosion \n 1: Dilation", "Demo", &feature, max_feature);
  
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Demo", &elem, max_elem);

  createTrackbar( "Kernel size:\n 2n +1", "Demo", &sizeF, max_kernel_size);
  
  while (true)
	{
		int type;
  		if( elem == 0 ){ type = MORPH_RECT; }
  		else if( elem == 1 ){ type = MORPH_CROSS; }
  		else if( elem == 2) { type = MORPH_ELLIPSE; }

  		Mat element = getStructuringElement( type,
                                       Size( 2*sizeF + 1, 2*sizeF+1 ),
                                       Point( sizeF, sizeF ) );
        
        if (feature == 0) {
        	erode( src, erosion_dst, element );
        	imshow( "Demo", erosion_dst);
        }
        else if (feature == 1) {
        	dilate( src, dilation_dst, element );
        	imshow( "Demo", dilation_dst);
        }

		if (waitKey(20) == 27) {
			break;
		}
	}
}
