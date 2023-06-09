/*
* evilUnit2.cpp
*/

#include "defenderUnit.hpp"

DefenderUnit::DefenderUnit(Unit& target) : _target(target)
{
    GameObject::_r = 1.2;
    GameObject::_m = 5.0;
    GameObject::_maxSpeed = 13.0;;

    Unit::_segmentCount = 4;
    Unit::_accAbility = 30.0;
    Unit::_doesDealDamage = true;

    BotUnit::_threshold = 5.0;

    reset();
}

DefenderUnit::~DefenderUnit()
{
}

void DefenderUnit::reset()
{
    Unit::_health = Yellow;
}

void DefenderUnit::defend()
{
    _destination = _target.getPos();
    //printf("_destination: %f, %f\n", _destination[0], _destination[1]);
    goToDestination();
}
