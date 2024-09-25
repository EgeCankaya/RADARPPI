#include "CInteractionHandler.h"
#include <GL/freeglut.h>
#include <string>
#include <iostream>
#include "_Variables.h"

_Variables* _VarsHandler = _Variables::getInstance();

CInteractionHandler& CInteractionHandler::getInstance() {
    static CInteractionHandler instance;
    return instance;
}

bool CInteractionHandler::isMouseClickInsideBox(float buttonX, float buttonY, float buttonWidth, float buttonHeight) {
    return (_VarsHandler->getMousePosX() >= buttonX && _VarsHandler->getMousePosX() <= buttonX + buttonWidth &&
        _VarsHandler->getMousePosY() >= buttonY && _VarsHandler->getMousePosY() <= buttonY + buttonHeight);
}

void CInteractionHandler::keyboard(unsigned char key, int x, int y) {
    if (_VarsHandler->getIsClicked()) {
        if (key >= '0' && key <= '9') {
            _VarsHandler->addToInputBuffer(std::string(1, key));
        }
        else if (key == 13) {
            _VarsHandler->setIsClicked(false);

            if (!_VarsHandler->checkInputBufferEmpty()) {
                int number = std::stoi(_VarsHandler->getInputBuffer());

                if (_VarsHandler->getBoxID() == 0) {
                    if (_VarsHandler->getHeightLowlimit() > number) {
                        _VarsHandler->setHeightUplimit(_VarsHandler->getHeightLowlimit());
                    }
                    else {
                        _VarsHandler->setHeightUplimit(static_cast<float>(number));
                    }
                }
                else if (_VarsHandler->getBoxID() == 1) {
                    if (_VarsHandler->getHeightUplimit() < number) {
                        _VarsHandler->setHeightLowlimit(_VarsHandler->getHeightUplimit());
                    }
                    else {
                        _VarsHandler->setHeightLowlimit(static_cast<float>(number));
                    }
                }
                else if (_VarsHandler->getBoxID() == 2) {
                    if (number > _VarsHandler->getMaxRange()) {
                        _VarsHandler->setOuterRange(_VarsHandler->getMaxRange());
                    }
                    else {
                        _VarsHandler->setOuterRange(static_cast<float>(number));
                    }
                }
                else if (_VarsHandler->getBoxID() == 3) {
                    _VarsHandler->setLineGap(static_cast<float>(number));
                }
            }

            _VarsHandler->clearInputBuffer();
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

        _VarsHandler->setMousePosX(_VarsHandler->getXleft() + (_VarsHandler->getXright() - _VarsHandler->getXleft()) * (mouseX + 1.0f) / 2.0f);
        _VarsHandler->setMousePosY(_VarsHandler->getBottom() + (_VarsHandler->getTop() - _VarsHandler->getBottom()) * (mouseY + 1.0f) / 2.0f);

        if (_VarsHandler->getCurrentScreen() == Screen::Main) {
            if (isMouseClickInsideBox(0.60f, -0.85f, 0.15f, 0.075f)) {
                decreaseRange();
            }
            else if (isMouseClickInsideBox(0.75f, -0.85f, 0.15f, 0.075f)) {
                increaseRange();
            }
            else if (isMouseClickInsideBox(-0.95f, 0.85f, 0.25f, 0.1f)) {
                _VarsHandler->setCurrentScreen(Screen::Settings);
            }
        }
        else if (_VarsHandler->getCurrentScreen() == Screen::Settings) {
            if (_VarsHandler->getCurrentScreen() == Screen::Main) {
                if (isMouseClickInsideBox(0.60f, -0.85f, 0.15f, 0.075f)) {
                    decreaseRange();
                }
                else if (isMouseClickInsideBox(0.75f, -0.85f, 0.15f, 0.075f)) {
                    increaseRange();
                }
                else if (isMouseClickInsideBox(-0.95f, 0.85f, 0.25f, 0.1f)) {
                    _VarsHandler->setCurrentScreen(Screen::Settings);
                }
            }
            else if (_VarsHandler->getCurrentScreen() == Screen::Settings) {
                if (isMouseClickInsideBox(-0.95f, 0.85f, 0.25f, 0.1f)) {
                    _VarsHandler->setCurrentScreen(Screen::Main);
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
                    _VarsHandler->setBoxID(0);
                    _VarsHandler->setIsClicked(true);
                }

                else if (isMouseClickInsideBox(-0.70f, 0.55f, 0.30f, 0.1f)) {
                    _VarsHandler->setBoxID(1);
                    _VarsHandler->setIsClicked(true);
                }

                else if (isMouseClickInsideBox(-0.70f, 0.40f, 0.30f, 0.1f)) {
                    _VarsHandler->setBoxID(2);
                    _VarsHandler->setIsClicked(true);
                }

                else if (isMouseClickInsideBox(-0.70f, 0.25f, 0.50f, 0.1f)) {
                    _VarsHandler->setBoxID(3);
                    _VarsHandler->setIsClicked(true);
                }
                else if (isMouseClickInsideBox(-0.70f, 0.10f, 0.52f, 0.1f)) {
                    if (_VarsHandler->getClockwise()) _VarsHandler->setClockwise(false);
                    else _VarsHandler->setClockwise(true);
                }
            }
        }
    }
}

void CInteractionHandler::mouseHover(int x, int y) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    float mouseX = 2.0f * (x - width / 2) / std::min(width, height);
    float mouseY = 2.0f * (height / 2 - y) / std::min(width, height);

    _VarsHandler->setMousePosX(_VarsHandler->getXleft() + (_VarsHandler->getXright() - _VarsHandler->getXleft()) * (mouseX + 1.0f) / 2.0f);
    _VarsHandler->setMousePosY(_VarsHandler->getBottom() + (_VarsHandler->getTop() - _VarsHandler->getBottom()) * (mouseY + 1.0f) / 2.0f);
}

