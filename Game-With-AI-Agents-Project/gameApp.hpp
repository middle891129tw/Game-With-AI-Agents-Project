/*
* gameApp.hpp
*/

#pragma once

#include "playerUnit.hpp"
#include "enemyUnit.hpp"
#include "defenderUnit.hpp"
#include "attackerUnit.hpp"


void reshapeCallback(int, int);
void displayCallback();
void idleCallback();
void keyboardCallback(unsigned char, int, int);
void keyboardUpCallback(unsigned char, int, int);

void makeProjection();
void makeView();

void renderScene();
void drawGrid();