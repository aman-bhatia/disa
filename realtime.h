#ifndef REALTIME_H
#define REALTIME_H

#include "opencv2/xfeatures2d.hpp"
#include <stdio.h>
#include <fstream>
#include <vector>
#include <pthread.h>
#include <sstream>
#include "getinput.h"

using namespace cv;
using namespace std;

struct match {
    string name;
    vector<Point> contours;
    float distance;
};

struct by_distance {
    bool operator()(match const &a, match const &b) {
        return a.distance < b.distance;
    }
};

extern Mat previmg;
extern vector<match> images;
void suggestions(string category);
void *run(void*);
#endif // REALTIME_H
