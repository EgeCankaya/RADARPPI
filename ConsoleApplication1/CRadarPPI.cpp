#include "CRadarPPI.h"

void CRadarPPI::run() {
    display->run();
}

void CRadarPPI::endRadarPPI() {
    display->endRadarPPI();
}

void CRadarPPI::addEnemy(float distance, float angle, float height, bool clockwise) {
    display->addEnemy(distance, angle, height, clockwise);
}

void CRadarPPI::updateEnemy() {
    display->updateEnemy();
}

void CRadarPPI::setHeightUplimit(int limit) {
    display->setHeightUplimit(limit);
}

int CRadarPPI::getHeightUplimit() const {
    return display->getHeightUplimit();
}

void CRadarPPI::setHeightLowlimit(int limit) {
    display->setHeightLowlimit(limit);
}

int CRadarPPI::getHeightLowlimit() const {
    return display->getHeightLowlimit();
}

void CRadarPPI::setOuterRange(float range) {
    display->setOuterRange(range);
}

float CRadarPPI::getOuterRange() const {
    return display->getOuterRange();
}

void CRadarPPI::setLineGap(int gap) {
    display->setLineGap(gap);
}

int CRadarPPI::getLineGap() const {
    return display->getLineGap();
}

void CRadarPPI::setClockwise(bool direction) {
    display->setClockwise(direction);
}

bool CRadarPPI::getClockwise() const {
    return display->getClockwise();
}

void CRadarPPI::setAngle(float a) {
    display->setAngle(a);
}

float CRadarPPI::getAngle() const {
    return display->getAngle();
}

void CRadarPPI::setHighlightDuration(int duration) {
    display->setHighlightDuration(duration);
}

int CRadarPPI::getHighlightDuration() const {
    return display->getHighlightDuration();
}

void CRadarPPI::setSeekerSpeed(float speed) {
    display->setSeekerSpeed(speed);
}