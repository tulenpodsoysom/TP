// AppletDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "MFCApplet.h"
#include "AppletDialog.h"
#include "afxdialogex.h"


// диалоговое окно CAppletDialog

IMPLEMENT_DYNAMIC(CAppletDialog, CDialog)

CAppletDialog::CAppletDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAppletDialog::IDD, pParent)
{

}

CAppletDialog::~CAppletDialog()
{
}

void CAppletDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAppletDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CAppletDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAppletDialog::OnBnClickedButton2)
END_MESSAGE_MAP()


// обработчики сообщений CAppletDialog


void CAppletDialog::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	BOOL param;
	SystemParametersInfo(SPI_GETFONTSMOOTHING, 0, &param, 0);
	SystemParametersInfo(SPI_SETFONTSMOOTHING, (param == TRUE)? FALSE:TRUE, NULL, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

	this->RedrawWindow();
}


void CAppletDialog::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	BOOL param;
	SystemParametersInfo(SPI_GETDROPSHADOW, 0, &param, 0);
	SystemParametersInfo(SPI_SETDROPSHADOW, (param == TRUE) ? FALSE : TRUE, NULL, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

	this->UpdateWindow();
}
