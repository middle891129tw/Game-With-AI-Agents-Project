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
    Unit::_accAbility = 20.0;
    Unit::_doesDealDamage = true;
    Unit::_team = Player;

    reset();
}

PlayerUnit::~PlayerUnit()
{
}

void PlayerUnit::reset()
{
    Unit::_health = Green;
    Unit::_energyPt = 60.0;
}
