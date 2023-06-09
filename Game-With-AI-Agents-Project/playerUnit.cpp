/*
* playerUnit.cpp
*/

#include "playerUnit.hpp"


PlayerUnit::PlayerUnit()
{
    GameObject::_pos[2] = 0.2;
    GameObject::_m = 2.0;

    Unit::_segmentCount = 5;
    Unit::_doesDealDamage = true;
    Unit::_health = Green;
}

PlayerUnit::~PlayerUnit()
{
}