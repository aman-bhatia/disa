#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "getinput.h"
Mat result;
using namespace cv;
using namespace std;

void combine(Mat image1 , Mat image2)
{
	
	Mat gray_image1;
	Mat gray_image2;
	
	cvtColor(image1, gray_image1, CV_RGB2GRAY);
	cvtColor(image2, gray_image2, CV_RGB2GRAY);
	
	int minHessian = 400; //??????????
	//SurfFeatureDetector detector(minHessian);
	Ptr<Feature2D> detector = xfeatures2d::SURF::create(minHessian);
	std::vector< KeyPoint > keypoints_object,keypoints_scene;
	//detector.detect(gray_image1, keypoints_object);
	detector->detect(gray_image1, keypoints_object);
	//detector.detect(gray_image2, keypoints_scene);
	detector->detect(gray_image2, keypoints_scene);
	
	//SurfDescriptorExtractor extractor;
	Mat descriptors_object, descriptors_scene;
	//extractor.compute(gray_image1, keypoints_object, descriptors_object);
	detector->compute(gray_image1, keypoints_object, descriptors_object);
	//extractor.compute(gray_image2, keypoints_scene, descriptors_scene);
	detector->compute(gray_image2, keypoints_scene, descriptors_scene);
	
	FlannBasedMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match(descriptors_object, descriptors_scene, matches);
	
	double max_dist = 0; double min_dist = 100;
	for(int i = 0; i < descriptors_object.rows; i++)
	{
		double dist = matches[i].distance;
		if(dist < min_dist) min_dist = dist;
		if(dist > max_dist) max_dist = dist;
	}
	
	std::vector< DMatch > good_matches;
	for(int i = 0; i < descriptors_object.rows; i++)
	{
		if(matches[i].distance < 3*min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}
	
	std::vector< Point2f > obj;
	std::vector< Point2f > scene;

	for(int i = 0; i < good_matches.size(); i++)
	{
		obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
	}
	
	//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-//

	Mat H = findHomography(obj, scene, CV_RANSAC);

	warpPerspective(image1,result,H,cv::Size(image1.cols+image2.cols,image1.rows));
	cv::Mat half(result,cv::Rect(0,0,image2.cols,image2.rows));
	image2.copyTo(half);
	//imshow("input1",image1);
	//imshow("input2",image2);
	//imshow("Result", result);
	//cvWaitKey(0);
}
