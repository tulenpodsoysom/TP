// Drawer.cpp: файл реализации
//

#include "pch.h"
#include "GraphTP1.h"
#include "GraphTP1Dlg.h"
#include "Drawer.h"

using namespace Gdiplus;


// Drawer

IMPLEMENT_DYNAMIC(Drawer, CStatic)

Drawer::Drawer()
{
	Status s =GdiplusStartup(&token,&input,NULL);
	if (s != Status::Ok) {}
}

Drawer::~Drawer()
{
	GdiplusShutdown(token);
}


BEGIN_MESSAGE_MAP(Drawer, CStatic)
END_MESSAGE_MAP()



// Обработчики сообщений Drawer




void Drawer::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//CRect r = lpDrawItemStruct->rcItem;
	//Rect rect{r.left,r.top,r.Width(),r.Height()};

	CMemDC memDC(*CDC::FromHandle(lpDrawItemStruct->hDC), CWnd::FromHandle(lpDrawItemStruct->hwndItem));


	Graphics graphics(memDC.GetDC());
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	SolidBrush brush1(Color(128, 128, 128));
	SolidBrush brush2(Color(255, 0, 0));
	SolidBrush brush3(Color(255, 255, 255));

	Rect rect{ 20, 20, 180, 90 };
	Rect circle{ 250, 100, 90, 90 };

	LinearGradientBrush rectBrush(rect, Color{ 0,255,0 }, Color{ 0,100,0 },0);
	LinearGradientBrush circleBrush(circle, Color{ 0,0,255 }, Color{ 0,0,100 },0);

	Pen pen(Color(0, 0, 0),1.5);
	
	graphics.Clear(Color(200, 200, 200));

	static POINT point = {0,0};
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		GetCursorPos(&point); 
		Drawer::ScreenToClient(&point);
	}



	Matrix matrix;
	matrix.RotateAt(angle, PointF(point.x, point.y));
	graphics.SetTransform(&matrix);

	graphics.FillRectangle(&rectBrush, rect);
	graphics.DrawRectangle(&pen, rect);

	graphics.FillEllipse(&circleBrush, circle);
	graphics.DrawEllipse(&pen,			circle);


	int width = 8;
	graphics.FillEllipse(&brush2, point.x - width / 2, point.y - width / 2, width, width);
	graphics.FillEllipse(&brush3, point.x - width / 4, point.y - width / 4, width / 2, width / 2);

}
