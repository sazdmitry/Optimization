#pragma once
#include "Stopper.h"
#include "Domain.h"
#include "MyFunction.h"
///Поиск минимума методом случайного поиска
/*!
Случайный поиск не требует дополнительного исследования функции и очень прост в реализации и использовании.
Класс использует в качестве критерия остановки класс Stopper.
*/
class RandomSearch
{
private:
	///Текущая область поиска на шаге
	Domain current_dom;
	///Объект типа MyFunction, обозначающий, где производить поиск минимума
	MyFunction* current_func;
	///Критерий остановки
	Stopper* stop_method;
	///Вероятность локального поиска
	double p = 0.5;
	///Текущая размерность
	int dim = 0;
public:
	RandomSearch();
	~RandomSearch();
    int GetCount() const;
	///Установить вероятность локального поиска (автоматическое приведение к 0 или 1 при неправильном вводе)
	void SetProb(const double& p);
	///Инициализация объектом MyFunction
	void init_funct(MyFunction *f);
	///Устанавливаем метод установки
	void SetStopper(Stopper* s);
    vector<vector<double>> start_alg(const vector<double>& x0);
};

