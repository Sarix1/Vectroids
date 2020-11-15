#include "templates.h"

#include <stdlib.h>
#include "globals.h"
#include "my_math.h"
#include "vector2.h"
#include "particle.h"
#include "projectile.h"
#include "polygon.h"
#include "baseobject.h"
#include "effects.h"

int numAsteroids;
int asteroidObjects;
struct BaseObject* Player;

void initObjectMemory()
{
    initVec2Array();
    initParticleArray();
    initProjectileArray();
    initPolygonArray();
    initBaseObjectArray();
}

void initGameObjects()
{
    Player = &(BaseObjectArray[spawnShip(shipStartPos, shipColor)]);

    numAsteroids = 0;
    asteroidObjects = numBaseObjects;
    spawnAsteroids(asteroidCount);
}

int spawnShip(struct Vec2 location, uint8_t color[])
{
    int lastNumVec2 = numVec2;

    makeVec2(12*shipScale, 0*shipScale);
    makeVec2(-8*shipScale, 7*shipScale);
    makeVec2(-4*shipScale, 0*shipScale);
    makeVec2(-8*shipScale, -7*shipScale);

    int shipPolygon                     = makePolygon(zero, 0, 0, 4, lastNumVec2, -1, color);
    int shipBaseObject                  = makeBaseObject(location, zero, 0, 0, shipRadius, shipPolygon, shipHealth);
    PolygonArray[shipPolygon].parent    = shipBaseObject;

    numVec2 = lastNumVec2 + vec2ChunkSize;

    return shipBaseObject;
}

int spawnAsteroid(struct Vec2 location_, float scale_, uint8_t color_[])
{
    int lastNumVec2 = numVec2;
    int numVectors = asteroidMinVectors + (rand() % (asteroidMaxVectors - asteroidMinVectors));

    if (numVectors > vec2ChunkSize)
        numVectors = vec2ChunkSize;

    for (int i = 0; i < numVectors; i++)
    {
        struct Vec2* newVector = makeVec2(scale_ * randomFloat(1-asteroidIrregular, 1+asteroidIrregular), 0);
        *newVector = rotateVec2(*newVector, i* (360.0/numVectors) * randomFloat(1-asteroidRandAngles, 1+asteroidRandAngles));
    }

    float randomAngVel      = randomFloat(-asteroidMaxAngVel, asteroidMaxAngVel);
    int asteroidPolygon     = makePolygon(zero, 0, randomAngVel, numVectors, lastNumVec2, -1, color_);
    int asteroidBaseObject  =
    makeBaseObject
    (
        location_,                                          // origin
        randomVec2(asteroidMinVel, asteroidMaxVel),         // velocity
        0, 0,                                               // angle, angVel
        asteroidRadius * scale_,                            // radius
        asteroidPolygon,                                    // shape id
        (int)(asteroidHealth * (scale_/asteroidMaxScale))   // health
    );

    PolygonArray[asteroidPolygon].parent = asteroidBaseObject;
    numVec2 = lastNumVec2 + vec2ChunkSize;
    numAsteroids++;

    return asteroidBaseObject;
}

void spawnAsteroids(int c)
{
    struct Vec2 randomPos;

    for (int i = 0; i < c; i++)
    {
        do {randomPos = randomVec2Box(screenWidth, screenHeight);}
        while (getVec2Distance(randomPos, Player->origin) < minClearance);

        spawnAsteroid(randomPos, randomFloat(asteroidMinScale, asteroidMaxScale), asteroidColor);
    }
}

void killAsteroid(int index)
{
    struct BaseObject* asteroid = &(BaseObjectArray[index]);
    spawnExplosion(asteroid->origin, asteroid->velocity, explosionMagnitude * asteroid->radius);
    numAsteroids--;

    killBaseObject(index);

    if (numAsteroids == 0)
        spawnAsteroids(asteroidCount);
}

void splitAsteroid(int index)
{
    struct BaseObject* asteroid = &(BaseObjectArray[index]);
    spawnAsteroid(asteroid->origin, asteroid->radius/2, asteroidColor);
    spawnAsteroid(asteroid->origin, asteroid->radius/2, asteroidColor);
}

void hitAsteroid(int index, int damage)
{
    struct BaseObject* asteroid = &(BaseObjectArray[index]);
    asteroid->health -= damage;
    addToColor(PolygonArray[asteroid->shape].color, &RGBA_DAMAGE);

    if (asteroid->health <= 0)
    {
        if (asteroid->radius > asteroidMinRadius)
            splitAsteroid(index);

        killAsteroid(index);
    }
}

void spawnBullet(struct Vec2 origin_, struct Vec2 moveVector_, float angle_, float offset_, float velocity_, float range_, float damage_)
{
    struct Vec2 offset = rotateVec2((struct Vec2){offset_, 0}, angle_);
    makeProjectile(add2Vec2(origin_, offset), moveVector_, velocity_, angle_, range_, damage_, -1);
}

void playerShoot()
{
    spawnBullet(Player->origin, Player->velocity, Player->angle, bulletOffset, bulletVelocity, bulletRange, bulletDamage);
}
