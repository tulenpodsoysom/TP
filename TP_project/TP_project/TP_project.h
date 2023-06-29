
// TP_project.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CTPprojectApp:
// Сведения о реализации этого класса: TP_project.cpp
//

class CTPprojectApp : public CWinApp
{
public:
	CTPprojectApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CTPprojectApp theApp;
