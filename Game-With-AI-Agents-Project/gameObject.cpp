/*
* gameObject.cpp
*/

#include "gameObject.hpp"

GameObject::GameObject() : _pos(0.0, 0.0, 0.0),
                           _vel(0.0, 0.0, 0.0),
                           _acc(0.0, 0.0, 0.0),
                           _front(0.0, 1.0, 0.0),
                           _radius(1.0),
                           _mass(1.0)
{
}

GameObject::~GameObject()
{
}

void GameObject::draw()
{
}

void GameObject::translate(Vector3 deltaPos)
{
    _pos += deltaPos;
}

void GameObject::translate(double deltaTime)
{
    translate(_vel * deltaTime);
}

void GameObject::accelerate(Vector3 deltaVel)
{
    _vel += deltaVel;
}

void GameObject::accelerate(double deltaTime)
{
    translate(_acc * deltaTime);
}

void GameObject::turn()
{
    // TODO
}

void GameObject::update(double deltaTime)
{
    accelerate(deltaTime);
    translate(deltaTime);
    turn();
}
