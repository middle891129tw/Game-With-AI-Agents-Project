/*
* gameObject.hpp
*/

#pragma once

#include "vector3.hpp"

class GameObject
{
protected:
    Vector3 _pos;       // position
    Vector3 _vel;       // velocity
    Vector3 _acc;       // acceleration
    Vector3 _front;     // front direction
    Vector3 _minPos;
    Vector3 _maxPos;
    double _maxSpeed;
    double _turnSpeed;
    double _radius;
    double _mass;

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
    void applyForce(Vector3 force);

    void update(double deltaTime);

    Vector3 getPos();
    Vector3 getVel();
    Vector3 getAcc();
    Vector3 getFront();
    double getRadius();
};

