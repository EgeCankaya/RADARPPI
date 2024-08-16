#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;

class RadarDisplay {
public:
    RadarDisplay() : angle(0.0f), outerRange(300.0f), searchStartAngle(0.0f), searchEndAngle(30.0f), highlightDuration(1500), lastDetectionTime(0), rangeScale(1), heightLowlimit(15), heightUplimit(30), lineGap(30), boxID(0), isClicked(false), maxRange(300), clockwise(true) {}

    float left = -1.0f, right = 1.0f, bottom = -1.0f, top = 1.0f;
    const float zNear = -1.0f, zFar = 1.0f;

    const float zoomFactor = 0.1f;

    void init() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    struct Point {
        float x;
        float y;
        float height;
        float lastX = 0.0f;
        float lastY = 0.0f;
    };

    struct Enemy {
        float distance;
        float angle;
        float height;
        bool isHighlighted;
        int lastDetectionTime;
        bool once;
    };

    Point calculateObjectPosition(float distance, float angle) {
        Point pos;
        pos.x = distance * cosf(angle * M_PI / 180.0f) / rangeScale;
        pos.y = distance * -sinf(angle * M_PI / 180.0f) / rangeScale;
        return pos;
    }

    void reshape(int width, int height) {
        int size = std::min(width, height);  

        glViewport((width - size) / 2, (height - size) / 2, size, size);  
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(left, right, bottom, top, zNear, zFar);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }


