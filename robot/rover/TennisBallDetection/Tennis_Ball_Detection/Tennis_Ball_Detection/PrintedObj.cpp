#include "PrintedObj.h"

//Local method to sort contours by area
bool compareContourAreas(vector<Point> contour1, vector<Point> contour2) {
	double i = fabs(contourArea(Mat(contour1)));
	double j = fabs(contourArea(Mat(contour2)));
	return (i < j);
}

PrintedObj::PrintedObj(int CameraNumber)
{
	//Declare a video instance
	VideoCapture cap1;

	//put number of camera 0=webcam 1=camera
	cap1.open(CameraNumber);

	//check connection of camera
	if (!cap1.isOpened())
	{
		cout << "\nThe Camera cannot be identifeid";
		_getch();
		exit(0);
	}
	else
	{
		cap = cap1;
	}

	//load distortion matrix from intrinsics.xml file
	FileStorage fs;
	fs.open("intrinsics.xml", FileStorage::READ);
	if (fs.isOpened())
	{
		cout << "\nimage width: " << (int)fs["image_width"];
		cout << "\nimage height: " << (int)fs["image_height"];

		fs["camera_matrix"] >> intrinsic_matrix_loaded;
		fs["distortion_coefficients"] >> distortion_coeffs_loaded;
		cout << "\nintrinsic matrix:" << intrinsic_matrix_loaded;
		cout << "\ndistortion coefficients: " << distortion_coeffs_loaded << endl;
	}
	else
	{
		cout << "\nThe intrinsic.xml file does not exist ";
		_getch();
		exit(0);

	}

}

//get the current frame of camera
Mat PrintedObj::GetFrame()
{
	Mat frameInput;
	cap >> frameInput;
	return frameInput;
}

//apply distortion matrix to frame
void PrintedObj::UndisrortedFrame(Mat &frame)
{
	Size image_size;
	image_size = frame.size();
	Mat map1, map2;
	initUndistortRectifyMap(
		intrinsic_matrix_loaded,
		distortion_coeffs_loaded,
		cv::Mat(),
		intrinsic_matrix_loaded,
		image_size,
		CV_16SC2,
		map1,
		map2
		);
	// Just run the camera to the screen, now showing the raw and
	// the undistorted image.
	remap(
		frame,
		frame,
		map1,
		map2,
		INTER_LINEAR,
		BORDER_CONSTANT,
		Scalar()
		);
}


vector<vector<Point>> PrintedObj::FindContours(Mat inputFrame, Mat &HSVframe, int low_h, int high_h, int low_s, int high_s, int low_v, int high_v)
{
	//apply Gaussian filter to reduce noises
	GaussianBlur(inputFrame, HSVframe, Size(5, 5), 3, 3);

	//convert RGB to HSV
	cvtColor(inputFrame, HSVframe, COLOR_RGB2HSV);

	//apply values of the range of Hue,Saturation and value
	inRange(HSVframe, Scalar(low_h, low_s, low_v), Scalar(high_h, high_s, high_v), HSVframe);
	GaussianBlur(HSVframe, HSVframe, Size(5, 5), 3, 3);

	//remove redundant pixels around the boundry of contour
	erode(HSVframe, HSVframe, Mat(), Point(-1, -1), 3, BORDER_CONSTANT, morphologyDefaultBorderValue());
	
	//compensate pixels near the boundry of contour
	dilate(HSVframe, HSVframe, Mat(), Point(-1, -1), 2, BORDER_CONSTANT, morphologyDefaultBorderValue());

	//declare contour object
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Mat temp;

	//copy HSV frame into temp
	HSVframe.copyTo(temp);

	//find contour
	findContours(temp, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	if (contours.empty())
	{
		cout << "\ncontours not found !!";
		ExistedContours = false;
	}
	else
	{
		
		ExistedContours = true;
		sort(contours.begin(), contours.end(), compareContourAreas);
		return contours;
	}
}

Point2f PrintedObj::FindCentroid(vector<vector<Point>> contours)
{
	vector<Point2f> CentroidPoint(1);
	if (ExistedContours)
	{
		vector<Moments> mu(1);
		mu[0] = moments(contours[contours.size() - 1], false);


		// get the centroid of contour.
		vector<Point2f> mc(1);
		mc[0] = Point2f(mu[0].m10 / mu[0].m00, mu[0].m01 / mu[0].m00);

		CentroidPoint[0] = mc[0];

	}
	else
	{
		cout << "\nThe Centroid cannot be calculated!";
	}
	return CentroidPoint[0];
}

void PrintedObj::ShowContours(vector<vector<Point>> contours, Mat frame)
{
	Scalar color = Scalar(0, 0, 255); // B G R values
	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(frame, contours, i, color, 3, 8, noArray(), 0, Point());
	}
}

