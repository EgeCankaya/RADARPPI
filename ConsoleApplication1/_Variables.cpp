#include "_Variables.h"

float mousePosX, mousePosY;
bool isClicked = false;
std::string inputBuffer;

int boxID = 0;
int heightUplimit = 30, heightLowlimit = 0;
int maxRange = 300;
float outerRange = 300.0f;
int lineGap = 30;
float rangeScale = 1.0f;


float xleft = -1.0f;
float xright = 1.0f;
float bottom = -1.0f;
float top = 1.0f;
const float zNear = -1.0f;
const float zFar = 1.0f;
const float zoomFactor = 0.1f;

bool clockwise = true;

float angle = 0.0f;

int highlightDuration = 10000;
int lastDetectionTime = 0;

Screen currentscreen;
