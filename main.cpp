#include "mainwindow.h"
#include "getinput.h"
#include "realtime.h"
#include <QApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*
QImage Mat2QImage(cv::Mat_<double> &src)
{
        double scale = 255.0;
        QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
        for (int y = 0; y < src.rows; ++y) {
                const double *srcrow = src[y];
                QRgb *destrow = (QRgb*)dest.scanLine(y);
                for (int x = 0; x < src.cols; ++x) {
                        unsigned int color = srcrow[x] * scale;
                        destrow[x] = qRgba(color, color, color, 255);
                }
        }
        return dest;
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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

    suggestions("noCategorySelected");
    pthread_t t;
    pthread_create(&t , NULL , run , (void *)0);

    Mat toshow;
    layer1 = layer0.clone();
    while(true){
        if (category_selected){
            w.addToLabel(1,"../EasyDraw/database/"+sq[0]);
            w.addToLabel(2,"../EasyDraw/database/"+sq[1]);
            w.addToLabel(3,"../EasyDraw/database/"+sq[2]);
            w.addToLabel(4,"../EasyDraw/database/"+sq[3]);
        } else {
            w.addToLabel(1,"../EasyDraw/images/select_category.png");
            w.addToLabel(2,"../EasyDraw/images/select_category.png");
            w.addToLabel(3,"../EasyDraw/images/select_category.png");
            w.addToLabel(4,"../EasyDraw/images/select_category.png");
        }
        overlayImage(layer1,img,toshow,Point(0,0));
        imshow(window_name, toshow);
        if (waitKey(1) == 27) break;
    }

    //QImage qimg((uchar*)img.data, img.cols, img.rows, QImage::Format_Indexed8);
    //imwrite("../EasyDraw/Result.jpg", img);
    imwrite("../EasyDraw/Drawing.png", img);
    destroyAllWindows();

    return a.exec();
}
