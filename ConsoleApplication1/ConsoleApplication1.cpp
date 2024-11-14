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
bool once = false;
CRadarPPI* radarPPI = nullptr;

void timerFunc(int value) {
    while (true) {
        int randNum = 2;
        
        for (int i = 0; i < randNum; ++i) {

            data[i].seeker_deg = seekerAngle % 360;
            data[i].dist_km = rand() % 300;
            data[i].angle_deg = seekerAngle % 360;
            data[i].height_m = rand () % 3000;
        }

        radarPPI->addEnemy(data, randNum);
        
        //seekerAngle += 1.0f;
        if (seekerAngle < 120.0f && !once)
            seekerAngle += 1.0f;
        else if (seekerAngle == 0 && once) {
            once = false;
         
        }
        else {
            once = true;
            seekerAngle -= 1.0f;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(value));
    }
}

int main() {
    std::thread t(timerFunc, 20);
    t.detach();
    CRadarDisplay display;
    radarPPI = new CRadarPPI(&display);

    radarPPI->run();
    radarPPI->setHighlightDuration(2); //Default value is 10 inside the code, at 40ms duration of 10 last about a rotation. Decrease the value to highlight on screen less.
    radarPPI->endRadarPPI();
}


