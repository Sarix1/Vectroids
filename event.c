#include "event.h"

int doEvents(SDL_Window* window)
{
    SDL_Event event;
    int running = 1;

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
                    running = 0;
                }
            }
            break;

            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
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
    memset(inputCommands, 0, sizeof(int) * NUM_COMMANDS);
    if (state[SDL_SCANCODE_UP])     inputCommands[UP] = 1;
    if (state[SDL_SCANCODE_DOWN])   inputCommands[DOWN] = 1;
    if (state[SDL_SCANCODE_LEFT])   inputCommands[LEFT] = 1;
    if (state[SDL_SCANCODE_RIGHT])  inputCommands[RIGHT] = 1;

    return running;
}
