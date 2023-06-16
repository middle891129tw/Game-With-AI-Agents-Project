/*
* gameApp.cpp
*/

#include <GL/glut.h>
#include <stdio.h>
#include <chrono>
#include <map>

#include "gameApp.hpp"
#include "camera.hpp"

#define PI 3.14159

unsigned int _width  = 1280;
unsigned int _height = 720;

float _gridSize    = 30;
float _gridSpacing = 5;

double _collisionFactor = 160.0;

Camera camera;
PlayerUnit playerUnit;
BotUnit evilUnit1;
DefenderUnit evilUnit2(evilUnit1);
BotUnit evilUnit3;
BotUnit evilUnit4;

std::chrono::high_resolution_clock::time_point prevTime;
std::chrono::high_resolution_clock::time_point currTime;

std::map<char, bool> keyDown;

void setUpUnits()
{
    evilUnit1.setTeam(Unit::MARTIANS);
    evilUnit2.setTeam(Unit::MARTIANS);
    evilUnit3.setTeam(Unit::MARTIANS);
    evilUnit4.setTeam(Unit::MARTIANS);

    evilUnit1.setMode(BotUnit::WANDER);
    evilUnit3.setMode(BotUnit::ATTACK);
    evilUnit4.setMode(BotUnit::ATTACK);

    evilUnit1.addFriendlyUnit(evilUnit2);
    evilUnit3.addHostileUnit(playerUnit);
    evilUnit4.addHostileUnit(playerUnit);
}


#pragma region GL Rendering

