#include <stdlib.h>
#include "armrulelib_novo.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

#define DEBUG 1
#define CONV 1

struct Ponto {
	double x;
	double y;
	double z;
	double phi;
};

using namespace cv;

void capturar_ciculos(vector<Vec3f> &circulos);
void mover_suave(Ponto source, Ponto dest);
void init_pontos(Ponto pontos[6], vector<Vec3f> circulos);

// using namespace std;

int main(int argc, char** argv) {
	init();
	if (argc < 7) {
		printf("Quantidade de argumentos insuficiente: %d", argc);
		exit(1);
	}

	// Detecção de circulos coloridos
	vector<Vec3f> circulos(7);
	// int key = 0;
	// do {
	// 	capturar_ciculos(circulos);
	// 	key = waitKey(100);
	// 	printf("Tecla: %d\n", key);
	// } while (key != 1048683 || key == -1);
	soltar();
	sleep(5);
	Ponto pontos[7];
	init_pontos(pontos, circulos);
	if (DEBUG) printf("Mover para caneta\n");
	// Mover para caneta
	mover(pontos[6].x, pontos[6].y, pontos[6].z, pontos[6].phi);
	sleep(5);
	if (DEBUG) printf("Movido para caneta\n");
	// Pegar caneta
	pegar();
	sleep(5);
	if (DEBUG) printf("Iniciar sequência\n");
	Ponto p_ant = pontos[6];
	// Mover entre cada ponto
	for (int i = 1; i < 7; i++) {
		Ponto p = pontos[atoi(argv[i]) - 1];
		if (DEBUG) printf("Ponto i: %d\n", i);
		mover_suave(p_ant, p);
		p_ant = p;
	}

	// Mover para preto
	if (DEBUG) printf("Voltar para preto\n");
	mover_suave(p_ant, pontos[6]);

	if (DEBUG) printf("Voltou para preto\n");
}

void mover_suave(Ponto source, Ponto dest) {
	Ponto p;
	p.x = (dest.x - source.x) / 10.0;
	p.y = (dest.y - source.y) / 10.0;
	p.z = (dest.z - source.z) / 10.0;
	p.phi = (dest.phi - source.phi) / 10.0;

	for (int i = 0; i < 10; i++) {
		if (DEBUG) printf("\tPasso i: %d\n", i);
		if (DEBUG) printf("\tx: %lf\ty: %lf\tz: %lf\tphi: %lf\n", source.x + p.x * (i+1), source.y + p.y * (i+1), source.z + p.z * (i+1), source.phi + p.phi * (i+1));
		mover(source.x + p.x * (i+1), source.y + p.y * (i+1), source.z + p.z * (i+1), source.phi + p.phi * (i+1));
		usleep(500000);
	}
}

void init_pontos(Ponto pontos[6], vector<Vec3f> circulos) {
	/*
	 *	0 - Blue
	 *	1 - Magenta
	 *	2 - Green
	 *	3 - Cyan
	 *	4 - Yellow
	 *	5 - Red
	 *	6 - Black
	 */
	pontos[0].x = 25.9499;	pontos[0].y = -7.9337;	pontos[0].z = 16;	pontos[0].phi = -3;
	pontos[1].x = 30;	pontos[1].y = -4.5262;	pontos[1].z = 16;	pontos[1].phi = 8;
	pontos[2].x = 21.8025;	pontos[2].y = 3.0641;	pontos[2].z = 16;	pontos[2].phi = 2;
	pontos[3].x = 21.6122;	pontos[3].y = -4.2009;	pontos[3].z = 16;	pontos[3].phi = 2;
	pontos[4].x = 26.5427;	pontos[4].y = 5.6418;	pontos[4].z = 16;	pontos[4].phi = -3;
	pontos[5].x = 30;	pontos[5].y = 1.5142;	pontos[5].z = 16;	pontos[5].phi = 8;
	pontos[6].x = 15.9611;	pontos[6].y = 0;		pontos[6].z = 18.9398;	pontos[6].phi = 8;
	// pontos[0].x = (abs(circulos[0][0] - circulos[6][0]) * CONV) + pontos[6].x;
	// pontos[0].y = (-1)*(abs(circulos[0][1] - circulos[6][1]) * CONV) + pontos[6].y;
	// pontos[0].z = pontos[6].z;
	// pontos[0].phi = pontos[6].phi;

	// pontos[1].x = (abs(circulos[0][0] - circulos[6][0]) * CONV) + pontos[6].x;
	// pontos[1].y = (-1)*(abs(circulos[0][1] - circulos[6][1]) * CONV) + pontos[6].y;
	// pontos[1].z = pontos[6].z;
	// pontos[1].phi = pontos[6].phi;

	// pontos[2].x = (abs(circulos[0][0] - circulos[6][0]) * CONV) + pontos[6].x;
	// pontos[2].y = (-1)*(abs(circulos[0][1] - circulos[6][1]) * CONV) + pontos[6].y;
	// pontos[2].z = pontos[6].z;
	// pontos[2].phi = pontos[6].phi;

	// pontos[3].x = (abs(circulos[0][0] - circulos[6][0]) * CONV) + pontos[6].x;
	// pontos[3].y = (-1)*(abs(circulos[0][1] - circulos[6][1]) * CONV) + pontos[6].y;
	// pontos[3].z = pontos[6].z;
	// pontos[3].phi = pontos[6].phi;

	// pontos[4].x = (abs(circulos[0][0] - circulos[6][0]) * CONV) + pontos[6].x;
	// pontos[4].y = (-1)*(abs(circulos[0][1] - circulos[6][1]) * CONV) + pontos[6].y;
	// pontos[4].z = pontos[6].z;
	// pontos[4].phi = pontos[6].phi;

	// pontos[5].x = (abs(circulos[0][0] - circulos[6][0]) * CONV) + pontos[6].x;
	// pontos[5].y = (-1)*(abs(circulos[0][1] - circulos[6][1]) * CONV) + pontos[6].y;
	// pontos[5].z = pontos[6].z;
	// pontos[5].phi = pontos[6].phi;
}

void capturar_ciculos(vector<Vec3f> &circulos) {
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
		printf("No camera detected\n");
	}
	// img = imread(f, 1);
	img = cvQueryFrame(capture);

	// imshow("Camera", img);

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
	if (DEBUG) printf("Detecção de Cores\n");
	HoughCircles(blue, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[0] = circles[0];
	if (DEBUG) printf("Azul: %lu\n", circles.size());

	HoughCircles(magenta, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[1] = circles[0];
	if (DEBUG) printf("Mag: %lu\n", circles.size());

	HoughCircles(green, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[2] = circles[0];
	if (DEBUG) printf("Verde: %lu\n", circles.size());

	HoughCircles(cyan, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[3] = circles[0];
	if (DEBUG) printf("Cyan: %lu\n", circles.size());

	HoughCircles(yellow, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[4] = circles[0];
	if (DEBUG) printf("Ye: %lu\n", circles.size());

	HoughCircles(red, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[5] = circles[0];
	if (DEBUG) printf("Red: %lu\n", circles.size());

	HoughCircles(black, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 1, 25);
	circulos[6] = circles[0];
	if (DEBUG) printf("Black: %lu\n", circles.size());
	if (DEBUG) printf("---------------------\n");
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

		imshow("img",img);
	}
	cvReleaseCapture( &capture );
}
