/*
* botUnit.cpp
*/

#include <random>

#include "botUnit.hpp"

BotUnit::BotUnit() : _destination(),
                     _threshold(2.0)
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
    GameObject::_r = 2.0;
    GameObject::_m = 8.0;

    Unit::_segmentCount = 7;
    Unit::_bodyColor = { 0.6, 0.6, 0.6 };
    Unit::_health = Green;
}

BotUnit::~BotUnit()
{
}

void BotUnit::goToDestination()
{
    if (_pos[0] < _destination[0] - _threshold)
        move(Rightward);
    else if (_pos[0] > _destination[0] + _threshold)
        move(Leftward);
    else
        stop(Rightward);

    if (_pos[1] < _destination[1] - _threshold)
        move(Forward);
    else if (_pos[1] > _destination[1] + _threshold)
        move(Backward);
    else
        stop(Forward);
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
