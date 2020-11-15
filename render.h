#include <SDL2/SDL.h>
#include "globals.h"
#include "effects.h"
#include "particle.h"
#include "projectile.h"
#include "polygon.h"
#include "baseobject.h"

extern SDL_Window* Window;
extern SDL_Renderer* Renderer;
extern SDL_Renderer* drawTarget;

void initRender();
void setRenderColor(SDL_Renderer* renderer_, uint8_t RGBA[4]);
void renderParticles(SDL_Renderer* renderer);
void renderPolygon(int index, SDL_Renderer* renderer_);
void renderPolygons(SDL_Renderer* renderer);
void doRender(SDL_Renderer* renderer);
