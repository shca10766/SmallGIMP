#include <stdio.h>
#include <string.h>
#include "tinyfiledialogs.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main()
{
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

	lTheOpenFileName = tinyfd_openFileDialog(
		"let us read the password back",
		"",
		2,
		lFilterPatterns,
		NULL,
		0);

	if (! lTheOpenFileName)
	{
		tinyfd_messageBox(
			"Error",
			"Open file name is NULL",
			"ok",
			"error",
			1);
		return 1 ;
	}
	
	Mat image = imread(lTheOpenFileName , IMREAD_COLOR );
	
	namedWindow( "test", WINDOW_AUTOSIZE );

    // Show our images inside the created windows.
    imshow( "test",  image );

    // Wait for any keystroke in the window
    waitKey(0);

    //destroy all opened windows
	destroyAllWindows();
}

