#include "vector2.h"

#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "my_math.h"

int numVec2;
struct Vec2* Vec2Array;
const struct Vec2 zero = {0,0};
const struct Vec2 world = zero;
const struct Vec2 center = {screenWidth/2, screenHeight/2};

int initVec2Array()
{
    numVec2 = 0;
    Vec2Array = calloc(maxVec2, sizeof(struct Vec2));

    if (Vec2Array == NULL)
    {
        printf("calloc() failed for Vec2Array\n");

        return 1;
    }

    return 0;
}

struct Vec2* makeVec2(float x, float y)
{
    if (numVec2 < maxVec2)
    {
        Vec2Array[numVec2] = (struct Vec2){.x = x, .y = y};
        return &(Vec2Array[numVec2++]);
    }
    else
    {
        printf("maxVec2 exceeded\n");
        return NULL;
    }
}

void copyVec2(int source, int destination, int count)
{
    for (int i = 0; i < count; i++)
        Vec2Array[destination+i] = Vec2Array[source+i];
}

void killVec2(int index, int killCount)
{
    copyVec2(numVec2-killCount, index, killCount);
    numVec2 -= killCount;
}

struct Vec2 add2Vec2(struct Vec2 a, struct Vec2 b)
{
    return (struct Vec2){a.x+b.x, a.y+b.y};
}

struct Vec2 subtractVec2(struct Vec2 a, struct Vec2 b)
{
    return (struct Vec2){a.x-b.x, a.y-b.y};
}

struct Vec2 add3Vec2(struct Vec2 a, struct Vec2 b, struct Vec2 c)
{
    return (struct Vec2){a.x+b.x+c.x, a.y+b.y+c.y};
}

struct Vec2 scaleVec2(struct Vec2 v, float scale)
{
    return (struct Vec2){v.x*scale, v.y*scale};
}

struct Vec2 rotateVec2(const struct Vec2 v, float angle)
{
    struct Vec2 rotatedVector = v;
    angle = degToRad(angle);
    rotatedVector.x = v.x*cos(angle) - v.y*sin(angle);
    rotatedVector.y = v.x*sin(angle) + v.y*cos(angle);

    return rotatedVector;
}

struct Vec2 moveVec2(struct Vec2 v, float angle, float magnitude)
{
    angle = degToRad(angle);
    v.x += magnitude*cos(angle);
    v.y += magnitude*sin(angle);

    return v;
}

struct Vec2 randomVec2(float min, float max)
{
    struct Vec2 v = {randomFloat(min, max), 0};
    v = rotateVec2(v, randomFloat(0, 360));

    return v;
}

struct Vec2 randomVec2Box(float x, float y)
{
    struct Vec2 v;
    v.x = randomFloat(0, x);
    v.y = randomFloat(0, y);

    return v;
}

struct Vec2 newVec2(float length, float angle)
{
    return rotateVec2((struct Vec2){length, 0}, angle);
}

float getVec2Angle(struct Vec2 v)
{
    return radToDeg(atan2(v.y, v.x));
}

float getVec2Length(struct Vec2 v)
{
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

float getVec2Distance(struct Vec2 v1, struct Vec2 v2)
{
    struct Vec2 v = subtractVec2(v1, v2);

    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}
