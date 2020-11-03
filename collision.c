#include "collision.h"

#include "vector2.h"
#include "projectile.h"
#include "baseobject.h"
#include "templates.h"
#include "effects.h"

void collideBulletsWithAsteroids()
{
    for (int i = 1; i < baseObjectCount; i++)
    {
        for (int j = 0; j < maxProjectiles; j++)
        {
            float distance = getVector2Distance(BaseObjectArray[i].origin, ProjectileArray[j].origin);
            float minDistance = BaseObjectArray[i].radius;
            int bulletAlive = (ProjectileArray[j].delta < ProjectileArray[j].range) ? 1 : 0;

            if (distance < minDistance && bulletAlive)
            {
                ProjectileArray[j].delta = ProjectileArray[j].range; // should be killProjectile(j);
                destroyAsteroid(&(BaseObjectArray[i]));
            }
        }
    }
}

void doCollide()
{
    collideBulletsWithAsteroids();
}
