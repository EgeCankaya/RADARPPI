#pragma once
#ifndef DRAWINGLABELS_H
#define DRAWINGLABELS_H

class CDrawingLabels {
public:
    static CDrawingLabels& getInstance();
private:
    friend class CDisplay;
    void renderText(float x, float y, const char* text);
    void drawSeeker();
    void drawLinesWithAngles(int gap_in_degrees);
    void drawCircle(float cx, float cy, float radius, int num_segments);
    void drawRangeLabels();
    void drawRangeLabel(float radius, float value);
    void drawBox();
    void renderValues(float x, float y, const char* text);
    void drawCurrentValues();
    void drawButton(float x, float y, float width, float height, const char* label);
    void drawButtons();
};

#endif // DRAWINGLABELS_H