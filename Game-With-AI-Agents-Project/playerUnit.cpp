/*
* playerUnit.cpp
*/

#include "playerUnit.hpp"


PlayerUnit::PlayerUnit()
{
	_pos[2] = 0.2;

	_segmentCount = 5;
	_m = 2.0;

	_health = Green;
}

PlayerUnit::~PlayerUnit()
{
}