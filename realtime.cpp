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
Mat previmg = Mat(window_height, window_width, CV_8UC1, Scalar(0));

cv::Ptr <cv::ShapeContextDistanceExtractor> mysc = cv::createShapeContextDistanceExtractor();

vector<Point> simpleContour( const Mat& currentQuery, int n=100 )
{
    vector<vector<Point> > _contoursQuery;
    vector <Point> contoursQuery;
    findContours(currentQuery, _contoursQuery, RETR_LIST, CHAIN_APPROX_NONE);
    for (size_t border=0; border<_contoursQuery.size(); border++)
    {
        for (size_t p=0; p<_contoursQuery[border].size(); p++)
        {
            contoursQuery.push_back( _contoursQuery[border][p] );
        }
    }

    // In case actual number of points is less than n
    int dummy=0;
    for (int add=contoursQuery.size()-1; add<n; add++)
    {
        contoursQuery.push_back(contoursQuery[dummy++]); //adding dummy values
    }

    // Uniformly sampling
    random_shuffle(contoursQuery.begin(), contoursQuery.end());
    vector<Point> cont;
    for (int i=0; i<n; i++)
    {
        cont.push_back(contoursQuery[i]);
    }
    return cont;
}

void suggestions(string category)
{
    images.clear();

    DIR *dir;
    dirent *entry;
    string dirname = "../EasyDraw/sda/compressed/" + category + "/";
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
              m.contours = simpleContour(queryImg);
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
}


void *run(void *k){
    while(true){
        Mat gray_img;
        cv::cvtColor(img, gray_img, CV_BGR2GRAY);
        cv::Mat diff;
        cv::compare(previmg, gray_img, diff, cv::CMP_NE);
        int nz = cv::countNonZero(diff);
        if(nz != 0 && category_selected)
        {
            //qDebug() << "nz != 0 and its value is " << nz;
            Mat resizedImg;
            resize(gray_img,resizedImg,Size(100,100));
            vector<Point> contImg = simpleContour(resizedImg);
            for (int i=0;i<images.size();i++){
                images[i].distance = mysc->computeDistance( images[i].contours, contImg );
            }
            sort(images.begin(), images.end(), by_distance());
            previmg = gray_img.clone();
        }
    }
}
