#pragma once
#include <windows.h>
#include <math.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>
using namespace std;

class Matrix
{
private:
	array<array<double, 3>, 3> mt;
public:
	Matrix();
	void PrintMatrix();
	void IdentityMatrix();
	double& operator()(int i, int j) { return mt[i][j]; }
	friend Matrix operator*(Matrix, Matrix);
	void Scale(double);
	void Translated(double, double);
	void Rotate(double);
} ;
Matrix MT;

void Matrix::Scale(double kf)
{
	mt[0][0] = kf;
	mt[1][1] = kf;
}

void Matrix::Translated(double tx, double ty)
{
	mt[0][2] = tx;
	mt[1][2] = ty;
}

void Matrix::Rotate(double alfa)
{
	double rad = 0.0174533;
	alfa = rad * alfa;

	mt[0][0] = cos(alfa);
	mt[1][0] = sin(alfa);

	mt[0][1] = -sin(alfa);
	mt[1][1] = cos(alfa);
}


Matrix operator* (Matrix m1, Matrix m2)
{
	Matrix res;
	res.mt = { 0 };
	size_t i, j, k;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			for (k = 0; k < 3; k++)
				res(i, j) += m1(i, k) * m2(k, j);
		}
	return res;
}

void Matrix::IdentityMatrix()
{
	mt = { 0 };
	for (size_t i = 0; i < mt.size(); i++)
		mt[i][i] = 1;
}

Matrix::Matrix()
{
	IdentityMatrix();
}

void Matrix::PrintMatrix()
{
	for (size_t i = 0; i < mt.size(); i++)
	{
		for (size_t j = 0; j < mt[i].size(); j++)
			cout << mt[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}
//======================================================================

class Vector
{
private:
	array<double, 3> vec;
public:
	Vector() : vec{ 0, 0, 0 } {};
	Vector(double x, double y) : vec{ x, y, 1 } {}
	double& operator[](int i) { return vec[i];  }
	friend Vector operator*(Matrix, Vector);
	void PrintVector();
	void ClearVec() { vec[0] = 0; vec[1] = 0; vec[2] = 1; }
};

void Vector::PrintVector()
{
	cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << endl << endl;
}

Vector operator*(Matrix m, Vector v)
{
	Vector res;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			res[i] += m(i, j) * v.vec[j];
		}
	}
	return res;
}

//=============================================================================



