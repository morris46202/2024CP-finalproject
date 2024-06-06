all:
	gcc sdl_func.c main.c `sdl2-config --cflags --libs` -o main

