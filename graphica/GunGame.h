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
	void VisBoll();

private:
	//int bollSize = 0;
	Sphere *enemySphiere;
	int amountOfEnemyBolls;

};

void Boll :: VisBoll()
{
	Sphere::VisSphere(this ->enemySphiere, this ->amountOfEnemyBolls);
}
//спавн вражеских шаров
Boll::Boll(int amount) {
	amountOfEnemyBolls = amount;
	Sphere* enemy = new Sphere[amount];
	//int j = 0;
	//int wid = Graphics::GetWid();
	//int heg = Graphics::GetHeg();
	//int x = rand() % wid - wid / 2;
	//int y = rand() % heg - heg / 2;
	//int rad = 40 + rand() % 10;
	//for (int i = 0; i < amount; i++)
	//{
	//	do
	//	{
	//		x = rand() % wid - wid / 2 + wid;
	//		y = rand() % heg - heg / 2 + heg;
	//		cout << x << " " << y << endl;
	//	} while ((x == 0 || y == 0));

	//	//while ((x < wid/2 && x >  -wid/2)
	//	//	&& (y < heg/2 && y >  -heg/2)) {
	//	//	x = rand() % wid - wid / 2;
	//	//	y = rand() % heg - heg / 2;
	//	//}
	//	enemy[j] = Sphere(x, y, rad);
	//}
	enemySphiere = enemy;

	Sphere::VisSphere(enemySphiere, amount);
}

Boll::~Boll()
{
	free(enemySphiere);
}


int Boll::getAmountOfEnemyBolls() {
	return amountOfEnemyBolls;
}

/////////////////////    GUN    /////////////////////////
class Gun
{
public:
	Gun(int, int);
	//~Gun();
	void Shot(int, Boll*, int );
	bool EndOfGame(Boll*, int);


private:
	POINT pt[7] = { {0 ,20},{20,0},{10,-20},{10,-50},{-10,-50},{-10,-20},{-20,0} };
	int angle;
	int xz = Graphics::GetWid() / 2;
	int yz = Graphics::GetHeg() / 2;
};

//спавн пушки
Gun::Gun(int angle, int rgb)
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
	if (rgb == 0)
	{
		Graphics::Set_pen(RGB(0, 0, 0), 3);
		Graphics::Set_brush(RGB(0, 0, 0), 0);
	}
	else
	{
		Graphics::Set_pen(RGB(0, 255, 0), 3);
		Graphics::Set_brush(RGB(0, 255, 0), 0);
	}
	Polygon(Graphics::dc, pt, 7);

}

//Gun::~Gun()
//{
//}

void Gun::Shot(int angle, Boll* boll, int amountOfEnemyBolls)
{
	//отчистка поля
	//Rectangle(Graphics::dc, 0, 0, Graphics::GetWid(), Graphics::GetHeg());

	//обработка попаданий
	double radian = (angle - 90) * 0.0174533;
	double k = sin(radian) / cos(radian);
	double d, r;
	int xS, yS;
	for (int i = 0; i < amountOfEnemyBolls; i++)
	{
		if (boll->enemySphiere[i].getExist() == 0)
			continue;
		xS = boll->enemySphiere[i].getCenter().x;
		yS = boll->enemySphiere[i].getCenter().y;
		d = abs(double(xS * (-k) + yS)) / sqrt(k * k + 1);
		r = boll->enemySphiere[i].getR();

		
		if (d <= r )
		{
			//0-90
			if (angle % 360 >= 0 && angle % 360 < 90 
				&& boll->enemySphiere[i].getCenter().x > 0 && boll->enemySphiere[i].getCenter().y < 0)
			{
				boll->enemySphiere[i].setExist(0);
				boll->enemySphiere[i].delSphere();
			}
			//90-180
			else if (angle % 360 >= 90 && angle % 360 < 180
				&& boll->enemySphiere[i].getCenter().x > 0 && boll->enemySphiere[i].getCenter().y > 0)
			{
				boll->enemySphiere[i].setExist(0);
				boll->enemySphiere[i].delSphere();
			}
			//180 - 270
			else if (angle % 360 >= 180 && angle % 360 < 270
				&& boll->enemySphiere[i].getCenter().x < 0 && boll->enemySphiere[i].getCenter().y > 0)
			{
				boll->enemySphiere[i].setExist(0);
				boll->enemySphiere[i].delSphere();
			}
			//270 - 360
			else if (angle % 360 >= 270 && angle % 360 < 360
				&& boll->enemySphiere[i].getCenter().x < 0 && boll->enemySphiere[i].getCenter().y < 0)
			{
				boll->enemySphiere[i].setExist(0);
				boll->enemySphiere[i].delSphere();
			}
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
	yLineEnd = yLineEnd + yz;


	Graphics:: Set_pen(RGB(255, 0, 0), 1);
	Graphics::Line(xLine, yLine, xLineEnd, yLineEnd);

	{Gun gun(angle, 1); }

	//закрашивание выстрела
	Sleep(100);
	Graphics::Set_pen(RGB(0, 0, 0), 1);
	Graphics::Line(xLine, yLine, xLineEnd, yLineEnd);
	Gun gun(angle, 1);

	//Sphere::VisSphere(boll->enemySphiere, boll->amountOfEnemyBolls);
	//Graphics::Osi();
}

bool Gun::EndOfGame(Boll* boll, int amountOfEnemyBolls) {
	int k = 0;
	for (int i = 0; i < amountOfEnemyBolls; i++)
	{
		if (boll->enemySphiere[i].getExist())
		{
			k++;
			return 0;
		}
	}
	if (k == 0) {
		return 1;
	}
}

////////////////////////////////////////////////////