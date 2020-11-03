#include "baseobject.h"

#include <stdio.h>

int baseObjectCount = 0;
struct BaseObject* BaseObjectArray;
struct BaseObject* Player;

struct BaseObject* makeBaseObject(struct Vector2 origin_, struct Vector2 velocity_,
                                  float angle_, float angVelocity_, float radius_, struct Polygon* shape_)
{
    if (baseObjectCount < maxBaseObjects)
    {
        struct BaseObject* newBaseObject = &(BaseObjectArray[baseObjectCount]);
        *newBaseObject = (struct BaseObject){.origin        = origin_,
                                             .velocity      = velocity_,
                                             .angle         = angle_,
                                             .angVelocity   = angVelocity_,
                                             .radius        = radius_,
                                             .shape         = shape_};

        return &(BaseObjectArray[baseObjectCount++]);
    }

    else
    {
        printf("maxBaseObjects exceeded\n");

        return NULL;
    }
}

/*
void copyBaseObject(struct BaseObject* source, struct BaseObject* destination)
{
    copyPolygon(source->shape, destination->shape);
    *destination = *source;
}

void killBaseObject(struct BaseObject* target)
{
    copyBaseObject(&(BaseObjectArray[--baseObjectCount]), target);
}
*/
