#include "effects.h"

#include <SDL2/SDL_types.h>
#include "globals.h"
#include "my_math.h"
#include "particle.h"
#include "templates.h"
#include "event.h"

void spawnFlame(struct Vec2 origin, struct Vec2 moveVector, float scale, float randomness, int life)
{
    moveVector = scaleVec2(moveVector, scale);
    struct Vec2 particleVelocity = add2Vec2(moveVector, randomVec2(0, randomness));
    makeParticle(origin, particleVelocity, zero, fireColor1, fireColor2, life);
}

void spawnExplosion(struct Vec2 origin, struct Vec2 moveVector, int magnitude)
{
    struct Vec2 particleVelocity;

    for (int i = 0; i < magnitude; i++)
    {
        particleVelocity = add2Vec2(moveVector, randomVec2(magnitude/100.0, 0));
        makeParticle(origin, particleVelocity, zero, fireColor1, fireColor2, rand() % magnitude);
    }
}

void generateExhaust()
{
    if (inputCommands[UP])
    {
        if (!inputCommands[RIGHT] || (inputCommands[LEFT] && inputCommands[RIGHT]))
        {
            spawnFlame(add2Vec2(Player->origin,
                                   rotateVec2((struct Vec2){exhaustLongitudinal, exhaustLateral}, Player->angle)),
                       add2Vec2(scaleVec2(Player->moveVector, -exhaustVelocity/exhaustVelModifier),
                                   scaleVec2(Player->velocity, exhaustInheritedVel)),
                       1, exhaustDiffusion, exhaustLife);
        }

        if (!inputCommands[LEFT] || (inputCommands[LEFT] && inputCommands[RIGHT]))
        {
            spawnFlame(add2Vec2(Player->origin,
                                   rotateVec2((struct Vec2){exhaustLongitudinal, -exhaustLateral}, Player->angle)),
                       add2Vec2(scaleVec2(Player->moveVector, -exhaustVelocity/exhaustVelModifier),
                                   scaleVec2(Player->velocity, exhaustInheritedVel)),
                       1, exhaustDiffusion, exhaustLife);
        }
    }
}

void generateStar()
{
    struct Vec2 randomPos = randomVec2Box(screenWidth, screenHeight);
    struct Vec2 offsetPos = subtractVec2(randomPos, center);
    float velMagnitude = getVec2Length(offsetPos);
    struct Vec2 velocity = newVec2(velMagnitude / screenWidth * starMaxVelChange, getVec2Angle(offsetPos));
    makeParticle(randomPos, zero, velocity, RGBA_BLACK, RGBA_WHITE, 20000/velMagnitude);
}
