#include "vector2.h"
#include "baseobject.h"

#define asteroidMinVel      0.1
#define asteroidMaxVel      1.5
#define asteroidMaxAngVel   5.0
#define asteroidMinScale    10.0
#define asteroidMaxScale    50.0

void initObjectMemory();
void initGameObjects();
struct BaseObject* spawnShip(struct Vector2 location, uint8_t color[]);
struct BaseObject* spawnAsteroid(struct Vector2 location, float scale, uint8_t color[]);
