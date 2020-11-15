#ifndef PARTICLE_H
#define PARTICLE_H

#include "globals.h"
#include "vector2.h"

struct Particle
{
    struct Vec2 origin;
    struct Vec2 velocity;
    struct Vec2 velChange;
    uint8_t color1[4];
    uint8_t color2[4];
    int lifeTime;
    int lifeLeft;
};

extern int numParticles;
extern struct Particle* ParticleArray;

int initParticleArray();
int makeParticle(struct Vec2 origin_, struct Vec2 velocity_, struct Vec2 velChange_, uint8_t color1_[], uint8_t color2_[], int lifeTime_);
void killParticle(int index);

#endif
