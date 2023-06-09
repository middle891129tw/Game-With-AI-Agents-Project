/*
* gameObject.cpp
*/

#include <stdio.h>

#include "gameObject.hpp"

GameObject::GameObject() : _pos(0.0, 0.0, 0.0),
                           _vel(0.0, 0.0, 0.0),
                           _acc(0.0, 0.0, 0.0),
                           _front(0.0, 1.0, 0.0),
                           _minPos(-25.0, -25.0, -1.0),
                           _maxPos( 25.0,  25.0,  1.0),
                           _maxSpeed(15.0),
                           _turnSpeed(3.0),
                           _radius(1.0),
                           _mass(1.0)
{
}

GameObject::~GameObject()
{
}

void GameObject::draw()
{
    // virtual
}

void GameObject::confinePos()
{
    if (_pos[0] < _minPos[0] + _radius * 2.0)
        _pos[0] = _minPos[0] + _radius * 2.0;
    if (_pos[1] < _minPos[1] + _radius * 2.0)
        _pos[1] = _minPos[1] + _radius * 2.0;

    if (_pos[0] > _maxPos[0] - _radius * 2.0)
        _pos[0] = _maxPos[0] - _radius * 2.0;
    if (_pos[1] > _maxPos[1] - _radius * 2.0)
        _pos[1] = _maxPos[1] - _radius * 2.0;
}

void GameObject::confineVel()
{
    if (_vel.magnitude() > _maxSpeed)
        _vel = _maxSpeed * _vel.normalized();
}

void GameObject::translate(Vector3 deltaPos)
{
    _pos += deltaPos;
    confinePos();
}

void GameObject::translate(double deltaTime)
{
    translate(_vel * deltaTime);
}

void GameObject::accelerate(Vector3 deltaVel)
{
    _vel += deltaVel;
    confineVel();
}

void GameObject::accelerate(double deltaTime)
{
    accelerate(_acc * deltaTime);
}

void GameObject::turn(double deltaTime)
{
    Vector3 targetFront = _acc.normalized();
    double interpolationFactor = _turnSpeed * deltaTime;
    Vector3 interpolatedFront = Vector3::slerp(_front, targetFront, interpolationFactor);
    _front = interpolatedFront;
}

void GameObject::applyForce(Vector3 force)
{
    if (_mass <= 0.0)
        return;

    _acc[0] += force[0] / _mass;
    _acc[1] += force[1] / _mass;
}

void GameObject::update(double deltaTime)
{
    accelerate(deltaTime);
    translate(deltaTime);
    turn(deltaTime);
}

Vector3 GameObject::getPos()
{
    return _pos;
}

Vector3 GameObject::getVel()
{
    return _vel;
}

Vector3 GameObject::getAcc()
{
    return _acc;
}

Vector3 GameObject::getFront()
{
    return _front;
}

double GameObject::getRadius()
{
    return _radius;
}
