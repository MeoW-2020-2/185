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
	imshow("Исходное изображение", img);

	Mat src_gray;
	Mat canny_output;

	cvtColor(img, src_gray, COLOR_RGB2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	double otsu_thresh_val = threshold(src_gray, img, 0, 255, THRESH_BINARY | THRESH_OTSU);
	double height_thresh_val = otsu_thresh_val, lower_thresh_val = otsu_thresh_val * 0.5;

	cout << otsu_thresh_val;

	Canny(src_gray, canny_output, lower_thresh_val, height_thresh_val, 3);
	
	//char* source_gray_window = "Серое изображение";
	namedWindow("Серое изображение", WINDOW_AUTOSIZE);
	imshow("Серое изображение", canny_output);
	imwrite("grib.png", canny_output);

	waitKey(0);
	system("pause");
	return 0;
}
