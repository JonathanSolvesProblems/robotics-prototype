#pragma once
#include <opencv2\opencv.hpp>
#include <conio.h>
#include <iostream>

#define CircleShape 0 ;
#define TriangleShape 1 ;
#define RectangleShape 2;

using namespace std;
using namespace cv;

class PrintedObj
{

	VideoCapture cap;
	Mat intrinsic_matrix_loaded, distortion_coeffs_loaded;

public:
	PrintedObj(int CameraNumber);
	//PrintedObj(int CameraNumber, Mat frame,double distortionMatrix[]);

	Mat GetFrame();
	void UndisrortedFrame(Mat &frame);
	vector<vector<Point>> FindContours(Mat inputFrame, Mat &HSVframe, int low_h, int high_h, int low_s, int high_s, int low_v, int high_v);
	Point2f FindCentroid(vector<vector<Point>> contours);
	void ShowContours(vector<vector<Point>> contours, Mat frame);
	void DrawMinCircle(Point2f center, vector<vector<Point>> contours, Mat frame);
	void DrawMinRect(vector<vector<Point>> contours, Mat frame);
	double GeometricRatio(float RealLength);
	//double FocalLength(double PixelLength, double DistToNozzle, double width);
	double DistancePoints(Point2f Point1, Point2f Point2, double GeometricRatio);
	void DrawPointOnCircle(Point Center, double Radius, int PointNumber);
	void DrawPointOnLine(Point Point1, Point Point2);
	void ShapeDetector(vector<vector<Point>> contours);


	bool ExistedContours =false;
	float RadiusMinCircle;
	Point2f Points_minRect[4];
	double AreaCircle, AreaRect, AreaContours;
	string ShapeType;

	~PrintedObj();
};

