#ifndef DRAWINGLABELS_H
#define DRAWINGLABELS_H

#include <GL/freeglut.h>
#include <cmath>
#include "Variables.h"
#include "Display.h"

class DrawingLabels {

private:
    friend class Display;

    void renderText(float x, float y, const char* text);
    void drawString(float x, float y, const char* str);
    void drawSeeker();
    void drawLinesWithAngles(int gap_in_degrees);
    void drawCircle(float cx, float cy, float radius, int num_segments);
    void drawRangeLabels();
    void drawRangeLabel(float radius, float value);
    void drawUnderline();
    void renderValues(float x, float y, const char* text);
    void drawCurrentValues();
    void drawButton(float x, float y, float width, float height, const char* label);
    void drawButtons();
};
extern DrawingLabels label;

#endif // DRAWINGLABELS_H

