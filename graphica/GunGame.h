#pragma once

#include <iostream>
#include "Figure.h"
#include "Graphics.h"
#include "Matrix.h"
#include "Sphere.h"


//////////////   BOLL   ///////////////////
class Boll
{
public:
	Boll(int);
	~Boll();
	void enemyBollSpawn(int);

private:
	int bollSize = 0;
	Sphere *enemySphiere;

};

Boll::Boll(int size)
{
	bollSize = size;
}

Boll::~Boll()
{
}
//спавн вражеских шаров
void Boll::enemyBollSpawn(int amount) {
	Sphere* enemy = new Sphere[amount];
	int j = 0;
	int x = rand() % Graphics::GetWid() - Graphics::GetWid() / 2;
	int y = rand() % Graphics::GetHeg() - Graphics::GetHeg() / 2;
	int rad = 10 + rand() % 40;
	for (int i = 0; i < amount; i++)
	{
		while ( (x < Graphics::GetWid() + 100 && x > Graphics::GetWid() - 100)
			|| (y < Graphics::GetHeg() + 100 && y > Graphics::GetHeg() - 100) ) {
			x = rand() % Graphics::GetWid() - Graphics::GetWid() / 2;
			y = rand() % Graphics::GetHeg() - Graphics::GetHeg() / 2;
		}
		enemy[j] = Sphere(x, y, rad);
	}
	enemySphiere = enemy;

	Sphere::VisSphere(enemySphiere, amount);
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

//спавн пушки
Gun::Gun(int angle, int force, int xz, int yz)
{
	this->angle = angle;
	this->force = force;

	for (int i = 0; i < 7; i++)
	{
		pt[i].x = pt[i].x * 2 + xz;
		pt[i].y = pt[i].y * 2 + yz;
	}

	Graphics::Set_pen(RGB(0, 255, 0), 3);
	Graphics::Set_brush(RGB(0, 255, 0), 0);
	Polygon(Graphics::dc, pt, 7);
	
}

Gun::~Gun()
{
}

////////////////////////////////////////////////////