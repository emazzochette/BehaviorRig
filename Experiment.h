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
			Point CantileverRealSpace;
			Point CantileverImageSpace; // = (621, 365); //in pixel space.  
		} cantileverProperties;

		struct AmbientParameters{
			double temperature;
			double humidity;
		} ambientParameters;
		
		WormAnalysis wormAnalysis;
		ImageControl imageControl;
		DataManagement dataManagement;

		
		//Location of worm head in real space
		Point WormHeadRealSpace;
		//Location of worm target in real space.
		Point WormTargetRealSpace;
		//Location of worm tail in real space.
		Point WormTailRealSpace;
		//Distace to move stage in real space - unit should be micrometer.
		double moveStageXRealSpace;
		double moveStageYRealSpace;
		
		
		//Image dimensions in real space
		Point ImageDimensions;


		ExperimentStruct(void);
	} exp;

	public:
	
	void DefineExpProperties(void);
	void SetUpDataOutput(void);
	int SetUpCamera(void);
	int trackWorm(int n, BackgroundWorker^ worker, DoWorkEventArgs ^ e);



};
