#include "vector2.h"
#include "globals.h"

void spawnFlame(struct Vector2 origin, struct Vector2 moveVector, float scale, float randomness, unsigned life);
void spawnExplosion(struct Vector2 origin, struct Vector2 moveVector, unsigned magnitude);
void generateExhaust();
