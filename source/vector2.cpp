#include "../include/vector2.h"
#include <cmath>
#include <string>

mth::Vector2::Vector2(double x, double y) : _X(x), _Y(y) {}

mth::Vector2 mth::Vector2::operator+(const mth::Vector2& vec) const
{
	return mth::Vector2{ _X + vec._X, _Y + vec._Y };
}
mth::Vector2 mth::Vector2::operator+=(const mth::Vector2& vec)
{
	return *this = *this + vec;
}
mth::Vector2 mth::Vector2::operator-(const mth::Vector2& vec) const
{
	return mth::Vector2{ _X - vec._X, _Y - vec._Y };
}
mth::Vector2 mth::Vector2::operator-=(const mth::Vector2& vec)
{
	return *this = *this - vec;
}
double mth::Vector2::operator*(const mth::Vector2& vec) const
{
	return _X * vec._X + _Y * vec._Y;
}
mth::Vector2 mth::Vector2::operator*(double k) const
{
	return mth::Vector2{ _X * k, _Y * k };
}
mth::Vector2 mth::Vector2::operator*=(double k)
{
	return *this = *this * k;
}
mth::Vector2 mth::Vector2::operator/(double k) const
{
	return mth::Vector2{ _X / k, _Y / k };
}
mth::Vector2 mth::Vector2::operator/=(double k)
{
	return *this = *this / k;
}
mth::Vector2 mth::Vector2::operator-() const
{
	return mth::Vector2{ -_X, -_Y };
}

double mth::Vector2::length() const
{
	return std::sqrt(_X * _X + _Y * _Y);
}
std::string mth::Vector2::ToString() const
{
	return std::string{ std::to_string(_X) + ' ' + std::to_string(_Y) };
}
std::ostream& operator <<(std::ostream& str, const mth::Vector2& vec)
{
	return str << vec.ToString();
}
