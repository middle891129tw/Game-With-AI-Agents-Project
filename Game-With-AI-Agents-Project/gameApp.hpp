/*
* gameApp.hpp
*/

#pragma once

#include "playerUnit.hpp"
#include "botUnit.hpp"
#include "defenderUnit.hpp"
#include "attackerUnit.hpp"


void reshapeCallback(int, int);
void displayCallback();
void idleCallback();
void keyboardCallback(unsigned char, int, int);
void keyboardUpCallback(unsigned char, int, int);
void joystickCallback(unsigned int, int, int, int);

void makeProjection();
void makeView();

void handleCollisions();
bool handleCollision(GameObject& a, GameObject& b);

void renderScene();
void drawGrid();