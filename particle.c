#include "particle.h"

struct Particle* makeParticle(struct Vector2 origin_, struct Vector2 velocity_, uint8_t color1_[], uint8_t color2_[], unsigned life_)
{
    if (particleCount >= maxParticles)
        particleCount = 0;

    struct Particle* newParticle = &(ParticleArray[particleCount]);
    *newParticle = (struct Particle){.origin    = origin_,
                                     .velocity  = velocity_,
                                     .life      = life_,
                                     .lifeLeft  = life_};

    memcpy(newParticle->color1, color1_, 4 * sizeof(uint8_t));
    memcpy(newParticle->color2, color2_, 4 * sizeof(uint8_t));

    return &(ParticleArray[particleCount++]);
}
