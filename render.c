#include "render.h"
#include "particle.h"

SDL_Window* Window;
SDL_Renderer* Renderer;
SDL_Renderer* drawTarget;

void initRender()
{
    SDL_Init(SDL_INIT_VIDEO);
    Window = SDL_CreateWindow("Vectroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, fullScreen ? SDL_WINDOW_FULLSCREEN : 0);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
}

void setRenderColor(SDL_Renderer* renderer_, uint8_t RGBA[4])
{
    SDL_SetRenderDrawColor(renderer_, RGBA[0], RGBA[1], RGBA[2], RGBA[3]);
}

void renderParticles(SDL_Renderer* renderer)
{
    uint8_t newColor[3];
    struct Particle* p;

    for (int i = 0; i < numParticles; i++)
    {
        p = &(ParticleArray[i]);

        if (p->lifeLeft-- > 0)
        {
            p->velocity = add2Vec2(p->velocity, p->velChange);
            p->origin = add2Vec2(p->origin, p->velocity);

            for (int c = 0; c < 3; c++)
                newColor[c] = (p->lifeLeft * p->color1[c] + (p->lifeTime - p->lifeLeft) * p->color2[c]) / p->lifeTime;

            SDL_SetRenderDrawColor(renderer, newColor[0], newColor[1], newColor[2], 0);
            SDL_RenderDrawPoint(renderer, (int)(p->origin.x), (int)(p->origin.y));
        }

        else
        {
            killParticle(i);
        }
    }
}

void renderProjectiles(SDL_Renderer* renderer_)
{
    setRenderColor(renderer_, shotColor);

    for (int i = 0; i < numProjectiles; i++)
        SDL_RenderDrawPoint(renderer_, (int)(ProjectileArray[i].origin.x), (int)(ProjectileArray[i].origin.y));
}

void renderPolygon(int index, SDL_Renderer* renderer_)
{
    int i;
    struct Polygon* polygon     = &(PolygonArray[index]);
    struct BaseObject* parent   = &(BaseObjectArray[polygon->parent]); // replace with physics component later
    struct Vec2* polygonVectors = &(Vec2Array[polygon->vectors]);
    struct Vec2 rotatedVectors[polygon->numVectors];// = malloc(sizeof(struct Vec2) * polygon->numVectors);

    polygon->angle += polygon->angVelocity;

    for (i = 0; i < polygon->numVectors; i++)
        rotatedVectors[i] = rotateVec2(polygonVectors[i], polygon->angle + parent->angle);

    SDL_SetRenderDrawColor(renderer_, polygon->color[0], polygon->color[1], polygon->color[2], polygon->color[3]);

    for (i = 0; i < polygon->numVectors-1; i++)
    {
        SDL_RenderDrawLine(renderer_,
            (parent->origin.x + polygon->origin.x + rotatedVectors[i].x),
            (parent->origin.y + polygon->origin.y + rotatedVectors[i].y),
            (parent->origin.x + polygon->origin.x + rotatedVectors[i+1].x),
            (parent->origin.y + polygon->origin.y + rotatedVectors[i+1].y) );
    }

    if (polygon->numVectors > 2)
    {
        SDL_RenderDrawLine(renderer_,
            (parent->origin.x + polygon->origin.x + rotatedVectors[i].x),
            (parent->origin.y + polygon->origin.y + rotatedVectors[i].y),
            (parent->origin.x + polygon->origin.x + rotatedVectors[0].x),
            (parent->origin.y + polygon->origin.y + rotatedVectors[0].y) );
    }

    free(rotatedVectors);
}

void renderPolygons(SDL_Renderer* renderer_)
{
    for (int i = 0; i < numPolygons; i++)
        renderPolygon(i, renderer_);
}

void doRender(SDL_Renderer* renderer_)
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
    SDL_RenderClear(renderer_);

    generateStar();
    generateExhaust();
    renderParticles(renderer_);
    renderProjectiles(renderer_);
    renderPolygons(renderer_);

    SDL_RenderPresent(renderer_);
}
