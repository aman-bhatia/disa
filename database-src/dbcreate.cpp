#include <iostream>
#include <stdio.h>
#include <sstream>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <dirent.h>
#include <fstream>
using namespace std;
using namespace cv;
string correctpart(string s)
{
	string a = "";
	for(int i = 0 ; i < s.length() && s[i] != '+' && s[i] != '_' ; ++i)
		a = a + s[i];
	return a;
}
int main(int argc , char** argv)
{
	DIR *dp = opendir(argv[1]);
	DIR *dp1;
	dirent *entry1 , *entry2;

	//All the variables needed for storing the detectors

	Mat image , descriptor;
	//SiftFeatureDetector detector;
	Ptr<Feature2D> detector = xfeatures2d::SIFT::create();
	vector<KeyPoint> keypoints;
	//SiftDescriptorExtractor extractor;
	//Over
	int i = 0;
	ofstream os;
	int s = 0;
	string present , prev = "";
	FileStorage fs;
	cout << "hi" << endl;
	vector<string> nam;
	while(entry1 = readdir(dp))
		nam.push_back(string(entry1->d_name));
	sort(nam.begin() , nam.end());
	for(int qw = 0 ; qw < nam.size() ; ++qw)
	{
		cout << (string(argv[1]) + nam[qw]) << endl;
		dp1 = opendir((string(argv[1]) + nam[qw]).c_str());
		//cout << "hi" << endl;
		if (((nam[qw][0]) == '.'))
			continue;
		present = correctpart(nam[qw]);
		cout << present << endl;
		if(present != prev)
		{
			if(prev != "")
			{
				i = 0;
				os << (i) << endl;
				fs.release();
				os.close();
			}
			fs.open(("../database/" + present + ".yml").c_str() , FileStorage::WRITE);
			os.open(("../database/" + present + ".dat").c_str() , ios::binary);
		}
		s = 0;
		while(entry2 = readdir(dp1))
		{
			string a = entry2->d_name;
			if ((entry2->d_name[0]) == '.')
				continue;
			image = imread((string(argv[1]) + nam[qw]) + "/" + string(entry2->d_name) , CV_LOAD_IMAGE_UNCHANGED);
			//detector.detect(image , keypoints);
			detector->detect(image , keypoints);
			//extractor.compute(image , keypoints , descriptor);
			detector->compute(image , keypoints , descriptor);
			stringstream ss;
			ss << s;
			cout << s << endl;
			write(fs , "a" + ss.str() , descriptor);
			++s;
			os << ((string(argv[1]) + nam[qw]) + "/" + string(entry2->d_name)) << endl;
			++i;
			prev = present;
			//cout << i << endl;
		}
	}
	os << (0) << endl;
	fs.release();
	os.close();
	return 0;
}
