#include "polygon.h"

struct Polygon* makePolygon(struct Vector2 origin_, float angle_, float angVelocity_,
                            struct Vector2* parentOrigin_, float* parentAngle_,
                            unsigned numPoints_, struct Vector2* points_, uint8_t color_[])
{
    if (polygonCount < maxPolygons)
    {
        struct Polygon* newPolygon = &(PolygonArray[polygonCount]);
        *newPolygon = (struct Polygon){.origin          = origin_,
                                       .angle           = angle_,
                                       .angVelocity     = angVelocity_,
                                       .parentOrigin    = parentOrigin_,
                                       .parentAngle     = parentAngle_,
                                       .numPoints       = numPoints_};

        newPolygon->points = malloc(sizeof(struct Vector2*) * numPoints_);
        memcpy(newPolygon->color, color_, 4 * sizeof(uint8_t));

        for (int i = 0; i < numPoints_; i++)
            newPolygon->points[i] = &(points_[i]);

        return &(PolygonArray[polygonCount++]);
    }

    else
    {
        printf("maxPolygons exceeded");

        return NULL;
    }
}
