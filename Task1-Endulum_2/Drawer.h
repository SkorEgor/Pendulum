#pragma once

#include <afxwin.h>
#include <vector>
#include "RungeKutta_method.h"
#define pi 3.1415926535897932384626433832795

using namespace std;

struct MyRGB {
	int R, G, B;
};

class Drawer
{
	// Прямоугольник области рисования.
	CRect frame;
	// Указатель на объект окна, области рисования.
	CWnd* wnd;
	// Контекст рисования, привязанный к области рисования.
	CDC* dc;
	// Контекст рисования, привязанный к памяти.
	CDC memDC;
	// Контекст рисования, для сохранения осей.
	CDC memDC_axis;
	// Память для контекста рисования memDC.
	CBitmap bmp;
	// Флаг для отслеживания состояния инициализации класса.
	bool init, init_data, init_axis;

	double _data_x_max, _data_x_min, _data_width;
	double _data_y_max, _data_y_min, _data_height;

	double _screen_x_max, _screen_x_min, _screen_width;
	double _screen_y_max, _screen_y_min, _screen_height;

	double _scaling_x, _scaling_y;
	double _shift_x, _shift_y;

	//отступ от края
	double _indent_x, _indent_y;

	//Название осей
	CString nameX, nameY;
public:
	// Проинициализировать объект класса на основе HWND.
	void Create(HWND hWnd)
	{
		// Получаем указатель на окно.
		wnd = CWnd::FromHandle(hWnd);
		// Получаем прямоугольник окна.
		wnd->GetClientRect(frame);
		// Получаем контекст для рисования в этом окне.
		dc = wnd->GetDC();

		// Создаем буфер-контекст.
		memDC.CreateCompatibleDC(dc);
		memDC_axis.CreateCompatibleDC(dc);
		// Создаем растр для контекста рисования.
		bmp.CreateCompatibleBitmap(dc, frame.Width(), frame.Height());
		// Выбираем растр для использования буфер-контекстом.
		memDC.SelectObject(&bmp);
		memDC_axis.SelectObject(&bmp);
		init = true;
		init_axis = false;
	}

	void SetDataCoordinate(
		double data_x_max, double data_x_min,
		double data_y_max, double data_y_min) {

		_data_x_max = data_x_max;
		_data_x_min = data_x_min;
		_data_width = data_x_max - data_x_min;
		_data_y_max = data_y_max;
		_data_y_min = data_y_min;
		_data_height = data_y_max - data_y_min;

		_indent_x = frame.Width() * 0.05;

		_screen_x_max = frame.Width() - _indent_x;
		_screen_x_min = _indent_x;
		_screen_width = _screen_x_max - _screen_x_min;

		_indent_y = frame.Height() * 0.05;

		_screen_y_max = frame.Height() - _indent_y;
		_screen_y_min = _indent_y;
		_screen_height = _screen_y_max - _screen_y_min;

		_scaling_x = _screen_width / _data_width;
		_scaling_y = -(_screen_height / _data_height);

		_shift_x = _screen_width / 2 + _indent_x;
		_shift_y = _screen_height / 2 + _indent_y;

		init_data = true;
		init_axis = false;
	}

	// Нарисовать график по переданным данным.
	void Draw(	vector<double>& data_x, vector<double>& data_y,	char color, CString nameX = L"X", CString nameY=L"Y")
	{
		if (!init && !init_data) return;

		CPen subgrid_pen(PS_DOT, 1, RGB(200, 200, 200));
		CPen Xgrid_pen(PS_SOLID, 2, RGB(128, 0, 0));
		CPen Ygrid_pen(PS_SOLID, 2, RGB(0, 128, 0));
		CPen grid_pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen data_pen(PS_SOLID, 2, RGB(255, 0, 0));
		CPen data_pen2(PS_SOLID, 2, RGB(38, 0, 255));
		CPen data_blue(PS_SOLID, 2, RGB(106, 90, 205));
		CPen pen_red(PS_SOLID, 2, RGB(178, 34, 34));
		CPen pen_green(PS_SOLID, 2, RGB(0, 128, 0));
		CFont font;
		font.CreateFontW(18, 0, 0, 0,
			FW_DONTCARE,
			FALSE,				// Курсив
			FALSE,				// Подчеркнутый
			FALSE,				// Перечеркнутый
			DEFAULT_CHARSET,	// Набор символов
			OUT_OUTLINE_PRECIS,	// Точность соответствия.	
			CLIP_DEFAULT_PRECIS,//  
			CLEARTYPE_QUALITY,	// Качество
			VARIABLE_PITCH,		//
			TEXT("Times New Roman")		//
		);

		if (!init_axis) {
			// Белый фон.
			memDC.FillSolidRect(frame, RGB(255, 255, 255));

			// Рисуем сетку и подсетку.
			unsigned int grid_size = 10;

			memDC.SelectObject(&subgrid_pen);

			for (double i = 0.5; i < grid_size; i += 1.0)
			{
				memDC.MoveTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_min);
				memDC.LineTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_max);
				memDC.MoveTo(_screen_x_min, _screen_y_min + i * _screen_height / grid_size);
				memDC.LineTo(_screen_x_max, _screen_y_min + i * _screen_height / grid_size);
			}



