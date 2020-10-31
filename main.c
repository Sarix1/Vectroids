#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define degToRad(degrees) ((degrees) * M_PI / 180.0)
#define radToDeg(radians) ((radians) * 180.0 / M_PI)

// Graphics constants
SDL_Renderer* drawTarget;
const int screenWidth = 640, screenHeight = 480;

// Physics and controls variables
enum inputDirEnum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    MAX_DIRS
};

uint8_t inputCommands[MAX_DIRS] = {0,0,0,0};
#define turnSpeed           2.0
#define acceleration        0.03
#define maxVelocity         5.0
#define maxVelocitySquared  maxVelocity * maxVelocity

// Random color
void randomColor(uint8_t color[])
{
    for (int i = 0; i < 4; i++)
        color[i] = rand() % 255;
}

// Vector2
#define maxVector2 1000
struct Vector2* Vector2Array;
int vector2Count = 0;

struct Vector2
{
    float x, y;
};

struct Vector2* makeVector2(float x, float y)
{
    if (vector2Count < maxVector2)
    {
        Vector2Array[vector2Count] = (struct Vector2){.x = x, .y = y};

        return &(Vector2Array[vector2Count++]);
    }

    else
    {
        printf("maxVector2 exceeded");

        return NULL;
    }
}

struct Vector2 add2Vector2(struct Vector2 a, struct Vector2 b)
{
    return (struct Vector2){a.x+b.x, a.y+b.y};
}

struct Vector2 scaleVector2(struct Vector2 v, float scale)
{
    return (struct Vector2){v.x*scale, v.y*scale};
}

struct Vector2 add3Vector2(struct Vector2 a, struct Vector2 b, struct Vector2 c)
{
    return (struct Vector2){a.x+b.x+c.x, a.y+b.y+c.y};
}

struct Vector2 rotateVector2(const struct Vector2* v, float angle)
{
    struct Vector2 rotatedVector = *v;
    angle = degToRad(angle);
    rotatedVector.x = v->x*cos(angle) - v->y*sin(angle);
    rotatedVector.y = v->x*sin(angle) + v->y*cos(angle);

    return rotatedVector;
}

struct Vector2 moveVector2(struct Vector2 v, float angle, float magnitude)
{
    angle = degToRad(angle);
    v.x += magnitude*cos(angle);
    v.y += magnitude*sin(angle);

    return v;
}

struct Vector2 newVector2(float length, float angle)
{
    return rotateVector2(&(struct Vector2){length, 0}, angle);
}


