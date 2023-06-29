
// GraphTP2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "GraphTP2.h"
#include "GraphTP2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CGraphTP2Dlg



CGraphTP2Dlg::CGraphTP2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAPHTP2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGraphTP2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICGRAPH, graph);
	DDX_Control(pDX, IDC_CHECK1, AnimateCtrl);
}

BEGIN_MESSAGE_MAP(CGraphTP2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGraphTP2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CGraphTP2Dlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// Обработчики сообщений CGraphTP2Dlg

BOOL CGraphTP2Dlg::OnInitDialog()
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

	animateThread.m_pfnThreadProc = AnimateThreadFunc;
	animateThread.m_pThreadParams = this;
	animateThread.CreateThread(CREATE_SUSPENDED);

	Gdiplus::RectF worldRect = { 0,-2,2,4 };
	graph.captionX = L"t,с";
	graph.captionY = L"x";
	graph.title = L"Биение колебаний со сдвигом по фазе";
	graph.worldRect = worldRect;

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CGraphTP2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CGraphTP2Dlg::OnPaint()
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
HCURSOR CGraphTP2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGraphTP2Dlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	double w1, dw; static double phase = 0;
	if (!AnimateCtrl.GetCheck()) phase = 0;

	CString buffer;
	GetDlgItemText(IDC_EDIT1, buffer); w1 = wcstof(buffer, NULL);
	GetDlgItemText(IDC_EDIT2, buffer); dw = wcstof(buffer, NULL);



	const double PI = 3.1415926535;
	double fd = 512;
	std::vector<double> signal(1024);
	for (size_t i = 0; i < 1024; i++)
	{
		signal[i] = sin(2 * PI * w1 * i / fd) + sin(2 * PI * (w1 - dw) * i / fd + phase);
	}

	//std::generate(signal.begin(), signal.end(), [&, n = 0]() mutable {return sin(2 * PI * w1 * n / fd) + sin(2 * PI * (w1 - dw) * n++ / fd + phase); });
	
	Gdiplus::RectF worldRect = { 0,-2,2,4 };

	graph.SetPoints({ signal });

	DRAWITEMSTRUCT drawStruct = {};

	drawStruct.CtlType = ODT_STATIC;
	drawStruct.CtlID = IDC_STATICGRAPH;
	drawStruct.hwndItem = graph.GetSafeHwnd();
	drawStruct.hDC = graph.GetDC()->GetSafeHdc();
	drawStruct.itemAction = ODA_DRAWENTIRE;
	drawStruct.itemState = ODS_DEFAULT;
	drawStruct.itemID = -1;
	GetDlgItem(IDC_STATICGRAPH)->GetClientRect(&drawStruct.rcItem);

	graph.DrawItem(&drawStruct);

	ReleaseDC(CDC::FromHandle(drawStruct.hDC));

	if (AnimateCtrl.GetCheck()) {
		phase += 0.1; phase = fmod(phase, 2 * 3.1415);
	}
}

UINT CGraphTP2Dlg::AnimateThreadFunc(LPVOID pv)
{
	auto p = (CGraphTP2Dlg*)pv;

	while (true)
	{
		p->OnBnClickedButton1();
		Sleep(1000 / 30);
	}
	return 0;
}

void CGraphTP2Dlg::OnBnClickedCheck1()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (AnimateCtrl.GetCheck())
	{
		animateThread.ResumeThread();

		GetDlgItem(IDC_EDIT1)->EnableWindow(0);
		GetDlgItem(IDC_EDIT2)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(0);
	}
	else
	{
		animateThread.SuspendThread();

		GetDlgItem(IDC_EDIT1)->EnableWindow(1);
		GetDlgItem(IDC_EDIT2)->EnableWindow(1);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(1);
	}
}


void CGraphTP2Dlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса

	//CDialogEx::OnOK();
}
