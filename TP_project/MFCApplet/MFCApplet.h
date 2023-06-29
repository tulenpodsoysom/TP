// MFCApplet.h: главный файл заголовка для DLL MFCApplet
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include <Cpl.h>
#include "resource.h"		// основные символы
#include "AppletDialog.h"


// CMFCAppletApp
// Про реализацию данного класса см. MFCApplet.cpp
//

//DWORD count = 0;
LONG WINAPI CPlApplet(HWND hwnd, UINT msg, LPARAM param1, LPARAM param2);

class CMFCAppletApp : public CWinApp
{
public:
	CMFCAppletApp();

// Переопределение
public:
	virtual BOOL InitInstance();

	//CAppletDialog dialog;

	DECLARE_MESSAGE_MAP()
};
