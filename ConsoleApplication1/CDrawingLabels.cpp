#include "CDrawingLabels.h"
#include <GL/freeglut.h>
#include <cmath>
#include "_Variables.h"

_Variables* _VarsLabel = _Variables::getInstance();

CDrawingLabels& CDrawingLabels::getInstance() {
    static CDrawingLabels instance;
    return instance;
}

void CDrawingLabels::renderText(float x, float y, const char* text) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.0003f, 0.0004f, 1.0f);
    while (*text) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *text++);
    }
    glPopMatrix();
}

void CDrawingLabels::drawSeeker() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.90f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);

    float angleIncrement = (_VarsLabel->getClockwise()) ? -0.02f : 0.02f;
    float angle = 0.0f;

    for (float i = 0.95f; i >= 0.05f; i -= 0.05f) {
        glColor4f(0.0f, i, 0.0f, i);

        float x = 0.90f * cos(angle);
        float y = 0.90f * -sin(angle);

        glVertex2f(x, y); 
        glVertex2f(0.0f, 0.0f);

        angle += angleIncrement;
    }

    glEnd();
}

void CDrawingLabels::drawLinesWithAngles(int gap_in_degrees) {
    int num_points = static_cast<int>(360.0f / gap_in_degrees);
    float offsetX = 0.0f;
    float offsetY = 0.0f;

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
        snprintf(buffer, sizeof(buffer), "%.0f�", angle);
        glColor3f(0.0f, 0.75f, 0.0f);

        if (angle <= 90 && angle >= 0) {
            offsetX = 0.03f;
            offsetY = 0.06f;
        }

        else if (angle < 180 && angle > 90) {
            offsetX = 0.08f;
            offsetY = 0.08f;
        }

        else if (angle <= 270 && angle >= 180) {
            offsetX = 0.08f;
            offsetY = 0.04f;
        }

        else if (angle < 360 && angle > 270) {
            offsetX = 0.03f;
            offsetY = 0.03f;
        }

        float label_x = x + offsetX * cosf(-angle_radians);
        float label_y = y + offsetY * sinf(-angle_radians);

        renderText(label_x, label_y, buffer);
    }
}

void CDrawingLabels::drawCircle(float cx, float cy, float radius, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void CDrawingLabels::drawRangeLabels() {
    const float radii[] = { 0.30f, 0.60f, 0.90f };
    const float range_values[] = { _VarsLabel->getOuterRange() / 3.0f, _VarsLabel->getOuterRange() * 2.0f / 3.0f , _VarsLabel->getOuterRange() };

    for (int i = 0; i < 3; ++i) {
        drawRangeLabel(radii[i], range_values[i]);
    }
}

void CDrawingLabels::drawRangeLabel(float radius, float value) {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%.0f", value);

    float label_x = radius - 0.08f;
    float label_y = 0.0f - 0.05f;

    glColor3f(0.0f, 0.75f, 0.0f);

    renderText(label_x, label_y, buffer);
}

void CDrawingLabels::drawBox() {
    if (_VarsLabel->getIsClicked() == true) {
        int currentTime = glutGet(GLUT_ELAPSED_TIME);

        float blinkSpeed = 500.0f;

        bool isVisible = (currentTime % (int)(2 * blinkSpeed)) < blinkSpeed;

        if (isVisible) {
            glColor3f(0.0f, 1.0f, 0.0f);

            float widthStart = 0.0f, widthEnd = 0.0f, heightStart = 0.0f, heightEnd = 0.0f;

            if (_VarsLabel->getBoxID() == 0) {
                widthStart = -0.09f;
                widthEnd = 0.15f;
                heightStart = 0.80f;
                heightEnd = heightStart - 0.10f;
            }
            else if (_VarsLabel->getBoxID() == 1) {
                widthStart = -0.09f;
                widthEnd = 0.15f;
                heightStart = 0.65f;
                heightEnd = heightStart - 0.10f;
            }
            else if (_VarsLabel->getBoxID() == 2) {
                widthStart = -0.09f;
                widthEnd = 0.12f;
                heightStart = 0.50f;
                heightEnd = heightStart - 0.10f;
            }
            else if (_VarsLabel->getBoxID() == 3) {
                widthStart = 0.07f;
                widthEnd = 0.32f;
                heightStart = 0.35f;
                heightEnd = heightStart - 0.10f;
            }
            else if (_VarsLabel->getBoxID() == 4) {
                widthStart = 0.07f;
                widthEnd = 0.32f;
                heightStart = 0.35f;
                heightEnd = heightStart - 0.10f;
            }
            glBegin(GL_LINE_LOOP);
            glVertex2f(widthStart, heightStart);
            glVertex2f(widthEnd, heightStart);
            glVertex2f(widthEnd, heightEnd);
            glVertex2f(widthStart, heightEnd);
            glEnd();
        }
    }
}

void CDrawingLabels::renderValues(float x, float y, const char* text) {                                 //USABLE
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.0003f, 0.0003f, 1.0f);
    while (*text) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *text++);
    }
    glPopMatrix();
}

void CDrawingLabels::drawCurrentValues() {
    char buffer[256];

    sprintf_s(buffer, "%d m", _VarsLabel->getHeightUplimit());
    renderValues(-0.05f, 0.73f, buffer);

    sprintf_s(buffer, "%d m", _VarsLabel->getHeightLowlimit());
    renderValues(-0.05f, 0.58f, buffer);

    sprintf_s(buffer, "%.0f km", _VarsLabel->getOuterRange());
    renderValues(-0.05f, 0.43f, buffer);

    sprintf_s(buffer, "%d degrees", _VarsLabel->getLineGap());
    renderValues(0.08f, 0.28f, buffer);
}

void CDrawingLabels::drawButton(float x, float y, float width, float height, const char* label) {                                 //USABLE

    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    if (label == "-" || label == "+") {
        renderText(x + width / 2 - 0.015f, y + height / 2 - 0.02f, label);
    }

    else if (label == "Degree Between Lines") {
        renderText(x + width / 2 - 0.22f, y + height / 2 - 0.01f, label);
    }

    else if (label == "Settings") {
        renderText(x + width / 2 - 0.08f, y + height / 2 - 0.01f, label);
    }

    else {
        renderText(x + width / 2 - 0.10f, y + height / 2 - 0.02f, label);
    }
}

void CDrawingLabels::drawButtons() {
    if (_VarsLabel->getCurrentScreen() == Screen::Main) {
        drawButton(0.75f, -0.85f, 0.15f, 0.075f, "+");

        drawButton(0.60f, -0.85f, 0.15f, 0.075f, "-");

        drawButton(-0.95f, 0.85f, 0.25f, 0.1f, "Settings");
    }
    else if (_VarsLabel->getCurrentScreen() == Screen::Settings) {
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
    }
}
