#include <matrix.h>
#include <string>

namespace mth
{

	Matrix::Matrix() : Matrix(1, 1) {}
	Matrix::Matrix(double **arr, std::int32_t rows, std::int32_t columns)
	{
		this->_rows = rows;
		this->_columns = columns;
		for (std::int32_t i = 0; i < this->_rows; ++i)
		{
			this->_matrix.push_back(std::vector<double>{});
			for (std::int32_t j = 0; j < this->_columns; ++j)
				this->_matrix[i].push_back(*(double *)(arr + j + i * columns));
		}
	}
	Matrix::Matrix(std::int32_t rows, std::int32_t columns)
	{
		this->_rows = rows;
		this->_columns = columns;
		for (std::int32_t i = 0; i < this->_rows; ++i)
		{
			this->_matrix.push_back(std::vector<double>{});
			for (std::int32_t j = 0; j < this->_columns; ++j)
				this->_matrix[i].push_back(0);
		}
	}
	Matrix::Matrix(std::int32_t rows, std::int32_t columns, std::initializer_list<double> array)
	{
		this->_rows = rows;
		this->_columns = columns;
		std::initializer_list<double>::iterator el = array.begin();
		for (std::int32_t i = 0; i < this->_rows; ++i)
		{
			this->_matrix.push_back(std::vector<double>{});
			for (std::int32_t j = 0; j < this->_columns; ++j)
				this->_matrix[i].push_back(*el++);
		}
	}
	Matrix::Matrix(const Matrix &origin)
	{
		this->_columns = origin._columns;
		this->_rows = origin._rows;
		for (auto i = origin._matrix.begin(); i < origin._matrix.end(); ++i)
		{
			this->_matrix.push_back(std::vector<double>{});
			for (auto j = i->begin(); j < i->end(); ++j)
				this->_matrix.back().push_back(*j);
		}
	}
	Matrix::Matrix(Matrix &&moved)
	{
		this->_matrix = moved._matrix;
		this->_rows = moved._rows;
		this->_columns = moved._columns;
		moved._matrix = std::vector<std::vector<double>>{};
	}
	Matrix::~Matrix()
	{
		for (std::vector<std::vector<double>>::iterator iter = _matrix.begin(); iter < _matrix.end(); ++iter)
			iter->clear();
		_matrix.clear();
	}

	Matrix Matrix::operator+(const Matrix &matrix_2) const
	{
		if (this->_rows != matrix_2._rows || this->_columns != matrix_2._columns)
			throw "incorrect sizes";
		mth::Matrix result{this->_rows, this->_columns};
		for (std::int32_t i = 0; i < this->_rows; ++i)
			for (std::int32_t j = 0; j < this->_columns; ++j)
				result._matrix[i][j] = this->_matrix[i][j] + matrix_2._matrix[i][j];
		return result;
	}
	Matrix mth::Matrix::operator+=(const Matrix &matrix_2)
	{
		return *this = *this + matrix_2;
	}
	Matrix mth::Matrix::operator-(const Matrix &matrix_2) const
	{
		if (this->_rows != matrix_2._rows || this->_columns != matrix_2._columns)
			throw "incorrect sizes";
		mth::Matrix result{this->_rows, this->_columns};
		for (std::int32_t i = 0; i < this->_rows; ++i)
			for (std::int32_t j = 0; j < this->_columns; ++j)
				result._matrix[i][j] = this->_matrix[i][j] - matrix_2._matrix[i][j];
		return result;
	}
	Matrix mth::Matrix::operator-=(const Matrix &matrix_2)
	{
		return *this = *this - matrix_2;
	}
	Matrix mth::Matrix::operator*(const Matrix &matrix_2) const
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
	Matrix mth::Matrix::operator*=(const Matrix &matrix_2)
	{
		return *this = *this * matrix_2;
	}
	Matrix mth::Matrix::operator*(double k) const
	{
		mth::Matrix result{_rows, _columns};
		for (std::int32_t i = 0; i < this->_rows; ++i)
			for (std::int32_t j = 0; j < this->_columns; ++j)
				result._matrix[i][j] = this->_matrix[i][j] * k;
		return result;
	}
	Matrix mth::Matrix::operator*=(double k)
	{
		return *this = *this * k;
	}
	Matrix mth::Matrix::operator/(double k) const
	{
		mth::Matrix result{_rows, _columns};
		for (std::int32_t i = 0; i < this->_rows; ++i)
			for (std::int32_t j = 0; j < this->_columns; ++j)
				result._matrix[i][j] = this->_matrix[i][j] / k;
		return result;
	}
	Matrix mth::Matrix::operator/=(double k)
	{
		return *this = *this / k;
	}
	bool Matrix::operator==(const Matrix &matrix_2) const
	{
		if (this->_rows != matrix_2._rows || this->_columns != matrix_2._columns)
			return false;
		for (std::int32_t i = 0; i < this->_rows; ++i)
			for (std::int32_t j = 0; j < this->_columns; ++j)
				if (this->_matrix[i][j] != matrix_2._matrix[i][j])
					return false;
		return true;
	}
	bool Matrix::operator!=(const Matrix &matrix_2) const
	{
		return !(*this == matrix_2);
	}

