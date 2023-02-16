#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "main.h"
#include <QMainWindow>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ximgproc.hpp>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QString>
#include <iostream>
using namespace std;
using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    imageContour obj;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
public:
    QString lower_area = QString::fromStdString("10000");
    QString upper_area = QString::fromStdString("100000");
    QString aspect_ratio_value = QString::fromStdString("8");

};
#endif // MAINWINDOW_H
