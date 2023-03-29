//1) Подключение файла диалога
#include "pch.h"
#include "framework.h"
#include "Task1-Endulum_2.h"
#include "Task1-Endulum_2Dlg.h"
#include "afxdialogex.h"

#include <vector>
using namespace std;

#define PI 3.14159265358979
#define GI 9.81


//Определяет работать или нет потоку
bool status_th = false;


double c = 1.;
double l = 5;
double k = 0.2;
//Функция движения
double funkX(double t, double x, double v) {
	double new_c = (c / l * l);
	if (v > 0) new_c *= -1;
	return  (new_c - (k * v)/ (l * l)  - (GI / l) * sin(x));
}



//4)Задаем действия в потоке
DWORD WINAPI animationThread(LPVOID t)
{
	//4.1)Создаем объект нашего окна
	CTask1Endulum2Dlg* thisWind = (CTask1Endulum2Dlg*)t;

	//Проверяем нач. параметры
	c = thisWind->input_C;
	l = thisWind->input_L;
	k = thisWind->input_K;
	
	//Начальные условия Рунгетута
	double x = thisWind->input_Fi0, v = thisWind->input_input_V0, time = 0;
	thisWind->myRungeKutta.resetAll(x, v, time, funkX);

	//Область отрисовки маятника
	double rad = l;
	thisWind->painterPendulum.SetDataCoordinate(rad, -rad, rad, -rad);

	//Область отрисовки траектории
	double maxV = sqrt(2 * GI * rad * (1 - cos(x)));
	thisWind->painterTrajectory.SetDataCoordinate(x, -x, maxV, -maxV);
	vector<double> x_vector, v_vector;


	int start = 0;
	int iter_save = 4;
	bool not_find_max_V = true;
	double step_t = thisWind->input_stepT;
	int delTime = thisWind->input_delayFrame;
	int skip = 4;

	int stop = 0;
	bool stop_first = true;
	double new_x, old_x;
	while (status_th) {
		//---------Работа в потоке---------//
		//4.2)Прописываем необходимые команды в потоке

		//Получение нового состояния
		state_system new_state;
		new_state = thisWind->myRungeKutta.getNextPosition(step_t);

		//Расчет координаты маятника по углу и отрисовка
		double dataX = sin(new_state.x) * rad, dataY = - cos(new_state.x) * rad;
		thisWind->painterPendulum.Draw2(dataX, dataY);
		
		//Сохранение точек фазовой траектории
		if (iter_save == skip) {
			x_vector.push_back(new_state.x);
			v_vector.push_back(new_state.v);
			iter_save = 0;		
		}
		else {
			iter_save++;
		}
		/*
		//Проверка остановки
		if (2000/(delTime+20)  <=stop) {
			if (!stop_first) {
				new_x = x_vector[x_vector.size() - 1];

				double otnosh_x = abs(new_x / old_x);

				CString str;
				str.Format(L"%.0001f", otnosh_x);
				thisWind->AAAA.SetWindowTextW(str);

				if (otnosh_x > 0.99 && otnosh_x < 1.01) {
					CString str = L"stop";
					thisWind->AAAA.SetWindowTextW(str);
					break;
				}
				old_x = new_x;

			}
			else {
				old_x = x_vector[x_vector.size() - 1];
				stop_first = false;
			}
			stop = 0;
		}
		else {
			stop++;
		}
		*/
		//Находи макс скорость и масштабирует фаз траекторию по размеры
		if (abs(new_state.x)< x*0.1 && not_find_max_V) {
			not_find_max_V = false;
			maxV = abs(new_state.v);
			thisWind->painterTrajectory.SetDataCoordinate(x, -x, maxV, -maxV);
		}

		thisWind->painterTrajectory.Draw(x_vector, v_vector,'B',L"φ",L"V");



		//------Конец работы в потоке------//
		Sleep(delTime);		//4.3) Указываем задержку между кадрами
	}

	//thisWind->AAAA.SetWindowTextW(L"stop");
	return 0;
}


//2) Функция создания потока и указываем нужно простарнство
void CTask1Endulum2Dlg::startAnimationFlow()	
{
	if (status_th) {
		finishAnimationFlow();
		if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())choiceParameterResearched('l');
		else if (((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck())choiceParameterResearched('k');
		else if (((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck())choiceParameterResearched('c');
		else if (((CButton*)GetDlgItem(IDC_RADIO4))->GetCheck())choiceParameterResearched('v');
		else if (((CButton*)GetDlgItem(IDC_RADIO5))->GetCheck())choiceParameterResearched('f');
		return;
	}


	portrait_adjustment(false);
	//запуск потока
	status_th = true;
	LPVOID lpParameter = (LPVOID)this;
	HANDLE thread = CreateThread(
		NULL,				//LPSECURITY_ATTRIBUTES lpThreadAttributes, // дескриптор защиты
		0,					//SIZE_T dwStackSize,                       // начальный размер стека
		animationThread,	//LPTHREAD_START_ROUTINE lpStartAddress,    // функция потока
		lpParameter,		//LPVOID lpParameter,                       // параметр потока
		0,					//DWORD dwCreationFlags,                    // опции создания
		NULL				//LPDWORD lpThreadId						// идентификатор потока
	);
	//UpdateData(FALSE);
}

//3) Создаем функцию endAnimationFlow и указываем нужно простарнство
void CTask1Endulum2Dlg::finishAnimationFlow()
{
	status_th = false;
	//UpdateData(FALSE);
}
