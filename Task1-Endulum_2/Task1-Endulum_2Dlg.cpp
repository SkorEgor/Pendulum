
// Task1-Endulum_2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Task1-Endulum_2.h"
#include "Task1-Endulum_2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//-----------------СТАНДАРТНЫЕ ФУНКЦИИ/МЕТОДЫ СГЕНЕРИРОВАННЫЕ MFC------------------//

// Диалоговое окно CAboutDlg используется для описания сведений о приложении
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Диалоговое окно CTask1Endulum2Dlg
CTask1Endulum2Dlg::CTask1Endulum2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TASK1ENDULUM_2_DIALOG, pParent)
	, aaaa(0)
	, input_L(5)
	, input_K(0.2)
	, input_C(0.3)
	, input_input_V0(0)
	, input_stepT(0.01)
	, input_Fi0(2)
	, input_delayFrame(16)

	, inputFP_L0(5)
	, inputFP_L_end(10)
	, inputFP_L_step(2.5)

	, inputFP_K_start(0.2)
	, inputFP_K_end(1)
	, inputFP_K_step(0.2)

	, inputFP_C_start(0.3)
	, inputFP_C_end(0.9)
	, inputFP_C_step(0.3)

	, inputFP_delay(0)

	, inputFP_V0_start(0)
	, inputFP_V0_end(0.9)
	, inputFP_V0_step(0.3)

	, inputFP_Fi0_start(1.5)
	, inputFP_Fi0_end(3)
	, inputFP_Fi0_step(0.5)

	, inputFP_TimeStep(0.01)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTask1Endulum2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, aaaa);
	DDX_Control(pDX, IDC_EDIT1, AAAA);
	DDX_Text(pDX, IDC_EDIT2, input_L);
	DDX_Text(pDX, IDC_EDIT3, input_K);
	DDX_Text(pDX, IDC_EDIT4, input_C);
	DDX_Text(pDX, IDC_EDIT6, input_input_V0);
	DDX_Text(pDX, IDC_EDIT7, input_stepT);
	DDX_Text(pDX, IDC_EDIT5, input_Fi0);
	DDX_Text(pDX, IDC_EDIT8, input_delayFrame);
	DDX_Text(pDX, IDC_EDIT10, inputFP_L0);
	DDX_Text(pDX, IDC_EDIT17, inputFP_L_end);
	DDX_Text(pDX, IDC_EDIT18, inputFP_L_step);
	DDX_Text(pDX, IDC_EDIT11, inputFP_K_start);
	DDX_Text(pDX, IDC_EDIT19, inputFP_K_end);
	DDX_Text(pDX, IDC_EDIT20, inputFP_K_step);
	DDX_Text(pDX, IDC_EDIT12, inputFP_C_start);
	DDX_Text(pDX, IDC_EDIT22, inputFP_C_end);
	DDX_Text(pDX, IDC_EDIT16, inputFP_delay);
	DDX_Text(pDX, IDC_EDIT13, inputFP_V0_start);
	DDX_Text(pDX, IDC_EDIT23, inputFP_V0_end);
	DDX_Text(pDX, IDC_EDIT24, inputFP_V0_step);
	DDX_Text(pDX, IDC_EDIT14, inputFP_Fi0_start);
	DDX_Text(pDX, IDC_EDIT25, inputFP_Fi0_end);
	DDX_Text(pDX, IDC_EDIT26, inputFP_Fi0_step);
	DDX_Text(pDX, IDC_EDIT15, inputFP_TimeStep);
	DDX_Text(pDX, IDC_EDIT21, inputFP_C_step);
}

