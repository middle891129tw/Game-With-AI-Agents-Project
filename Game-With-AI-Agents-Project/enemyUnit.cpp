/*
* enemyUnit.cpp
*/

#include <random>

#include "enemyUnit.hpp"

EnemyUnit::EnemyUnit()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	double min = -20.0;
	double max =  20.0;
	double randomValue;

	std::uniform_real_distribution<double> dis(min, max);

	randomValue = dis(gen);
	_pos[0] = randomValue;
	randomValue = dis(gen);
	_pos[1] = randomValue;
	_destination = _pos;

	_segmentCount = 7;
	_radius = 2.0;
}

EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::goToDestination()
{
	if (_pos[0] < _destination[0])
		move(Rightward);
	else if (_pos[0] > _destination[0])
		move(Leftward);
	else
		stop(Rightward);

	if (_pos[1] < _destination[1])
		move(Forward);
	else if (_pos[1] > _destination[1])
		move(Backward);
	else
		stop(Forward);
}

void EnemyUnit::wander()
{
	if (abs(_pos[0] - _destination[0]) < 5.0 && abs(_pos[1] - _destination[1]) < 5.0)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		double min = -20.0;
		double max = 20.0;
		double randomValue;

		std::uniform_real_distribution<double> dis(min, max);

		randomValue = dis(gen);
		_destination[0] = randomValue;
		randomValue = dis(gen);
		_destination[1] = randomValue;
		//printf("_destination: %f, %f\n", _destination[0], _destination[1]);
	}
	else
	{
		goToDestination();
	}
}
