#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

extern float mousePosX, mousePosY;
extern bool isClicked;
extern string inputBuffer;
extern int boxID;
extern int heightUplimit, heightLowlimit;
extern int maxRange;
extern float outerRange;
extern int lineGap;
extern float rangeScale;

extern float scale;
extern float xleft;
extern float xright;
extern float bottom;
extern float top;

extern const float zNear;
extern const float zFar;
extern const float zoomFactor;
extern bool clockwise;

enum class Screen { Main, Settings };
extern Screen currentscreen;

extern float angle;
extern float searchStartAngle;
extern float searchEndAngle;
extern float limitedConst;
extern int highlightDuration;
extern int lastDetectionTime;
extern float objectDistance;
extern float objectAngle;
extern float objectHeight;

#endif // VARIABLES_H
