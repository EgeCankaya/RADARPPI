/*#include "RadarDisplayInterface.h"
#include <GL/freeglut.h>

IRadarDisplay::IRadarDisplay(){}

IRadarDisplay& IRadarDisplay::getInstance() {
    static IRadarDisplay instance;
    return instance;
}

void IRadarDisplay::run() {
    int argc = 1;
    char* argv[1] = { (char*)"RadarDisplay" };
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Radar PPI");

    radar.setCallbacks();
    handler.setCallbacks();

    
}

void IRadarDisplay::addEnemy(float& distance, float& angle, float& height) {
    radar.enemyWrapper(distance, angle, height);
}

void updateEnemy(int enemyIndex, float distance, float angle, float height) {
    radar.updateEnemy(enemyIndex, distance, angle, height);
}

void EndOpenGL()
{glutMainLoop();
}

void Update()
{
    glutPostRedisplay();
}

void IRadarDisplayInit() {
    IRadarDisplay::getInstance().run();
}

void radarAddEnemy(float& distance, float& angle, float& height) {
    IRadarDisplay::getInstance().addEnemy(distance, angle, height);
    glutPostRedisplay();
}

void radarUpdateEnemy(int enemyIndex, float distance, float angle, float height) {
    IRadarDisplay::getInstance().updateEnemy(enemyIndex, distance, angle, height);
    glutPostRedisplay();
}
*/