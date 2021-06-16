#ifndef SPHERE_H
#define SPHERE_H
#include "Graphics.h"

class Sphere
{
private:
	COLORREF col;
	POINT ctr;
	double R;
	bool Hit(int, int, double *);
	bool exist /*= 1*/;
public:
	Sphere();
	Sphere(int, int, double);
	static void VisSphere(Sphere *, int);
	COLORREF getCol(){return col;}
	POINT getCenter(){return ctr;}
	double getR(){ return R; }
	bool getExist() { return exist; }
	void setExist(bool a) { exist = a; }
	void delSphere();
};


Sphere::Sphere()
{
	exist = 1;
	BYTE r, g, b;
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
	col = RGB(r, g, b);
	R = 40 + rand() % 20;
	int wid = Graphics::GetWid();
	int heg = Graphics::GetHeg();
	do
	{
		Sleep(10);
		ctr.x = rand() % (wid - 2 * (int)R - 6) - wid / 2 + R + 3;
		Sleep(10);
		ctr.y = rand() % (heg - 2 * (int)R - 6) - heg / 2 + R + 3;
	} 	while (/*ctr.x == 0 || ctr.y == 0 || */(abs(ctr.x) < 150 && abs(ctr.y) < 150) || (abs(ctr.x) < R || abs(ctr.y) < R));

	
}

Sphere::Sphere(int x, int y, double rad)
{
	exist = 1;
	BYTE r, g, b;
	r = rand() % 255 + 1;
	g = rand() % 255 + 1;
	b = rand() % 255 + 1;
	col = RGB(r, g, b);

	int wid = Graphics::GetWid();
	int heg = Graphics::GetHeg();
	Sleep(10);
	ctr.x = x;
	Sleep(10);
	ctr.y = y;

	R = rad;
}

bool Sphere::Hit(int wx, int wy, double *n)
{
	double dx = wx - ctr.x;
	double dy = wy - ctr.y;
	double dz;
	if ((dx * dx + dy * dy) < R * R) //Проверка пересесечения луча сферы
	{
		dz = sqrt(R * R - dx * dx - dy * dy); //Опрделение длины луча
		*n = dz / R; //Определение коэф-та, определяющего оттенок пиксела
		return true;
	}
	return false;
}

void Sphere::VisSphere(Sphere *sp,int kol)
{
	
	int y,x,k, dx, dy;
	double n;
	COLORREF col;
	BYTE r,g,b;

	int wid = Graphics::GetWid();
	int heg = Graphics::GetHeg();

	for (y=0; y<heg; y++)
	{
		dy = y - heg / 2;
		for (x=0; x<wid; x++)
		{
			dx = x - wid / 2;
			for(k=0; k<kol; k++)
			{
				if(sp[k].Hit(dx,dy, &n) == true && sp[k].getExist())  
				{
					col = sp[k].getCol();
					r = (BYTE)(GetRValue(col)*n);
					g = (BYTE)(GetGValue(col)*n);
					b = (BYTE)(GetBValue(col)*n);
					Graphics::Point(x, y, RGB(r,g,b));
				}
			}
		}
	}
}

//закрашивание сферы чёрным цветом
void Sphere :: delSphere()
{
	int wid = Graphics::GetWid()/2;
	int heg = Graphics::GetHeg()/2;
	POINT c = this ->getCenter();
	double R = this->getR();
	Graphics::Set_pen(RGB(0, 0, 0), 3);
	Graphics::Set_brush(RGB(0, 0, 0), 0);
	Ellipse(Graphics::dc, c.x - R + wid, c.y - R + heg, c.x + R + wid, c.y + R + heg);

}

#endif SPHERE_H

//=======================================================================
//struct Star
//{
//public:
//	Rgb col;
//	int x, y;
//	Star();
//};
//
//Star::Star()
//{
//	x = rand() % wid;
//	y = rand() % heg;
//	col.r = 10 + rand() / 250;
//	col.g = 10 + rand() / 250;
//	col.b = 10 + rand() / 250;
//}
//
//void VisStar(Graphics gr)
//{
//	Star star[100];
//	int x, y, x1, y1, x2, y2;
//	for (int i = 0; i < 100; i++)
//	{
//		gr.Set_pen(star[i].col, 1);
//		x = star[i].x;
//		y = star[i].y;
//
//		x1 = x - 4;	y1 = y;
//		x2 = x + 4; y2 = y;
//		gr.Line(x1, y1, x2, y2);
//
//		x1 = x;	y1 = y - 4;
//		x2 = x; y2 = y + 4;
//		gr.Line(x1, y1, x2, y2);
//
//		x1 = x - 3;	y1 = y - 3;
//		x2 = x + 3; y2 = y + 3;
//		gr.Line(x1, y1, x2, y2);
//
//		x1 = x + 3;	y1 = y - 3;
//		x2 = x - 3; y2 = y + 3;
//		gr.Line(x1, y1, x2, y2);
//
//	}
//}



