#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include "render.h"

enum inputCommandEnum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NUM_COMMANDS
};

extern SDL_Event Event;
extern uint8_t inputCommands[NUM_COMMANDS];

int doEvents(SDL_Window* window);

#endif
