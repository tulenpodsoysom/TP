
// GraphTP1Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "GraphTP1.h"
#include "GraphTP1Dlg.h"
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


// Диалоговое окно CGraphTP1Dlg



CGraphTP1Dlg::CGraphTP1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAPHTP1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGraphTP1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICDRAW, drawer);
	DDX_Control(pDX, IDC_SLIDER3, AngleCtrl);
}

BEGIN_MESSAGE_MAP(CGraphTP1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_STN_CLICKED(IDC_STATICDRAW, &CGraphTP1Dlg::OnStnClickedStaticdraw)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Обработчики сообщений CGraphTP1Dlg

BOOL CGraphTP1Dlg::OnInitDialog()
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

	
	drawStruct = {};

	drawStruct.CtlType = ODT_STATIC;
	drawStruct.CtlID = IDC_STATICDRAW;
	drawStruct.hwndItem = drawer.GetSafeHwnd();
	drawStruct.hDC = drawer.GetDC()->GetSafeHdc();
	drawStruct.itemAction = ODA_DRAWENTIRE;
	drawStruct.itemState = ODS_DEFAULT;
	drawStruct.itemID = -1;

	drawStruct.itemData = (ULONG_PTR)this;
	GetDlgItem(IDC_STATICDRAW)->GetClientRect(&drawStruct.rcItem);


	drawStructOnClick = { drawStruct };
	drawStructOnClick.itemState |= ODS_SELECTED;


	AngleCtrl.SetRange(-180, 180,1);
	AngleCtrl.SetPos(0);
	//AngleCtrl.ShowWindow(1);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CGraphTP1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGraphTP1Dlg::OnPaint()
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
	//drawer.DrawItem(&drawStruct);
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CGraphTP1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGraphTP1Dlg::OnStnClickedStaticdraw()
{
	// TODO: добавьте свой код обработчика уведомлений
	AngleCtrl.SetPos(0);
	drawer.angle = 0;
	drawer.DrawItem(&drawStructOnClick);
}


void CGraphTP1Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	drawer.angle = AngleCtrl.GetPos();
	drawer.DrawItem(&drawStruct);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
