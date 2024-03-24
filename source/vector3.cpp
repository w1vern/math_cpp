#include "vector3.h"
#include <cmath>
#include <string>

mth::Vector3::Vector3(double x, double y, double z) : _X(x), _Y(y), _Z(z) {}

mth::Vector3 mth::Vector3::operator+(const mth::Vector3& vec) const
{
	return mth::Vector3{ _X + vec._X, _Y + vec._Y, _Z + vec._Z };
}
mth::Vector3 mth::Vector3::operator+=(const mth::Vector3& vec)
{
	return *this = *this + vec;
}
mth::Vector3 mth::Vector3::operator-(const mth::Vector3& vec) const
{
	return mth::Vector3{ _X - vec._X, _Y - vec._Y, _Z - vec._Z };
}
mth::Vector3 mth::Vector3::operator-=(const mth::Vector3& vec)
{
	return *this = *this - vec;
}
double mth::Vector3::operator*(const mth::Vector3& vec) const
{
	return _X * vec._X + _Y * vec._Y + _Z * vec._Z;
}
mth::Vector3 mth::Vector3::operator*(double k) const
{
	return mth::Vector3{ _X * k, _Y * k, _Z * k };
}
mth::Vector3 mth::Vector3::operator*=(double k)
{
	return *this = *this * k;
}
mth::Vector3 mth::Vector3::operator/(double k) const
{
	return mth::Vector3{ _X / k, _Y / k, _Z / k };
}
mth::Vector3 mth::Vector3::operator/=(double k)
{
	return *this = *this / k;
}
mth::Vector3 mth::Vector3::operator^(const mth::Vector3& vec) const
{
	return mth::Vector3{ _Y * vec._Z - vec._Y * _Z,
		vec._X * _Z - _X * vec._Z,
		_X * vec._Y - vec._X * _Y };
}
mth::Vector3 mth::Vector3::operator^=(const mth::Vector3& vec)
{
	return *this = *this ^ vec;
}
mth::Vector3 mth::Vector3::operator-() const
{
	return mth::Vector3{ -_X, -_Y, -_Z };
}

double mth::Vector3::length() const
{
	return std::sqrt(_X * _X + _Y * _Y + _Z * _Z);
}
std::string mth::Vector3::ToString() const
{
	return std::string{ std::to_string(_X) + ' ' + std::to_string(_Y) + ' ' + std::to_string(_Z)};
}
std::ostream& operator <<(std::ostream& str, const mth::Vector3& vec)
{
	return str << vec.ToString();
}
