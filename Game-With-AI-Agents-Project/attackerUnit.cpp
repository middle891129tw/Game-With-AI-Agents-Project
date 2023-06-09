/*
* attackerUnit.cpp
*/

#include "attackerUnit.hpp"

AttackerUnit::AttackerUnit(Unit* target)
{
    _target = target;

    _segmentCount = 3;
    _radius = 0.7;
    _mass = 0.5;
    _threshold = 0.1;

    _maxSpeed = 15.0;
    _accAbility = 15.0;

    _health = Red;
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
