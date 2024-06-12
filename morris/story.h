#pragma once 
#include <stdint.h>

typedef struct _morris_return {
    int32_t success; // 1 for success, 0 for fail
    int32_t kind; // 1 for scene, 2 for dialogue, 3 for choice, 4 for event
    char* scene;
    char* speaker;
    char* dialogue;
    char* choice;
    char* event;
    char* attribute;
    char* operation;
    int32_t value;
    int32_t jump_to;
} mo_return;

enum {
    SCENE = 1,
    DIALOGUE = 2,
    CHOICE = 3,
    EVENT = 4
};

void easy_read_story(char* filename);
mo_return *easy_find_scene(char* line);
mo_return *easy_find_dialogue(char* line);
//mo_return *easy_find_special(char* line);
mo_return *init();

void hard_read_story(char* filename);
mo_return *hard_find_scene(char* line, char* scene);
mo_return *hard_find_dialogue(char* line, char* speaker, char* dialogue);
mo_return *hard_find_choice(char* line, char* choice, int32_t* jump_to);
mo_return *hard_find_event(char* line, char* event, char* attribute, char* operation, int32_t* value);












