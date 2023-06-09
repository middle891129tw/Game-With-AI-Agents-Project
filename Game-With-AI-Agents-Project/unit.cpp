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
               _accAbility(15.0),
               _dashFactor(300.0),
               _bodyColor(0.8, 0.8, 0.8),
               _arrowColor(0.8, 0.8, 0.8),
               _health(Empty),
               _team(Neutral)
{
    _pos = { 0.0, 0.0, 0.1 };
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
      drawHealthBar();
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
            float x = _radius * cos(angle);
            float y = _radius * sin(angle);
            glVertex3f(x, y, 0.0);
        }
      glEnd();
    glPopMatrix();
}

void Unit::drawArrow(float angleOffset)
{
    glPushMatrix();
      glTranslatef(1.25 * _radius * _front[0],
                   1.25 * _radius * _front[1],
                   1.25 * _radius * _front[2]);
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

void Unit::drawHealthBar()
{
    double length;
    switch (_health)
    {
    case Red:
        glColor3f(0.8, 0.2, 0.3);
        length = 0.3;
        break;
    case Yellow:
        glColor3f(0.8, 0.8, 0.2);
        length = 0.6;
        break;
    case Green:
        glColor3f(0.2, 0.8, 0.3);
        length = 0.9;
        break;
    case Empty:
    default:
        return;
    }
    glPushMatrix();
      glTranslatef(0.0, 1.5 * _radius, 0.0);
      glBegin(GL_POLYGON);
        glVertex3f(-length, -0.05, 0.0);
        glVertex3f( length, -0.05, 0.0);
        glVertex3f( length,  0.05, 0.0);
        glVertex3f(-length,  0.05, 0.0);
      glEnd();
    glPopMatrix();
}

void Unit::turn(double deltaTime)
{
    if (_isStoppingX && _isStoppingY)
        return;

    GameObject::turn(deltaTime);
}

void Unit::move(Direction dir)
{
    switch (dir)
    {
    case Forward:
        _isStoppingY = false;
        _acc[1] = _accAbility;
        break;
    case Backward:
        _isStoppingY = false;
        _acc[1] = -_accAbility;
        break;
    case Leftward:
        _isStoppingX = false;
        _acc[0] = -_accAbility;
        break;
    case Rightward:
        _isStoppingX = false;
        _acc[0] = _accAbility;
        break;
    default:
        break;
    }
}

void Unit::stop(Direction dir)
{
    if (dir == Forward)
    {
        _isStoppingY = true;
        if (_vel[1] < -0.1)
        {
            _acc[1] = _accAbility * 0.9;
        }
        else if (_vel[1] > 0.1)
        {
            _acc[1] = -_accAbility * 0.9;
        }
        else
        {
            _vel[1] = 0.0;
            _acc[1] = 0.0;
        }
    }

    if (dir == Rightward)
    {
        _isStoppingX = true;
        if (_vel[0] < -0.1)
        {
            _acc[0] = _accAbility * 0.9;
        }
        else if (_vel[0] > 0.1)
        {
            _acc[0] = -_accAbility * 0.9;
        }
        else
        {
            _vel[0] = 0.0;
            _acc[0] = 0.0;
        }
    }
}

void Unit::dash()
{
    if (_isDashing)
        return;

    _isDashing = true;
    applyForce(_dashFactor * _front);
    
    // TODO
}

