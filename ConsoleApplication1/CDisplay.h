#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include "_Variables.h"
#include "CDrawingLabels.h"

using std::vector;

class CDisplay {
public:
    void setCallbacks();
    static CDisplay& getInstance();
    void enemyWrapper(float distance, float angle, float height);
    //void enemyWrapper(float* distance, float* angle, float* height);
    ~CDisplay();
private:
    
    struct Enemy {
        float realDistance;
        float angle;
        float height;
        float distance;
        float realDist;
        float x;
        float y;
        float lastX = 0.0f;
        float lastY = 0.0f;
        float hX;
        float hY;
        int lastDetectionTime;
        bool once;
        bool isHighlighted;
        bool visited;
        float fadeAlpha;
    };

    Enemy* enemies;        
    int enemyCount;        
    int enemyCapacity;

    void display();
    void enemyHighlight();

    void updateAngle();
    void setOuterRange(float range);

    static void timerWrapper(int value);
    static void displayWrapper();
    void addEnemy(float distance, float angle, float height);
    //void addEnemy(float* distance, float* angle, float* height);
    float findClosestEnemyAngle();
    void expandEnemyArray(); // New function to expand the dynamic array
    void removeEnemy(int index);
};

extern CDisplay radar;

#endif // DISPLAY_H