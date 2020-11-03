#ifndef VECTOR2_H
#define VECTOR2_H

#include "globals.h"

struct Vector2
{
    float x, y;
};

extern int vector2Count;
extern struct Vector2* Vector2Array;
extern const struct Vector2 zero;
extern const struct Vector2 world;
extern const struct Vector2 center;

struct Vector2* makeVector2(float x, float y);
// void killVector2(struct Vector2* target);
struct Vector2 add2Vector2(struct Vector2 a, struct Vector2 b);
struct Vector2 add3Vector2(struct Vector2 a, struct Vector2 b, struct Vector2 c);
struct Vector2 subtractVector2(struct Vector2 v1, struct Vector2 v2);
struct Vector2 scaleVector2(struct Vector2 v, float scale);
struct Vector2 rotateVector2(const struct Vector2 v, float angle);
struct Vector2 moveVector2(struct Vector2 v, float angle, float magnitude);
struct Vector2 randomVector2(float min, float max);
struct Vector2 randomVector2Box(float x, float y);
struct Vector2 newVector2(float length, float angle);
float getVector2Angle(struct Vector2 v);
float getVector2Length(struct Vector2 v);
float getVector2Distance(struct Vector2 v1, struct Vector2 v2);


#endif
