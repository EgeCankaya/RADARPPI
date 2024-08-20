#include <GL/freeglut.h>
#include "RadarDisplayInterface.h"

void RadarDisplayInterface::run() {
   
    int argc = 1;
    char* argv[1] = { (char*)"RadarDisplay" };
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Radar PPI");

    radar.setCallbacks();
    handler.setCallbacks();

    glutMainLoop();
}

void RadarDisplayInit() {
    RadarDisplayInterface radarDisplay;
    radarDisplay.run();
}

void radarAddEnemy(float distance, float angle, float height) {
    radar.enemyWrapper(distance, angle, height);
},