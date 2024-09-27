#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

class CDisplay {
public:
    void setCallbacks();
    void enemyWrapper(float distance, float angle, float height, bool clockwise);
    ~CDisplay();
    
    static CDisplay& getInstance();
private:
    
    struct Enemy {
        float realDistance;
        float angle;
        float height;
        float distance;
        float x;
        float y;
        float lastX;
        float lastY;
        float hX;
        float hY;
        int lastDetectionTime;
        bool once;
        bool isHighlighted;
        bool visited;
        float fadeAlpha;
        float highlightedRange;
        bool changedRange;
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
    void addEnemy(float distance, float angle, float height, bool clockwise);
    float findClosestEnemyAngle();
    void expandEnemyArray();
    void removeEnemy(int index);
};


#endif // DISPLAY_H