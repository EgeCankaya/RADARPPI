#include "CInteractionHandler.h"
#include <GL/freeglut.h>
#include <string>
#include <iostream>

CInteractionHandler::CInteractionHandler() {}

bool CInteractionHandler::isMouseClickInsideBox(float buttonX, float buttonY, float buttonWidth, float buttonHeight) {                                 //USABLE
    return (mousePosX >= buttonX && mousePosX <= buttonX + buttonWidth &&
        mousePosY >= buttonY && mousePosY <= buttonY + buttonHeight);
}

void CInteractionHandler::keyboard(unsigned char key, int x, int y) {                                 //USABLE
    if (isClicked) {
        if (key >= '0' && key <= '9') {

            inputBuffer += key;
        }
        else if (key == 13) {
            isClicked = false;

            if (boxID == 0) {
                int number = std::stoi(inputBuffer);

                if (heightLowlimit > number) {
                    heightUplimit = heightLowlimit;
                }
                else {
                    heightUplimit = static_cast<float>(number);
                }
            }
            if (boxID == 1) {
                int number = std::stoi(inputBuffer);

                if (heightUplimit < number) {
                    heightLowlimit = heightUplimit;
                }
                else {
                    heightLowlimit = static_cast<float>(number);
                }
            }
            if (boxID == 2) {
                int number = std::stoi(inputBuffer);
                if (number > maxRange) {
                    outerRange = maxRange;
                }
                else {
                    outerRange = static_cast<float>(number);
                }
            }
            if (boxID == 3) {
                int number = std::stoi(inputBuffer);
                lineGap = static_cast<float>(number);
            }
            inputBuffer.clear();
        }
        glutPostRedisplay();
    }
}

void CInteractionHandler::mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);

        float mouseX = 2.0f * (x - width / 2) / std::min(width, height);
        float mouseY = 2.0f * (height / 2 - y) / std::min(width, height);

        mousePosX = xleft + (xright - xleft) * (mouseX + 1.0f) / 2.0f;
        mousePosY = bottom + (top - bottom) * (mouseY + 1.0f) / 2.0f;

        if (currentscreen == Screen::Main) {
            if (isMouseClickInsideBox(0.60f, -0.85f, 0.15f, 0.075f)) {
                decreaseRange();
            }
            else if (isMouseClickInsideBox(0.75f, -0.85f, 0.15f, 0.075f)) {
                increaseRange();
            }
            else if (isMouseClickInsideBox(-0.95f, 0.85f, 0.25f, 0.1f)) {
                currentscreen = Screen::Settings;
            }
        }
        else if (currentscreen == Screen::Settings) {
            if (currentscreen == Screen::Main) {
                if (isMouseClickInsideBox(0.60f, -0.85f, 0.15f, 0.075f)) {
                    decreaseRange();
                }
                else if (isMouseClickInsideBox(0.75f, -0.85f, 0.15f, 0.075f)) {
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
}

void CInteractionHandler::mouseHover(int x, int y) {                                  //USABLE
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    float mouseX = 2.0f * (x - width / 2) / std::min(width, height);
    float mouseY = 2.0f * (height / 2 - y) / std::min(width, height);

    mousePosX = xleft + (xright - xleft) * (mouseX + 1.0f) / 2.0f;
    mousePosY = bottom + (top - bottom) * (mouseY + 1.0f) / 2.0f;
}

void CInteractionHandler::mouseWheel(int wheel, int direction, int x, int y) {                                  //USABLE
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    float mouseX = 2.0f * (x - width / 2) / std::min(width, height);
    float mouseY = 2.0f * (height / 2 - y) / std::min(width, height);

    mouseX = xleft + (xright - xleft) * (mouseX + 1.0f) / 2.0f;
    mouseY = bottom + (top - bottom) * (mouseY + 1.0f) / 2.0f;

    if (direction > 0) {
        float newLeft = xleft + zoomFactor * (mouseX - xleft) / (xright - xleft);
        float newRight = xright - zoomFactor * (xright - mouseX) / (xright - xleft);
        float newBottom = bottom + zoomFactor * (mouseY - bottom) / (top - bottom);
        float newTop = top - zoomFactor * (top - mouseY) / (top - bottom);

        if (newRight > newLeft && newTop > newBottom) {
            xleft = newLeft;
            xright = newRight;
            bottom = newBottom;
            top = newTop;
        }
    }
    else {
        float newLeft = xleft - zoomFactor * (mouseX - xleft) / (xright - xleft);
        float newRight = xright + zoomFactor * (xright - mouseX) / (xright - xleft);
        float newBottom = bottom - zoomFactor * (mouseY - bottom) / (top - bottom);
        float newTop = top + zoomFactor * (top - mouseY) / (top - bottom);

        if (newRight > newLeft && newTop > newBottom) {
            xleft = newLeft;
            xright = newRight;
            bottom = newBottom;
            top = newTop;
        }
    }
    reshape(width, height);
    glutPostRedisplay();


   // std::cout << heightUplimit << std::endl;
}

void CInteractionHandler::reshape(int width, int height) {
    int size = std::min(width, height);

    glViewport((width - size) / 2, (height - size) / 2, size, size);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(xleft, xright, bottom, top, zNear, zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

CInteractionHandler& CInteractionHandler::getInstance() {                                 //USABLE
    static CInteractionHandler instance;
    return instance;
}

void CInteractionHandler::increaseRange() {
    outerRange += 30;
}

void CInteractionHandler::decreaseRange() {
    outerRange -= 30;
}

void CInteractionHandler::increaseHeightUp() {
    heightUplimit += 5.0f;
}

void CInteractionHandler::decreaseHeightUp() {
    heightUplimit -= 5.0f;
}

void CInteractionHandler::increaseHeightLow() {
    heightLowlimit += 5.0f;
}

void CInteractionHandler::decreaseHeightLow() {
    heightLowlimit -= 5.0f;
}

void CInteractionHandler::decreaseLineGap() {
    lineGap -= 15.0f;
}

void CInteractionHandler::increaseLineGap() {
    lineGap += 15.0f;
}

void CInteractionHandler::setCallbacks() {
    glutKeyboardFunc(keyboardWrapper);
    glutReshapeFunc(reshapeWrapper);
    glutMouseFunc(mouseWrapper);
    glutPassiveMotionFunc(mouseHoverWrapper);
    glutMouseWheelFunc(mouseWheelWrapper);
}

void CInteractionHandler::keyboardWrapper(unsigned char key, int x, int y) {
    getInstance().keyboard(key, x, y);
}

void CInteractionHandler::mouseHoverWrapper(int x, int y) {
    getInstance().mouseHover(x, y);
}

void CInteractionHandler::mouseWheelWrapper(int wheel, int direction, int x, int y) {
    getInstance().mouseWheel(wheel, direction, x, y);
}

void CInteractionHandler::reshapeWrapper(int width, int height) {
    getInstance().reshape(width, height);
}

void CInteractionHandler::mouseWrapper(int button, int state, int x, int y) {
    getInstance().mouse(button, state, x, y);
}

CInteractionHandler handler;
