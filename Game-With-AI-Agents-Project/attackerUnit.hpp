/*
* attackerUnit.hpp
*/

#pragma once

#include "botUnit.hpp"

class AttackerUnit : public BotUnit
{
public:
    AttackerUnit(Unit& target);
    ~AttackerUnit();

    void reset() override;

    void attack();

protected:
    Unit& _target;
};