#include "CDisplay.h"
#include <cmath>
#include <GL/freeglut.h>

CDisplay& CDisplay::getInstance() {
    static CDisplay instance;
    return instance;
}

void CDisplay::display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (currentscreen == Screen::Main) {
        glColor3f(0.0f, 0.75f, 0.0f);
        label.drawCircle(0.0f, 0.0f, 0.90f, 100);
        label.drawCircle(0.0f, 0.0f, 0.30f, 100);
        label.drawCircle(0.0f, 0.0f, 0.60f, 100);
        label.drawLinesWithAngles(lineGap);
        label.drawRangeLabels();
        label.drawButtons();
        enemyHighlight();

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(angle, 0.0f, 0.0f, -1.0f);
        glTranslatef(0.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 0.75f, 0.0f);
        label.drawSeeker();
        glPopMatrix();
    }
    else if (currentscreen == Screen::Settings) {
        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        label.drawButtons();
        label.drawCurrentValues();
        label.drawBox();
    }
    glFlush();

}

CDisplay::~CDisplay() {
    delete[] enemies; 
}

    void CDisplay::enemyWrapper(float distance, float angle, float height) {
        getInstance().addEnemy(distance, angle, height);
    }

    void CDisplay::addEnemy(float distance, float angle, float height) {
        if (enemyCount == enemyCapacity) {
            expandEnemyArray();
        }

        enemies[enemyCount].realDistance = distance;
        enemies[enemyCount].angle = angle;
        enemies[enemyCount].height = height;
        // Initialize other fields...
        enemies[enemyCount].distance = 0.0f;
        enemies[enemyCount].realDist = 0.0f;
        enemies[enemyCount].x = 0.0f;
        enemies[enemyCount].y = 0.0f;
        enemies[enemyCount].isHighlighted = false;
        enemies[enemyCount].visited = false;
        enemies[enemyCount].fadeAlpha = 1.0f;
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

    void CDisplay::enemyHighlight() {
        for (int i = 0; i < enemyCount; ++i) {
            Enemy& enemy = enemies[i];
            if (enemy.height < heightLowlimit || enemy.height > heightUplimit) {
                continue;
            }

            if (!enemy.isHighlighted) {
                enemy.distance = 0.90f / (outerRange / enemy.realDistance);
                enemy.realDist = enemy.realDistance;
                enemy.x = enemy.distance * cosf(enemy.angle * M_PI / 180.0f) / rangeScale;
                enemy.y = enemy.distance * -sinf(enemy.angle * M_PI / 180.0f) / rangeScale;
            }

            const float angleTolerance = 2.0f;

            if (fabs(angle - enemy.angle) < angleTolerance && !enemy.visited) {
                enemy.lastDetectionTime = glutGet(GLUT_ELAPSED_TIME);
                enemy.isHighlighted = true;
                enemy.once = true;
                enemy.fadeAlpha = 1.0f;
                enemy.visited = true;
            }

            if (enemy.isHighlighted && ((mousePosX > enemy.x - 0.02f) && (mousePosX < enemy.x + 0.02f) && (mousePosY > enemy.y - 0.02f) && (mousePosY < enemy.y + 0.02f))) {
                glColor3f(0.0f, 1.0f, 0.0f);
                char buffer[256];
                sprintf_s(buffer, "h:%.0fkm ", enemy.height);
                label.renderValues(enemy.x + 0.05f, enemy.y + 0.05f, buffer);

                sprintf_s(buffer, "d:%.0fkm ", enemy.realDist);
                label.renderValues(enemy.x + 0.05f, enemy.y, buffer);
            }

            if (enemy.isHighlighted) {
                if (enemy.fadeAlpha >= 0.05f) {
                    glColor3f(0.0f, enemy.fadeAlpha, 0.0f);
                    glPushMatrix();
                    glTranslatef(enemy.x, enemy.y, 1.0f);
                    glBegin(GL_TRIANGLE_FAN);
                    label.drawCircle(0.0f, 0.0f, 0.02f, 100);
                    glEnd();
                    glPopMatrix();
                    enemy.fadeAlpha -= 0.005f;
                }

                if (enemy.fadeAlpha < 0.05f) {
                    removeEnemy(i); // Remove the enemy if faded out
                    --i;            // Adjust the index after removal
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
        float closestEnemyAngle = angle;

        for (int i = 0; i < enemyCount; ++i) {
            Enemy& enemy = enemies[i];

            if (enemy.height < heightLowlimit || enemy.height > heightUplimit || enemy.visited) {
                continue;
            }

            float enemyAngle = enemy.angle;
            float angleDiff = fabsf(angle - enemyAngle);

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


    void CDisplay::updateAngle() {
        float targetAngle = findClosestEnemyAngle();
        float angleDiff = targetAngle - angle;

        if (angleDiff > 180.0f) {
            angleDiff -= 360.0f;
        }
        else if (angleDiff < -180.0f) {
            angleDiff += 360.0f;
        }

        if (fabs(angleDiff) > 1.0f) {
            if (angleDiff > 0) {
                clockwise = true;
            }
            else {
                clockwise = false;
            }

            if (clockwise) {
                angle += 1.0f;
            }
            else {
                angle -= 1.0f;
            }
        }

        angle = fmod(angle, 360.0f);
        if (angle < 0) {
            angle += 360.0f;
        }

        glutPostRedisplay();
        glutTimerFunc(16, timerWrapper, 0);
    }

    void CDisplay::setOuterRange(float range) {
        outerRange = range;
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

   CDisplay radar;
