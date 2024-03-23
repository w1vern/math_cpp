#include <cstdint>
#include <iostream>

class Matrix
{
public:
    Matrix(void* arr, std::uint32_t rows, std::uint32_t columns);
    Matrix(std::uint32_t rows, std::uint32_t columns);
    Matrix(const Matrix& matrix);
    ~Matrix();

    Matrix operator +(Matrix matrix_2);
    Matrix operator +=(Matrix matrix_2);
    Matrix operator -(Matrix matrix_2);
    Matrix operator -=(Matrix matrix_2);
    Matrix operator *(Matrix matrix_2);
    Matrix operator *=(Matrix matrix_2);
    Matrix operator *(double k);
    Matrix operator *=(double k);
    Matrix operator /(double k);
    Matrix operator /=(double k);
    bool operator ==(Matrix matrix_2);
    bool operator !=(Matrix matrix_2);

    double det();
    double M(std::uint32_t row, std::uint32_t column);
    Matrix getSubMatrix(std::uint32_t row, std::uint32_t column);
    Matrix getAlgMatrix();
    double getAlg(std::uint32_t row, std::uint32_t column);
    Matrix T();
    Matrix Inverse();

    std::string ToString();

    friend std::ostream& operator <<(std::ostream& str, const Matrix& matrix); 

    private:
    double **matrix;
    std::uint32_t rows;
    std::uint32_t columns;
};