BEGIN_MESSAGE_MAP(CTask1Endulum2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTask1Endulum2Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CTask1Endulum2Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CTask1Endulum2Dlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CTask1Endulum2Dlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT6, &CTask1Endulum2Dlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CTask1Endulum2Dlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT5, &CTask1Endulum2Dlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT8, &CTask1Endulum2Dlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT10, &CTask1Endulum2Dlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT17, &CTask1Endulum2Dlg::OnEnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, &CTask1Endulum2Dlg::OnEnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT11, &CTask1Endulum2Dlg::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT19, &CTask1Endulum2Dlg::OnEnChangeEdit19)
	ON_EN_CHANGE(IDC_EDIT20, &CTask1Endulum2Dlg::OnEnChangeEdit20)
	ON_EN_CHANGE(IDC_EDIT12, &CTask1Endulum2Dlg::OnEnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT21, &CTask1Endulum2Dlg::OnEnChangeEdit21)
	ON_EN_CHANGE(IDC_EDIT22, &CTask1Endulum2Dlg::OnEnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT16, &CTask1Endulum2Dlg::OnEnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT13, &CTask1Endulum2Dlg::OnEnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT23, &CTask1Endulum2Dlg::OnEnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT24, &CTask1Endulum2Dlg::OnEnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT14, &CTask1Endulum2Dlg::OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT25, &CTask1Endulum2Dlg::OnEnChangeEdit25)
	ON_EN_CHANGE(IDC_EDIT26, &CTask1Endulum2Dlg::OnEnChangeEdit26)
	ON_EN_CHANGE(IDC_EDIT15, &CTask1Endulum2Dlg::OnEnChangeEdit15)
	ON_BN_CLICKED(IDC_RADIO1, &CTask1Endulum2Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CTask1Endulum2Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CTask1Endulum2Dlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CTask1Endulum2Dlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CTask1Endulum2Dlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON2, &CTask1Endulum2Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Обработчики сообщений CTask1Endulum2Dlg
BOOL CTask1Endulum2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// Добавление пункта "О программе..." в системное меню.
	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	painterPendulum.Create(GetDlgItem(IDC_PENDULUM_CONTROL)->GetSafeHwnd());
	painterTrajectory.Create(GetDlgItem(IDC_TRAJECTORY_CONTROL)->GetSafeHwnd());
	painterPortrait.Create(GetDlgItem(IDC_TRAJECTORY_CONTROL)->GetSafeHwnd());

	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(TRUE);
	OnBnClickedRadio5();
	


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CTask1Endulum2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CTask1Endulum2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CTask1Endulum2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//-------------КОНЕЦ СТАНДАРТНЫХ ФУНКЦИЙ/МЕТОДОВ СГЕНЕРИРОВАННЫХ MFC---------------//

void CTask1Endulum2Dlg::portrait_adjustment(bool off) {
	GetDlgItem(IDC_EDIT10)->EnableWindow(off);
	GetDlgItem(IDC_EDIT11)->EnableWindow(off);
	GetDlgItem(IDC_EDIT12)->EnableWindow(off);
	GetDlgItem(IDC_EDIT13)->EnableWindow(off);
	GetDlgItem(IDC_EDIT14)->EnableWindow(off);
	GetDlgItem(IDC_EDIT15)->EnableWindow(off);
	GetDlgItem(IDC_EDIT16)->EnableWindow(off);
	GetDlgItem(IDC_EDIT17)->EnableWindow(off);
	GetDlgItem(IDC_EDIT18)->EnableWindow(off);
	GetDlgItem(IDC_EDIT19)->EnableWindow(off);
	GetDlgItem(IDC_EDIT20)->EnableWindow(off);
	GetDlgItem(IDC_EDIT21)->EnableWindow(off);
	GetDlgItem(IDC_EDIT22)->EnableWindow(off);
	GetDlgItem(IDC_EDIT23)->EnableWindow(off);
	GetDlgItem(IDC_EDIT24)->EnableWindow(off);
	GetDlgItem(IDC_EDIT25)->EnableWindow(off);
	GetDlgItem(IDC_EDIT26)->EnableWindow(off);

	GetDlgItem(IDC_RADIO1)->EnableWindow(off);
	GetDlgItem(IDC_RADIO2)->EnableWindow(off);
	GetDlgItem(IDC_RADIO3)->EnableWindow(off);
	GetDlgItem(IDC_RADIO4)->EnableWindow(off);
	GetDlgItem(IDC_RADIO5)->EnableWindow(off);

	GetDlgItem(IDC_BUTTON2)->EnableWindow(off);
}

void CTask1Endulum2Dlg::portrait_trajectoryt(bool off) {
	GetDlgItem(IDC_EDIT2)->EnableWindow(off);
	GetDlgItem(IDC_EDIT3)->EnableWindow(off);
	GetDlgItem(IDC_EDIT4)->EnableWindow(off);
	GetDlgItem(IDC_EDIT5)->EnableWindow(off);
	GetDlgItem(IDC_EDIT6)->EnableWindow(off);
	GetDlgItem(IDC_EDIT7)->EnableWindow(off);
	GetDlgItem(IDC_EDIT8)->EnableWindow(off);

	GetDlgItem(IDC_BUTTON1)->EnableWindow(off);
}

void CTask1Endulum2Dlg::choiceParameterResearched(char val) {
	//l
	GetDlgItem(IDC_EDIT10)->EnableWindow(true);
	GetDlgItem(IDC_EDIT17)->EnableWindow(val == 'l');
	GetDlgItem(IDC_EDIT18)->EnableWindow(val == 'l');

	//k
	GetDlgItem(IDC_EDIT11)->EnableWindow(true);
	GetDlgItem(IDC_EDIT19)->EnableWindow(val == 'k');
	GetDlgItem(IDC_EDIT20)->EnableWindow(val == 'k');

	//c
	GetDlgItem(IDC_EDIT12)->EnableWindow(true);
	GetDlgItem(IDC_EDIT22)->EnableWindow(val == 'c');
	GetDlgItem(IDC_EDIT21)->EnableWindow(val == 'c');

	//V0
	GetDlgItem(IDC_EDIT13)->EnableWindow(true);
	GetDlgItem(IDC_EDIT23)->EnableWindow(val == 'v');
	GetDlgItem(IDC_EDIT24)->EnableWindow(val == 'v');

	//fi0
	GetDlgItem(IDC_EDIT14)->EnableWindow(true);
	GetDlgItem(IDC_EDIT25)->EnableWindow(val == 'f');
	GetDlgItem(IDC_EDIT26)->EnableWindow(val == 'f');

	GetDlgItem(IDC_EDIT16)->EnableWindow(true);
	GetDlgItem(IDC_EDIT15)->EnableWindow(true);

	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);

	GetDlgItem(IDC_RADIO1)->EnableWindow(true);
	GetDlgItem(IDC_RADIO2)->EnableWindow(true);
	GetDlgItem(IDC_RADIO3)->EnableWindow(true);
	GetDlgItem(IDC_RADIO4)->EnableWindow(true);
	GetDlgItem(IDC_RADIO5)->EnableWindow(true);
}

