
// TP5Dlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "TP5.h"
#include "TP5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ������ ����������� ����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// ���������� ���� CTP5Dlg



CTP5Dlg::CTP5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTP5Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTP5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, filePathControl);
	DDX_Control(pDX, IDC_EDIT2, name);
	DDX_Control(pDX, IDC_EDIT3, description);
	DDX_Control(pDX, IDC_STATICICON, cplIcon);
}

BEGIN_MESSAGE_MAP(CTP5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTP5Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTP5Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTP5Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// ����������� ��������� CTP5Dlg

BOOL CTP5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���������� ������ "� ���������..." � ��������� ����.

	// IDM_ABOUTBOX ������ ���� � �������� ��������� �������.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

void CTP5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CTP5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CTP5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//typedef LONG WINAPI (*CPlApplet)(HWND, UINT, LPARAM, LPARAM);

void CTP5Dlg::OnBnClickedButton1()
{
	// TODO: �������� ���� ��� ����������� �����������

	CFileDialog filedialog(TRUE);
	filedialog.DoModal();
	filepath = filedialog.GetPathName();
	filePathControl.SetWindowTextW(filepath);

	if (lib != NULL) FreeLibrary(lib);
	lib = LoadLibrary(filepath);

	if (lib != NULL)
	{
		func = (APPLET_PROC)GetProcAddress(lib, "CPlApplet");
		if (!func)
		{
			FreeLibrary(lib);
		}
		else
		{
			CPLINFO cplinfo;

						func(NULL, CPL_INIT		, 0, 0);
			int count = func(NULL, CPL_GETCOUNT	, 0, 0);
						func(NULL, CPL_INQUIRE	, count - 1, (LPARAM)&cplinfo);
						//func(NULL, CPL_DBLCLK	, count - 1, (LPARAM)&(cplinfo.lData));

			WCHAR namestr[256];
			WCHAR infostr[256];
			LoadString(lib, cplinfo.idName, namestr, 256);
			LoadString(lib, cplinfo.idInfo, infostr, 256);
			HICON icon = LoadIcon(lib, MAKEINTRESOURCE(cplinfo.idIcon));

			this->name.SetWindowTextW(namestr);
			this->description.SetWindowTextW(infostr);

			cplIcon.SetIcon(icon);
			GetDlgItem(IDC_BUTTON3)->EnableWindow();
		}
	}
}


void CTP5Dlg::OnBnClickedButton2()
{
	// TODO: �������� ���� ��� ����������� �����������

	this->OnCancel();
}



void CTP5Dlg::OnBnClickedButton3()
{
	// TODO: �������� ���� ��� ����������� �����������
	CPLINFO cplinfo;
	int count = func(NULL, CPL_GETCOUNT, 0, 0);
	func(NULL, CPL_INQUIRE, count - 1, (LPARAM)&cplinfo);
	func(this->GetSafeHwnd(), CPL_DBLCLK	, count - 1, (LPARAM)&(cplinfo.lData));

}
