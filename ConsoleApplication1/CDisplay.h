#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

class CDisplay {
public:
    void setCallbacks();
    void addEnemy(float distance, float angle, float height, float seekerAngle);
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
    void drawEnemyHighlight();
    void calculateEnemyHighlight();
    void updateAngle();
    void setOuterRange(float range);

    static void timerWrapper(int value);
    static void displayWrapper();
    
    void expandEnemyArray();
    void removeEnemy(int index);
};


#endif // DISPLAY_H