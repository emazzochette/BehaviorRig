#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)


#include <highgui.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <complex>
#include <ctime>

#include "WormAnalysis.h"
#include "ImageControl.h"
#include "DataManagement.h"

using namespace System;
using namespace System::IO::Ports;
using namespace System::ComponentModel;
using namespace System::Threading;
using namespace System::Text;


using namespace cv;
using namespace std;


class Experiment{

	public:
	//Experiment(void);
	struct doublePoint{
			double x;
			double y;
		};
	
	struct ExperimentStruct{
		public:
		string dataOutputLocation;
		string experimentMode;
		string experimentTitle;
		string otherInfo;

		struct WormProperties{
			string wormStrain;
			string wormTreatments;
			string wormGender;
			string wormAge;
			string percentAgar;
			string foodStatus;
		} wormProperties;

		struct CantileverProperties{
			string serialNumber;
			//inclue control parameters
			double frequency;
			double stiffness;
			double sensitivity;
			//Location of Cantilever in real space
			double xCantileverRealSpace;
			double yCantileverRealSpace;
			Point CantileverImageSpace; // = (621, 365); //in pixel space.  
		} cantileverProperties;

		struct AmbientParameters{
			double temperature;
			double humidity;
		} ambientParameters;
		
		WormAnalysis wormAnalysis;
		ImageControl imageControl;
		DataManagement dataManagement;
		
		//Distace to move stage in real space - unit should be micrometer.
		doublePoint WormHeadRealSpace, WormTailRealSpace, WormTargetRealSpace, moveStageRealSpace;
		
		double timeStamp;
		int processedFrameCount;
		int cameraFrameNumber;
	
		string inputMode;

		VideoWriter videoWriter;
		VideoCapture videoCapture;
		string videoFilename;
		Mat currentVideoFrame;

		double imageScale;

	
		ExperimentStruct(void);
	} exp;




	public:
	
	int OpenVideo(string);
	int getImage(string);

	int getNextVideoFrame(void);
	void DefineExpProperties(void);
	void SetUpDataOutput(void);
	int WriteTimingDataToDisk(void);
	void WriteCurrentFrameData(WormAnalysis::WormDataStructures);
	int SetUpCamera(void);
	doublePoint DetermineStageMovement(double, double);
	void EndExperiment(void);


};
