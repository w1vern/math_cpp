#include "../include/matrix.h"
#include <string>
#include <stdarg.h>

mth::Matrix::Matrix(double **arr, std::int32_t rows, std::int32_t columns)
{
	this->rows = rows;
	this->columns = columns;
	this->_matrix = new double *[this->rows];
	for (std::int32_t i = 0; i < this->rows; ++i)
		this->_matrix[i] = new double[this->columns];
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
		{
			this->_matrix[i][j] = *(double *)(arr + j + i * columns);
		}
}
mth::Matrix::Matrix(std::int32_t rows, std::int32_t columns)
{
	this->rows = rows;
	this->columns = columns;
	this->_matrix = new double *[this->rows];
	for (std::int32_t i = 0; i < this->rows; ++i)
		_matrix[i] = new double[this->columns];
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			this->_matrix[i][j] = 0;
}
mth::Matrix::Matrix(std::int32_t rows, std::int32_t columns, bool rows_, ...)
{
	va_list args;
	va_start(args, rows * columns);
	this->rows = rows;
	this->columns = columns;
	this->_matrix = new double *[this->rows];
	for (std::int32_t i = 0; i < this->rows; ++i)
		_matrix[i] = new double[this->columns];
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			if (rows_)
				this->_matrix[i][j] = va_arg(args, double);
			else
				this->_matrix[j][i] = va_arg(args, double);
}
mth::Matrix::~Matrix()
{
	for (std::int32_t i = 0; i < this->rows; ++i)
		delete[] this->_matrix[i];
	delete[] this->_matrix;
}

