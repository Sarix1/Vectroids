#include <SDL2/SDL.h>
#include "physics.h"
#include "render.h"
#include "templates.h"

int main(int argc, char *argv[])
{
    initRender();
    initObjectMemory();
    initGameObjects();

    int running = 0;
    while (running)
    {
        running = doEvents(Window);
        doPhysics(Player);
        doRender(Renderer);
        SDL_Delay(10);
    }

    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();

    return 0;
}
