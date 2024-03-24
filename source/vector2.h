#pragma once
#include <iostream>
#include <cstdint>
namespace mth {
    class Vector2 {
    public:
        Vector2(double x, double y);

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

        double length() const;
        std::string ToString() const;
        friend std::ostream& operator <<(std::ostream&, const Vector2&);

    private:
        double _X;
        double _Y;
    };
}