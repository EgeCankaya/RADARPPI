#include "RadarPPI.h"
#include <cmath>
#include <ctime>
#include <GL/freeglut.h>
#include <iostream>

CRadarPPI* radarPPI = nullptr;

float distance1 = 100.0f;
float angle1 = 45.0f;
float height1 = 20.0f;
float randNum = 0.0f;
bool clockwiseCheck = false;

void timerFunc(int value) {
    randNum = rand() % 5;
    if (randNum == 5.0f) {
        clockwiseCheck = true;
    }
    
    angle1 = rand() % 360;
    distance1 = rand() % 300;
    height1 = rand() % 14 + 15;
    radarPPI->addEnemy(distance1, angle1, height1, clockwiseCheck);
    glutTimerFunc(value, timerFunc, value);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    CRadarDisplay display;
    radarPPI = new CRadarPPI(&display);

    radarPPI->run();
    radarPPI->addEnemy(distance1, angle1, height1, clockwiseCheck);

    timerFunc(1000);
    radarPPI->setHeightUplimit(35);
    radarPPI->setOuterRange(350);
    int h = radarPPI->getHeightUplimit();
    radarPPI->endRadarPPI();
    return 0;
}

