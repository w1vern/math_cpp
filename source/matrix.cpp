#include "dmath.h"
#include <string>

Matrix::Matrix(double **arr, std::int32_t rows, std::int32_t columns)
{
	this->rows = rows;
	this->columns = columns;
	this->matrix = new double *[this->rows];
	for (std::int32_t i = 0; i < this->rows; ++i)
		this->matrix[i] = new double[this->columns];
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
		{
			this->matrix[i][j] = *(double *)(arr + j + i * columns);
		}
}
Matrix::Matrix(std::int32_t rows, std::int32_t columns)
{
	this->rows = rows;
	this->columns = columns;
	this->matrix = new double *[this->rows];
	for (std::int32_t i = 0; i < this->rows; ++i)
		matrix[i] = new double[this->columns];
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			this->matrix[i][j] = 0;
}
Matrix::~Matrix()
{
	for (std::int32_t i = 0; i < this->rows; ++i)
		delete[] this->matrix[i];
	delete[] this->matrix;
}

Matrix Matrix::operator+(const Matrix &matrix_2) const
{
	if (this->rows != matrix_2.rows || this->columns != matrix_2.columns)
		throw "incorrect sizes";
	Matrix result{this->rows, this->columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			result.matrix[i][j] = this->matrix[i][j] + matrix_2.matrix[i][j];
	return result;
}
Matrix Matrix::operator+=(const Matrix &matrix_2)
{
	return *this = *this + matrix_2;
}
Matrix Matrix::operator-(const Matrix &matrix_2) const
{
	if (this->rows != matrix_2.rows || this->columns != matrix_2.columns)
		throw "incorrect sizes";
	Matrix result{this->rows, this->columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			result.matrix[i][j] = this->matrix[i][j] - matrix_2.matrix[i][j];
	return result;
}
Matrix Matrix::operator-=(const Matrix &matrix_2)
{
	return *this = *this - matrix_2;
}
Matrix Matrix::operator*(const Matrix &matrix_2) const
{
	if (this->columns != matrix_2.rows)
		throw "incorrect sizes";
	Matrix result{this->rows, matrix_2.columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < matrix_2.columns; ++j)
			for (std::int32_t k = 0; k < this->columns; ++k)
				result.matrix[i][j] += this->matrix[i][k] * matrix_2.matrix[k][j];
	return result;
}
Matrix Matrix::operator*=(const Matrix &matrix_2)
{
	return *this = *this * matrix_2;
}
Matrix Matrix::operator*(double k) const
{
	Matrix result{rows, columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			result.matrix[i][j] = this->matrix[i][j] * k;
	return result;
}
Matrix Matrix::operator*=(double k)
{
	return *this = *this * k;
}
Matrix Matrix::operator/(double k) const
{
	Matrix result{rows, columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			result.matrix[i][j] = this->matrix[i][j] / k;
	return result;
}
Matrix Matrix::operator/=(double k)
{
	return *this = *this / k;
}
bool Matrix::operator==(const Matrix &matrix_2) const
{
	if (this->rows != matrix_2.rows || this->columns != matrix_2.columns)
		return false;
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			if (this->matrix[i][j] != matrix_2.matrix[i][j])
				return false;
	return true;
}
bool Matrix::operator!=(const Matrix &matrix_2) const
{
	return !(*this == matrix_2);
}

double Matrix::det() const
{
	if (rows != columns)
		throw "incorrect sizes";
	if (rows == 1)
		return matrix[0][0];
	if (rows == 2)
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	if (rows == 3)
		return matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][1] * matrix[1][0] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1];
	double res = 0;
	for (int i = 0; i < rows; ++i)
		res += getAlg(0, i) * matrix[0][i];
	return res;
}
double Matrix::M(std::int32_t row, std::int32_t column) const
{
	return getSubMatrix(row, column).det();
}
Matrix Matrix::getSubMatrix(std::int32_t row, std::int32_t column) const
{
	if (row >= rows || column >= columns)
		throw "incorrect sizes";
	Matrix result{rows - 1, columns - 1};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			if (i == row || j == column)
				continue;
			else
				result.matrix[i - static_cast<std::int32_t>(i >= row)][j - static_cast<std::int32_t>(j >= column)] = matrix[i][j];
	return result;
}
Matrix Matrix::getAlgMatrix() const
{
	Matrix result{rows, columns};
	for (std::int32_t i = 0; i < this->rows; ++i)
		for (std::int32_t j = 0; j < this->columns; ++j)
			result.matrix[i][j] = getAlg(i, j);
	return result;
}
double Matrix::getAlg(std::int32_t row, std::int32_t column) const
{
	return (1 - ((row + column) & 1) * 2) * M(row, column);
}
Matrix Matrix::T() const
{
	Matrix result{columns, rows};
	for (std::int32_t i = 0; i < columns; ++i)
		for (std::int32_t j = 0; j < rows; ++j)
		{
			result.matrix[i][j] = matrix[j][i];
		}
	return result;
}
Matrix Matrix::Inverse() const
{
	return this->getAlgMatrix().T() / this->det();
}

std::string Matrix::ToString() const
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
			string[i][j] = std::to_string(matrix[i][j]);
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

std::ostream &operator<<(std::ostream &str, const Matrix &matrix)
{
	return str << matrix.ToString();
}



Vector3d::Vector3d(double arr[], std::int32_t length)
{

}

Vector3d Vector3d::operator+(const Vector3d&) const
{

}
Vector3d Vector3d::operator+=(const Vector3d&)
{

}
Vector3d Vector3d::operator-(const Vector3d&) const
{

}
Vector3d Vector3d::operator-=(const Vector3d&)
{

}
double Vector3d::operator*(const Vector3d&) const
{

}
Vector3d Vector3d::operator*(double) const
{

}
Vector3d Vector3d::operator*=(double)
{

}
Vector3d Vector3d::operator/(double) const
{

}
Vector3d Vector3d::operator/=(double)
{

}
Vector3d Vector3d::operator^(const Vector3d&) const
{

}
Vector3d Vector3d::operator^=(const Vector3d&)
{

}
Vector3d Vector3d::operator-() const
{

}

double Vector3d::lenght() const
{

}