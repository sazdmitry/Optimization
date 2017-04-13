#include "funcinformation.h"

FuncInformation::FuncInformation()
{
    mf=new Myfunc1();
    nm=new Nelder_mead();
    rs=new RandomSearch();
    st=new CounterStop();
    st->init_counter(1001);
    st->init_dist(1E-05);
    nm->init_funct(mf);
    rs->init_funct(mf);
    rs->SetStopper(st);
};

FuncInformation::~FuncInformation() {
    delete mf;
    delete nm;
    delete rs;
    delete st;
};

vector<double> FuncInformation::ConvertPoint(int width,int height,int x, int y) const {
    vector<double> point(2);
    double xmin = mf->GetDom().GetLowCase()[0];
    double ymin = mf->GetDom().GetLowCase()[1];
    double xmax = mf->GetDom().GetUpperCase()[0];
    double ymax = mf->GetDom().GetUpperCase()[1];

    double step_x=(xmax-xmin)/width;
    double step_y=(ymax-ymin)/height;

    point[0]=xmin+x*step_x;
    point[1]=ymax-y*step_y;
    return point;
};

void FuncInformation::StartAlg(int width,int height, int x, int y){
    vector<double> x0 = ConvertPoint(width,height,x,y);
    track = idx_met==0 ? rs->start_alg(x0) : nm ->start_alg(x0);
    result = mf->evaluate(track[track.size()-1]);
    current_counter = idx_met==0 ? rs->GetCount() : nm ->get_counter();
}



void FuncInformation::CalculateRange(int width,int height, int Npart) {
    vector<vector<double>> EvaluateField;
    double value;
    double xmin = mf->GetDom().GetLowCase()[0];
    double ymin = mf->GetDom().GetLowCase()[1];
    double xmax = mf->GetDom().GetUpperCase()[0];
    double ymax = mf->GetDom().GetUpperCase()[1];

    double step_x=(xmax-xmin)/width;
    double step_y=(ymax-ymin)/height;

    double min_value=mf->evaluate({xmin,ymax});
    double max_value=mf->evaluate({xmin,ymax});

    vector<double> row(height);
    for (int i=0;i<width;++i) {
        row.clear();
        for (int j=0;j<height;++j) {
            value = mf->evaluate({xmin+i*step_x,ymax-j*step_y});
            if (min_value>value) min_value=value;
            if (max_value<value) max_value=value;
            row.push_back(value);
        }
        EvaluateField.push_back(row);
    }

    RangeField=vector<vector<int>>(width);
    for (int i=0; i<width;++i) {
       RangeField[i]=vector<int>(height);

        std::transform(EvaluateField[i].begin(),
                       EvaluateField[i].end(),
                      RangeField[i].begin(),
                       [&](double x) -> int {
            return Npart*(log((x-min_value)+1)/log(max_value-min_value+1));
        });
  };
};

void FuncInformation::ChangeFunction(int idx){
    delete mf;
    switch (idx) {
    case 0: mf = new Myfunc1(); break;
    case 1: mf = new Myfunc2(); break;
    case 2: mf = new Myfunc3(); break;
    }
    nm->init_funct(mf);
    rs->init_funct(mf);
    track.clear();
    track.shrink_to_fit();
}

void FuncInformation::ChangeStopper(int idx){
    int prev_counter = st->get_maxcounter();
    int prev_dist = st->get_distance();
    delete st;
    switch (idx) {
    case 0: st = new CounterStop(); break;
    case 1: st = new FailStop(); break;
    case 2: st = new DistanceStop(); break;
    }
    st->init_counter(prev_counter);
    st->init_dist(prev_dist);
    rs->SetStopper(st);
}

void FuncInformation::ChangeMethod(int idx){
    idx_met=idx;
}
