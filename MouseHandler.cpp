//#include "MouseHandler.h"
//
//
//
//MouseHandler::MouseHandler(Frame* _frame,String name)
//{
//	frame = _frame;
//	setMouseCallback(name, CallBackFunc, this);
//	bool down = false;
//	int initialX = 0;
//	int initialY = 0;
//	int cX = 0;
//	int cY = 0;
//}
//
//
//MouseHandler::~MouseHandler()
//{
//}
//
//void CallBackFunc(int event, int x, int y, int flags, void* userdata)
//{
//	Mat image = frame->getImage();
//	if (event == EVENT_LBUTTONDOWN)
//	{
//		down = true;
//		initialX = x;
//		initialY = y;
//	}
//	else if (event == EVENT_LBUTTONUP)
//	{
//		frame->addToBackgroundPos(cX, cY);
//		cX = 0;
//		cY = 0;
//		down = false;
//	}
//	else if (event == EVENT_MOUSEMOVE)
//	{
//		if (down)
//		{
//			cX = initialX - x;
//			cY = initialY - y;
//		}
//	}
//	//else if (event == EVENT_MOUSEWHEEL)
//	//{
//	//	int d = getMouseWheelDelta(flags);
//	//	if (d > 0)
//	//	{
//	//		imgSize = Size(imgSize.width*1.05, imgSize.height*1.05);
//	//	}
//	//	else
//	//	{
//	//		imgSize = Size(imgSize.width*0.95, imgSize.height*0.95);
//	//	}
//	//	resize(img, imageTemp, imgSize);
//	//	background.setTo(Scalar(255, 255, 255));
//	//	imageTemp.copyTo(background(Rect(ix + baseImageX, iy + baseImageY, imgSize.width, imgSize.height)));
//	//}
//}
