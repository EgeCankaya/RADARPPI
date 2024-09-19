#include "CRadarDisplay.h"
#include <GL/freeglut.h>
#include "_Variables.h"

void CRadarDisplay::run() {
    int argc = 1;    char* argv[1] = { (char*)"RadarDisplay" };
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Radar PPI");
    
    radar.setCallbacks();
    handler.setCallbacks();
}

void CRadarDisplay::addEnemy(float distance, float angle, float height) {
    radar.enemyWrapper(distance, angle, height);
}

void CRadarDisplay::updateEnemy() {
    glutPostRedisplay();
}

void CRadarDisplay::endRadarPPI() {
    glutMainLoop();
}

void CRadarDisplay::setHeightUplimit(int limit) {
    if (limit >= 0) {
        heightUplimit = limit;
    }
}

int CRadarDisplay::getHeightUplimit() const {
    return heightUplimit;
}

void CRadarDisplay::setHeightLowlimit(int limit) {
    if (limit >= 0 && limit <= heightUplimit) { 
        heightLowlimit = limit;
    }
}

int CRadarDisplay::getHeightLowlimit() const {
    return heightLowlimit;
}

void CRadarDisplay::setMaxRange(int range) {
    if (range > 0) {
        maxRange = range;
    }
}

int CRadarDisplay::getMaxRange() const {
    return maxRange;
}

void CRadarDisplay::setOuterRange(float range) {
    if (range > 0 && range <= maxRange) {
        outerRange = range;
    }
    else {
        outerRange = maxRange;  
    }
}

float CRadarDisplay::getOuterRange() const {
    return outerRange;
}

void CRadarDisplay::setLineGap(int gap) {
    if (gap >= 0) {
        lineGap = gap;
    }
}

int CRadarDisplay::getLineGap() const {
    return lineGap;
}

void CRadarDisplay::setRangeScale(float scale) {
    if (scale > 0) {
        rangeScale = scale;
    }
}

float CRadarDisplay::getRangeScale() const {
    return rangeScale;
}

void CRadarDisplay::setClockwise(bool direction) {
    clockwise = direction;
}

bool CRadarDisplay::getClockwise() const {
    return clockwise;
}

void CRadarDisplay::setAngle(float a) {
    angle = a;
}

float CRadarDisplay::getAngle() const {
    return angle;
}

void CRadarDisplay::setHighlightDuration(int duration) {
    if (duration >= 0) {
        highlightDuration = duration;
    }
}

int CRadarDisplay::getHighlightDuration() const {
    return highlightDuration;
}

void CRadarDisplay::setLastDetectionTime(int time) {
    if (time >= 0) {
        lastDetectionTime = time;
    }
}

int CRadarDisplay::getLastDetectionTime() const {
    return lastDetectionTime;
}