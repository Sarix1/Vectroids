#include <SDL2/SDL.h>
#include "templates.h"
#include "event.h"
#include "physics.h"
#include "collision.h"
#include "render.h"

int main(int argc, char *argv[])
{
    initObjectMemory();
    initGameObjects();
    initRender();

    int running = 1;
    while (running)
    {
        running = doEvents(Window);
        doPhysics();
        doCollide();
        doRender(Renderer);
        SDL_Delay(10);
    }

    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();

    return 0;
}
