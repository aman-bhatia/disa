#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <fstream>
#include <vector>
#include <pthread.h>
#include "getinput.h"
#include "realtime.h"
#include <sstream>
#include <dirent.h>
#include "opencv2/shape.hpp"


using namespace cv;
using namespace std;

vector<match> images(0);
Mat previmg = Mat(window_height, window_width, CV_8UC1, Scalar(255));

cv::Ptr <cv::ShapeContextDistanceExtractor> mysc = cv::createShapeContextDistanceExtractor();

vector<Point> getContours(Mat img){
    vector<Vec4i> hierarchy;
    vector<vector<Point> > contours;
    findContours(img , contours , hierarchy , RETR_EXTERNAL , CV_CHAIN_APPROX_NONE);

    int n=200;
    vector<Point> cont(0);
    for (int i=0;i<contours.size();i++){
        for (int j=0;j<contours[i].size();j++){
            cont.push_back(contours[i][j]);
        }
    }
    vector<Point> ret(0);
    if (cont.size() == 0)
        return ret;

    while (cont.size() < n){
        cont.push_back(cont.back());
    }
    random_shuffle(cont.begin(), cont.end());
    for (int i=0;i<n;i++){
        ret.push_back(cont[i]);
    }
    return ret;
}

void suggestions(string category)
{
    images.clear();

    DIR *dir;
    dirent *entry;
    string dirname = "../sda/" + category + "/";
    if ((dir = opendir (dirname.data())) != NULL) {
      while ((entry = readdir (dir)) != NULL) {
          string filename = entry->d_name;
          if (filename != "." && filename != ".."){
              match m;
              m.name = category + "/" + filename;
              Mat queryImg = imread(dirname + filename,CV_LOAD_IMAGE_GRAYSCALE);
              if (queryImg.empty()){
                  cout << "Unable to open Image file : from suggestions function\n";
                  exit(0);
              }
              threshold(queryImg,queryImg,240,255,CV_THRESH_BINARY_INV);
              m.contours = getContours(queryImg);
              m.distance = 0;
              images.push_back(m);
          }
      }
      closedir (dir);
    } else {
      cout << "Cannot open the directory" << endl;
      exit(0);
    }

    Mat gray_img;
    cv::cvtColor(img, gray_img, CV_BGR2GRAY);
    threshold(gray_img,gray_img,127,255,CV_THRESH_BINARY_INV);
    previmg = gray_img.clone();
    cout << "Done initializing" << endl;
}

bool sameImages(Mat& img1, Mat& img2){
    if (img1.rows==img2.rows && img1.cols==img2.cols){
        for (int i=0;i<img1.rows;i++){
            for(int j=0;j<img1.cols;j++){
                if (img1.at<uchar>(i,j) != img2.at<uchar>(i,j))
                    return false;
            }
        }
        return true;
    } else return false;
}

float getDistance(vector<Point> cont1, vector<Point> cont2){
    if (cont1.size()==0 || cont2.size()==0)
        return 0;
    return mysc->computeDistance(cont1,cont2);
}

void drawContour(vector<Point> cont, Mat img,string name){
    Mat ret = img.clone();
    for (int i=0;i<cont.size();i++){
        circle(ret,cont[i],2,Scalar(255),-1);
    }
    imwrite("../"+name,ret);
}

void *run(void *k){
    while(true){
        Mat gray_img;
        cv::cvtColor(img, gray_img, CV_BGR2GRAY);
        //Mat gray_img = imread("../Drawing.png",0);
        threshold(gray_img,gray_img,127,255,CV_THRESH_BINARY_INV);
        if(category_selected && !sameImages(gray_img,previmg))
        {
            qDebug() << "Processing Images...";
            previmg = gray_img.clone();
            vector<Point> contours_img = getContours(gray_img);
            for (int i=0;i<images.size();i++){
                images[i].distance = getDistance(images[i].contours, contours_img);
            }
            sort(images.begin(), images.end(), by_distance());
//            for (int i=0;i<images.size();i++){
//                cout << images[i].name << " : " << images[i].distance << endl;
//            }
//            drawContour(contours_img,gray_img,"gray_img.png");
//            for (int i=0;i<images.size();i++){
//                Mat temp_img = imread("../sda/"+images[i].name);
//                drawContour(images[i].contours,temp_img,"images"+to_string(i) + ".png");
//            }
            qDebug() << "Processing Completed...";
        }
    }
}
