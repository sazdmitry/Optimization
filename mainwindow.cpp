#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout* layout = findChild<QGridLayout*>("LayoutMain");
    da = new DrawingArea();
    Q_ASSERT(layout);
    layout->addWidget(da);

    QObject::connect(da,&DrawingArea::SignResultEval,this,&MainWindow::ResultEval);
    QObject::connect(da,&DrawingArea::SignSetCounter,this,&MainWindow::SetCounter);
    QObject::connect(da,&DrawingArea::SignSet_fx,this,&MainWindow::Set_fx);
    QObject::connect(da,&DrawingArea::SignSet_fy,this,&MainWindow::Set_fy);
    QObject::connect(da,&DrawingArea::SignSetDomMax,this,&MainWindow::SetDomMax);
    QObject::connect(da,&DrawingArea::SignSetDomMin,this,&MainWindow::SetDomMin);

    QObject::connect(da,&DrawingArea::EvalFunction,ui->statusBar,&QStatusBar::showMessage);

    QObject::connect(ui->NMalpha,
                     static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),da,&DrawingArea::ChangeAlpha);
    QObject::connect(ui->NMbeta,
                     static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),da,&DrawingArea::ChangeBeta);
    QObject::connect(ui->NMgamma,
                     static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),da,&DrawingArea::ChangeGamma);
    QObject::connect(ui->NMsigma,
                     static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),da,&DrawingArea::ChangeSigma);
    QObject::connect(ui->NMdist,
                     static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),da,&DrawingArea::ChangeNMdist);

    QObject::connect(ui->MinDist,
                     static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),da,&DrawingArea::ChangeRSdist);
    QObject::connect(ui->MaxCounter,&QLineEdit::textEdited,da,&DrawingArea::ChangeCounter);
    QObject::connect(ui->RSprob,
                     static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),da,&DrawingArea::ChangeProb);


    QLineEdit* MaxCounter = findChild<QLineEdit*>("MaxCounter");
    MaxCounter->setValidator(new QIntValidator(1,40000,MaxCounter));


}

MainWindow::~MainWindow()
{
    delete ui;
    delete da;
}


void MainWindow::on_comboBoxFunc_currentIndexChanged(int index)
{
   da->ChangeFunction(index);
}

void MainWindow::on_radioButtonRS_clicked(bool checked)
{
    if (checked) {
        da->ChangeMethod(0);
    }
}

void MainWindow::on_radioButtonNM_clicked(bool checked)
{
    if (checked) {
        da->ChangeMethod(1);
    }
}

void MainWindow::on_radioButtonCount_clicked(bool checked) {
    if (checked) da->ChangeStop(0);
}

void MainWindow::on_radioButtonFail_clicked(bool checked) {
    if (checked) da->ChangeStop(1);
}

void MainWindow::on_radioButtonDist_clicked(bool checked)
{
    if (checked) da->ChangeStop(2);
}

void MainWindow::ResultEval(double result) {
    QString vall = QString::number(result);
    ui->Res_eval->setText(vall);
}

void MainWindow::SetCounter(int i) {
    QString vall = QString::number(i);
    ui->ResultCounter->setText(vall);
}

void MainWindow::Set_fx(double x) {
    QString vall = QString::number(x,'f',3);
    ui->Res_x->setText(vall);
}

void MainWindow::Set_fy(double y) {
    QString vall = QString::number(y,'f',3);
    ui->Res_y->setText(vall);
}

void MainWindow::SetDomMax(vector<double> max) {
    QString vall = QString::number(max[0],'f',1)+"; "+QString::number(max[1],'f',1);
    ui->DomainFrom->setText(vall);
}

void MainWindow::SetDomMin(vector<double> min) {
    QString vall = QString::number(min[0],'f',1)+"; "+QString::number(min[1],'f',1);
    ui->DomainTo->setText(vall);
}
