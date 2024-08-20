#include "Display.h"


    Display::Point Display::calculateObjectPosition(float distance, float angle) {
        Display::Point pos;
        pos.x = distance * cosf(angle * M_PI / 180.0f) / rangeScale;
        pos.y = distance * -sinf(angle * M_PI / 180.0f) / rangeScale;
        return pos;
    }


    void Display::display() {
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
            label.drawUnderline();
        }
        glFlush();
    }

    void Display::enemyHighlight() {
        for (auto& enemy : enemies) {
            Point objectPos = calculateObjectPosition(enemy.distance, enemy.angle);
            objectPos.height = enemy.height;
            objectPos.distance = enemy.realDistance;

            const float angleTolerance = 2.0f;
            if (clockwise) {

                if ((enemy.isHighlighted || ((fabs(angle - enemy.angle) < angleTolerance)) && (heightLowlimit <= objectPos.height && objectPos.height <= heightUplimit))) {
                    glColor3f(0.0f, 1.0f, 0.0f);
                    glPushMatrix();
                    glTranslatef(objectPos.x, objectPos.y, 0.0f);
                    glBegin(GL_TRIANGLE_FAN);
                    label.drawCircle(0.0f, 0.0f, 0.02f, 100);
                    glEnd();
                    glPopMatrix();

                    if (fabs(angle - enemy.angle) < angleTolerance) {
                        enemy.lastDetectionTime = glutGet(GLUT_ELAPSED_TIME);
                        enemy.isHighlighted = true;
                        enemy.once = true;
                    }
                }

                if (enemy.isHighlighted && ((mousePosX > objectPos.x - 0.02f) && (mousePosX < objectPos.x + 0.02f) && (mousePosY > objectPos.y - 0.02f) && (mousePosY < objectPos.y + 0.02f))) {
                    char buffer[256];
                    sprintf_s(buffer, "h:%.0f ", objectPos.height);
                    label.renderValues(objectPos.x + 0.05f, objectPos.y + 0.05f, buffer);

                    sprintf_s(buffer, "d:%.0f ", objectPos.distance);
                    label.renderValues(objectPos.x + 0.05f, objectPos.y, buffer);
                }
            }

            else {
                if ((enemy.isHighlighted || ((fabs(angle - enemy.angle) < angleTolerance) || (fabs((360 - fabs(angle)) - enemy.angle) < angleTolerance)) && (heightLowlimit <= objectPos.height && objectPos.height <= heightUplimit))) {
                    glColor3f(0.0f, 1.0f, 0.0f);
                    glPushMatrix();
                    glTranslatef(objectPos.x, objectPos.y, 0.0f);
                    glBegin(GL_TRIANGLE_FAN);
                    label.drawCircle(0.0f, 0.0f, 0.02f, 100);
                    glEnd();
                    glPopMatrix();

                    if ((fabs(angle - enemy.angle) < angleTolerance) || (fabs((360 - fabs(angle)) - enemy.angle)) < angleTolerance) {
                        enemy.lastDetectionTime = glutGet(GLUT_ELAPSED_TIME);
                        enemy.isHighlighted = true;
                        enemy.once = true;
                    }
                }

                if (enemy.isHighlighted && ((mousePosX > objectPos.x - 0.02f) && (mousePosX < objectPos.x + 0.02f) && (mousePosY > objectPos.y - 0.02f) && (mousePosY < objectPos.y + 0.02f))) {
                    char buffer[256];
                    sprintf_s(buffer, "h:%.0f ", objectPos.height);
                    label.renderValues(objectPos.x + 0.05f, objectPos.y + 0.05f, buffer);

                    sprintf_s(buffer, "d:%.0f ", objectPos.distance);
                    label.renderValues(objectPos.x + 0.05f, objectPos.y, buffer);
                }
            }
            if (enemy.isHighlighted && (glutGet(GLUT_ELAPSED_TIME) - enemy.lastDetectionTime > highlightDuration)) {

                enemy.isHighlighted = false;
            }

            if ((!enemy.isHighlighted || (objectPos.lastX != 0.0f || objectPos.lastY != 0.0f)) && enemy.once) {
                objectPos.lastX = objectPos.x;
                objectPos.lastY = objectPos.y;

                glColor3f(0.0f, 0.3f, 0.0f);
                glPushMatrix();
                glTranslatef(objectPos.lastX, objectPos.lastY, 0.0f);
                glBegin(GL_TRIANGLE_FAN);
                label.drawCircle(0.0f, 0.0f, 0.02f, 100);
                glEnd();
                glPopMatrix();
            }
        }
    }
    
    Display& Display::getInstance() {
        static Display instance;
        return instance;
    }

    void Display::addEnemy(float distance, float angle, float height) {
        float dist = 0.90f / (300.0f / distance);
        enemies.push_back({ dist, angle, height, false, distance });
    }

    void Display::updateAngle() {
        if (clockwise) {
            angle += 1.0f;

        }
        else {
            angle -= 1.0f;
        }
        angle = fmod(angle, 360.0f);
        glutPostRedisplay();
        glutTimerFunc(16, timerWrapper, 0);
    }

    void Display::setOuterRange(float range) {
        outerRange = range;
    }

   void Display::timerWrapper(int value) {
        getInstance().updateAngle();
   }

   void Display::displayWrapper() {
        getInstance().display();
   }

    void Display::enemyWrapper(float distance, float angle, float height) {
        getInstance().addEnemy(distance, angle, height);
    }

    void Display::setCallbacks() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glutTimerFunc(0, timerWrapper, 0);
        glutDisplayFunc(displayWrapper);
    }

    Display radar;