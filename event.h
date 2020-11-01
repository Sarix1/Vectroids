#ifndef EVENT_H
#define EVENT_H

#include <string.h>
#include <SDL2/SDL_events.h>
#include "SDL2/SDL_render.h"

enum inputCommandEnum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NUM_COMMANDS
};

uint8_t inputCommands[NUM_COMMANDS] = {0,0,0,0};

int doEvents(SDL_Window* window);

#endif
