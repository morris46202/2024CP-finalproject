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

    *fp = fopen("story.txt", "r");
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
        // printf("load image %s failed\n", filepath);
        // throw_sdl_err("Could not load image: %s");
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

void display_data(GameData *data, TTF_Font *Sans, SDL_Color white, SDL_Renderer *renderer){
    int love_count = 0;
    int item_count = 0;
    SDL_Texture *love_texture;
    
    char love_text[32] = {0};
    sprintf(love_text, "女號千: %d", data -> love[love_count]);
    SDL_Rect love_rect = {900, 100 + love_count * 50, strlen(love_text) * 10, 25};
    love_texture = load_text(love_text, Sans, white, renderer);
    renderTexture(love_texture, renderer, love_rect.x, love_rect.y, love_rect.w, love_rect.h);
    love_count++;

    char love_text_2[32] = {0};
    sprintf(love_text_2, "Jcup: %d", data -> love[love_count]);
    SDL_Rect love_rect_2 = {900, 100 + love_count * 50, strlen(love_text_2) * 10, 25};
    love_texture = load_text(love_text_2, Sans, white, renderer);
    renderTexture(love_texture, renderer, love_rect_2.x, love_rect_2.y, love_rect_2.w, love_rect_2.h);
    love_count++;

    char love_text_3[32] = {0};
    sprintf(love_text_3, "洪suk: %d", data -> love[love_count]);
    SDL_Rect love_rect_3 = {900, 100 + love_count * 50, strlen(love_text_3) * 10, 25};
    love_texture = load_text(love_text_3, Sans, white, renderer);
    renderTexture(love_texture, renderer, love_rect_3.x, love_rect_3.y, love_rect_3.w, love_rect_3.h);
    love_count++;

    char love_text_4[32] = {0};
    sprintf(love_text_4, "Tikili: %d", data -> love[love_count]);
    SDL_Rect love_rect_4 = {900, 100 + love_count * 50, strlen(love_text_4) * 10, 25};
    love_texture = load_text(love_text_4, Sans, white, renderer);
    renderTexture(love_texture, renderer, love_rect_4.x, love_rect_4.y, love_rect_4.w, love_rect_4.h);
    love_count++;
    
    char love_text_5[32] = {0};
    sprintf(love_text_5, "林欣芮: %d", data -> love[love_count]);
    SDL_Rect love_rect_5 = {900, 100 + love_count * 50, strlen(love_text_5) * 10, 25};
    love_texture = load_text(love_text_5, Sans, white, renderer);
    renderTexture(love_texture, renderer, love_rect_5.x, love_rect_5.y, love_rect_5.w, love_rect_5.h);
    love_count++;
    
    return;
    // item_count = love_count
    // for(int i = 0; i < 7; i++){

    // }
}

void display_data_graph(GameData *data, TTF_Font *Sans, SDL_Color white, SDL_Renderer *renderer){
    int love_count = 0;
    int item_count = 0;
    
    for(int i = 0; i < 5; i++){
        SDL_Rect love_rect = {900, 10 + i * 90, 70, 70};
        SDL_Rect text_rect = {1000, 10 + i * 95, 50, 50};
        SDL_Texture *love_texture;
        SDL_Texture *text_texture;
        char path[128] = {"image/head/"};
        char text[32] = {0};
        switch(i){
            case LOVE_HOWARD:
                strcat(path, "howard.png");
                break;
            case LOVE_JCUP:
                strcat(path, "jcup.png");
                break;
            case LOVE_SUKI:
                strcat(path, "suki.png");
                break;
            case LOVE_TIKILI:
                strcat(path, "tikili.png");
                break;
            case LOVE_SHINRAY:
                strcat(path, "shinray.png");
                break;
            default:
                break;
        }

        sprintf(text, "%d", data -> love[i]);
        love_texture = load_png(path, renderer);
        text_texture = load_text(text, Sans, white, renderer);
        text_rect.w = strlen(text) * 25;
        
        renderTexture(love_texture, renderer, love_rect.x, love_rect.y, love_rect.w, love_rect.h);
        renderTexture(text_texture, renderer, text_rect.x, text_rect.y, text_rect.w, text_rect.h);
    
        SDL_DestroyTexture(love_texture);
        SDL_DestroyTexture(text_texture);
    }
}

