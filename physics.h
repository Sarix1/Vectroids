#include "globals.h"
#include "event.h"
#include "vector.h"
#include "particle.h"
#include "projectile.h"
#include "baseobject.h"

#define turnSpeed           2.0
#define acceleration        0.03
#define maxVelocity         5.0
#define maxVelocitySquared  maxVelocity * maxVelocity

void calcPlayerPhysics();
void calcParticlePhysics();
void calcProjectilePhysics();
void calcBaseObjectPhysics();
void doPhysics();
