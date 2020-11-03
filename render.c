#include "render.h"

SDL_Window* Window;
SDL_Renderer* Renderer;
SDL_Renderer* drawTarget;

void initRender()
{
    SDL_Init(SDL_INIT_VIDEO);
    Window = SDL_CreateWindow("Vectroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, fullScreen ? SDL_WINDOW_FULLSCREEN : 0);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
}

void renderParticles(SDL_Renderer* renderer)
{
    for (int i = 0; i < maxParticles; i++)
    {
        struct Particle* p = &(ParticleArray[i]);

        if (p->lifeLeft > 0)
        {
            p->lifeLeft -= 1;
            uint8_t newColor[3];

            for (int c = 0; c < 3; c++)
                newColor[c] = (p->lifeLeft * p->color1[c] + (p->life - p->lifeLeft) * p->color2[c]) / p->life;

            SDL_SetRenderDrawColor(renderer, newColor[0], newColor[1], newColor[2], 0);
            SDL_RenderDrawPoint(renderer, (int)(p->origin.x), (int)(p->origin.y));
        }
    }
}

void drawPolygon(struct Polygon* polygon, SDL_Renderer* renderer_)
{
    int i;
    struct Vector2* rotatedVectors = malloc(sizeof(struct Vector2) * polygon->numVectors);

    for (i = 0; i < polygon->numVectors; i++)
        rotatedVectors[i] = rotateVector2(*(polygon->vectors[i]), polygon->angle + *(polygon->parentAngle));

    SDL_SetRenderDrawColor(renderer_, polygon->color[0], polygon->color[1], polygon->color[2], polygon->color[3]);

    for (i = 0; i < polygon->numVectors-1; i++)
    {
        SDL_RenderDrawLine(renderer_,
            (polygon->parentOrigin->x + polygon->origin.x + rotatedVectors[i].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedVectors[i].y),
            (polygon->parentOrigin->x + polygon->origin.x + rotatedVectors[i+1].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedVectors[i+1].y) );
    }

    if (polygon->numVectors > 2)
    {
        SDL_RenderDrawLine(renderer_,
            (polygon->parentOrigin->x + polygon->origin.x + rotatedVectors[i].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedVectors[i].y),
            (polygon->parentOrigin->x + polygon->origin.x + rotatedVectors[0].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedVectors[0].y) );
    }

    free(rotatedVectors);
}

void renderPolygons(SDL_Renderer* renderer_)
{
    for (int i = 0; i < polygonCount; i++)
    {
        PolygonArray[i].angle += PolygonArray[i].angVelocity;
        drawPolygon(&(PolygonArray[i]), renderer_);
    }
}

void renderProjectiles(SDL_Renderer* renderer_)
{
    for (int i = 0; i < maxProjectiles; i++)
    {
        struct Projectile* p = &(ProjectileArray[i]);

        if (p->delta < p->range)
        {
            SDL_SetRenderDrawColor(renderer_, RGBA_YELLOW[0], RGBA_YELLOW[1], RGBA_YELLOW[2], 0);
            SDL_RenderDrawPoint(renderer_, (int)(p->origin.x), (int)(p->origin.y));
        }
    }
}

void doRender(SDL_Renderer* renderer_)
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
    SDL_RenderClear(renderer_);

    generateExhaust();
    renderParticles(renderer_);
    renderProjectiles(renderer_);
    renderPolygons(renderer_);

    SDL_RenderPresent(renderer_);
}
