#include "RadarPPI.h"
#include <ctime>
#include <GL/freeglut.h>
#include <limits>
#include <chrono>
#include <iostream>

CRadarPPI* radarPPI = nullptr;

float seekerAngle = 0.0f;

typedef struct {
    double dist_km;
    double angle_deg;
    double height_m;
    double seeker_deg;
} Scope_Data;

Scope_Data data[100];

void timerFunc(int value) {
    int randNum = rand() % 100;  // Random number of enemies (0 to 99)
    for (int i = 0; i < randNum; ++i) {
        seekerAngle += rand() % 5 + 1.0f;
        
        data[i].seeker_deg = seekerAngle;
        data[i].dist_km = rand() % 300;  // Random distance (0 to 299 km)
        data[i].angle_deg = rand() % 361;  // Random angle (0 to 360 degrees)
        data[i].height_m = rand() % 16 + 15;  // Random height (15 to 30 meters)
        std::cout << data[i].dist_km << std::endl;
    }

    radarPPI->addEnemy(data, randNum);  

    glutTimerFunc(value, timerFunc, value);
}

int main() {
    unsigned int seed = static_cast<unsigned int>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
        );
    srand(seed);

    CRadarDisplay display;
    radarPPI = new CRadarPPI(&display);

    radarPPI->run();

    timerFunc(1000);  
    radarPPI->setHeightUplimit(35); 
    radarPPI->setOuterRange(350);    

    radarPPI->endRadarPPI();
    return 0;
}
