#include "MyFunction.h"


MyFunction::MyFunction() {}
MyFunction::~MyFunction()
{
}
double MyFunction::evaluate(const vector<double>& x) const
{
	return 0.0;
}
;
void MyFunction::setDomain(const vector<double>& min, const vector<double>& max)
{
	Dom.setDomain(min, max);
}
Domain MyFunction::GetDom() const { return Dom; }
double MyFunction::get_min_value() const
{
	return min_of_func;
}
;

Myfunc1::Myfunc1()
{
	min_of_func = 0;
	Dom.setDimension(2);
    vector<double> min({-5,-5});
    vector<double> max({5,5});
    Dom.setDomain(min, max);
}

double Myfunc1::evaluate(const vector<double>& x) const {
    return ((x[0] - 2)*(x[0] - 2) + 3 * (x[0] - x[1])*(x[0] - x[1]));
}

Myfunc2::Myfunc2()
{
	min_of_func = -1;
	Dom.setDimension(2);
    vector<double> min({-1.5,-1.5});
    vector<double> max({1.5,1.5});
    Dom.setDomain(min, max);
}

double Myfunc2::evaluate(const vector<double>& x) const {
    return 9*sin((x[0]-x[1])*(x[0]-x[1]))-cos((x[0] + x[1])*(x[0]+x[1])) + exp(-x[0] + x[1]+1);
}

Myfunc3::Myfunc3()
{
	min_of_func = -1;
    Dom.setDimension(2);
    vector<double> min({-3,-3});
    vector<double> max({2,2});
    Dom.setDomain(min, max);
}
//x_1*exp(-|x|^2)+sin(10*|x|^2)
double Myfunc3::evaluate(const vector<double>& x) const {
    return (x[1]*exp(-x[0]*x[0])+sin(x[0]*x[0]+x[1]*x[1]));
}



