#include "math.h"

Matrix::Matrix(void *arr, std::uint32_t rows, std::uint32_t columns)
{
    this->rows = rows;
    this->columns = columns;
    this->matrix = new double *[this->rows];
    for (std::uint32_t i = 0; i < this->rows; ++i)
        this->matrix[i] = new double[this->columns];
    for (std::uint32_t i = 0; i < this->rows; ++i)
        for (std::uint32_t j = 0; j < this->columns; ++j)
            this->matrix[i][j] = *(double *)(arr + (j + i * columns) * sizeof(double));
}
Matrix::Matrix(std::uint32_t rows, std::uint32_t columns)
{
    this->rows = rows;
    this->columns = columns;
    this->matrix = new double *[this->rows];
    for (std::uint32_t i = 0; i < this->rows; ++i)
        matrix[i] = new double[this->columns];
    for (std::uint32_t i = 0; i < this->rows; ++i)
        for (std::uint32_t j = 0; j < this->columns; ++j)
            this->matrix[i][j] = 0;
}
Matrix::~Matrix()
{
    /*  for (std::uint32_t i = 0; i < this->rows; ++i)
         delete[] this->matrix[i];
     delete[] this->matrix; */
}

Matrix Matrix::operator+(const Matrix& matrix_2) const
{
    if (this->rows != matrix_2.rows || this->columns != matrix_2.columns)
        throw "incorrect sizes";
    Matrix result{this->rows, this->columns};
    for (std::uint32_t i = 0; i < this->rows; ++i)
        for (std::uint32_t j = 0; j < this->columns; ++j)
            result.matrix[i][j] = this->matrix[i][j] + matrix_2.matrix[i][j];
    return result;
}
Matrix Matrix::operator+=(const Matrix& matrix_2)
{
    return *this = *this + matrix_2;
}
Matrix Matrix::operator-(const Matrix& matrix_2) const
{
    if (this->rows != matrix_2.rows || this->columns != matrix_2.columns)
        throw "incorrect sizes";
    Matrix result{this->rows, this->columns};
    for (std::uint32_t i = 0; i < this->rows; ++i)
        for (std::uint32_t j = 0; j < this->columns; ++j)
            result.matrix[i][j] = this->matrix[i][j] - matrix_2.matrix[i][j];
    return result;
}
Matrix Matrix::operator-=(const Matrix& matrix_2)
{
    return *this = *this - matrix_2;
}
Matrix Matrix::operator*(const Matrix& matrix_2) const
{
    if (this->columns != matrix_2.rows)
        throw "incorrect sizes";
    Matrix result{this->rows, matrix_2.columns};
    for (std::uint32_t i = 0; i < this->rows; ++i)
        for (std::uint32_t j = 0; j < matrix_2.columns; ++j)
            for (std::uint32_t k = 0; k < this->columns; ++k)
                result.matrix[i][j] += this->matrix[i][k] * matrix_2.matrix[k][j];
    return result;
}
Matrix Matrix::operator*=(const Matrix& matrix_2)
{
    return *this = *this * matrix_2;
}
Matrix Matrix::operator*(double k) const
{
    Matrix result{rows, columns};
    for (std::uint32_t i = 0; i < this->rows; ++i)
        for (std::uint32_t j = 0; j < this->columns; ++j)
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
    for (std::uint32_t i = 0; i < this->rows; ++i)
        for (std::uint32_t j = 0; j < this->columns; ++j)
            result.matrix[i][j] = this->matrix[i][j] / k;
    return result;
}
Matrix Matrix::operator/=(double k)
{
    return *this = *this / k;
}
bool Matrix::operator==(const Matrix& matrix_2) const
{
    if (this->rows != matrix_2.rows || this->columns != matrix_2.columns)
        return false;
    for (std::uint32_t i = 0; i < this->rows; ++i)
        for (std::uint32_t j = 0; j < this->columns; ++j)
            if (this->matrix[i][j] != matrix_2.matrix[i][j])
                return false;
    return true;
}
bool Matrix::operator!=(const Matrix& matrix_2) const
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
double Matrix::M(std::uint32_t row, std::uint32_t column) const
{
    return getSubMatrix(row, column).det();
}
Matrix Matrix::getSubMatrix(std::uint32_t row, std::uint32_t column) const
{
    if (row >= rows || column >= columns)
        throw "incorrect sizes";
    Matrix result{rows - 1, columns - 1};
    for (std::uint32_t i = 0; i < this->rows; ++i)
        for (std::uint32_t j = 0; j < this->columns; ++j)
            if (i == row || j == column)
                continue;
            else
                result.matrix[i - static_cast<std::uint32_t>(i >= row)][j - static_cast<std::uint32_t>(j >= column)] = matrix[i][j];
    return result;
}
Matrix Matrix::getAlgMatrix() const
{
    Matrix result{rows, columns};
    for (std::uint32_t i = 0; i < this->rows; ++i)
        for (std::uint32_t j = 0; j < this->columns; ++j)
            result.matrix[i][j] = getAlg(i, j);
    return result;
}
double Matrix::getAlg(std::uint32_t row, std::uint32_t column) const
{
    return (1 - ((row + column) & 1) * 2) * M(row, column);
}
Matrix Matrix::T() const
{
    Matrix result{columns, rows};
    for (std::uint32_t i = 0; i < columns; ++i)
        for (std::uint32_t j = 0; j < rows; ++j)
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
    for (std::uint32_t i = 0; i < rows; ++i)
        string[i] = new std::string[columns];
    std::uint32_t *column_size = new std::uint32_t[columns];
    for (std::uint32_t i = 0; i < columns; ++i)
        column_size[i] = 0;
    for (std::uint32_t i = 0; i < rows; ++i)
        for (std::uint32_t j = 0; j < columns; ++j)
        {
            string[i][j] = std::to_string(matrix[i][j]);
            if (string[i][j].length() > column_size[j])
                column_size[j] = string[i][j].length();
        }
    for (std::uint32_t i = 0; i < rows; ++i)
        for (std::uint32_t j = 0; j < columns; ++j)
        {
            std::uint32_t length = string[i][j].length();
            for (std::uint32_t k = 0; k < column_size[j] - length; ++k)
                string[i][j] += ' ';
        }
    std::string result = "";
    for (std::uint32_t i = 0; i < rows; ++i)
    {
        for (std::uint32_t j = 0; j < columns; ++j)
            result += string[i][j] + ' ';
        result += '\n';
    }
    result.pop_back();
    for (std::uint32_t i = 0; i < rows; ++i)
        delete[] string[i];
    delete[] string;
    delete[] column_size;
    return result;
}

std::ostream &operator<<(std::ostream &str, const Matrix& matrix)
{
    return str << matrix.ToString();
}

int main()
{
    double arr[][5] = {{15, 12, 3, -1, -1}, {1, 4, 5, 15, 8}, {5, 7, -11, 7, 8}, {3, 2, 1, 6, 5}, {5, 1, 1, 2, -4}};
    Matrix matrix{(double **)arr, 5, 5};
    std::cout << matrix << "\n\n" << matrix.det();

    //Matrix inv = matrix.Inverse();
    //std::cout << matrix << std::endl << inv << std::endl << matrix * inv;
    return 0;
}