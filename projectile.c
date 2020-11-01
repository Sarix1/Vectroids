#include "projectile.h"

struct Projectile* makeProjectile(struct Vector2 origin_, float speed_, float angle_, unsigned range_, int damage_, struct Polygon* shape_)
{
    if (projectileCount >= maxProjectiles)
        projectileCount = 0;

    struct Projectile* newProjectile = &(ProjectileArray[projectileCount]);
    *newProjectile = (struct Projectile){.origin    = origin_,
                                         .speed     = speed_,
                                         .angle     = angle_,
                                         .velocity  = newVector2(speed_, angle_),
                                         .range     = range_,
                                         .delta     = 0,
                                         .damage    = damage_,
                                         .shape     = shape_};

    return &(ProjectileArray[projectileCount++]);
}
