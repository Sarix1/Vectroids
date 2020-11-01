#include <SDL2/SDL.h>
#include "globals.h"
#include "effects.h"
#include "particle.h"
#include "polygon.h"

SDL_Window* Window;
SDL_Renderer* Renderer;
SDL_Renderer* drawTarget;

void initRender();
void drawPolygon(struct Polygon* polygon, SDL_Renderer* renderer);
void renderParticles(SDL_Renderer* renderer);
void renderPolygons(SDL_Renderer* renderer);
void doRender(SDL_Renderer* renderer);