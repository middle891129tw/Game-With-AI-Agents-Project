/*
* unit.hpp
*/

#pragma once

#include "gameObject.hpp"

class Unit : public GameObject
{
protected:
    unsigned int _segmentCount;

    bool _isStoppingX;
    bool _isStoppingY;
    double _accAbility;
    double _velMax;

    Vector3 _bodyColor;
    Vector3 _indicatorColor;

    void turn(double deltaTime) override;

public:
    enum Direction { Forward, Backward, Leftward, Rightward };
    
    Unit();
    ~Unit();
    
    void draw() override;
    void move(Direction);
    void stop(Direction);

    void applyForce(Vector3 f);
};