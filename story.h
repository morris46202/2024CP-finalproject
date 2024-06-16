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
    char event;
    char* attribute;
    char operation;
    int value;
    int jump_to;
} sline;

typedef struct option{
    char *text;
    int text_len;
    char *filepath;
    int jump;
} Option;

typedef struct game_data{
    int para;
    int backpack[10];
    int love[5];
} GameData;

typedef enum item{
    ITEM_CARD = 0,
    ITEM_TICKET = 1,
    ITEM_BIKE = 2,
    ITEM_TOWEL = 3,
    ITEM_MIDTERM = 4,
    ITEM_FINAL = 5,
    ITEM_SPECIAL = 6
} Item;

typedef enum love{
    LOVE_HOWARD = 0,
    LOVE_JCUP = 1,
    LOVE_SUKI = 2,
    LOVE_TIKILI = 3,
    LOVE_SHINRAY = 4
} Love;

enum {
    SCENE = 1,
    DIALOGUE = 2,
    CHOICE = 3,
    EVENT = 4,
    END = 5,
    PARA = 6,
    CONDITION = 7
};

char *readline(FILE *fp);

sline *parse_line(char buff[], int len);

void mod_data(GameData *data, sline *line);

GameData *load_game(char filename[]);

void save_game(GameData *data, char filename[]);

char *get_scene(sline *line);

char *get_speaker(sline *line, char *speaker);

char *get_dialogue(sline *line, int *len);

Option *get_choice(sline *line);

void jump(FILE *fp, int para);

void free_sline(sline *line);