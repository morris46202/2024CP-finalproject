#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma once

typedef struct sline{
    int success; // 1 for success, 0 for fail
    int kind; // 1 for scene, 2 for dialogue, 3 for choice, 4 for event
    int para;
    char* scene;
    char* speaker;
    char* dialogue;
    char* choice;
    char* event;
    char* attribute;
    char* operation;
    int value;
    int jump_to;
} sline;

enum {
    SCENE = 1,
    DIALOGUE = 2,
    CHOICE = 3,
    EVENT = 4
};

char *readline(FILE *fp);

sline *parse_line(char buff[], int len);

char *get_scene(sline *line);

char *get_speaker(sline *line);

char *get_dialogue(sline *line, int *len);

void free_sline(sline *line);