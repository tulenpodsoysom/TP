// MFCApplet.h: ������� ���� ��������� ��� DLL MFCApplet
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include <Cpl.h>
#include "resource.h"		// �������� �������
#include "AppletDialog.h"


// CMFCAppletApp
// ��� ���������� ������� ������ ��. MFCApplet.cpp
//

//DWORD count = 0;
LONG WINAPI CPlApplet(HWND hwnd, UINT msg, LPARAM param1, LPARAM param2);

class CMFCAppletApp : public CWinApp
{
public:
	CMFCAppletApp();

// ���������������
public:
	virtual BOOL InitInstance();

	//CAppletDialog dialog;

	DECLARE_MESSAGE_MAP()
};
