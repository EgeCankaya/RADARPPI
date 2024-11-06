#include "RadarPPI.h"
#include <ctime>
#include <chrono>
#include <iostream> 
#include <cstdlib>
#include <thread>

typedef struct {
    float dist_km;
    float angle_deg;
    float height_m;
    float seeker_deg;
} Scope_Data;

Scope_Data data[100];

int seekerAngle = 0;
CRadarPPI* radarPPI = nullptr;

void timerFunc(int value) {
    while (true) {
        int randNum = 3;
        
        for (int i = 0; i < randNum; ++i) {

            data[i].seeker_deg = seekerAngle % 360;
            data[i].dist_km = rand() % 300;
            data[i].angle_deg = rand() % 360;
            data[i].height_m = rand () % 3000;
        }

        radarPPI->addEnemy(data, randNum);
        
        seekerAngle += 1.0f;
        std::this_thread::sleep_for(std::chrono::milliseconds(value));
    }
}

int main() {
    std::thread t(timerFunc, 40);
    t.detach();
    CRadarDisplay display;
    radarPPI = new CRadarPPI(&display);

    radarPPI->run();
    radarPPI->setHighlightDuration(10); //Default value is 10 inside the code, at 40ms duration of 10 last about a rotation. Decrease the value to highlight on screen less.
    radarPPI->endRadarPPI();
}


