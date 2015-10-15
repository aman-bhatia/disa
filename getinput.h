#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <iostream>
#include "mainwindow.h"
using namespace cv;
using namespace std;

extern string window_name;
extern int window_width;
extern int window_height;
extern Mat layer0;
extern Mat layer1;
extern Mat img;
extern Mat result;
extern vector<string> sq;
extern int sgstn_x, sgstn_y, sgstn_w, sgstn_h;
extern string selected_sgstn;
extern bool eraser_selected;
extern vector<string> filenames;

void overlayImage(const cv::Mat &background, const cv::Mat &foreground, cv::Mat &output, cv::Point2i location);
void draw_sgstn();
void draw(int,int,int,int,void*);
void *getimage(void *);