			for (double i = 0.0; i < grid_size + 1; i += 1.0)
			{
				memDC.SelectObject(&grid_pen);
				if (i == grid_size / 2) memDC.SelectObject(&Ygrid_pen);
				memDC.MoveTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_min);
				memDC.LineTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_max);
				if (i == grid_size / 2) memDC.SelectObject(&Xgrid_pen);
				memDC.MoveTo(_screen_x_min, _screen_y_min + i * _screen_height / grid_size);
				memDC.LineTo(_screen_x_max, _screen_y_min + i * _screen_height / grid_size);
			}

			//Отрисовка цифр координат
			memDC.SelectObject(&font);
			memDC.SetTextColor(RGB(0, 0, 0));
			//SetTextAlign(memDC,);
			for (int i = 0; i < grid_size / 2 + 1; i++)
			{
				CString str;
				str.Format(L"%.1f", _data_x_min + i * (_data_x_max - _data_x_min) / (grid_size / 2));
				memDC.TextOutW(_screen_x_min + (double)i * _screen_width / (grid_size / 2) - _indent_y, _screen_y_min + _screen_height / 2, str);

				str.Format(L"%.1f", _data_y_min + i * (_data_y_max - _data_y_min) / (grid_size / 2));
				memDC.TextOutW(_screen_x_min + _screen_width / 2, _screen_y_max - (double)i * _screen_height / (grid_size / 2) - _indent_y, str);
			}
			//Название оси
			memDC.SetTextColor(RGB(128, 0, 0));
			memDC.TextOutW(_screen_x_max + _indent_x / 3, _screen_y_min + _screen_height / 2, nameX);
			memDC.SetTextColor(RGB(0, 128, 0));
			memDC.TextOutW(_screen_x_min + _screen_width / 2 - 20, 0, nameY);

			//Сохранение в буфер
			memDC_axis.BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);


		}
		else {
			memDC.BitBlt(0, 0, frame.Width(), frame.Height(), &memDC_axis, 0, 0, SRCCOPY);
		}

		// Рисуем график.
		if (data_x.empty() || data_y.empty()) return;

		if (color == 'R')memDC.SelectObject(&pen_red);
		else if (color == 'G')memDC.SelectObject(&pen_green);
		else if (color == 'B')memDC.SelectObject(&data_blue);

		else memDC.SelectObject(&data_pen);


		vector<double> y = convert_range_y(data_y);
		vector<double> x = convert_range_x(data_x);

		memDC.MoveTo(x[0], y[0]);
		for (unsigned int i = 0; i < y.size(); i++)
		{
			memDC.LineTo(x[i], y[i]);
		}

		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
	}

	// Нарисовать график по переданным данным.
	void Draw2(double end_x, double end_y)
	{
		if (!init && !init_data) return;
		if (end_x == 0 || end_y == 0) return;

		CPen subgrid_pen(PS_DOT, 1, RGB(200, 200, 200));
		CPen grid_pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen Xgrid_pen(PS_SOLID, 2, RGB(128, 0, 0));
		CPen Ygrid_pen(PS_SOLID, 2, RGB(0, 128, 0));

		CPen data_pen(PS_SOLID, 2, RGB(255, 0, 0));
		CPen data_pen2(PS_SOLID, 2, RGB(38, 0, 255));
		CPen pen_red(PS_SOLID, 2, RGB(178, 34, 34));
		CPen pen_green(PS_SOLID, 2, RGB(0, 128, 0));
		CFont font;
		font.CreateFontW(18, 0, 0, 0,
			FW_DONTCARE,
			FALSE,				// Курсив
			FALSE,				// Подчеркнутый
			FALSE,				// Перечеркнутый
			DEFAULT_CHARSET,	// Набор символов
			OUT_OUTLINE_PRECIS,	// Точность соответствия.	
			CLIP_DEFAULT_PRECIS,//  
			CLEARTYPE_QUALITY,	// Качество
			VARIABLE_PITCH,		//
			TEXT("Times New Roman")		//
		);
		
		if (!init_axis) {
			// Белый фон.
			memDC.FillSolidRect(frame, RGB(255, 255, 255));

			// Рисуем сетку и подсетку.
			unsigned int grid_size = 10;

			memDC.SelectObject(&subgrid_pen);

			for (double i = 0.5; i < grid_size; i += 1.0)
			{
				memDC.MoveTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_min);
				memDC.LineTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_max);
				memDC.MoveTo(_screen_x_min, _screen_y_min + i * _screen_height / grid_size);
				memDC.LineTo(_screen_x_max, _screen_y_min + i * _screen_height / grid_size);
			}



			for (double i = 0.0; i < grid_size + 1; i += 1.0)
			{
				memDC.SelectObject(&grid_pen);
				if (i == grid_size / 2) memDC.SelectObject(&Ygrid_pen);
				memDC.MoveTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_min);
				memDC.LineTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_max);
				if (i == grid_size / 2) memDC.SelectObject(&Xgrid_pen);
				memDC.MoveTo(_screen_x_min, _screen_y_min + i * _screen_height / grid_size);
				memDC.LineTo(_screen_x_max, _screen_y_min + i * _screen_height / grid_size);
			}

			//Отрисовка цифр координат
			memDC.SelectObject(&font);
			memDC.SetTextColor(RGB(0, 0, 0));
			//SetTextAlign(memDC,);
			for (int i = 0; i < grid_size / 2 + 1; i++)
			{
				CString str;
				str.Format(L"%.1f", _data_x_min + i * (_data_x_max - _data_x_min) / (grid_size / 2));
				memDC.TextOutW(_screen_x_min + (double)i * _screen_width / (grid_size / 2) - _indent_y, _screen_y_min + _screen_height / 2, str);

				str.Format(L"%.1f", _data_y_min + i * (_data_y_max - _data_y_min) / (grid_size / 2));
				memDC.TextOutW(_screen_x_min + _screen_width / 2, _screen_y_max - (double)i * _screen_height / (grid_size / 2) - _indent_y, str);
			}
			//Название оси
			memDC.SetTextColor(RGB(128, 0, 0));
			CString str = L"X";
			memDC.TextOutW(_screen_x_max + _indent_x / 3, _screen_y_min + _screen_height / 2, str);
			memDC.SetTextColor(RGB(0, 128, 0));
			str = L"Y";
			memDC.TextOutW(_screen_x_min + _screen_width / 2 - 20, 0, str);

			//Сохранение в буфер
			memDC_axis.BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);


		}
		else {
			memDC.BitBlt(0, 0, frame.Width(), frame.Height(), &memDC_axis, 0, 0, SRCCOPY);
		}

		//Отрисовка стержня
		CPen rod_pen(PS_SOLID, 3, RGB(106, 90, 205));
		memDC.SelectObject(&rod_pen);

		double screen_beginning_rod_x = 0 * _scaling_x + _shift_x;
		double screen_beginning_rod_y = 0 * _scaling_y + _shift_y;

		double screen_end_rod_x = end_x * _scaling_x + _shift_x;
		double screen_end_rod_y = end_y * _scaling_y + _shift_y;


		memDC.MoveTo(screen_beginning_rod_x, screen_beginning_rod_y);
		memDC.LineTo(screen_end_rod_x, screen_end_rod_y);

		//Орисока шарика
		//Радиус стержня, в экранных координатах
		double rod_radius = sqrt(
			(screen_end_rod_x - screen_beginning_rod_x) * (screen_end_rod_x - screen_beginning_rod_x) +
			(screen_end_rod_y - screen_beginning_rod_y) * (screen_end_rod_y - screen_beginning_rod_y)
		);

		//Радиус шара, в экранных координатах
		double ball_radius = rod_radius * 0.05; //Радиус шара -> 5% от длинны стержня
		
		CBrush brush(HS_BDIAGONAL, RGB(106, 90, 205));
		memDC.SelectObject(&rod_pen);
		memDC.Ellipse(
			screen_end_rod_x - ball_radius,
			screen_end_rod_y - ball_radius,
			screen_end_rod_x + ball_radius,
			screen_end_rod_y + ball_radius
			);


		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
	}

	void Clean() {
		memDC.FillSolidRect(frame, RGB(255, 255, 255));
		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
	}

	vector<double> convert_range(vector <double>& data, double outmax, double outmin, double inmax, double inmin)
	{
		vector<double> output = data;
		double k = (outmax - outmin) / (inmax - inmin);
		for (auto& item : output)
		{
			item = (item - inmin) * k + outmin;
		}

		return output;
	}

	vector<double> convert_range_x(vector <double>& data) {
		vector<double> output;
		for (int i = 0; i < data.size(); i++)output.push_back(data[i] * _scaling_x + _shift_x);
		return output;
	}

	vector<double> convert_range_y(vector <double>& data) {
		vector<double> output;
		for (int i = 0; i < data.size(); i++)output.push_back(data[i] * _scaling_y + _shift_y);
		return output;
	}
};

