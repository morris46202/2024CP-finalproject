all:
	gcc sdl_func.c story.c main.c `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o main

