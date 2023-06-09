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

float _gridSize    = 25;
float _gridSpacing = 5;

double _collisionFactor = 80.0;

Camera camera;
PlayerUnit playerUnit;
BotUnit enemyUnit1;
DefenderUnit enemyUnit2(&enemyUnit1);
AttackerUnit enemyUnit3(&playerUnit);

std::chrono::high_resolution_clock::time_point prevTime;
std::chrono::high_resolution_clock::time_point currTime;

std::map<char, bool> keyDown;

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
    enemyUnit1.draw();
    enemyUnit2.draw();
    enemyUnit3.draw();

    glutSwapBuffers();
}

#pragma endregion

void handleCollisions()
{
    bool isColliding1 = handleCollision(playerUnit, enemyUnit1);
    bool isColliding2 = handleCollision(playerUnit, enemyUnit3);
    bool isColliding3 = handleCollision(playerUnit, enemyUnit2);
    playerUnit.setIsColliding( isColliding1 || isColliding2 || isColliding3);
    enemyUnit1.setIsColliding(isColliding1);
    enemyUnit2.setIsColliding(isColliding2);
    enemyUnit3.setIsColliding(isColliding3);
}

bool handleCollision(GameObject& a, GameObject& b)
{
    if ((a.getPos() - b.getPos()).magnitude() < a.getR() + b.getR())
    {
        Vector3 forceB2A(_collisionFactor * (a.getPos() - b.getPos()));;
        a.applyForce(forceB2A);
        Vector3 forceA2B(_collisionFactor * (b.getPos() - a.getPos()));;
        b.applyForce(forceA2B);
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
    std::chrono::duration<double> deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currTime - prevTime);
    prevTime = currTime;

    // control player unit
    if (keyDown['w'] && !keyDown['s'])
        playerUnit.move(Unit::Forward);
    else if (keyDown['s'] && !keyDown['w'])
        playerUnit.move(Unit::Backward);
    else
        playerUnit.stop(Unit::Forward);

    if (keyDown['d'] && !keyDown['a'])
        playerUnit.move(Unit::Rightward);
    else if (keyDown['a'] && !keyDown['d'])
        playerUnit.move(Unit::Leftward);
    else
        playerUnit.stop(Unit::Rightward);
    //if (keyDown[' '])
    //    playerUnit.dash();

    camera.setPos(playerUnit.getPos());

    // control enemy units
    enemyUnit1.wander();
    enemyUnit2.defend();
    enemyUnit3.attack();

    //printf("_acc: %f, %f\n", playerUnit.getAcc().getX(), playerUnit.getAcc().getY());
    handleCollisions();
    //printf("_acc: %f, %f\n", playerUnit.getAcc().getX(), playerUnit.getAcc().getY());
    //printf("_vel: %f, %f\n\n", playerUnit.getVel().getX(), playerUnit.getVel().getY());


    playerUnit.update(deltaTime.count());
    enemyUnit1.update(deltaTime.count());
    enemyUnit2.update(deltaTime.count());
    enemyUnit3.update(deltaTime.count());

    renderScene();
}

void keyboardCallback(unsigned char key, int, int)
{
    keyDown[key] = true;
    switch (key)
    {
    case 'q':
        printf("quit ");
        break;
    default:
        break;
    }
}

void keyboardUpCallback(unsigned char key, int, int)
{
    keyDown[key] = false;
}

#pragma endregion


int main(int argc, char** argv)
{
    printf("Hello world!\n");

    initializeGlut(&argc, argv);
    initializeOpenGL();
    glutMainLoop();


    return 0;
}