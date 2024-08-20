#ifndef INTERACTION_HANDLER_H
#define INTERACTION_HANDLER_H

#include <GL/freeglut.h>
#include <string>

#include "Variables.h"

class InteractionHandler {
public:
 
    static InteractionHandler& getInstance();
    void setCallbacks();

private:
    bool isMouseClickInsideBox(float buttonX, float buttonY, float buttonWidth, float buttonHeight);
    void keyboard(unsigned char key, int x, int y);
    void mouse(int button, int state, int x, int y);
    void mouseHover(int x, int y);
    void mouseWheel(int wheel, int direction, int x, int y);
    void reshape(int width, int height);

    void increaseRange();
    void decreaseRange();
    void increaseHeightUp();
    void decreaseHeightUp();
    void increaseHeightLow();
    void decreaseHeightLow();
    void increaseLineGap();
    void decreaseLineGap();

    static void keyboardWrapper(unsigned char key, int x, int y);
    static void mouseHoverWrapper(int x, int y);
    static void mouseWheelWrapper(int wheel, int direction, int x, int y);
    static void reshapeWrapper(int width, int height);
    static void mouseWrapper(int button, int state, int x, int y);
};
extern InteractionHandler handler;

#endif // INTERACTION_HANDLER_H
