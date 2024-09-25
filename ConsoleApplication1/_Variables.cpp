#include "_Variables.h"

_Variables* _Variables::instance = nullptr;

_Variables::_Variables()
    : mousePosX(0), mousePosY(0), isClicked(false), boxID(0),
    heightUplimit(30), heightLowlimit(0), maxRange(300),
    outerRange(300.0f), lineGap(30), rangeScale(1.0f), clockwise(true),
    angle(0.0f), highlightDuration(10000), lastDetectionTime(0),
    xleft(-1.0f), xright(1.0f), bottom(-1.0f), top(1.0f),
    currentscreen(Screen::Main) {}

_Variables* _Variables::getInstance() {
    if (!instance)
        instance = new _Variables();
    return instance;
}

float _Variables::getMousePosX() const { return mousePosX; }
void _Variables::setMousePosX(float x) { mousePosX = x; }

float _Variables::getMousePosY() const { return mousePosY; }
void _Variables::setMousePosY(float y) { mousePosY = y; }

bool _Variables::getIsClicked() const { return isClicked; }
void _Variables::setIsClicked(bool clicked) { isClicked = clicked; }

std::string _Variables::getInputBuffer() const { return inputBuffer; }
void _Variables::setInputBuffer(const std::string& input) { inputBuffer = input; }
void _Variables::addToInputBuffer(const std::string& input) { inputBuffer += input; }
bool _Variables::checkInputBufferEmpty() const { return inputBuffer.empty(); }
void _Variables::clearInputBuffer() { inputBuffer.clear(); }

int _Variables::getBoxID() const { return boxID; }
void _Variables::setBoxID(int id) { boxID = id; }

int _Variables::getHeightUplimit() const { return heightUplimit; }
void _Variables::setHeightUplimit(int limit) { heightUplimit = limit; }
void _Variables::addToHeightUplimit(int limit) { heightUplimit += limit; }

int _Variables::getHeightLowlimit() const { return heightLowlimit; }
void _Variables::setHeightLowlimit(int limit) { heightLowlimit = limit; }
void _Variables::addToHeightLowlimit(int limit) { heightLowlimit += limit; }

int _Variables::getMaxRange() const { return maxRange; }
void _Variables::setMaxRange(int range) { maxRange = range; }

float _Variables::getOuterRange() const { return outerRange; }
void _Variables::setOuterRange(float range) { outerRange = range; }
void _Variables::addToOuterRange(float range) { outerRange += range; }

int _Variables::getLineGap() const { return lineGap; }
void _Variables::setLineGap(int gap) { lineGap = gap; }
void _Variables::addToLineGap(int gap) { lineGap += gap; }

float _Variables::getRangeScale() const { return rangeScale; }
void _Variables::setRangeScale(float scale) { rangeScale = scale; }

bool _Variables::getClockwise() const { return clockwise; }
void _Variables::setClockwise(bool cw) { clockwise = cw; }

float _Variables::getAngle() const { return angle; }
void _Variables::setAngle(float a) { angle = a; }
void _Variables::addToAngle(float a) { angle += a; }

int _Variables::getHighlightDuration() const { return highlightDuration; }
void _Variables::setHighlightDuration(int duration) { highlightDuration = duration; }

int _Variables::getLastDetectionTime() const { return lastDetectionTime; }
void _Variables::setLastDetectionTime(int time) { lastDetectionTime = time; }

float _Variables::getXleft() const { return xleft; }
void _Variables::setXleft(float x) { xleft = x; }

float _Variables::getXright() const { return xright; }
void _Variables::setXright(float x) { xright = x; }

float _Variables::getBottom() const { return bottom; }
void _Variables::setBottom(float b) { bottom = b; }

float _Variables::getTop() const { return top; }
void _Variables::setTop(float t) { top = t; }

float _Variables::getZNear() { return zNear; }
float _Variables::getZFar() { return zFar; }
float _Variables::getZoomFactor() { return zoomFactor; }

Screen _Variables::getCurrentScreen() const { return currentscreen; }
void _Variables::setCurrentScreen(Screen screen) { currentscreen = screen; }
