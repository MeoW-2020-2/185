#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat img = imread("grib.png", 1);
	//IplImage* img = cvLoadImage("grib.pmg");
	imshow("Load", img);

	waitKey(0);
	system("pause");
	return 0;
}