#pragma once

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)


#include "WormAnalysis.h"

#include <iostream>
#include <stdio.h>


using namespace cv;
//using namespace std;



class DataManagement
{
public:
	struct WriteOutStruct{
		FileStorage fs;
		char* filename;
		char* videoFilename;
		int error;

		WriteOutStruct(void);
	} DataWriter;


	vector<Mat> videoBuffer;

	//DataManagement(void);
	char* CreateFileName(const char* , const char*, const char* );
	//void DestroyFileName(char**);
	void SetUpWriteToDisk(const char*, const char*);//,  MemStorage*);

	//int AppendWormFrameToDisk(WormAnalysis::WormDataStructures,  WriteOut*);
	//int AppendWormFrameToDisk(WormAnalysis::WormDataStructures WormData, int count, int frameNumber, double xStagePos, double yStagePos, double time);//, WriteOut* DataWriter);
	int AppendWormFrameToDisk(array<double>^, double, double);
	int WriteStringToDisk(string, string);
	int WriteDoubleToDisk(string, double);
	int WritePointToDisk(string, Point);
	void StartNode(string);
	void EndNode(void);
	void CloseDoc(void);
};
