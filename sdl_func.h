#include <SDL2/SDL.h>

#pragma once

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int throw_sdl_err(const char* fmt);

void init_sdl();