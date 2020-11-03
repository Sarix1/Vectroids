#include "templates.h"

#include <stdlib.h>
#include "globals.h"
#include "my_math.h"
#include "particle.h"
#include "polygon.h"
#include "projectile.h"
#include "effects.h"

void initObjectMemory()
{
    Vector2Array    = calloc(maxVector2, sizeof(struct Vector2));
    ParticleArray   = calloc(maxParticles, sizeof(struct Particle));
    PolygonArray    = calloc(maxPolygons, sizeof(struct Polygon));
    ProjectileArray = calloc(maxProjectiles, sizeof(struct Projectile));
    BaseObjectArray = calloc(maxBaseObjects, sizeof(struct BaseObject));
}

void initGameObjects()
{
    Player = spawnShip(shipStartPos, shipColor);

    for (int i = 0; i < asteroidCount; i++)
        spawnAsteroid(randomVector2Box(screenWidth, screenHeight), randomFloat(asteroidMinScale, asteroidMaxScale), asteroidColor);
}

struct BaseObject* spawnShip(struct Vector2 location, uint8_t color[])
{
    struct Vector2* shipPoints =
    makeVector2(12*shipScale, 0*shipScale);
    makeVector2(-8*shipScale, 7*shipScale);
    makeVector2(-4*shipScale, 0*shipScale);
    makeVector2(-8*shipScale, -7*shipScale);
    struct Polygon* shipPolygon     = makePolygon(zero, 0, 0, NULL, NULL, 4, shipPoints, color);
    struct BaseObject* shipObject   = makeBaseObject(location, zero, 0, 0, shipRadius, shipPolygon);
    shipPolygon->parentOrigin       = &(shipObject->origin);
    shipPolygon->parentAngle        = &(shipObject->angle);

    return shipObject;
}

struct BaseObject* spawnAsteroid(struct Vector2 location_, float scale_, uint8_t color_[])
{
    struct Vector2* asteroidVectors =
    makeVector2(scale_, scale_);
    makeVector2(scale_, -scale_);
    makeVector2(-scale_, -scale_);
    makeVector2(-scale_, scale_);
    float randomAngVel                  = randomFloat(-asteroidMaxAngVel, asteroidMaxAngVel);
    struct Polygon* asteroidPolygon     = makePolygon(zero, 0, randomAngVel, NULL, NULL, 4, asteroidVectors, color_);
    struct BaseObject* asteroidObject   = makeBaseObject(location_, randomVector2(asteroidMinVel, asteroidMaxVel), 0, 0, asteroidRadius * scale_, asteroidPolygon);
    asteroidPolygon->parentOrigin       = &(asteroidObject->origin);
    asteroidPolygon->parentAngle        = &(asteroidObject->angle);

    return asteroidObject;
}

void destroyAsteroid(struct BaseObject* asteroid)
{
    spawnExplosion(asteroid->origin, asteroid->velocity, explosionMagnitude * asteroid->radius);
    memcpy(asteroid->shape->color, RGBA_BLACK, 4);

    if (asteroid->radius > asteroidMinRadius)
    {
        spawnAsteroid(asteroid->origin, asteroid->radius/2, asteroidColor);
        spawnAsteroid(asteroid->origin, asteroid->radius/2, asteroidColor);
    }

    // killBaseObject(asteroid);
}

void spawnBullet(struct Vector2 origin_, struct Vector2 moveVector_, float angle_, float offset_, float velocity_, float range_, float damage_)
{
    struct Vector2 offset = rotateVector2((struct Vector2){offset_, 0}, angle_);
    makeProjectile(add2Vector2(origin_, offset), moveVector_, velocity_, angle_, range_, damage_, NULL);
}

void playerShoot()
{
    spawnBullet(Player->origin, Player->velocity, Player->angle, bulletOffset, bulletVelocity, bulletRange, bulletDamage);
}
