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

//#include <vector.h>

using namespace cv;
using namespace std;


class WormAnalysis{
	
public:

	
	double imageResizeScale;
	int wormCount;
	double target;

	struct WormImageStructures{
		Mat OriginalImage;
		Mat OriginalImageResize;
		Mat ThresholdImage;
		Mat SmoothImage;
	} WormImages;

	struct WormDataStructures{
		vector<vector<Point> > Contours;
		Vector<Point> Worm;
		int TailIndex;
		int HeadIndex;
		vector<Point> Segments;// [500][2];
		bool FirstImageFlag;
		Mat ImageToPrint;
		vector<Point> Skeleton;// [50000];
		int NumberOfSegments;
		Point Target;
		Point Head;
		Point Tail;
	//	Point PreviousHeadTranslated;

		WormDataStructures(void);
	} WormData, PreviousWormData;

	struct GaussianSmoothingParameters{
	public:
		
		int ksizeHeight;
		int ksizeWidth;
		int sigmaX;
		int sigmaY;
		int borderType;
		
		GaussianSmoothingParameters(void);
	} WormSmoothParam;

	struct WormThresholdParameters{
	public:
		double threshold;
		double maxVal;
		int thresholdType;
		double OtsuThreshold;

		WormThresholdParameters(void);
	} WormThresholdParam;

	struct WormContourFindingParameters{
	public:
		int mode;
		int method;
		WormContourFindingParameters(void);
	} WormContourParam;

	struct WormSegmentationStructures{
	public:
		public:
		int SegJump; //How many points on each side of the current point and the guess point used to create the vector.
		int PointsBetweenSegments; //How many points along the contour are between each segment.
		int numPoints; // Number of points in the worm contour
		int numberOfSegments;  //Number of segments we'll make across the worm. 
		int currentLocation;//segmentation point. 
		int guess;
		int guessMin;
		vector<int> WormVec1;	// Create vectors to find the angles between for segmentation
		vector<int> WormVec2;
		vector<int> CrossVec;
		double Angle1;	//Used to hold angle measurement.
		double Angle2;
		vector<double> AngleDifference;	// will find the local minimum over the differences to find best segmentation
		double AngleDifferenceMinimum;
		
		WormSegmentationStructures(void);
	} WormSeg;

private:

	//Data for contour finding
	vector<Vec4i> hierarchy;
	Point offset;

	//Function prototypes
private:
	
	void WriteWormDataToFile(string, WormDataStructures &WormData);
	int boundCheck(int , int);
	double DotProduct(vector<int>, vector<int>);
	double VectorNorm(vector<int>);
	double PointDistance(Point, Point);
	void FindWormTail(void);
	void FindWormTailInsideRange(void);
	void FindWormHead(void);
	void HeadTailCheck(void);
	void WormSegmentation(void);
	void WormSegmentation2(void);
	void FindSkeleton(void);
	void addMidpointToSkeleton(Point);
	Point FindTarget(double);

public:	
	void FindWorm(void);
	void DrawResult(void);
	void ShowImage(Mat);
};