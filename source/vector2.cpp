#include "../include/vector2.h"
#include <cmath>
#include <string>

namespace mth
{
	Vector2::Vector2() : Vector2(0, 0) {}
	Vector2::Vector2(double x, double y) : _x(x), _y(y) {}
	Vector2::Vector2(const Vector2& origin)
	{	
		this->_x = origin._x;
		this->_y = origin._y;
	}
	Vector2::Vector2(Vector2&& moved)
	{
		this->_x = moved._x;
		this->_y = moved._y;
	}

	Vector2 Vector2::operator+(const Vector2 &vec) const
	{
		return Vector2{_x + vec._x, _y + vec._y};
	}
	Vector2 Vector2::operator+=(const Vector2 &vec)
	{
		return *this = *this + vec;
	}
	Vector2 Vector2::operator-(const Vector2 &vec) const
	{
		return Vector2{_x - vec._x, _y - vec._y};
	}
	Vector2 Vector2::operator-=(const Vector2 &vec)
	{
		return *this = *this - vec;
	}
	double Vector2::operator*(const Vector2 &vec) const
	{
		return _x * vec._x + _y * vec._y;
	}
	Vector2 Vector2::operator*(double k) const
	{
		return Vector2{_x * k, _y * k};
	}
	Vector2 Vector2::operator*=(double k)
	{
		return *this = *this * k;
	}
	Vector2 Vector2::operator/(double k) const
	{
		return Vector2{_x / k, _y / k};
	}
	Vector2 Vector2::operator/=(double k)
	{
		return *this = *this / k;
	}
	Vector2 Vector2::operator-() const
	{
		return Vector2{-_x, -_y};
	}

	Vector2 Vector2::operator=(const Vector2& origin)
	{	
		this->_x = origin._x;
		this->_y = origin._y;
		return *this;
	}
	Vector2 Vector2::operator=(Vector2&& moved)
	{
		this->_x = moved._x;
		this->_y = moved._y;
		return *this;
	}

	double Vector2::getX() const
	{
		return _x;
	}
	double Vector2::getY() const
	{
		return _y;
	}
	double Vector2::length() const
	{
		return std::sqrt(_x * _x + _y * _y);
	}
	std::string Vector2::ToString() const
	{
		return std::string{std::to_string(_x) + ' ' + std::to_string(_y)};
	}
	std::ostream &operator<<(std::ostream &str, const Vector2 &vec)
	{
		return str << vec.ToString();
	}
}