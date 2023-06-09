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

    _velMax = 20.0;
    _accAbility = 20.0;
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
