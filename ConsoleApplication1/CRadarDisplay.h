#include "IRadarDisplay.h"
#include "CDisplay.h"         
#include "CInteractionHandler.h"

class CRadarDisplay : public IRadarDisplay {
public:
    void run() override;
    //void addEnemy(float* distance, float* angle, float* height) override;
    void addEnemy(float distance, float angle, float height) override;
    void updateEnemy() override;
    void endRadarPPI() override;

    void setHeightUplimit(int limit)  override;
    int getHeightUplimit() const  override;

    void setHeightLowlimit(int limit)  override;
    int getHeightLowlimit() const  override;

    void setMaxRange(int range)  override;
    int getMaxRange() const  override;

    void setOuterRange(float range)  override;
    float getOuterRange() const  override;

    void setLineGap(int gap)  override;
    int getLineGap() const  override;

    void setRangeScale(float scale)  override;
    float getRangeScale() const  override;

    void setClockwise(bool direction)  override;
    bool getClockwise() const  override;

    void setAngle(float a)  override;
    float getAngle() const  override;

    void setHighlightDuration(int duration)  override;
    int getHighlightDuration() const  override;

    void setLastDetectionTime(int time)  override;
    int getLastDetectionTime() const  override;

      
};
