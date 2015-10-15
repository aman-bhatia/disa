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

long ret = 0;
vector<string> sq(20);
vector<Mat> db(10000);
vector<string> filenames;
Mat descriptor;
int ranks[20];
int numbers[20];
int numbergreater = 0;
Mat previmg = Mat(window_height, window_width, CV_8UC1, Scalar(0));

int matchrank(Mat* descriptors_1 , Mat* descriptors_2)
{
	vector<vector<DMatch> > matches;
	FlannBasedMatcher matcher;
    matcher.knnMatch(*descriptors_1, *descriptors_2, matches, 2);  // Find two nearest matches
	//vector<DMatch> good_matches;
	int rank = 0;
    const float ratio = 0.8; // As in Lowe's paper; can be tuned
	for (int i = 0; i < matches.size(); ++i)
	    if (matches[i][0].distance < ratio * matches[i][1].distance)
	    	rank++;
	    //{
	    //    good_matches.push_back(matches[i][0]);
        //}
    if(rank > 10)
        numbergreater++;
	return rank;
}

void rankall()
{
    for(int i = 0 ; i < 20 ; ++i)
	{
		numbers[i] = 0;
		ranks[i] = 0;
	}
    //qDebug() << "--" << endl;
	int rank;
	for(int i = 0 ; i < ret ; ++i)
	{
		rank = matchrank(&descriptor , &db[i]);
        //qDebug() << "The rank is " << rank << endl;
        for(int j = 0 ; j < 20 ; ++j)
		{
			if(rank > ranks[j])
			{
                for(int k = 19 ; k > j ; --k)
					ranks[k] = ranks[k - 1];
				ranks[j] = rank;
                for(int k = 19 ; k > j ; --k)
					numbers[k] = numbers[k - 1];
				numbers[j] = i;
				break;
			}
		}
    }
}

void suggestions(string category)
{

    sq.clear();
    db.clear();
    filenames.clear();
    for(int i = 0 ; i < 20 ; ++i)
    {
        ranks[i] = 0;
        numbers[i] = 0;
    }
    numbergreater = 0;
    FileStorage fs(("../EasyDraw/database/" + category + ".yml").c_str() , FileStorage::READ);
    ifstream files(("../EasyDraw/database/" + category + ".dat").c_str() , ios::binary);
    string name;
    FileNode hell;
    int s = 0;
    files >> name;
    //qDebug() << (db.size()) << " " << (db.capacity()) << endl;
    //sleep(3);
    do
    {
        filenames.push_back(name);
        stringstream sq;
        sq << s;
        hell = fs[("a" + sq.str())];
        read(hell , db[s]);
        //cout << "The descriptor is " << (db[s]) << endl;
        files >> name;
        ++s;
        //qDebug() << s << endl;
        //qDebug() << name.data() << endl;
    } while (name[0] != '0');
    ret = s;
    fs.release();
    files.close();
}


Ptr<Feature2D> sfd = xfeatures2d::SIFT::create();
vector<KeyPoint> kp;
Mat temp;

void *run(void *k){
    while(true){
        Mat gray_img;
        cv::cvtColor(img, gray_img, CV_BGR2GRAY);
        cv::Mat diff;
        cv::compare(previmg, gray_img, diff, cv::CMP_NE);
        int nz = cv::countNonZero(diff);
        if(nz != 0)
        {
            //qDebug() << "hi" << endl;
            temp = img;
            /*
            sfd.detect(temp , kp);
            sde.compute(temp , kp , descriptor);
            */

            sfd->detect(temp , kp);
            sfd->compute(temp , kp , descriptor);

            rankall();
            Mat all;
            //cout << "--------" << endl;
            for(int i = 0 ; i < 20 ; ++i)
            {
                sq[i] = (filenames[numbers[i]]);
                //all = imread(filenames[numbers[i]] , CV_LOAD_IMAGE_UNCHANGED);
                //cout << ranks[i] << " " << numbers[i] << endl;
                //namedWindow("Here is lena", WINDOW_NORMAL );
                //imshow("Here is lena", all);
                //waitKey(250);
            }
            previmg = gray_img.clone();
         }
    }
}
