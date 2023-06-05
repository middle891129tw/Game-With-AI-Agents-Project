/*
* camera.hpp
*/

#pragma once

#include "vector3.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	Vector3 getEye();
	Vector3 getCenter();
	Vector3 getUp();

	void reset();
	void translate(Vector3);
	void setPos(Vector3);

private:
	Vector3 _front;
	Vector3 _eye;
	Vector3 _center;
	Vector3 _up;
	
};