#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "globals.h"
#include "polygon.h"
#include "vector2.h"

struct BaseObject
{
    struct Vec2 origin;
    struct Vec2 velocity;
    struct Vec2 moveVector;
    float angle;
    float angVelocity;
    float radius;
    int shape;
    int health;
};

extern int numBaseObjects;
extern struct BaseObject* BaseObjectArray;

int initBaseObjectArray();
int makeBaseObject(struct Vec2 origin_, struct Vec2 velocity_, float angle_, float angVelocity_, float radius_, int shape_, int health_);
void printBaseObject(int index);

#endif
