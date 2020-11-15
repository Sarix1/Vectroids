#include "collision.h"

#include "vector2.h"
#include "projectile.h"
#include "baseobject.h"
#include "templates.h"
#include "effects.h"

void collideProjectilesWithAsteroids()
{
    for (int i = asteroidObjects; i < asteroidObjects + numAsteroids; i++)
    {
        for (int j = 0; j < numProjectiles; j++)
        {
            float distance = getVec2Distance(BaseObjectArray[i].origin, ProjectileArray[j].origin);
            float minDistance = BaseObjectArray[i].radius;

            if (distance < minDistance)
            {
                killProjectile(j);
                hitAsteroid(i, ProjectileArray[j].damage);

                continue;
            }
        }
    }
}

void doCollide()
{
    collideProjectilesWithAsteroids();
}
