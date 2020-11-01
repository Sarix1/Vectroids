#include "vector.h"

struct Vector2* makeVector2(float x, float y)
{
    if (vector2Count < maxVector2)
    {
        Vector2Array[vector2Count] = (struct Vector2){.x = x, .y = y};

        return &(Vector2Array[vector2Count++]);
    }

    else
    {
        printf("maxVector2 exceeded");

        return NULL;
    }
}

struct Vector2 add2Vector2(struct Vector2 a, struct Vector2 b)
{
    return (struct Vector2){a.x+b.x, a.y+b.y};
}

struct Vector2 add3Vector2(struct Vector2 a, struct Vector2 b, struct Vector2 c)
{
    return (struct Vector2){a.x+b.x+c.x, a.y+b.y+c.y};
}

struct Vector2 scaleVector2(struct Vector2 v, float scale)
{
    return (struct Vector2){v.x*scale, v.y*scale};
}

struct Vector2 rotateVector2(const struct Vector2* v, float angle)
{
    struct Vector2 rotatedVector = *v;
    angle = degToRad(angle);
    rotatedVector.x = v->x*cos(angle) - v->y*sin(angle);
    rotatedVector.y = v->x*sin(angle) + v->y*cos(angle);

    return rotatedVector;
}

struct Vector2 moveVector2(struct Vector2 v, float angle, float magnitude)
{
    angle = degToRad(angle);
    v.x += magnitude*cos(angle);
    v.y += magnitude*sin(angle);

    return v;
}

struct Vector2 randomVector2(float min, float max)
{
    struct Vector2 v = {randomFloat(min, max), 0};
    v = rotateVector2(&v, randomFloat(0, 360));

    return v;
}

struct Vector2 randomVector2Box(float x, float y)
{
    struct Vector2 v;
    v.x = randomFloat(0, x);
    v.y = randomFloat(0, y);

    return v;
}

struct Vector2 newVector2(float length, float angle)
{
    return rotateVector2(&(struct Vector2){length, 0}, angle);
}

float getVector2Angle(struct Vector2 v)
{
    return radToDeg(atan2(v.y, v.x));
}

float getVector2Length(struct Vector2 v)
{
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}
