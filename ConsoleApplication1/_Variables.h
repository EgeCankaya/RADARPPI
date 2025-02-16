#pragma once
#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

enum class Screen { Main, Settings };

class _Variables {
private:
    static _Variables* instance;

    float mousePosX, mousePosY;
    bool isClicked;
    std::string inputBuffer;
    int boxID;
    bool isMinimized;

    int heightUplimit, heightLowlimit;
    float outerRange;
    int lineGap;
    float rangeScale;
    bool clockwise;
    float clockwiseCheck;
    float angle;
    float seekerSpeed;
    int highlightDuration;
    int lastDetectionTime;

    float xleft;
    float xright;
    float bottom;
    float top;
    static constexpr float zNear = -1.0f;
    static constexpr float zFar = 1.0f;
    static constexpr float zoomFactor = 0.1f;

    Screen currentscreen;

    _Variables();

public:
    static _Variables* getInstance();

    // Mouse variables
    float getMousePosX() const;
    void setMousePosX(float x);

    float getMousePosY() const;
    void setMousePosY(float y);

    bool getIsClicked() const;
    void setIsClicked(bool clicked);

    std::string getInputBuffer() const;
    void setInputBuffer(const std::string& input);
    void addToInputBuffer(const std::string& input);
    bool checkInputBufferEmpty() const;
    void clearInputBuffer();

    int getBoxID() const;
    void setBoxID(int id);

    bool getIsMinimized() const;
    void setIsMinimized(bool minimized);

    // Radar variables
    int getHeightUplimit() const;
    void setHeightUplimit(int limit);
    void addToHeightUplimit(int limit);

    int getHeightLowlimit() const;
    void setHeightLowlimit(int limit);
    void addToHeightLowlimit(int limit);

    float getOuterRange() const;
    void setOuterRange(float range);
    void addToOuterRange(float range);

    int getLineGap() const;
    void setLineGap(int gap);
    void addToLineGap(int gap);

    float getRangeScale() const;
    void setRangeScale(float scale);

    bool getClockwise() const;
    void setClockwise(bool cw);

    float getClockwiseCheck() const;
    void setClockwiseCheck(float a);

    float getAngle() const;
    void setAngle(float a);
    void addToAngle(float a);

    float getSeekerSpeed() const;
    void setSeekerSpeed(float speed);

    int getHighlightDuration() const;
    void setHighlightDuration(int duration);

    int getLastDetectionTime() const;
    void setLastDetectionTime(int time);

    // Ortho variables
    float getXleft() const;
    void setXleft(float x);

    float getXright() const;
    void setXright(float x);

    float getBottom() const;
    void setBottom(float b);

    float getTop() const;
    void setTop(float t);

    // Constants for ortho
    static float getZNear();
    static float getZFar();
    static float getZoomFactor();

    // Screen state
    Screen getCurrentScreen() const;
    void setCurrentScreen(Screen screen);
};

#endif // VARIABLES_H
