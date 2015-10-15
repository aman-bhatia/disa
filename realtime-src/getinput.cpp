#include "getinput.h"
string window_name = "Easy Draw";
int window_width = 600;
int window_height = 800;


bool button_down = false; //true if mouse is pressed
int line_thickness = 4;
Mat img;
int prev_x, prev_y;

void draw(int event, int x, int y, int flags, void* param){
     if (event == CV_EVENT_LBUTTONDOWN){
		button_down = true;
		prev_x = x;
		prev_y = y;
	} else if (event == CV_EVENT_MOUSEMOVE){
		if (button_down) line(img, Point(prev_x,prev_y), Point(x,y), Scalar(0,0,0),line_thickness);
	} else if (event == CV_EVENT_LBUTTONUP){
		button_down = false;
		line(img, Point(prev_x,prev_y), Point(x,y), Scalar(0,0,0),line_thickness);
	}
	prev_x = x;
	prev_y = y;
}


void *getimage(void *k){
	// Create black empty images
	img = Mat(window_height, window_width, CV_8UC3, Scalar(200,200,200));

	namedWindow( window_name, CV_WINDOW_AUTOSIZE );		// Create a window for display.
	setMouseCallback(window_name, draw, NULL);			//set the callback function for any mouse event
	
	while(true){
		imshow(window_name, img);
		if (waitKey(1) == 27) break;
	}
	
	destroyAllWindows();
}
