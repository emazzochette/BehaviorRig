#include "StdAfx.h"
#include "DataManagement.h"

//#pragma managed(push,off)
#include <cv.h>
//#pragma managed(pop)
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
//#include <opencv2/highgui/highgui.hpp>
#include <highgui.h>
#include "WormAnalysis.h"
#include "Experiment.h"
#include <string.h>
#include <stdio.h>

//#include <iostream>
//#include <fstream>


using namespace cv;
using namespace std;

//DataManagement::DataManagement(void)
//{
//}

DataManagement::WriteOutStruct::WriteOutStruct(void){
	//WriteOut* DataWriter = (WriteOut*) malloc(sizeof(WriteOut));
	//DataWriter->error = 0;
	//DataWriter->filename = NULL;
	//DataWriter->fs = NULL;
	//return DataWriter;
	fs = NULL;
	error = 0;
	filename = NULL;
	videoFilename = NULL;
}



char* DataManagement::CreateFileName(const char* dir, const char* core, const char* suffix)
{
	//Prepare string with time stamp:
	char timestamp[30];
	time_t curtime;
	struct tm *loctime;
	//Get the current time
	curtime = time(NULL);
	//convert to local time
	loctime = localtime (&curtime);
	strftime(timestamp,30,"%Y%m%d_%H%M_",loctime);
	//Allocate memory for filename:
	char* filename = (char*) malloc(strlen(timestamp)+ strlen(dir)+strlen(core)+strlen(suffix)+1);

	strcpy(filename,dir);
	strcat(filename,timestamp);
	strcat(filename,core);
	strcat(filename,suffix);

	//free(&timestamp);
	return filename;
}

//void DestroyFileName(char** filename)
//{
//	free(*filename);
//	*filename=NULL;
//}
void DataManagement::SetUpWriteToDisk(const char* dirfilename, const char* outfilename)//,  MemStorage* Mem)
{
		
	//Create filename
	char* YAMLDataFileName = CreateFileName(dirfilename, outfilename,".yaml");
	char* VideoDataFileName = CreateFileName(dirfilename, outfilename, ".avi");
	//char* ImageDataFileNAme = CreateFileName(dirfilename, outfilename, ".tiff");

	//Open YAML Data File for writing //
	DataWriter.fs.open(YAMLDataFileName, FileStorage::WRITE );
	//DataWriter.fs << "write data" << 5;
	if (~DataWriter.fs.isOpened()){
		//Do something - write out error.
		DataWriter.error = -1;
	}
	
	
	//Write header for YAML data file
	DataWriter.fs << "Behavior Rig" << 2;
	DataWriter.fs << "Microsystems Lab Stanford University" << 2014;

	//Write local time
	struct tm *local;
	time_t t;
	t = time(NULL);
	local = localtime(&t);
	DataWriter.fs << "Experiment Time" << asctime(local);
	

	DataWriter.filename = YAMLDataFileName;
	DataWriter.videoFilename = VideoDataFileName;
	
	return;
}



//int DataManagement::AppendWormFrameToDisk(WormAnalysis::WormDataStructures WormData, int count, int frameNumber, double xStagePos, double yStagePos, double time){//, WriteOut* DataWriter){

int DataManagement::AppendWormFrameToDisk(array<double>^ wormDataArray, double xPosition, double yPosition){//, double xStagePos, double yStagePos){

	DataWriter.fs << "WormInfo" << "{" ;
	//DataWriter.fs << "Time " <<  wormDataArray[0];
	DataWriter.fs << "Processed frame number" <<  (int)wormDataArray[1];
	DataWriter.fs << "Camera frame number" <<  (int)wormDataArray[2];
	DataWriter.fs << "Target" << "{" << "x" <<  (int)wormDataArray[3] << "y" <<  (int)wormDataArray[4] << "}";
	DataWriter.fs << "Head" << "{" << "x" <<  (int)wormDataArray[5] << "y" <<  (int)wormDataArray[6] << "}";
	DataWriter.fs << "Tail" << "{" << "x" <<  (int)wormDataArray[7] << "y" <<  (int)wormDataArray[8] << "}";
    DataWriter.fs << "Stage Position" << "{" << "x" << xPosition << "y" << yPosition << "}";
	
	DataWriter.fs << "}";

	return 0;

}


int DataManagement::WriteStringToDisk(string LineToWrite, string DataToWrite){
	DataWriter.fs << LineToWrite << DataToWrite;
	return 0;
}

int DataManagement::WriteDoubleToDisk(string LineToWrite, double DataToWrite){
	DataWriter.fs << LineToWrite << DataToWrite;
	return 0;

}

int DataManagement::WritePointToDisk(string LineToWrite, Point PointToWrite){
	DataWriter.fs << LineToWrite << PointToWrite;
	return 0;
}

void DataManagement::StartNode(string NodeTitle){
	DataWriter.fs << NodeTitle << "{";
}

void DataManagement::EndNode(void){
	DataWriter.fs << "}";
}
void DataManagement::CloseDoc(void){
	DataWriter.fs.release();
}