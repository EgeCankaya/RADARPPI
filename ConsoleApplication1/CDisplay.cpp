#include "CDisplay.h"
#include <cmath>
#include <GL/freeglut.h>
#include "_Variables.h"
#include "CDrawingLabels.h"
#include <iostream>

_Variables* _VarsDisp = _Variables::getInstance();
CDrawingLabels& label = CDrawingLabels::getInstance();

CDisplay& CDisplay::getInstance() {
    static CDisplay instance;
    return instance;
}

CDisplay::~CDisplay() {
    delete[] enemies;
}

void CDisplay::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (_VarsDisp->getCurrentScreen() == Screen::Main) {
        glColor3f(0.0f, 0.75f, 0.0f);
        label.drawCircle(0.0f, 0.0f, 0.90f, 100);
        glColor3f(0.0f, 0.50f, 0.0f);
        label.drawCircle(0.0f, 0.0f, 0.30f, 100);
        label.drawCircle(0.0f, 0.0f, 0.60f, 100);
        label.drawLinesWithAngles(_VarsDisp->getLineGap());
        label.drawRangeLabels();
        label.drawButtons();
        drawEnemyHighlight();

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(_VarsDisp->getAngle(), 0.0f, 0.0f, -1.0f);
        glTranslatef(0.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 0.75f, 0.0f);
        label.drawSeeker();
        glPopMatrix();
    }
    else if (_VarsDisp->getCurrentScreen() == Screen::Settings) {
        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        label.drawButtons();
        label.drawCurrentValues();
        label.drawBox();
    }
    glFlush();
}

void CDisplay::updateAngle() {
    float targetAngle = findClosestEnemyAngle();
    float angleDiff = targetAngle - _VarsDisp->getAngle();

    if (angleDiff > 180.0f) {
        angleDiff -= 360.0f;
    }
    else if (angleDiff < -180.0f) {
        angleDiff += 360.0f;
    }

    _VarsDisp->setAngle(fmod(_VarsDisp->getAngle(), 360.0f));
    if (_VarsDisp->getAngle() < 0) {
        _VarsDisp->addToAngle(360.0f);
    }
    calculateEnemyHighlight();

    glutPostRedisplay();
    glutTimerFunc(16, timerWrapper, 0);
}

void CDisplay::calculateEnemyHighlight() {
    for (int i = 0; i < enemyCount; ++i) {
        Enemy& enemy = enemies[i];

        if (enemy.height < _VarsDisp->getHeightLowlimit() || enemy.height > _VarsDisp->getHeightUplimit()) {
            removeEnemy(i);
            continue;
        }

        if (!enemy.isHighlighted) {
            enemy.fadeAlpha = 1.0f;
            enemy.distance = 0.90f / (_VarsDisp->getOuterRange() / enemy.realDistance);
            enemy.x = enemy.distance * cosf(enemy.angle * M_PI / 180.0f) / _VarsDisp->getRangeScale();
            enemy.y = enemy.distance * -sinf(enemy.angle * M_PI / 180.0f) / _VarsDisp->getRangeScale();
        }

        float angleTolerance = _VarsDisp->getSeekerSpeed();
        float angleDiff = _VarsDisp->getAngle() - enemy.angle;

        if (angleDiff > 180.0f) {
            angleDiff -= 360.0f;
        }

        else if (angleDiff < -180.0f) {
            angleDiff += 360.0f;
        }

        if (_VarsDisp->getClockwise() && angleDiff >= 0 && angleDiff <= angleTolerance && !enemy.visited) {
            enemy.isHighlighted = true;
            enemy.fadeAlpha = 1.0f;
            enemy.visited = true;
        }
        else if (!_VarsDisp->getClockwise() && angleDiff <= 0 && angleDiff >= -angleTolerance && !enemy.visited) {
            enemy.isHighlighted = true;
            enemy.fadeAlpha = 1.0f;
            enemy.visited = true;
        }

        if (enemy.fadeAlpha >= 0.05f && _VarsDisp->getOuterRange() >= enemy.highlightedRange) {
            enemy.distance = 0.90f / (_VarsDisp->getOuterRange() / enemy.realDistance);
            enemy.x = enemy.distance * cosf(enemy.angle * M_PI / 180.0f) / _VarsDisp->getRangeScale();
            enemy.y = enemy.distance * -sinf(enemy.angle * M_PI / 180.0f) / _VarsDisp->getRangeScale();
        }

        if (enemy.fadeAlpha <= 0.05f && enemy.visited) {
            removeEnemy(i);
            --i;
        }

        if (enemy.visited) {
            enemy.fadeAlpha -= 0.011f / _VarsDisp->getHighlightDuration();
        }
    }
}

