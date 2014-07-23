#include "StdAfx.h"
#include "ImageControl.h"

//#include "CmdHelper.h"

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)

using namespace _DSHOWLIB_NAMESPACE;
using namespace std;

//ImageControl::ImageControl(void)
//{
//
//}

void ImageControl::StartCamera(void)
{
		InitLibrary();
        //Grabber grabber;
        // Create RGB24 image format in memory.
        //FrameHandlerSink::tFHSPtr sink = FrameHandlerSink::create( DShowLib::eRGB24, 5 );
        sink = FrameHandlerSink::create( DShowLib::eY800, 5 );


        sink->setSnapMode( true );
        grabber.setSinkType( sink );

		
        // Show the device selection dialog
        grabber.showDevicePage();

		//grabber.setVideoFormat("Y800 (96x96-512x384) [Binning 2x]");
        
		
		long val = grabber.getProperty(CameraControl_Exposure);
		tsPropertyRange ExposureRange = grabber.getPropertyRange(CameraControl_Exposure);
		grabber.setProperty(CameraControl_Exposure, false);
		long ExposureValue = -8;
		grabber.setProperty(CameraControl_Exposure,ExposureValue);
		
		//enable overlay for camera.
		grabber.getOverlay()->setEnable(true);
		grabber.getOverlay()->setColorMode(OverlayBitmap::eCOLOR);
		grabber.getOverlay()->setDropOutColor(RGB(0,255,255));

		/*
		tCodecListPtr pCodecs = Codec::getAvailableCodecs();
 
		// Display all codec names on the screen.
		int choice = presentUserChoice( toStringArrayPtrListPtr( pCodecs ) );
		if(choice == -1)
		{
			choice = 2;
		}
		pSink = MediaStreamSink::create(MediaStreamContainer::create( MSC_AviContainer ), pCodecs->at( choice ) );
		//set video file name
		pSink->setFilename( "C:\\Users\\Eileen Mazzochette\\Desktop\\VideoTest");
		//grabber.setSinkType( pSink );
		// The sink is initially paused, so that no video data is written to the file.
		pSink->setSinkMode( GrabberSinkType::ePAUSE );
*/


}
void ImageControl::StartLive(void)
{
	 if( grabber.isDevValid() )
     {
        // Start the camera and show the nice "Active Movie Window"
        grabber.startLive(true);
		FrameTypeInfo info;
		sink->getOutputFrameType( info );

		//Mat img;
		img = cvCreateImage( cvSize(info.dim.cx,info.dim.cy), IPL_DEPTH_8U , 1 );
		grabber.setExternalTrigger(true);
	 }
}
void ImageControl::GetImage()
{
	if( grabber.isDevValid() )
	{
            // Snap an image and save in memory.
            sink->snapImages(1);
            
            if( grabber.getLastError().isError() )
            {
                    printf("Failed to snap an image");
            }
            else
            {
					img.data = (uchar*)sink->getLastAcqMemBuffer()->getPtr();
					frameCount = sink->getFrameCount();				
			}
      }     
}
void ImageControl::StopLive(void)
{
	// Stop the live video
	if(grabber.isLive())
	{
		grabber.stopLive();
		//grabber.closeDev();
		ExitLibrary(); // Tidy up memory.
	}
}
void ImageControl::SaveCurrentFrame(string FileName)
{
	if( grabber.isDevValid() )
	{
            // Snap an image and save in memory.
            sink->snapImages(1);
            
            if( grabber.getLastError().isError() )
            {
                    printf("Failed to snap an image");
            }
            else
            {
					sink->getLastAcqMemBuffer()->save( FileName );
			}

      }
	
	
}
void ImageControl::StartRecord(void)
{
	// Start the sink. The image stream is written to the AVI file.
	if(grabber.isLive())
	{
		//pSink->setSinkMode(GrabberSinkType::eRUN );
	}
}
void ImageControl::StopRecord(void)
{
	// Pause the sink. This stops writing the image stream to the AVI file.
	// A subsequent call to setSinkMode with GrabberSinkType::eRUN as the
	// parameter would restart AVI recording.
	//if(pSink->getSinkMode == GrabberSinkType::eRUN)
	//{
		//pSink->setSinkMode(GrabberSinkType::ePAUSE );
	//}
}

void ImageControl::SetImageDimensions(double scale){
	 
	 xImageDimensions = (int)scale*1024*UmPerPixel();
	 yImageDimensions = (int)scale*768*UmPerPixel();

}