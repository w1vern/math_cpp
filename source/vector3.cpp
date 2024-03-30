#include "../include/vector3.h"
#include <cmath>
#include <string>

mth::Vector3::Vector3(double x, double y, double z) : _x(x), _y(y), _z(z) {}

mth::Vector3 mth::Vector3::operator+(const mth::Vector3& vec) const
{
	return mth::Vector3{ _x + vec._x, _y + vec._y, _z + vec._z };
}
mth::Vector3 mth::Vector3::operator+=(const mth::Vector3& vec)
{
	return *this = *this + vec;
}
mth::Vector3 mth::Vector3::operator-(const mth::Vector3& vec) const
{
	return mth::Vector3{ _x - vec._x, _y - vec._y, _z - vec._z };
}
mth::Vector3 mth::Vector3::operator-=(const mth::Vector3& vec)
{
	return *this = *this - vec;
}
double mth::Vector3::operator*(const mth::Vector3& vec) const
{
	return _x * vec._x + _y * vec._y + _z * vec._z;
}
mth::Vector3 mth::Vector3::operator*(double k) const
{
	return mth::Vector3{ _x * k, _y * k, _z * k };
}
mth::Vector3 mth::Vector3::operator*=(double k)
{
	return *this = *this * k;
}
mth::Vector3 mth::Vector3::operator/(double k) const
{
	return mth::Vector3{ _x / k, _y / k, _z / k };
}
mth::Vector3 mth::Vector3::operator/=(double k)
{
	return *this = *this / k;
}
mth::Vector3 mth::Vector3::operator^(const mth::Vector3& vec) const
{
	return mth::Vector3{ _y * vec._z - vec._y * _z,
		vec._x * _z - _x * vec._z,
		_x * vec._y - vec._x * _y };
}
mth::Vector3 mth::Vector3::operator^=(const mth::Vector3& vec)
{
	return *this = *this ^ vec;
}
mth::Vector3 mth::Vector3::operator-() const
{
	return mth::Vector3{ -_x, -_y, -_z };
}

double mth::Vector3::getX()
{
	return _x;
}
double mth::Vector3::getY()
{
	return _y;
}
double mth::Vector3::getZ()
{
	return _z;
}
double mth::Vector3::length() const
{
	return std::sqrt(_x * _x + _y * _y + _z * _z);
}
std::string mth::Vector3::ToString() const
{
	return std::string{ std::to_string(_x) + ' ' + std::to_string(_y) + ' ' + std::to_string(_z)};
}
std::ostream& operator <<(std::ostream& str, const mth::Vector3& vec)
{
	return str << vec.ToString();
}
