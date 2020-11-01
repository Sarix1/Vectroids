#include "effects.h"

void spawnFlame(struct Vector2 origin, struct Vector2 moveVector, float scale, float randomness, unsigned life)
{
    moveVector = scaleVector2(moveVector, scale);
    struct Vector2 particleVelocity = add2Vector2(moveVector, randomVector2(0, randomness));
    makeParticle(origin, particleVelocity, RGBA_YELLOW, RGBA_RED, life);
}

void spawnExplosion(struct Vector2 origin, struct Vector2 moveVector, unsigned magnitude)
{
    struct Vector2 particleVelocity;

    for (int i = 0; i < magnitude; i++)
    {
        particleVelocity = add2Vector2(moveVector, randomVector2(magnitude/100.0, 0));
        makeParticle(origin, particleVelocity, RGBA_YELLOW, RGBA_RED, rand() % magnitude);
    }
}

void generateExhaust()
{
    if (inputCommands[UP])
    {
        if (!inputCommands[RIGHT] || (inputCommands[LEFT] && inputCommands[RIGHT]))
        {
            spawnFlame(add2Vector2(Player->origin,
                                   rotateVector2(&(struct Vector2){exhaustLongitudinal, exhaustLateral}, Player->angle)),
                       add2Vector2(scaleVector2(Player->moveVector, -exhaustVelocity/exhaustVelocityModifier),
                                   scaleVector2(Player->velocity, exhaustInheritedVelocity)),
                       1, exhaustDiffusion, exhaustLife);
        }

        if (!inputCommands[LEFT] || (inputCommands[LEFT] && inputCommands[RIGHT]))
        {
            spawnFlame(add2Vector2(Player->origin,
                                   rotateVector2(&(struct Vector2){exhaustLongitudinal, -exhaustLateral}, Player->angle)),
                       add2Vector2(scaleVector2(Player->moveVector, -exhaustVelocity/exhaustVelocityModifier),
                                   scaleVector2(Player->velocity, exhaustInheritedVelocity)),
                       1, exhaustDiffusion, exhaustLife);
        }
    }
}
