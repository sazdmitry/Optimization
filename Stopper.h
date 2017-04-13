#pragma once

#include "iostream"
#include <vector>
#include <memory>
#include <random>  
#include <ctime>  
#include <math.h>

using std::vector;

double genAlpha();
double Norm(vector<double> x1, vector<double> x2, int dom);
template <typename T> void PrintVector(vector<T>& x);

///Метод остановки для случайного поиска
class Stopper {
protected:

	vector<double> current_vector;
	int max_value = 0;
	int counter = 0;
	int failcounter = 0;
	double distance = 0;
public:
    void reset();
    void init_counter(int max);
    void init_dist(double max_distance);
    int get_counter() const;
    int get_maxcounter() const;
    double get_distance() const;
    Stopper();
	virtual ~Stopper();
	///Возвращает true, если больше не нужно проводить случайный поиск
	virtual bool end_of_search(const vector<double>& x1, const vector<double>& x2, int n)=0;
};

///Остановка по счетчику
class CounterStop : public Stopper {
public:
    CounterStop();
	bool end_of_search(const vector<double>& x1, const vector<double>& x2, int n);
};

///Остановка по числу неудач
class FailStop : public Stopper {
public:
    FailStop();
	bool end_of_search(const vector<double>& current, const vector<double>& previous, int n);
};

///Остановка по расстоянию между значениями
class DistanceStop : public Stopper {
public:
    DistanceStop();
	bool end_of_search(const vector<double>& x1, const vector<double>& x2, int n);
};




