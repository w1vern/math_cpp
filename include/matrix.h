#pragma once
#include <iostream>
#include <vector>
#include <cstdint>

namespace mth {

    class Vector2;
    class Vector3;
    class Matrix
    {
    public:
        Matrix();
        Matrix(double** arr, std::int32_t rows, std::int32_t columns);
        Matrix(std::int32_t rows, std::int32_t columns);
        Matrix(std::int32_t rows, std::int32_t columns, std::initializer_list<double>);
        Matrix(const Matrix&);
        Matrix(Matrix&&);
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
        
        const Matrix& operator=(const Matrix&);
        const Matrix& operator=(Matrix&&);

        double det() const;
        double M(std::int32_t row, std::int32_t column) const;
        Matrix get_submatrix(std::int32_t row, std::int32_t column) const;
        Matrix get_alg_matrix() const;
        double get_alg(std::int32_t row, std::int32_t column) const;
        Matrix T() const;
        Matrix get_inverse() const;
        double el_by_index(std::int32_t, std::int32_t) const;

        Vector2 to_vector2() const;
        Vector3 to_vector3() const;
        std::string to_string() const;

        friend std::ostream& operator <<(std::ostream& str, const Matrix& matrix);

    private:
        std::vector<std::vector<double>> _matrix;
        std::int32_t _rows;
        std::int32_t _columns;
    };
}