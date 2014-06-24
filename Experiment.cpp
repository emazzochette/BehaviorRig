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

#include "WormAnalysis.h"
#include "DataManagement.h"

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
	 cantileverProperties.CantileverImageSpace.x = 621;
	 cantileverProperties.CantileverImageSpace.y = 365;

	 ImageDimensions.x = (int)1024*imageControl.UmPerPixel();
	 ImageDimensions.y = (int)768*imageControl.UmPerPixel();


};

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


	exp.dataManagement.CloseDoc();
	

	

}
int Experiment::SetUpCamera(void){
	exp.imageControl.StartCamera();
	exp.imageControl.StartLive();
	return 0;

}
int Experiment::trackWorm(int n, BackgroundWorker^ worker, DoWorkEventArgs ^ e){
	 //Abort the operation if the user has cancelled.
	 //Note that a call to CancelAsync may have set
	 //CancellationPending to true just after the 
	 //last invocation of this method exits, so this
	 //code will not have the oppotunity to set the 
	 //DoWorkEventArgs.Cancel flag to true. This means
	 //the RunWorkerCompletedEventArgs.Cancelled will
	 //not be set to true in your RunWorkerCompleted
	 //event handler. This is a race condition.
	if (worker->CancellationPending )
	{
		e->Cancel = true;
	}
	else
	{
		//exp.imageControl.GetImage();
		//exp.wormAnalysis.WormImages.OriginalImage = exp.imageControl.img;
		//exp.wormAnalysis.FindWorm();
		//do some data output.
		//exp.dataManagement.AppendWormFrameToDisk(WormAnalysis::WormDataStructures WormData, int count, int frameNumber, double xStagePos, double yStagePos, double time);

		worker->ReportProgress( 0 , "Tracker Running");
		Thread::Sleep(5000);
		
	}
	return 0;

}