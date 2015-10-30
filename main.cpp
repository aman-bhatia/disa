#include "mainwindow.h"
#include "getinput.h"
#include "realtime.h"
#include <QApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <QSplashScreen>
#include <QTimer>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("../EasyDraw/images/screen.jpg"));
    splash->show();
    QApplication::processEvents();
    sleep(5);
    QTimer::singleShot(0,splash,SLOT(close()));

    MainWindow w;
    w.setWindowTitle(QString::fromUtf8("Suggestions"));
    w.resize(300, 750);
    w.move(window_width+100,0);
    w.show();
    w.on_pushButton_toggled(false);
    w.on_pushButton_2_toggled(false);
    w.on_pushButton_3_toggled(false);
    w.on_pushButton_4_toggled(false);

    qDebug() << "Starting Program";
    layer0 = Mat(window_height, window_width, CV_8UC1, Scalar(255));
    img = Mat(window_height, window_width, CV_8UC4, Scalar(255,255,255,0));
    namedWindow( window_name, CV_WINDOW_OPENGL | CV_WINDOW_AUTOSIZE);		// Create a window for display.
    setMouseCallback(window_name, draw, NULL);                              //set the callback function for any mouse event

    pthread_t t;
    pthread_create(&t , NULL , run , (void *)0);

    Mat toshow;
    layer1 = layer0.clone();
    while(true){
        if (category_selected){
            string temp = "../EasyDraw/sda/";
            w.addToLabel(1,temp+images[0].name);
            w.addToLabel(2,temp+images[1].name);
            w.addToLabel(3,temp+images[2].name);
            w.addToLabel(4,temp+images[3].name);
        } else {
            string temp = "../EasyDraw/images/select_category.png";
            w.addToLabel(1,temp);
            w.addToLabel(2,temp);
            w.addToLabel(3,temp);
            w.addToLabel(4,temp);
        }
        overlayImage(layer1,img,toshow,Point(0,0));
        imshow(window_name, toshow);
        if (waitKey(1) == 27) break;
    }
    Mat gray_img;
    cv::cvtColor(img, gray_img, CV_BGR2GRAY);
    imwrite("../EasyDraw/Drawing.png", gray_img);
    destroyAllWindows();

    return a.exec();
}
