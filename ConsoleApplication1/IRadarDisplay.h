#pragma once
#ifndef IRADARDISPLAY_H
#define IRADARDISPLAY_H

class IRadarDisplay {
public:
    virtual void run() = 0;
    virtual void addEnemy(float distance, float angle, float height, bool clockwise) = 0;

    virtual void updateEnemy() = 0;
    virtual void endRadarPPI() = 0;
    virtual ~IRadarDisplay() = default;

    virtual void setHeightUplimit(int limit) = 0;
    virtual int getHeightUplimit() const = 0;

    virtual void setHeightLowlimit(int limit) = 0;
    virtual int getHeightLowlimit() const = 0;
 
    virtual void setOuterRange(float range) = 0;
    virtual float getOuterRange() const = 0;

    virtual void setLineGap(int gap) = 0;
    virtual int getLineGap() const = 0;
   
    virtual void setClockwise(bool direction) = 0;
    virtual bool getClockwise() const = 0;
     
    virtual void setAngle(float a) = 0;
    virtual float getAngle() const = 0;
    
    virtual void setHighlightDuration(int duration) = 0;
    virtual int getHighlightDuration() const = 0;
};

#endif // IRADARDISPLAY_H
