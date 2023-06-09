/*
* defenderUnit.cpp
*/

#include "defenderUnit.hpp"

DefenderUnit::DefenderUnit(Unit* target)
{
    _target = target;

    _segmentCount = 4;
    _radius = 1.0;
    _mass = 5.0;
    _threshold = 5.0;

    _maxSpeed = 13.0;
    _accAbility = 30.0;

    _health = Yellow;
}

DefenderUnit::~DefenderUnit()
{
}

void DefenderUnit::defend()
{
    _destination = _target->getPos();
    //printf("_destination: %f, %f\n", _destination[0], _destination[1]);
    goToDestination();
}
