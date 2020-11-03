#include "event.h"

#include <string.h>

SDL_Event Event;
uint8_t inputCommands[NUM_COMMANDS] = {0,0,0,0};

int doEvents(SDL_Window* window)
{
    int running = 1;

    // Check for Events
    while (SDL_PollEvent(&Event))
    {
        switch(Event.type)
        {
            case SDL_WINDOWEVENT_CLOSE:
            {
                if (window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    running = 0;
                }
            }
            break;

            case SDL_KEYDOWN:
            {
                switch(Event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                }
            }
            break;

            case SDL_QUIT:
            {
                running = 0;
                break;
            }
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    memset(inputCommands, 0, sizeof(uint8_t) * NUM_COMMANDS);

    if (state[SDL_SCANCODE_UP])     inputCommands[UP]       = 1;
    if (state[SDL_SCANCODE_DOWN])   inputCommands[DOWN]     = 1;
    if (state[SDL_SCANCODE_LEFT])   inputCommands[LEFT]     = 1;
    if (state[SDL_SCANCODE_RIGHT])  inputCommands[RIGHT]    = 1;
    if (state[SDL_SCANCODE_RCTRL])  inputCommands[SHOOT]    = 1;

    return running;
}