void CDisplay::addEnemy(float distance, float angle, float height, float seekerAngle) {
    if (enemyCount == enemyCapacity) {
        expandEnemyArray();
    }
    
    if (seekerAngle < _VarsDisp->getClockwiseCheck()) {
        if (seekerAngle != 0 && (_VarsDisp->getClockwiseCheck() < 359.0f)) {
            _VarsDisp->setClockwise(false);
        }
        _VarsDisp->setClockwiseCheck(seekerAngle);
    }

    else if (seekerAngle > _VarsDisp->getClockwiseCheck()) {
        if (seekerAngle != 0 && (_VarsDisp->getClockwiseCheck() > 1)) {
            _VarsDisp->setClockwise(true);
        }
        _VarsDisp->setClockwiseCheck(seekerAngle);
    }

    else {
        _VarsDisp->setClockwiseCheck(seekerAngle);
    }

    _VarsDisp->setAngle(seekerAngle);
    enemies[enemyCount].realDistance = distance;
    enemies[enemyCount].angle = angle;
    enemies[enemyCount].height = height;
    enemies[enemyCount].distance = 0.0f;
    enemies[enemyCount].x = 0.0f;
    enemies[enemyCount].y = 0.0f;
    enemies[enemyCount].lastX = 0.0f;
    enemies[enemyCount].lastY = 0.0f;
    enemies[enemyCount].hX = 0.0f;
    enemies[enemyCount].hY = 0.0f;
    enemies[enemyCount].isHighlighted = false;
    enemies[enemyCount].visited = false;
    enemies[enemyCount].fadeAlpha = 0.0f;
    enemies[enemyCount].highlightedRange = 0.0f;
    enemies[enemyCount].changedRange = false;
    enemyCount++;
}

void CDisplay::expandEnemyArray() {
    enemyCapacity = (enemyCapacity == 0) ? 1 : enemyCapacity * 2;
    Enemy* newEnemies = new Enemy[enemyCapacity];

    for (int i = 0; i < enemyCount; ++i) {
        newEnemies[i] = enemies[i];
    }

    delete[] enemies;
    enemies = newEnemies;
}

void CDisplay::drawEnemyHighlight() {
    for (int i = 0; i < enemyCount; ++i) {
        Enemy& enemy = enemies[i];
        
        if (enemy.isHighlighted && ((_VarsDisp->getMousePosX() > enemy.x - 0.01f) && (_VarsDisp->getMousePosX() < enemy.x + 0.01f) && (_VarsDisp->getMousePosY() > enemy.y - 0.01f) && (_VarsDisp->getMousePosY() < enemy.y + 0.01f)) && !enemy.changedRange && enemy.realDistance < _VarsDisp->getOuterRange()) {
            glColor3f(1.0f, 1.0f, 1.0f);
            char buffer[256];
            sprintf_s(buffer, "h:%.0fm ", enemy.height);
            label.renderValues(enemy.x + 0.05f, enemy.y + 0.05f, buffer);

            sprintf_s(buffer, "d:%.0fkm ", enemy.realDistance);
            label.renderValues(enemy.x + 0.05f, enemy.y, buffer);
        }

        if (enemy.isHighlighted && enemy.realDistance < _VarsDisp->getOuterRange()) {
            if (enemy.fadeAlpha >= 0.05f && _VarsDisp->getOuterRange() >= enemy.highlightedRange && !enemy.changedRange) {
                glColor3f(0.0f, enemy.fadeAlpha, 0.0f);
                glPushMatrix();
                glTranslatef(enemy.x, enemy.y, 1.0f);
                glBegin(GL_TRIANGLE_FAN);
                label.drawCircle(0.0f, 0.0f, 0.01f, 100);
                glEnd();
                glPopMatrix();
            }
        }
    }
}

void CDisplay::removeEnemy(int index) {
    for (int i = index; i < enemyCount - 1; ++i) {
        enemies[i] = enemies[i + 1];
    }
    enemyCount--;
}

float CDisplay::findClosestEnemyAngle() {
    float minAngleDiff = 360.0f;
    float closestEnemyAngle = _VarsDisp->getAngle();

    for (int i = 0; i < enemyCount; ++i) {
        Enemy& enemy = enemies[i];

        if (enemy.height < _VarsDisp->getHeightLowlimit() || enemy.height > _VarsDisp->getHeightUplimit() || enemy.visited) {
            continue;
        }

        float enemyAngle = enemy.angle;
        float angleDiff = fabsf(_VarsDisp->getAngle() - enemyAngle);

        if (angleDiff > 180.0f) {
            angleDiff = 360.0f - angleDiff;
        }

        if (angleDiff < minAngleDiff) {
            minAngleDiff = angleDiff;
            closestEnemyAngle = enemyAngle;
        }
    }
    return closestEnemyAngle;
}

void CDisplay::setOuterRange(float range) {
    _VarsDisp->setOuterRange(range);
}

void CDisplay::timerWrapper(int value) {
    getInstance().updateAngle();
}

void CDisplay::displayWrapper() {
    getInstance().display();
}

void CDisplay::setCallbacks() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutTimerFunc(0, timerWrapper, 0);
    glutDisplayFunc(displayWrapper);
}