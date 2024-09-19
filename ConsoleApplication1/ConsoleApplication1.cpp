#include "RadarPPI.h"
#include <cmath>
#include <ctime>
#include <GL/freeglut.h>
#include <iostream>

CRadarPPI* radarPPI = nullptr;

float distance1 = 100.0f;
float angle1 = 45.0f;
float height1 = 20.0f;


void timerFunc(int value) {
    
    angle1 = rand() % 360;
    distance1 = rand() % 300;
    height1 = rand() % 14 + 15;
    radarPPI->addEnemy(distance1, angle1, height1);
    glutTimerFunc(value, timerFunc, value);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    CRadarDisplay display;
    radarPPI = new CRadarPPI(&display);

    radarPPI->run();
    radarPPI->addEnemy(distance1, angle1, height1);

    timerFunc(1000);
    radarPPI->setHeightUplimit(35);
    int h = radarPPI->getHeightUplimit();

    std::cout << h << std::endl;

    radarPPI->endRadarPPI();
    return 0;
}

