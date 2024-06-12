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
    TTF_Init();
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw_sdl_err("Could not init the SDL: %s");
    }

    SDL_CreateWindowAndRenderer(
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE,
        window, renderer
    );
}

SDL_Texture *load_bmp(char *filepath, SDL_Renderer *renderer){
    SDL_Surface *surface = SDL_LoadBMP(filepath);
    if (surface == NULL) {
        throw_sdl_err("Could not load image: %s");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture *load_png(char *filepath, SDL_Renderer *renderer){
    SDL_Surface *surface = IMG_Load(filepath);
    if (surface == NULL) {
        throw_sdl_err("Could not load image: %s");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// SDL_Texture *load_text(char *text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer){
//     SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
//     if (surface == NULL) {
//         throw_sdl_err("Could not render text: %s");
//     }

//     SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
//     SDL_FreeSurface(surface);
//     return texture;
// }

void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y, int w, int h){
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;
  SDL_RenderCopy(renderer, tex, NULL, &dst);
}