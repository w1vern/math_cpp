#pragma once
#include <iostream>
#include <cstdint>
namespace mth {
    class Vector3 {
    public:
        Vector3();
        Vector3(double x, double y, double z);
        Vector3(const Vector3& origin);
        Vector3(Vector3&& moved);

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

        Vector3 operator=(const Vector3& origin);
        Vector3 operator=(Vector3&& moved);

        double getX() const;
        double getY() const;
        double getZ() const;
        double length() const;
        std::string ToString() const;
        friend std::ostream& operator <<(std::ostream&, const Vector3&);

    private:
        double _x;
        double _y;
        double _z;
    };
}