	const Matrix &Matrix::operator=(const Matrix &origin)
	{
		this->_matrix.clear();
		this->_columns = origin._columns;
		this->_rows = origin._rows;
		for (auto i = origin._matrix.begin(); i < origin._matrix.end(); ++i)
		{
			this->_matrix.push_back(std::vector<double>{});
			for (auto j = i->begin(); j < i->end(); ++j)
				this->_matrix.back().push_back(*j);
		}
		return *this;
	}
	const Matrix &Matrix::operator=(Matrix &&moved)
	{
		this->_matrix.clear();
		this->_matrix = moved._matrix;
		this->_rows = moved._rows;
		this->_columns = moved._columns;
		moved._matrix = std::vector<std::vector<double>>{};
		return *this;
	}

	double Matrix::det() const
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
			res += get_alg(0, i) * _matrix[0][i];
		return res;
	}
	double Matrix::M(std::int32_t row, std::int32_t column) const
	{
		return get_submatrix(row, column).det();
	}
	Matrix Matrix::get_submatrix(std::int32_t row, std::int32_t column) const
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
	Matrix Matrix::get_alg_matrix() const
	{
		mth::Matrix result{_rows, _columns};
		for (std::int32_t i = 0; i < this->_rows; ++i)
			for (std::int32_t j = 0; j < this->_columns; ++j)
				result._matrix[i][j] = get_alg(i, j);
		return result;
	}
	double Matrix::get_alg(std::int32_t row, std::int32_t column) const
	{
		return (1 - ((row + column) & 1) * 2) * M(row, column);
	}
	Matrix Matrix::T() const
	{
		mth::Matrix result{_columns, _rows};
		for (std::int32_t i = 0; i < _columns; ++i)
			for (std::int32_t j = 0; j < _rows; ++j)
			{
				result._matrix[i][j] = _matrix[j][i];
			}
		return result;
	}
	Matrix Matrix::get_inverse() const
	{
		return this->get_alg_matrix().T() / this->det();
	}
	double Matrix::el_by_index(std::int32_t row, std::int32_t column) const
	{
		if (row >= _rows || row < 0 || column >= _columns || column < 0)
			throw "incorrect index";
		return _matrix[row][column];
	}

	Vector2 Matrix::to_vector2() const
	{
		if (_rows == 2 && _columns == 1)
			return Vector2(_matrix[0][0], _matrix[1][0]);
		if (_rows == 1 && _columns == 2)
			return Vector2(_matrix[0][0], _matrix[0][1]);
		throw "not possible to transform this matrix into Vector2";
	}
	Vector3 Matrix::to_vector3() const
	{
		if (_rows == 3 && _columns == 1)
			return Vector3(_matrix[0][0], _matrix[1][0], _matrix[2][0]);
		if (_rows == 1 && _columns == 3)
			return Vector3(_matrix[0][0], _matrix[0][1], _matrix[0][2]);
		throw "not possible to transform this matrix into Vector3";
	}
	std::string Matrix::to_string() const
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
	std::ostream &operator<<(std::ostream &str, const Matrix &matrix)
	{
		return str << matrix.to_string();
	}
}