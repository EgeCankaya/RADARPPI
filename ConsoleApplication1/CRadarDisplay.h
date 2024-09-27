#pragma once
#include "IRadarDisplay.h"

class CRadarDisplay : public IRadarDisplay {
public:
    void run() override;
    void addEnemy(float distance, float angle, float height, bool clockwise) override;
    void updateEnemy() override;
    void endRadarPPI() override;

    void setHeightUplimit(int limit)  override;
    int getHeightUplimit() const  override;

    void setHeightLowlimit(int limit)  override;
    int getHeightLowlimit() const  override;

    void setOuterRange(float range)  override;
    float getOuterRange() const  override;

    void setLineGap(int gap)  override;
    int getLineGap() const  override;

    void setClockwise(bool direction)  override;
    bool getClockwise() const  override;

    void setAngle(float a)  override;
    float getAngle() const  override;

    void setHighlightDuration(int duration)  override;
    int getHighlightDuration() const  override;
      
};
