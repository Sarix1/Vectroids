#ifndef POLYGON_H
#define POLYGON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_types.h>
#include "vector.h"

#define maxPolygons 100

struct Polygon
{
    struct Vector2 origin;
    float angle;
    float angVelocity;

    struct Vector2* parentOrigin;
    float* parentAngle;

    unsigned numPoints;
    struct Vector2** points;

    uint8_t color[4];
};

int polygonCount = 0;
struct Polygon* PolygonArray;

struct Polygon* makePolygon(struct Vector2 origin_, float angle_, float angVelocity_,
                            struct Vector2* parentOrigin_, float* parentAngle_,
                            unsigned numPoints_, struct Vector2* points_, uint8_t color_[]);

#endif
