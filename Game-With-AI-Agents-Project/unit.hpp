/*
* unit.hpp
*/

#pragma once

#include <functional>
#include <list>
#include <map>

#include "gameObject.hpp"

class Unit : public GameObject
{
public:
    enum Direction { FORWARD, BACKWARD, LEFTWARD, RIGHTWARD };
    enum Health { H_EMPTY, H_LOW, H_MEDIUM, H_HIGH, H_FULL };
    enum Energy { E_EMPTY, E_LOW, E_MEDIUM, E_HIGH, E_FULL };
    enum Team { NEUTRAL, TERRANS, MARTIANS };

protected:
    unsigned int _segmentCount;
    bool _isStoppingX;
    bool _isStoppingY;
    bool _isDashing;
    bool _doesDealDamage;
    double _accAbility;
    double _dashFactor;
    float _initHealthPt;
    float _initEnergyPt;
    float _healthPt;
    float _energyPt;
    const float _emptyHealthPt;
    const float _emptyEnergyPt;
    const float _fullHealthPt;
    const float _fullEnergyPt;
    Vector3 _bodyColor;
    Vector3 _arrowColor;
    Team _team;
    std::list<std::reference_wrapper<Unit>> _friendlyUnits;
    std::list<std::reference_wrapper<Unit>> _hostileUnits;


public:
    Unit();
    ~Unit();
    
    void draw() override;
    void turn(double deltaTime) override;
    void applyForce(Vector3 force, GameObject& source) override;

    void virtual update(double deltaTime) override;

    void drawBody(float angleOffset);
    void drawArrow(float angleOffset);
    void drawBars();
    void move(Direction);
    void stop(Direction);
    void addFriendlyUnit(Unit& unit);
    void addHostileUnit(Unit& unit);

    void virtual reset();

    Vector3 getVel() const;

    bool getIsDashing() const;
    void setIsDashing(bool isDashing);

    bool getDoesDealDamage() const;

    float getHealthPt() const;
    float getEnergyPt() const;

    Team getTeam() const;
    void setTeam(Team team);

    std::map<Health, float> getHealthLevels() const;
};