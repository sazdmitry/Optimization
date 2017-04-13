#include "drawingarea.h"
#include "QPainter"
#include "iterator"


DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    FuncInf = new FuncInformation();
    emit SignSetDomMin(FuncInf->mf->GetDom().GetLowCase());
    emit SignSetDomMax(FuncInf->mf->GetDom().GetUpperCase());
    setMouseTracking(true);
}

DrawingArea::~DrawingArea() {
    delete FuncInf;
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event) {
    int x=event->x();
    int y=event->y();
    QSize sz = size();
    int width=sz.width(); // ширина
    int height=sz.height(); // высота
    double result = FuncInf->mf->evaluate(FuncInf->ConvertPoint(width,height,x,y));

    QString vall = "Evaluate in ("+QString::number(FuncInf->ConvertPoint(width,height,x,y)[0],'f',6)+","+QString::number(FuncInf->ConvertPoint(width,height,x,y)[1],'f',6)+") is "+QString::number(result,'f',6);
    emit EvalFunction(vall);
}

void DrawingArea::mousePressEvent(QMouseEvent* event){
      int x=event->x();
      int y=event->y();
      QSize sz = size();
      int width=sz.width(); // ширина
      int height=sz.height(); // высота
      FuncInf->StartAlg(width,height,x,y);
      emit SignResultEval(FuncInf->result);
      emit SignSetCounter(FuncInf->current_counter);
      emit SignSet_fx(FuncInf->track[FuncInf->track.size()-1][0]);
      emit SignSet_fy(FuncInf->track[FuncInf->track.size()-1][1]);
      repaint();
};

void DrawingArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPen pen;
    QSize sz = size();

    int width=sz.width(); // ширина
    int height=sz.height(); // высота

    FuncInf->CalculateRange(width,height,Npart);
    auto it = FuncInf->RangeField.begin();
    for (int i=0;i<width;++i) {
        for (int j=0;j<height;++j) {
            pen.setColor(QColor(200,(*it)[j]*5,0));
            p.setPen(pen);
            p.drawPoint(i,j);
        }
        ++it;
    }
    DrawTrack();
}

QPointF DrawingArea::ConvertVect(const vector<double> x0) {
    QSize sz = size();
    int width=sz.width(); // ширина
    int height=sz.height(); // высота
    return QPointF(
                (x0[0]-FuncInf->mf->GetDom().GetLowCase()[0])/
            (FuncInf->mf->GetDom().GetUpperCase()[0]-FuncInf->mf->GetDom().GetLowCase()[0])*width,
            (1-(x0[1]-FuncInf->mf->GetDom().GetLowCase()[1])/
        (FuncInf->mf->GetDom().GetUpperCase()[1]-FuncInf->mf->GetDom().GetLowCase()[1]))*height);
}

void DrawingArea::DrawTrack() {
    if (FuncInf->track.size()!=0) {
    auto it = FuncInf->track.begin();
    vector<double> prev = *it;
    it++;
    int length = FuncInf->track.size();

    QPainter p(this);
    int color = 0;

    for (;it!=FuncInf->track.end();){
        //pen.setColor(QColor(color,color,color));
        //brush.setColor(QColor(color,color,color));
        p.setPen(QColor(color,color,color));
        p.setBrush(QColor(color,color,color));
        p.drawLine(ConvertVect(prev),ConvertVect(*it));
        p.drawEllipse(ConvertVect(prev),2,2);
        p.drawEllipse(ConvertVect(*it),2,2);
        prev=*it;
        it++;
        color += 250/length;
    }
    }
}

void DrawingArea::ChangeFunction(int idx) {
    FuncInf->ChangeFunction(idx);
    emit SignSetDomMin(FuncInf->mf->GetDom().GetLowCase());
    emit SignSetDomMax(FuncInf->mf->GetDom().GetUpperCase());
    repaint();
}

void DrawingArea::ChangeMethod(int idx) {
    FuncInf->ChangeMethod(idx);
}

void DrawingArea::ChangeStop(int idx) {
    FuncInf->ChangeStopper(idx);
}

void DrawingArea::ChangeAlpha(double a) {
    FuncInf->nm->set_alpha(a);
}

void DrawingArea::ChangeBeta(double b) {
    FuncInf->nm->set_beta(b);
}

void DrawingArea::ChangeGamma(double g) {
    FuncInf->nm->set_gamma(g);
}

void DrawingArea::ChangeSigma(double s) {
    FuncInf->nm->set_sigma(s);
}

void DrawingArea::ChangeNMdist(double d){
    FuncInf->nm->set_epsilon(d);
}

void DrawingArea::ChangeRSdist(double d){
    FuncInf->st->init_dist(d);
}

void DrawingArea::ChangeProb(double p){
    FuncInf->rs->SetProb(p);
}

void DrawingArea::ChangeCounter(const QString & text){
    double c = text.toInt();
    FuncInf->st->init_counter(c);
}
