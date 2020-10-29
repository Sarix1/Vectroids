#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

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

uint8_t inputDir[MAX_DIRS] = {0,0,0,0};
float turnSpeed = 2, accSpeed = 0.01, maxVel = 2;

// Random color
uint8_t* randomColor()
{
    uint8_t color[4];
    for (int i = 0; i < 4; i++)
        color[i] = rand() % 255;

    return color;
}

// Point
#define maxPoints 1000
struct Point* PointArray;
int pointCount = 0;

struct Point
{
    float x, y;
};

struct Point* makePoint(float x, float y)
{
    if (pointCount < maxPoints)
    {
        PointArray[pointCount] = (struct Point){.x = x, .y = y};

        return &(PointArray[pointCount++]);
    }

    else
    {
        printf("maxPoints exceeded");

        return NULL;
    }
}

struct Point addPoints(struct Point a, struct Point b)
{
    return (struct Point){a.x+b.x, a.y+b.y};
}

struct Point rotateVector(const struct Point* p, float angle)
{
    struct Point rotatedPoint = *p;
    angle = degToRad(angle);
    rotatedPoint.x = p->x*cos(angle) - p->y*sin(angle);
    rotatedPoint.y = p->x*sin(angle) + p->y*cos(angle);

    return rotatedPoint;
}

struct Point movePoint(struct Point p, float angle, float magnitude)
{
    angle = degToRad(angle);
    p.x += magnitude*cos(angle);
    p.y += magnitude*sin(angle);

    return p;
}

float randomFloat(float min, float max)
{
    return ((float)rand()/(float)(RAND_MAX)) * (min+max) - min;
}

struct Point randomPoint()
{
    struct Point p;
    p.x = randomFloat(0, screenWidth);
    p.y = randomFloat(0, screenHeight);

    return p;
}

struct Point randomVector(float min, float max)
{
    struct Point p = {0, randomFloat(min, max)};
    p = rotateVector(&p, randomFloat(0, 360));

    return p;
}

void changeVelocity(struct Point* velocity, struct Point vector)
{
    *velocity = addPoints(*velocity, vector);
}

// Important points
struct Point zero = {0,0};
struct Point world = {0,0};
struct Point center = {screenWidth/2, screenHeight/2};

// Particle
#define maxParticles 1000
struct Particle* ParticleArray;
int particleCount = 0;

struct Particle
{
    struct Point origin;
    struct Point velocity;
    uint8_t color1[4];
    uint8_t color2[4];
    unsigned life;
    unsigned lifeLeft;
};

struct Point* makeParticle(struct Point origin_, struct Point velocity_, uint8_t color1_[], uint8_t color2_[], unsigned life_)
{
    if (particleCount >= maxParticles)
        particleCount = 0;

    struct Particle* newParticle = &(ParticleArray[particleCount]);
    *newParticle = (struct Particle){.origin = origin_,
                                   .velocity = velocity_,
                                   .life = life_,
                                   .lifeLeft = life_};

    memcpy(newParticle->color1, color1_, 4 * sizeof(uint8_t));
    memcpy(newParticle->color2, color2_, 4 * sizeof(uint8_t));

    return &(ParticleArray[particleCount++]);
}

// Polygon
#define maxPolygons 100
struct Polygon* PolygonArray;
int polygonCount = 0;

struct Polygon
{
    struct Point origin;
    float angle;
    float angVelocity;

    struct Point* parentOrigin;
    float* parentAngle;

    unsigned num_points;
    struct Point** points;

    uint8_t color[4];
};

