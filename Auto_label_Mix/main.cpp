#include "mainwindow.h"
#include "main.h"
#include <QApplication>
#include <vector>
#include <QString>

MainWindow* wPtr;

  //coordinates function which belongs to class imageContour
  void imageContour::coordinates(Point2i a, Point2i b, float* topleft_x, float* topleft_y, float* bottomright_x, float* bottomright_y/* float* topright_x, float* topright_y, float* bottomleft_x, float* bottomleft_y*/)
  {
      *topleft_x = a.x;
      *topleft_y = a.y;
      *bottomright_x = b.x;
      *bottomright_y = b.y;
  }

  // preprocess function which belongs to class imageContour
  Mat imageContour::preprocess(Mat image, QString temp){

        Mat img = image;
        Mat original = image.clone();
        Mat imgGray, imgBlur, imgCanny, imgDil, imgBlur1;

        cv::medianBlur(original,original,7);
        cv::floodFill(original, cv::Point(150,100), cv::Scalar(255,255,255), 0, Scalar(1, 1, 1),
                          Scalar(1, 1, 1));
        cv::floodFill(original, cv::Point(original.cols - 100,100), cv::Scalar(255,255,255), 0, Scalar(1, 1, 1),
                          Scalar(1, 1, 1));
        cvtColor(original, imgGray, COLOR_BGR2GRAY);

        cv::threshold(imgGray,imgGray,125,255,cv::THRESH_BINARY_INV);

        getContours(imgGray,img, temp);
        return img;
  }

 //getContours function which belongs to class imageContour
  Mat imageContour::getContours(Mat imgDil, Mat &img, QString temp) {

      vector<vector<int>> main_v;
      //vector<string> temp;
      int count = 0;

          vector<vector<Point>> contours;
          vector<Vec4i> hierarchy;
          findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0,0));

          //loop to iterate through each contour.
          for (size_t i = 0; i < contours.size(); i++)
          {
              double lower_area = wPtr->lower_area.toDouble();
              double upper_area = wPtr->upper_area.toDouble();
              double aspect_ratio_value = wPtr->aspect_ratio_value.toDouble();

//              qDebug() <<"lower area " << lower_area;
//              qDebug() <<"upper area " << upper_area;
//              qDebug() <<"aspect ratio value" << aspect_ratio_value;

              cv::Rect contourRect = cv::boundingRect(contours[i]);
              int area = contourRect.area();
              double aspectRatio = contourRect.height/contourRect.width;

              if((area < lower_area) || (area > upper_area) ){
                  continue;
              }
              if(aspectRatio > aspect_ratio_value){
                  continue;
              }
              isFound = true;
              cv::rectangle(img,contourRect,cv::Scalar(0,255,0),2);


              //rectangle size is calculated here, 10% far from the edges of the object.

              contourRect.x = contourRect.x-contourRect.width*0.1;
              if(contourRect.x<0) contourRect.x=0;
              contourRect.y = contourRect.y-contourRect.height*0.1;
              if(contourRect.y<0) contourRect.y= 0;
              contourRect.width = contourRect.width+ contourRect.width*0.2;
              if(contourRect.x + contourRect.width>imgDil.cols-1) contourRect.width = imgDil.cols-1;
              contourRect.height = contourRect.height+ contourRect.height*0.2;
              if(contourRect.y + contourRect.height>imgDil.rows-1) contourRect.height = imgDil.rows-1;


//              imshow("rect", img); // remove this comment to verify the pre-processed image as well as contours in it.
//              waitKey();

              Point2i topleft = contourRect.tl();
              Point2i bottomright = contourRect.br();

              float topleft_x, topleft_y, bottomright_x, bottomright_y;

              coordinates(topleft, bottomright, &topleft_x, &topleft_y, &bottomright_x, &bottomright_y/* &topright_x, &topright_y, &bottomleft_x, &bottomleft_y*/);

              // parameters are stored in .txt files are calculated here.
              centroid_x = ((topleft_x + bottomright_x)/2)/imgDil.cols;
              centroid_y = ((topleft_y + bottomright_y)/2)/imgDil.rows;
              battery_wi = (bottomright_x - topleft_x) / imgDil.cols;
              battery_he = (bottomright_y - topleft_y) / imgDil.rows;

                          QFile file(temp);
                          file.open(QIODevice::Append | QIODevice::Text);
                          QTextStream stream(&file);

                          if (isFound) {

                              count++;
                              stream << "0 ";

                              stream <<centroid_x<< " ";

                              stream <<centroid_y<< " ";

                              stream <<battery_wi<< " ";

                              stream <<battery_he<< Qt::endl;

                              file.flush();
                              stream.flush();
                          }
                          file.close();

//              temp.push_back(to_string(centroid_x));
//              temp.push_back(to_string(centroid_y));
//              temp.push_back(to_string(battery_wi));
//              temp.push_back(to_string(battery_he));


          }
          qDebug() <<"No. of images where contour is detected " << count;

          return img;
    }


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    wPtr = &w;
    w.show();
    return a.exec();
}
