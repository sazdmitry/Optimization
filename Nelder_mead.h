#pragma once
#include "Stopper.h"
#include "Domain.h"
#include "MyFunction.h"
///Поиск минимума методом деформируемого многогранника
/*!
Метод безусловной оптимизации функции от нескольких переменных, не использующий производной (точнее — градиентов) функции, а поэтому легко применим к негладким и/или зашумлённым функциям.
Суть метода заключается в последовательном перемещении и деформировании симплекса вокруг точки экстремума.
*/
class Nelder_mead
{
	friend Domain;
protected:
	///Коэффициент отражения(наихудшей вершины относительно центроида)
	double alpha = 1.3;
	///Коэффициент сжатия
	double beta = 0.35;
	///Коэффициент растяжения
	double gamma = 2.5;
	///Коэффициент сжатия вершин симплекса к найденному минимуму
    double sigma = 0.75;
	///Вершины симплекса
	vector<vector<double>> A;
	///Счетчик итераций
	int counter = 0;
	///Индекс вершины симплекса, на которой достигается наибольшее значение
	int argmax_idx = 0;
	///Индекс вершины симплекса, на которой достигается наименьшее значение
	int argmin_idx = 0;
	///Индекс вершины симплекса, на которой достигается второе наибольшее значение
	int secargmax_idx = 0;
	///Центроид симплекса без вершины с наибольшим значением целевой функции
	vector<double> center_of_mass;
	///Точка, полученная отражением
	vector<double> reflection; 
	///Точка, полученная растяжением 
	vector<double> expansion;
	///Точка, полученная при сжатии
	vector<double> compression;
	///Функция, устанавливающая значения argmax, argmin и argsecmax на данном этапе
	void FindMinMax();
	///Объект типа MyFunction, обозначающий, где производить поиск минимума
	MyFunction* current_func = 0;
	///Константа для критерия остановки
	double eps = 10E-5;
	///Текущая размерность
	int dim = 0;
public:
	Nelder_mead();
	~Nelder_mead();
	///Устанавливаем параметры поиска: Коэф. отражения alpha=a, коэф. сжатия beta=b, коэф. растяжения gamma=c и коэф. сжатия вершин к найденному минимуму sigma=d
	void SetCoef(const double a, const double b, const double c, const double d);
	///Запускаем алгоритм в начальной точке x0
    vector<vector<double>> start_alg(const vector<double>& x0);
	///Инициализация объектом MyFunction
	void init_funct(MyFunction *f);
	///Установить константу для критерия остановки
	void set_epsilon(double e);
	///Получить значение счетчика
	int get_counter() const;
    void set_alpha(double a);
    void set_beta(double b);
    void set_gamma(double g);
    void set_sigma(double s);
};

