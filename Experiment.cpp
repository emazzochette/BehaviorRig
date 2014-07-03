#include "StdAfx.h"
#include "Experiment.h"

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)


#include <highgui.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <complex>
#include <ctime>
#include <string.h>
#include <map>

#include "WormAnalysis.h"
#include "DataManagement.h"


using namespace std;
using namespace TICTOC;

using namespace System;
using namespace System::IO::Ports;
using namespace System::ComponentModel;
using namespace System::Threading;
using namespace System::Text;

//Experiment::Experiment(void)
//{
	//ExperimentStruct;
//}
Experiment::ExperimentStruct::ExperimentStruct(void){
	// mageScale = 0.75;
	 
	// cantileverProperties.CantileverImageSpace.x= 621*imageScale ;
	// cantileverProperties.CantileverImageSpace.y = 365*imageScale;


	 
};

int Experiment::OpenVideo(string videoFilename){

	exp.videoCapture.open(videoFilename);
	if(exp.videoCapture.isOpened())
		return 0;
	else
		return -1;

}

int Experiment::getImage(string imageFilename){
	exp.currentVideoFrame = imread(imageFilename);
	if (exp.currentVideoFrame.empty())
		return -1;
	else
		return 0;
}

int Experiment::getNextVideoFrame(void){

	exp.videoCapture >> exp.currentVideoFrame;
	if (exp.currentVideoFrame.empty())
		return -1;
	else
		return 0;
}
void Experiment::DefineExpProperties(void){
		exp.dataOutputLocation = "C:\\Users\\Eileen Mazzochette\\Desktop\\TestFolder\\";
		exp.experimentMode = "ForceClamp";
		exp.experimentTitle = "TitleTest";
		exp.otherInfo = "other info test";

		exp.wormProperties.wormStrain = "N2";
		exp.wormProperties.wormTreatments = "none";
		exp.wormProperties.wormGender = "H";
		exp.wormProperties.wormAge = "L4";
		exp.wormProperties.percentAgar = "2%";
		exp.wormProperties.foodStatus = "off food";

		exp.cantileverProperties.serialNumber = "AAAA####";
		exp.cantileverProperties.frequency = 0;
		exp.cantileverProperties.stiffness = 0;
		exp.cantileverProperties.sensitivity = 0;

		exp.ambientParameters.temperature = 22;
		exp.ambientParameters.humidity = 25;

		exp.cantileverProperties.CantileverImageSpace.x = 621*exp.imageScale;
		exp.cantileverProperties.CantileverImageSpace.y = 365*exp.imageScale;
}
void Experiment::SetUpDataOutput(void){


	exp.dataManagement.SetUpWriteToDisk(exp.dataOutputLocation.c_str(), exp.experimentTitle.c_str());//,  MemStorage* Mem);
	exp.dataManagement.WriteStringToDisk("Experiment Title",exp.experimentTitle);
	exp.dataManagement.WriteStringToDisk("Experiment Mode",exp.experimentMode);
	exp.dataManagement.WriteStringToDisk("Other Experiment Info", exp.otherInfo);

	exp.dataManagement.StartNode("Worm Properties");
	exp.dataManagement.WriteStringToDisk("Worm Strain", exp.wormProperties.wormStrain);
	exp.dataManagement.WriteStringToDisk("Worm Treatments", exp.wormProperties.wormTreatments);
	exp.dataManagement.WriteStringToDisk("Worm Gender", exp.wormProperties.wormGender);
	exp.dataManagement.WriteStringToDisk("Worm Age", exp.wormProperties.wormAge);
	exp.dataManagement.WriteStringToDisk("Percent Agar", exp.wormProperties.percentAgar);
	exp.dataManagement.WriteStringToDisk("Food Status", exp.wormProperties.foodStatus);
	exp.dataManagement.EndNode();

	exp.dataManagement.StartNode("Cantilever Properties");
	exp.dataManagement.WriteStringToDisk("Serial Number",exp.cantileverProperties.serialNumber);
	exp.dataManagement.WriteDoubleToDisk("Resonant Frequency",exp.cantileverProperties.frequency);
	exp.dataManagement.WriteDoubleToDisk("Stiffness",exp.cantileverProperties.stiffness);
	exp.dataManagement.WriteDoubleToDisk("Sensitivity",exp.cantileverProperties.sensitivity);
	//exp.dataManagement.WritePointToDisk("Cantilever Image Space", exp.cantileverProperties.CantileverImageSpace);
	exp.dataManagement.EndNode();
	
	exp.dataManagement.StartNode("Ambient Parameters");
	exp.dataManagement.WriteDoubleToDisk("Temperature", exp.ambientParameters.temperature);
	exp.dataManagement.WriteDoubleToDisk("Humidity", exp.ambientParameters.humidity);
	exp.dataManagement.EndNode();


	
	//Set up video writer
	Size frameSize = Size(1024*exp.imageScale, 768*exp.imageScale);
	string FilenameTest = std::string(exp.dataManagement.DataWriter.videoFilename);
	double FPS = 2;
	int codec = -1; 
	exp.videoWriter.open(FilenameTest, codec, FPS, frameSize, true);
	
	if (exp.videoWriter.isOpened())
		cout << "I'm open";
	
	

}

