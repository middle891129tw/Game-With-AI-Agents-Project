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

void GameObject::translate(Vector3 t)
{
}

void GameObject::translate(double deltaTime)
{
}

void GameObject::accelerate(Vector3 a)
{
}

void GameObject::accelerate(double deltaTime)
{
}

void GameObject::draw()
{
}

void GameObject::animate(double deltaTime)
{
}

void GameObject::update(double deltaTime)
{
}
