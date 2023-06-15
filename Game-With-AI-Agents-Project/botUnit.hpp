/*
* botUnit.hpp
*/

#pragma once

#include <list>
#include <functional>

#include "unit.hpp"

class BotUnit : public Unit
{
public:
    enum Mode
    {
        WANDER,
        REGAIN,
        ATTACK,
        DEFEND,
        ESCAPE,
        RESCUE
    };

protected:
    Vector3 _destination;
    double _threshold;
    Mode _mode;
    std::list<std::reference_wrapper<Unit>> _friendlyUnits;
    std::list<std::reference_wrapper<Unit>> _hostileUnits;

public:
    BotUnit();
    ~BotUnit();

    void update(double deltTime) override;
    void virtual reset() override;

    void addFriendlyUnit(Unit unit);

    void goToDestination();
    void wander();
    void attack();

    Mode getMode();
    void setMode(Mode mode);
};