#include "physics.h"

void calcPlayerPhysics()
{
    if (inputCommands[UP])
        Player->velocity = add2Vector2(Player->velocity, Player->moveVector);

    // if (inputCommands[DOWN])
        // Nothing

    if (inputCommands[LEFT])
        Player->angle -= turnSpeed;

    if (inputCommands[RIGHT])
        Player->angle += turnSpeed;

    Player->moveVector = moveVector2(zero, Player->angle, acceleration);

    // Cap velocity
    float excessVelocitySquared = pow(Player->velocity.x, 2) + pow(Player->velocity.y, 2) - maxVelocitySquared;
    if (excessVelocitySquared > 0)
    {
        float excessVelocity = sqrt(excessVelocitySquared);
        struct Vector2 cancelVector = newVector2(-excessVelocity, getVector2Angle(Player->velocity));
        Player->velocity = add2Vector2(Player->velocity, cancelVector);
    }
}

void calcParticlePhysics()
{
    for (int i = 0; i < maxParticles; i++)
    {
        struct Particle* p = &(ParticleArray[i]);
        p->origin = add2Vector2(p->origin, p->velocity);
    }
}

void calcProjectilePhysics()
{
    for (int i = 0; i < projectileCount; i++)
    {
        struct Projectile* e = &(ProjectileArray[i]);

        if (e->delta < e->range)
        {
            e->origin = add2Vector2(e->origin, e->velocity);
            e->delta += e->speed;
        }
    }
}

void calcBaseObjectPhysics()
{
    for (int i = 0; i < baseObjectCount; i++)
    {
        struct BaseObject* object = &(BaseObjectArray[i]);

        object->origin = add2Vector2(object->origin, object->velocity);
        object->angle += object->angVelocity;

        if (object->origin.x < 0)                   object->origin.x = screenWidth;
        else if (object->origin.x >= screenWidth)   object->origin.x = 0;

        if (object->origin.y < 0)                   object->origin.y = screenHeight;
        else if (object->origin.y >= screenHeight)  object->origin.y = 0;

        if (object->angle < 0)                      object->angle += 360;
        else if (object->angle >= 360)              object->angle -= 360;
    }
}

void doPhysics()
{
    calcPlayerPhysics(Player);
    calcBaseObjectPhysics();
    calcProjectilePhysics();
    calcParticlePhysics();
}
