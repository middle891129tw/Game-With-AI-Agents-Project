/*
* unit.hpp
*/

#pragma once

#include "gameObject.hpp"

class Unit : protected GameObject
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
	void applyForce(Vector3 f);

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
};