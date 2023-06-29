
// GraphTP1Dlg.h: файл заголовка
//

#pragma once
#include <gdiplus.h>
#include "Drawer.h"

// Диалоговое окно CGraphTP1Dlg
class CGraphTP1Dlg : public CDialogEx
{
// Создание
public:
	CGraphTP1Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPHTP1_DIALOG };
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

	DRAWITEMSTRUCT drawStruct;
	DRAWITEMSTRUCT drawStructOnClick;
	Drawer drawer;


	CSliderCtrl AngleCtrl;

	afx_msg void OnStnClickedStaticdraw();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
