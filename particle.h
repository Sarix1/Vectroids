#ifndef PARTICLE_H
#define PARTICLE_H

#include "globals.h"
#include "vector2.h"

struct Particle
{
    struct Vector2 origin;
    struct Vector2 velocity;
    uint8_t color1[4];
    uint8_t color2[4];
    unsigned life;
    unsigned lifeLeft;
};

extern struct Particle* ParticleArray;

struct Particle* makeParticle(struct Vector2 origin_, struct Vector2 velocity_, uint8_t color1_[], uint8_t color2_[], unsigned life_);

#endif
