#include "vector2.h"

#define exhaustVelocity             100
#define exhaustVelocityModifier     5
#define exhaustInheritedVelocity    0.9
#define exhaustDiffusion            0.5
#define exhaustLife                 50
#define exhaustLongitudinal        -10
#define exhaustLateral              4

void spawnFlame(struct Vector2 origin, struct Vector2 moveVector, float scale, float randomness, unsigned life);
void spawnExplosion(struct Vector2 origin, struct Vector2 moveVector, unsigned magnitude);
void generateExhaust();
