#include "globals.h"
#include "vector2.h"
#include "baseobject.h"

extern int numAsteroids;
extern int asteroidObjects;
extern struct BaseObject* Player;

void initObjectMemory();
void initGameObjects();
int spawnShip(struct Vec2 location, uint8_t color[]);
int spawnAsteroid(struct Vec2 location, float scale, uint8_t color[]);
void spawnAsteroids(int c);
void splitAsteroid(int index);
void spawnBullet(struct Vec2 origin_, struct Vec2 moveVector_, float angle_, float offset_, float velocity_, float range_, float damage_);
void playerShoot();
