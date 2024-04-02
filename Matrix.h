#pragma once
#include <cstdlib>
#include <cassert>

class Matrix
{
public:
	Matrix();
	Matrix(int rows, int cols);
	~Matrix();

	int rows() { return _rows; }
	int cols() { return _cols; }

	double& operator ()(int row, int col);

	Matrix T();

	static Matrix I(int n);
private:
	int _rows, _cols;
	double* _data;
};

Matrix::Matrix()
{
	_rows = 1;
	_cols = 1;
	_data = reinterpret_cast<double*>(std::malloc(sizeof(double)));
}

Matrix::~Matrix()
{
	free(_data);
}

Matrix::Matrix(int rows, int cols)
{
	_rows = rows;
	_cols = cols;
	_data = reinterpret_cast<double*>(std::malloc(sizeof(double) * rows * cols));
}

double& Matrix::operator() (int row, int col)
{
	return _data[row * _cols + col];
}

//TODO: implement override of equals so it always copies (probably, still not sure)
Matrix operator = ()
{

}

Matrix operator + (Matrix lhs, Matrix rhs)
{
	assert(lhs.rows() == rhs.rows());
	assert(lhs.cols() == rhs.cols());

	Matrix m(lhs.rows(), lhs.cols());
	for (int i = 0; i < lhs.rows(); i++)
		for (int j = 0; j < lhs.cols(); j++)
			m(i, j) = lhs(i, j) + rhs(i, j);

	return m;
}

Matrix operator - (Matrix m)
{
	Matrix n(m.rows(), m.cols());
	for (int i = 0; i < m.rows(); i++)
		for (int j = 0; j < m.cols(); j++)
			n(i, j) = -m(i, j);

	return n;
}

Matrix operator - (Matrix lhs, Matrix rhs)
{
	assert(lhs.rows() == rhs.rows());
	assert(lhs.cols() == rhs.cols());

	Matrix m(lhs.rows(), lhs.cols());
	for (int i = 0; i < lhs.rows(); i++)
		for (int j = 0; j < lhs.cols(); j++)
			m(i, j) = lhs(i, j) + rhs(i, j);

	return m;
}

Matrix Matrix::T()
{
	Matrix n(cols() , rows());
	for (int i = 0; i < rows(); i++)
		for (int j = 0; j < cols(); j++)
			n(j, i) = this->operator()(i, j);
	
	return n;
}

Matrix operator * (Matrix lhs, Matrix rhs)
{
	assert(lhs.cols() == rhs.rows());

	Matrix m(lhs.rows(), rhs.cols());
	for (int i = 0; i < lhs.rows(); i++)
		for (int j = 0; j < rhs.cols(); j++)
		{
			m(i, j) = 0;
			for (int k = 0; k < lhs.cols(); k++)
			{
				m(i, j) += lhs(i, k) * rhs(k, j);
			}
		}
			

	return m;
}

Matrix Matrix::I(int n)
{
	Matrix m(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				m(i, j) = 1;
			else
				m(i, j) = 0;

	return m;
}

