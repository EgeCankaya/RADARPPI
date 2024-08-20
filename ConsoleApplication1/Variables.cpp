#include "Variables.h"

float mousePosX, mousePosY;
bool isClicked = false;
string inputBuffer;
int boxID = 0;
int heightUplimit = 30, heightLowlimit = 15; 
int maxRange = 300;
float outerRange = 300.0f;
int lineGap = 30;
float rangeScale = 1.0f;

float scale;
float xleft = -1.0f;
float xright = 1.0f;
float bottom = -1.0f;
float top = 1.0f;

const float zNear = -1.0f;
const float zFar = 1.0f;
const float zoomFactor = 0.1f;
bool clockwise = true;

Screen currentscreen = Screen::Main;

float angle = 0.0f;
float searchStartAngle = 0.0f;
float searchEndAngle = 30.0f;
float limitedConst = 1.0f;
int highlightDuration = 1500;
int lastDetectionTime = 0;
float objectDistance;
float objectAngle;
float objectHeight;
