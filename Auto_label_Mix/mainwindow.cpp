#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.h"
#include "fstream"

extern QString lower_area;
extern QString upper_area;
extern QString aspect_ratio_value;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //values taken from the UI are store in these variables.
    lower_area = ui->lineEdit_Area1->text();
    //lower_area = ui->lineEdit_Area1->textChanged();
    upper_area = ui->lineEdit_Area2->text();
    aspect_ratio_value = ui->lineEdit_AspectRatio->text();

    Mat img;
    //int count=0;
    string path;

    //Asks user for input from file dialog.
    QStringList filenames = QFileDialog::getOpenFileNames(NULL, "Select Images Files", "/home/irs_jay");
        for(int i = 0; i<filenames.count(); i++){

            path = filenames[i].toStdString();
            cout << path;
            img = imread(path);
            int fc = 0;

            //replaces ".jpg" to ".txt" in path variable.
            QString temp = QString::fromStdString(path);
            temp.replace(".jpg",".txt");

            Mat hsv;
            cvtColor(img,img,COLOR_BGR2HSV);
            cv::inRange(img,cv::Scalar(48,110,134),cv::Scalar(255,255,255),img);

            Mat new_image = obj.preprocess(img, temp);

    }
}
