/*
* enemyUnit3.cpp
*/

#include "attackerUnit.hpp"

AttackerUnit::AttackerUnit(Unit* target) : _target(target)
{
    GameObject::_r = 0.7;
    GameObject::_m = 0.2;
    GameObject::_maxSpeed = 15.0;

    Unit::_segmentCount = 3;
    Unit::_accAbility = 15.0;
    Unit::_doesDealDamage = true;
    Unit::_health = Red;

    BotUnit::_threshold = 0.1;
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
