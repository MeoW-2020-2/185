#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("grib.png", 1);
	imshow("test", img);

	waitKey(0);
	system("pause");
	return 0;
}
