#ifndef CRADARPPI_H
#define CRADARPPI_H

#include "IRadarDisplay.h"
#include <vector>

class CRadarPPI {
public:
    CRadarPPI(IRadarDisplay* display) : display(display) {}

    void run();
    void endRadarPPI();
    void addEnemy(float distance, float angle, float height);
    void updateEnemy();

    // Getters and Setters for the variables
    void setHeightUplimit(int limit);
    int getHeightUplimit() const;

    void setHeightLowlimit(int limit);
    int getHeightLowlimit() const;

    void setMaxRange(int range);
    int getMaxRange() const;

    void setOuterRange(float range);
    float getOuterRange() const;

    void setLineGap(int gap);
    int getLineGap() const;

    void setRangeScale(float scale);
    float getRangeScale() const;

    void setClockwise(bool direction);
    bool getClockwise() const;

    void setAngle(float a);
    float getAngle() const;

    void setHighlightDuration(int duration);
    int getHighlightDuration() const;

    void setLastDetectionTime(int time);
    int getLastDetectionTime() const;

private:
    IRadarDisplay* display;
    std::vector<std::pair<float, float>> dataPoints;
};

#endif // CRADARPPI_H
