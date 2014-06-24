#pragma once 

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

#include "tisudshl.h" 


using namespace _DSHOWLIB_NAMESPACE;
using namespace std;

class ImageControl
{
public:
	Grabber grabber;
	FrameHandlerSink::tFHSPtr sink;
	//tMediaStreamSinkPtr pSink;
	cv::Mat img;
	unsigned int frameCount;


public:
	void StartCamera(void);
	void StartLive(void);
	void StopLive(void);
	void GetImage(void);
	void SaveCurrentFrame(string FileName);
	void StartRecord(void);
	void StopRecord(void);

	static double PixelsPerUm()
		{ return 0.567369167; }
	static double UmPerPixel()
		{ return 1.7633422; }



	

};
