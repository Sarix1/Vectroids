#include "physics.h"

#include "globals.h"
#include "event.h"
#include "my_math.h"
#include "vector2.h"
#include "particle.h"
#include "projectile.h"
#include "baseobject.h"
#include "templates.h"

int shootTimer = 0;

void calcPlayerPhysics()
{
    if (inputCommands[UP])
        Player->velocity = add2Vec2(Player->velocity, Player->moveVector);

    // if (inputCommands[DOWN])
        // Nothing

    if (inputCommands[LEFT])
        Player->angle -= turnSpeed;

    if (inputCommands[RIGHT])
        Player->angle += turnSpeed;

    Player->moveVector = moveVec2(zero, Player->angle, acceleration);

    // Cap velocity
    float excessVelocitySquared = pow(Player->velocity.x, 2) + pow(Player->velocity.y, 2) - maxVelSquared;
    if (excessVelocitySquared > 0)
    {
        float excessVelocity = sqrt(excessVelocitySquared);
        struct Vec2 cancelVector = newVec2(-excessVelocity, getVec2Angle(Player->velocity));
        Player->velocity = add2Vec2(Player->velocity, cancelVector);
    }
}

void calcProjectilePhysics()
{
    if (shootTimer > 0)
        shootTimer--;

    if (inputCommands[SHOOT] && !shootTimer)
    {
        shootTimer = shootDelay;
        playerShoot();
    }

    for (int i = 0; i < maxProjectiles; i++)
    {
        struct Projectile* p = &(ProjectileArray[i]);

        if (p->delta < p->range)
        {
            p->origin = add2Vec2(p->origin, p->velocity);
            p->delta += p->speed;
        }
        else
            killProjectile(i);
    }
}

void calcBaseObjectPhysics()
{
    for (int i = 0; i < numBaseObjects; i++)
    {
        struct BaseObject* object = &(BaseObjectArray[i]);

        object->origin = add2Vec2(object->origin, object->velocity);
        object->angle += object->angVelocity;

        if (object->origin.x < -object->radius)
            object->origin.x = screenWidth + object->radius;
        else if (object->origin.x >= (screenWidth + object->radius))
            object->origin.x = -object->radius;

        if (object->origin.y < -object->radius)
            object->origin.y = screenHeight + object->radius;
        else if (object->origin.y >= (screenHeight + object->radius))
            object->origin.y = -object->radius;

        if (object->angle < 0)
            object->angle += 360;
        else if (object->angle >= 360)
            object->angle -= 360;
    }
}

void doPhysics()
{
    calcPlayerPhysics(Player);
    calcBaseObjectPhysics();
    calcProjectilePhysics();
}
