
// GraphTP2Dlg.h: файл заголовка
//

#pragma once
#include <vector>
#include <gdiplus.h>
#include <algorithm>
#include "Graph.h"



// Диалоговое окно CGraphTP2Dlg
class CGraphTP2Dlg : public CDialogEx
{
// Создание
public:
	CGraphTP2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPHTP2_DIALOG };
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
	Graph graph;
	afx_msg void OnBnClickedCheck1();
	CButton AnimateCtrl;

	CWinThread animateThread;

	static UINT AnimateThreadFunc(LPVOID pv);
	virtual void OnOK();
};
