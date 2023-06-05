/*
* vector3.hpp
*/

class Vector3
{
public:
	Vector3(double, double, double);
	~Vector3();

	double getX();
	double getY();
	double getZ();

	double& operator[](size_t);

    // Vector arithmetic operators
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(double scalar) const;
    Vector3 operator/(double scalar) const;
    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator*=(double scalar);
    Vector3& operator/=(double scalar);
    Vector3 operator-() const;

    // Vector comparison operators
    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;

    // Vector operations
    double magnitude() const;
    double dotProduct(const Vector3& other) const;
    Vector3 crossProduct(const Vector3& other) const;
    Vector3 normalized() const;

private:
	double _data[3];
};