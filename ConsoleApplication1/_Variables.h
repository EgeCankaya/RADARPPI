#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//mouse
extern float mousePosX, mousePosY;
extern bool isClicked;
extern std::string inputBuffer;
extern int boxID;
//Radar
extern int heightUplimit, heightLowlimit;
extern int maxRange;
extern float outerRange;
extern int lineGap;
extern float rangeScale;
extern bool clockwise;
extern float angle;
extern int highlightDuration;
extern int lastDetectionTime;
//ortho
extern float xleft;
extern float xright;
extern float bottom;
extern float top;
extern const float zNear;
extern const float zFar;
extern const float zoomFactor;

enum class Screen { Main, Settings };
extern Screen currentscreen;

#endif // VARIABLES_H