class Drawer2
{
	// Прямоугольник области рисования.
	CRect frame;
	// Указатель на объект окна, области рисования.
	CWnd* wnd;
	// Контекст рисования, привязанный к области рисования.
	CDC* dc;
	// Контекст рисования, привязанный к памяти.
	CDC memDC;
	// Память для контекста рисования memDC.
	CBitmap bmp;
	// Флаг для отслеживания состояния инициализации класса.
	bool init;
public:
	// Проинициализировать объект класса на основе HWND.
	void Create(HWND hWnd)
	{
		// Получаем указатель на окно.
		wnd = CWnd::FromHandle(hWnd);
		// Получаем прямоугольник окна.
		wnd->GetClientRect(frame);
		// Получаем контекст для рисования в этом окне.
		dc = wnd->GetDC();

		// Создаем буфер-контекст.
		memDC.CreateCompatibleDC(dc);
		// Создаем растр для контекста рисования.
		bmp.CreateCompatibleBitmap(dc, frame.Width(), frame.Height());
		// Выбираем растр для использования буфер-контекстом.
		memDC.SelectObject(&bmp);
		init = true;
	}

	// Нарисовать график по переданным данным.
	void Draw(	vector<double>& data, double min_data, double max_data,
				vector<double>& keys, double min_keys, double max_keys,
				char color,
				vector<double>& data2,
				vector<double>& keys2,
				char color2
	)
	{
		if (!init) return;

		CPen subgrid_pen(PS_DOT, 1, RGB(200, 200, 200));
		CPen grid_pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen data_pen(PS_SOLID, 2, RGB(255, 0, 0));
		CPen data_pen2(PS_SOLID, 2, RGB(38, 0, 255));
		CPen pen_red(PS_SOLID, 2, RGB(178, 34, 34));
		CPen pen_green(PS_SOLID, 2, RGB(0, 128, 0));
		CFont font;
		font.CreateFontW(18, 0, 0, 0,
			FW_DONTCARE,
			FALSE,				// Курсив
			FALSE,				// Подчеркнутый
			FALSE,				// Перечеркнутый
			DEFAULT_CHARSET,	// Набор символов
			OUT_OUTLINE_PRECIS,	// Точность соответствия.	
			CLIP_DEFAULT_PRECIS,//  
			CLEARTYPE_QUALITY,	// Качество
			VARIABLE_PITCH,		//
			TEXT("Times New Roman")		//
		);

		int padding = 20;
		int left_keys_padding = 20;
		int bottom_keys_padding = 10;

		int actual_width = frame.Width() - 2 * padding - left_keys_padding;
		int actual_height = frame.Height() - 2 * padding - bottom_keys_padding;

		int actual_top = padding;
		int actual_bottom = actual_top + actual_height;
		int actual_left = padding + left_keys_padding;
		int actual_right = actual_left + actual_width;

		// Белый фон.
		memDC.FillSolidRect(frame, RGB(255, 255, 255));

		// Рисуем сетку и подсетку.
		unsigned int grid_size = 10;

		memDC.SelectObject(&subgrid_pen);

		for (double i = 0.5; i < grid_size; i += 1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}

		memDC.SelectObject(&grid_pen);

		for (double i = 0.0; i < grid_size + 1; i += 1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}

		// Рисуем график.
		if (data.empty()) return;

		if (keys.size() != data.size())
		{
			keys.resize(data.size());
			for (int i = 0; i < keys.size(); i++)
			{
				keys[i] = i;
			}
		}

		/*РИСУЕМ ПЕРВЫЙ ГРАФИК*/
		if (color == 'R')memDC.SelectObject(&pen_red);
		else if (color == 'G')memDC.SelectObject(&pen_green);
		else memDC.SelectObject(&data_pen);

		double data_y_max(max_data), data_y_min(min_data);
		double data_x_max(max_keys), data_x_min(min_keys);

		vector<double> y = convert_range(data, actual_top, actual_bottom, data_y_max, data_y_min);
		vector<double> x = convert_range(keys, actual_right, actual_left, data_x_max, data_x_min);

		memDC.MoveTo(x[0], y[0]);
		for (unsigned int i = 0; i < y.size(); i++)
		{
			memDC.LineTo(x[i], y[i]);
		}
		/*РИСУЕМ ВТОРОЙ ГРАФИК*/
		if (color2 == 'R')memDC.SelectObject(&pen_red);
		else if (color2 == 'G')memDC.SelectObject(&pen_green);
		else memDC.SelectObject(&data_pen);

		y = convert_range(data2, actual_top, actual_bottom, data_y_max, data_y_min);
		x = convert_range(keys2, actual_right, actual_left, data_x_max, data_x_min);

		memDC.MoveTo(x[0], y[0]);
		for (unsigned int i = 0; i < y.size(); i++)
		{
			memDC.LineTo(x[i], y[i]);
		}
		/**/

		memDC.SelectObject(&font);
		memDC.SetTextColor(RGB(0, 0, 0));
		for (int i = 0; i < grid_size / 2 + 1; i++)
		{
			CString str;
			str.Format(L"%.1f", data_x_min + i * (data_x_max - data_x_min) / (grid_size / 2));
			memDC.TextOutW(actual_left + (double)i * actual_width / (grid_size / 2) - bottom_keys_padding, actual_bottom + bottom_keys_padding / 2, str);

			str.Format(L"%.1f", data_y_min + i * (data_y_max - data_y_min) / (grid_size / 2));
			memDC.TextOutW(actual_left - 1.5 * left_keys_padding, actual_bottom - (double)i * actual_height / (grid_size / 2) - bottom_keys_padding, str);
		}

		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
	}

