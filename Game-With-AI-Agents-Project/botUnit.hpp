/*
* botUnit.hpp
*/

#pragma once

#include "unit.hpp"

class BotUnit : public Unit
{
public:
    enum Type
    {
        DUMMY,
        BOSS,
        ATTACKER,
        DEFENDER
    };

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
    const Type  _type;
    Mode        _mode;
    Vector3     _destination;
    double      _threshold;

public:
    BotUnit();
    BotUnit(Type type);
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