    void display() {
        glClear(GL_COLOR_BUFFER_BIT);

        if (currentscreen == Screen::Main) {

            glColor3f(0.0f, 0.75f, 0.0f);
            drawCircle(0.0f, 0.0f, 0.90f, 100);
            drawCircle(0.0f, 0.0f, 0.30f, 100);
            drawCircle(0.0f, 0.0f, 0.60f, 100);
            drawLinesWithAngles(lineGap);

            drawRangeLabels();
            drawButtons();
            enemyHighlight();

            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.0f);
            glRotatef(angle, 0.0f, 0.0f, -1.0f);
            glTranslatef(0.0f, 0.0f, 0.0f);
            glColor3f(0.0f, 0.75f, 0.0f);
            drawSeeker();
            glPopMatrix();
        }
        else if (currentscreen == Screen::Settings) {
            glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
            drawButtons();
            drawCurrentValues();
            drawUnderline();
        }
        glFlush();
    }

    void enemyHighlight() {
        for (auto& enemy : enemies) {
            Point objectPos = calculateObjectPosition(enemy.distance, enemy.angle);
            objectPos.height = enemy.height;

            const float angleTolerance = 2.0f;
            if (clockwise) {

                if ((enemy.isHighlighted || ((fabs(angle - enemy.angle) < angleTolerance)) && (heightLowlimit <= objectPos.height && objectPos.height <= heightUplimit))) {
                    glColor3f(0.0f, 1.0f, 0.0f);
                    glPushMatrix();
                    glTranslatef(objectPos.x, objectPos.y, 0.0f);
                    glBegin(GL_TRIANGLE_FAN);
                    drawCircle(0.0f, 0.0f, 0.02f, 100);
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
                    renderValues(objectPos.x + 0.05f, objectPos.y + 0.05f, buffer);
                }
            }

            else {
                if ((enemy.isHighlighted || ((fabs(angle - enemy.angle) < angleTolerance) || (fabs((360 - fabs(angle)) - enemy.angle) < angleTolerance)) && (heightLowlimit <= objectPos.height && objectPos.height <= heightUplimit))) {
                    glColor3f(0.0f, 1.0f, 0.0f);
                    glPushMatrix();
                    glTranslatef(objectPos.x, objectPos.y, 0.0f);
                    glBegin(GL_TRIANGLE_FAN);
                    drawCircle(0.0f, 0.0f, 0.02f, 100);
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
                    renderValues(objectPos.x + 0.05f, objectPos.y + 0.05f, buffer);
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
                    drawCircle(0.0f, 0.0f, 0.02f, 100);
                    glEnd();
                    glPopMatrix();
            }
        }
    }


    void addEnemy(float distance, float angle, float height) {
        distance = 0.90f / (300.0f / distance);
        enemies.push_back({ distance, angle, height, false });
    }

    void renderText(float x, float y, const char* text) {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glScalef(0.0003f, 0.0004f, 1.0f); 
        while (*text) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *text++);
        }
        glPopMatrix();
    }

    void drawButton(float x, float y, float width, float height, const char* label) {

        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();

        if (label == "-" || label == "+") {
            renderText(x + width / 2 - 0.01, y + height / 2 - 0.01f, label);
        }

        else if (label == "Degree Between Lines") {
            renderText(x + width / 2 - 0.22, y + height / 2 - 0.01f, label);
        }
        
        else if (label == "Change Seeker Rotation") {
            renderText(x + width / 2 - 0.25, y + height / 2 - 0.01f, label);
        }

        else {
            renderText(x + width / 2 - 0.10, y + height / 2 - 0.01f, label);
        }
    }

    void updateAngle() {
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

    void setOuterRange(float range) {
        outerRange = range;
    }

private:
    float angle;
    float outerRange;
    float searchStartAngle;
    float searchEndAngle;
    float limitedConst = 1.0f;
    int highlightDuration;
    int lastDetectionTime;
    int heightUplimit, heightLowlimit;
    float rangeScale;
    int lineGap;
    float mousePosX, mousePosY;
    float objectDistance;
    float objectAngle;
    float objectHeight;
    bool isClicked;
    int boxID;
    int maxRange;
    string inputBuffer;
    bool clockwise;
    float scale;
   
    vector<Enemy> enemies;

    enum class Screen { Main, Settings };
    Screen currentscreen = Screen::Main;

    static void timerWrapper(int value) {
        getInstance().updateAngle();
    }

    static RadarDisplay& getInstance() {
        static RadarDisplay instance;
        return instance;
    }

    static void keyboardWrapper(unsigned char key, int x, int y) {
        getInstance().keyboard(key, x, y);
    }

    static void displayWrapper() {
        getInstance().display();
    }

    static void reshapeWrapper(int width, int height) {
        getInstance().reshape(width, height);
    }

    static void mouseWrapper(int button, int state, int x, int y) {
        getInstance().mouse(button, state, x, y);
    }

    static void enemyWrapper(float distance, float angle, float height) {
        getInstance().addEnemy(distance, angle, height);
    }

    static void mouseHoverWrapper(int x, int y) {
        getInstance().mouseHover(x, y);
    }

    static void mouseWheelWrapper(int wheel, int direction, int x, int y) {
        getInstance().mouseWheel(wheel, direction, x, y);
    }

    void drawString(float x, float y, const char* str) {
        glRasterPos2f(x, y);
        while (*str) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *str++);
        }
    }

    void drawSeeker() {
         glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
         glBegin(GL_LINES);
         glVertex2f(0.0f, 0.0f);
         glVertex2f(0.90f, 0.0f);
         glEnd();

         if (clockwise) {
             glColor4f(0.0f, 0.95f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.89f, 0.01f);
             glEnd();

             glColor4f(0.0f, 0.90f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.88f, 0.02f);
             glEnd();

             glColor4f(0.0f, 0.85f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.87f, 0.03f);
             glEnd();

             glColor4f(0.0f, 0.80f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.86f, 0.04f);
             glEnd();

             glColor4f(0.0f, 0.75f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.85f, 0.05f);
             glEnd();

             glColor4f(0.0f, 0.70f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.84f, 0.06f);
             glEnd();

             glColor4f(0.0f, 0.65f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.83f, 0.07f);
             glEnd();

             glColor4f(0.0f, 0.60f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.82f, 0.08f);
             glEnd();

             glColor4f(0.0f, 0.55f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.81f, 0.09f);
             glEnd();

             glColor4f(0.0f, 0.50f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.80f, 0.10f);
             glEnd();

             glColor4f(0.0f, 0.45f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.79f, 0.11f);
             glEnd();

             glColor4f(0.0f, 0.40f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.78f, 0.12f);
             glEnd();

             glColor4f(0.0f, 0.35f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.77f, 0.13f);
             glEnd();

             glColor4f(0.0f, 0.30f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.76f, 0.14f);
             glEnd();

             glColor4f(0.0f, 0.25f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.75f, 0.15f);
             glEnd();

             glColor4f(0.0f, 0.20f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.74f, 0.16f);
             glEnd();

             glColor4f(0.0f, 0.15f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.73f, 0.17f);
             glEnd();

             glColor4f(0.0f, 0.10f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.72f, 0.18f);
             glEnd();

             glColor4f(0.0f, 0.05f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.71f, 0.19f);
             glEnd();
         }

         else {
             glColor4f(0.0f, 0.95f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.89f, -0.01f);
             glEnd();

             glColor4f(0.0f, 0.90f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.88f, -0.02f);
             glEnd();

             glColor4f(0.0f, 0.85f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.87f, -0.03f);
             glEnd();

             glColor4f(0.0f, 0.80f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.86f, -0.04f);
             glEnd();

             glColor4f(0.0f, 0.75f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.85f, -0.05f);
             glEnd();

             glColor4f(0.0f, 0.70f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.84f, -0.06f);
             glEnd();

             glColor4f(0.0f, 0.65f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.83f, -0.07f);
             glEnd();

             glColor4f(0.0f, 0.60f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.82f, -0.08f);
             glEnd();

             glColor4f(0.0f, 0.55f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.81f, -0.09f);
             glEnd();

             glColor4f(0.0f, 0.50f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.80f, -0.10f);
             glEnd();

             glColor4f(0.0f, 0.45f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.79f, -0.11f);
             glEnd();

             glColor4f(0.0f, 0.40f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.78f, -0.12f);
             glEnd();

             glColor4f(0.0f, 0.35f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.77f, -0.13f);
             glEnd();

             glColor4f(0.0f, 0.30f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.76f, -0.14f);
             glEnd();

             glColor4f(0.0f, 0.25f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.75f, -0.15f);
             glEnd();

             glColor4f(0.0f, 0.20f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.74f, -0.16f);
             glEnd();

             glColor4f(0.0f, 0.15f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.73f, -0.17f);
             glEnd();

             glColor4f(0.0f, 0.10f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.72f, -0.18f);
             glEnd();

             glColor4f(0.0f, 0.05f, 0.0f, 1.0f);
             glBegin(GL_LINES);
             glVertex2f(0.0f, 0.0f);
             glVertex2f(0.71f, -0.19f);
             glEnd();
         }
         
    }

    void drawLinesWithAngles(int gap_in_degrees) {
        int num_points = static_cast<int>(360.0f / gap_in_degrees);
        float offset;

        glBegin(GL_LINES);
        for (int i = 0; i < num_points; i++) {
            float angle = gap_in_degrees * float(i);
            float angle_radians = angle * M_PI / 180.0f;
            float x = 0.90f * cosf(-angle_radians);
            float y = 0.90f * sinf(-angle_radians);

            glVertex2f(0.0f, 0.0f);
            glVertex2f(x, y);
        }
        glEnd();

        for (int i = 0; i < num_points; i++) {
            float angle = gap_in_degrees * float(i);
            float angle_radians = angle * M_PI / 180.0f;
            float x = 0.90f * cosf(-angle_radians);
            float y = 0.90f * sinf(-angle_radians);

            char buffer[16];
            snprintf(buffer, sizeof(buffer), "%.0f°", angle);
            glColor3f(0.0f, 0.75f, 0.0f);

            if (angle < 90 || angle > 269) {
                offset = 0.02f;
            }
            else if (angle == 90) {
                offset = 0.03f;
            }
            else {
                offset = 0.06f;
            }

            float label_x = x + offset * cosf(-angle_radians);
            float label_y = y + offset * sinf(-angle_radians);

            renderText(label_x, label_y, buffer);
        }
    }


    void drawCircle(float cx, float cy, float radius, int num_segments) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < num_segments; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            glVertex2f(x + cx, y + cy);
        }
        glEnd();
    }

    void drawRangeLabels() {
        const float radii[] = { 0.30f, 0.60f, 0.90f };
        const float range_values[] = { outerRange / 3.0f * rangeScale, outerRange * 2.0f / 3.0f * rangeScale, outerRange * rangeScale };

        for (int i = 0; i < 3; ++i) {
            drawRangeLabel(radii[i], range_values[i]);
        }
    }

    void drawRangeLabel(float radius, float value) {
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%.0f", value);
       
        float label_x = radius - 0.08f;  
        float label_y = 0.0f -0.05f;

        glColor3f(0.0f, 0.75f, 0.0f); 

        renderText(label_x, label_y, buffer);
    }

    void drawUnderline() {
        if (isClicked == true) {
            if (boxID == 0) {
                glColor3f(0.0f, 1.0f, 0.0f);
                glBegin(GL_LINES);
                glVertex2f(-0.05f, 0.70f);
                glVertex2f(0.08f, 0.70f);
                glEnd();
            }
            if (boxID == 1) {
                glColor3f(0.0f, 1.0f, 0.0f);
                glBegin(GL_LINES);
                glVertex2f(-0.05f, 0.55f);
                glVertex2f(0.08f, 0.55f);
                glEnd();
            }
            if (boxID == 2) {
                glColor3f(0.0f, 1.0f, 0.0f);
                glBegin(GL_LINES);
                glVertex2f(-0.05f, 0.40f);
                glVertex2f(0.08f, 0.40f);
                glEnd();
            }
            if (boxID == 3) {
                glColor3f(0.0f, 1.0f, 0.0f);
                glBegin(GL_LINES);
                glVertex2f(0.07, 0.25f);
                glVertex2f(0.32f, 0.25f);
                glEnd();
            }
        }
    }
    
    bool isMouseClickInsideBox(float buttonX, float buttonY, float buttonWidth, float buttonHeight) {
        return (mousePosX >= buttonX && mousePosX <= buttonX + buttonWidth &&
            mousePosY >= buttonY && mousePosY <= buttonY + buttonHeight);
    }

    void keyboard(unsigned char key, int x, int y) {
        if (isClicked) {
            if (key >= '0' && key <= '9') {

                inputBuffer += key;
            }
            else if (key == 13) {
                isClicked = false;

                if (boxID == 0) {
                    int number = stoi(inputBuffer);

                    if (heightLowlimit > number) {
                        heightUplimit = heightLowlimit;
                    }
                    else {
                        heightUplimit = static_cast<float>(number);
                    }
                }
                if (boxID == 1) {
                    int number = stoi(inputBuffer);

                    if (heightUplimit < number) {
                        heightLowlimit = heightUplimit;
                    }
                    else {
                        heightLowlimit = static_cast<float>(number);
                    }
                }
                if (boxID == 2) {
                    int number = stoi(inputBuffer);
                    if (number > maxRange) {
                        outerRange = maxRange;
                    }
                    else {
                        outerRange = static_cast<float>(number);
                    }
                }
                if (boxID == 3) {
                    int number = stoi(inputBuffer);
                    lineGap = static_cast<float>(number);
                }
                inputBuffer.clear();
            }
            glutPostRedisplay();
        }
    }
    void mouse(int button, int state, int x, int y) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

            int width = glutGet(GLUT_WINDOW_WIDTH);
            int height = glutGet(GLUT_WINDOW_HEIGHT);
            float boxWidth = 0.15f;
            float boxHeight = 0.075f;

            mousePosX = 2.0f * (x - width / 2) / min(width, height);
            mousePosY = 2.0f * (height / 2 - y) / min(width, height);

            if (currentscreen == Screen::Main) {
                if (isMouseClickInsideBox(0.60f, -0.85f, boxWidth, boxHeight)) {
                    decreaseRange();
                }
                else if (isMouseClickInsideBox(0.75f, -0.85f, boxWidth, boxHeight)) {
                    increaseRange();
                }
                else if (isMouseClickInsideBox(-0.95f, 0.85f, 0.25f, 0.1f)) {
                    currentscreen = Screen::Settings;
                }
            }
            else if (currentscreen == Screen::Settings) {
                if (isMouseClickInsideBox(-0.95f, 0.85f, 0.25f, 0.1f)) {
                    currentscreen = Screen::Main;
                }

                else if (isMouseClickInsideBox(-0.40f, 0.70f, 0.15f, 0.1f)) { 
                    decreaseHeightUp(); 
                }

                else if (isMouseClickInsideBox(-0.25f, 0.70f, 0.15f, 0.1f)) { 
                    increaseHeightUp(); 
                }

                else if (isMouseClickInsideBox(-0.40f, 0.55f, 0.15f, 0.1f)) { 
                    decreaseHeightLow(); 
                }

                else if (isMouseClickInsideBox(-0.25f, 0.55f, 0.15f, 0.1f)) { 
                    increaseHeightLow(); 
                }

                else if (isMouseClickInsideBox(-0.40f, 0.40f, 0.15f, 0.1f)) { 
                    decreaseRange(); 
                }

                else if (isMouseClickInsideBox(-0.25f, 0.40f, 0.15f, 0.1f)) { 
                    increaseRange(); 
                }

                else if (isMouseClickInsideBox(-0.20f, 0.25f, 0.13f, 0.1f)) { 
                    decreaseLineGap(); 
                }

                else if (isMouseClickInsideBox(-0.07f, 0.25f, 0.13f, 0.1f)) { 
                    increaseLineGap(); 
                }

                else if (isMouseClickInsideBox(-0.70f, 0.70f, 0.30f, 0.1f)) {
                    boxID = 0;
                    isClicked = true;
                }

                else if (isMouseClickInsideBox(-0.70f, 0.55f, 0.30f, 0.1f)) {
                    boxID = 1;
                    isClicked = true;
                }

                else if (isMouseClickInsideBox(-0.70f, 0.40f, 0.30f, 0.1f)) {
                    boxID = 2;
                    isClicked = true;
                }

                else if (isMouseClickInsideBox(-0.70f, 0.25f, 0.50f, 0.1f)) {
                    boxID = 3;
                    isClicked = true;
                }
                else if (isMouseClickInsideBox(-0.70f, 0.10f, 0.52f, 0.1f)) {
                    if (clockwise) clockwise = false;
                    else clockwise = true;
                }
            }
        }
    }

    void mouseHover(int x, int y) {
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);

        mousePosX = 2.0f * (x - width / 2) / min(width, height);
        mousePosY = 2.0f * (height / 2 - y) / min(width, height);
    }

    void mouseWheel(int wheel, int direction, int x, int y) {
        if (direction > 0) {
            
            left += zoomFactor;
            right -= zoomFactor;
            bottom += zoomFactor;
            top -= zoomFactor;
        }
        else {
            
            left -= zoomFactor;
            right += zoomFactor;
            bottom -= zoomFactor;
            top += zoomFactor;
        }
        
        reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        glutPostRedisplay();
    }

    void renderValues(float x, float y, const char* text) {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glScalef(0.0003f, 0.0003f, 1.0f); 
        while (*text) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *text++);
        }
        glPopMatrix();
    }


    void drawCurrentValues() {
        char buffer[256];

        sprintf_s(buffer, "%d km", heightUplimit);
        renderValues(-0.05f, 0.73f, buffer);

        sprintf_s(buffer, "%d km", heightLowlimit);
        renderValues(-0.05f, 0.58f, buffer);

        sprintf_s(buffer, "%.0f km", outerRange * rangeScale);
        renderValues(-0.05f, 0.43f, buffer);

        sprintf_s(buffer, "%d degrees", lineGap);
        renderValues(0.08f, 0.28f, buffer);

        if (clockwise) {
            sprintf_s(buffer, "Clockwise");
            renderValues(-0.15f, 0.13f, buffer);
        }
        
        else {
            sprintf_s(buffer, "Counter Clockwise");
            renderValues(-0.15f, 0.13f, buffer);
        }
    }

    void drawButtons() {
        if (currentscreen == Screen::Main) {
            drawButton(0.75f, -0.85f, 0.15f, 0.075f, "+");

            drawButton(0.60f, -0.85f, 0.15f, 0.075f, "-");

            drawButton(-0.95f, 0.85f, 0.25f, 0.1f, "Settings");
        }
        else if (currentscreen == Screen::Settings) {
            drawButton(-0.95f, 0.85f, 0.25f, 0.1f, "Settings");

            drawButton(-0.7f, 0.7f, 0.30f, 0.1f, "Height Max");
            drawButton(-0.40f, 0.7f, 0.15f, 0.1f, "-");
            drawButton(-0.25f, 0.7f, 0.15f, 0.1f, "+");

            drawButton(-0.7f, 0.55f, 0.30f, 0.1f, "Height Min");
            drawButton(-0.40f, 0.55f, 0.15f, 0.1f, "-");
            drawButton(-0.25f, 0.55f, 0.15f, 0.1f, "+");

            drawButton(-0.7f, 0.40f, 0.30f, 0.1f, "Range");
            drawButton(-0.40f, 0.40f, 0.15f, 0.1f, "-");
            drawButton(-0.25f, 0.40f, 0.15f, 0.1f, "+");

            drawButton(-0.7f, 0.25f, 0.50f, 0.1f, "Degree Between Lines");

            drawButton(-0.20f, 0.25f, 0.13f, 0.1f, "-");
            drawButton(-0.07f, 0.25f, 0.13f, 0.1f, "+");

            drawButton(-0.70f, 0.10f, 0.52f, 0.1f, "Change Seeker Rotation");

        }
    }

    void increaseRange() {
        rangeScale += 0.1f;
    }

    void decreaseRange() {
        rangeScale -= 0.1f;
    }

    void increaseHeightUp() {
        heightUplimit += 5.0f;
    }

    void decreaseHeightUp() {
        heightUplimit -= 5.0f;
    }

    void increaseHeightLow() {
        heightLowlimit += 5.0f;
    }

    void decreaseHeightLow() {
        heightLowlimit -= 5.0f;
    }

    void decreaseLineGap() {
        lineGap -= 15.0f;
    }
    void increaseLineGap() {
        lineGap += 15.0f;
    }

public:
    static void run(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(800, 800);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Radar PPI");

        getInstance().init();

        enemyWrapper(150.0f, 30.0f, 20.0f);
        enemyWrapper(100.0f, 160.0f, 25.0f);
        enemyWrapper(270.0f, 120.0f, 35.0f);

        glutKeyboardFunc(keyboardWrapper);
        glutDisplayFunc(displayWrapper);
        glutReshapeFunc(reshapeWrapper);
        glutMouseFunc(mouseWrapper);
        glutPassiveMotionFunc(mouseHoverWrapper);
        glutMouseWheelFunc(mouseWheelWrapper);
        glutTimerFunc(0, timerWrapper, 0);

        glutMainLoop();
    }

};

int main(int argc, char** argv) {
    RadarDisplay::run(argc, argv);
    return 0;
}