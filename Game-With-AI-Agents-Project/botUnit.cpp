/*
* botUnit.cpp
*/

#include <random>

#include "botUnit.hpp"

BotUnit::BotUnit() : _destination(),
                     _threshold(2.0),
                     _mode(WANDER)
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
    switch (_mode)
    {
    case BotUnit::WANDER:
        wander();
        break;
    case BotUnit::REGAIN:
        regain();
        break;
    case BotUnit::ATTACK:
        attack();
        break;
    case BotUnit::DEFEND:
        defend();
        break;
    case BotUnit::FOLLOW:
        follow();
        break;
    case BotUnit::ESCAPE:
        escape();
        break;
    case BotUnit::RESCUE:
        rescue();
        break;
    default:
        break;
    }

    Unit::update(deltTime);
}

void BotUnit::reset()
{
    Unit::reset();
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

void BotUnit::regain()
{
    // TODO
}

void BotUnit::attack()
{
    if (_hostileUnits.empty())
        return;

    _destination = _hostileUnits.front().get().getPos();
    goToDestination();
}

void BotUnit::defend()
{
    if (_friendlyUnits.empty())
        return;

    _destination = _friendlyUnits.front().get().getPos();
    goToDestination();
}

void BotUnit::follow()
{
    // TODO
}

void BotUnit::escape()
{
    // TODO
}

void BotUnit::rescue()
{
    // TODO
}

BotUnit::Mode BotUnit::getMode() const
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
        GameObject::_r = 0.7;
        GameObject::_m = 0.2;
        GameObject::_maxSpeed = 18.0;

        Unit::_segmentCount = 3;
        Unit::_accAbility = 20.0;
        Unit::_doesDealDamage = true;
        Unit::_initEnergyPt = 30.0;

        BotUnit::_threshold = 2.0;
        break;
    case DEFEND:
        GameObject::_r = 1.2;
        GameObject::_m = 5.0;
        GameObject::_maxSpeed = 13.0;;

        Unit::_segmentCount = 4;
        Unit::_accAbility = 30.0;
        Unit::_doesDealDamage = true;

        BotUnit::_threshold = 5.0;
        break;
    case ESCAPE:
        break;
    case RESCUE:
        break;
    default:
        break;
    }
}
