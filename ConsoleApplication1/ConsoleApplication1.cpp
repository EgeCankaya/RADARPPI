#include "RadarPPI.h"
#include <ctime>
#include <GL/freeglut.h>
#include <iostream>

CRadarPPI* radarPPI = nullptr;

float distance1 = NULL;
float angle1 = NULL;
float height1 = NULL;
int randNum = 0;
bool clockwiseCheck = false;

void timerFunc(int value) {
    randNum = rand() % 5;
    if (randNum < 2) {
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
    radarPPI->endRadarPPI();
    return 0;
}

