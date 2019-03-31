
#include "Window_and_Renderer.h"

SDL_Window * make_window(char * name)
{
    struct SDL_Window *window = NULL;
    window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, 0);
    if (!window) {
        printf("\nERROR: SDL window failed--\n%s\n", SDL_GetError());
    }
    return window;
}

SDL_Renderer * make_renderer(SDL_Window ** window)
{
    Uint32 render_flags;
    SDL_Renderer *renderer = NULL;
    render_flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE;

    renderer = SDL_CreateRenderer(*window, -1, render_flags);

    if (!renderer) {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_Quit();
    }
    return renderer;
}

