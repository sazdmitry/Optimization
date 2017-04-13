#ifndef DRAWINGFIELD_H
#define DRAWINGFIELD_H
#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include "funcinformation.h"


class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = 0);
    ~DrawingArea();
protected:
    QPointF ConvertVect(const vector<double> x0);
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent * event) override;
    void DrawTrack();

    int Npart=50;
    void mousePressEvent(QMouseEvent * event) override;
    FuncInformation *FuncInf;
signals:
    void SignResultEval(double result);
    void SignSet_fx(double x);
    void SignSet_fy(double y);
    void SignSetCounter(int c);
    void SignSetDomMax(vector<double> max);
    void SignSetDomMin(vector<double> min);
    void EvalFunction(const QString & message, int timeout = 0);
public slots:

   void ChangeFunction(int idx);
   void ChangeMethod(int idx);
   void ChangeStop(int idx);

   void ChangeAlpha(double a);
   void ChangeBeta(double b);
   void ChangeGamma(double g);
   void ChangeSigma(double s);
   void ChangeCounter(const QString & text);
   void ChangeNMdist(double d);
   void ChangeRSdist(double d);
   void ChangeProb(double p);

//    void ChangeNMalpha(double a);
//    void ChangeNMbeta(double b);
//    void ChangeNMgamma(double g);
//    void ChangeNMsigma(double s);
//    void ChangeNMdist(double dist);

//    void ChangeRSprob(double p);
//    void ChangeRScounter(int c);
//    void ChangeRSdist(double dist);
};

#endif // DRAWINGFIELD_H
