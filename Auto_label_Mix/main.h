#ifndef MAIN_H
#define MAIN_H

#include <mainwindow.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/ximgproc.hpp>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <iostream>
#include <QString>
#include <vector>


using namespace cv;
using namespace std;

//class imageContour declaration
class imageContour{

public:

    //variable declarations.
     string objectType;
     float centroid_x, centroid_y, battery_wi, battery_he;
     bool isFound = false;
     QString lower_area;
     QString upper_area;
     QString aspect_ratio_value;

     //function declaration.
    void coordinates(Point2i a, Point2i b, float* topleft_x, float* topleft_y, float* bottomright_x, float* bottomright_y /* float* topright_x, float* topright_y, float* bottomleft_x, float* bottomleft_y*/);
    Mat preprocess(Mat image, QString temp);
    Mat getContours(Mat imgDil, Mat& img, QString temp);
    void txtWrite(string path, int no_of_images);

};

#endif // MAIN_H
