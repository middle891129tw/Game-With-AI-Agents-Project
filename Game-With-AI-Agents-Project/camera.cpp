/*
* camera.cpp
*/

#include "camera.hpp"

Camera::Camera()
{
	reset();
}

Camera::~Camera()
{
}

std::vector<double> Camera::getEye()	{ return _eye; }
std::vector<double> Camera::getCenter()	{ return _center; }
std::vector<double> Camera::getUp()		{ return _up; }

void Camera::reset()
{
	_eye	= {  0.0, -2.0,  8.0 };
	_front	= {  0.0,  2.0, -8.0 };
	_center	= {  0.0,  0.0,  0.0 };
	_up		= {  0.0,  1.0,  0.0 };
}

void Camera::translate(std::vector<double> t)
{
	_eye	[0] += t[0] * 0.9;
	_eye	[1] += t[1] * 0.9;
	_eye	[2] += t[2];
	_center	[0] += t[0] * 0.9;
	_center	[1] += t[1] * 0.9;
	_center	[2] += t[2];
}

void Camera::setPos(std::vector<double> p)
{
	_eye	[0] = p[0];
	_eye	[1] = p[1] - _front[1];
	_eye	[2] = p[2] - _front[2];
	_center	[0] = p[0];
	_center	[1] = p[1];
	_center	[2] = p[2];
}