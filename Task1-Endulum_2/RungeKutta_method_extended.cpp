#include "pch.h"
#include "RungeKutta_method_extended.h"

//-----------------Методы:------------------//

//k1
double RungeKutta_method_extended::_k1(double&  delta_t)
{
	return (_move_function(_t, _x, _x_1degree, _param) * delta_t);
}

//k2
double RungeKutta_method_extended::_k2(double& k1, double& delta_t)
{
	return _move_function(
		_t + delta_t / 2,					//t
		_x + _x_1degree * (delta_t / 2),	//x
		_x_1degree + k1 / 2,				//x'
		_param ) * delta_t;
}

//k3
double RungeKutta_method_extended::_k3(double&  k1, double&  k2, double&  delta_t)
{
	return _move_function(
		_t + delta_t / 2,										//t
		_x + _x_1degree * (delta_t / 2) + (k1 / 4) * delta_t,	//x
		_x_1degree + k2 / 2										//x'
		, _param
	) * delta_t;
}

//k4
double RungeKutta_method_extended::_k4(double&  k2, double&  k3, double&  delta_t)
{
	return _move_function(
		_t + delta_t,											//t
		_x + _x_1degree * delta_t + (k2 / 2) * delta_t,			//x
		_x_1degree + k3											//x'
		, _param
	) * delta_t;
}

//x_(k+1)
double RungeKutta_method_extended::_x_kPlusOne(double&  k1, double&  k2, double&  k3, double&  delta_t)
{
	return _x + _x_1degree * delta_t + (1. / 6.) * (k1 + k2 + k3) * delta_t;
}

//x_(k+1)
double RungeKutta_method_extended::_x_kPlusOne_1degree(double&  k1, double&  k2, double& k3, double&  k4, double& delta_t)
{
	return _x_1degree + (1. / 6.) * (k1 + 2 * k2 + 2 * k3 + k4);
}


//--------------Конструкторы:---------------//

RungeKutta_method_extended::RungeKutta_method_extended()
{ 
	_initialization_status = false;
}

//Задание начальных условий и функции движения
RungeKutta_method_extended::RungeKutta_method_extended
(
	double& x0, double& x0_1degree, double& t0,
	double (*move_function)(double t, double x, double x_1degree, vector <double> funk_param),
	vector <double> &const_param
)
{
	resetAll(x0, x0_1degree, t0, move_function, const_param);
}

//-----------------Методы:------------------//

//Сброс всего
void RungeKutta_method_extended::resetAll(
	double& x0, double& x0_1degree, double& t0,
	double (*move_function)(double t, double x, double x_1degree, vector <double> funk_param),
	vector <double> &const_param
)
{
	//Задаем нач-ную коорд. 	x
	_x = x0;

	//Задаем нач-ную Скорость	x'
	_x_1degree = x0_1degree;

	//Задаем нач-ное Время 		t
	_t = t0;

	//Задаем функцию движения коорднаты x'' = f(t, x, x')
	_move_function = move_function;

	_param = const_param;

	//Инициализация заончена
	_initialization_status = true;
}

//Сброс в начальные координаты
void RungeKutta_method_extended::resetToBeginning(double& x0, double& x0_1degree, double& t0)
{
	//Задаем нач-ную коорд. 	x
	_x = x0;

	//Задаем нач-ную Скорость	x'
	_x_1degree = x0_1degree;

	//Задаем нач-ное Время 		t
	_t = t0;
}

//Функция получения следующей позиции
state_system RungeKutta_method_extended::getNextPosition(double& delta_t)
{
	state_system res;

	//0) Проверка, что начальные параметры заданны, иначе NULL
	if (_initialization_status = false) return res;

	//1) Вычисляем коофиценты k
	double k1 = _k1(delta_t);
	double k2 = _k2(k1, delta_t);
	double k3 = _k3(k1, k2, delta_t);
	double k4 = _k4(k2, k3, delta_t);

	//2) Вычисляем координату на след-щем шаге
	double x_kPlusOne = _x_kPlusOne(k1, k2, k3, delta_t);

	//3) Вычисляем скорость на след-щем шаге
	double x_kPlusOne_1degree = _x_kPlusOne_1degree(k1, k2, k3, k4, delta_t);

	//4) Сохраняем в поля класса координту, время и скорость						x
	_x = x_kPlusOne;
	_x_1degree = x_kPlusOne_1degree;
	_t = _t + delta_t;

	//5) Возвращаем координату
	res.x = _x;
	res.v = _x_1degree;
	res.t = _t;
	return res;
}


