#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	//IMAGE UPLOAD
	Mat img = imread("grib.png", 1);
	imshow("Исходное изображение", img);


	//CANNY
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
	//imwrite("grib.png", canny_output);


	//FINDCOUNTOUTS
	RNG rng(12345);
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));
	
	vector<Moments>mu(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		mu[i] = moments(contours[i], false);
	}

	vector<Point2f>mc(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	for (int i = 0; i < contours.size(); i++) {
		printf("Контур №%d: центр масс - x = %.2f y = %.2f; длина - %.2f \n", i, mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00, arcLength(contours[i], true));
	}

	waitKey(0);
	system("pause");
	return 0;
}
