#pragma once 
#include <stdint.h>


void read_story(char* filename);
int32_t find_scene(char* line, char* scene);
int32_t find_dialogue(char* line, char* speaker, char* dialogue);
int32_t find_choice(char* line, char* choice, int32_t* jump_to);
int32_t find_event(char* line, char* event, char* attribute, char* operation, int32_t* value);












