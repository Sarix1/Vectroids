#include "baseobject.h"

#include <stdio.h>

int baseObjectCount = 0;
struct BaseObject* BaseObjectArray;
struct BaseObject* Player;

struct BaseObject* makeBaseObject(struct Vector2 origin_, struct Vector2 velocity_,
                                  float angle_, float angVelocity_, struct Polygon* shape_)
{
    if (baseObjectCount < maxBaseObjects)
    {
        struct BaseObject* newBaseObject = &(BaseObjectArray[baseObjectCount]);
        *newBaseObject = (struct BaseObject){.origin        = origin_,
                                             .velocity      = velocity_,
                                             .angle         = angle_,
                                             .angVelocity   = angVelocity_,
                                             .shape         = shape_};

        return &(BaseObjectArray[baseObjectCount++]);
    }

    else
    {
        printf("maxBaseObjects exceeded");

        return NULL;
    }
}
