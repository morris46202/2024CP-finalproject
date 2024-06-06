#include "sdl_func.h"

int throw_sdl_err(const char* fmt){
    SDL_LogError(
        SDL_LOG_CATEGORY_APPLICATION,
        fmt,
        SDL_GetError()
    );
    return 3; // constant error code.
}

void init_sdl(SDL_Window** window, SDL_Renderer** renderer){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw_sdl_err("Could not init the SDL: %s");
    }

    SDL_CreateWindowAndRenderer(
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE,
        window, renderer
    );
}