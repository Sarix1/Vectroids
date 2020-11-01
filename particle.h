#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL_types.h>
#include "vector.h"

#define maxParticles 1000

struct Particle
{
    struct Vector2 origin;
    struct Vector2 velocity;
    uint8_t color1[4];
    uint8_t color2[4];
    unsigned life;
    unsigned lifeLeft;
};

int particleCount = 0;
struct Particle* ParticleArray;

struct Particle* makeParticle(struct Vector2 origin_, struct Vector2 velocity_, uint8_t color1_[], uint8_t color2_[], unsigned life_);

#endif
