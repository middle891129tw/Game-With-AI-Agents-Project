/*
* playerUnit.cpp
*/

#include "playerUnit.hpp"


PlayerUnit::PlayerUnit()
{
    GameObject::_pos[2] = 0.2;
    GameObject::_maxSpeed = 20.0;
    GameObject::_m = 2.0;

    Unit::_segmentCount = 5;
    Unit::_accAbility = 25.0;
    Unit::_doesDealDamage = true;
    Unit::_team = TERRANS;
    Unit::_bodyColor = { 0.3, 0.4, 0.7 };

    reset();
}

PlayerUnit::~PlayerUnit()
{
}

void PlayerUnit::reset()
{
    Unit::_healthPt = 95.0f;
    Unit::_energyPt = 60.0;
}
