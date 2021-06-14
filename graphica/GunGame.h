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
	friend class Gun;
	int getAmountOfEnemyBolls();

private:
	int bollSize = 0;
	Sphere *enemySphiere;
	int amountOfEnemyBolls;

};
//спавн вражеских шаров
Boll::Boll(int amount) {
	amountOfEnemyBolls = amount;
	Sphere* enemy = new Sphere[amount];
	int j = 0;
	int x = rand() % Graphics::GetWid() - Graphics::GetWid() / 2;
	int y = rand() % Graphics::GetHeg() - Graphics::GetHeg() / 2;
	int rad = 10 + rand() % 40;
	for (int i = 0; i < amount; i++)
	{
		while ((x < Graphics::GetWid() + 100 && x > Graphics::GetWid() - 100)
			|| (y < Graphics::GetHeg() + 100 && y > Graphics::GetHeg() - 100)) {
			x = rand() % Graphics::GetWid() - Graphics::GetWid() / 2;
			y = rand() % Graphics::GetHeg() - Graphics::GetHeg() / 2;
		}
		enemy[j] = Sphere(x, y, rad);
	}
	enemySphiere = enemy;

	Sphere::VisSphere(enemySphiere, amount);
}

Boll::~Boll()
{
}


int Boll::getAmountOfEnemyBolls() {
	return amountOfEnemyBolls;
}

/////////////////////    GUN    /////////////////////////
class Gun
{
public:
	Gun(int, Boll*, int);
	~Gun();
	void Shot(int, Boll*, int );


private:
	POINT pt[7] = { {0 ,20},{20,0},{10,-20},{10,-50},{-10,-50},{-10,-20},{-20,0} };
	int angle;
	int xz = Graphics::GetWid() / 2;
	int yz = Graphics::GetHeg() / 2;
};

//спавн пушки
Gun::Gun(int angle, Boll *boll, int amountOfEnemyBolls)
{

	Vector v;
	Matrix rote;
	rote.Rotate(angle);

	this->angle = angle;

	for (int i = 0; i < 7; i++)
	{
		v = rote * Vector(pt[i].x, pt[i].y);
		pt[i].x = v[0];
		pt[i].y = v[1];

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

void Gun::Shot(int angle, Boll* boll, int amountOfEnemyBolls)
{
	//отчистка поля
	Rectangle(Graphics::dc, 0, 0, Graphics::GetWid(), Graphics::GetHeg());

	//!!!добавить обработку попаданий
	double radian = (angle - 90) * 0.0174533;
	double k = sin(radian) / cos(radian);
	double d, r;
	int xS, yS;
	for (int i = 0; i < amountOfEnemyBolls; i++)
	{
		xS = boll->enemySphiere[i].getCenter().x;
		yS = boll->enemySphiere[i].getCenter().y;
		d = abs(double(xS * (-k) + yS)) / sqrt(k * k + 1);
		r = boll->enemySphiere[i].getR();
		if (d <= r)
		{
			boll->enemySphiere[i].setExist(0);
		}
	}

	//laser
	int xLine = 0;
	int yLine = 0;
	int xLineEnd = 0;
	int yLineEnd = -1000;

	Vector v;
	Matrix rote;
	rote.Rotate(angle);

	
	xLine = xLine + xz;
	yLine = yLine + yz;

	v = rote * Vector(xLineEnd, yLineEnd);
	xLineEnd = v[0];
	yLineEnd = v[1];

	xLineEnd = xLineEnd + xz;
	yLineEnd = yLineEnd + xz;


	Graphics:: Set_pen(RGB(255, 0, 0), 1);
	Graphics::Line(xLine, yLine, xLineEnd, yLineEnd);

	Gun gun(angle, boll, amountOfEnemyBolls);


	Sphere::VisSphere(boll->enemySphiere, boll->amountOfEnemyBolls);
	Graphics::Osi();
}

////////////////////////////////////////////////////