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
        break;
    case BotUnit::ATTACK:
        attack();
        break;
    case BotUnit::DEFEND:
        break;
    case BotUnit::FOLLOW:
        break;
    case BotUnit::ESCAPE:
        break;
    case BotUnit::RESCUE:
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

void BotUnit::attack()
{
    if (_hostileUnits.empty())
        return;

    _destination = _hostileUnits.front().get().getPos();
    goToDestination();
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
        GameObject::_maxSpeed = 15.0;

        Unit::_segmentCount = 3;
        Unit::_accAbility = 15.0;
        Unit::_doesDealDamage = true;
        Unit::_initEnergyPt = 30.0;

        BotUnit::_threshold = 2.0;
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
