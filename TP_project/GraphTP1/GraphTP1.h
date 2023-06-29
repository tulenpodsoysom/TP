
// GraphTP1.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CGraphTP1App:
// Сведения о реализации этого класса: GraphTP1.cpp
//

class CGraphTP1App : public CWinApp
{
public:
	CGraphTP1App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CGraphTP1App theApp;
