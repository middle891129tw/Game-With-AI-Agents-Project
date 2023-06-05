/*
* enemyUnit.hpp
*/

#pragma once

#include "unit.hpp"

class EnemyUnit : public Unit
{
public:
	EnemyUnit();
	~EnemyUnit();
	
	void goToDestination();
	void wander();

protected:
	Vector3 _destination;
	double _threshold;
};