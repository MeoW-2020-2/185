#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");  //setlocale - позволяет настраивать локальные параметры (LC_ALL - применяется для всей программы, "Russian" - установка русского языка)

	char filename[80];  //создание переменной символьного типа [максимальное кол-во символов - 80]
	cout << "Введите имя файла, в который хотите внести измеениея, и нажмите Enter" << endl;    //вывод в консоль << "Выводимые данные" << переход на новую строку;
	cin.getline(filename, 80);  //получение значения, введенного пользователем.запись в переменную(переменная, макс. кол-во символов);
	cout << "Открыть файл ";  //вывод в консоль << "Открыть файл ";
	cout << filename << endl;  //вывод в консоль << переменная с именем файла << переход на новую строку;


	//IMAGE UPLOAD
	Mat img = imread(filename, 1);  //создание матрицы с именем img = чтение файла(имя файла, тип вывода цвета - 1 = IMREAD_COLOR - всегда конвертировать изображение в трехканальное цветное изображение BGR);
	imshow("Исходное изображение", img);  //вывод изображения(имя окна, выводимая матрица);


	//CANNY
	Mat src_gray;  //создание пустой матрицы с именем src_gray;
	Mat canny_output; //создание пустой матрицы с именем canny_output;

	cvtColor(img, src_gray, COLOR_RGB2GRAY);  //конвертация цвета(входное изображение, матрица для записи выходного изображения, тип конвертации - rgb в серое);
 	blur(src_gray, src_gray, Size(3, 3));  //размытие изображения для сглаживания контуров(входное изображение, матрица для записи результата, степень размытия);

	double otsu_thresh_val = threshold(src_gray, img, 0, 255, THRESH_BINARY | THRESH_OTSU);  //определения порога изображения
	double height_thresh_val = otsu_thresh_val, lower_thresh_val = otsu_thresh_val * 0.5;  //

	cout << otsu_thresh_val;  //вывод значения

	Canny(src_gray, canny_output, lower_thresh_val, height_thresh_val, 3);  //обнаружения краев изображения(исходное изображение, результат, нижний порог, верхний порог, размер апертуры для оператора Sobel);

	//char* source_gray_window = "Серое изображение";
	namedWindow("Серое изображение", WINDOW_AUTOSIZE);
	imshow("Серое изображение", canny_output);
	//imwrite("grib.png", canny_output);


	//FINDCOUNTOUTS
	RNG rng(12345);  //генерация случайного числа
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));  //нахождение контуров

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


	//CONTOURS DRAWING
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);  //CV_8UC3 - трехканальное изображение

	for (int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));  //задание цвета
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());  //рисование контуров
		circle(drawing, mc[i], 4, color, -1, 5, 0);  //рисование точек
	}

	namedWindow("Контуры", WINDOW_AUTOSIZE);
	imshow("Контуры", drawing);


	waitKey(0);
	system("pause");
	return 0;
}
 
