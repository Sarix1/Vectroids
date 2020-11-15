#include "projectile.h"

int numProjectiles;
struct Projectile* ProjectileArray;

int initProjectileArray()
{
    numProjectiles = 0;
    ProjectileArray = calloc(maxProjectiles, sizeof(struct Projectile));

    if (ProjectileArray == NULL)
    {
        printf("calloc() failed for ProjectileArray\n");

        return 1;
    }

    return 0;
}

int makeProjectile(struct Vec2 origin_, struct Vec2 moveVector_, float speed_, float angle_, int range_, int damage_, int shape_)
{
    int i;

    if (numProjectiles >= maxProjectiles)
        i = 0;
    else
        i = numProjectiles++;

    ProjectileArray[i] = (struct Projectile)
    {
        .origin    = origin_,
        .speed     = speed_,
        .angle     = angle_,
        .velocity  = add2Vec2(moveVector_, newVec2(speed_, angle_)),
        .range     = range_,
        .delta     = 0,
        .damage    = damage_,
        .shape     = shape_
    };

    return i;
}

void killProjectile(int index)
{
    if (index < numProjectiles)
    {
        ProjectileArray[index].origin = center;
        ProjectileArray[index] = ProjectileArray[numProjectiles-1];
        numProjectiles--;
    }
}

int projectileAlive(int index)
{
    return (ProjectileArray[index].delta < ProjectileArray[index].range) ? 1 : 0;
}
