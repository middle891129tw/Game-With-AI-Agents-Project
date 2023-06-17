/*
* gameObject.cpp
*/

#include <stdio.h>

#include "gameObject.hpp"

GameObject::GameObject() : _pos(0.0, 0.0, 0.0),
                           _vel(0.0, 0.0, 0.0),
                           _acc(0.0, 0.0, 0.0),
                           _front(0.0, 1.0, 0.0),
                           _minPos(-29.5, -29.5, -1.0),
                           _maxPos( 29.5,  29.5,  1.0),
                           _maxSpeed(15.0),
                           _turnSpeed(3.0),
                           _r(1.0),
                           _m(1.0),
                           _timeSinceUpdate(0.0),
                           _isColliding(false)
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
    if (_pos[0] < _minPos[0] + _r * 2.0)
        _pos[0] = _minPos[0] + _r * 2.0;
    if (_pos[1] < _minPos[1] + _r * 2.0)
        _pos[1] = _minPos[1] + _r * 2.0;

    if (_pos[0] > _maxPos[0] - _r * 2.0)
        _pos[0] = _maxPos[0] - _r * 2.0;
    if (_pos[1] > _maxPos[1] - _r * 2.0)
        _pos[1] = _maxPos[1] - _r * 2.0;
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

void GameObject::applyForce(Vector3 force, GameObject& source)
{
    // virtual

    if (_m <= 0.0)
        return;

    _acc[0] += force[0] / _m;
    _acc[1] += force[1] / _m;
}

void GameObject::update(double deltaTime)
{
    accelerate(deltaTime);
    translate(deltaTime);
    turn(deltaTime);
}

Vector3 GameObject::getPos() const
{
    return _pos;
}

Vector3 GameObject::getVel() const
{
    return _vel;
}

Vector3 GameObject::getAcc() const
{
    return _acc;
}

Vector3 GameObject::getFront() const
{
    return _front;
}

double GameObject::getR() const
{
    return _r;
}

void GameObject::setIsColliding(bool isColliding)
{
    _isColliding = isColliding;
}
