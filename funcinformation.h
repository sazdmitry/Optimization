#ifndef FUNCINFORMATION_H
#define FUNCINFORMATION_H
#pragma once

#include "MyFunction.h"
#include "Nelder_mead.h"
#include "RandomSearch.h"
#include "Stopper.h"

#include "algorithm"
#include <iterator>

class FuncInformation
{
friend class DrawingArea;
public:
    FuncInformation();
private:
    ~FuncInformation();

    MyFunction* mf=0;
    Nelder_mead* nm=0;
    RandomSearch* rs=0;
    Stopper* st=0;
    int idx_func=0;
    int idx_met=0; //0-NM 1-RS
    int idx_stop=0; //0-counter 1-fail 2-distance

    void CalculateRange(int width, int height, int Npart);
    void StartAlg(int width,int height,int x, int y);
    vector<double> ConvertPoint(int width,int height,int x, int y) const;
    double result;
    int current_counter;
    void ChangeFunction(int idx);
    void ChangeStopper(int idx);
    void ChangeMethod(int idx);

//    void ChangeRSprob(double p);
//    void ChangeRScounter(int c);
//    void ChangeRSdist(double d);

//    void ChangeNMdist(double d);
//    void ChangeNMalpha(double a);
//    void ChangeNMbeta(double b);
//    void ChangeNMgamma(double g);
//    void ChangeNMsigma(double s);

    vector<vector<double>> track;
    vector<vector<int>> RangeField;
};

#endif // FUNCINFORMATION_H
