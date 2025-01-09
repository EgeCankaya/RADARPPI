#pragma once

class CRadarPPI {
public:
    void run();
    void addEnemy(void* dataArray, size_t arraySize);

    void updateEnemy();
    void endRadarPPI();

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

    void setSeekerSpeed(float speed);
};
