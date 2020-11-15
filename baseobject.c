#include "baseobject.h"

#include <stdio.h>

int numBaseObjects;
struct BaseObject* BaseObjectArray;

int initBaseObjectArray()
{
    numBaseObjects = 0;
    BaseObjectArray = calloc(maxBaseObjects, sizeof(struct BaseObject));

    if (BaseObjectArray == NULL)
    {
        printf("calloc() failed for BaseObjectArray\n");

        return 1;
    }

    return 0;
}

int makeBaseObject(struct Vec2 origin_, struct Vec2 velocity_, float angle_, float angVelocity_, float radius_, int shape_, int health_)
{
    if (numBaseObjects < maxBaseObjects)
    {
        struct BaseObject* newBaseObject = &(BaseObjectArray[numBaseObjects++]);
        *newBaseObject = (struct BaseObject)
        {
            .origin        = origin_,
            .velocity      = velocity_,
            .angle         = angle_,
            .angVelocity   = angVelocity_,
            .radius        = radius_,
            .shape         = shape_,
            .health        = health_
        };

        return numBaseObjects-1;
    }
    else
    {
        printf("maxBaseObjects exceeded\n");

        return -1;
    }
}

void killBaseObject(int index)
{
    /**** debug ****/ /*
    printf("Before kill:\n\n\
numBaseObjects: %d\n\
numPolygons: %d\n\
numVec2: %d\n\n",
    numBaseObjects,
    numPolygons,
    numVec2);
    printBaseObject(index);
    printPolygon(BaseObjectArray[index].shape);
    */ /**** debug ****/

    // Index is same as targetBaseObjectId
    struct BaseObject* targetBaseObject = &(BaseObjectArray[index]);

    int substituteBaseObjectId               = --numBaseObjects;
    struct BaseObject* substituteBaseObject  = &(BaseObjectArray[substituteBaseObjectId]);

    int targetPolyId                        = targetBaseObject->shape;
    struct Polygon* targetPolygon           = &(PolygonArray[targetPolyId]);

    int substitutePolyId                     = BaseObjectArray[numBaseObjects].shape;
    struct Polygon* substitutePoly           = &(PolygonArray[substitutePolyId]);

    int targetVecsId                        = targetPolygon->vectors;
    struct Vec2* targetVecs                 = &(Vec2Array[targetVecsId]);

    int substituteVecsId                     = targetPolygon->vectors;
    struct Vec2* substituteVecs              = &(Vec2Array[targetVecsId]);

    *targetBaseObject   = *substituteBaseObject;
    *targetPolygon      = *substitutePoly;
    memcpy(targetVecs, substituteVecs, sizeof(struct Vec2) * vec2ChunkSize);  //substitutePoly->numVectors);

    if (substitutePolyId == numPolygons-1)
        numPolygons--;
    else
        *substitutePoly = PolygonArray[--numPolygons];

    if (substituteVecsId + vec2ChunkSize + 1 > numVec2)
        numVec2 -= vec2ChunkSize;
    else
    {
        memcpy(substituteVecs, &(Vec2Array[numVec2-vec2ChunkSize]), sizeof(struct Vec2) * vec2ChunkSize);
        numVec2 -= vec2ChunkSize;
    }

    targetPolygon->parent   = index;
    targetPolygon->vectors  = targetVecsId;
    targetBaseObject->shape = targetPolyId;

    /**** debug ****/ /*
    printf("AFTER kill:\n\n\
numBaseObjects: %d\n\
numPolygons: %d\n\
numVec2: %d\n\n",
    numBaseObjects,
    numPolygons,
    numVec2);
    printBaseObject(index);
    printPolygon(BaseObjectArray[index].shape);
    */ /**** debug ****/
}

void printBaseObject(int index)
{
    struct BaseObject* o = &(BaseObjectArray[index]);

    printf("\
BaseObject: %d\n\
Origin: %f, %f\n\
Radius: %f\n\
Shape: %d\n\
\n",
    index,
    o->origin.x,
    o->origin.y,
    o->radius,
    o->shape);
}
