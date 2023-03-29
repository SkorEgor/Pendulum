
// Task1-Endulum_2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CTask1Endulum2App:
// Сведения о реализации этого класса: Task1-Endulum_2.cpp
//

class CTask1Endulum2App : public CWinApp
{
public:
	CTask1Endulum2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CTask1Endulum2App theApp;
