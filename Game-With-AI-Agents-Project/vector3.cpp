/*
* vector3.cpp
*/

#include <cmath>

#include "vector3.hpp"

Vector3::Vector3() : _x(0.0),
                     _y(0.0),
                     _z(0.0)
{
}

Vector3::Vector3(double x, double y, double z) : _x(x),
                                                 _y(y),
                                                 _z(z)
{
}

Vector3::~Vector3()
{
}

double Vector3::getX()
{
    return _x;
}

double Vector3::getY()
{
    return _y;
}

double Vector3::getZ()
{
    return _z;
}

double& Vector3::operator[](size_t index)
{
    switch (index)
    {
    case 0:
        return _x;
    case 1:
        return _y;
    case 2:
        return _z;
    default:
        return _x;
    }
}

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(_x + other._x,
                   _y + other._y,
                   _z + other._z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3(_x - other._x,
                   _y - other._y,
                   _z - other._z);
}

Vector3 Vector3::operator*(double scalar) const
{
    return Vector3(_x * scalar,
                   _y * scalar,
                   _z * scalar);
}

Vector3 operator*(double scalar, const Vector3& vector)
{
    return Vector3(scalar * vector._x,
                   scalar * vector._y,
                   scalar * vector._z);
}


Vector3 Vector3::operator/(double scalar) const
{
    return Vector3(_x / scalar,
                   _y / scalar,
                   _z / scalar);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}

Vector3& Vector3::operator*=(double scalar)
{
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
    return *this;
}

Vector3& Vector3::operator/=(double scalar)
{
    _x /= scalar;
    _y /= scalar;
    _z /= scalar;
    return *this;
}

Vector3 Vector3::operator-() const
{
    return Vector3(-_x,
                   -_y,
                   -_z);
}


bool Vector3::operator==(const Vector3& other) const
{
    return _x == other._x &&
           _y == other._y &&
           _z == other._z;
}

bool Vector3::operator!=(const Vector3& other) const
{
    return !operator==(other);
}

double Vector3::magnitude() const
{
    return std::sqrt(_x * _x +
                     _y * _y +
                     _z * _z);
}

double Vector3::dotProduct(const Vector3& other) const
{
    return _x * other._x +
           _y * other._y +
           _z * other._z;
}

Vector3 Vector3::crossProduct(const Vector3& other) const
{
    double x = _y * other._z - _z * other._y;
    double y = _z * other._x - _x * other._z;
    double z = _x * other._y - _y * other._x;

    return Vector3(x, y, z);
}

Vector3 Vector3::normalized() const
{
    double mag = magnitude();
    if (mag != 0.0)
        return Vector3(_x / mag,
                       _y / mag,
                       _z / mag);
    else
        return Vector3(0.0, 0.0, 0.0);
}

Vector3 Vector3::slerp(const Vector3& start, const Vector3& end, double t)
{
    // Ensure start and end vectors are unit vectors
    Vector3 v1 = start.normalized();
    Vector3 v2 = end.normalized();

    // Calculate the dot product between the two vectors
    double dotProduct = v1.dotProduct(v2);

    // If dot product is close to -1 or 1, return either start or end vector
    if (std::abs(dotProduct) >= 0.99999)
        return t < 0.5 ? v1 : v2;

    // Calculate the angle between the two vectors
    double angle = std::acos(dotProduct);

    // Calculate the sin of the angle
    double sinAngle = std::sin(angle);

    // Calculate the interpolation factors
    double startWeight = std::sin((1.0 - t) * angle) / sinAngle;
    double endWeight = std::sin(t * angle) / sinAngle;

    // Perform spherical linear interpolation (slerp)
    Vector3 interpolatedVec = v1 * startWeight + v2 * endWeight;
    return interpolatedVec.normalized();
}
