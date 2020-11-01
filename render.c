#include "render.h"

void initRender()
{
    SDL_Init(SDL_INIT_VIDEO);
    Window = SDL_CreateWindow("Vectroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, 0);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
}

void drawPolygon(struct Polygon* polygon, SDL_Renderer* renderer)
{
    int i;
    struct Vector2* rotatedVectors = malloc(sizeof(struct Vector2) * polygon->numPoints);

    for (i = 0; i < polygon->numPoints; i++)
        rotatedVectors[i] = rotateVector2(polygon->points[i], polygon->angle + *(polygon->parentAngle));

    SDL_SetRenderDrawColor(renderer, polygon->color[0], polygon->color[1], polygon->color[2], polygon->color[3]);

    for (i = 0; i < polygon->numPoints-1; i++)
    {
        SDL_RenderDrawLine(renderer,
            (polygon->parentOrigin->x + polygon->origin.x + rotatedVectors[i].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedVectors[i].y),
            (polygon->parentOrigin->x + polygon->origin.x + rotatedVectors[i+1].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedVectors[i+1].y) );
    }

    if (polygon->numPoints > 2)
    {
        SDL_RenderDrawLine(renderer,
            (polygon->parentOrigin->x + polygon->origin.x + rotatedVectors[i].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedVectors[i].y),
            (polygon->parentOrigin->x + polygon->origin.x + rotatedVectors[0].x),
            (polygon->parentOrigin->y + polygon->origin.y + rotatedVectors[0].y) );
    }

    free(rotatedVectors);
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
