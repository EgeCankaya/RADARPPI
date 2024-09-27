#pragma once
#ifndef CRADARPPI_H
#define CRADARPPI_H

#include "IRadarDisplay.h"

class CRadarPPI {
public:
    CRadarPPI(IRadarDisplay* display) : display(display) {}

    void run();
    void endRadarPPI();
    void addEnemy(float distance, float angle, float height, bool clockwise);
    void updateEnemy();

    void setHeightUplimit(int limit);
    int getHeightUplimit() const;

    void setHeightLowlimit(int limit);
    int getHeightLowlimit() const;

    void setOuterRange(float range);
    float getOuterRange() const;

    void setLineGap(int gap);
    int getLineGap() const;

    void setClockwise(bool direction);
    bool getClockwise() const;

    void setAngle(float a);
    float getAngle() const;

    void setHighlightDuration(int duration);
    int getHighlightDuration() const;

private:
    IRadarDisplay* display;
};

#endif // CRADARPPI_H