mth::Matrix mth::Matrix::operator+(const mth::Matrix &matrix_2) const
{
	if (this->rows != matrix_2.rows || this->columns != matrix_2.columns)
		throw "incorrect sizes";
	mth::Matrix result{this->rows, this->columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			result._matrix[i][j] = this->_matrix[i][j] + matrix_2._matrix[i][j];
	return result;
}
mth::Matrix mth::Matrix::operator+=(const mth::Matrix &matrix_2)
{
	return *this = *this + matrix_2;
}
mth::Matrix mth::Matrix::operator-(const mth::Matrix &matrix_2) const
{
	if (this->rows != matrix_2.rows || this->columns != matrix_2.columns)
		throw "incorrect sizes";
	mth::Matrix result{this->rows, this->columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			result._matrix[i][j] = this->_matrix[i][j] - matrix_2._matrix[i][j];
	return result;
}
mth::Matrix mth::Matrix::operator-=(const mth::Matrix &matrix_2)
{
	return *this = *this - matrix_2;
}
mth::Matrix mth::Matrix::operator*(const mth::Matrix &matrix_2) const
{
	if (this->columns != matrix_2.rows)
		throw "incorrect sizes";
	mth::Matrix result{this->rows, matrix_2.columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < matrix_2.columns; ++j)
			for (std::int32_t k = 0; k < this->columns; ++k)
				result._matrix[i][j] += this->_matrix[i][k] * matrix_2._matrix[k][j];
	return result;
}
mth::Matrix mth::Matrix::operator*=(const mth::Matrix &matrix_2)
{
	return *this = *this * matrix_2;
}
mth::Matrix mth::Matrix::operator*(double k) const
{
	mth::Matrix result{rows, columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			result._matrix[i][j] = this->_matrix[i][j] * k;
	return result;
}
mth::Matrix mth::Matrix::operator*=(double k)
{
	return *this = *this * k;
}
mth::Matrix mth::Matrix::operator/(double k) const
{
	mth::Matrix result{rows, columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			result._matrix[i][j] = this->_matrix[i][j] / k;
	return result;
}
mth::Matrix mth::Matrix::operator/=(double k)
{
	return *this = *this / k;
}
bool mth::Matrix::operator==(const mth::Matrix &matrix_2) const
{
	if (this->rows != matrix_2.rows || this->columns != matrix_2.columns)
		return false;
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			if (this->_matrix[i][j] != matrix_2._matrix[i][j])
				return false;
	return true;
}
bool mth::Matrix::operator!=(const mth::Matrix &matrix_2) const
{
	return !(*this == matrix_2);
}

double mth::Matrix::det() const
{
	if (rows != columns)
		throw "incorrect sizes";
	if (rows == 1)
		return _matrix[0][0];
	if (rows == 2)
		return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
	if (rows == 3)
		return _matrix[0][0] * _matrix[1][1] * _matrix[2][2] + _matrix[0][1] * _matrix[1][2] * _matrix[2][0] + _matrix[0][2] * _matrix[1][0] * _matrix[2][1] - _matrix[0][2] * _matrix[1][1] * _matrix[2][0] - _matrix[0][1] * _matrix[1][0] * _matrix[2][2] - _matrix[0][0] * _matrix[1][2] * _matrix[2][1];
	double res = 0;
	for (int i = 0; i < rows; ++i)
		res += getAlg(0, i) * _matrix[0][i];
	return res;
}
double mth::Matrix::M(std::int32_t row, std::int32_t column) const
{
	return getSubMatrix(row, column).det();
}
mth::Matrix mth::Matrix::getSubMatrix(std::int32_t row, std::int32_t column) const
{
	if (row >= rows || column >= columns)
		throw "incorrect sizes";
	mth::Matrix result{rows - 1, columns - 1};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			if (i == row || j == column)
				continue;
			else
				result._matrix[i - static_cast<std::int32_t>(i >= row)][j - static_cast<std::int32_t>(j >= column)] = _matrix[i][j];
	return result;
}
mth::Matrix mth::Matrix::getAlgMatrix() const
{
	mth::Matrix result{rows, columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			result._matrix[i][j] = getAlg(i, j);
	return result;
}
double mth::Matrix::getAlg(std::int32_t row, std::int32_t column) const
{
	return (1 - ((row + column) & 1) * 2) * M(row, column);
}
mth::Matrix mth::Matrix::T() const
{
	mth::Matrix result{columns, rows};
	for (std::int32_t i = 0; i < columns; ++i)
		for (std::int32_t j = 0; j < rows; ++j)
		{
			result._matrix[i][j] = _matrix[j][i];
		}
	return result;
}
mth::Matrix mth::Matrix::Inverse() const
{
	return this->getAlgMatrix().T() / this->det();
}
double mth::Matrix::getEl(std::int32_t row, std::int32_t column)
{
	if (row >= rows || row < 0 || column >= columns || column < 0)
		throw "incorrect index";
	return _matrix[row][column];
}
std::string mth::Matrix::ToString() const
{
	std::string **string = new std::string *[rows];
	for (std::int32_t i = 0; i < rows; ++i)
		string[i] = new std::string[columns];
	std::int32_t *column_size = new std::int32_t[columns];
	for (std::int32_t i = 0; i < columns; ++i)
		column_size[i] = 0;
	for (std::int32_t i = 0; i < rows; ++i)
		for (std::int32_t j = 0; j < columns; ++j)
		{
			string[i][j] = std::to_string(_matrix[i][j]);
			if (string[i][j].length() > column_size[j])
				column_size[j] = static_cast<std::int32_t>(string[i][j].length());
		}
	for (std::int32_t i = 0; i < rows; ++i)
		for (std::int32_t j = 0; j < columns; ++j)
		{
			std::int32_t length = static_cast<std::int32_t>(string[i][j].length());
			for (std::int32_t k = 0; k < column_size[j] - length; ++k)
				string[i][j] += ' ';
		}
	std::string result = "";
	for (std::int32_t i = 0; i < rows; ++i)
	{
		for (std::int32_t j = 0; j < columns; ++j)
			result += string[i][j] + ' ';
		result += '\n';
	}
	result.pop_back();
	for (std::int32_t i = 0; i < rows; ++i)
		delete[] string[i];
	delete[] string;
	delete[] column_size;
	return result;
}
std::ostream &operator<<(std::ostream &str, const mth::Matrix &matrix)
{
	return str << matrix.ToString();
}
