#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <iostream>

using namespace cv;
using namespace std;


extern Mat img;
extern Mat result;
extern vector<string> sq;

void draw(int,int,int,int,void*);
void *getimage(void *);