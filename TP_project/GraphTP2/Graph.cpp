// Graph.cpp: файл реализации
//

#include "pch.h"
#include "GraphTP2.h"
#include "Graph.h"

#include <algorithm>

using namespace Gdiplus;

// Graph

IMPLEMENT_DYNAMIC(Graph, CStatic)

Graph::Graph()
{
	Status s = GdiplusStartup(&token, &input, NULL);
	if (s != Status::Ok) {}
}

Graph::~Graph()
{
	GdiplusShutdown(token);
}


BEGIN_MESSAGE_MAP(Graph, CStatic)
END_MESSAGE_MAP()



// Обработчики сообщений Graph




void Graph::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	auto& a = lpDrawItemStruct->rcItem;
	Rect outerrect{ a.left, a.top, a.right - a.left, a.bottom - a.top };
   
	Graphics graphicsDC(lpDrawItemStruct->hDC);
	Bitmap bitmap(outerrect.Width,outerrect.Height,&graphicsDC);
    Graphics graphics(&bitmap);


	graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.Clear(Color(255, 255, 255));

	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);
	format.SetLineAlignment(StringAlignmentCenter);

	Gdiplus::Font font1(L"Arial", 9, FontStyleRegular);
	Gdiplus::Font font2(L"Arial", 11, FontStyleRegular);
	Gdiplus::Font font3(L"Arial", 11, FontStyleItalic);

	Pen gridPen(Color(128, 128, 128), 0.005);
	Pen mainGridPen(Color(0, 0, 0),0.01);

	Pen graphPen1(Color(255, 0, 0), 0.005);
	Pen graphPen2(Color(0, 0, 255), 0.005);
	Pen graphPen3(Color(0, 255, 0), 0.005);
	Pen graphPen4(Color(255, 255, 0), 0.005);
	Pen graphPen5(Color(0x1f, 0x3a, 0x3d), 0.005);


    Rect rect = outerrect;	REAL offsetX = 30, offsetY = 30;
    rect.X += offsetX; rect.Y += offsetY; rect.Width -= offsetX *2; rect.Height -= offsetY *2;
   
    int nGridX = 10; double y_max = max(worldRect.Y,worldRect.Y + worldRect.Height);
    int nGridY = 2 * round(pow(10, log10(y_max) - floor(log10(y_max)))) * ((ceil(pow(10, log10(y_max) - floor(log10(y_max)))) == 1) ? 5 : 1);
    //ymax = [0,1,2,3,4,5,6,7,8,9] * 10^n!!!


	Matrix matrix;
    
	matrix.Translate(offsetX, offsetY);
	matrix.Scale((REAL)rect.Width / worldRect.Width, -(REAL)rect.Height / worldRect.Height);
	matrix.Translate(0, worldRect.Y);

	
	// Отрисовка сетки 

    for (int var = 1; var < nGridX; ++var)
    {
		PointF p1 = { worldRect.X + (REAL)var / nGridX * worldRect.Width ,worldRect.Y };
        PointF p2 = { worldRect.X + (REAL)var / nGridX * worldRect.Width ,worldRect.Y+worldRect.Height };
		CString caption; caption.Format(L"%g", p1.X);

		matrix.TransformPoints(&p1);
		matrix.TransformPoints(&p2);

		graphics.DrawLine(&gridPen, p1, p2);

		RectF r = { PointF{ p1.X - offsetX, p1.Y }, SizeF{ 2*offsetX, offsetY } };
		graphics.DrawString(caption.GetString(), caption.GetLength(), &font1, r, &format, &SolidBrush(Color(0, 0, 0)));
    }
    for (int var = 1; var < nGridY; ++var)
    {
        PointF p1 = {worldRect.X,                    worldRect.Y + (REAL)var / nGridY * worldRect.Height };
        PointF p2 = {worldRect.X + worldRect.Width , worldRect.Y + (REAL)var / nGridY * worldRect.Height };
		CString caption; caption.Format(L"%g", p1.Y);
		
		matrix.TransformPoints(&p1);
		matrix.TransformPoints(&p2);

        graphics.DrawLine(&gridPen, p1, p2);


		RectF r = { PointF{ 0, p1.Y - 30 }, SizeF{ offsetX, 30 * 2 } };
		graphics.DrawString(caption.GetString(), caption.GetLength(), &font1, r, &format, &SolidBrush(Color(0, 0, 0)));
    }


	// Отрисовка значений графика
	graphics.SetTransform(&matrix);
    if (!points.empty())
        for (size_t var = 0; var < points.size(); ++var) 
                {
					if (counts[var] == 0) continue;
                    Pen* graphPen;
                    switch (var) {
                    case 0: {graphPen = &graphPen1; break; }
                    case 1: {graphPen = &graphPen2; break; }
                    case 2: {graphPen = &graphPen3; break; }
                    case 3: {graphPen = &graphPen4; break; }
                    case 4: {graphPen = &graphPen5; break; }
                    default: {continue; break; }
                    }

					graphics.DrawCurve(graphPen, points[var], counts[var]);
                }

	// Отрисовка главных осей 
	PointF xl{ worldRect.X, 0 }, xr{ worldRect.X + worldRect.Width, 0 };
	PointF yb{ 0, worldRect.Y }, yt{ 0, worldRect.Y + worldRect.Height };

	graphics.DrawLine(&mainGridPen, xl, xr);
	graphics.DrawLine(&mainGridPen, yb, yt);


	// Отрисовка подписей к осям и названия
	graphics.ResetTransform();
	graphics.TranslateTransform(offsetX, offsetY);
    graphics.DrawString(captionY.GetString(), captionY.GetLength(), &font2, PointF{0.0f, 0.0f }, &SolidBrush(Color(0, 0, 0)));
    graphics.DrawString(captionX.GetString(), captionX.GetLength(), &font2, PointF{ (REAL)rect.Width, (REAL)rect.Height/ 2.0f }, &SolidBrush(Color(0, 0, 0)));
    graphics.DrawString(title.GetString(), title.GetLength(), &font3, RectF{ PointF{0.0f,-offsetY },SizeF{(REAL)rect.Width,offsetY} },&format, &SolidBrush(Color(0, 0, 0)));
	graphics.ResetTransform();


	graphicsDC.DrawImage(&bitmap, outerrect);
}


double Graph::ClosestMantissa(std::vector<double> values)
{
    double fmax = *(std::max_element(values.begin(), values.end()));
    double fmin = *(std::min_element(values.begin(), values.end()));
    double fextr = (fmax > -fmin) ? fmax : -fmin;

    return pow(10, floor(log10(fextr))) * ceil(pow(10, log10(fextr) - floor(log10(fextr))));
}

std::pair<PointF*, size_t> Graph::DoubleToPoints(std::vector<double> values, RectF worldRect)
{
	PointF* points = new PointF[values.size()];
	for (size_t i = 0; i < values.size(); i++)
	{
		points[i].X = worldRect.X + i * worldRect.Width / values.size();
		points[i].Y = values[i];
	}

	return std::pair<PointF*,size_t>{points,values.size()};
}

void Graph::SetPoints(std::vector<std::vector<double>> values)
{
	for (auto& i : points)
	{
		delete[] i;
	}
	points.clear(); points.resize(values.size());
	counts.clear(); counts.resize(values.size());

	for (auto it = values.begin(); it < values.end(); it++)
	{
		auto a = DoubleToPoints(*it, this->worldRect);
		points[it - values.begin()] = a.first;
		counts[it - values.begin()] = a.second;
	}

	
}