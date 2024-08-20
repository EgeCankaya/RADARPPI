#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <cmath>
#include <GL/freeglut.h>

#include "Variables.h"
#include "DrawingLabels.h"

using std::vector;

class Display {
public:
    void setCallbacks();
    static Display& getInstance();
    static void enemyWrapper(float distance, float angle, float height);
    void addEnemy(float distance, float angle, float height);
private:
    struct Point {
        float x;
        float y;
        float height;
        float distance;
        float lastX = 0.0f;
        float lastY = 0.0f;
    };

    struct Enemy {
        float distance;
        float angle;
        float height;
        bool isHighlighted;
        float realDistance;
        int lastDetectionTime;
        bool once;
    };

    vector<Enemy> enemies;

    Point calculateObjectPosition(float distance, float angle);
    void display();
    void enemyHighlight();
    
    
    void updateAngle();
    void setOuterRange(float range);

    static void timerWrapper(int value);
    static void displayWrapper();
};

extern Display radar;

#endif // DISPLAY_H

