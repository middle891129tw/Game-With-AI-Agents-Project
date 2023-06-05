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

Camera camera;
PlayerUnit playerUnit;
EnemyUnit enemyUnit;
DefenderUnit defenderUnit(&enemyUnit);
AttackerUnit attackerUnit(&playerUnit);

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
    enemyUnit.draw();
    defenderUnit.draw();
    attackerUnit.draw();

    glutSwapBuffers();
}

#pragma endregion

void handleCollision()
{
    if (playerUnit.getPos()[0] - enemyUnit.getPos()[0])
    {
        ;
    }
}


void drawGrid()
{
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

    if (keyDown['w'])
        playerUnit.move(Unit::Forward);
    else if (keyDown['s'])
        playerUnit.move(Unit::Backward);
    else
        playerUnit.stop(Unit::Forward);

    if (keyDown['d'])
        playerUnit.move(Unit::Rightward);
    else if (keyDown['a'])
        playerUnit.move(Unit::Leftward);
    else
        playerUnit.stop(Unit::Rightward);

    playerUnit.animate(deltaTime.count());
    camera.setPos(playerUnit.getPos());

    enemyUnit.wander();
    enemyUnit.animate(deltaTime.count());

    defenderUnit.defend();
    defenderUnit.animate(deltaTime.count());

    attackerUnit.attack();
    attackerUnit.animate(deltaTime.count());

    handleCollision();

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