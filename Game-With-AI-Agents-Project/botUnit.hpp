/*
* botUnit.hpp
*/

#pragma once

#include "unit.hpp"

class BotUnit : public Unit
{
public:
    BotUnit();
    ~BotUnit();
    
    void goToDestination();
    void wander();

protected:
    Vector3 _destination;
    double _threshold;
};