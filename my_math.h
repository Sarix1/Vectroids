#ifndef MATH_H
#define MATH_H

#include <math.h>
#include "globals.h"

#define degToRad(degrees) ((degrees) * M_PI / 180.0)
#define radToDeg(radians) ((radians) * 180.0 / M_PI)

float randomFloat(float min, float max);
void setColor(uint8_t target[], int color[]);
void addToColor(uint8_t target[], int color[]);
uint32_t randomColor();

#endif