void display_item(GameData *data, TTF_Font *Sans, SDL_Color white, SDL_Renderer *renderer){
    int item_count = 0;
    for(int i = 0; i < 7; i++){
        if(data -> backpack[i] != 0){
            char item_text[32] = {0};
            switch(i){
                case ITEM_CARD:
                    sprintf(item_text, "Card: %d", data -> backpack[i]);
                    break;
                case ITEM_TICKET:
                    sprintf(item_text, "Ticket: %d", data -> backpack[i]);
                    break;
                case ITEM_BIKE:
                    sprintf(item_text, "Bike: %d", data -> backpack[i]);
                    break;
                case ITEM_TOWEL:
                    sprintf(item_text, "Towel: %d", data -> backpack[i]);
                    break;
                case ITEM_MIDTERM:
                    sprintf(item_text, "Midterm: %d", data -> backpack[i]);
                    break;
                case ITEM_FINAL:
                    sprintf(item_text, "Final: %d", data -> backpack[i]);
                    break;
                case ITEM_SPECIAL:
                    sprintf(item_text, "Special: %d", data -> backpack[i]);
                    break;
                default:
                    break;
            }
            SDL_Rect item_rect = {900, 500 + item_count * 50, strlen(item_text) * 10, 25};
            SDL_Texture *item_texture = load_text(item_text, Sans, white, renderer);
            renderTexture(item_texture, renderer, item_rect.x, item_rect.y, item_rect.w, item_rect.h);
            item_count++;
        }
    }
    return;
}

void display_item_hve(GameData *data, TTF_Font *Sans, SDL_Color white, SDL_Renderer *renderer){
    int item_count = 0;
    int prev_x = 10;
    for(int i = 0; i < 7; i++){
        if(data -> backpack[i] != 0){
            char item_text[32] = {0};
            switch(i){
                case ITEM_CARD:
                    sprintf(item_text, "Card");
                    break;
                case ITEM_TICKET:
                    sprintf(item_text, "Ticket");
                    break;
                case ITEM_BIKE:
                    sprintf(item_text, "Bike");
                    break;
                case ITEM_TOWEL:
                    sprintf(item_text, "Towel");
                    break;
                case ITEM_MIDTERM:
                    sprintf(item_text, "Midterm");
                    break;
                case ITEM_FINAL:
                    sprintf(item_text, "Final");
                    break;
                case ITEM_SPECIAL:
                    sprintf(item_text, "Special");
                    break;
                default:
                    break;
            }
            SDL_Rect item_rect = {30 + prev_x, 800, strlen(item_text) * 15, 30};
            // printf("item_rect.x: %d\n", item_rect.x);s
            prev_x += strlen(item_text) * 15 + 20;
            SDL_Texture *item_texture = load_text(item_text, Sans, white, renderer);
            renderTexture(item_texture, renderer, item_rect.x, item_rect.y, item_rect.w, item_rect.h);
            item_count++;
        }
    }
    return;

}

void draw_exit_button(TTF_Font *Sans, SDL_Color white, SDL_Renderer *renderer, SDL_Rect exit_rect){
    SDL_Texture *exit_texture = load_text("Exit", Sans, white, renderer);
    renderTexture(exit_texture, renderer, exit_rect.x, exit_rect.y, exit_rect.w, exit_rect.h);
}

void show_stats(GameData *data){
    // printf("女號千: %d\n", data -> love[0]);
    // printf("Jcup: %d\n", data -> love[1]);
    // printf("洪suk: %d\n", data -> love[2]);
    // printf("Tikili: %d\n", data -> love[3]);
    // printf("林欣芮: %d\n", data -> love[4]);
    printf("total: %d\n", data -> total);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y, int w, int h){
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;
  SDL_RenderCopy(renderer, tex, NULL, &dst);
}
