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
    while (cont.size() < n){
        cont.push_back(cont.back());
    }
    random_shuffle(cont.begin(), cont.end());
    vector<Point> ret(0);
    for (int i=0;i<n;i++){
        ret.push_back(cont[i]);
    }
    return ret;
}

float getDistance(vector<Point> &contours1, vector<Point> &contours2)
{
//    vector<float> distances;
//    cout << "\t contours1.size() : " << contours1.size() << endl;
//    cout << "\t contours2.size() : " << contours2.size() << endl;
//    for(int i = 0 ; i < contours1.size() ; ++i)
//    {
//        for(int j = 0 ; j < contours2.size() ; ++j)
//        {
//            distances.push_back(mysc->computeDistance(contours1[i] , contours2[j]));
//        }
//    }
//    sort(distances.begin() , distances.end());
//    float to_return = 0;
//    int limit = (10 < distances.size()) ? 10 : distances.size();
//    for(int i = 0 ; i < limit ; ++i)
//        to_return += distances[i];
//    return to_return;

    return mysc->computeDistance(contours1 , contours2);
}

void suggestions(string category)
{
    images.clear();

    DIR *dir;
    dirent *entry;
    string dirname = "../EasyDraw/sda/" + category + "/";
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
      // could not open directory
      cout << "Cannot open the directory" << endl;
      exit(0);
    }
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

void drawContour(vector<Point> cont, Mat img,string name){
    Mat ret = img.clone();
    for (int i=0;i<cont.size();i++){
        circle(ret,cont[i],2,Scalar(255),-1);
    }
    imwrite("../EasyDraw/"+name,ret);
}

void *run(void *k){
    while(true){
        //Mat gray_img;
        //cv::cvtColor(img, gray_img, CV_BGR2GRAY);
        Mat gray_img = imread("../EasyDraw/Drawing.png",0);
        threshold(gray_img,gray_img,127,255,CV_THRESH_BINARY_INV);
        if(category_selected && !sameImages(gray_img,previmg))
        {
            cout << "I am running\n";
            previmg = gray_img.clone();
            vector<Point> contours_img = getContours(gray_img);
            for (int i=0;i<images.size();i++){
                cout << "\t images[i].name : " << images[i].name << endl;
                images[i].distance = getDistance(images[i].contours, contours_img);
            }
            sort(images.begin(), images.end(), by_distance());
            for (int i=0;i<images.size();i++){
                cout << images[i].name << " : " << images[i].distance << endl;
            }
            for (int i=0;i<images.size();i++){
                Mat temp_img = imread("../EasyDraw/sda/"+images[i].name);
                drawContour(images[i].contours,temp_img,"images"+to_string(i) + ".png");
            }
            cout << "\n\n";
        }
    }
}