void initializeGlut(int* argcPtr, char** argv)
{
    glutInit(argcPtr, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(_width, _height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Game");

    glutReshapeFunc(reshapeCallback);
    glutDisplayFunc(displayCallback);
    glutIdleFunc(idleCallback);
    glutKeyboardFunc(keyboardCallback);
    glutKeyboardUpFunc(keyboardUpCallback);
    //glutJoystickFunc(joystickCallback, 10);
}

void initializeOpenGL()
{
    glClearColor(0.05f, 0.10f, 0.15f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    prevTime = std::chrono::high_resolution_clock::now();
}

void makeProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspectRatio = static_cast<double>(_width) / _height;
    double fov = 45.0;
    double horizontalFov = 2.0 * atan(tan(fov * 0.5 * PI / 180.0) * aspectRatio) * 180.0 / PI;

    gluPerspective(horizontalFov, aspectRatio, 1.0, 100.0);

    glViewport(0, 0, _width, _height);
}

void makeView()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(	camera.getEye()		[0],
                camera.getEye()		[1],
                camera.getEye()		[2],
                camera.getCenter()	[0],
                camera.getCenter()	[1],
                camera.getCenter()	[2],
                camera.getUp()		[0],
                camera.getUp()		[1],
                camera.getUp()		[2]);
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    makeProjection();
    makeView();

    drawGrid();
    playerUnit.draw();
    evilUnit1.draw();
    evilUnit2.draw();
    evilUnit3.draw();
    evilUnit4.draw();

    glutSwapBuffers();
}

#pragma endregion

void handleCollisions()
{
    bool isCollidingp1 = handleCollision(playerUnit, evilUnit1);
    bool isCollidingp2 = handleCollision(playerUnit, evilUnit2);
    bool isCollidingp3 = handleCollision(playerUnit, evilUnit3);
    bool isCollidingp4 = handleCollision(playerUnit, evilUnit4);
    bool isColliding34 = handleCollision(evilUnit3, evilUnit4);
    playerUnit.setIsColliding(isCollidingp1 || isCollidingp2 || isCollidingp3 || isCollidingp4);
    evilUnit1.setIsColliding(isCollidingp1);
    evilUnit2.setIsColliding(isCollidingp2);
    evilUnit3.setIsColliding(isCollidingp3 || isColliding34);
    evilUnit4.setIsColliding(isCollidingp4 || isColliding34);
}

bool handleCollision(GameObject& a, GameObject& b)
{
    if ((a.getPos() - b.getPos()).magnitude() < a.getR() + b.getR())
    {
        Vector3 forceB2A(_collisionFactor * (a.getPos() - b.getPos()));;
        a.applyForce(forceB2A, b);
        Vector3 forceA2B(_collisionFactor * (b.getPos() - a.getPos()));;
        b.applyForce(forceA2B, a);
        return true;
    }
    else
    {
        return false;
    }
}

void drawGrid()
{
    glPushMatrix();
      glColor3f(0.8f, 0.8f, 0.8f);
      
      // Draw grid lines along X-axis
      for (float x = -_gridSize; x <= _gridSize; x += _gridSpacing)
      {
          glBegin(GL_LINES);
            glVertex3f(x, -_gridSize, 0.0f);
            glVertex3f(x,  _gridSize, 0.0f);
          glEnd();
      }
      
      // Draw grid lines along Y-axis
      for (float y = -_gridSize; y <= _gridSize; y += _gridSpacing)
      {
          glBegin(GL_LINES);
            glVertex3f(-_gridSize, y, 0.0f);
            glVertex3f( _gridSize, y, 0.0f);
          glEnd();
      }
    glPopMatrix();
}


#pragma region Callbacks

void reshapeCallback(int width, int height)
{
    _width = width;
    _height = height;
}

void displayCallback()
{
    renderScene();
}

void idleCallback()
{
    currTime = std::chrono::high_resolution_clock::now();
    double deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currTime - prevTime).count();
    prevTime = currTime;

    // control player unit
    if (keyDown['w'] && !keyDown['s'])
        playerUnit.move(Unit::FORWARD);
    else if (keyDown['s'] && !keyDown['w'])
        playerUnit.move(Unit::BACKWARD);
    else
        playerUnit.stop(Unit::FORWARD);

    if (keyDown['d'] && !keyDown['a'])
        playerUnit.move(Unit::RIGHTWARD);
    else if (keyDown['a'] && !keyDown['d'])
        playerUnit.move(Unit::LEFTWARD);
    else
        playerUnit.stop(Unit::RIGHTWARD);

    playerUnit.setIsDashing(keyDown[' ']);

    camera.setPos(playerUnit.getPos());

    // control enemy units
    //evilUnit1.wander();
    //evilUnit1.setMode(BotUnit::WANDER);
    //evilUnit1.addFriendlyUnit(evilUnit2);

    evilUnit2.defend();
    //evilUnit3.addHostileUnit(playerUnit);
    //evilUnit3.attack();
    //evilUnit3.setMode(BotUnit::ATTACK);
    //evilUnit4.attack();

    //printf("_acc: %f, %f\n", playerUnit.getAcc().getX(), playerUnit.getAcc().getY());
    handleCollisions();
    //printf("_acc: %f, %f\n", playerUnit.getAcc().getX(), playerUnit.getAcc().getY());
    //printf("_vel: %f, %f\n\n", playerUnit.getVel().getX(), playerUnit.getVel().getY());


    playerUnit.update(deltaTime);
    evilUnit1.update(deltaTime);
    evilUnit2.update(deltaTime);
    evilUnit3.update(deltaTime);
    evilUnit4.update(deltaTime);

    renderScene();
}

void keyboardCallback(unsigned char key, int, int)
{
    keyDown[key] = true;
    switch (key)
    {
    case 'f':
        glutFullScreen();
        break;
    case 'r':
        playerUnit.reset();
        evilUnit1.reset();
        evilUnit2.reset();
        evilUnit3.reset();
        evilUnit4.reset();
    default:
        break;
    }
}

void keyboardUpCallback(unsigned char key, int, int)
{
    keyDown[key] = false;
}

void joystickCallback(unsigned int buttonMask, int x, int y, int z)
{
    if (x < -512)
    {
        keyDown['a'] = true;
        keyDown['d'] = false;
    }
    else if (x > 512)
    {
        keyDown['a'] = false;
        keyDown['d'] = true;
    }
    else
    {
        keyDown['a'] = keyDown['d'] = false;
    }
    if (y < -512)
    {
        keyDown['w'] = true;
        keyDown['s'] = false;
    }
    else if (y > 512)
    {
        keyDown['w'] = false;
        keyDown['s'] = true;
    }
    else
    {
        keyDown['w'] = keyDown['s'] = false;
    }
}

#pragma endregion


int main(int argc, char** argv)
{
    printf("Hello world!\n");
    setUpUnits();
    initializeGlut(&argc, argv);
    initializeOpenGL();
    glutMainLoop();
    return 0;
}