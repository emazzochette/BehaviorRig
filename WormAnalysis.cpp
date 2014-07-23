#include "stdafx.h"
#include "WormAnalysis.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
  
using namespace cv;
using namespace std;


WormAnalysis::WormDataStructures::WormDataStructures(void)
{
	FirstImageFlag = true;
} 

WormAnalysis::GaussianSmoothingParameters::GaussianSmoothingParameters(void)
{
	ksizeHeight = 5;
	ksizeWidth = 5;
	sigmaX = 3;
	sigmaY = 3;
	borderType=BORDER_DEFAULT;
}

WormAnalysis::WormThresholdParameters::WormThresholdParameters(void)
{
	threshold = 75;
	maxVal = 255;
	thresholdType = THRESH_BINARY;
};

WormAnalysis::WormContourFindingParameters::WormContourFindingParameters(void)
{
	mode = CV_RETR_EXTERNAL;
	method = CV_CHAIN_APPROX_NONE;
	//offset = (0,0);
};

WormAnalysis::WormSegmentationStructures::WormSegmentationStructures(void)
{
	SegJump = 10;
	PointsBetweenSegments = 5; 	
};


// Lower Level Functions:
void WormAnalysis::WriteWormDataToFile(string FileName, WormDataStructures &WormData)
{
	//FileStorage fs(FileName, FileStorage::APPEND);
	//fs << "WormData";
	//fs << "Worm" << WormData.ImageToPrint; // << WormData;
	//fs.release();
}

//This function makes sure that the current index is within the bounds of
//the potential indices. If not, it wraps the current index to the end or
//the beginning.
int WormAnalysis::boundCheck(int currentIndex, int maxIndex)
{
	if (currentIndex < 0){
        return maxIndex - abs(currentIndex);
	} else if (currentIndex > maxIndex-1){
        return currentIndex - maxIndex;
	} else {
        return currentIndex;
	}
}

double WormAnalysis::DotProduct(vector<int> a, vector<int> b)
{
	return double(a[0]*b[0] + a[1]*b[1]);
}

double WormAnalysis::VectorNorm(vector<int> a)
{
	return sqrt(double(a[0])*double(a[0]) + double(a[1])*double(a[1]));
}

double WormAnalysis::PointDistance(Point a, Point b)
{
	double exponent = 2;
 	return sqrt(pow(double(a.x-b.x),exponent) + pow(double(a.y - b.y),exponent));
}


