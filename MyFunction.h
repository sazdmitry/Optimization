#pragma once
#include "Domain.h"
#include "Stopper.h"
///Родительский класс исследуемой функции
class MyFunction {
protected:
	Domain Dom;
	double min_of_func;
public:
	MyFunction();
	virtual ~MyFunction();
	///Вычисление значения функции в заданной точке
	virtual double evaluate(const vector<double>& x) const;
	///Установить область определения функции
	void setDomain(const vector<double>& min, const vector<double>& max);
	///Получить текущую область
	Domain GetDom() const;
	///Получить минимальное значение функции (аналитическое)
	double get_min_value() const;
};
///f(x,y)=(x-70)^2+(x-y)^2
class Myfunc1 : public MyFunction
{
public:
    Myfunc1();
	double evaluate (const vector<double>& x) const;
};
///f(x,y)=y^2*exp(|x+y|^2)-cos(x+y)
class Myfunc2 : public MyFunction {
public:
    Myfunc2();
	double evaluate(const vector<double>& x) const;
};
///x_1*exp(-|x|^2)+sin(10*|x|^2)
class Myfunc3 : public MyFunction {
public:
    Myfunc3();
	double evaluate(const vector<double>& x) const;
};
