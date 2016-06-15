#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <iostream>

#define DEBUG 1

using namespace cv;
using namespace std;

static void help()
{
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
            "Usage:\n"
            "./houghcircles <image_name>, Default is pic1.png\n" << endl;
}

void capturar_ciculos(vector<Vec3f> &circulos, char* f);

int main(int argc, char** argv) {
  vector<Vec3f> circulos(7);
  capturar_ciculos(circulos, "1.jpg");
  capturar_ciculos(circulos, "2.jpg");
  capturar_ciculos(circulos, "3.jpg");
  capturar_ciculos(circulos, "4.jpg");
  capturar_ciculos(circulos, "5.jpg");
  capturar_ciculos(circulos, "6.jpg");
  capturar_ciculos(circulos, "7.jpg");
  return 0;
}

void capturar_ciculos(vector<Vec3f> &circulos, char* f) {
/*
 *	0 - Blue
 *	1 - Magenta
 *	2 - Green
 *	3 - Cyan
 *	4 - Yellow
 *	5 - Red
 *	6 - Black
 */
	CvCapture* capture = 0;
	Mat img;
	Mat img_new;
	Mat hsv_img;
	capture = cvCaptureFromCAM(CV_CAP_ANY); //0=default, -1=any camera, 1..99=your camera
	if (!capture) {
		cout << "No camera detected" << endl;
	}
  // img = imread(f, 1);
	img = cvQueryFrame(capture);

	imshow("Camera", img);
  waitKey(0);
	// cvReleaseCapture( &capture );
	GaussianBlur(img, img_new,  Size(9, 9), 0.5, 0.5);
	cvtColor(img_new, hsv_img, COLOR_BGR2HSV);

//-------------------------------Cores----------------------------------------------------
    Mat red;
    inRange(hsv_img, Scalar(160, 80, 100),Scalar(180, 255, 255), red);
    GaussianBlur(red, red, Size(9, 9), 4, 4);
    Mat yellow;
    inRange(hsv_img, Scalar(24, 100, 200),Scalar(30, 255, 255), yellow);
    GaussianBlur(yellow, yellow, Size(9, 9), 4, 4);
    Mat cyan;
    inRange(hsv_img, Scalar(104, 120, 240), Scalar(120,255,255), cyan);
    GaussianBlur(cyan,cyan,  Size(9, 9), 4, 4);
    Mat magenta;
    inRange(hsv_img, Scalar(130, 89, 168),Scalar(160, 146, 200), magenta);
    GaussianBlur(magenta, magenta, Size(9, 9), 4, 4);
    Mat black;
    inRange(hsv_img, Scalar(70, 40, 115),Scalar(140, 220, 187), black);
    GaussianBlur(black, black, Size(9, 9), 4, 4);
    Mat blue;
    inRange(hsv_img, Scalar(100, 120, 200), Scalar(120,225,245), blue);
    GaussianBlur(blue,blue,  Size(9, 9), 4, 4);
    Mat green;
    inRange(hsv_img, Scalar(70, 60, 180), Scalar(95,115,255), green);
    GaussianBlur(green,green,  Size(9, 9), 4, 4);
//-------------------------------Fim - Cores---------------------------------------------------- //
//--------------------------------Circles-------------------------------------------------------//
	vector<Vec3f> circles(1);
  printf("%s\n", f);
  HoughCircles(blue, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
  circulos[0] = circles[0];
  printf("Azul: %lu\n", circles.size());

  HoughCircles(magenta, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[1] = circles[0];
  printf("Mag: %lu\n", circles.size());

	HoughCircles(green, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[2] = circles[0];
  printf("Verde: %lu\n", circles.size());

	HoughCircles(cyan, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[3] = circles[0];
  printf("Cyan: %lu\n", circles.size());

	HoughCircles(yellow, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[4] = circles[0];
  printf("Ye: %lu\n", circles.size());

	HoughCircles(red, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[5] = circles[0];
  printf("Red: %lu\n", circles.size());

	HoughCircles(black, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[6] = circles[0];
	printf("Black: %lu\n", circles.size());
  printf("---------------------\n");
//-------------------------------Fim - Circles-------------------------------------------//
	if (DEBUG) {
		// Janelas com imagens
		circle(img, 	Point(circulos[0][0], circulos[0][1]), circulos[0][2],	Scalar(0,0,255), 3, CV_AA);
		circle(img, 	Point(circulos[0][0], circulos[0][1]), 2, 				Scalar(0,255,0), 3, CV_AA);
		circle(img, 	Point(circulos[1][0], circulos[1][1]), circulos[1][2],	Scalar(0,0,255), 3, CV_AA);
		circle(img, 	Point(circulos[1][0], circulos[1][1]), 2,				Scalar(0,255,0), 3, CV_AA);
		circle(img, 	Point(circulos[2][0], circulos[2][1]), circulos[2][2],	Scalar(0,0,255), 3, CV_AA);
		circle(img, 	Point(circulos[2][0], circulos[2][1]), 2,				Scalar(0,255,0), 3, CV_AA);
		circle(img, 	Point(circulos[3][0], circulos[3][1]), circulos[3][2],	Scalar(0,0,255), 3, CV_AA);
		circle(img, 	Point(circulos[3][0], circulos[3][1]), 2, 				Scalar(0,255,0), 3, CV_AA);
		circle(img, 	Point(circulos[4][0], circulos[4][1]), circulos[4][2],	Scalar(0,0,255), 3, CV_AA);
		circle(img, 	Point(circulos[4][0], circulos[4][1]), 2, 				Scalar(0,255,0), 3, CV_AA);
		circle(img, 	Point(circulos[5][0], circulos[5][1]), circulos[5][2],	Scalar(0,0,255), 3, CV_AA);
		circle(img, 	Point(circulos[5][0], circulos[5][1]), 2, 				Scalar(0,255,0), 3, CV_AA);
		circle(img, 	Point(circulos[6][0], circulos[6][1]), circulos[6][2],	Scalar(0,0,255), 3, CV_AA);
		circle(img, 	Point(circulos[6][0], circulos[6][1]), 2, 				Scalar(0,255,0), 3, CV_AA);

		imshow("img",img);		waitKey();
	}
}
