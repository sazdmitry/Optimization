#include "Domain.h"

int Domain::GetDim() { return dim; };
Domain::Domain() : upper(vector<double>(0)), lower(vector<double>(0)), dim(0) {};
Domain::Domain(const Domain& dom) { lower = dom.lower; upper = dom.upper; dim = dom.dim; };
Domain::Domain(int DIM,const vector<double>& MIN,const vector<double>& MAX) :dim(DIM), lower(MIN), upper(MAX) {};
Domain::~Domain() {};
void Domain::FixDomain(vector<double>* vect)
{
	for (int i = 0; i < dim; ++i) {
		if ((*vect)[i] > upper[i]) (*vect)[i] = upper[i];
		if ((*vect)[i] < lower[i]) (*vect)[i] = lower[i];
	}
}
void Domain::setDomain(const vector<double>& MIN, const vector<double>& MAX) {
	lower = MIN;
	upper = MAX;
}
vector<double> Domain::GetLowCase() const {
    return lower;
}
vector<double> Domain::GetUpperCase() const {
    return upper;
}
void Domain::setDimension(const int& DIM) { dim = DIM; }
void Domain::Compress(const vector<double>& x, double c) {
	for (int i = 0; i < dim; ++i) {
		upper[i] = (upper[i] + x[i]) / c;
		lower[i] = (lower[i] + x[i]) / c;
	}
}

vector<double> Domain::ThrowPoint()
{
	vector<double> temp;
	for (int i = 0; i < dim; ++i) {
		temp.push_back(genAlpha()*(upper[i] - lower[i]) + lower[i]);
	}
	return temp;
}
