#include "RadarPPI.h"
#include <GL/freeglut.h>
#include "_Variables.h"
#include "CDisplay.h"         
#include "CInteractionHandler.h"
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <ctime>


_Variables* _VarsUserDef = _Variables::getInstance();
CDisplay& display = CDisplay::getInstance();
CInteractionHandler& interactionHandler = CInteractionHandler::getInstance();

typedef struct {
    float dist_km;
    float angle_deg;
    float height_m;
    float seeker_deg;
}Scope_Data;

void CRadarPPI::run() {
    int argc = 1;    char* argv[1] = { (char*)"RadarDisplay" };
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Radar PPI");
    
    display.setCallbacks();
    interactionHandler.setCallbacks();
}

void CRadarPPI::addEnemy(void* dataArray, size_t arraySize) {

    Scope_Data* data = static_cast<Scope_Data*>(dataArray);

    float distance = 0.0f;
    float angle = 0.0f;
    float height = 0.0f;
    float seekerAngle = 0.0f;

    for (size_t i = 0; i < arraySize; ++i) {
        distance = data[i].dist_km;
        angle = data[i].angle_deg;
        height = data[i].height_m;
        seekerAngle = data[i].seeker_deg;

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
                int angle_info = static_cast<int>(seekerAngle) % 360;

                outFile << "[" << timestamp << "] "
                    << "distance: " << (std::isnan(distance) ? "NULL" : std::to_string(distance))
                    << ", angle: " << (std::isnan(angle) ? "NULL" : std::to_string(angle))
                    << ", height: " << (std::isnan(height) ? "NULL" : std::to_string(height))
                    << ", seeker angle: " << angle_info
                    << std::endl;
                outFile.close();
            }
            else {
                std::cerr << "Unable to open file for writing." << std::endl;
            }
        }        
        display.addEnemy(distance, angle, height, seekerAngle);
    }
}

void CRadarPPI::updateEnemy() {
    glutPostRedisplay();
}

void CRadarPPI::endRadarPPI() {
    glutMainLoop();
}

void CRadarPPI::setHeightUplimit(int limit) {
    if (limit >= 0) {
        _VarsUserDef->setHeightUplimit(limit);
    }
}

int CRadarPPI::getHeightUplimit() const {
    return _VarsUserDef->getHeightUplimit();
}

void CRadarPPI::setHeightLowlimit(int limit) {
    if (limit >= 0 && limit <= _VarsUserDef->getHeightUplimit()) {
        _VarsUserDef->setHeightLowlimit(limit);
    }
}

int CRadarPPI::getHeightLowlimit() const {
    return _VarsUserDef->getHeightLowlimit();
}

void CRadarPPI::setOuterRange(float range) {
    _VarsUserDef->setOuterRange(range);
}

float CRadarPPI::getOuterRange() const {
    return _VarsUserDef->getOuterRange();
}

void CRadarPPI::setLineGap(int gap) {
    if (gap >= 0) {
        _VarsUserDef->setLineGap(gap);
    }
}

int CRadarPPI::getLineGap() const {
    return _VarsUserDef->getLineGap();
}

void CRadarPPI::setClockwise(bool direction) {
    _VarsUserDef->setClockwise(direction);
}

bool CRadarPPI::getClockwise() const {
    return _VarsUserDef->getClockwise();
}

void CRadarPPI::setAngle(float a) {
    _VarsUserDef->setAngle(a);
}

float CRadarPPI::getAngle() const {
    return _VarsUserDef->getAngle();
}

void CRadarPPI::setHighlightDuration(int duration) {
    if (duration >= 0) {
        _VarsUserDef->setHighlightDuration(duration);
    }
}

int CRadarPPI::getHighlightDuration() const {
    return _VarsUserDef->getHighlightDuration();
}

void CRadarPPI::setSeekerSpeed(float speed) {
    _VarsUserDef->setSeekerSpeed(speed);
}