	vector<double> convert_range(vector <double>& data, double outmax, double outmin, double inmax, double inmin)
	{
		vector<double> output = data;
		double k = (outmax - outmin) / (inmax - inmin);
		for (auto& item : output)
		{
			item = (item - inmin) * k + outmin;
		}

		return output;
	}
};

class DrawerVector
{
	// Прямоугольник области рисования.
	CRect frame;
	// Указатель на объект окна, области рисования.
	CWnd* wnd;
	// Контекст рисования, привязанный к области рисования.
	CDC* dc;
	// Контекст рисования, привязанный к памяти.
	CDC memDC;
	// Контекст рисования, для сохранения осей.
	CDC memDC_axis;
	// Память для контекста рисования memDC.
	CBitmap bmp;
	// Флаг для отслеживания состояния инициализации класса.
	bool init, init_data, init_axis;

	double _data_x_max, _data_x_min, _data_width;
	double _data_y_max, _data_y_min, _data_height;

	double _screen_x_max, _screen_x_min, _screen_width;
	double _screen_y_max, _screen_y_min, _screen_height;

	double _scaling_x, _scaling_y;
	double _shift_x, _shift_y;

	//отступ от края
	double _indent_x, _indent_y;

	//Название осей
	CString nameX, nameY;

	//Карандаши
	vector<MyRGB> dataPen;
public:
	// Проинициализировать объект класса на основе HWND.
	void Create(HWND hWnd)
	{
		// Получаем указатель на окно.
		wnd = CWnd::FromHandle(hWnd);
		// Получаем прямоугольник окна.
		wnd->GetClientRect(frame);
		// Получаем контекст для рисования в этом окне.
		dc = wnd->GetDC();

		// Создаем буфер-контекст.
		memDC.CreateCompatibleDC(dc);
		memDC_axis.CreateCompatibleDC(dc);
		// Создаем растр для контекста рисования.
		bmp.CreateCompatibleBitmap(dc, frame.Width(), frame.Height());
		// Выбираем растр для использования буфер-контекстом.
		memDC.SelectObject(&bmp);
		memDC_axis.SelectObject(&bmp);
		init = true;
		init_axis = false;
	}

