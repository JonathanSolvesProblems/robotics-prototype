#include <opencv2\opencv.hpp>
#include <conio.h>
#include <iostream>
#include "PrintedObj.h"

using namespace std;
using namespace cv;

//global variable
const int max_value_H = 360 / 2;
const int max_value = 255;
const String window_orginal = "Video Capture";
const String window_HSV = "HSV Video";
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;

//Trackbar functions
static void on_low_H_thresh_trackbar(int, void *)
{
	low_H = min(high_H - 1, low_H);
	setTrackbarPos("Low H", window_HSV, low_H);
}
static void on_high_H_thresh_trackbar(int, void *)
{
	high_H = max(high_H, low_H + 1);
	setTrackbarPos("High H", window_HSV, high_H);
}
static void on_low_S_thresh_trackbar(int, void *)
{
	low_S = min(high_S - 1, low_S);
	setTrackbarPos("Low S", window_HSV, low_S);
}
static void on_high_S_thresh_trackbar(int, void *)
{
	high_S = max(high_S, low_S + 1);
	setTrackbarPos("High S", window_HSV, high_S);
}
static void on_low_V_thresh_trackbar(int, void *)
{
	low_V = min(high_V - 1, low_V);
	setTrackbarPos("Low V", window_HSV, low_V);
}
static void on_high_V_thresh_trackbar(int, void *)
{
	high_V = max(high_V, low_V + 1);
	setTrackbarPos("High V", window_HSV, high_V);
}



int main(){
	//create instance of Tennis Ball
	PrintedObj TennisBall(0);

	//Define the window to display original video
	namedWindow(window_orginal,WINDOW_AUTOSIZE);

	//Define the window to display converted image to HSV
	namedWindow(window_HSV, WINDOW_AUTOSIZE);



	// Trackbars to set thresholds for HSV values
	createTrackbar("Low H", window_HSV, &low_H, max_value_H, on_low_H_thresh_trackbar);
	createTrackbar("High H", window_HSV, &high_H, max_value_H, on_high_H_thresh_trackbar);
	createTrackbar("Low S", window_HSV, &low_S, max_value, on_low_S_thresh_trackbar);
	createTrackbar("High S", window_HSV, &high_S, max_value, on_high_S_thresh_trackbar);
	createTrackbar("Low V", window_HSV, &low_V, max_value, on_low_V_thresh_trackbar);
	createTrackbar("High V", window_HSV, &high_V, max_value, on_high_V_thresh_trackbar);

	Mat HSVframe;
	for (;;)
	{
		//get frame of video
		Mat frame = TennisBall.GetFrame();

		//apply distortion matrix to prevent radials shapes on the corners
		TennisBall.UndisrortedFrame(frame);

		//Find contours of Tennis Ball
		vector<vector<Point>> contours = TennisBall.FindContours(frame, HSVframe, low_H, high_H, low_S, high_S, low_V, high_V);
		
		//Calculate the centroid of Tennis ball
		Point2f centroid = TennisBall.FindCentroid(contours);

		//Define a Red color
		Scalar colorRed = Scalar(0, 0, 255); // B G R values

		//Define a Green color
		Scalar colorGreen = Scalar(0, 255, 0); // B G R values

		//Draw a point on the centroid of Tennis Ball
		circle(frame, centroid, 4, colorRed, -1, 8, 0);

		//Draw a Min Circle around Tennis Ball regarding the centroid
		TennisBall.DrawMinCircle(centroid, contours, frame);

		//Draw lines in the center of screen
		line(frame, Point(300, 240), Point(340, 240), colorGreen, 2, 8, 0);
		line(frame, Point(320, 220), Point(320, 260), colorGreen,2, 8, 0);


		//display Distance of centroid from the center of screen
		//screen size : 640*480 px
		int distanceX = (centroid.x - 640 / 2);
		int distanceY = (centroid.y - 480 / 2);

		string Xvalue = "X(px) = " + to_string(distanceX);
		string Yvalue = "Y(px) = " + to_string(distanceY);

		putText(frame, Xvalue, Point(20, 30), FONT_HERSHEY_SIMPLEX, 0.7, colorGreen, 3, 8, false);
		putText(frame, Yvalue, Point(20, 60), FONT_HERSHEY_SIMPLEX, 0.7, colorGreen, 3, 8, false);



		//show videos
		imshow(window_orginal, frame);
		imshow(window_HSV, HSVframe);

		if (waitKey(33) >= 0){
			break;
			destroyAllWindows();
		}
	}

}