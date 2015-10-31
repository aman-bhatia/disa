#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "realtime.h"

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
    ui->pushButton->setIcon(QIcon("../images/cross.png"));
    ui->pushButton_2->setIcon(QIcon("../images/cross.png"));
    ui->pushButton_3->setIcon(QIcon("../images/cross.png"));
    ui->pushButton_4->setIcon(QIcon("../images/cross.png"));
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    uncheck_all_pushButtons();
    if (checked){
        ui->pushButton->setIcon(QIcon("../images/tick.png"));
        selected_sgstn = "../sda/"+images[0].name;
    } else {
        ui->pushButton->setIcon(QIcon("../images/cross.png"));
        selected_sgstn = "";
    }
}

void MainWindow::on_pushButton_2_toggled(bool checked)
{
    uncheck_all_pushButtons();
    if (checked){
        ui->pushButton_2->setIcon(QIcon("../images/tick.png"));
        selected_sgstn = "../sda/"+images[1].name;
    } else {
        ui->pushButton_2->setIcon(QIcon("../images/cross.png"));
        selected_sgstn = "";
    }
}

void MainWindow::on_pushButton_3_toggled(bool checked)
{
    uncheck_all_pushButtons();
    if (checked){
        ui->pushButton_3->setIcon(QIcon("../images/tick.png"));
        selected_sgstn = "../sda/"+images[2].name;
    } else {
        ui->pushButton_3->setIcon(QIcon("../images/cross.png"));
        selected_sgstn = "";
    }
}

void MainWindow::on_pushButton_4_toggled(bool checked)
{
    uncheck_all_pushButtons();
    if (checked){
        ui->pushButton_4->setIcon(QIcon("../images/tick.png"));
        selected_sgstn = "../sda/"+images[3].name;
    } else {
        ui->pushButton_4->setIcon(QIcon("../images/cross.png"));
        selected_sgstn = "";
    }
}

// Choose Category
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    category_selected = false;
    if (arg1 == "Choose Category") return;
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
        QApplication::setOverrideCursor(QCursor(QPixmap("../EasyDraw/"
                                                        "images/eraser.png")));
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