	void SetDataCoordinate(
		double data_x_max, double data_x_min,
		double data_y_max, double data_y_min) {

		_data_x_max = data_x_max;
		_data_x_min = data_x_min;
		_data_width = data_x_max - data_x_min;
		_data_y_max = data_y_max;
		_data_y_min = data_y_min;
		_data_height = data_y_max - data_y_min;

		_indent_x = frame.Width() * 0.05;

		_screen_x_max = frame.Width() - _indent_x;
		_screen_x_min = _indent_x;
		_screen_width = _screen_x_max - _screen_x_min;

		_indent_y = frame.Height() * 0.05;

		_screen_y_max = frame.Height() - _indent_y;
		_screen_y_min = _indent_y;
		_screen_height = _screen_y_max - _screen_y_min;

		_scaling_x = _screen_width / _data_width;
		_scaling_y = -(_screen_height / _data_height);

		_shift_x = _screen_width / 2 + _indent_x;
		_shift_y = _screen_height / 2 + _indent_y;

		init_data = true;
		init_axis = false;
	}

	// Нарисовать график по переданным данным.
	void Draw(vector<vector<state_system>>& data, CString nameX = L"X", CString nameY = L"Y")
	{
		if (!init && !init_data) return;

		CPen subgrid_pen(PS_DOT, 1, RGB(200, 200, 200));
		CPen Xgrid_pen(PS_SOLID, 2, RGB(128, 0, 0));
		CPen Ygrid_pen(PS_SOLID, 2, RGB(0, 128, 0));
		CPen grid_pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen data_pen(PS_SOLID, 2, RGB(255, 0, 0));
		CPen data_pen2(PS_SOLID, 2, RGB(38, 0, 255));
		CPen data_blue(PS_SOLID, 2, RGB(106, 90, 205));
		CPen pen_red(PS_SOLID, 2, RGB(178, 34, 34));
		CPen pen_green(PS_SOLID, 2, RGB(0, 128, 0));
		CFont font;
		font.CreateFontW(18, 0, 0, 0,
			FW_DONTCARE,
			FALSE,				// Курсив
			FALSE,				// Подчеркнутый
			FALSE,				// Перечеркнутый
			DEFAULT_CHARSET,	// Набор символов
			OUT_OUTLINE_PRECIS,	// Точность соответствия.	
			CLIP_DEFAULT_PRECIS,//  
			CLEARTYPE_QUALITY,	// Качество
			VARIABLE_PITCH,		//
			TEXT("Times New Roman")		//
		);

		if (!init_axis) {
			// Белый фон.
			memDC.FillSolidRect(frame, RGB(255, 255, 255));

			// Рисуем сетку и подсетку.
			unsigned int grid_size = 10;

			memDC.SelectObject(&subgrid_pen);

			for (double i = 0.5; i < grid_size; i += 1.0)
			{
				memDC.MoveTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_min);
				memDC.LineTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_max);
				memDC.MoveTo(_screen_x_min, _screen_y_min + i * _screen_height / grid_size);
				memDC.LineTo(_screen_x_max, _screen_y_min + i * _screen_height / grid_size);
			}



