#include "CRadarDisplay.h"
#include <GL/freeglut.h>
#include "_Variables.h"
#include "CDisplay.h"         
#include "CInteractionHandler.h"
#include <string>
#include <cmath>
#include <limits>
#include <fstream>
#include <iostream>
#include <ctime>

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
    static bool isFirstCall = true;

    bool hasNull = std::isnan(distance) || std::isnan(angle) || std::isnan(height);

    if (hasNull) {
        std::ofstream outFile;

       
        if (isFirstCall) {
            outFile.open("null_values_log.txt", std::ios::trunc);
            isFirstCall = false;
        }
        else {
            outFile.open("null_values_log.txt", std::ios::app); 
        }

        if (outFile.is_open()) {
            std::time_t now = std::time(nullptr);
            std::tm timeinfo;
            localtime_s(&timeinfo, &now); 

            char timestamp[20];
            std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);

            outFile << "[" << timestamp << "] "
                << "distance: " << (std::isnan(distance) ? "NULL" : std::to_string(distance))
                << ", angle: " << (std::isnan(angle) ? "NULL" : std::to_string(angle))
                << ", height: " << (std::isnan(height) ? "NULL" : std::to_string(height))
                << ", clockwise: " << (clockwise ? "true" : "false")
                << std::endl;
            outFile.close(); 
        }
        else {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    }

    // Proceed to add the enemy to the display
    display.addEnemy(distance, angle, height, clockwise);
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

void CRadarDisplay::setSeekerSpeed(float speed) {
    _VarsUserDef->setSeekerSpeed(speed);
}