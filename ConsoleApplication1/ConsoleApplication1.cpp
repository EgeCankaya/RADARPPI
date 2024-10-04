#include "RadarPPI.h"
#include <ctime>
#include <GL/freeglut.h>
#include <limits> 

CRadarPPI* radarPPI = nullptr;

float distance1 = std::numeric_limits<float>::quiet_NaN();
float angle1 = std::numeric_limits<float>::quiet_NaN();
float height1 = std::numeric_limits<float>::quiet_NaN();
int randNum = 0;
bool clockwiseCheck = false;

typedef struct {
    double dist_km;
    double angle_deg;
    double height_m;
    double seeker_deg;
}Scope_Data;

void timerFunc(int value) {
    randNum = rand() % 5;
    if (randNum < 2) {
        clockwiseCheck = true;
    }
    
    angle1 = std::numeric_limits<float>::quiet_NaN();
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
    radarPPI->setSeekerSpeed(1.5f);

    radarPPI->endRadarPPI();
    return 0;
}

