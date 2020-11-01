#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "polygon.h"
#include "vector2.h"

#define maxBaseObjects 100

struct BaseObject
{
    struct Vector2 origin;
    struct Vector2 velocity;
    struct Vector2 moveVector;
    float angle;
    float angVelocity;
    struct Polygon* shape;
};

extern int baseObjectCount;
extern struct BaseObject* BaseObjectArray;
extern struct BaseObject* Player;

struct BaseObject* makeBaseObject(struct Vector2 origin_, struct Vector2 velocity_,
                                  float angle_, float angVelocity_, struct Polygon* shape_);

#endif
