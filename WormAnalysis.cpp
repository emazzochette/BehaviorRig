#include "StdAfx.h"
#include "WormAnalysis.h"

#pragma managed(push,off)
#include <cv.h>
#pragma managed(pop)
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
  
#include <highgui.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <complex>
#include <ctime>

//#include <vector.h>

using namespace cv;
using namespace std;




WormAnalysis::WormDataStructures::WormDataStructures(void){

	FirstImageFlag = true;
} 

WormAnalysis::GaussianSmoothingParameters::GaussianSmoothingParameters(void){
	ksizeHeight = 5;
	ksizeWidth = 5;
	sigmaX = 3;
	sigmaY = 3;
	borderType=BORDER_DEFAULT;
}

WormAnalysis::WormThresholdParameters::WormThresholdParameters(void){
	threshold = 75;
	maxVal = 255;
	thresholdType = THRESH_BINARY;
};

WormAnalysis::WormContourFindingParameters::WormContourFindingParameters(void){
	mode = CV_RETR_EXTERNAL;
	method = CV_CHAIN_APPROX_NONE;
	//offset = (0,0);
};

WormAnalysis::WormSegmentationStructures::WormSegmentationStructures(void){
	SegJump = 10;
	PointsBetweenSegments = 5; 	
};







// Lower Level Functions:

void WormAnalysis::WriteWormDataToFile(string FileName, WormDataStructures &WormData){
	//FileStorage fs(FileName, FileStorage::APPEND);
	//fs << "WormData";
	//fs << "Worm" << WormData.ImageToPrint; // << WormData;
	//fs.release();
}
int WormAnalysis::boundCheck(int currentIndex, int maxIndex){
//This function makes sure that the current index is within the bounds of
//the potential indices. If not, it wraps the current index to the end or
//the beginning.
	if(currentIndex < 0){
        return maxIndex - abs(currentIndex);
	}
	else if (currentIndex > maxIndex-1){
        return currentIndex - maxIndex;
	}
	else {
        return currentIndex;
	}
}

double WormAnalysis::DotProduct(vector<int> a, vector<int> b){
	return double(a[0]*b[0] + a[1]*b[1]);
}
double WormAnalysis::VectorNorm(vector<int> a){
	return sqrt(double(a[0])*double(a[0]) + double(a[1])*double(a[1]));
}

double WormAnalysis::PointDistance(Point a, Point b){
	double exponent = 2;
 	return sqrt( pow(double(a.x-b.x),exponent) + pow(double(a.y - b.y),exponent) );
}