void CInteractionHandler::mouseWheel(int wheel, int direction, int x, int y) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    float mouseX = 2.0f * (x - width / 2) / std::min(width, height);
    float mouseY = 2.0f * (height / 2 - y) / std::min(width, height);

    mouseX = _VarsHandler->getXleft() + (_VarsHandler->getXright() - _VarsHandler->getXleft()) * (mouseX + 1.0f) / 2.0f;
    mouseY = _VarsHandler->getBottom() + (_VarsHandler->getTop() - _VarsHandler->getBottom()) * (mouseY + 1.0f) / 2.0f;

    if (direction > 0) {
        float newLeft = _VarsHandler->getXleft() + _VarsHandler->getZoomFactor()* (mouseX - _VarsHandler->getXleft()) / (_VarsHandler->getXright() - _VarsHandler->getXleft());
        float newRight = _VarsHandler->getXright() - _VarsHandler->getZoomFactor() * (_VarsHandler->getXright() - mouseX) / (_VarsHandler->getXright() - _VarsHandler->getXleft());
        float newBottom = _VarsHandler->getBottom() + _VarsHandler->getZoomFactor() * (mouseY - _VarsHandler->getBottom()) / (_VarsHandler->getTop() - _VarsHandler->getBottom());
        float newTop = _VarsHandler->getTop() - _VarsHandler->getZoomFactor() * (_VarsHandler->getTop() - mouseY) / (_VarsHandler->getTop() - _VarsHandler->getBottom());

        if (newRight > newLeft && newTop > newBottom) {
            _VarsHandler->setXleft(newLeft);
            _VarsHandler->setXright(newRight);
            _VarsHandler->setBottom(newBottom);
            _VarsHandler->setTop(newTop);
        }
    }
    else {
        float newLeft = _VarsHandler->getXleft() - _VarsHandler->getZoomFactor() * (mouseX - _VarsHandler->getXleft()) / (_VarsHandler->getXright() - _VarsHandler->getXleft());
        float newRight = _VarsHandler->getXright() + _VarsHandler->getZoomFactor() * (_VarsHandler->getXright() - mouseX) / (_VarsHandler->getXright() - _VarsHandler->getXleft());
        float newBottom = _VarsHandler->getBottom() - _VarsHandler->getZoomFactor() * (mouseY - _VarsHandler->getBottom()) / (_VarsHandler->getTop() - _VarsHandler->getBottom());
        float newTop = _VarsHandler->getTop() + _VarsHandler->getZoomFactor() * (_VarsHandler->getTop() - mouseY) / (_VarsHandler->getTop() - _VarsHandler->getBottom());

        if (newRight > newLeft && newTop > newBottom) {
            _VarsHandler->setXleft(newLeft);
            _VarsHandler->setXright(newRight);
            _VarsHandler->setBottom(newBottom);
            _VarsHandler->setTop(newTop);
        }
    }
    reshape(width, height);
    glutPostRedisplay();
}

void CInteractionHandler::reshape(int width, int height) {
    int size = std::min(width, height);

    glViewport((width - size) / 2, (height - size) / 2, size, size);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(_VarsHandler->getXleft(), _VarsHandler->getXright(), _VarsHandler->getBottom(), _VarsHandler->getTop(), _VarsHandler->getZNear(), _VarsHandler->getZFar());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CInteractionHandler::increaseRange() {
    _VarsHandler->addToOuterRange(30.0f);
}

void CInteractionHandler::decreaseRange() {
    _VarsHandler->addToOuterRange(-30.0f);
}

void CInteractionHandler::increaseHeightUp() {
    _VarsHandler->addToHeightUplimit(5.0f);
}

void CInteractionHandler::decreaseHeightUp() {
    _VarsHandler->addToHeightUplimit(-5.0f);
}

void CInteractionHandler::increaseHeightLow() {
    _VarsHandler->addToHeightLowlimit(5.0f);
}

void CInteractionHandler::decreaseHeightLow() {
    _VarsHandler->addToHeightLowlimit(-5.0f);
}

void CInteractionHandler::decreaseLineGap() {
    _VarsHandler->addToLineGap(15.0f);
}

void CInteractionHandler::increaseLineGap() {
    _VarsHandler->addToLineGap(-15.0f);
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

