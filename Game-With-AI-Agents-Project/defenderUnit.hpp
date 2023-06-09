/*
* defenfderUnit.hpp
*/

#pragma once

#include "botUnit.hpp"

class DefenderUnit : public BotUnit
{
public:
    DefenderUnit(Unit* target);
    ~DefenderUnit();

    void reset() override;

    void defend();

protected:
    Unit* _target;
};