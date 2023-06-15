/*
* botUnit.hpp
*/

#pragma once

#include "unit.hpp"

class BotUnit : public Unit
{
public:
    enum Mode
    {
        Wadner,
        Attack,
        Defend,
        Escape,
        Rescue
    };

public:
    BotUnit();
    ~BotUnit();

    void virtual reset() override;

    void goToDestination();
    void wander();

protected:
    Vector3 _destination;
    double _threshold;
};