#include "particle.h"

#include <string.h>

int numParticles;
struct Particle* ParticleArray;

int initParticleArray()
{
    numParticles = 0;
    ParticleArray = calloc(maxParticles, sizeof(struct Particle));

    if (ParticleArray == NULL)
    {
        printf("calloc() failed for ParticleArray\n");
        return 1;
    }

    return 0;
}

int makeParticle(struct Vec2 origin_, struct Vec2 velocity_, struct Vec2 velChange_, uint8_t color1_[], uint8_t color2_[], int lifeTime_)
{
    int i;

    if (numParticles >= maxParticles)
        i = 0;
    else
        i = numParticles++;

    ParticleArray[i] = (struct Particle)
    {
        .origin    = origin_,
        .velocity  = velocity_,
        .velChange = velChange_,
        .lifeTime  = lifeTime_,
        .lifeLeft  = lifeTime_
    };

    memcpy(ParticleArray[i].color1, color1_, 4);
    memcpy(ParticleArray[i].color2, color2_, 4);

    return i;
}

void killParticle(int index)
{
    if (index < numParticles)
    {
        ParticleArray[index] = ParticleArray[numParticles-1];
        numParticles--;
    }
}
