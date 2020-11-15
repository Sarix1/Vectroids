#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "globals.h"
#include "vector2.h"
#include "polygon.h"

struct Projectile
{
    struct Vec2 origin;
    struct Vec2 velocity;
    float speed;
    float angle;
    int range;
    int delta;
    int damage;
    int shape; // not implemented yet
};

extern int numProjectiles;
extern struct Projectile* ProjectileArray;

int initProjectileArray();
int makeProjectile(struct Vec2 origin_, struct Vec2 moveVector_, float speed_, float angle_, int range_, int damage_, int shape_);
void killProjectile(int index);
int projectileAlive(int index);

#endif
