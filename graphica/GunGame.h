#pragma once

#include <iostream>
#include "Figure.h"
#include "Graphics.h"
#include "Matrix.h"
#include "Sphere.h"


//////////////   BOLL    ///////////////////
class Boll
{
public:
	Boll(int);
	~Boll();

private:
	int bollSize = 0;

};

Boll::Boll(int size)
{
	bollSize = size;
}

Boll::~Boll()
{
}

/////////////////////    GUN    /////////////////////////
class Gun
{
public:
	Gun(int, int, int, int);
	~Gun();


private:
	POINT pt[7] = { {0 ,-20},{20,0},{10,20},{10,50},{-10,50},{-10,20},{-20,0} };
	int force;
	int angle;
};

Gun::Gun(int angle, int force, int xz, int yz)
{
	this->angle = angle;
	this->force = force;

	for (int i = 0; i < 7; i++)
	{
		pt[i].x = pt[i].x + xz;
		pt[i].y = pt[i].y + yz;
	}

	Graphics::Set_pen(RGB(0, 255, 0), 3);
	Graphics::Set_brush(RGB(0, 255, 0), 0);
	Polygon(Graphics::dc, pt, 7);
	
}

Gun::~Gun()
{
}

////////////////////////////////////////////////////