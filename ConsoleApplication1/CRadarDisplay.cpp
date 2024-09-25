#include "CRadarDisplay.h"
#include <GL/freeglut.h>
#include "_Variables.h"
#include "CDisplay.h"         
#include "CInteractionHandler.h"

_Variables* _VarsUserDef = _Variables::getInstance();
CDisplay& display = CDisplay::getInstance();
CInteractionHandler& interactionHandler = CInteractionHandler::getInstance();

void CRadarDisplay::run() {
    int argc = 1;    char* argv[1] = { (char*)"RadarDisplay" };
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Radar PPI");
    
    display.setCallbacks();
    interactionHandler.setCallbacks();
}

void CRadarDisplay::addEnemy(float distance, float angle, float height, bool clockwise) {
    display.enemyWrapper(distance, angle, height, clockwise);
}

void CRadarDisplay::updateEnemy() {
    glutPostRedisplay();
}

void CRadarDisplay::endRadarPPI() {
    glutMainLoop();
}

void CRadarDisplay::setHeightUplimit(int limit) {
    if (limit >= 0) {
        _VarsUserDef->setHeightUplimit(limit);
    }
}

int CRadarDisplay::getHeightUplimit() const {
    return _VarsUserDef->getHeightUplimit();
}

void CRadarDisplay::setHeightLowlimit(int limit) {
    if (limit >= 0 && limit <= _VarsUserDef->getHeightUplimit()) {
        _VarsUserDef->setHeightLowlimit(limit);
    }
}

int CRadarDisplay::getHeightLowlimit() const {
    return _VarsUserDef->getHeightLowlimit();
}

void CRadarDisplay::setMaxRange(int range) {
    if (range > 0) {
        _VarsUserDef->setMaxRange(range);
    }
}

int CRadarDisplay::getMaxRange() const {
    return _VarsUserDef->getMaxRange();
}

void CRadarDisplay::setOuterRange(float range) {
    _VarsUserDef->setOuterRange(range);
}

float CRadarDisplay::getOuterRange() const {
    return _VarsUserDef->getOuterRange();
}

void CRadarDisplay::setLineGap(int gap) {
    if (gap >= 0) {
        _VarsUserDef->setLineGap(gap);
    }
}

int CRadarDisplay::getLineGap() const {
    return _VarsUserDef->getLineGap();
}

void CRadarDisplay::setRangeScale(float scale) {
    if (scale > 0) {
        _VarsUserDef->setRangeScale(scale);
    }
}

float CRadarDisplay::getRangeScale() const {
    return _VarsUserDef->getRangeScale();
}

void CRadarDisplay::setClockwise(bool direction) {
    _VarsUserDef->setClockwise(direction);
}

bool CRadarDisplay::getClockwise() const {
    return _VarsUserDef->getClockwise();
}

void CRadarDisplay::setAngle(float a) {
    _VarsUserDef->setAngle(a);
}

float CRadarDisplay::getAngle() const {
    return _VarsUserDef->getAngle();
}

void CRadarDisplay::setHighlightDuration(int duration) {
    if (duration >= 0) {
        _VarsUserDef->setHighlightDuration(duration);
    }
}

int CRadarDisplay::getHighlightDuration() const {
    return _VarsUserDef->getHighlightDuration();
}

void CRadarDisplay::setLastDetectionTime(int time) {
    if (time >= 0) {
        _VarsUserDef->setLastDetectionTime(time);
    }
}

int CRadarDisplay::getLastDetectionTime() const {
    return _VarsUserDef->getLastDetectionTime();
}