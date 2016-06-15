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

void capturar_ciculos(vector<Vec3f> &circulos);

int main(int argc, char** argv)
{
	vector<Vec3f> circulos(7);
	capturar_ciculos(circulos);

//     const char* filename = argc >= 2 ? argv[1] : "board.jpg";
//
//     Mat img = imread(filename, 1);
//
//     //imshow("detected circles", img);
//     if(img.empty())
//     {
//         help();
//         cout << "can not open " << filename << endl;
//         return -1;
//     }
//
//     Mat color[7];
//
//     Mat img_new;
//     Mat cimg;
//
//     cvtColor(img, cimg, COLOR_BGR2GRAY);
//     Mat redColorOnly;
//     Mat hsv_img;
//
//     cvtColor(img, hsv_img,COLOR_BGR2HSV);
//     //medianBlur(hsv_img, img_new, 1);
//     GaussianBlur(hsv_img,img_new,  Size(9, 9), 0.5, 0.5);
//
// //-------------------------------Cores----------------------------------------------------
//     //red
//     Mat red;
//     inRange(hsv_img, Scalar(160, 80, 100),Scalar(180, 255, 255), red);
//     GaussianBlur(red, red, Size(9, 9), 4, 4);
//
//     //yellow
//     Mat yellow;
//     inRange(hsv_img, Scalar(24, 100, 200),Scalar(30, 255, 255), yellow);
//     GaussianBlur(yellow, yellow, Size(9, 9), 4, 4);
//
//     //cyan
//     Mat cyan;
//     inRange(img_new, Scalar(90, 120, 250), Scalar(120,255,255), cyan);
//     GaussianBlur(cyan,cyan,  Size(9, 9), 4, 4);
//
//     //magenta
//     Mat magenta;
//     inRange(img_new, Scalar(150, 89, 180),Scalar(160, 146, 200), magenta);
//     GaussianBlur(magenta, magenta, Size(9, 9), 4, 4);
//
//     //black
//     Mat black;
//     inRange(img_new, Scalar(80, 40, 130),Scalar(130, 100, 170), black);
//     GaussianBlur(black, black, Size(9, 9), 4, 4);
//
//     //blue
//     Mat blue;
//     inRange(img_new, Scalar(85, 110, 200), Scalar(112,220,245), blue);
//     GaussianBlur(blue,blue,  Size(9, 9), 4, 4);
//
//     //green
//     Mat green;
//     inRange(img_new, Scalar(70, 60, 180), Scalar(95,115,255), green);
//     GaussianBlur(green,green,  Size(9, 9), 4, 4);
//
// //-------------------------------Fim - Cores---------------------------------------------------- //
//
// //--------------------------------Circles-------------------------------------------------------//
// 	// for( size_t i = 0; i < circles.size(); i++ )
// 	// {
// 	//    Vec3i c = circles[0];
// 	//    circle(blue, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, CV_AA);
// 	//    circle(blue, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, CV_AA);
// 	//
// 	// }
// 	// printf("%lu\n",circles.size());
// 	// Blue circle;
// 	vector<Vec3f> circles;
// 	Vec3i c;
//     HoughCircles(blue, circles, CV_HOUGH_GRADIENT, 1, 10,
//                 100, 30, 1, 25 // change the last two parameters
//                                 // (min_radius & max_radius) to detect larger circles
//                 );
// 	printf("Azul: %lu\n",circles.size());
//     c = circles[0];
// 	circle(blue, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, CV_AA);
// 	circle(blue, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, CV_AA);
//
// 	// Magenta circle
// 	HoughCircles(magenta, circles, CV_HOUGH_GRADIENT, 1, 10,
// 				100, 30, 1, 25 // change the last two parameters
// 							// (min_radius & max_radius) to detect larger circles
// 			);
// 	printf("Magenta: %lu\n",circles.size());
// 	c = circles[0];
// 	circle(magenta, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, CV_AA);
// 	circle(magenta, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, CV_AA);
//
// 	//
// 	HoughCircles(green, circles, CV_HOUGH_GRADIENT, 1, 10,
// 				100, 30, 1, 25 // change the last two parameters
// 							// (min_radius & max_radius) to detect larger circles
// 			);
// 	printf("Verde: %lu\n",circles.size());
// 	c = circles[0];
// 	circle(green, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, CV_AA);
// 	circle(green, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, CV_AA);
//
// 	HoughCircles(cyan, circles, CV_HOUGH_GRADIENT, 1, 10,
// 				100, 30, 1, 25 // change the last two parameters
// 							// (min_radius & max_radius) to detect larger circles
// 			);
// 	printf("Ciano: %lu\n",circles.size());
// 	c = circles[0];
// 	circle(cyan, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, CV_AA);
// 	circle(cyan, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, CV_AA);
//
//
// 	HoughCircles(yellow, circles, CV_HOUGH_GRADIENT, 1, 10,
// 				100, 30, 1, 25 // change the last two parameters
// 							// (min_radius & max_radius) to detect larger circles
// 			);
// 	printf("Amarelo: %lu\n",circles.size());
// 	c = circles[0];
// 	circle(yellow, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, CV_AA);
// 	circle(yellow, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, CV_AA);
//
//
// 	HoughCircles(red, circles, CV_HOUGH_GRADIENT, 1, 10,
// 				100, 30, 1, 25 // change the last two parameters
// 							// (min_radius & max_radius) to detect larger circles
// 			);
// 	printf("Vermelho: %lu\n",circles.size());
// 	c = circles[0];
// 	circle(red, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, CV_AA);
// 	circle(red, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, CV_AA);
//
//
// 	HoughCircles(black, circles, CV_HOUGH_GRADIENT, 1, 10,
// 				100, 30, 1, 25 // change the last two parameters
// 							// (min_radius & max_radius) to detect larger circles
// 			);
// 	printf("Preto: %lu\n",circles.size());
// 	c = circles[0];
// 	circle(black, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, CV_AA);
// 	circle(black, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, CV_AA);
// //-------------------------------Fim - Circles-------------------------------------------//
//
// 	// Janelas com imagens
// 	imshow("red", red);
// 	imshow("yellow", yellow);
// 	imshow("cyan", cyan);
// 	imshow("magenta", magenta);
// 	imshow("black",black);
// 	imshow("blue", blue);
// 	imshow("green", green);
//
// //----------------------------------Function---------------------------------------------//
//     waitKey();
    return 0;
}

