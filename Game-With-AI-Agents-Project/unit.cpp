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
               _healthPt(95.0f),
               _energyPt(60.0f),
               _emptyHealthPt(0.0f),
               _emptyEnergyPt(0.0f),
               _fullHealthPt(100.0f),
               _fullEnergyPt(100.0f),
               _bodyColor(0.8, 0.8, 0.8),
               _arrowColor(0.8, 0.8, 0.8),
               _team(NEUTRAL)
{
    reset();
}

Unit::~Unit()
{
}


void Unit::draw()
{
    float angleOffset = atan2(_front[1], _front[0]);

    glPushMatrix();
      glTranslatef(_pos[0],
                   _pos[1],
                   _pos[2]);
      drawBody(angleOffset);
      drawArrow(angleOffset);
      drawBars();
    glPopMatrix();
}

void Unit::drawBody(float angleOffset)
{
    glPushMatrix();
      glColor3f(_bodyColor[0],
                _bodyColor[1],
                _bodyColor[2]);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, 0.0, 0.0);
        for (int i = 0; i <= _segmentCount; ++i)
        {
            float angle = 2.0f * PI * static_cast<float>(i) / static_cast<float>(_segmentCount) + angleOffset;
            float x = _r * cos(angle);
            float y = _r * sin(angle);
            glVertex3f(x, y, 0.0);
        }
      glEnd();
    glPopMatrix();
}

void Unit::drawArrow(float angleOffset)
{
    glPushMatrix();
      glTranslatef(1.25 * _r * _front[0],
                   1.25 * _r * _front[1],
                   1.25 * _r * _front[2] + 0.01);
      glColor3f(_arrowColor[0],
                _arrowColor[1],
                _arrowColor[2]);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, 0.0, 0.0);
        for (int i = 0; i <= 3; ++i)
        {
            float angle = 2.0f * PI * static_cast<float>(i) / static_cast<float>(3) + angleOffset;
            float x = cos(angle) * 0.15;
            float y = sin(angle) * 0.15;
            glVertex3f(x, y, 0.0);
        }
      glEnd();
    glPopMatrix();
}

void Unit::drawBars()
{
    float length;

    std::map<Health, float> healthLevels = getHealthLevels();
    if (healthLevels[H_EMPTY] > 0.0f)
        glColor3f(0.8f, 0.8f, 0.8f);
    else if (healthLevels[H_LOW] > 0.0f)
        glColor3f(0.8f, 0.2f, 0.3f);
    else if (healthLevels[H_MEDIUM] > 0.0f)
        glColor3f(0.8f, 0.8f, 0.2f);
    else if (healthLevels[H_HIGH] > 0.0f)
        glColor3f(0.2f, 0.8f, 0.3f);
    else if (healthLevels[H_FULL] > 0.0f)
        glColor3f(0.3f, 0.3f, 0.8f);

    length = _healthPt / _fullHealthPt * 0.9f;

    glPushMatrix();
      glTranslatef(0.0f, 1.6f * _r, 0.2f);
      glBegin(GL_POLYGON);
        glVertex3f(-length, -0.05f, 0.0f);
        glVertex3f( length, -0.05f, 0.0f);
        glVertex3f( length,  0.05f, 0.0f);
        glVertex3f(-length,  0.05f, 0.0f);
      glEnd();
      length = 0.9f;
      glColor3f(0.5f, 0.5f, 0.5f);
      glBegin(GL_POLYGON);
        glVertex3f(-length, -0.05f, 0.0f);
        glVertex3f( length, -0.05f, 0.0f);
        glVertex3f( length,  0.05f, 0.0f);
        glVertex3f(-length,  0.05f, 0.0f);
      glEnd();
    glPopMatrix();

    if (healthLevels[H_EMPTY] == 0.0f)
    {
        glPushMatrix();
          glTranslatef(0.0f, 1.6f * _r - 0.2f, 0.2f);
          length = 0.9f * _energyPt / 100.0f;
          glColor3f(0.8f, 0.8f, 0.8f);
          glBegin(GL_POLYGON);
            glVertex3f(-length, -0.05f, 0.0f);
            glVertex3f( length, -0.05f, 0.0f);
            glVertex3f( length,  0.05f, 0.0f);
            glVertex3f(-length,  0.05f, 0.0f);
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
        sourceUnitPtr->getIsDashing() &&
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
    GameObject::update(deltaTime);

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
}

void Unit::move(Direction dir)
{
    bool isStopping = getHealthLevels()[H_EMPTY] > 0.0f;
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

void Unit::reset()
{
    GameObject::_pos = { 0.0, 0.0, 0.1 };
}

bool Unit::getIsDashing()
{
    return _isDashing;
}

void Unit::setIsDashing(bool isDashing)
{
    _isDashing = isDashing;

    if (getHealthLevels()[H_EMPTY] > 0.0f || _energyPt <= 10.0)
        return;

    if (_isDashing)
        applyForce(200.0 * _front, *this);
}

bool Unit::getDoesDealDamage()
{
    return _doesDealDamage;
}

Unit::Team Unit::getTeam()
{
    return _team;
}

void Unit::setTeam(Team team)
{
    _team = team;
}

std::map<Unit::Health, float> Unit::getHealthLevels() const
{
    std::map<Unit::Health, float> levels;

    // H_EMPTY
    if (_healthPt == _emptyHealthPt)
        levels[H_EMPTY] = 1.0f;
    else
        levels[H_EMPTY] = 0.0f;

    // use linear equation
    // y - y0 = m(x - x0)
    // y = m(x - x0) + y0

    // H_LOW: 0~10 linear, 10~30 constant, 30~50, linear
    if (0.0f <= _healthPt && _healthPt <= 10.0f)
        levels[H_LOW] = 1.0f / (10.0f - 0.0f) * (_healthPt - 0.0f);
    else if (10.0f <= _healthPt && _healthPt <= 30.0f)
        levels[H_LOW] = 1.0f;
    else if (30.0f <= _healthPt && _healthPt <= 50.0f)
        levels[H_LOW] = -1.0f / (50.0f - 30.0f) * (_healthPt - 30.0f) + 1.0f;

    // H_MEDIUM: 30~40 linear, 40~60 constant, 60~70, linear
    if (30.0f <= _healthPt && _healthPt <= 40.0f)
        levels[H_MEDIUM] = 1.0f / (40.0f - 30.0f) * (_healthPt - 30.0f);
    else if (40.0f <= _healthPt && _healthPt <= 60.0f)
        levels[H_MEDIUM] = 1.0f;
    else if (60.0f <= _healthPt && _healthPt <= 70.0f)
        levels[H_MEDIUM] = -1.0f / (70.0f - 60.0f) * (_healthPt - 60.0f) + 1.0f;

    // H_HIGH: 50~70 linear, 70~90 constant, 90~100, linear
    if (50.0f <= _healthPt && _healthPt <= 70.0f)
        levels[H_HIGH] = 1.0f / (70.0f - 50.0f) * (_healthPt - 50.0f);
    else if (70.0f <= _healthPt && _healthPt <= 90.0f)
        levels[H_HIGH] = 1.0f;
    else if (90.0f <= _healthPt && _healthPt <= 100.0f)
        levels[H_HIGH] = -1.0f / (100.0f - 90.0f) * (_healthPt - 90.0f) + 1.0f;

    // H_FULL
    if (_healthPt == _fullHealthPt)
        levels[H_FULL] = 1.0f;
    else
        levels[H_FULL] = 0.0f;

    return levels;
}