float randomFloat(float min, float max)
{
    return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

struct Vector2 randomVector2(float min, float max)
{
    struct Vector2 v = {randomFloat(min, max), 0};
    v = rotateVector2(&v, randomFloat(0, 360));

    return v;
}

struct Vector2 randomVector2Box(float x, float y)
{
    struct Vector2 v;
    v.x = randomFloat(0, x);
    v.y = randomFloat(0, y);

    return v;
}

void changeVelocity(struct Vector2* velocity, struct Vector2 vector)
{
    *velocity = add2Vector2(*velocity, vector);
}

// Important points
struct Vector2 zero = {0,0};
struct Vector2 world = {0,0};
struct Vector2 center = {screenWidth/2, screenHeight/2};

// Particle
#define maxParticles 1000
struct Particle* ParticleArray;
int particleCount = 0;

struct Particle
{
    struct Vector2 origin;
    struct Vector2 velocity;
    uint8_t color1[4];
    uint8_t color2[4];
    unsigned life;
    unsigned lifeLeft;
};

struct Particle* makeParticle(struct Vector2 origin_, struct Vector2 velocity_, uint8_t color1_[], uint8_t color2_[], unsigned life_)
{
    if (particleCount >= maxParticles)
        particleCount = 0;

    struct Particle* newParticle = &(ParticleArray[particleCount]);
    *newParticle = (struct Particle){.origin    = origin_,
                                     .velocity  = velocity_,
                                     .life      = life_,
                                     .lifeLeft  = life_};

    memcpy(newParticle->color1, color1_, 4 * sizeof(uint8_t));
    memcpy(newParticle->color2, color2_, 4 * sizeof(uint8_t));

    return &(ParticleArray[particleCount++]);
}

// Projectile
#define maxProjectiles 1000
struct Projectile* ProjectileArray;
int projectileCount = 0;

struct Projectile
{
    struct Vector2 origin;
    struct Vector2 velocity;
    float speed;
    float angle;
    unsigned range;
    unsigned delta;
    int damage;
    struct Polygon* shape;
};

struct Projectile* makeProjectile(struct Vector2 origin_, float speed_, float angle_, unsigned range_, int damage_, struct Polygon* shape_)
{
    if (projectileCount >= maxProjectiles)
        projectileCount = 0;

    struct Projectile* newProjectile = &(ProjectileArray[projectileCount]);
    *newProjectile = (struct Projectile){.origin    = origin_,
                                         .speed     = speed_,
                                         .angle     = angle_,
                                         .velocity  = newVector2(speed_, angle_),
                                         .range     = range_,
                                         .delta     = 0,
                                         .damage    = damage_,
                                         .shape     = shape_};

    return &(ProjectileArray[projectileCount++]);
}

// Polygon
#define maxPolygons 100
struct Polygon* PolygonArray;
int polygonCount = 0;

struct Polygon
{
    struct Vector2 origin;
    float angle;
    float angVelocity;

    struct Vector2* parentOrigin;
    float* parentAngle;

    unsigned numPoints;
    struct Vector2** points;

    uint8_t color[4];
};

struct Polygon* makePolygon(struct Vector2 origin_, float angle_, float angVelocity_,
                            struct Vector2* parentOrigin_, float* parentAngle_,
                            unsigned numPoints_, struct Vector2* points_, uint8_t color_[])
{
    if (polygonCount < maxPolygons)
    {
        struct Polygon* newPolygon = &(PolygonArray[polygonCount]);
        *newPolygon = (struct Polygon){.origin          = origin_,
                                       .angle           = angle_,
                                       .angVelocity     = angVelocity_,
                                       .parentOrigin    = parentOrigin_,
                                       .parentAngle     = parentAngle_,
                                       .numPoints       = numPoints_};

        newPolygon->points = malloc(sizeof(struct Vector2*) * numPoints_);
        memcpy(newPolygon->color, color_, 4 * sizeof(uint8_t));

        for (int i = 0; i < numPoints_; i++)
            newPolygon->points[i] = &(points_[i]);

        return &(PolygonArray[polygonCount++]);
    }

    else
    {
        printf("maxPolygons exceeded");

        return NULL;
    }
}

// BaseObject
#define maxBaseObjects 100
struct BaseObject* BaseObjectArray;
int baseObjectCount = 0;

struct BaseObject
{
    struct Vector2 origin;
    struct Vector2 velocity;
    struct Vector2 moveVector;
    float angle;
    float angVelocity;
    struct Polygon* shape;
};

struct BaseObject* makeBaseObject(struct Vector2 origin_, struct Vector2 velocity_,
                                  float angle_, float angVelocity_, struct Polygon* shape_)
{
    if (baseObjectCount < maxBaseObjects)
    {
        struct BaseObject* newBaseObject = &(BaseObjectArray[baseObjectCount]);
        *newBaseObject = (struct BaseObject){.origin        = origin_,
                                             .velocity      = velocity_,
                                             .angle         = angle_,
                                             .angVelocity   = angVelocity_,
                                             .shape         = shape_};

        return &(BaseObjectArray[baseObjectCount++]);
    }

    else
    {
        printf("maxBaseObjects exceeded");

        return NULL;
    }
}

// Important BaseObjects globals
struct BaseObject* Player;

void drawPolygon(struct Polygon* polygon, SDL_Renderer* renderer)
{
    int i;

    // Rotate the points
    struct Vector2* rotatedPoints = malloc(sizeof(struct Vector2) * polygon->numPoints);

    for (i = 0; i < polygon->numPoints; i++)
        rotatedPoints[i] = rotateVector2(polygon->points[i], polygon->angle + *(polygon->parentAngle));

    // Set the color
    SDL_SetRenderDrawColor(renderer, polygon->color[0], polygon->color[1], polygon->color[2], polygon->color[3]);

    // Draw a line between each point
    for (i = 0; i < polygon->numPoints-1; i++)
    {
        SDL_RenderDrawLine(renderer,
            (polygon->parentOrigin->x + polygon->origin.x + rotatedPoints[i].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedPoints[i].y),
            (polygon->parentOrigin->x + polygon->origin.x + rotatedPoints[i+1].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedPoints[i+1].y) );
    }

    if (polygon->numPoints > 2)
    {
        SDL_RenderDrawLine(renderer,
            (polygon->parentOrigin->x + polygon->origin.x + rotatedPoints[i].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedPoints[i].y),
            (polygon->parentOrigin->x + polygon->origin.x + rotatedPoints[0].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedPoints[0].y) );
    }

    free(rotatedPoints);
}

struct BaseObject* spawnShip(struct Vector2 location, uint8_t color[])
{
    struct Vector2* shipPoints =
    makeVector2(12,0);
    makeVector2(-8,7);
    makeVector2(-4,0);
    makeVector2(-8,-7);
    struct Polygon* shipPolygon = makePolygon(zero, 0, 0, NULL, NULL, 4, shipPoints, color);
    struct BaseObject* shipObject = makeBaseObject(location, zero, 0, 0, shipPolygon);
    shipPolygon->parentOrigin = &(shipObject->origin);
    shipPolygon->parentAngle = &(shipObject->angle);

    return shipObject;
}

struct BaseObject* spawnAsteroid(struct Vector2 location, float scale, uint8_t color[])
{
    #define asteroidMinVel 0.1
    #define asteroidMaxVel 1.5
    #define asteroidMaxAngVel 5.0
    struct Vector2* asteroidVectors =
    makeVector2(15*scale, 15*scale);
    makeVector2(15*scale, -15*scale);
    makeVector2(-15*scale, -15*scale);
    makeVector2(-15*scale, 15*scale);
    float randomAngVel = randomFloat(-asteroidMaxAngVel, asteroidMaxAngVel);
    struct Polygon* asteroidPolygon = makePolygon(zero, 0, randomAngVel, NULL, NULL, 4, asteroidVectors, color);
    struct BaseObject* asteroidObject = makeBaseObject(location, randomVector2(asteroidMinVel, asteroidMaxVel), 0, 0, asteroidPolygon);
    asteroidPolygon->parentOrigin = &(asteroidObject->origin);
    asteroidPolygon->parentAngle = &(asteroidObject->angle);

    return asteroidObject;
}

int doEvents(SDL_Window* window)
{
    SDL_Event event;
    int done = 0;

    // Check for events
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_WINDOWEVENT_CLOSE:
            {
                if (window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
            break;

            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        done = 1;
                        break;
                }
            }
            break;

            case SDL_QUIT:
            {
                done = 1;
                break;
            }
        }
    }

    // Process user input
    const Uint8* state = SDL_GetKeyboardState(NULL);
    memset(inputCommands, 0, sizeof(int) * MAX_DIRS);
    if (state[SDL_SCANCODE_UP])     inputCommands[UP] = 1;
    if (state[SDL_SCANCODE_DOWN])   inputCommands[DOWN] = 1;
    if (state[SDL_SCANCODE_LEFT])   inputCommands[LEFT] = 1;
    if (state[SDL_SCANCODE_RIGHT])  inputCommands[RIGHT] = 1;

    return done;
}

