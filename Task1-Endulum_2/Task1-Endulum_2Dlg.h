#pragma once
#include "Drawer.h"
#include "RungeKutta_method.h"
#include "RungeKutta_method_extended.h"

// Диалоговое окно CTask1Endulum2Dlg
class CTask1Endulum2Dlg : public CDialogEx
{
// Создание
public:
	Drawer painterPendulum;					//1p) Определить объект отрисовщика
	Drawer painterTrajectory;
	DrawerVector painterPortrait;
	RungeKutta_method myRungeKutta;
	CTask1Endulum2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

	void startAnimationFlow();
	void finishAnimationFlow();

	void startAnimationFlowPortrait();
	void finishAnimationFlowPortrait();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASK1ENDULUM_2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	int aaaa;
	CEdit AAAA;
	double input_L;
	double input_K;
	double input_C;
	double input_input_V0;
	double input_stepT;
	double input_Fi0;
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit5();
	double input_delayFrame;
	afx_msg void OnEnChangeEdit8();
	double inputFP_L0;
	double inputFP_L_end;
	double inputFP_L_step;
	double inputFP_K_start;
	double inputFP_K_end;
	double inputFP_K_step;
	double inputFP_C_start;
	double inputFP_C_end;
	double inputFP_C_step;
	int inputFP_delay;
	double inputFP_V0_start;
	double inputFP_V0_end;
	double inputFP_V0_step;
	double inputFP_Fi0_start;
	double inputFP_Fi0_end;
	double inputFP_Fi0_step;
	double inputFP_TimeStep;
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit17();
	afx_msg void OnEnChangeEdit18();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit19();
	afx_msg void OnEnChangeEdit20();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnEnChangeEdit21();
	afx_msg void OnEnChangeEdit22();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnEnChangeEdit23();
	afx_msg void OnEnChangeEdit24();
	afx_msg void OnEnChangeEdit14();
	afx_msg void OnEnChangeEdit25();
	afx_msg void OnEnChangeEdit26();
	afx_msg void OnEnChangeEdit15();

	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();

	void portrait_adjustment(bool off);
	void portrait_trajectoryt(bool off);
	void choiceParameterResearched(char val);
	afx_msg void OnBnClickedButton2();
};
