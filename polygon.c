#include "polygon.h"

int polygonCount = 0;
struct Polygon* PolygonArray;

struct Polygon* makePolygon(struct Vector2 origin_, float angle_, float angVelocity_,
                            struct Vector2* parentOrigin_, float* parentAngle_,
                            unsigned numVectors_, struct Vector2* vectors_, uint8_t color_[])
{
    if (polygonCount < maxPolygons)
    {
        struct Polygon* newPolygon = &(PolygonArray[polygonCount]);
        *newPolygon = (struct Polygon){.origin          = origin_,
                                       .angle           = angle_,
                                       .angVelocity     = angVelocity_,
                                       .parentOrigin    = parentOrigin_,
                                       .parentAngle     = parentAngle_,
                                       .numVectors       = numVectors_};

        newPolygon->vectors = malloc(sizeof(struct Vector2*) * numVectors_);
        memcpy(newPolygon->color, color_, 4 * sizeof(uint8_t));

        for (int i = 0; i < numVectors_; i++)
            newPolygon->vectors[i] = &(vectors_[i]);

        return &(PolygonArray[polygonCount++]);
    }

    else
    {
        printf("maxPolygons exceeded\n");

        return NULL;
    }
}
/*
void copyPolygon(struct Polygon* source, struct Polygon* destination)
{
    // caution: this can override the next polygon's vectors if source has more than destination!
    for (int i = 0; i < source->numVectors; i++)
        destination->vectors[i] = source->vectors[i];

    *destination = *source;
}

void killPolygon(struct Polygon* target)
{
    //vector2Count -= target->numVectors;
    copyPolygon(&(PolygonArray[--polygonCount]), target);
}
*/
