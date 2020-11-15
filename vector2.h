#ifndef VECTOR2_H
#define VECTOR2_H

#include "globals.h"

struct Vec2
{
    float x, y;
};

extern int numVec2;
extern struct Vec2* Vec2Array;
extern const struct Vec2 zero;
extern const struct Vec2 world;
extern const struct Vec2 center;

int initVec2Array();
struct Vec2* makeVec2(float x, float y);
void copyVec2(int source, int destination, int count);
void killVec2(int index, int killCount);
struct Vec2 add2Vec2(struct Vec2 a, struct Vec2 b);
struct Vec2 add3Vec2(struct Vec2 a, struct Vec2 b, struct Vec2 c);
struct Vec2 subtractVec2(struct Vec2 v1, struct Vec2 v2);
struct Vec2 scaleVec2(struct Vec2 v, float scale);
struct Vec2 rotateVec2(const struct Vec2 v, float angle);
struct Vec2 moveVec2(struct Vec2 v, float angle, float magnitude);
struct Vec2 randomVec2(float min, float max);
struct Vec2 randomVec2Box(float x, float y);
struct Vec2 newVec2(float length, float angle);
float getVec2Angle(struct Vec2 v);
float getVec2Length(struct Vec2 v);
float getVec2Distance(struct Vec2 v1, struct Vec2 v2);

#endif
