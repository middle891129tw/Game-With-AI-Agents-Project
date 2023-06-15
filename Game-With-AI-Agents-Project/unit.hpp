/*
* unit.hpp
*/

#pragma once

#include "gameObject.hpp"

class Unit : public GameObject
{
public:
    enum Direction { FORWARD, BACKWARD, LEFTWARD, RIGHTWARD };
    enum Health { H_EMPTY, H_LOW, H_MEDIUM, H_HIGH, INVINCIBLE };
    enum Energy { E_EMPTY, E_LOW, E_MEDIUM, E_HIGH };
    enum Team { Neutral, Player, Evil };

protected:
    unsigned int _segmentCount;
    bool _isStoppingX;
    bool _isStoppingY;
    bool _isDashing;
    bool _doesDealDamage;
    double _accAbility;
    double _dashFactor;
    double _energyPt;
    Vector3 _bodyColor;
    Vector3 _arrowColor;

    Health _health;
    Energy _energy;
    Team _team;


public:
    Unit();
    ~Unit();
    
    void draw() override;
    void turn(double deltaTime) override;
    void applyForce(Vector3 force, GameObject& source) override;
    void update(double deltaTime) override;

    void drawBody(float angleOffset);
    void drawArrow(float angleOffset);
    void drawBars();
    void move(Direction);
    void stop(Direction);

    void virtual reset();

    bool getIsDashing();
    void setIsDashing(bool isDashing);

    bool getDoesDealDamage();

    Team getTeam();
    void setTeam(Team team);
};