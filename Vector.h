#pragma once
#include "Matrix.h"

class Vector : Matrix
{
public:
	Vector(int rows);

private:
	int _rows, _cols = 1;
	double* _data;
};

Vector::Vector(int rows)
{
	_rows = rows;
	_data = reinterpret_cast<double*>(std::malloc(sizeof(double) * rows));
}