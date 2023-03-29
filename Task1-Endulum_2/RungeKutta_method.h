//----------------------------------------------------------------------//
// 	   Класс реаоизация: Метод Рунге-Кутты 4-го порядка					//
//для решения дифференциального уравнения 2-го порядка вида				//
//				x'' = f(t, x, x')										//
//																		//
// НЕОБХОДИМЫЕ ФАЙЛЫ: RungeKutta_method.cpp ; RungeKutta_method.h		//
//																		//
// АЛГОРИТМ РАБОТЫ:														//
// 0) Проинцилизировать функцию: x'' = f(t, x, x')						//
// double funkX(double t,double x,double v)								//
// return  (x>0 ? -(1./2) : +(1./2)) - (0.2/2.)*v - (9.8/2.) * sin(x);	//
// 1)Подключите класс в свой проект										//
//		#include "RungeKutta_method.h"									//
// 2) Создать объект класса и заполнить начальными параметрами	(2 вар.)//
// 2.1) RungeKutta_method pendulum (0,		//нач. координата,			//
//									0,		//нач. ускорение,			//
//									0,		//время нач. отсчета,		//
//									funkX								//
//									);									//
// 2.2) RungeKutta_method pendulum;										//
//		pendulum.resetAll (			0,		//нач. координата,			//
//									0,		//нач. ускорение,			//
//									0,		//время нач. отсчета,		//
//									funkX	);							//
// 3)Вызвать метод getNextPosition,										//
//для получения следующей координаты через время дельта t				//
//		double xNewPosition = pendulum.getNextPosition(					//
//									0.1		//время шага				//
//									);									//
// *Для сброса в начальные условия,										//
//воспользоваться функцией resetToBeginning								//
//----------------------------------------------------------------------//

#pragma once

struct state_system {
	double x, v, t;
};

class RungeKutta_method
{
private:
	//------------------ПОЛЯ:-------------------//
	
	//Заданны ли начальные поля
	bool _initialization_status;

	//Координата сейчас							x
	double _x;

	//Скорость сейчас/первая производная коорд.	x'
	double _x_1degree;

	//Время сейчас								t
	double _t;

	//Функция движения коорднаты,
	//диф-ого ур-ния 2-ого порядка				x'' = f(t, x, x')
	double (*_move_function)(double t, double x, double x_1degree);

	//-----------------Методы:------------------//

	//k1
	double _k1(double& delta_t);

	//k2
	double _k2(double& k1, double& delta_t);

	//k3
	double _k3(double& k1, double& k2, double& delta_t);

	//k4
	double _k4(double& k2, double& k3, double& delta_t);

	//x_(k+1)
	double _x_kPlusOne(double& k1, double& k2, double& k3, double& delta_t);

	//x_(k+1)
	double _x_kPlusOne_1degree(double& k1, double& k2, double& k3, double& k4, double& delta_t);

public:

	//--------------Конструкторы:---------------//

	RungeKutta_method();

	//Задание начальных условий и функции движения
	RungeKutta_method(
		double& x0, double& x0_1degree, double& t0,
		double (*move_function)(double t, double x, double x_1degree)
	);
	//-----------------Методы:------------------//

	//Сброс всего
	void resetAll(
		double& x0, double& x0_1degree, double& t0,
		double (*move_function)(double t, double x, double x_1degree)
	);

	//Сброс в начальные координаты
	void resetToBeginning(double& x0, double& x0_1degree, double& t0);

	//Функция получения следующей позиции
	state_system getNextPosition(double& delta_t);
};

