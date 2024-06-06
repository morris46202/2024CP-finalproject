#include "sdl_func.h"

int main(int argc, char** argv)
{
    SDL_Window*     window;
    SDL_Renderer*   renderer;
    SDL_Surface*    surface;
    SDL_Surface*    surface2;
    SDL_Texture*    texture;
    SDL_Event       ev;

    init_sdl(&window, &renderer);

    surface = SDL_LoadBMP("image/maldives.bmp");
    // surface2 = SDL_LoadBMP("image/chrismas_ans.bmp");

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    // texture = SDL_CreateTextureFromSurface(renderer, surface2);

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