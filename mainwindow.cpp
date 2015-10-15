#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "realtime.h"
//#include "ia.h"

bool category_selected = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToLabel(int id, std::string fname){
    QString  s(fname.c_str());
    QPixmap p(s);
    switch(id){
        case(1):
            ui->label->setPixmap(p);
            break;
        case(2):
            ui->label_2->setPixmap(p);
            break;
        case(3):
            ui->label_3->setPixmap(p);
            break;
        case(4):
            ui->label_4->setPixmap(p);
            break;
        default:
            qDebug() << "Id not Handled";
            break;
    }
}

void MainWindow::uncheck_all_pushButtons(){
    ui->pushButton->setIcon(QIcon("../EasyDraw/images/cross.png"));
    ui->pushButton_2->setIcon(QIcon("../EasyDraw/images/cross.png"));
    ui->pushButton_3->setIcon(QIcon("../EasyDraw/images/cross.png"));
    ui->pushButton_4->setIcon(QIcon("../EasyDraw/images/cross.png"));
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    uncheck_all_pushButtons();
    if (checked){
        ui->pushButton->setIcon(QIcon("../EasyDraw/images/tick.png"));
        selected_sgstn = "../EasyDraw/database/"+sq[0];
    } else {
        ui->pushButton->setIcon(QIcon("../EasyDraw/images/cross.png"));
        selected_sgstn = "";
    }
}

void MainWindow::on_pushButton_2_toggled(bool checked)
{
    uncheck_all_pushButtons();
    if (checked){
        ui->pushButton_2->setIcon(QIcon("../EasyDraw/images/tick.png"));
        selected_sgstn = "../EasyDraw/database/"+sq[1];
    } else {
        ui->pushButton_2->setIcon(QIcon("../EasyDraw/images/cross.png"));
        selected_sgstn = "";
    }
}

void MainWindow::on_pushButton_3_toggled(bool checked)
{
    uncheck_all_pushButtons();
    if (checked){
        ui->pushButton_3->setIcon(QIcon("../EasyDraw/images/tick.png"));
        selected_sgstn = "../EasyDraw/database/"+sq[2];
    } else {
        ui->pushButton_3->setIcon(QIcon("../EasyDraw/images/cross.png"));
        selected_sgstn = "";
    }
}

void MainWindow::on_pushButton_4_toggled(bool checked)
{
    uncheck_all_pushButtons();
    if (checked){
        ui->pushButton_4->setIcon(QIcon("../EasyDraw/images/tick.png"));
        selected_sgstn = "../EasyDraw/database/"+sq[3];
    } else {
        ui->pushButton_4->setIcon(QIcon("../EasyDraw/images/cross.png"));
        selected_sgstn = "";
    }
}

// Choose Category
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Choose Category") category_selected = false;
    else {
        cout<<arg1.toStdString()<<endl;
        suggestions(arg1.toStdString());
        category_selected = true;
    }
}

// Clear Canvas
void MainWindow::on_pushButton_5_clicked()
{
    selected_sgstn = "";
    img = Mat(window_height, window_width, CV_8UC4, Scalar(255,255,255,0));
    draw_sgstn();
    uncheck_all_pushButtons();
}


// Eraser
void MainWindow::on_checkBox_toggled(bool checked)
{
    if (checked){
        eraser_selected = true;
        QApplication::setOverrideCursor(QCursor(QPixmap("../EasyDraw/images/eraser.png")));
    } else {
        eraser_selected = false;
        QApplication::restoreOverrideCursor();
    }
}


// Show Suggestion
void MainWindow::on_pushButton_6_clicked()
{
    if (selected_sgstn != ""){
        uncheck_all_pushButtons();
        draw_sgstn();
    }
}


// Hide Suggestion
void MainWindow::on_pushButton_7_clicked()
{
    if (selected_sgstn != ""){
        selected_sgstn = "";
        draw_sgstn();
    }
}

// Show Match
void MainWindow::on_pushButton_8_clicked()
{
    if (selected_sgstn != ""){
        Mat gray;
        cv::cvtColor(img, gray, CV_BGR2GRAY);
        Mat sgstn_img = imread(selected_sgstn);
        vector<KeyPoint> kp1, kp2;
        Ptr<Feature2D> sfd = xfeatures2d::SIFT::create();
        sfd->detect(img, kp1);
        sfd->detect(sgstn_img,kp2);
        Mat des1,des2;
        sfd->detectAndCompute(gray, Mat(), kp1,des1);
        sfd->detectAndCompute(sgstn_img, Mat(), kp2, des2);

        FlannBasedMatcher matcher;
        vector< DMatch > matches;
        matcher.match( des1, des2, matches );
        double max_dist = 0; double min_dist = 100;
        //-- Quick calculation of max and min distances between keypoints
        for( int i = 0; i < des1.rows; i++ )
        {
            double dist = matches[i].distance;
            if( dist < min_dist ) min_dist = dist;
            if( dist > max_dist ) max_dist = dist;
        }

        std::vector< DMatch > good_matches;
        for( int i = 0; i < des1.rows; i++ )
        {
            if( matches[i].distance <= max(2*min_dist, 0.02) )
            {
                good_matches.push_back( matches[i]);
            }
        }
        //-- Draw only "good" matches
        Mat img_matches;
        drawMatches( gray, kp1, sgstn_img, kp2,
                   good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                   vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
        //-- Show detected matches
        imshow( "Good Matches", img_matches );
    }
}
