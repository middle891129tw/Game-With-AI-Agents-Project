/*
* unit.hpp
*/

#pragma once

#include "vector3.hpp"

class Unit
{
public:
	enum Direction { Forward, Backward, Leftward, Rightward };
	
	Unit();
	~Unit();
	
	void draw();
	void animate(double deltaTime);
	void move(Direction);
	void stop(Direction);

	Vector3 getPos();
	double getRadius();

protected:
	Vector3 _pos;
	Vector3 _vel;
	Vector3 _acc;
	Vector3 _front;

	unsigned int _segmentCount;
	double _radius;
	double _mass;

	bool _isStoppingX;
	bool _isStoppingY;
	double _accAbility;
	double _velMax;

	void translate(Vector3 t);
	void translate(double deltaTime);
	void accelerate(Vector3 a);
	void accelerate(double deltaTime);
	void rotate(double deltaTime);
	void applyForce(Vector3 f);
};