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

public:
    GameObject();
    ~GameObject();

    void update(double deltaTime);
};

