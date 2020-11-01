#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "vector2.h"
#include "polygon.h"

#define maxProjectiles 1000

struct Projectile
{
    struct Vector2 origin;
    struct Vector2 velocity;
    float speed;
    float angle;
    unsigned range;
    unsigned delta;
    int damage;
    struct Polygon* shape;
};

extern int projectileCount;
extern struct Projectile* ProjectileArray;

struct Projectile* makeProjectile(struct Vector2 origin_, float speed_, float angle_, unsigned range_, int damage_, struct Polygon* shape_);

#endif
