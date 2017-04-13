#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawingarea.h"
#include "QString"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    DrawingArea *da;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBoxFunc_currentIndexChanged(int index);

    void on_radioButtonCount_clicked(bool checked);
    void on_radioButtonFail_clicked(bool checked);
    void on_radioButtonDist_clicked(bool checked);

    void on_radioButtonRS_clicked(bool checked);
    void on_radioButtonNM_clicked(bool checked);

    void ResultEval(double result);
    void SetCounter(int i);
    void Set_fx(double x);
    void Set_fy(double y);

    void SetDomMin(vector<double> min);
    void SetDomMax(vector<double> max);

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
