#pragma once
#include <iostream>
#include <cstdint>
#include <matrix.h>
namespace mth {
    class Vector2 {
    public:
        Vector2();
        Vector2(double x, double y);
        Vector2(const Vector2& origin);
        Vector2(Vector2&& moved);

        Vector2 operator+(const Vector2&) const;
        Vector2 operator+=(const Vector2&);
        Vector2 operator-(const Vector2&) const;
        Vector2 operator-=(const Vector2&);
        double operator*(const Vector2&) const;
        Vector2 operator*(double) const;
        Vector2 operator*=(double);
        Vector2 operator/(double) const;
        Vector2 operator/=(double);
        Vector2 operator-() const;

        Vector2 operator=(const Vector2& origin);
        Vector2 operator=(Vector2&& moved);

        double x() const;
        double y() const;
        double length() const;

        Matrix to_matrix() const;
        std::string to_string() const;
        friend std::ostream& operator <<(std::ostream&, const Vector2&);

    private:
        double _x;
        double _y;
    };
}