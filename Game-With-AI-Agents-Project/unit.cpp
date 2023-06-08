/*
* unit.cpp
*/

#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

#include "unit.hpp"

#define PI 3.14159

Unit::Unit()
{
    _segmentCount = 3;

    _isStoppingX = true;
    _isStoppingY = true;

    _velMax = 10.0;
    _accAbility = 15.0;
}

Unit::~Unit()
{
}


void Unit::draw()
{
    float angleOffset = atan2(_front[1], _front[0]);

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(_pos[0], _pos[1], _pos[2]);
      for (int i = 0; i <= _segmentCount; ++i)
      {
          float angle = 2.0f * PI * static_cast<float>(i) / static_cast<float>(_segmentCount) + angleOffset;
          float x = _pos[0] + _radius * cos(angle);
          float y = _pos[1] + _radius * sin(angle);
          glVertex3f(x, y, _pos[2]);
      }
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(_pos[0], _pos[1], _pos[2] + 0.1);
      for (int i = 0; i <= 3; ++i)
      {
          float angle = 2.0f * PI * static_cast<float>(i) / static_cast<float>(3) + angleOffset;
          float x = _pos[0] + _radius * cos(angle) * 0.2;
          float y = _pos[1] + _radius * sin(angle) * 0.2;
          glVertex3f(x, y, _pos[2]);
      }
    glEnd();
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
            _acc[1] = _accAbility;
        }
        else if (_vel[1] > 0.1)
        {
            _acc[1] = -_accAbility;
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
            _acc[0] = _accAbility;
        }
        else if (_vel[0] > 0.1)
        {
            _acc[0] = -_accAbility;
        }
        else
        {
            _vel[0] = 0.0;
            _acc[0] = 0.0;
        }
    }
}

void Unit::applyForce(Vector3 f)
{
    //_acc += f / _mass;
    _acc = Vector3(0.0, 0.0, 0.0);
    _vel = -_vel * 0.99;
}
