#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <fstream>
#include <vector>
#include <pthread.h>
#include "getinput.h"
#include <sstream>
using namespace cv;
using namespace std;
long ret = 0;
vector<string> sq(20);
vector<Mat> db(1000000);
Mat descriptor;
int ranks[20];
int numbers[20];

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
	return rank;
}

void rankall()
{
	for(int i = 0 ; i < 20 ; ++i)
	{
		numbers[i] = 0;
		ranks[i] = 0;
	}
	cout << "--" << endl;
	int rank;
	for(int i = 0 ; i < ret ; ++i)
	{
		rank = matchrank(&descriptor , &db[i]);
		//cout << "The rank is " << rank << endl;
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
	vector<string> filenames;
	FileStorage fs(("../database/" + category + ".yml").c_str() , FileStorage::READ);
	ifstream files(("../database/" + category + ".dat").c_str() , ios::binary);
	string name;
	FileNode hell;
	int s = 0;
	files >> name;
	cout << (db.size()) << " " << (db.capacity()) << endl;
	sleep(3);
	do
	{
		filenames.push_back(name);
		stringstream sq;
		sq << s;
		hell = fs[("a" + sq.str())];
		read(hell , db[s]);
		files >> name;
		++s;
		cout << s << endl;
		cout << name << endl;
	}while(name[0] != '0');
	ret = s;
	fs.release();
	files.close();

	//SiftFeatureDetector sfd;
	//SiftDescriptorExtractor sde;
	Ptr<Feature2D> sfd = xfeatures2d::SIFT::create();
	vector<KeyPoint> kp;
	Mat temp;
	while(true){
		cout << "hi" << endl;
		temp = img;
		//sfd.detect(temp , kp);
		sfd->detect(temp , kp);
		//sde.compute(temp , kp , descriptor);
		sfd->compute(temp , kp , descriptor);
		rankall();
		Mat all;
		for(int i = 0 ; i < 20 ; ++i)
		{
			sq[i] = (filenames[numbers[i]]);
			//all = imread(filenames[numbers[i]] , CV_LOAD_IMAGE_UNCHANGED);
			cout << ranks[i] << " " << numbers[i] << endl;
			//namedWindow("Here is lena", WINDOW_NORMAL );
			//imshow("Here is lena", all);
			//waitKey(250);
		}
		sleep(0.5);
	}
}
int main()
{
	pthread_t t;
	pthread_create(&t , NULL , getimage , (void *)0);
	suggestions("antelope");
	return 0;
}