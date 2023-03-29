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
bool status_thPortrait;


double c_Portrait = 0;
double l_Portrait = 5;
double k_Portrait = 0;
//Функция движения
//param: 0 - C; 1 - l; 2-k
double funkXX(double t, double x, double v, vector <double> param) {
	double new_c = (param[0] / param[1] * param[1]);
	if (v > 0) new_c *= -1;
	return  (new_c - (param[2] * v) / (param[1] * param[1]) - (GI / param[1]) * sin(x));
}



double max_vector(vector<double>& val) {
	double maxV = val[0];
	for (int i = 0; i < val.size(); i++) {
		if (maxV < val[i]) {
			maxV = val[i];
		}
	}
	return maxV;
}

double max_vectorStat_x(vector<vector<state_system>>& val) {
	vector<double> x;
	for (int i = 0; i < val.size(); i++) {
		x.push_back(val[i][0].x);
	}
	return max_vector(x);
}

double max_vectorStat_v(vector<vector<state_system>>& val) {
	vector<double> v;
	for (int i = 0; i < val.size(); i++) {
		v.push_back(val[i][0].v);
	}
	return max_vector(v);
}

vector<double> range(double start, double end, double step) {
	vector<double> res;
	for (double i = start; i <= end; i += step) {
		res.push_back(i);
	}
	return res;
}

