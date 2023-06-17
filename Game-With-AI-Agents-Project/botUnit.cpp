/*
* botUnit.cpp
*/

#include <random>

#include "botUnit.hpp"

BotUnit::BotUnit() : BotUnit(DUMMY)
{
}

BotUnit::BotUnit(Type type) : _type(type),
                              _mode(WANDER),
                              _destination(),
                              _threshold(2.0)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    double minCoord = -20.0;
    double maxCoord =  20.0;
    double randomValue;
    std::uniform_real_distribution<double> dis(minCoord, maxCoord);

    randomValue = dis(gen);
    GameObject::_pos[0] = randomValue;
    randomValue = dis(gen);
    GameObject::_pos[1] = randomValue;

    Unit::_bodyColor = { 0.7, 0.4, 0.3 };

    switch (_type)
    {
    case DUMMY:
        GameObject::_r = 1.0;
        GameObject::_m = 15.0;
        GameObject::_maxSpeed = 12.0;

        Unit::_segmentCount = 4;
        break;
    case BOSS:
        GameObject::_r = 1.8;
        GameObject::_m = 18.0;

        Unit::_segmentCount = 7;

        setMode(WANDER);
        break;
    case ATTACKER:
        GameObject::_r = 0.7;
        GameObject::_m = 0.2;
        GameObject::_maxSpeed = 20.0;

        Unit::_segmentCount = 3;
        Unit::_accAbility = 40.0;
        Unit::_doesDealDamage = true;
        Unit::_initEnergyPt = 30.0f;

        BotUnit::_threshold = 2.0;

        setMode(ATTACK);
        break;
    case DEFENDER:
        GameObject::_r = 1.2;
        GameObject::_m = 5.0;
        GameObject::_maxSpeed = 13.0;;

        Unit::_segmentCount = 6;
        Unit::_accAbility = 30.0;
        Unit::_doesDealDamage = true;

        BotUnit::_threshold = 5.0;

        setMode(DEFEND);
        break;
    default:
        break;
    }

    reset();
}

BotUnit::~BotUnit()
{
}

void BotUnit::update(double deltaTime)
{
    switch (_type)
    {
    case BOSS:
        if (!_friendlyUnits.empty())
        {
            Unit& friendlyUnit = _friendlyUnits.front().get();
            if (friendlyUnit.getHStatusTruthiness(H_EMPTY) > 0.0 ||
                friendlyUnit.getHStatusTruthiness(H_LOW) > 0.5)
                setMode(RESCUE);
            else setMode(WANDER);
        }
        break;
    default:
        break;
    }

    switch (_mode)
    {
    case WANDER: wander(); break;
    case REGAIN: regain(); break;
    case ATTACK: attack(); break;
    case DEFEND: defend(); break;
    case FOLLOW: follow(); break;
    case ESCAPE: escape(); break;
    case RESCUE: rescue(); break;
    default: break;
    }

    Unit::update(deltaTime);
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
    if (_friendlyUnits.empty())
        return;
    _destination = _friendlyUnits.front().get().getPos();
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