// Higher Level Functions:
void WormAnalysis::FindWormTail(void)
{
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
void WormAnalysis::FindWormTailInsideRange(void)
{
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

void WormAnalysis::FindWormHead(void)
{
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

void WormAnalysis::HeadTailCheck(void)
{
//	int Holder;
	double MaxMove = 7.6; //pixels
	if (pow(MaxMove, 2) < PointDistance(PreviousWormData.Head, WormData.Worm[WormData.HeadIndex]))
	{
		//Holder = WormData.TailIndex;
		//WormData.TailIndex = WormData.HeadIndex;
		//WormData.HeadIndex = Holder;
	}
}

void WormAnalysis::WormSegmentation(void)
{
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
			//WormSeg.guess = boundCheck(WormData.Segments[i-1][2], WormSeg.numPoints);
			WormSeg.guess = boundCheck(WormData.Segments[i-1].y, WormSeg.numPoints);
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
		WormData.Segments[i].x = WormSeg.currentLocation;
		WormData.Segments[i].y = WormSeg.guessMin;
		WormSeg.numberOfSegments = i;
		i++;
		
	}
}

void WormAnalysis::WormSegmentation2(void)
{
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

	//clear data from previous worm.
	WormData.Segments.clear();

	//Begin segmentation calculation
	//for(int i=1; i<numberOfSegments; i++){
	int i = 0;
	currentLocation = WormData.HeadIndex;
	while(abs(currentLocation-WormData.TailIndex)>N){
		AngleDifference = 10;
		LastAngleDifference = 10;
		currentLocation = boundCheck(WormData.HeadIndex + N*(i+1), numPoints);
		if(i == 0){
			guess = boundCheck(WormData.HeadIndex - N, numPoints);
		}
		else{
			//guess = boundCheck(WormData.Segments[i-1][2], numPoints);
			guess = boundCheck(WormData.Segments[i-1].y, numPoints);
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
				if(i == 0){
					guess = boundCheck(WormData.HeadIndex - N, numPoints);
				}
				else{
					//guess = boundCheck(WormData.Segments[i-1][2]-N, numPoints);
					guess = boundCheck(WormData.Segments[i-1].y-N, numPoints);
				}
				breakCount++;
				break;
			}


	   }//end while loop for angle search
	/*	WormData.Segments[i][1] = currentLocation;
		WormData.Segments[i][2] = guess;*/
		WormData.Segments.push_back(Point(currentLocation, guess));
		//WormData.Segments[i].y = guess;
		i++;
	}//end for loop over number of segments
	WormData.NumberOfSegments = i;

	/*int j;
	Scalar color(225, 225, 225);
	for(j=1; j<i; j++){
		line(WormData.ImageToPrint, WormData.Worm[WormData.Segments[j][1]], WormData.Worm[WormData.Segments[j][2]], color, 1, 8, 0);
		circle(WormData.ImageToPrint, WormData.Worm[WormData.Segments[j][1]], 3, color, 1, 8, 0);
	}*/
}

void WormAnalysis::WormSegmentation3(void)
{
	int numSegments = 50;
	WormData.NumberOfSegments = numSegments;
	int numPoints = WormData.Worm.size();

	int sideLength1 = abs(WormData.HeadIndex - WormData.TailIndex);
	int sideLength2 = numPoints - sideLength1;

	double sideJump1 = (double)sideLength1/(double)(numSegments);
	double weight1 = sideJump1 - floor(sideJump1);
	sideJump1 = floor(sideJump1);
	double random1; 

	double sideJump2 = (double)sideLength2/(double)(numSegments);
	double weight2 = sideJump2 - floor(sideJump2);
	sideJump2 = floor(sideJump2);
	double random2;


	int direction1 = 1;
	int direction2 = 1;
	if (WormData.HeadIndex - WormData.TailIndex > 0 )
		direction1 = -1;
	else
		direction2 = -1;


	int currSegmentIndex1;
	int currSegmentIndex2;
	int prevSegmentIndex1 = WormData.HeadIndex;
	int	prevSegmentIndex2 = WormData.HeadIndex;

	for (int i = 0; i < numSegments; i++) {

		random1 = rand() % 100 + 0;
		if (random1/100.0 > weight1) {
			sideJump1++;
		}

		//currSegmentIndex1 = prevSegmentIndex1 + sideJump1;
		currSegmentIndex1 = boundCheck(prevSegmentIndex1 + direction1*sideJump1, numPoints);
		//if (currSegmentIndex1 > numPoints - 1) {
			//currSegmentIndex1 -= numPoints;
		//}
		prevSegmentIndex1 = currSegmentIndex1;


		random2 = rand() % 100 + 0;
		if (random2/100.0 > weight2) {
			sideJump2++;
		}
		//currSegmentIndex2 = prevSegmentIndex2 - sideJump2;
		currSegmentIndex2 = boundCheck(prevSegmentIndex2 + direction2*sideJump2, numPoints);
		//if (currSegmentIndex2 < 0) {
			//currSegmentIndex2 += numPoints;
		//}
		prevSegmentIndex2 = currSegmentIndex2;

		WormData.Segments.push_back(Point(currSegmentIndex1, currSegmentIndex2));
	}
}

void WormAnalysis::DrawResult(WormDataStructures *wormData)
{
	wormData->ImageToPrint = NULL;
	
	cvtColor(wormData->OriginalImageResize, wormData->ImageToPrint, CV_GRAY2RGB);
	
	Scalar green(0,255,0);
	Scalar red(0,0,225);
	Scalar blue(225,0,0);

	//PRINT CONTOURS
	drawContours( wormData->ImageToPrint, wormData->Contours, wormData->MaxContour, green, 2, 0, NULL, 0, Point(0,0));

	//Print cantilever
	circle(wormData->ImageToPrint, Point((int)(621*imageResizeScale), (int)(365*imageResizeScale)), 15, green, 2, 8, 0);

	//PRINT TAIL
	circle(wormData->ImageToPrint, wormData->Worm[wormData->TailIndex], 7, red, 2, 8, 0);

	//PRINT HEAD
	circle(wormData->ImageToPrint, wormData->Worm[wormData->HeadIndex], 10, red, 2, 8, 0);

	////PRINT SEGMENTS:
	for(int j=1; j < wormData->NumberOfSegments; j++){
		line(wormData->ImageToPrint, wormData->Worm[wormData->Segments[j].x], wormData->Worm[wormData->Segments[j].y], red, 1, 8, 0);
		circle(wormData->ImageToPrint, wormData->Worm[wormData->Segments[j].x], 3, red, 1, 8, 0);
	}
	
	
	//PRINT SKELETON
	for (int i = 0; i < wormData->Skeleton.size() - 1; i++) {
		line(wormData->ImageToPrint, wormData->Skeleton[i], wormData->Skeleton[i+1], blue, 1, 8, 0);
	}

	//PRINT TARGET
	drawCross(&(wormData->ImageToPrint), wormData->Target);

	char numstr[21];
	sprintf_s(numstr, "Frame #%d", wormData->wormCount);
	putText(wormData->ImageToPrint, numstr, Point(50, 50), FONT_HERSHEY_SIMPLEX, 0.75, red, 2, 8, false);  

}

void WormAnalysis::drawCross(Mat *image, Point pt) {
	Scalar red(0, 0, 225);
	line(*image, Point(pt.x - 5, pt.y + 5), Point(pt.x + 5, pt.y - 5), red, 2, 8, 0);
	line(*image, Point(pt.x + 5, pt.y + 5), Point(pt.x - 5, pt.y - 5), red, 2, 8, 0);
}

//Highest Level Function:
void WormAnalysis::FindWorm(void)
{	
	WormData.wormCount++;
	WormData.OriginalImageResize = NULL;
	WormImages.ThresholdImage = NULL;
	WormImages.SmoothImage = NULL;
	WormData.Contours.clear();
	WormData.Worm.clear();
	WormData.Skeleton.clear();
	WormData.Segments.clear();

	//Data for Gaussian smoothing:
	Size_<int> ksize(WormSmoothParam.ksizeWidth,WormSmoothParam.ksizeHeight);
	offset.x = 0;
	offset.y = 0;

	//THRESHOLDING SECTION
	
	resize(WormImages.OriginalImage, WormData.OriginalImageResize, Size((int)(WormImages.OriginalImage.cols*imageResizeScale), (int)(WormImages.OriginalImage.rows*imageResizeScale)), 0, 0, INTER_LINEAR );

	WormThresholdParam.OtsuThreshold = threshold( WormData.OriginalImageResize, WormImages.ThresholdImage, 75, 255, THRESH_BINARY + THRESH_OTSU);//WormThresholdParam.threshold, WormThresholdParam.maxVal, WormThresholdParam.thresholdType + THRESH_OTSU);

	// SMOOTHING AND FINDING CONTOURS
	//Smooth using Gaussian Filter
	GaussianBlur(WormImages.ThresholdImage, WormImages.SmoothImage, ksize, WormSmoothParam.sigmaX, WormSmoothParam.sigmaY, WormSmoothParam.borderType);

	//Find Contours
	findContours(WormImages.SmoothImage, WormData.Contours, hierarchy, WormContourParam.mode, WormContourParam.method, offset);
	
	//Find the largest and the second largest contour:
	//TO Do:: turn this into a function:
	unsigned int MaxContourSize = 1;
	WormData.MaxContour=1;
	//TO DO: turn this into a vector interator:
	for(unsigned int i = 0; i < WormData.Contours.size(); i++){
		//CurrentContourSize = WormData.Contours[i].size();
		if (WormData.Contours[i].size() > MaxContourSize){
			WormData.MaxContour = i;
			MaxContourSize = WormData.Contours[i].size();			
		}
	}
	WormData.Worm = WormData.Contours[WormData.MaxContour];
	
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
	WormSegmentation3();
	
	//FIND SKELETON, TARGET
	//Use the segments to find the skeleton of the worm:
	FindSkeleton();

	WormData.Target = FindTarget(target);
	
	//Now done with at least one image, so turn off first image flag.
	WormData.FirstImageFlag = false;
}

void WormAnalysis::ShowImage(Mat imageToShow)
{
	namedWindow("Display window", CV_WINDOW_AUTOSIZE);
	imshow("Display window", imageToShow);
	cvWaitKey(3);
}

/* Function: addMidpointToSkeleton
 * -------------------------------
 * Takes a point indicating two indexs of points corresponding to a worm
 * segment. Computes the midpoint for that segment and adds it to the worm
 * skeleton.
 */
void WormAnalysis::addMidpointToSkeleton(Point segmentIndexes)
{
    //extract indexs
    int index1 = segmentIndexes.x;
    int index2 = segmentIndexes.y;
    
    //extract points
    Point point1 = WormData.Worm[index1];
    Point point2 = WormData.Worm[index2];
    
    //compute midpoint
    Point midpoint;
    midpoint.x = (point1.x + point2.x)/2;
    midpoint.y = (point1.y + point2.y)/2;
    
    //add midpoint to skeleton
    WormData.Skeleton.push_back(midpoint);
}

/* Function: FindSkeleton
 * ----------------------
 * Finds and stores points in the global skeleton array.
 */
void WormAnalysis::FindSkeleton(void)
{
    WormData.Skeleton.clear();
    
    //Add head to skeleton
    WormData.Skeleton.push_back(WormData.Worm[WormData.HeadIndex]);
    
    //Add midpoints to skeleton
    for(vector<Point>::iterator it = WormData.Segments.begin(); it< WormData.Segments.end(); it++){
		addMidpointToSkeleton(*it);
	}

    //Add tail to skeleton
    WormData.Skeleton.push_back(WormData.Worm[WormData.TailIndex]);
}

/* Function: target
 * ----------------
 * Returns a point to the target. Takes in a percent length of the worm starting
 * from the head to the tail.
 */
Point WormAnalysis::FindTarget(double percentLength)
{
    Point result;
    
    //finds the length of the skeleton
    double skeletonLength = 0.0;
    vector<double> skeletonDistances;
    for (unsigned int i = 0; i < WormData.Skeleton.size() - 1; i++) {
        Point point1 = WormData.Skeleton[i];
        Point point2 = WormData.Skeleton[i + 1];
        double distance = PointDistance(point1, point2);
        skeletonDistances.push_back(distance);
        skeletonLength += distance;
    }
    
    //target length from head
    double targetLength = percentLength * skeletonLength;
    
    //finds segment that contains target
    double lengthAlongSkeleton = 0;
    int indexAlongSkeleton = 0;
    while (lengthAlongSkeleton < targetLength) {
        lengthAlongSkeleton += skeletonDistances[indexAlongSkeleton];
        indexAlongSkeleton++;
    }
    
    //find target
    double extraLength = lengthAlongSkeleton - targetLength;
    
    double lastSegmentLength = skeletonDistances[indexAlongSkeleton];
    Point nextPoint = WormData.Skeleton[indexAlongSkeleton];
    Point prevPoint = WormData.Skeleton[indexAlongSkeleton - 1];
    
    result.x = (int)(nextPoint.x - extraLength * ((nextPoint.x - prevPoint.x)/lastSegmentLength));
    result.y = (int)(nextPoint.y - extraLength * ((nextPoint.y - prevPoint.y)/lastSegmentLength));
    
    return result;
}