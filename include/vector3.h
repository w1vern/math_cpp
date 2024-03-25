#pragma once
#include <iostream>
#include <cstdint>
namespace mth {
    class Vector3 {
    public:
        Vector3(double x, double y, double z);

        Vector3 operator+(const Vector3&) const;
        Vector3 operator+=(const Vector3&);
        Vector3 operator-(const Vector3&) const;
        Vector3 operator-=(const Vector3&);
        double operator*(const Vector3&) const;
        Vector3 operator*(double) const;
        Vector3 operator*=(double);
        Vector3 operator/(double) const;
        Vector3 operator/=(double);
        Vector3 operator^(const Vector3&) const;
        Vector3 operator^=(const Vector3&);
        Vector3 operator-() const;

        double length() const;
        std::string ToString() const;
        friend std::ostream& operator <<(std::ostream&, const Vector3&);

    private:
        double _X;
        double _Y;
        double _Z;
    };
}