//4)Задаем действия в потоке
DWORD WINAPI animationThreadPortrait(LPVOID t)
{

	char investigated_quantity = '?';

	//4.1)Создаем объект нашего окна
	CTask1Endulum2Dlg* thisWind = (CTask1Endulum2Dlg*)t;

	//Очищаем не нужное поле
	thisWind->painterPendulum.Clean();

	//Задаем нач параметры:
	vector <double> l, k, c, v0, fi0;


	if (((CButton*)thisWind->GetDlgItem(IDC_RADIO1))->GetCheck()) {
		l = range(
			thisWind->inputFP_L0,
			thisWind->inputFP_L_end,
			thisWind->inputFP_L_step);
		investigated_quantity = 'l';
	}
	else l.push_back(thisWind->inputFP_L0);

	if (((CButton*)thisWind->GetDlgItem(IDC_RADIO2))->GetCheck()) {
		k = range(
			thisWind->inputFP_K_start,
			thisWind->inputFP_K_end,
			thisWind->inputFP_K_step);
		investigated_quantity = 'k';
	}
	else k.push_back(thisWind->inputFP_K_start);

	if (((CButton*)thisWind->GetDlgItem(IDC_RADIO3))->GetCheck()) {
		c = range(
			thisWind->inputFP_C_start,
			thisWind->inputFP_C_end,
			thisWind->inputFP_C_step);
		investigated_quantity = 'c';
	}
	else c.push_back(thisWind->inputFP_C_start);

	//Вектора состояний
	vector<vector<state_system>> PhasePortraitStates;

	//Начальные условия Рунгетута
	if (((CButton*)thisWind->GetDlgItem(IDC_RADIO4))->GetCheck())
	{
		for (
			double V0 = thisWind->inputFP_V0_start;
			V0 <= thisWind->inputFP_V0_end; 
			V0 += thisWind->inputFP_V0_step
			)
		{
			state_system new_state = { thisWind->inputFP_Fi0_start,V0,0 };
			vector <state_system> new_trajectory;
			new_trajectory.push_back(new_state);
			PhasePortraitStates.push_back(new_trajectory);
		}
		investigated_quantity = 'v';
	}
	else if (((CButton*)thisWind->GetDlgItem(IDC_RADIO5))->GetCheck()) {
		for (
			double fi0 = thisWind->inputFP_Fi0_start;
			fi0 <= thisWind->inputFP_Fi0_end;
			fi0 += thisWind->inputFP_Fi0_step
			)
		{
			state_system new_state = { fi0,thisWind->inputFP_V0_start,0 };
			vector <state_system> new_trajectory;
			new_trajectory.push_back(new_state);
			PhasePortraitStates.push_back(new_trajectory);
		}
		investigated_quantity = 'f';
	}

	//Область отрисовки траектории
	double rad = max_vector(l);
	double maxX = thisWind->inputFP_Fi0_start;//max_vectorStat_x(PhasePortraitStates);
	double maxV = thisWind->inputFP_V0_start;//sqrt(2 * GI * rad * (1 - cos(maxX)) + max_vectorStat_v(PhasePortraitStates));
	thisWind->painterPortrait.SetDataCoordinate(PI, -PI, maxV, -maxV);

	//Создаем вектор рунгекут для вычисляения
	vector < RungeKutta_method_extended > myyRungeKutta;

	if (investigated_quantity == '?') return 0;
	else if (investigated_quantity == 'v' || investigated_quantity == 'f') {
		vector <double> myParam = { c[0],l[0],k[0] };

		for (int i = 0; i < PhasePortraitStates.size(); i++) {
			RungeKutta_method_extended experienceRungeKutta(
				PhasePortraitStates[i][0].x,
				PhasePortraitStates[i][0].v,
				PhasePortraitStates[i][0].t,
				funkXX,
				myParam);
			myyRungeKutta.push_back(experienceRungeKutta);
		}
	}
	else if (investigated_quantity == 'l') {
		state_system new_state = { thisWind->inputFP_Fi0_start,thisWind->inputFP_V0_start,0 };
		vector <state_system> new_trajectory;
		new_trajectory.push_back(new_state);
		
		for (int i = 0; i < l.size(); i++) {
			PhasePortraitStates.push_back(new_trajectory);

			vector <double> myParam = { c[0],l[i],k[0] };
			RungeKutta_method_extended experienceRungeKutta(
				PhasePortraitStates[i][0].x,
				PhasePortraitStates[i][0].v,
				PhasePortraitStates[i][0].t,
				funkXX,
				myParam);
			myyRungeKutta.push_back(experienceRungeKutta);
		}

	}
	else if (investigated_quantity == 'k') {
		state_system new_state = { thisWind->inputFP_Fi0_start,thisWind->inputFP_V0_start,0 };
		vector <state_system> new_trajectory;
		new_trajectory.push_back(new_state);

		for (int i = 0; i < k.size(); i++) {
			PhasePortraitStates.push_back(new_trajectory);

			vector <double> myParam = { c[0],l[0],k[i] };
			RungeKutta_method_extended experienceRungeKutta(
				PhasePortraitStates[i][0].x,
				PhasePortraitStates[i][0].v,
				PhasePortraitStates[i][0].t,
				funkXX,
				myParam);
			myyRungeKutta.push_back(experienceRungeKutta);
		}

	}
	else if (investigated_quantity == 'c') {
		state_system new_state = { thisWind->inputFP_Fi0_start,thisWind->inputFP_V0_start,0 };
		vector <state_system> new_trajectory;
		new_trajectory.push_back(new_state);

		for (int i = 0; i < c.size(); i++) {
			PhasePortraitStates.push_back(new_trajectory);

			vector <double> myParam = { c[i],l[0],k[0] };
			RungeKutta_method_extended experienceRungeKutta(
				PhasePortraitStates[i][0].x,
				PhasePortraitStates[i][0].v,
				PhasePortraitStates[i][0].t,
				funkXX,
				myParam);
			myyRungeKutta.push_back(experienceRungeKutta);
		}

	}


	int iter_save = 4;
	bool not_find_max_V = true;
	double step_t = thisWind->inputFP_TimeStep;
	int delTime = thisWind->inputFP_delay;
	int skip = 4;

	while (status_thPortrait) {
		//---------Работа в потоке---------//
		//4.2)Прописываем необходимые команды в потоке

		//Получение нового состояния
		int len = PhasePortraitStates[0].size();
		for (int i = 0; i < myyRungeKutta.size(); i++) {
			PhasePortraitStates[i].push_back(myyRungeKutta[i].getNextPosition(step_t));
			//Проверка, изменилось ли макс значение
			if (abs(PhasePortraitStates[i][len].v) > maxV) {
				maxV = abs(PhasePortraitStates[i][len].v);
				thisWind->painterPortrait.SetDataCoordinate(PI, -PI, maxV, -maxV);
			}
			if (abs(PhasePortraitStates[i][len].x) > maxX) {
				maxX = abs(PhasePortraitStates[i][len].x);
				thisWind->painterPortrait.SetDataCoordinate(PI, -PI, maxV, -maxV);
			}
		}
		/*
		//Находи макс скорость и масштабирует фаз траекторию по размеры
		if (not_find_max_V) {
			for (int i = 0; i < myyRungeKutta.size(); i++) {
				if (abs(PhasePortraitStates[i][PhasePortraitStates[i].size() - 1].x) < maxX * 0.1) {
					not_find_max_V = false;
					maxV = abs(PhasePortraitStates[i][PhasePortraitStates[i].size() - 1].v);
					thisWind->painterPortrait.SetDataCoordinate(PI, -PI, maxV, -maxV);
				}
			}
		}*/



		thisWind->painterPortrait.Draw(PhasePortraitStates,L"φ",L"V");



		//------Конец работы в потоке------//
		Sleep(delTime);		//4.3) Указываем задержку между кадрами
	}
	//thisWind->AAAA.SetWindowTextW(L"stop");
	return 0;
}


//2) Функция создания потока и указываем нужно простарнство
void CTask1Endulum2Dlg::startAnimationFlowPortrait()
{
	if (status_thPortrait) {
		status_thPortrait = false;
		finishAnimationFlow();
		portrait_trajectoryt(true);
		return;
	}
	portrait_trajectoryt(false);
	//запуск потока
	status_thPortrait = true;
	LPVOID lpParameter = (LPVOID)this;
	HANDLE thread = CreateThread(
		NULL,				//LPSECURITY_ATTRIBUTES lpThreadAttributes, // дескриптор защиты
		0,					//SIZE_T dwStackSize,                       // начальный размер стека
		animationThreadPortrait,	//LPTHREAD_START_ROUTINE lpStartAddress,    // функция потока
		lpParameter,		//LPVOID lpParameter,                       // параметр потока
		0,					//DWORD dwCreationFlags,                    // опции создания
		NULL				//LPDWORD lpThreadId						// идентификатор потока
	);
}

//3) Создаем функцию endAnimationFlow и указываем нужно простарнство
void CTask1Endulum2Dlg::finishAnimationFlowPortrait()
{
	status_thPortrait = false;
}