void capturar_ciculos(vector<Vec3f> &circulos) {

	CvCapture* capture = 0;
	Mat img;
	Mat img_new;
	Mat hsv_img;
	capture = cvCaptureFromCAM(CV_CAP_ANY); //0=default, -1=any camera, 1..99=your camera
	if (!capture) {
		cout << "No camera detected" << endl;
	}
	IplImage* iplImg = cvQueryFrame(capture);
	img = iplImg;

	imshow("Camera", img);

	waitKey(0);

	cvReleaseCapture( &capture );
	cvDestroyWindow( "result" );

	cvtColor(img, hsv_img,COLOR_BGR2HSV);
	GaussianBlur(hsv_img,img_new,  Size(9, 9), 0.5, 0.5);

//-------------------------------Cores----------------------------------------------------
    Mat red;
    inRange(hsv_img, Scalar(160, 80, 100),Scalar(180, 255, 255), red);
    GaussianBlur(red, red, Size(9, 9), 4, 4);
    Mat yellow;
    inRange(hsv_img, Scalar(24, 100, 200),Scalar(30, 255, 255), yellow);
    GaussianBlur(yellow, yellow, Size(9, 9), 4, 4);
    Mat cyan;
    inRange(img_new, Scalar(90, 120, 250), Scalar(120,255,255), cyan);
    GaussianBlur(cyan,cyan,  Size(9, 9), 4, 4);
    Mat magenta;
    inRange(img_new, Scalar(150, 89, 180),Scalar(160, 146, 200), magenta);
    GaussianBlur(magenta, magenta, Size(9, 9), 4, 4);
    Mat black;
    inRange(img_new, Scalar(80, 40, 130),Scalar(130, 100, 170), black);
    GaussianBlur(black, black, Size(9, 9), 4, 4);
    Mat blue;
    inRange(img_new, Scalar(85, 110, 200), Scalar(112,220,245), blue);
    GaussianBlur(blue,blue,  Size(9, 9), 4, 4);
    Mat green;
    inRange(img_new, Scalar(70, 60, 180), Scalar(95,115,255), green);
    GaussianBlur(green,green,  Size(9, 9), 4, 4);
//-------------------------------Fim - Cores---------------------------------------------------- //
//--------------------------------Circles-------------------------------------------------------//
/*
 *	0 - Blue
 *	1 - Magenta
 *	2 - Green
 *	3 - Cyan
 *	4 - Yellow
 *	5 - Red
 *	6 - Black
 */
	vector<Vec3f> circles;
	Vec3i c;
    HoughCircles(blue, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
    circulos[0] = circles[0];
	HoughCircles(magenta, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[1] = circles[0];
	HoughCircles(green, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[2] = circles[0];
	HoughCircles(cyan, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[3] = circles[0];
	HoughCircles(yellow, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[4] = circles[0];
	HoughCircles(red, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[5] = circles[0];
	HoughCircles(black, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[6] = circles[0];
//-------------------------------Fim - Circles-------------------------------------------//
	if (DEBUG) {
		// Janelas com imagens
		circle(blue, Point(circulos[0][0], circulos[0][1]), circulos[0][2], Scalar(0,0,255), 3, CV_AA);
		circle(blue, Point(circulos[0][0], circulos[0][1]), 2, Scalar(0,255,0), 3, CV_AA);
		circle(magenta, Point(circulos[1][0], circulos[1][1]), circulos[1][2], Scalar(0,0,255), 3, CV_AA);
		circle(magenta, Point(circulos[1][0], circulos[1][1]), 2, Scalar(0,255,0), 3, CV_AA);
		circle(green, Point(circulos[2][0], circulos[2][1]), circulos[2][2], Scalar(0,0,255), 3, CV_AA);
		circle(green, Point(circulos[2][0], circulos[2][1]), 2, Scalar(0,255,0), 3, CV_AA);
		circle(cyan, Point(circulos[3][0], circulos[3][1]), circulos[3][2], Scalar(0,0,255), 3, CV_AA);
		circle(cyan, Point(circulos[3][0], circulos[3][1]), 2, Scalar(0,255,0), 3, CV_AA);
		circle(yellow, Point(circulos[4][0], circulos[4][1]), circulos[4][2], Scalar(0,0,255), 3, CV_AA);
		circle(yellow, Point(circulos[4][0], circulos[4][1]), 2, Scalar(0,255,0), 3, CV_AA);
		circle(red, Point(circulos[5][0], circulos[5][1]), circulos[5][2], Scalar(0,0,255), 3, CV_AA);
		circle(red, Point(circulos[5][0], circulos[5][1]), 2, Scalar(0,255,0), 3, CV_AA);
		circle(black, Point(circulos[6][0], circulos[6][1]), circulos[6][2], Scalar(0,0,255), 3, CV_AA);
		circle(black, Point(circulos[6][0], circulos[6][1]), 2, Scalar(0,255,0), 3, CV_AA);

		imshow("blue", blue);		waitKey();
		imshow("magenta", magenta);	waitKey();
		imshow("green", green);		waitKey();
		imshow("cyan", cyan);		waitKey();
		imshow("yellow", yellow);	waitKey();
		imshow("red", red);			waitKey();
		imshow("black",black);		waitKey();
	}
}
