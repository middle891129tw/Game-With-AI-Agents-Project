/*
* unit.hpp
*/

#pragma once

#include "gameObject.hpp"

class Unit : public GameObject
{
public:
    enum Direction { Forward, Backward, Leftward, Rightward };
    
    Unit();
    ~Unit();
    
    void draw() override;
    void move(Direction);
    void stop(Direction);

    void applyForce(Vector3 f);

protected:
    unsigned int _segmentCount;

    bool _isStoppingX;
    bool _isStoppingY;
    double _accAbility;
    double _velMax;

    void turn(double deltaTime) override;
};