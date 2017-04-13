#pragma once
#include "Stopper.h"

///Область определения функции
class Domain {
protected:
	///Размерность
	int dim;
	///Верхняя граница рассматриваемой области	
	vector<double> upper;
	///Нижняя граница рассматриваемой области
	vector<double> lower;
public:
	///Получить размерность области
	int GetDim();
	Domain();
	Domain(const Domain& dom);
	Domain(int DIM, const vector<double>& MIN, const vector<double>& MAX);
	~Domain();
    vector<double> GetLowCase() const;
    vector<double> GetUpperCase() const;
	///Спроектировать точку на текущее пространство
	void FixDomain(vector<double>* vect);
	///Установить верхнюю и нижнюю границу области
	void setDomain(const vector<double>& MIN, const vector<double>& MAX);
	///Установка размерности
	void setDimension(const int& DIM);
	///Сжатие в заданной точке с заданным коэффициентом
	void Compress(const vector<double>& x, double c = 2);
	///Выдать случайную точку из текущей области
	vector<double> ThrowPoint();
};