int Experiment::WriteTimingDataToDisk(void){
	//std::map <std::string, struct TICTOC::_tictoc_data> tt = TICTOC::timer().generateDataOutput();
	//map<string, TICTOC::_tictoc_data>::iterator it;
	//const pair<string, _tictoc_data> *p;
 //   for (it = tt.begin(); it != tt.end(); ++it) {
 //       
	//	exp.dataManagement.StartNode("TimingInfo");
	//	//exp.dataManagement.WriteStringToDisk("name", it->first);
	//	//exp.dataManagement.WriteDoubleToDisk("ncalls", it.second.ncalls);
	//	exp.dataManagement.EndNode();


	///*	DataWriter.fs << "TimingInfo" << "{" ;
	//	DataWriter.fs  << "  name: " << it.first;
	//	DataWriter.fs  << "  ncalls: " << it.second.ncalls;
	//	DataWriter.fs  << "  totaltime: " << (1.0 * it.second.totaltime) / tictoc::TICKS_PER_SEC ;
	//	DataWriter.fs  << "  maxtime: " << (1.0 * it.second.maxtime) / tictoc::TICKS_PER_SEC ;
	//	DataWriter.fs  << "  mintime: " << (1.0 * it.second.mintime) / tictoc::TICKS_PER_SEC ;
	//	DataWriter.fs  << "  avg time: " << (1.0 * itp.second.totaltime) / (p.second.ncalls *tictoc::TICKS_PER_SEC);
	//	DataWriter.fs  << "  numblowntics: " << it.second.numblowntics;
	//	DataWriter.fs << "}";*/
 //       
 //   }
	return 0;
}
void Experiment::WriteCurrentFrameData(vector<double> wormDataArray, double xPosition, double yPosition, WormAnalysis::WormDataStructures wormData){
	exp.dataManagement.AppendWormFrameToDisk(wormDataArray, xPosition, yPosition, wormData); 

}
int Experiment::SetUpCamera(void){
	exp.imageControl.StartCamera();
	exp.imageControl.StartLive();
	exp.imageControl.SetImageDimensions(exp.imageScale);
	return 0;

}


Experiment::doublePoint Experiment::DetermineStageMovement(double xTargetImageSpace, double yTargetImageSpace){

		////Determine how far stage has to move
		doublePoint MoveStage;

		MoveStage.x = -(exp.cantileverProperties.CantileverImageSpace.x - xTargetImageSpace)*(exp.imageControl.UmPerPixel()/exp.imageScale);
		MoveStage.y = (exp.cantileverProperties.CantileverImageSpace.y - yTargetImageSpace)*(exp.imageControl.UmPerPixel()/exp.imageScale);

		//Translate stage movement to now previous image
		//exp.wormAnalysis.PreviousWormData.Head.x = (int)((exp.xWormHeadRealSpace - exp.moveStageXRealSpace)*exp.imageControl.PixelsPerUm());
		//exp.wormAnalysis.PreviousWormData.Head.y = (int)((exp.yWormHeadRealSpace - exp.moveStageYRealSpace)*exp.imageControl.PixelsPerUm());
		//exp.wormAnalysis.PreviousWormData.Tail.x = (int)((exp.xWormTailRealSpace - exp.moveStageXRealSpace)*exp.imageControl.PixelsPerUm());
		//exp.wormAnalysis.PreviousWormData.Tail.y = (int)((exp.yWormTailRealSpace - exp.moveStageYRealSpace)*exp.imageControl.PixelsPerUm());
		exp.wormAnalysis.PreviousWormData.Target.x = (int)(xTargetImageSpace - (MoveStage.x*(exp.imageScale/exp.imageControl.PixelsPerUm())));
		exp.wormAnalysis.PreviousWormData.Target.y = (int)(yTargetImageSpace + (MoveStage.y*(exp.imageScale/exp.imageControl.PixelsPerUm())));
		
		return MoveStage;
}

void Experiment::EndExperiment(void){

	exp.dataManagement.WriteStringToDisk("TimingData", TICTOC::timer().generateReportCstr());

	exp.dataManagement.CloseDoc();
	exp.videoWriter.release();
	//exp.imageControl.StopLive();

}