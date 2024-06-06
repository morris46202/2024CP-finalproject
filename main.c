#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int throw_sdl_err(const char* fmt)
{
    SDL_LogError(
        SDL_LOG_CATEGORY_APPLICATION,
        fmt,
        SDL_GetError()
    );
    return 3; // constant error code.
}

int main(int argc, char** argv)
{
    SDL_Window*     window;
    SDL_Renderer*   renderer;
    SDL_Surface*    surface;
    SDL_Texture*    texture;
    SDL_Event       ev;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return throw_sdl_err("Could not init the SDL: %s");
    }

    if (SDL_CreateWindowAndRenderer(
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE,
        &window, &renderer
    )) { return throw_sdl_err("Could not create new window and renderer: %s"); }

    surface = SDL_LoadBMP("image/maldives.bmp");
    if (!surface) {
        return throw_sdl_err("Could not load BMP image: %s");
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        return throw_sdl_err("Could not create new texture from surface: %s");
    }

    SDL_FreeSurface(surface); // free a RGB surface (?)

    while (1) {
        SDL_PollEvent(&ev);
        if (ev.type == SDL_QUIT) {
            break;
        } // break the loop

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    } // window loop

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}