#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>

extern bool category_selected;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addToLabel(int,std::string);

public slots:
    void uncheck_all_pushButtons();
    void on_pushButton_toggled(bool checked);
    void on_pushButton_2_toggled(bool checked);
    void on_pushButton_3_toggled(bool checked);
    void on_pushButton_4_toggled(bool checked);

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_checkBox_toggled(bool checked);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
