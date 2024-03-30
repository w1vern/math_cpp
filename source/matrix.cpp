#include "../include/matrix.h"
#include <string>

mth::Matrix::Matrix(double **arr, std::int32_t rows, std::int32_t columns)
{
	this->_rows = rows;
	this->_columns = columns;
	this->_matrix = new double *[this->_rows];
	for (std::int32_t i = 0; i < this->_rows; ++i)
		this->_matrix[i] = new double[this->_columns];
	for (std::int32_t i = 0; i < this->_rows; ++i)
		for (std::int32_t j = 0; j < this->_columns; ++j)
			this->_matrix[i][j] = *(double *)(arr + j + i * columns);
}
mth::Matrix::Matrix(std::int32_t rows, std::int32_t columns)
{
	this->_rows = rows;
	this->_columns = columns;
	this->_matrix = new double *[this->_rows];
	for (std::int32_t i = 0; i < this->_rows; ++i)
		_matrix[i] = new double[this->_columns];
	for (std::int32_t i = 0; i < this->_rows; ++i)
		for (std::int32_t j = 0; j < this->_columns; ++j)
			this->_matrix[i][j] = 0;
}
mth::Matrix::Matrix(std::int32_t rows, std::int32_t columns, std::initializer_list<double> array)
{
	this->_rows = rows;
	this->_columns = columns;
	this->_matrix = new double *[this->_rows];
	for (std::int32_t i = 0; i < this->_rows; ++i)
		_matrix[i] = new double[this->_columns];
	std::initializer_list<double>::iterator el = array.begin();
	for (std::int32_t i = 0; i < this->_rows; ++i)
		for (std::int32_t j = 0; j < this->_columns; ++j)
			_matrix[i][j] = *el++;
		
}
mth::Matrix::~Matrix()
{
	for (std::int32_t i = 0; i < this->_rows; ++i)
		delete[] this->_matrix[i];
	delete[] this->_matrix;
}

