/*
* unit.cpp
*/

#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

#include "unit.hpp"

#define PI 3.14159

Unit::Unit() : _segmentCount(3),
               _isStoppingX(true),
               _isStoppingY(true),
               _isDashing(false),
               _doesDealDamage(false),
               _accAbility(15.0),
               _dashFactor(300.0),
               _initHealthPt(95.0f),
               _initEnergyPt(60.0f),
               _healthPt(_initHealthPt),
               _energyPt(_initEnergyPt),
               _emptyHealthPt(0.0f),
               _emptyEnergyPt(0.0f),
               _fullHealthPt(100.0f),
               _fullEnergyPt(100.0f),
               _bodyColor(0.8, 0.8, 0.8),
               _arrowColor(0.8, 0.8, 0.8),
               _team(NEUTRAL),
               _friendlyUnits(),
               _hostileUnits()
{
    reset();
}

Unit::~Unit()
{
}


void Unit::draw()
{
    double angleOffset = atan2(_front[1], _front[0]);

    glPushMatrix();
      glTranslated(_pos[0],
                   _pos[1],
                   _pos[2]);
      drawBody(angleOffset);
      drawArrow(angleOffset);
      drawBars();
    glPopMatrix();
}

void Unit::drawBody(double angleOffset)
{
    glPushMatrix();
      glColor3f(_bodyColor[0],
                _bodyColor[1],
                _bodyColor[2]);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3d(0.0, 0.0, 0.0);
        for (int i = 0; i <= _segmentCount; ++i)
        {
            double angle = 2.0 * PI * static_cast<double>(i) / static_cast<double>(_segmentCount) + angleOffset;
            double x = _r * cos(angle);
            double y = _r * sin(angle);
            glVertex3d(x, y, 0.0);
        }
      glEnd();
    glPopMatrix();
}

void Unit::drawArrow(double angleOffset)
{
    glPushMatrix();
      glTranslated(1.25 * _r * _front[0],
                   1.25 * _r * _front[1],
                   1.25 * _r * _front[2] + 0.01);
      glColor3f(_arrowColor[0],
                _arrowColor[1],
                _arrowColor[2]);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3d(0.0, 0.0, 0.0);
        for (int i = 0; i <= 3; ++i)
        {
            double angle = 2.0f * PI * static_cast<double>(i) / static_cast<double>(3) + angleOffset;
            double x = cos(angle) * 0.15;
            double y = sin(angle) * 0.15;
            glVertex3d(x, y, 0.0);
        }
      glEnd();
    glPopMatrix();
}

void Unit::drawBars()
{
    double length;

    if (getHStatusTruthiness(H_FULL) > 0.0f)
        glColor3f(0.3f, 0.3f, 0.8f);
    else if (getHStatusTruthiness(H_HIGH) > 0.0f)
        glColor3f(0.2f, 0.8f, 0.3f);
    else if (getHStatusTruthiness(H_MEDIUM) > 0.0f)
        glColor3f(0.8f, 0.8f, 0.2f);
    else if (getHStatusTruthiness(H_LOW) > 0.0f)
        glColor3f(0.8f, 0.2f, 0.3f);
    else if (getHStatusTruthiness(H_EMPTY) > 0.0f)
        glColor3f(0.8f, 0.8f, 0.8f);

    length = _healthPt / _fullHealthPt * 0.9;

    glPushMatrix();
      glTranslated(0.0, 1.6 * _r, 0.2);
      glBegin(GL_POLYGON);
        glVertex3d(-length, -0.05, 0.0);
        glVertex3d( length, -0.05, 0.0);
        glVertex3d( length,  0.05, 0.0);
        glVertex3d(-length,  0.05, 0.0);
      glEnd();
      length = 0.9;
      glColor3f(0.5f, 0.5f, 0.5f);
      glBegin(GL_POLYGON);
        glVertex3d(-length, -0.05, 0.0);
        glVertex3d( length, -0.05, 0.0);
        glVertex3d( length,  0.05, 0.0);
        glVertex3d(-length,  0.05, 0.0);
      glEnd();
    glPopMatrix();

    if (getHStatusTruthiness(H_EMPTY) == 0.0f)
    {
        glPushMatrix();
          glTranslated(0.0, 1.6 * _r - 0.2, 0.2);
          length = 0.9f * _energyPt / 100.0f;
          glColor3f(0.8f, 0.8f, 0.8f);
          glBegin(GL_POLYGON);
            glVertex3d(-length, -0.05, 0.0);
            glVertex3d( length, -0.05, 0.0);
            glVertex3d( length,  0.05, 0.0);
            glVertex3d(-length,  0.05, 0.0);
          glEnd();
        glPopMatrix();
    }

}

