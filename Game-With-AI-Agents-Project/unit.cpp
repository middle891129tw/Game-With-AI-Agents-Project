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
    _pos    = { 0.0, 0.0, 0.1 };
    _vel    = { 0.0, 0.0, 0.0 };
    _acc    = { 0.0, 0.0, 0.0 };

    _front  = { 0.0, 0.9, 0.0 };

    _radius = 1.0;
    _segmentCount = 3;

    _isStoppingX = true;
    _isStoppingY = true;
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

void Unit::translate(std::vector<double> t)
{
    _pos[0] += t[0];
    _pos[1] += t[1];
    _pos[2] += t[2];
    if (_pos[0] < -25.0+_radius || 25.0-_radius < _pos[0]) _pos[0] -= t[0];
    if (_pos[1] < -25.0+_radius || 25.0-_radius < _pos[1]) _pos[1] -= t[1];
    if (_pos[2] < -25.0+_radius || 25.0-_radius < _pos[2]) _pos[2] -= t[2];
}

void Unit::translate(double deltaTime)
{
    std::vector<double> t = { _vel[0] * deltaTime, _vel[1] * deltaTime , _vel[2] * deltaTime };
    translate(t);
}

void Unit::accelerate(std::vector<double> a)
{
    _vel[0] += a[0];
    _vel[1] += a[1];
    _vel[2] += a[2];
    if (_vel[0] < -10.0 || 10.0 < _vel[0]) _vel[0] -= a[0];
    if (_vel[1] < -10.0 || 10.0 < _vel[1]) _vel[1] -= a[1];
    if (_vel[2] < -10.0 || 10.0 < _vel[2]) _vel[2] -= a[2];
}

void Unit::accelerate(double deltaTime)
{
    std::vector<double> a = { _acc[0] * deltaTime, _acc[1] * deltaTime , _acc[2] * deltaTime };
    accelerate(a);
}

void Unit::rotate(double deltaTime)
{
    if (_isStoppingX && _isStoppingY)
        return;

    std::vector<double> targetFront = _acc;

    // normalize
    double targetFrontLength = sqrt(targetFront[0] * targetFront[0] + targetFront[1] * targetFront[1] + targetFront[2] * targetFront[2]);
    targetFront[0] /= targetFrontLength;
    targetFront[1] /= targetFrontLength;
    targetFront[2] /= targetFrontLength;
    //printf("targetFront: %f, %f, %f\n", targetFront[0], targetFront[1], targetFront[2]);

    double rotationSpeed = 3.0;

    double interpolationFactor = rotationSpeed * deltaTime;
    
    std::vector<double> interpolatedFront = slerp(_front, targetFront, interpolationFactor);

    _front = interpolatedFront;
    //printf("_front: %f, %f, %f\n", _front[0], _front[1], _front[2]);
}

std::vector<double> Unit::slerp(const std::vector<double>& start, const std::vector<double>& end, double t)
{
    double dotProduct = start[0] * end[0] + start[1] * end[1] + start[2] * end[2];
    double angle = std::acos(dotProduct);

    double sinAngle = std::sin(angle);
    double invSinAngle = 1.0 / sinAngle;

    double startWeight = std::sin((1.0 - t) * angle) * invSinAngle;
    double endWeight = std::sin(t * angle) * invSinAngle;

    std::vector<double> interpolatedVec;
    interpolatedVec.push_back(startWeight * start[0] + endWeight * end[0]);
    interpolatedVec.push_back(startWeight * start[1] + endWeight * end[1]);
    interpolatedVec.push_back(startWeight * start[2] + endWeight * end[2]);

    return interpolatedVec;
}

void Unit::animate(double deltaTime)
{
    accelerate(deltaTime);
    translate(deltaTime);
    rotate(deltaTime);

    //printf("_pos: %f, %f, %f\t", _pos[0], _pos[1], _pos[2]);
    //printf("_vel: %f, %f, %f\t", _vel[0], _vel[1], _vel[2]);
    //printf("_acc: %f, %f, %f\n", _acc[0], _acc[1], _acc[2]);
}

void Unit::move(Direction dir)
{
    switch (dir)
    {
    case Forward:
        _isStoppingY = false;
        _acc[1] = 10.0;
        break;
    case Backward:
        _isStoppingY = false;
        _acc[1] = -10.0;
        break;
    case Leftward:
        _isStoppingX = false;
        _acc[0] = -10.0;
        break;
    case Rightward:
        _isStoppingX = false;
        _acc[0] = 10.0;
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
            _acc[1] = 15.0;
        }
        else if (_vel[1] > 0.1)
        {
            _acc[1] = -15.0;
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
            _acc[0] = 15.0;
        }
        else if (_vel[0] > 0.1)
        {
            _acc[0] = -15.0;
        }
        else
        {
            _vel[0] = 0.0;
            _acc[0] = 0.0;
        }
    }
}

std::vector<double> Unit::getPos()
{
    return _pos;
}
