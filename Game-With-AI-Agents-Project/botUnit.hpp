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
        WANDER,
        REGAIN,
        ATTACK,
        DEFEND,
        FOLLOW,
        ESCAPE,
        RESCUE
    };

protected:
    Vector3 _destination;
    double _threshold;
    Mode _mode;

public:
    BotUnit();
    ~BotUnit();

    void update(double deltTime) override;
    void reset() override;

    void goToDestination();
    void wander();
    void regain();
    void attack();
    void defend();
    void follow();
    void escape();
    void rescue();

    Mode getMode() const;
    void setMode(Mode mode);
};