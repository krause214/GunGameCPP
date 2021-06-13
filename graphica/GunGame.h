#pragma once

#include <iostream>
#include "Graphics.h"
#include "Matrix.h"


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
	Gun();
	~Gun();


private:
	int force;
	int angle;
};

Gun::Gun()
{
	angle = 90;
	force = 0;
}

Gun::~Gun()
{
}

////////////////////////////////////////////////////