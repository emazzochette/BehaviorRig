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


	//exp.dataManagement.CloseDoc();
	

	

}
void Experiment::WriteCurrentFrameData(array<double>^ wormDataArray, double xPosition, double yPosition){
	exp.dataManagement.AppendWormFrameToDisk(wormDataArray, xPosition, yPosition); 

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
	array<double>^ dataArray = gcnew array<double>{1,2,3,4,5,6,7,8,9};
	//int i =1;
	for (int i=1; i<n+1; i++)
	{
	
		if (worker->CancellationPending )
		{
			e->Cancel = true;
		}
		else
		{
		
		//do some data output.
		//exp.dataManagement.AppendWormFrameToDisk(WormAnalysis::WormDataStructures WormData, int count, int frameNumber, double xStagePos, double yStagePos, double time);
		
	
			exp.imageControl.GetImage();
			exp.wormAnalysis.WormImages.OriginalImage = exp.imageControl.img;
			//exp.wormAnalysis.FindWorm();
			exp.wormAnalysis.WormData.Target.x = 2;
			exp.wormAnalysis.WormData.Target.y = 3;
			exp.wormAnalysis.WormData.Head.x = 44;
			exp.wormAnalysis.WormData.Head.y = 55;
			exp.wormAnalysis.WormData.Tail.x = 666;
			exp.wormAnalysis.WormData.Tail.y = 777;

			dataArray[0] = 0; //Time Stamp
			dataArray[1] = i; //Processed Frame Count
			dataArray[2] = exp.imageControl.frameCount; //Frame Number
			dataArray[3] = (double)exp.wormAnalysis.WormData.Target.x; //Target Position X
			dataArray[4] = (double)exp.wormAnalysis.WormData.Target.y;
			dataArray[5] = (double)exp.wormAnalysis.WormData.Head.x;
			dataArray[6] = (double)exp.wormAnalysis.WormData.Head.y;
			dataArray[7] = (double)exp.wormAnalysis.WormData.Tail.x;
			dataArray[8] = (double)exp.wormAnalysis.WormData.Tail.y;

			worker->ReportProgress( 0 , dataArray);
			Thread::Sleep(2000);
		}
		
		
	}
	return 0;

}

void Experiment::EndExperiment(void){

	exp.dataManagement.CloseDoc();
	exp.imageControl.StopLive();

}