// Higher Level Functions:
void WormAnalysis::FindWormTail(void){
	
	vector<int> ForVec (2);
	vector<int> BackVec (2);

	//Parameters for head, tail search
	int Jump = 10;
	
	Point CurrentPoint;
	Point JumpUpPoint;
	Point JumpBackPoint;
	
	//Dot Pruduct:
	double DotProductEval; // stores the current value of the dot product
	double Tail = 1000; //Stores the minimum dot product found
	
	int numPoints = WormData.Worm.size();
	
	WormData.TailIndex = 1;


	//Scan through contour to find the tail
	for(int i = 0; i<numPoints; i++){
		JumpUpPoint = WormData.Worm[boundCheck(i+Jump, numPoints)];
		CurrentPoint = WormData.Worm[boundCheck(i, numPoints)];
		JumpBackPoint = WormData.Worm[boundCheck(i-Jump, numPoints)];
				
		ForVec[0] = JumpUpPoint.x - CurrentPoint.x;
		ForVec[1] = JumpUpPoint.y - CurrentPoint.y;
		BackVec[0] = CurrentPoint.x - JumpBackPoint.x;
		BackVec[1] = CurrentPoint.y - JumpBackPoint.y;
		
		DotProductEval = DotProduct(ForVec, BackVec);
		if(DotProductEval<Tail){
			Tail = DotProductEval;
			WormData.TailIndex = i;
		}		
	}
	WormData.Tail = WormData.Worm[WormData.TailIndex];	

}
void WormAnalysis::FindWormTailInsideRange(void){

	vector<int> ForVec (2);
	vector<int> BackVec (2);

	//Parameters for head, tail search
	int Jump = 10;
	
	Point CurrentPoint;
	Point JumpUpPoint;
	Point JumpBackPoint;
	
	//Dot Pruduct:
	double DotProductEval; // stores the current value of the dot product
	double Tail = 1000; //Stores the minimum dot product found
	double SearchRadius = 200; // pixels
	int numPoints = WormData.Worm.size();
	
	WormData.TailIndex = 1;

//Scan through contour to find the tail
	for(int i = 0; i<numPoints; i++){
		if (WormAnalysis::PointDistance(CurrentPoint,PreviousWormData.Tail)<= pow(SearchRadius,2))
		{
			JumpUpPoint = WormData.Worm[boundCheck(i+Jump, numPoints)];
			CurrentPoint = WormData.Worm[boundCheck(i, numPoints)];
			JumpBackPoint = WormData.Worm[boundCheck(i-Jump, numPoints)];
					
			ForVec[0] = JumpUpPoint.x - CurrentPoint.x;
			ForVec[1] = JumpUpPoint.y - CurrentPoint.y;
			BackVec[0] = CurrentPoint.x - JumpBackPoint.x;
			BackVec[1] = CurrentPoint.y - JumpBackPoint.y;
			
			DotProductEval = DotProduct(ForVec, BackVec);
			if(DotProductEval<Tail){
				Tail = DotProductEval;
				WormData.TailIndex = i;
			}		
		}
	}

	WormData.Tail = WormData.Worm[WormData.TailIndex];	
}
void WormAnalysis::FindWormHead(void){
	//Parameters for head, tail search
	vector<int> ForVec (2);
	vector<int> BackVec (2);
	
	int Jump = 10;
	int numPoints = WormData.Worm.size();
	
	Point CurrentPoint;
	Point JumpUpPoint;
	Point JumpBackPoint;
	
	double DotProductEval;	
	double Head = 1000; // Initialize head to 1000



	//Find the bounds over which to search for the head
	int Bound1;
	int Bound2;
	Bound1 = boundCheck(WormData.TailIndex - (int)floor(double(numPoints)/3), numPoints);
	Bound2 = boundCheck(WormData.TailIndex + (int)ceil(double(numPoints)/3), numPoints);

	WormData.HeadIndex = 1;

	if(Bound1<WormData.TailIndex && WormData.TailIndex<Bound2){
		for(int i = 0; i<Bound1; i++){
			JumpUpPoint = WormData.Worm[boundCheck(i+Jump, numPoints)];
			CurrentPoint = WormData.Worm[boundCheck(i, numPoints)];
			JumpBackPoint = WormData.Worm[boundCheck(i-Jump, numPoints)];

			ForVec[0] = JumpUpPoint.x - CurrentPoint.x;
			ForVec[1] = JumpUpPoint.y - CurrentPoint.y;
			BackVec[0] = CurrentPoint.x - JumpBackPoint.x;
			BackVec[1] = CurrentPoint.y - JumpBackPoint.y;
			
			DotProductEval = DotProduct(ForVec, BackVec);
			if(DotProductEval<Head){
				Head = DotProductEval;
				WormData.HeadIndex = i;
			}		
		}
		for(int i = Bound2; i<numPoints; i++){
			JumpUpPoint = WormData.Worm[boundCheck(i+Jump, numPoints)];
			CurrentPoint = WormData.Worm[boundCheck(i, numPoints)];
			JumpBackPoint = WormData.Worm[boundCheck(i-Jump, numPoints)];

			ForVec[0] = JumpUpPoint.x - CurrentPoint.x;
			ForVec[1] = JumpUpPoint.y - CurrentPoint.y;
			BackVec[0] = CurrentPoint.x - JumpBackPoint.x;
			BackVec[1] = CurrentPoint.y - JumpBackPoint.y;
			
			DotProductEval = DotProduct(ForVec, BackVec);
			if(DotProductEval<Head){
				Head = DotProductEval;
				WormData.HeadIndex = i;
			}		
		}
	}
	else {
		if(Bound2<Bound1){
			int BoundHold;
			BoundHold = Bound1;
			Bound1 = Bound2;
			Bound2 = BoundHold;
		}
		for(int i = Bound1; i<Bound2; i++){
			JumpUpPoint = WormData.Worm[boundCheck(i+Jump, numPoints)];
			CurrentPoint = WormData.Worm[boundCheck(i, numPoints)];
			JumpBackPoint = WormData.Worm[boundCheck(i-Jump, numPoints)];

			ForVec[0] = JumpUpPoint.x - CurrentPoint.x;
			ForVec[1] = JumpUpPoint.y - CurrentPoint.y;
			BackVec[0] = CurrentPoint.x - JumpBackPoint.x;
			BackVec[1] = CurrentPoint.y - JumpBackPoint.y;
			
			DotProductEval = DotProduct(ForVec, BackVec);
			if(DotProductEval<Head){
				Head = DotProductEval;
				WormData.HeadIndex = i;
			}
		}
	}
	
	WormData.Head = WormData.Worm[WormData.HeadIndex];
}
void WormAnalysis::HeadTailCheck(void){

	int Holder;
	double MaxMove = 7.6; //pixels
	if (pow(MaxMove, 2) < PointDistance(PreviousWormData.Head, WormData.Worm[WormData.HeadIndex]))
	{
		//Holder = WormData.TailIndex;
		//WormData.TailIndex = WormData.HeadIndex;
		//WormData.HeadIndex = Holder;
	}
	



}
void WormAnalysis::WormSegmentation(void){
	WormSeg.numPoints = WormData.Worm.size();
	WormSeg.WormVec1.clear();
	WormSeg.WormVec2.clear();
	WormSeg.CrossVec.clear();

	//WormSeg.numberOfSegments = int(floor(double(WormSeg.numPoints)/(3*double(N))));
	
	//WormSeg.currentLocation = WormData.HeadIndex;
	
	int i = 1;
	while(abs(WormSeg.currentLocation-WormData.TailIndex)>WormSeg.PointsBetweenSegments){
		WormSeg.AngleDifference.clear();
		WormSeg.AngleDifferenceMinimum = 10;

		WormSeg.currentLocation = boundCheck(WormData.HeadIndex + WormSeg.PointsBetweenSegments*i, WormSeg.numPoints);
		if(i == 1){
			WormSeg.guess = boundCheck(WormData.HeadIndex, WormSeg.numPoints);
		}
		else{
			WormSeg.guess = boundCheck(WormData.Segments[i-1][2], WormSeg.numPoints);
		}
		//Calculate vector along body of the worm - points in direction of head
		WormSeg.WormVec1.push_back(WormData.Worm[boundCheck(WormSeg.currentLocation+WormSeg.SegJump, WormSeg.numPoints)].x - WormData.Worm[boundCheck(WormSeg.currentLocation-WormSeg.SegJump, WormSeg.numPoints)].x);
		WormSeg.WormVec1.push_back(WormData.Worm[boundCheck(WormSeg.currentLocation+WormSeg.SegJump, WormSeg.numPoints)].y - WormData.Worm[boundCheck(WormSeg.currentLocation-WormSeg.SegJump, WormSeg.numPoints)].y);
	
		
		

		for(int ii = 0; ii<WormSeg.PointsBetweenSegments*2; ii++){
			WormSeg.WormVec2.push_back(WormData.Worm[boundCheck(WormSeg.guess+WormSeg.SegJump, WormSeg.numPoints)].x-WormData.Worm[boundCheck(WormSeg.guess-WormSeg.SegJump, WormSeg.numPoints)].x);
			WormSeg.WormVec2.push_back(WormData.Worm[boundCheck(WormSeg.guess+WormSeg.SegJump, WormSeg.numPoints)].y-WormData.Worm[boundCheck(WormSeg.guess-WormSeg.SegJump, WormSeg.numPoints)].y);
			//Calculate vector connecting currentLocation and guess point
			WormSeg.CrossVec.push_back(WormData.Worm[WormSeg.guess].x - WormData.Worm[WormSeg.currentLocation].x);
			WormSeg.CrossVec.push_back(WormData.Worm[WormSeg.guess].y - WormData.Worm[WormSeg.currentLocation].y);

			//Use the cross product to calculate angles
			WormSeg.Angle1 = acos(DotProduct(WormSeg.WormVec1, WormSeg.CrossVec)/(VectorNorm(WormSeg.WormVec1)*VectorNorm(WormSeg.CrossVec)));
			WormSeg.Angle2 = acos(DotProduct(WormSeg.WormVec2, WormSeg.CrossVec)/(VectorNorm(WormSeg.WormVec2)*VectorNorm(WormSeg.CrossVec)));
			
			WormSeg.AngleDifference.push_back(abs(WormSeg.Angle1 - WormSeg.Angle2));
			WormSeg.guess = boundCheck(WormSeg.guess - 1, WormSeg.numPoints);
			
			if(WormSeg.AngleDifferenceMinimum >= WormSeg.AngleDifference[ii]){
				WormSeg.AngleDifferenceMinimum = WormSeg.AngleDifference[ii];
				WormSeg.guessMin = WormSeg.guess;
			}

			WormSeg.WormVec2.clear();
			WormSeg.CrossVec.clear();
		}

		WormSeg.WormVec1.clear();
		WormData.Segments[i][1] = WormSeg.currentLocation;
		WormData.Segments[i][2] = WormSeg.guessMin;
		WormSeg.numberOfSegments = i;
		i++;
		
	}
}
void WormAnalysis::WormSegmentation2(void){
		//SEGMENTATION
	//Parameters for segmentation
	double THRESHOLD = 0.8;
	int SegJump = 10;
	int N = 5;

	//Data for segmentation
	int numPoints = WormData.Worm.size();
	int numberOfSegments; 
	numberOfSegments = int(floor(double(numPoints)/(3*double(N))));
	int currentLocation;
	int guess;
	vector<int> WormVec1 (2);
	vector<int> WormVec2 (2);
	vector<int> CrossVec (2);
	double Angle1;
	double Angle2;
	double AngleDifference = 10;
	double LastAngleDifference = 10;
	int Direction = 1;
	int count;
	int breakCount = 0;
	//int Segments [100][2];
	
	
	//if(abs(CurrentLocation-TailIndex)<N)    
	
	

	//Begin segmentation calculation
	//for(int i=1; i<numberOfSegments; i++){
	int i = 1;
	currentLocation = WormData.HeadIndex;
	while(abs(currentLocation-WormData.TailIndex)>N){
		AngleDifference = 10;
		LastAngleDifference = 10;
		currentLocation = boundCheck(WormData.HeadIndex + N*i, numPoints);
		if(i == 1){
			guess = boundCheck(WormData.HeadIndex - N, numPoints);
		}
		else{
			guess = boundCheck(WormData.Segments[i-1][2], numPoints);
		}
		//Calculate vector along body of the worm - points in direction of head
		WormVec1[0] = WormData.Worm[boundCheck(currentLocation+SegJump, numPoints)].x - WormData.Worm[boundCheck(currentLocation-SegJump, numPoints)].x;
		WormVec1[1] = WormData.Worm[boundCheck(currentLocation+SegJump, numPoints)].y - WormData.Worm[boundCheck(currentLocation-SegJump, numPoints)].y;

		
		count = 0;
		while(AngleDifference>THRESHOLD){


			//Calculate vector along body of the worm at guess point - points in direction of head
			WormVec2[0] = WormData.Worm[boundCheck(guess+SegJump, numPoints)].x-WormData.Worm[boundCheck(guess-SegJump, numPoints)].x;
			WormVec2[1] = WormData.Worm[boundCheck(guess+SegJump, numPoints)].y-WormData.Worm[boundCheck(guess-SegJump, numPoints)].y;
			//Calculate vector connecting currentLocation and guess point
			CrossVec[0] = WormData.Worm[guess].x - WormData.Worm[currentLocation].x;
			CrossVec[1] = WormData.Worm[guess].y - WormData.Worm[currentLocation].y;

			//Use the cross product to calculate angles
			Angle1 = acos(DotProduct(WormVec1, CrossVec)/(VectorNorm(WormVec1)*VectorNorm(CrossVec)));
			Angle2 = acos(DotProduct(WormVec2, CrossVec)/(VectorNorm(WormVec2)*VectorNorm(CrossVec)));

			AngleDifference = abs(Angle1 - Angle2);

			if (Angle1>Angle2){
				guess = boundCheck(guess - 1, numPoints);
			}
			else {
				guess = boundCheck(guess + 1, numPoints);
			}


			/*
			if(AngleDifference>LastAngleDifference){
				Direction = -1*Direction;
				count = count + 1;
			}//end if statement
			if (count == 2){
				break;
			}
			guess = boundCheck(guess + Direction, numPoints);
	        LastAngleDifference = AngleDifference;
			*/
			count++;
			if (count>100){ //TO DO: fix this
				if(i == 1){
					guess = boundCheck(WormData.HeadIndex - N, numPoints);
				}
				else{
					guess = boundCheck(WormData.Segments[i-1][2]-N, numPoints);
				}
				breakCount++;
				break;
			}


	   }//end while loop for angle search
		WormData.Segments[i][1] = currentLocation;
		WormData.Segments[i][2] = guess;
		i++;
	}//end for loop over number of segments
	WormData.NumberOfSegments = i;
	
	int j;
	Scalar color(225, 225, 225);
	for(j=1; j<i; j++){
		line(WormData.ImageToPrint, WormData.Worm[WormData.Segments[j][1]], WormData.Worm[WormData.Segments[j][2]], color, 1, 8, 0);
		circle(WormData.ImageToPrint, WormData.Worm[WormData.Segments[j][1]], 3, color, 1, 8, 0);
	}
}
void WormAnalysis::FindSkeleton(void){
	//First Point on skeleton is the head.
	WormData.Skeleton.clear();
	WormData.Skeleton.push_back(WormData.Worm[WormData.HeadIndex]);

	Point DummyPoint;
	Scalar color(225, 225, 51);
	for( int i=1;i<WormSeg.numberOfSegments; i++){
		DummyPoint.x = ( WormData.Worm[WormData.Segments[i][1]].x +  WormData.Worm[WormData.Segments[i][2]].x )/2;
		DummyPoint.y = ( WormData.Worm[WormData.Segments[i][1]].y +  WormData.Worm[WormData.Segments[i][2]].y )/2;
		WormData.Skeleton.push_back(DummyPoint);
	}
	//Last point is the tail.
	WormData.Skeleton.push_back(WormData.Worm[WormData.TailIndex]);
	

	//Create a vector of the distance between each point along skeleton
	//Use that to find the length of the skeleton
	vector<double> DistanceBetweenSkeletonPoints;
	double SkeletonLength = 0 ;
	DistanceBetweenSkeletonPoints.clear();
	double dummy;
	for(int i=1;i<=WormSeg.numberOfSegments;i++){
		dummy = PointDistance(WormData.Skeleton[i-1],WormData.Skeleton[i]);
		DistanceBetweenSkeletonPoints.push_back(dummy);
		SkeletonLength += dummy;
	}

	double TargetLength = 0.25*SkeletonLength;
	double DistanceFromHead = 0;

	//variables for finding target between two points:
	double Length;
	double Ratio;
	for(int i=1;i<WormSeg.numberOfSegments;i++){
		Length = TargetLength-DistanceFromHead;	
		DistanceFromHead += DistanceBetweenSkeletonPoints[i-1];
		if( DistanceFromHead>TargetLength){
			if (WormData.Skeleton[i].x - WormData.Skeleton[i-1].x != 0){
				Ratio = (WormData.Skeleton[i].y - WormData.Skeleton[i-1].y)/(WormData.Skeleton[i].x - WormData.Skeleton[i-1].x);
				WormData.Target.x = (int)floor(Length/(sqrt(pow(Ratio,2)+1))+WormData.Skeleton[i-1].x);
				WormData.Target.y = (int)floor(Ratio*(WormData.Target.x-WormData.Skeleton[i-1].x)+WormData.Skeleton[i-1].y);
			}
			else{
				WormData.Target.x = WormData.Skeleton[i-1].x;
				WormData.Target.y = (int)floor(WormData.Skeleton[i-1].y+Length);
			}
			break;
		}

	}
}
void WormAnalysis::DrawResult(void){
	
	//WormData.ImageToPrint = Mat::zeros(WormImages.OriginalImage.rows, WormImages.OriginalImage.cols, CV_8UC3);
	//WormData.ImageToPrint = WormImages.OriginalImage;
	cvtColor(WormImages.OriginalImage, WormData.ImageToPrint, CV_GRAY2RGB);
	
	//PRINT CONTOURS
    int idx = 0;
	for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
		Scalar color(0,255,0);   
		drawContours( WormData.ImageToPrint, WormData.Contours, idx, color, 2, 0, hierarchy, 0 );
    }
	

	//Print cantilever
	Scalar color(0,0,255);
	circle(WormData.ImageToPrint, Point(621, 365),5,color,2,8,0);

	//PRINT TAIL
	
	circle(WormData.ImageToPrint, WormData.Worm[WormData.TailIndex], 7, color, 2, 8, 0);


	//PRINT HEAD
	circle(WormData.ImageToPrint, WormData.Worm[WormData.HeadIndex], 10, color, 2, 8, 0);
	if (!WormData.FirstImageFlag){
		circle(WormData.ImageToPrint, PreviousWormData.Head, 5, color, 1, 8, 0);
	}

	////PRINT SEGMENTS:
	////Scalar color(225, 225, 225);
	//for(int j=1; j<WormSeg.numberOfSegments; j++){
	//	line(WormData.ImageToPrint, WormData.Worm[WormData.Segments[j][1]], WormData.Worm[WormData.Segments[j][2]], color, 1, 8, 0);
	//	circle(WormData.ImageToPrint, WormData.Worm[WormData.Segments[j][1]], 3, color, 1, 8, 0);
	//}
	
	
	////PRINT SKELETON
	//idx = 0;
	////Scalar color( rand()&255, rand()&255, rand()&255 );
	//	for( ; idx >= 0; idx = hierarchy[idx][0] )
 //   {
	//	Scalar color(255,255,255);   
	//	drawContours(WormData.ImageToPrint, WormData.Contours, idx, color, 0, 0, hierarchy, 0 );
 //   }

	//PRINT TARGET
	//circle(WormData.ImageToPrint, WormData.Target, 10, color, 1, 8, 0);


	////Print to Screen
	/*namedWindow("Display window", CV_WINDOW_AUTOSIZE);
	imshow("Display window", WormData.ImageToPrint);
	cvWaitKey(3);*/

	//Write to disc
	//imwrite(SaveFileName, WormData.ImageToPrint);
	//videoWriter << WormData.ImageToPrint;

}
//Highest Level Function:
void WormAnalysis::FindWorm(void){	

	//Data for Gaussian smoothing:
	Size_<int> ksize(WormSmoothParam.ksizeWidth,WormSmoothParam.ksizeHeight);
	offset.x = 0;
	offset.y = 0;

	//THRESHOLDING SECTION
	WormThresholdParam.OtsuThreshold = threshold( WormImages.OriginalImage, WormImages.ThresholdImage, WormThresholdParam.threshold, WormThresholdParam.maxVal, WormThresholdParam.thresholdType + THRESH_OTSU);

	// SMOOTHING AND FINDING CONTOURS
	//Smooth using Gaussian Filter
	GaussianBlur(WormImages.ThresholdImage, WormImages.SmoothImage, ksize, WormSmoothParam.sigmaX, WormSmoothParam.sigmaY, WormSmoothParam.borderType);

	//Find Contours
	findContours(WormImages.SmoothImage, WormData.Contours, hierarchy, WormContourParam.mode, WormContourParam.method, offset);
	//Find the largest and the second largest contour:	
	int MaxContourSize = 1;
	int MaxContour=1;
	for(int i = 0; i<WormData.Contours.size(); i++){
		//CurrentContourSize = WormData.Contours[i].size();
		if (WormData.Contours[i].size()>MaxContourSize){
			MaxContour = i;
			MaxContourSize = WormData.Contours[i].size();			
		}
	}
	WormData.Worm = WormData.Contours[MaxContour];
	
	//FINDING HEAD AND TAIL
	
	FindWormTail();
	FindWormHead();
	
	//If this is not the first image, check against previous head and tail.
	if(WormData.FirstImageFlag){
		FindWormTail();
		FindWormHead();
	}
	else{
		FindWormTailInsideRange();
		FindWormHead();
		HeadTailCheck();
	}
		
	//SEGMENTATION
	// Perform the segmentation of the worm:
	//WormSegmentation();
	
	//FIND SKELETON, TARGET
	//Use the segments to find the skeleton of the worm:
	//FindSkeleton();
	
	//Now done with at least one image, so turn off first image flag.
	WormData.FirstImageFlag = false;
}

void WormAnalysis::ShowImage(void){
	namedWindow("Display window", CV_WINDOW_AUTOSIZE);
	imshow("Display window", WormImages.OriginalImage);
	cvWaitKey(3);

}