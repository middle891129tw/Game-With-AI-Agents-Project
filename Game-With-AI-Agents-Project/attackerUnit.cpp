/*
* attackerUnit.cpp
*/

#include "attackerUnit.hpp"

AttackerUnit::AttackerUnit(Unit* target)
{
	_target = target;

	_segmentCount = 3;
	_radius = 0.7;
	_threshold = 0.1;

	_velMax = 15.0;
	_accAbility = 15.0;
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
