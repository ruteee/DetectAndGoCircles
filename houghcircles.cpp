#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
            "Usage:\n"
            "./houghcircles <image_name>, Default is pic1.png\n" << endl;
}

int main(int argc, char** argv)
{
    const char* filename = argc >= 2 ? argv[1] : "board.jpg";

    Mat img = imread(filename, 1);

    //imshow("detected circles", img);
    if(img.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }

    Mat color[7];

    Mat img_new;
    Mat cimg;

    cvtColor(img, cimg, COLOR_BGR2GRAY);
    Mat redColorOnly;
    Mat hsv_img;

    cvtColor(img, hsv_img,COLOR_BGR2HSV);
    medianBlur(hsv_img, img_new, 1);
    GaussianBlur(hsv_img,img_new,  Size(9, 9), 0.5, 0.5);

//-------------------------------Cores----------------------------------------------------
    //red
    Mat red;
    inRange(hsv_img, Scalar(160, 80, 100),Scalar(180, 255, 255), red);
    GaussianBlur(red, red, Size(9, 9), 4, 4);
    //imshow("red", red);

    //yellow
    Mat yellow;
    inRange(hsv_img, Scalar(24, 100, 200),Scalar(30, 255, 255), yellow);
    GaussianBlur(yellow, yellow, Size(9, 9), 4, 4);
    //imshow("yellow", yellow);

    //cyan
    Mat cyan;
    inRange(img_new, Scalar(90, 120, 250), Scalar(120,255,255), cyan);
    GaussianBlur(cyan,cyan,  Size(9, 9), 4, 4);
    //imshow("cyan", cyan);

    //magenta
    Mat magenta;
    inRange(img_new, Scalar(146, 89, 89),Scalar(160, 146, 202), magenta);
    GaussianBlur(magenta, magenta, Size(9, 9), 4, 4);
    //imshow("magenta", magenta);

    //black
    Mat black;
    inRange(img_new, Scalar(80, 40, 130),Scalar(130, 100, 170), black);
    GaussianBlur(black, black, Size(9, 9), 4, 4);
    //imshow("black",black);

    //blue
    Mat blue;
    inRange(img_new, Scalar(85, 110, 200), Scalar(112,220,245), blue);
    GaussianBlur(blue,blue,  Size(9, 9), 4, 4);
    imshow("blue", blue);

    //green
    Mat green;
    inRange(img_new, Scalar(70, 60, 180), Scalar(95,115,255), green);
    GaussianBlur(green,green,  Size(9, 9), 4, 4);
    //imshow("green", green);

//-------------------------------Fim - Cores---------------------------------------------------- //

//--------------------------------Circles-------------------------------------------------------//
    vector<Vec3f> circles;
    HoughCircles(blue, circles, CV_HOUGH_GRADIENT, 1, 10,
                 100, 30, 1, 25 // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle(blue, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, CV_AA);
        circle(blue, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, CV_AA);

    }
   printf("%d\n",circles.size());
   imshow("detected circles", blue);


  //-------------------------------Fim - Circles-------------------------------------------//

  //----------------------------------Function---------------------------------------------//
    waitKey();

    return 0;
}
