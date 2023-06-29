#pragma once


// Drawer

class Drawer : public CStatic
{
	DECLARE_DYNAMIC(Drawer)

public:
	Drawer();
	virtual ~Drawer();

	ULONG_PTR token;
	Gdiplus::GdiplusStartupInput input;

	int angle;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};


