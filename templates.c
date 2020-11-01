#include "templates.h"

void initObjectMemory()
{
    Vector2Array    = malloc(sizeof(struct Vector2) * maxVector2);
    ParticleArray   = malloc(sizeof(struct Particle) * maxParticles);
    PolygonArray    = malloc(sizeof(struct Polygon) * maxPolygons);
    ProjectileArray = malloc(sizeof(struct Projectile) * maxProjectiles);
    BaseObjectArray = malloc(sizeof(struct BaseObject) * maxBaseObjects);
}

struct BaseObject* spawnShip(struct Vector2 location, uint8_t color[])
{
    struct Vector2* shipPoints =
    makeVector2(12,0);
    makeVector2(-8,7);
    makeVector2(-4,0);
    makeVector2(-8,-7);
    struct Polygon* shipPolygon     = makePolygon(zero, 0, 0, NULL, NULL, 4, shipPoints, color);
    struct BaseObject* shipObject   = makeBaseObject(location, zero, 0, 0, shipPolygon);
    shipPolygon->parentOrigin       = &(shipObject->origin);
    shipPolygon->parentAngle        = &(shipObject->angle);

    return shipObject;
}

struct BaseObject* spawnAsteroid(struct Vector2 location, float scale, uint8_t color[])
{
    struct Vector2* asteroidVectors =
    makeVector2(scale, scale);
    makeVector2(scale, -scale);
    makeVector2(-scale, -scale);
    makeVector2(-scale, scale);
    float randomAngVel                  = randomFloat(-asteroidMaxAngVel, asteroidMaxAngVel);
    struct Polygon* asteroidPolygon     = makePolygon(zero, 0, randomAngVel, NULL, NULL, 4, asteroidVectors, color);
    struct BaseObject* asteroidObject   = makeBaseObject(location, randomVector2(asteroidMinVel, asteroidMaxVel), 0, 0, asteroidPolygon);
    asteroidPolygon->parentOrigin       = &(asteroidObject->origin);
    asteroidPolygon->parentAngle        = &(asteroidObject->angle);

    return asteroidObject;
}

void initGameObjects()
{
    Player = spawnShip(center, RGBA_GREEN);

    for (int i = 0; i < 10; i++)
        spawnAsteroid(randomVector2Box(screenWidth, screenHeight), randomFloat(asteroidMinScale, asteroidMaxScale), RGBA_RED);
}