mth::Matrix mth::Matrix::operator+(const mth::Matrix &matrix_2) const
{
	if (this->_rows != matrix_2._rows || this->_columns != matrix_2._columns)
		throw "incorrect sizes";
	mth::Matrix result{this->_rows, this->_columns};
	for (std::int32_t i = 0; i < this->_rows; ++i)
		for (std::int32_t j = 0; j < this->_columns; ++j)
			result._matrix[i][j] = this->_matrix[i][j] + matrix_2._matrix[i][j];
	return result;
}
mth::Matrix mth::Matrix::operator+=(const mth::Matrix &matrix_2)
{
	return *this = *this + matrix_2;
}
mth::Matrix mth::Matrix::operator-(const mth::Matrix &matrix_2) const
{
	if (this->_rows != matrix_2._rows || this->_columns != matrix_2._columns)
		throw "incorrect sizes";
	mth::Matrix result{this->_rows, this->_columns};
	for (std::int32_t i = 0; i < this->_rows; ++i)
		for (std::int32_t j = 0; j < this->_columns; ++j)
			result._matrix[i][j] = this->_matrix[i][j] - matrix_2._matrix[i][j];
	return result;
}
mth::Matrix mth::Matrix::operator-=(const mth::Matrix &matrix_2)
{
	return *this = *this - matrix_2;
}
mth::Matrix mth::Matrix::operator*(const mth::Matrix &matrix_2) const
{
	if (this->_columns != matrix_2._rows)
		throw "incorrect sizes";
	mth::Matrix result{this->_rows, matrix_2._columns};
	for (std::int32_t i = 0; i < this->_rows; ++i)
		for (std::int32_t j = 0; j < matrix_2._columns; ++j)
			for (std::int32_t k = 0; k < this->_columns; ++k)
				result._matrix[i][j] += this->_matrix[i][k] * matrix_2._matrix[k][j];
	return result;
}
mth::Matrix mth::Matrix::operator*=(const mth::Matrix &matrix_2)
{
	return *this = *this * matrix_2;
}
mth::Matrix mth::Matrix::operator*(double k) const
{
	mth::Matrix result{_rows, _columns};
	for (std::int32_t i = 0; i < this->_rows; ++i)
		for (std::int32_t j = 0; j < this->_columns; ++j)
			result._matrix[i][j] = this->_matrix[i][j] * k;
	return result;
}
mth::Matrix mth::Matrix::operator*=(double k)
{
	return *this = *this * k;
}
mth::Matrix mth::Matrix::operator/(double k) const
{
	mth::Matrix result{_rows, _columns};
	for (std::int32_t i = 0; i < this->_rows; ++i)
		for (std::int32_t j = 0; j < this->_columns; ++j)
			result._matrix[i][j] = this->_matrix[i][j] / k;
	return result;
}
mth::Matrix mth::Matrix::operator/=(double k)
{
	return *this = *this / k;
}
bool mth::Matrix::operator==(const mth::Matrix &matrix_2) const
{
	if (this->_rows != matrix_2._rows || this->_columns != matrix_2._columns)
		return false;
	for (std::int32_t i = 0; i < this->_rows; ++i)
		for (std::int32_t j = 0; j < this->_columns; ++j)
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
	if (_rows != _columns)
		throw "incorrect sizes";
	if (_rows == 1)
		return _matrix[0][0];
	if (_rows == 2)
		return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
	if (_rows == 3)
		return _matrix[0][0] * _matrix[1][1] * _matrix[2][2] + _matrix[0][1] * _matrix[1][2] * _matrix[2][0] + _matrix[0][2] * _matrix[1][0] * _matrix[2][1] - _matrix[0][2] * _matrix[1][1] * _matrix[2][0] - _matrix[0][1] * _matrix[1][0] * _matrix[2][2] - _matrix[0][0] * _matrix[1][2] * _matrix[2][1];
	double res = 0;
	for (int i = 0; i < _rows; ++i)
		res += getAlg(0, i) * _matrix[0][i];
	return res;
}
double mth::Matrix::M(std::int32_t row, std::int32_t column) const
{
	return getSubMatrix(row, column).det();
}
mth::Matrix mth::Matrix::getSubMatrix(std::int32_t row, std::int32_t column) const
{
	if (row >= _rows || column >= _columns)
		throw "incorrect sizes";
	mth::Matrix result{_rows - 1, _columns - 1};
	for (std::int32_t i = 0; i < this->_rows; ++i)
		for (std::int32_t j = 0; j < this->_columns; ++j)
			if (i == row || j == column)
				continue;
			else
				result._matrix[i - static_cast<std::int32_t>(i >= row)][j - static_cast<std::int32_t>(j >= column)] = _matrix[i][j];
	return result;
}
mth::Matrix mth::Matrix::getAlgMatrix() const
{
	mth::Matrix result{_rows, _columns};
	for (std::int32_t i = 0; i < this->_rows; ++i)
		for (std::int32_t j = 0; j < this->_columns; ++j)
			result._matrix[i][j] = getAlg(i, j);
	return result;
}
double mth::Matrix::getAlg(std::int32_t row, std::int32_t column) const
{
	return (1 - ((row + column) & 1) * 2) * M(row, column);
}
mth::Matrix mth::Matrix::T() const
{
	mth::Matrix result{_columns, _rows};
	for (std::int32_t i = 0; i < _columns; ++i)
		for (std::int32_t j = 0; j < _rows; ++j)
		{
			result._matrix[i][j] = _matrix[j][i];
		}
	return result;
}
mth::Matrix mth::Matrix::Inverse() const
{
	return this->getAlgMatrix().T() / this->det();
}
double mth::Matrix::getEl(std::int32_t row, std::int32_t column) const
{
	if (row >= _rows || row < 0 || column >= _columns || column < 0)
		throw "incorrect index";
	return _matrix[row][column];
}
std::string mth::Matrix::ToString() const
{
	std::string **string = new std::string *[_rows];
	for (std::int32_t i = 0; i < _rows; ++i)
		string[i] = new std::string[_columns];
	std::int32_t *column_size = new std::int32_t[_columns];
	for (std::int32_t i = 0; i < _columns; ++i)
		column_size[i] = 0;
	for (std::int32_t i = 0; i < _rows; ++i)
		for (std::int32_t j = 0; j < _columns; ++j)
		{
			string[i][j] = std::to_string(_matrix[i][j]);
			if (string[i][j].length() > column_size[j])
				column_size[j] = static_cast<std::int32_t>(string[i][j].length());
		}
	for (std::int32_t i = 0; i < _rows; ++i)
		for (std::int32_t j = 0; j < _columns; ++j)
		{
			std::int32_t length = static_cast<std::int32_t>(string[i][j].length());
			for (std::int32_t k = 0; k < column_size[j] - length; ++k)
				string[i][j] += ' ';
		}
	std::string result = "";
	for (std::int32_t i = 0; i < _rows; ++i)
	{
		for (std::int32_t j = 0; j < _columns; ++j)
			result += string[i][j] + ' ';
		result += '\n';
	}
	result.pop_back();
	for (std::int32_t i = 0; i < _rows; ++i)
		delete[] string[i];
	delete[] string;
	delete[] column_size;
	return result;
}
std::ostream &operator<<(std::ostream &str, const mth::Matrix &matrix)
{
	return str << matrix.ToString();
}
