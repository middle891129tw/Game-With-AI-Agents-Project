/*
* attackerUnit.cpp
*/

#include "attackerUnit.hpp"

AttackerUnit::AttackerUnit(Unit& target) : _target(target)
{
    GameObject::_r = 0.7;
    GameObject::_m = 0.2;
    GameObject::_maxSpeed = 15.0;

    Unit::_segmentCount = 3;
    Unit::_accAbility = 15.0;
    Unit::_doesDealDamage = true;

    BotUnit::_threshold = 2.0;

    reset();
}

AttackerUnit::~AttackerUnit()
{
}

void AttackerUnit::reset()
{
    Unit::_healthPt = 95.0f;
    Unit::_energyPt = 30.0f;
}

void AttackerUnit::attack()
{
    _destination = _target.getPos();
    //printf("_destination: %f, %f\n", _destination[0], _destination[1]);
    goToDestination();
}
