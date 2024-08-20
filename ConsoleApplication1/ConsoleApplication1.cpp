#include "RadarDisplayInterface.h"


int main() {
    
    float distance = 50.0f;
    radarAddEnemy(100.0f, 45.0f, 20.0f);
    radarAddEnemy(140.0f, 55.0f, 21.0f);
    RadarDisplayInit();
    
    return 0;
}
