#pragma once
#include <vector>
#include <string>
#include <gdiplus.h>

// Graph

class Graph : public CStatic
{
	DECLARE_DYNAMIC(Graph)

public:
	Graph();
	virtual ~Graph();

private:

	std::vector<Gdiplus::PointF*> points;
	std::vector<size_t> counts;
	Gdiplus::GdiplusStartupInput input;
	ULONG_PTR token;

public:
    



    //Gdiplus::Rect  outerrect;
    Gdiplus::RectF worldRect = {0,-1,2,2};


    CString title;
    CString captionX;
    CString captionY;

    


    static double ClosestMantissa(std::vector<double> values);
	static std::pair<Gdiplus::PointF*, size_t> DoubleToPoints(std::vector<double>, Gdiplus::RectF worldRect);
    
	void SetPoints(std::vector<std::vector<double>> values);

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};