void CTask1Endulum2Dlg::OnBnClickedButton1()
{
	startAnimationFlow();

	
}

//Элементы маятника и фаз траектории
void CTask1Endulum2Dlg::OnEnChangeEdit2() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit3() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit4() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit6() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit7() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit5() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit8() { UpdateData(TRUE); }

//Эелементы фазового портрета
void CTask1Endulum2Dlg::OnEnChangeEdit10() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit17() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit18() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit11() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit19() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit20() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit12() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit21() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit22() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit16() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit13() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit23() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit24() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit14() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit25() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit26() { UpdateData(TRUE); }
void CTask1Endulum2Dlg::OnEnChangeEdit15() { UpdateData(TRUE); }

void CTask1Endulum2Dlg::OnBnClickedRadio1() { choiceParameterResearched('l'); }
void CTask1Endulum2Dlg::OnBnClickedRadio2() { choiceParameterResearched('k'); }
void CTask1Endulum2Dlg::OnBnClickedRadio3() { choiceParameterResearched('c'); }
void CTask1Endulum2Dlg::OnBnClickedRadio4() { choiceParameterResearched('v'); }
void CTask1Endulum2Dlg::OnBnClickedRadio5() { choiceParameterResearched('f'); }

void CTask1Endulum2Dlg::OnBnClickedButton2()
{
	startAnimationFlowPortrait();
	//UpdateData(FALSE);
}
