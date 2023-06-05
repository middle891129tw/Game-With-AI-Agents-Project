/*
* unit.hpp
*/

#pragma once

#include <vector>

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

	std::vector<double> getPos();
	double getRadius();

protected:
	std::vector<double> _pos;
	std::vector<double> _vel;
	std::vector<double> _acc;
	std::vector<double> _front;

	unsigned int _segmentCount;
	double _radius;
	double _mass;

	bool _isStoppingX;
	bool _isStoppingY;
	double _accAbility;
	double _velMax;

	void translate(std::vector<double> t);
	void translate(double deltaTime);
	void accelerate(std::vector<double> a);
	void accelerate(double deltaTime);
	void rotate(double deltaTime);
	void applyForce(std::vector<double> f);

	std::vector<double> slerp(const std::vector<double>& start, const std::vector<double>& end, double t);
};