void Unit::turn(double deltaTime)
{
    if (_isStoppingX && _isStoppingY)
        return;

    GameObject::turn(deltaTime);
}

void Unit::applyForce(Vector3 force, GameObject& source)
{
    Unit* sourceUnitPtr = dynamic_cast<Unit*>(&source);
    if (!_isColliding &&
        sourceUnitPtr != NULL &&
        sourceUnitPtr->getVel().magnitude() > 15.0 &&
        sourceUnitPtr->getIsDashing() &&
        sourceUnitPtr->getEnergyPt() > 10.0f &&
        sourceUnitPtr->getDoesDealDamage() &&
        sourceUnitPtr->getTeam() != _team)
    {
        _healthPt -= 15.0f;
        if (_healthPt < _emptyHealthPt)
            _healthPt = _emptyHealthPt;
    }
    GameObject::applyForce(force, source);
}

void Unit::update(double deltaTime)
{
    if (_healthPt > _emptyHealthPt && _isStoppingX && _isStoppingY)
    {
        _healthPt += 0.1f;
        if (_healthPt > _fullHealthPt)
            _healthPt = _fullHealthPt;
    }

    if (_isDashing)
    {
        _energyPt -= 2.0f;
        if (_energyPt < _emptyEnergyPt)
            _energyPt = _emptyEnergyPt;
    }
    else
    {
        _energyPt += 0.2f;
        if (_energyPt > _fullEnergyPt)
            _energyPt = _fullEnergyPt;
    }

    GameObject::update(deltaTime);
}

void Unit::move(Direction dir)
{
    bool isStopping = getHStatusTruthiness(H_EMPTY) > 0.0f;
    double accAbility = _accAbility * (isStopping ? 0.0 : 1.0);

    switch (dir)
    {
    case FORWARD:
        _isStoppingY = isStopping;
        _acc[1] = accAbility;
        break;
    case BACKWARD:
        _isStoppingY = isStopping;
        _acc[1] = -accAbility;
        break;
    case LEFTWARD:
        _isStoppingX = isStopping;
        _acc[0] = -accAbility;
        break;
    case RIGHTWARD:
        _isStoppingX = isStopping;
        _acc[0] = accAbility;
        break;
    default:
        break;
    }
}

void Unit::stop(Direction dir)
{
    if (dir == FORWARD)
    {
        _isStoppingY = true;
        if (_vel[1] < -0.1)
        {
            _acc[1] = _accAbility * 0.3;
        }
        else if (_vel[1] > 0.1)
        {
            _acc[1] = -_accAbility * 0.3;
        }
        else
        {
            _vel[1] = 0.0;
            _acc[1] = 0.0;
        }
    }

    if (dir == RIGHTWARD)
    {
        _isStoppingX = true;
        if (_vel[0] < -0.1)
        {
            _acc[0] = _accAbility * 0.3;
        }
        else if (_vel[0] > 0.1)
        {
            _acc[0] = -_accAbility * 0.3;
        }
        else
        {
            _vel[0] = 0.0;
            _acc[0] = 0.0;
        }
    }
}

void Unit::addFriendlyUnit(Unit& unit)
{
    _friendlyUnits.push_back(unit);
}

void Unit::addHostileUnit(Unit& unit)
{
    _hostileUnits.push_back(unit);
}

void Unit::reset()
{
    GameObject::_pos[2] = 0.1;

    _healthPt = _initHealthPt;
    _energyPt = _initEnergyPt;
}

Vector3 Unit::getVel() const
{
    return _vel;
}

bool Unit::getIsDashing() const
{
    return _isDashing;
}

void Unit::setIsDashing(bool isDashing)
{
    _isDashing = isDashing;

    if (getHStatusTruthiness(H_EMPTY) > 0.0f || _energyPt <= 10.0)
        return;

    if (_isDashing)
        applyForce(200.0 * _front, *this);
}

bool Unit::getDoesDealDamage() const
{
    return _doesDealDamage;
}

float Unit::getHealthPt() const
{
    return _healthPt;
}

float Unit::getEnergyPt() const
{
    return _energyPt;
}

Unit::Team Unit::getTeam() const
{
    return _team;
}

void Unit::setTeam(Team team)
{
    _team = team;
}