struct Polygon* makePolygon(struct Point origin_, float angle_, float angVelocity_,
                            struct Point* parentOrigin_, float* parentAngle_,
                            unsigned num_points_, struct Point* points_, uint8_t color_[])
{
    if (polygonCount < maxPolygons)
    {
        struct Polygon* newPolygon = &(PolygonArray[polygonCount]);
        *newPolygon = (struct Polygon){.origin = origin_,
                                       .angle = angle_,
                                       .angVelocity = angVelocity_,
                                       .parentOrigin = parentOrigin_,
                                       .parentAngle = parentAngle_,
                                       .num_points = num_points_};

        newPolygon->points = malloc(sizeof(struct Point*) * num_points_);
        memcpy(newPolygon->color, color_, 4 * sizeof(uint8_t));

        for (int i = 0; i < num_points_; i++)
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
    struct Point origin;
    struct Point velocity;
    float angle;
    float angVelocity;
    struct Polygon* shape;
};

struct BaseObject* makeBaseObject(struct Point origin_, struct Point velocity_,
                                  float angle_, float angVelocity_, struct Polygon* shape_)
{
    if (baseObjectCount < maxBaseObjects)
    {
        struct BaseObject* newBaseObject = &(BaseObjectArray[baseObjectCount]);
        *newBaseObject = (struct BaseObject){.origin = origin_,
                                             .velocity = velocity_,
                                             .angle = angle_,
                                             .angVelocity = angVelocity_,
                                             .shape = shape_};

        return &(BaseObjectArray[baseObjectCount++]);
    }

    else
    {
        printf("maxBaseObjects exceeded");

        return NULL;
    }
}

void drawPolygon(struct Polygon* polygon, SDL_Renderer* renderer)
{
    int i;

    // Rotate the points
    struct Point* rotatedPoints = malloc(sizeof(struct Point) * polygon->num_points);

    for (i = 0; i < polygon->num_points; i++)
        rotatedPoints[i] = rotateVector(polygon->points[i], polygon->angle + *(polygon->parentAngle));

    // Set the color
    SDL_SetRenderDrawColor(renderer, polygon->color[0], polygon->color[1], polygon->color[2], polygon->color[3]);

    // Draw a line between each point
    for (i = 0; i < polygon->num_points-1; i++)
    {
        SDL_RenderDrawLine(renderer,
            (polygon->parentOrigin->x + polygon->origin.x + rotatedPoints[i].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedPoints[i].y),
            (polygon->parentOrigin->x + polygon->origin.x + rotatedPoints[i+1].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedPoints[i+1].y) );
    }

    SDL_RenderDrawLine(renderer,
        (polygon->parentOrigin->x + polygon->origin.x + rotatedPoints[i].x),
        (polygon->parentOrigin->y + polygon->origin.y + rotatedPoints[i].y),
        (polygon->parentOrigin->x + polygon->origin.x + rotatedPoints[0].x),
        (polygon->parentOrigin->y + polygon->origin.y + rotatedPoints[0].y) );

    free(rotatedPoints);
}

struct BaseObject* spawnShip(struct Point location, uint8_t color[])
{
    struct Point* shipPoints =
    makePoint(12,0);
    makePoint(-8,7);
    makePoint(-4,0);
    makePoint(-8,-7);
    struct Polygon* shipPolygon = makePolygon(zero, 0, 0, NULL, NULL, 4, shipPoints, color);
    struct BaseObject* shipObject = makeBaseObject(location, zero, 0, 0, shipPolygon);
    shipPolygon->parentOrigin = &(shipObject->origin);
    shipPolygon->parentAngle = &(shipObject->angle);

    return shipObject;
}

struct BaseObject* spawnAsteroid(struct Point location, float scale, uint8_t color[])
{
    struct Point* asteroidPoints =
    makePoint(15*scale, 15*scale);
    makePoint(15*scale, -15*scale);
    makePoint(-15*scale, -15*scale);
    makePoint(-15*scale, 15*scale);
    struct Polygon* asteroidPolygon = makePolygon(zero, 0, randomFloat(-maxVel, maxVel), NULL, NULL, 4, asteroidPoints, color);
    struct BaseObject* asteroidObject = makeBaseObject(location, randomVector(0.1, 1.5), 0, 0, asteroidPolygon);
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
    memset(inputDir, 0, sizeof(int) * MAX_DIRS);
    if (state[SDL_SCANCODE_UP])     inputDir[UP] = 1;
    if (state[SDL_SCANCODE_DOWN])   inputDir[DOWN] = 1;
    if (state[SDL_SCANCODE_LEFT])   inputDir[LEFT] = 1;
    if (state[SDL_SCANCODE_RIGHT])  inputDir[RIGHT] = 1;

    return done;
}

void doPhysics(struct BaseObject* player)
{
    // Only player
    struct Point moveVector = {0, 0};
    moveVector = movePoint(moveVector, player->angle, accSpeed);

    if (inputDir[UP])
    {
        changeVelocity(&(player->velocity), moveVector);

        struct Point particleVelocity = addPoints((struct Point){moveVector.x *= -100, moveVector.y *= -100}, randomVector(0, 0.5));
        particleVelocity = addPoints((struct Point){player->velocity.x/2, player->velocity.y/2}, particleVelocity);
        makeParticle(player->origin, particleVelocity, (uint8_t[]){255,255,0,0}, (uint8_t[]){255,0,0,0}, 50);
    }
    if (inputDir[DOWN])
        changeVelocity(&(player->velocity), (struct Point){moveVector.x *= -1, moveVector.y *= -1});
    if (inputDir[LEFT])
        player->angle -= turnSpeed;
    if (inputDir[RIGHT])
        player->angle += turnSpeed;

    // All objects
    for (int i = 0; i < maxBaseObjects; i++)
    {
        struct BaseObject* object = &(BaseObjectArray[i]);

        object->origin.x += object->velocity.x;
        object->origin.y += object->velocity.y;
        object->angle    += object->angVelocity;

        if (object->origin.x < 0)                   object->origin.x = screenWidth;
        else if (object->origin.x >= screenWidth)   object->origin.x = 0;

        if (object->origin.y < 0)                   object->origin.y = screenHeight;
        else if (object->origin.y >= screenHeight)  object->origin.y = 0;

        if (object->angle < 0)                      object->angle += 360;
        else if (object->angle >= 360)              object->angle -= 360;
    }
}

void doRender(SDL_Renderer* renderer)
{
    int i;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (i = 0; i < maxParticles; i++)
    {
        struct Particle* p = &(ParticleArray[i]);

        if (p->lifeLeft > 0)
        {
            p->lifeLeft -= 1;
            p->origin = addPoints(p->origin, p->velocity);

            uint8_t newColor[3];
            float lifeRatio = p->lifeLeft / p->life;
            float lifeInverse = 1 - lifeRatio;

            for (int c; c < 3; c++)
                newColor[c] = (int)(lifeRatio * p->color1[c] + lifeInverse * p->color2[c]);

            SDL_SetRenderDrawColor(renderer, newColor[0], newColor[1], newColor[2], 0);
            SDL_RenderDrawPoint(renderer, (int)(p->origin.x), (int)(p->origin.y));
        }

    }

    for (i = 0; i < polygonCount; i++)
    {
        PolygonArray[i].angle += PolygonArray[i].angVelocity;
        drawPolygon(&(PolygonArray[i]), renderer);
    }

    SDL_RenderPresent(renderer);
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
    PointArray = malloc(sizeof(struct Point) * maxPoints);
    ParticleArray = malloc(sizeof(struct Particle) * maxParticles);
    PolygonArray = malloc(sizeof(struct Polygon) * maxPolygons);
    BaseObjectArray = malloc(sizeof(struct BaseObject) * maxBaseObjects);

    struct BaseObject* PlayerObject = spawnShip(center, (uint8_t[]){0,255,0,0});

    for (int i = 0; i < 10; i++)
        spawnAsteroid(randomPoint(), randomFloat(0.5, 1.5), (uint8_t[]){255,255,255,0});

    // Game loop
    int done = 0;
    while (!done)
    {
        done = doEvents(Window);
        doPhysics(PlayerObject);
        doRender(Renderer);
        SDL_Delay(10);
    }

    // Quit
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();

    return 0;
}
