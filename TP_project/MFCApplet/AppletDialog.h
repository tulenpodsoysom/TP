#pragma once
#include "afxwin.h"


// диалоговое окно CAppletDialog

class CAppletDialog : public CDialog
{
	DECLARE_DYNAMIC(CAppletDialog)

public:
	CAppletDialog(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CAppletDialog();

// Данные диалогового окна
	enum { IDD = IDD_APPLETDIALOG };

	//SystemParametersInfo sysinfo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	//CStatic cplIcon;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
