#include <vector3.h>
#include <cmath>
#include <string>

namespace mth
{

	Vector3::Vector3() : Vector3(0, 0, 0) {}
	Vector3::Vector3(double x, double y, double z) : _x(x), _y(y), _z(z) {}

	Vector3::Vector3(const Vector3& origin)
	{
		this->_x = origin._x;
		this->_y = origin._y;
		this->_z = origin._z;
	}
	Vector3::Vector3(Vector3&& moved)
	{
		this->_x = moved._x;
		this->_y = moved._y;
		this->_z = moved._z;
	}

	Vector3 Vector3::operator+(const Vector3 &vec) const
	{
		return Vector3{_x + vec._x, _y + vec._y, _z + vec._z};
	}
	Vector3 Vector3::operator+=(const Vector3 &vec)
	{
		return *this = *this + vec;
	}
	Vector3 Vector3::operator-(const Vector3 &vec) const
	{
		return Vector3{_x - vec._x, _y - vec._y, _z - vec._z};
	}
	Vector3 Vector3::operator-=(const Vector3 &vec)
	{
		return *this = *this - vec;
	}
	double Vector3::operator*(const Vector3 &vec) const
	{
		return _x * vec._x + _y * vec._y + _z * vec._z;
	}
	Vector3 Vector3::operator*(double k) const
	{
		return Vector3{_x * k, _y * k, _z * k};
	}
	Vector3 Vector3::operator*=(double k)
	{
		return *this = *this * k;
	}
	Vector3 Vector3::operator/(double k) const
	{
		return Vector3{_x / k, _y / k, _z / k};
	}
	Vector3 Vector3::operator/=(double k)
	{
		return *this = *this / k;
	}
	Vector3 Vector3::operator^(const Vector3 &vec) const
	{
		return Vector3{_y * vec._z - vec._y * _z,
							vec._x * _z - _x * vec._z,
							_x * vec._y - vec._x * _y};
	}
	Vector3 Vector3::operator^=(const Vector3 &vec)
	{
		return *this = *this ^ vec;
	}
	Vector3 Vector3::operator-() const
	{
		return Vector3{-_x, -_y, -_z};
	}

	Vector3 Vector3::operator=(const Vector3& origin)
	{
		this->_x = origin._x;
		this->_y = origin._y;
		this->_z = origin._z;
		return *this;
	}
	Vector3 Vector3::operator=(Vector3&& moved)
	{
		this->_x = moved._x;
		this->_y = moved._y;
		this->_z = moved._z;
		return *this;
	}

	double Vector3::x() const
	{
		return _x;
	}
	double Vector3::y() const
	{
		return _y;
	}
	double Vector3::z() const
	{
		return _z;
	}
	double Vector3::length() const
	{
		return std::sqrt(_x * _x + _y * _y + _z * _z);
	}
	Matrix Vector3::to_matrix() const 
	{
		return Matrix{1, 3, {_x, _y, _z}};
	}
	std::string Vector3::to_string() const
	{
		return std::string{std::to_string(_x) + ' ' + std::to_string(_y) + ' ' + std::to_string(_z)};
	}
	std::ostream &operator<<(std::ostream &str, const Vector3 &vec)
	{
		return str << vec.to_string();
	}
}
