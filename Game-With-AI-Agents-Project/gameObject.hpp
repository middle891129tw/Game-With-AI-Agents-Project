/*
* gameObject.hpp
*/

#pragma once

#include "vector3.hpp"

class GameObject
{
protected:
    Vector3     _pos;       // position
    Vector3     _vel;       // velocity
    Vector3     _acc;       // acceleration
    Vector3     _front;     // front direction
    Vector3     _minPos;
    Vector3     _maxPos;
    double      _maxSpeed;
    double      _turnSpeed;
    double      _r;          // radius
    double      _m;          // mass
    double      _timeSinceUpdate;
    bool        _isColliding;

public:
    GameObject();
    ~GameObject();

    void virtual draw();
    void confinePos();
    void confineVel();
    void translate(Vector3 deltaPos);
    void translate(double deltaTime);
    void accelerate(Vector3 deltaVel);
    void accelerate(double deltaTime);
    void virtual turn(double deltaTime);
    void virtual applyForce(Vector3 force, GameObject& source);
    void virtual update(double deltaTime);

    Vector3 getPos() const;
    Vector3 getVel() const;
    Vector3 getAcc() const;
    Vector3 getFront() const;
    double getR() const;

    void setIsColliding(bool isColliding);
};

