/*
* gameObject.hpp
*/

#pragma once

#include "vector3.hpp"

class GameObject
{
protected:
    Vector3 _pos;   // position
    Vector3 _vel;   // velocity
    Vector3 _acc;   // acceleration
    Vector3 _front; // front direction
    double _radius;
    double _mass;

public:
    GameObject();
    ~GameObject();

    void virtual draw();

    void translate(Vector3 deltaPos);
    void translate(double deltaTime);
    void accelerate(Vector3 deltaVel);
    void accelerate(double deltaTime);
    void turn();

    void update(double deltaTime);
};

