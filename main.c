#include "sdl_func.h"

int main(int argc, char** argv)
{
    SDL_Window     *window;
    SDL_Renderer   *renderer;
    SDL_Surface    *screen;
    SDL_Event       ev;
    TTF_Font       *iansui = TTF_OpenFont("font/sans.ttf", 24);

    SDL_Color       white = {255, 255, 255};
    SDL_Color       black = {0, 0, 0};

    SDL_Texture    *test1;
    SDL_Texture    *test2;

    init_sdl(&window, &renderer);

    test1 = load_bmp("image/maldives.bmp", renderer);
    test2 = load_png("image/pop.png", renderer);

    int x = 0, y = 0;

    while (1) {
        SDL_PollEvent(&ev);
        if (ev.type == SDL_QUIT) {
            break;
        } // break the loop

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        renderTexture(test1, renderer, 0, 0, 900, 600);
        renderTexture(test2, renderer, x, y, 100, 100);
        // renderTexture(text1, renderer, 0, 0, 100, 100);
        
        SDL_RenderPresent(renderer);
    } // window loop



    SDL_DestroyTexture(test1);
    SDL_DestroyTexture(test2);
    // SDL_DestroyTexture(text1);
    SDL_FreeSurface(screen);
    TTF_CloseFont(iansui);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}