std::map<Unit::HStatus, float> Unit::getHStatusTruthinessMap() const
{
    std::map<Unit::HStatus, float> levelMap;

    //// H_EMPTY
    //if (_healthPt == _emptyHealthPt)
    //    levelMap[H_EMPTY] = 1.0f;
    //else
    //    levelMap[H_EMPTY] = 0.0f;
    //
    //// H_LOW: 0~10 linear, 10~30 constant, 30~50, linear
    //if (0.0f <= _healthPt && _healthPt <= 10.0f)
    //    levelMap[H_LOW] = 1.0f / (10.0f - 0.0f) * (_healthPt - 0.0f);
    //else if (10.0f <= _healthPt && _healthPt <= 30.0f)
    //    levelMap[H_LOW] = 1.0f;
    //else if (30.0f <= _healthPt && _healthPt <= 50.0f)
    //    levelMap[H_LOW] = -1.0f / (50.0f - 30.0f) * (_healthPt - 30.0f) + 1.0f;
    //
    //// H_MEDIUM: 30~40 linear, 40~60 constant, 60~70, linear
    //if (30.0f <= _healthPt && _healthPt <= 40.0f)
    //    levelMap[H_MEDIUM] = 1.0f / (40.0f - 30.0f) * (_healthPt - 30.0f);
    //else if (40.0f <= _healthPt && _healthPt <= 60.0f)
    //    levelMap[H_MEDIUM] = 1.0f;
    //else if (60.0f <= _healthPt && _healthPt <= 70.0f)
    //    levelMap[H_MEDIUM] = -1.0f / (70.0f - 60.0f) * (_healthPt - 60.0f) + 1.0f;
    //
    //// H_HIGH: 50~70 linear, 70~90 constant, 90~100, linear
    //if (50.0f <= _healthPt && _healthPt <= 70.0f)
    //    levelMap[H_HIGH] = 1.0f / (70.0f - 50.0f) * (_healthPt - 50.0f);
    //else if (70.0f <= _healthPt && _healthPt <= 90.0f)
    //    levelMap[H_HIGH] = 1.0f;
    //else if (90.0f <= _healthPt && _healthPt <= 100.0f)
    //    levelMap[H_HIGH] = -1.0f / (100.0f - 90.0f) * (_healthPt - 90.0f) + 1.0f;
    //
    //// H_FULL
    //if (_healthPt == _fullHealthPt)
    //    levelMap[H_FULL] = 1.0f;
    //else
    //    levelMap[H_FULL] = 0.0f;

    for (HStatus healthStatus : { H_EMPTY, H_LOW, H_MEDIUM, H_HIGH, H_FULL })
    {
        levelMap[healthStatus] = getHStatusTruthiness(healthStatus);
    }

    return levelMap;
}

float Unit::getHStatusTruthiness(HStatus healthStatus) const
{
    // fuzzy logic, uses linear equation
    // y - y0 = m(x - x0)
    // y = m(x - x0) + y0

    switch (healthStatus)
    {
    case H_EMPTY:
        if (_healthPt == _emptyHealthPt)
            return 1.0f;
        else
            return 0.0f;

    case H_LOW:
        if (0.0f <= _healthPt && _healthPt <= 10.0f)
            return 1.0f / (10.0f - 0.0f) * (_healthPt - 0.0f);
        else if (10.0f <= _healthPt && _healthPt <= 30.0f)
            return 1.0f;
        else if (30.0f <= _healthPt && _healthPt <= 50.0f)
            return -1.0f / (50.0f - 30.0f) * (_healthPt - 30.0f) + 1.0f;

    case H_MEDIUM:
        if (30.0f <= _healthPt && _healthPt <= 40.0f)
            return 1.0f / (40.0f - 30.0f) * (_healthPt - 30.0f);
        else if (40.0f <= _healthPt && _healthPt <= 60.0f)
            return 1.0f;
        else if (60.0f <= _healthPt && _healthPt <= 70.0f)
            return -1.0f / (70.0f - 60.0f) * (_healthPt - 60.0f) + 1.0f;

    case H_HIGH:
        if (50.0f <= _healthPt && _healthPt <= 70.0f)
            return 1.0f / (70.0f - 50.0f) * (_healthPt - 50.0f);
        else if (70.0f <= _healthPt && _healthPt <= 90.0f)
            return 1.0f;
        else if (90.0f <= _healthPt && _healthPt <= 100.0f)
            return -1.0f / (100.0f - 90.0f) * (_healthPt - 90.0f) + 1.0f;

    case H_FULL:
        if (_healthPt == _fullHealthPt)
            return 1.0f;
        else
            return 0.0f;

    default:
        return 0.0f;
    }
}

