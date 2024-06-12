#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#pragma once

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

int throw_sdl_err(const char* fmt);

void init_sdl();

SDL_Texture *load_bmp(char *filepath, SDL_Renderer *renderer);

SDL_Texture *load_png(char *filepath, SDL_Renderer *renderer);

// SDL_Texture *load_text(char *text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer);

void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y, int w, int h);