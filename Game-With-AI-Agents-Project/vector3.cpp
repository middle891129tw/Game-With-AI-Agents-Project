/*
* vector3.cpp
*/

#include "vector3.hpp"

Vector3::Vector3(double x=0.0, double y=0.0, double z=0.0) : _data{ x, y, z }
{
}

Vector3::~Vector3()
{
}

double Vector3::getX()
{
    return _data[0];
}

double Vector3::getY()
{
    return _data[1];
}

double Vector3::getZ()
{
    return _data[2];
}

double& Vector3::operator[](size_t index)
{
    return _data[index];
}

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3( _data[0] + other._data[0],
                    _data[1] + other._data[1],
                    _data[2] + other._data[2]);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3( _data[0] - other._data[0],
                    _data[1] - other._data[1],
                    _data[2] - other._data[2]);
}

Vector3 Vector3::operator*(double scalar) const
{
    return Vector3( _data[0] * scalar,
                    _data[1] * scalar,
                    _data[2] * scalar);
}

Vector3 Vector3::operator/(double scalar) const
{
    return Vector3( _data[0] / scalar,
                    _data[1] / scalar,
                    _data[2] / scalar);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    _data[0] += other._data[0];
    _data[1] += other._data[1];
    _data[2] += other._data[2];
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    _data[0] -= other._data[0];
    _data[1] -= other._data[1];
    _data[2] -= other._data[2];
    return *this;
}

Vector3& Vector3::operator*=(double scalar)
{
    _data[0] *= scalar;
    _data[1] *= scalar;
    _data[2] *= scalar;
    return *this;
}

Vector3& Vector3::operator/=(double scalar)
{
    _data[0] /= scalar;
    _data[1] /= scalar;
    _data[2] /= scalar;
    return *this;
}

Vector3 Vector3::operator-() const
{
    return Vector3( -_data[0],
                    -_data[1],
                    -_data[2]);
}


bool Vector3::operator==(const Vector3& other) const
{
    return _data[0] == other._data[0] &&
           _data[1] == other._data[1] &&
           _data[2] == other._data[2];
}

bool Vector3::operator!=(const Vector3& other) const
{
    return !operator==(other);
}
