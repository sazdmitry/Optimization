
#include "Stopper.h"

static std::random_device rd;
std::mt19937 gen_eng(rd.entropy() ? rd() : (unsigned long)(std::time(nullptr)));

double genAlpha() {
	static std::uniform_real_distribution<double> unif_real_01(0.0, 1.0);
	return unif_real_01(gen_eng);
}

double Norm(vector<double> x1, vector<double> x2, int dom) {
	double temp = 0;
	for (int i = 0; i < dom; ++i) {
		temp += (x1[i] - x2[i])*(x1[i] - x2[i]);
	}
	return sqrt(temp);
};


int Stopper::get_counter() const
{
	return counter;
}

int Stopper::get_maxcounter() const {
    return max_value;
}

double Stopper::get_distance() const {
    return distance;
}

Stopper::~Stopper()
{
}
bool Stopper::end_of_search(const vector<double>& x1, const vector<double>& x2, int n)
{
	return false;
}
;

void Stopper::init_counter(int max) {
    max_value=max;
}

void Stopper::init_dist(double max_distance) {
    distance=max_distance;
}

void Stopper::reset() {
    counter=0;
    failcounter=0;
}
Stopper::Stopper() {};

CounterStop::CounterStop() {};
bool CounterStop::end_of_search(const vector<double>& x1, const vector<double>& x2, int n) {
	++counter;
	return (counter >= max_value);
};


FailStop::FailStop() {};
bool FailStop::end_of_search(const vector<double>& current, const vector<double>& previous, int n) {
	if (current_vector == current) ++failcounter; else failcounter = 0;
	current_vector = current;
	++counter;
	return (failcounter >= max_value);
};


DistanceStop::DistanceStop() {};
bool DistanceStop::end_of_search(const vector<double>& x1, const vector<double>& x2, int n) {
	++counter;
	return ((Norm(x1, x2, n) < distance) || (counter >= max_value));
};

