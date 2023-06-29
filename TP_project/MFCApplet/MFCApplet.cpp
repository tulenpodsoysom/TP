// MFCApplet.cpp: ���������� ��������� ������������� ��� DLL.
//

#include "stdafx.h"
#include "MFCApplet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ���� ��� ���������� DLL ����������� ������� � ������������ DLL MFC,
//		��� �������, ���������������� �� ������ DLL-����������, ������� ��������� ������ �
//		MFC, ������ ��������� ������ AFX_MANAGE_STATE �
//		����� ������ �������.
//
//		��������:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// ���� ���������� �������
//		}
//
//		�����, ����� ������ ������ ��� ����������� � ������
//		������� �� ������ MFC.  ��� ��������, ���
//		�� ������ ���� ������ ���������� 
//		������� � �������������� ���� ����� ����������� ���������� �������,
//		��������� �� ������������ ����� ��������� ������ � MFC
//		DLL.
//
//		� ����������� ��������� MFC 33 � 58 ���������� �����
//		��������� ��������.
//

LONG  WINAPI  CPlApplet(HWND hwnd, UINT msg, LPARAM param1, LPARAM param2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	switch (msg)
	{
	case CPL_INIT: {
		
		return 1;
	}
	case CPL_GETCOUNT: {
		return 1;
	}
	case CPL_INQUIRE: {
		auto& uAppNum = param1;
		CPLINFO* lpcpli = (CPLINFO*)param2;
		if (lpcpli == NULL) return -1;

		lpcpli->idName = IDS_NAME;
		lpcpli->idInfo = IDS_INFO;
		lpcpli->idIcon = IDI_ICON1;
		lpcpli->lData  = NULL;

		return 0;
	}
	case CPL_DBLCLK: {
		//if (hwnd == NULL) return -1;
		CAppletDialog dialog(CWnd::FromHandle(hwnd));

		dialog.DoModal();

		return 0;
	}
	default:
		break;
	}

}










// CMFCAppletApp

BEGIN_MESSAGE_MAP(CMFCAppletApp, CWinApp)
END_MESSAGE_MAP()


// �������� CMFCAppletApp

CMFCAppletApp::CMFCAppletApp()
{
	// TODO: �������� ��� ��������,
	// ��������� ���� ������ ��� ������������� � InitInstance
}


// ������������ ������ CMFCAppletApp

CMFCAppletApp theApp;


// ������������� CMFCAppletApp

BOOL CMFCAppletApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
