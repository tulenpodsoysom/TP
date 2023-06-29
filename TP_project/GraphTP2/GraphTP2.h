
// GraphTP2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CGraphTP2App:
// Сведения о реализации этого класса: GraphTP2.cpp
//

class CGraphTP2App : public CWinApp
{
public:
	CGraphTP2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CGraphTP2App theApp;
