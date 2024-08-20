#include "Display.h"
#include "InteractionHandler.h"
#include "DrawingLabels.h"

class RadarDisplayInterface {
public:
    void run();
    void addEnemy(float distance, float angle, float height);
};

void radarAddEnemy(float distance, float angle, float height);
void RadarDisplayInit();

