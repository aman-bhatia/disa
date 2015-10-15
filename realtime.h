#ifndef REALTIME_H
#define REALTIME_H

#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <fstream>
#include <vector>
#include <pthread.h>
#include "getinput.h"
#include <sstream>
using namespace cv;
using namespace std;
extern int numbergreater;
extern long ret;
extern vector<string> sq;
extern vector<Mat> db;
extern Mat descriptor;
extern int ranks[20];
extern int numbers[20];

extern Mat previmg;
int matchrank(Mat* descriptors_1 , Mat* descriptors_2);
void rankall();
void suggestions(string category);
void *run(void*);
#endif // REALTIME_H