void PrintedObj::DrawMinCircle(Point2f center, vector<vector<Point>> contours, Mat frame)
{
	if (ExistedContours)
	{
		//sort contours by the area
		AreaCircle = contourArea(contours[contours.size() - 1], false);

		float radius = 0;
		Scalar color = Scalar(0, 0, 255); // B G R values

		//draw circle around the contour and also return the radius of the circle
		minEnclosingCircle(contours[contours.size() - 1], center, radius);

		//draw circle
		circle(frame, center, radius, color, 4, 8, 0);

		//return the radius 
		RadiusMinCircle = radius;

	}
	else
	{
		cout << "\nMinCricle cannot be drawn!";
	}
}

void PrintedObj::DrawMinRect(vector<vector<Point>> contours, Mat frame)
{
	if (ExistedContours)
	{
		//sort contours by the area
		AreaRect = contourArea(contours[contours.size() - 1], false);

		//declare a vectors of rectangle 
		vector<RotatedRect> minRect(contours.size());

		//define the area of the vector according to the biggest contour
		minRect[0] = minAreaRect(Mat(contours[contours.size() - 1]));

		Point2f rect_points[4];

		//initial the points of corners
		minRect[0].points(rect_points);

		//Define a color
		Scalar color = Scalar(0, 0, 255); // B G R values

		//draw lines between corner points
		for (int j = 0; j < 4; j++)
		{
			line(frame, rect_points[j], rect_points[(j + 1) % 4], color, 4, 8, 0);
			Points_minRect[j] = rect_points[j];
		}
	}
	else
	{
		cout << "\nMinRect cannot be drawn!";
	}
}

double PrintedObj::GeometricRatio(float RealLength)
{
	if (AreaRect != 0)
	{
		//Calculate distance between to points by pixel
		//we assumed that the geometric ratio in both direction(Horizontal and Vertical) have the same value 
		float length1 = norm(Mat(Points_minRect[0]), Mat(Points_minRect[1]));
		
		//calculate ratio by the known object
		//to avoid deviation put the camera exactly perpendicular to the pattern
		float ratio = length1 / RealLength;
		return ratio;
	}
	else
	{
		cout << "\nGeometricRatio Cannot be calculated !";
		return 0.0;
	}
}

//double PrintedObj::FocalLength(double PixelLength, double DistToNozzle, double width)
//{
//
//	return 0.0;
//}

//real distance between two points
double PrintedObj::DistancePoints(Point2f Point1, Point2f Point2, double GeometricRatio)
{
	double res = norm(Mat(Point1), Mat(Point2));

	//return real length
	return res / GeometricRatio;

}

void PrintedObj::DrawPointOnCircle(Point Center, double Radius, int PointNumber)
{

}

void PrintedObj::DrawPointOnLine(Point Point1, Point Point2)
{

}

//detect shape of object by vertices
void PrintedObj::ShapeDetector(vector<vector<Point>> contours)
{
	if (ExistedContours)
	{

		double perimter = arcLength(Mat(contours[contours.size() - 1]), true);
		vector<Point> contours2;

		//draw polygon around the contour
		approxPolyDP(contours[contours.size() - 1],contours2, 0.04*perimter, true);
		if (contours2.size() == 3)
		{
			ShapeType = "Triangle";
		}
		else if (contours2.size() == 4)
		{
			Rect bound = boundingRect(contours2);
			float ar = bound.width / float(bound.height);
			if (ar >= 0.95 && ar <= 1.05)
			{
				ShapeType = "Square";
			}
			else
			{
				ShapeType = "Rectangle";
			}
		}
		else
		{
			ShapeType = "Circle";
		}
	}

}
PrintedObj::~PrintedObj()
{
}
