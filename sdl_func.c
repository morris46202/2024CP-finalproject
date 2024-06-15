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

bool initSDL(SDL_Window** window, SDL_Renderer** renderer, FILE **fp, TTF_Font **Sans) {
    TTF_Init();
    // 嘗試初始化 SDL 視頻子系統
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    // 創建視窗
    *window = SDL_CreateWindow("Final project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    // 為視窗創建渲染器
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }
    // 設置渲染器繪製顏色（用於按鈕背景）
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 204); // 80% 透明度的黑色
    
    *Sans = TTF_OpenFont("font/iansui.ttf", 24);
    if(*Sans == NULL){
        throw_sdl_err("Could not load font: %s");
    }

    *fp = fopen("test.txt", "r");
    if(*fp == NULL){
        printf("File not found\n");
        return 1;
    }

    return true;
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

SDL_Texture *load_text(char *text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer){
    if(font == NULL){
        throw_sdl_err("Could not load font: %s");
    }
    int text_width, text_height;
    // uint32_t wrap_length = TTF_SizeUTF8(font, text, &text_width, &text_height);
    // printf("text_width: %d, text_height: %d\n", text_width, text_height);
    // printf("wrap_length: %d\n", wrap_length); 
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    if (surface == NULL) {
        throw_sdl_err("Could not render text: %s");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y, int w, int h){
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;
  SDL_RenderCopy(renderer, tex, NULL, &dst);
}
