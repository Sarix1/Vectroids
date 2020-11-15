#include "polygon.h"

int numPolygons;
struct Polygon* PolygonArray;

int initPolygonArray()
{
    numPolygons = 0;
    PolygonArray = calloc(maxPolygons, sizeof(struct Polygon));

    if (PolygonArray == NULL)
    {
        printf("calloc() failed for PolygonArray\n");

        return 1;
    }

    return 0;
}

int makePolygon(struct Vec2 origin_, float angle_, float angVelocity_,
                int numVectors_, int vectors_, int parent_, uint8_t color_[])
{
    if (numPolygons < maxPolygons)
    {
        struct Polygon* newPolygon = &(PolygonArray[numPolygons++]);
        *newPolygon = (struct Polygon)
        {
            .origin         = origin_,
            .angle          = angle_,
            .angVelocity    = angVelocity_,
            .numVectors     = numVectors_,
            .parent         = parent_,
            .vectors        = vectors_
        };

        memcpy(newPolygon->color, color_, 4);

        return numPolygons-1;
    }
    else
    {
        printf("maxPolygons exceeded\n");

        return -1;
    }
}

void printPolygon(int index)
{
    struct Polygon* p = &(PolygonArray[index]);

    printf("\
Polygon: %d\n\
Origin: %f, %f\n\
Vectors: ",
    index,
    p->origin.x,
    p->origin.y);

    for (int i = 0; i < p->numVectors; i++)
        printf("%d ", p->vectors+i);

    printf("\n\Parent: %d\n\n", p->parent);
}
