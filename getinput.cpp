#include "getinput.h"

string window_name = "Easy Draw";
int window_width = 900;
int window_height = 800;

bool left_button_down = false; //true if mouse is pressed
bool right_button_down = false; //true if mouse is pressed
int line_thickness = 2;
Mat layer0;                                                         // backgroung image
Mat layer1;                                                         // suggestion added to background
Mat img;                                                            // Image on which user draws
int prev_x, prev_y;
int sgstn_x = 50, sgstn_y = 50, sgstn_w = 400, sgstn_h = 400;
string selected_sgstn = "";
bool eraser_selected = false;


void overlayImage(const cv::Mat &background, const cv::Mat &foreground, cv::Mat &output, cv::Point2i location){
    background.copyTo(output);

    // start at the row indicated by location, or at row 0 if location.y is negative.
    for(int y = std::max(location.y , 0); y < background.rows; ++y){
        int fY = y - location.y; // because of the translation

        // we are done of we have processed all rows of the foreground image.
        if(fY >= foreground.rows)
            break;

        // start at the column indicated by location,

        // or at column 0 if location.x is negative.
        for(int x = std::max(location.x, 0); x < background.cols; ++x){
            int fX = x - location.x; // because of the translation.

            // we are done with this row if the column is outside of the foreground image.
            if(fX >= foreground.cols)
                break;

            // determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
            double opacity =
                ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])

                / 255.;


            // and now combine the background and foreground pixel, using the opacity,

            // but only if opacity > 0.
            for(int c = 0; opacity > 0 && c < output.channels(); ++c){
                unsigned char foregroundPx =
                    foreground.data[fY * foreground.step + fX * foreground.channels() + c];
                unsigned char backgroundPx =
                    background.data[y * background.step + x * background.channels() + c];
                output.data[y*output.step + output.channels()*x + c] =
                    backgroundPx * (1.-opacity) + foregroundPx * opacity;
            }
        }
    }
}

// this function will clear layer1 and add the updated suggestion to it
void draw_sgstn(){
    layer1.release();
    layer1 = layer0.clone();
    if (selected_sgstn != ""){
        Mat sgstn = imread(selected_sgstn, 0);
        Mat sgstn_resized;
        cv::resize(sgstn,sgstn_resized,Size(sgstn_w,sgstn_h));
        blur(sgstn_resized,sgstn_resized,Size(7,7));
        sgstn_resized.copyTo(layer1(Rect(Point(sgstn_x,sgstn_y),Size(sgstn_w,sgstn_h))));
    }
};

void draw(int event, int x, int y, int flags, void* param){
    if (category_selected){
         if (event == CV_EVENT_LBUTTONDOWN){
            left_button_down = true;
            prev_x = x;
            prev_y = y;
        } else if (event == CV_EVENT_MOUSEMOVE){
             if ((right_button_down) && (selected_sgstn != "") && (x>sgstn_x) && x<(sgstn_x+sgstn_w) && (y>sgstn_y) && y<(sgstn_y+sgstn_h)){
                 sgstn_x += (x - prev_x);
                 sgstn_y += (y - prev_y);

                 if (sgstn_x+sgstn_w>window_width) sgstn_x=window_width-sgstn_w;
                 else if (sgstn_x<0) sgstn_x=0;
                 else if (sgstn_y+sgstn_h>window_height) sgstn_y=window_height-sgstn_h;
                 else if (sgstn_y<0) sgstn_y=0;

                 draw_sgstn();
             } else if (left_button_down){
                 if (eraser_selected) circle(img, Point(x,y), 10, Scalar(255,255,255,0),-1);
                 else line(img, Point(prev_x,prev_y), Point(x,y), Scalar(0,0,0,255),line_thickness);
             }
        } else if (event == CV_EVENT_LBUTTONUP){
            left_button_down = false;
            if (eraser_selected) circle(img, Point(x,y), 10, Scalar(255,255,255,0),-1);
            else line(img, Point(prev_x,prev_y), Point(x,y), Scalar(0,0,0,255),line_thickness);
        } else if (event == CV_EVENT_RBUTTONDOWN){
             right_button_down = true;
        } else if (event == CV_EVENT_RBUTTONUP){
             right_button_down = false;
        } else if (event == CV_EVENT_LBUTTONDBLCLK){
             if (selected_sgstn != ""){
                 sgstn_w += 20;
                 if (sgstn_w > 600) sgstn_w = 600;
                 sgstn_h += 20;
                 if (sgstn_h > 600) sgstn_h = 600;
                 draw_sgstn();
             }
         } else if (event == CV_EVENT_RBUTTONDBLCLK){
             if (selected_sgstn != ""){
                 sgstn_w -= 20;
                 if (sgstn_w < 100) sgstn_w = 100;
                 sgstn_h -= 20;
                 if (sgstn_h < 100) sgstn_h = 100;
                 draw_sgstn();
             }
         }
        prev_x = x;
        prev_y = y;
    }
}
