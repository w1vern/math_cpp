#include "../include/vector2.h"
#include <cmath>
#include <string>

mth::Vector2::Vector2() : Vector2(0, 0) {}
mth::Vector2::Vector2(double x, double y) : _x(x), _y(y) {}

mth::Vector2 mth::Vector2::operator+(const mth::Vector2 &vec) const
{
	return mth::Vector2{_x + vec._x, _y + vec._y};
}
mth::Vector2 mth::Vector2::operator+=(const mth::Vector2 &vec)
{
	return *this = *this + vec;
}
mth::Vector2 mth::Vector2::operator-(const mth::Vector2 &vec) const
{
	return mth::Vector2{_x - vec._x, _y - vec._y};
}
mth::Vector2 mth::Vector2::operator-=(const mth::Vector2 &vec)
{
	return *this = *this - vec;
}
double mth::Vector2::operator*(const mth::Vector2 &vec) const
{
	return _x * vec._x + _y * vec._y;
}
mth::Vector2 mth::Vector2::operator*(double k) const
{
	return mth::Vector2{_x * k, _y * k};
}
mth::Vector2 mth::Vector2::operator*=(double k)
{
	return *this = *this * k;
}
mth::Vector2 mth::Vector2::operator/(double k) const
{
	return mth::Vector2{_x / k, _y / k};
}
mth::Vector2 mth::Vector2::operator/=(double k)
{
	return *this = *this / k;
}
mth::Vector2 mth::Vector2::operator-() const
{
	return mth::Vector2{-_x, -_y};
}

double mth::Vector2::getX() const
{
	return _x;
}
double mth::Vector2::getY() const
{
	return _y;
}
double mth::Vector2::length() const
{
	return std::sqrt(_x * _x + _y * _y);
}
std::string mth::Vector2::ToString() const
{
	return std::string{std::to_string(_x) + ' ' + std::to_string(_y)};
}
std::ostream &operator<<(std::ostream &str, const mth::Vector2 &vec)
{
	return str << vec.ToString();
}
