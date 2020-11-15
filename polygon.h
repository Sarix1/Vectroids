#ifndef POLYGON_H
#define POLYGON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "vector2.h"

struct Polygon
{
    struct Vec2 origin;
    float angle;
    float angVelocity;
    int numVectors;
    int vectors;
    int parent;
    uint8_t color[4];
};

extern int numPolygons;
extern struct Polygon* PolygonArray;

int initPolygonArray();
int makePolygon(struct Vec2 origin_, float angle_, float angVelocity_,
                int numVectors_, int vectors_, int parent, uint8_t color_[]);
void printPolygon(int index);

#endif
