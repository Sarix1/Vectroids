#ifndef POLYGON_H
#define POLYGON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_types.h>
#include "vector2.h"

#define maxPolygons 100

struct Polygon
{
    struct Vector2 origin;
    float angle;
    float angVelocity;

    struct Vector2* parentOrigin;
    float* parentAngle;

    unsigned numVectors;
    struct Vector2** vectors;

    uint8_t color[4];
};

extern int polygonCount;
extern struct Polygon* PolygonArray;

struct Polygon* makePolygon(struct Vector2 origin_, float angle_, float angVelocity_,
                            struct Vector2* parentOrigin_, float* parentAngle_,
                            unsigned numVectors_, struct Vector2* vectors_, uint8_t color_[]);

#endif
