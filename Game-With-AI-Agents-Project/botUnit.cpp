/*
* botUnit.cpp
*/

#include <random>

#include "botUnit.hpp"

BotUnit::BotUnit() : _destination(),
                     _threshold(2.0),
                     _mode(WANDER),
                     _friendlyUnits(),
                     _hostileUnits()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    double min = -20.0;
    double max =  20.0;
    double randomValue;
    std::uniform_real_distribution<double> dis(min, max);

    randomValue = dis(gen);
    GameObject::_pos[0] = randomValue;
    randomValue = dis(gen);
    GameObject::_pos[1] = randomValue;
    GameObject::_r = 1.8;
    GameObject::_m = 18.0;

    Unit::_segmentCount = 7;
    Unit::_bodyColor = { 0.5, 0.5, 0.5 };

    reset();
}

BotUnit::~BotUnit()
{
}

void BotUnit::update(double deltTime)
{
    /**/

    Unit::update(deltTime);
}

void BotUnit::reset()
{
    Unit::_healthPt = 95.0f;
    Unit::_energyPt = 60.0;
}

void BotUnit::addFriendlyUnit(Unit unit)
{
    _friendlyUnits.push_back(unit);
}

void BotUnit::goToDestination()
{
    if (_pos[0] < _destination[0] - _threshold)
        move(RIGHTWARD);
    else if (_pos[0] > _destination[0] + _threshold)
        move(LEFTWARD);
    else
        stop(RIGHTWARD);

    if (_pos[1] < _destination[1] - _threshold)
        move(FORWARD);
    else if (_pos[1] > _destination[1] + _threshold)
        move(BACKWARD);
    else
        stop(FORWARD);

    setIsDashing((_destination - _pos).magnitude() < _threshold * 2.0 &&
                 _energyPt > 10.0);
}

void BotUnit::wander()
{
    if (abs(_pos[0] - _destination[0]) < _threshold && abs(_pos[1] - _destination[1]) < _threshold)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        double min = -20.0;
        double max = 20.0;
        double randomValue;

        std::uniform_real_distribution<double> dis(min, max);

        randomValue = dis(gen);
        _destination[0] = randomValue;
        randomValue = dis(gen);
        _destination[1] = randomValue;
    }
    else
    {
        goToDestination();
    }
}

void BotUnit::attack()
{
    //_destination = ???;
    goToDestination();
}

BotUnit::Mode BotUnit::getMode()
{
    return _mode;
}

void BotUnit::setMode(Mode mode)
{
    _mode = mode;

    switch (mode)
    {
    case WANDER:
        wander();
        break;
    case REGAIN:
        break;
    case ATTACK:
        break;
    case DEFEND:
        break;
    case ESCAPE:
        break;
    case RESCUE:
        break;
    default:
        break;
    }
}
