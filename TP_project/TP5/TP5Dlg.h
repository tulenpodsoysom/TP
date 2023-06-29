
// TP5Dlg.h : ���� ���������
//

#pragma once

#include <Cpl.h>
#include "afxwin.h"


// ���������� ���� CTP5Dlg
class CTP5Dlg : public CDialogEx
{
// ��������
public:
	CTP5Dlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_TP5_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CString filepath;

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1();
	CEdit filePathControl;
	afx_msg void OnBnClickedButton3();
	CEdit name;
	CEdit description;
	CStatic cplIcon;

	HINSTANCE lib;
	APPLET_PROC func;
};
