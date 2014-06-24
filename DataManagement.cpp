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
	//Create new instance of write out object
	//WriteOut* DataWriter = CreateDataWriter();


	
	//Create filename
	char* YAMLDataFileName = CreateFileName(dirfilename, outfilename,".yml");

	//cv::FileStorage fs("C:\\Users\\Eileen Mazzochette\\Desktop\\TestFolder\\test.yml", cv::FileStorage::WRITE );
	//fs << "write data" << 5;
	//fs.release();
	//	//fs.open(YAMLDataFileName, FileStorage::APPEND );
	//if(~fs.isOpened()){

	//	DataWriter.error = -1;
	//}

	//Open YAML Data File for writing //
	DataWriter.fs.open(YAMLDataFileName, FileStorage::WRITE );
	//DataWriter.fs << "write data" << 5;
	if (~DataWriter.fs.isOpened()){
		//Do something - write out error.
		DataWriter.error = -1;
	}
	

	//if (DataWriter.error < 0) return;

	
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
	
	return;
}



int DataManagement::AppendWormFrameToDisk(WormAnalysis::WormDataStructures WormData, int count, int frameNumber, double xStagePos, double yStagePos, double time){//, WriteOut* DataWriter){

	//FileStorage fs = DataWriter->fs;
	DataWriter.fs << "{" ;
	DataWriter.fs << "Frame number" << frameNumber;
	DataWriter.fs << "Time Stamp" << time;
	DataWriter.fs << "Stage Position" << "{" << "x" << xStagePos << "y" << yStagePos << "}";
	DataWriter.fs << "Head" << WormData.Head;
	DataWriter.fs << "Tail" << WormData.Tail;
	DataWriter.fs << "Target" << WormData.Target;
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