void spawnFlame(struct Vector2 origin, struct Vector2 moveVector, float scale, float random, unsigned life)
{
    moveVector = scaleVector2(moveVector, scale);
    struct Vector2 particleVelocity = add2Vector2(moveVector, randomVector2(0, random));
    #define RGBA_RED     (uint8_t[]){255,0,0,0}
    #define RGBA_YELLOW  (uint8_t[]){255,255,0,0}
    makeParticle(origin, particleVelocity, RGBA_YELLOW, RGBA_RED, life);
}

void spawnExplosion(struct Vector2 origin, struct Vector2 moveVector, unsigned magnitude)
{
    struct Vector2 particleVelocity;

    for (int i = 0; i < magnitude; i++)
    {
        particleVelocity = add2Vector2(moveVector, randomVector2(magnitude/100.0, 0));
        makeParticle(origin, particleVelocity, RGBA_YELLOW, RGBA_RED, rand() % magnitude);
    }
}

float getVector2Angle(struct Vector2 v)
{
    return radToDeg(atan2(v.y, v.x));
}

float getVector2Length(struct Vector2 v)
{
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

void calcPlayerPhysics(struct BaseObject* player_)
{
    if (inputCommands[UP])
        changeVelocity(&(player_->velocity), player_->moveVector);

    // if (inputCommands[DOWN])
        // Nothing

    if (inputCommands[LEFT])
        player_->angle -= turnSpeed;

    if (inputCommands[RIGHT])
        player_->angle += turnSpeed;

    player_->moveVector = moveVector2(zero, player_->angle, acceleration);

    // Limit player velocity to max
    float excessVelocitySquared = pow(player_->velocity.x, 2) + pow(player_->velocity.y, 2) - maxVelocitySquared;
    if (excessVelocitySquared > 0)
    {
        float excessVelocity = sqrt(excessVelocitySquared);
        struct Vector2 cancelVector = newVector2(-excessVelocity, getVector2Angle(player_->velocity));
        player_->velocity = add2Vector2(player_->velocity, cancelVector);
    }
}

void calcBaseObjectPhysics()
{
    for (int i = 0; i < baseObjectCount; i++)
    {
        struct BaseObject* object = &(BaseObjectArray[i]);

        object->origin = add2Vector2(object->origin, object->velocity);
        object->angle += object->angVelocity;

        if (object->origin.x < 0)                   object->origin.x = screenWidth;
        else if (object->origin.x >= screenWidth)   object->origin.x = 0;

        if (object->origin.y < 0)                   object->origin.y = screenHeight;
        else if (object->origin.y >= screenHeight)  object->origin.y = 0;

        if (object->angle < 0)                      object->angle += 360;
        else if (object->angle >= 360)              object->angle -= 360;
    }
}

void calcProjectilePhysics()
{
    for (int i = 0; i < projectileCount; i++)
    {
        struct Projectile* e = &(ProjectileArray[i]);

        if (e->delta < e->range)
        {
            e->origin = add2Vector2(e->origin, e->velocity);
            e->delta += e->speed;
        }
    }
}

void doPhysics(struct BaseObject* player_)
{
    calcPlayerPhysics(player_);
    calcBaseObjectPhysics();
    calcProjectilePhysics();
}

void generateExhaust()
{
    if (inputCommands[UP])
    {
        #define exhaustVelocity             100
        #define exhaustVelocityModifier     5
        #define exhaustInheritedVelocity    0.9
        #define exhaustDiffusion            0.5
        #define exhaustLife                 50
        #define exhaustLongitudinal        -10
        #define exhaustLateral              4

        if (!inputCommands[RIGHT] || (inputCommands[LEFT] && inputCommands[RIGHT]))
        {
            spawnFlame(add2Vector2(Player->origin, rotateVector2(&(struct Vector2){exhaustLongitudinal, exhaustLateral}, Player->angle)),
                       add2Vector2(scaleVector2(Player->moveVector, -exhaustVelocity/exhaustVelocityModifier), scaleVector2(Player->velocity, exhaustInheritedVelocity)),
                       1, exhaustDiffusion, exhaustLife);
        }

        if (!inputCommands[LEFT] || (inputCommands[LEFT] && inputCommands[RIGHT]))
        {
            spawnFlame(add2Vector2(Player->origin, rotateVector2(&(struct Vector2){exhaustLongitudinal, -exhaustLateral}, Player->angle)),
                       add2Vector2(scaleVector2(Player->moveVector, -exhaustVelocity/exhaustVelocityModifier), scaleVector2(Player->velocity, exhaustInheritedVelocity)),
                       1, exhaustDiffusion, exhaustLife);
        }
    }
}

void renderParticles(SDL_Renderer* renderer)
{
    for (int i = 0; i < maxParticles; i++)
    {
        struct Particle* p = &(ParticleArray[i]);

        if (p->lifeLeft > 0)
        {
            p->lifeLeft -= 1;
            p->origin = add2Vector2(p->origin, p->velocity);

            uint8_t newColor[3];

            for (int c = 0; c < 3; c++)
                newColor[c] = (p->lifeLeft * p->color1[c] + (p->life - p->lifeLeft) * p->color2[c]) / p->life;

            SDL_SetRenderDrawColor(renderer, newColor[0], newColor[1], newColor[2], 0);
            SDL_RenderDrawPoint(renderer, (int)(p->origin.x), (int)(p->origin.y));
        }
    }
}

void renderPolygons(SDL_Renderer* renderer)
{
    for (int i = 0; i < polygonCount; i++)
    {
        PolygonArray[i].angle += PolygonArray[i].angVelocity;
        drawPolygon(&(PolygonArray[i]), renderer);
    }
}

void doRender(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    generateExhaust();

    renderParticles(renderer);
    renderPolygons(renderer);

    SDL_RenderPresent(renderer);
}

void initObjectMemory()
{
    Vector2Array    = malloc(sizeof(struct Vector2) * maxVector2);
    ParticleArray   = malloc(sizeof(struct Particle) * maxParticles);
    PolygonArray    = malloc(sizeof(struct Polygon) * maxPolygons);
    BaseObjectArray = malloc(sizeof(struct BaseObject) * maxBaseObjects);
}

void initGameObjects()
{
    Player = spawnShip(center, (uint8_t[]){0,255,0,0});

    #define asteroidMinScale 0.5
    #define asteroidMaxScale 1.8
    for (int i = 0; i < 10; i++)
        spawnAsteroid(randomVector2Box(screenWidth, screenHeight), randomFloat(asteroidMinScale, asteroidMaxScale), (uint8_t[]){255,255,255,0});
}

int main(int argc, char *argv[])
{
    // Initialize graphics
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Init(SDL_INIT_VIDEO);
    Window = SDL_CreateWindow("Vectroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, 0);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize game objects
    initObjectMemory();
    initGameObjects();

    // Game loop
    int done = 0;
    while (!done)
    {
        done = doEvents(Window);
        doPhysics(Player);
        doRender(Renderer);
        SDL_Delay(10);
    }

    // Quit
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();

    return 0;
}