			for (double i = 0.0; i < grid_size + 1; i += 1.0)
			{
				memDC.SelectObject(&grid_pen);
				if (i == grid_size / 2) memDC.SelectObject(&Ygrid_pen);
				memDC.MoveTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_min);
				memDC.LineTo(_screen_x_min + i * _screen_width / grid_size, _screen_y_max);
				if (i == grid_size / 2) memDC.SelectObject(&Xgrid_pen);
				memDC.MoveTo(_screen_x_min, _screen_y_min + i * _screen_height / grid_size);
				memDC.LineTo(_screen_x_max, _screen_y_min + i * _screen_height / grid_size);
			}

			//Отрисовка цифр координат
			memDC.SelectObject(&font);
			memDC.SetTextColor(RGB(0, 0, 0));
			//SetTextAlign(memDC,);
			for (int i = 0; i < grid_size / 2 + 1; i++)
			{
				CString str;
				str.Format(L"%.1f", _data_x_min + i * (_data_x_max - _data_x_min) / (grid_size / 2));
				memDC.TextOutW(_screen_x_min + (double)i * _screen_width / (grid_size / 2) - _indent_y, _screen_y_min + _screen_height / 2, str);

				str.Format(L"%.1f", _data_y_min + i * (_data_y_max - _data_y_min) / (grid_size / 2));
				memDC.TextOutW(_screen_x_min + _screen_width / 2, _screen_y_max - (double)i * _screen_height / (grid_size / 2) - _indent_y, str);
			}
			//Название оси
			memDC.SetTextColor(RGB(128, 0, 0));
			memDC.TextOutW(_screen_x_max + _indent_x / 3, _screen_y_min + _screen_height / 2, nameX);
			memDC.SetTextColor(RGB(0, 128, 0));
			memDC.TextOutW(_screen_x_min + _screen_width / 2 - 20, 0, nameY);

			//Сохранение в буфер
			memDC_axis.BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);

			for (int trajectory_number = 0; trajectory_number < data.size(); trajectory_number++) {
				MyRGB trajectory_number_pen = { rand() % 255, rand() % 255, rand() % 255 };
				dataPen.push_back(trajectory_number_pen);
			}
		}
		else {
			memDC.BitBlt(0, 0, frame.Width(), frame.Height(), &memDC_axis, 0, 0, SRCCOPY);
		}

		// Рисуем график.
		if (data.empty()) return;

		for (int trajectory_number = 0; trajectory_number < data.size(); trajectory_number++) {
			//Генерируем цвет
			CPen trajectory_number_pen(PS_SOLID, 2, RGB(
				dataPen[trajectory_number].R,
				dataPen[trajectory_number].G,
				dataPen[trajectory_number].B));
			memDC.SelectObject(&trajectory_number_pen);



			vector<double> y = convert_range_y(getvectorV(data, trajectory_number));
			vector<double> x = convert_range_x(getvectorX(data, trajectory_number));

			memDC.MoveTo(x[0], y[0]);
			for (unsigned int i = 0; i < y.size(); i++)
			{
				memDC.LineTo(x[i], y[i]);
			}
		}


		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
	}
	vector<double> getvectorX(vector<vector<state_system>>& data, int trajectory_number) {
		vector<double>x;
		for (int i = 0; i < data[trajectory_number].size(); i++) {
			x.push_back(data[trajectory_number][i].x);
		}
		return x;
	}

	vector<double> getvectorV(vector<vector<state_system>>& data, int trajectory_number) {
		vector<double>v;
		for (int i = 0; i < data[trajectory_number].size(); i++) {
			v.push_back(data[trajectory_number][i].v);
		}
		return v;
	}

	vector<double> convert_range(vector <double>& data, double outmax, double outmin, double inmax, double inmin)
	{
		vector<double> output = data;
		double k = (outmax - outmin) / (inmax - inmin);
		for (auto& item : output)
		{
			item = (item - inmin) * k + outmin;
		}

		return output;
	}

	vector<double> convert_range_x(vector <double>& data) {
		vector<double> output;
		for (int i = 0; i < data.size(); i++)output.push_back(data[i] * _scaling_x + _shift_x);
		return output;
	}

	vector<double> convert_range_y(vector <double>& data) {
		vector<double> output;
		for (int i = 0; i < data.size(); i++)output.push_back(data[i] * _scaling_y + _shift_y);
		return output;
	}


};