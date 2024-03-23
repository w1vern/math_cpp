#include <cstdint>
#include <iostream>

class Matrix
{
public:
    Matrix(void* arr, std::uint32_t rows, std::uint32_t columns);
    Matrix(std::uint32_t rows, std::uint32_t columns);
    ~Matrix();

    Matrix operator +(const Matrix& matrix_2) const;
    Matrix operator +=(const Matrix& matrix_2);
    Matrix operator -(const Matrix& matrix_2) const;
    Matrix operator -=(const Matrix& matrix_2);
    Matrix operator *(const Matrix& matrix_2) const;
    Matrix operator *=(const Matrix& matrix_2);
    Matrix operator *(double k) const;
    Matrix operator *=(double k);
    Matrix operator /(double k) const;
    Matrix operator /=(double k);
    bool operator ==(const Matrix& matrix_2) const;
    bool operator !=(const Matrix& matrix_2) const;

    double det() const;
    double M(std::uint32_t row, std::uint32_t column) const;
    Matrix getSubMatrix(std::uint32_t row, std::uint32_t column) const;
    Matrix getAlgMatrix() const;
    double getAlg(std::uint32_t row, std::uint32_t column) const;
    Matrix T() const;
    Matrix Inverse() const;

    std::string ToString() const;

    friend std::ostream& operator <<(std::ostream& str, const Matrix& matrix); 

    //private:
    double **matrix;
    std::uint32_t rows;
    std::uint32_t columns;
};