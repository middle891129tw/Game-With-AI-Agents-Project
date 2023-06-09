/*
* unit.hpp
*/

#pragma once

#include "gameObject.hpp"

class Unit : public GameObject
{
public:
    enum Direction { Forward, Backward, Leftward, Rightward };
    enum Team { Neutral, Player, Enemy };

protected:
    unsigned int _segmentCount;

    bool _isStoppingX;
    bool _isStoppingY;
    bool _isDashing;
    double _accAbility;
    double _dashFactor;
    double _hp;

    Vector3 _bodyColor;
    Vector3 _arrowColor;

    Team _team;

    void turn(double deltaTime) override;

public:
    Unit();
    ~Unit();
    
    void draw() override;
    void drawBody(float angleOffset);
    void drawArrow(float angleOffset);
    void drawHealthBar();
    void move(Direction);
    void stop(Direction);
    void dash();
};