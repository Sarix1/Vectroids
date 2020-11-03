#include "globals.h"
#include "vector2.h"
#include "baseobject.h"

void initObjectMemory();
void initGameObjects();
struct BaseObject* spawnShip(struct Vector2 location, uint8_t color[]);
struct BaseObject* spawnAsteroid(struct Vector2 location, float scale, uint8_t color[]);
void destroyAsteroid(struct BaseObject* asteroid);
void spawnBullet(struct Vector2 origin_, struct Vector2 moveVector_, float angle_, float offset_, float velocity_, float range_, float damage_);
void playerShoot();
