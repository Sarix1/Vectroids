#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "globals.h"
#include "polygon.h"
#include "vector2.h"

struct BaseObject
{
    struct Vector2 origin;
    struct Vector2 velocity;
    struct Vector2 moveVector;
    float angle;
    float angVelocity;
    float radius;
    struct Polygon* shape;
};

extern int baseObjectCount;
extern struct BaseObject* BaseObjectArray;
extern struct BaseObject* Player;

struct BaseObject* makeBaseObject(struct Vector2 origin_, struct Vector2 velocity_,
                                  float angle_, float angVelocity_, float radius_, struct Polygon* shape_);
// void copyBaseObject(struct BaseObject* source, struct BaseObject* destination);
// void killBaseObject(struct BaseObject* target);

#endif
