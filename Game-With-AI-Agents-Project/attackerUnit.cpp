/*
* attackerUnit.cpp
*/

#include "attackerUnit.hpp"

AttackerUnit::AttackerUnit(Unit* target)
{
	_target = target;

	_segmentCount = 3;
	_radius = 0.5;
	_threshold = 1.0;

	_velMax = 30.0;
	_accAbility = 20.0;
}

AttackerUnit::~AttackerUnit()
{
}

void AttackerUnit::attack()
{
	_destination = _target->getPos();
	//printf("_destination: %f, %f\n", _destination[0], _destination[1]);
	goToDestination();
}
