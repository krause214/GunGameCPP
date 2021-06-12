#pragma once

#include <windows.h>
#include <math.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "Graphics.h"
#include "Matrix.h"
using namespace std;

#define PI 3.141592653589

struct Pt
{
public:
	double x, y;
};

class Figure
{
private:
	vector<Pt> rpt;
protected:
	double a;
public:
	Figure(double);
	void VisFigure(COLORREF);
};

Figure::Figure(double a_)
{
	a = a_;

	Vector v;
	Pt pt;

	double d = a / 2;

	v = MT * Vector(-d, d);
	pt.x = v[0];
	pt.y = v[1];
	rpt.push_back(pt);

	v = MT * Vector(-d, -d);
	pt.x = v[0];
	pt.y = v[1];
	rpt.push_back(pt);

	v = MT * Vector(d, -d);
	pt.x = v[0];
	pt.y = v[1];
	rpt.push_back(pt);

	v = MT * Vector(d, d);
	pt.x = v[0];
	pt.y = v[1];
	rpt.push_back(pt);
}

void Figure::VisFigure(COLORREF col)
{
	Graphics::Set_pen(col, 3);
	Graphics::Set_brush(col, 0);

	POINT pt[4];
	int wid = Graphics::GetWid();
	int heg = Graphics::GetHeg();

	for (int i=0; i<4; i++)
	{
		pt[i].x = LONG((rpt[i].x + 1.0) * (wid / 2.));
		pt[i].y = heg - LONG((rpt[i].y + 1.0) * (heg / 2.));
	}

	Polygon(Graphics::dc, pt, 4);

	Graphics::Set_pen(RGB(0, 255, 0), 3);
	Graphics::Line(pt[0].x, pt[0].y, pt[2].x, pt[2].y);

	Graphics::Set_pen(RGB(0, 0, 255), 3);
	Graphics::Line(pt[1].x, pt[1].y, pt[3].x, pt[3].y);
}
//=====================================================================================

class Octagon : public Figure
{
private:
	void InitOctagon();
protected:
	vector<Pt> opt;
public:
	Octagon(double a) : Figure(a) { InitOctagon(); }
	void VisOctagon(COLORREF);
	Pt& operator[] (const int ind) {return opt[ind];}
};

void Octagon::InitOctagon()
{
	double r = sqrt(a * a + a * a) / 2.;

	Pt pt;
	Vector v;
	for (int i = 0; i < 8; i++)
	{
		pt.x = r * cos(PI * i / 4.0);
		pt.y = r * sin(PI * i / 4.0);
		v = MT * Vector(pt.x, pt.y);
		pt.x = v[0];
		pt.y = v[1];
		opt.push_back(pt);
	}
}

void Octagon::VisOctagon(COLORREF col)
{
	POINT pt[8];
	int wid = Graphics::GetWid();
	int heg = Graphics::GetHeg();

	for (int i = 0; i < 8; i++)
	{
		pt[i].x = LONG((opt[i].x + 1.0) * (wid / 2.));
		pt[i].y = heg - LONG((opt[i].y + 1.0) * (heg / 2.));
	}

	Graphics::Set_pen(col, 3);
	Graphics::Set_brush(col, 0);
	Polygon(Graphics::dc, pt, 8);
}

