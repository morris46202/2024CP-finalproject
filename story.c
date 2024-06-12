#include "story.h"

char *readline(FILE *fp){
    if(fp == NULL){
        printf("File not found\n");
        return NULL;
    }

    char *buffer = (char *)calloc(1024, sizeof(char));
    fgets(buffer, 1024, fp);

    return buffer;
}

sline *parse_line(char buff[], int len){
    sline *line = (sline *)calloc(1, sizeof(sline));
    switch(buff[0]){
        case '#':
            int para = 0;
            sscanf(buff, "#%d", &para);
            printf("para: %d\n", para);
            break;
        
        case '@':
            line -> kind = SCENE;
            line -> scene = (char *)calloc(len, sizeof(char));
            sscanf(buff, "@%s", line -> scene);
            printf("scene: %s\n", line -> scene);
            break;

        case '-':
            line -> kind = DIALOGUE;
            line -> speaker = (char *)calloc(len, sizeof(char));
            line -> dialogue = (char *)calloc(len, sizeof(char));
            sscanf(buff, "- %[^:]:%[^\n]", line -> speaker, line -> dialogue);
            printf("speaker: %s\n", line -> speaker);
            printf("dialogue: %s\n", line -> dialogue);
            break;

        case '?':
            line -> kind = CHOICE;
            line -> choice = (char *)calloc(len, sizeof(char));
            sscanf(buff, "? %s ~%d~", line -> choice, &(line->jump_to));
            printf("choice: %s jump: %d\n", line -> choice, line -> jump_to);
            break;

        case '!':
            line -> kind = EVENT;
            line -> event = (char *)calloc(len, sizeof(char));
            line -> attribute = (char *)calloc(len, sizeof(char));
            line -> operation = (char *)calloc(len, sizeof(char));
            sscanf(buff, "! %s %s %s %d", line -> event, line -> attribute, line -> operation, &(line -> value));
            printf("event: %s attr: %s oper: %s val: %d\n", line -> event, line -> attribute, line -> operation, line -> value);
            break;
    }
    return line;
}

char *get_scene(sline *line){
    char *ret = (char *)calloc(32, sizeof(char));
    if(strcmp(line -> scene, "sc1") == 0){
        strcpy(ret, "image/scene/sc1.png");
    }else if(strcmp(line -> scene, "sc2") == 0){
        strcpy(ret, "image/scene/sc2.png");
    }else if(strcmp(line -> scene, "sc3") == 0){
        strcpy(ret, "image/scene/sc3.png");
    }
    return ret;
}

char *get_speaker(sline *line){
    char *ret = (char *)calloc(32, sizeof(char));
    if(strcmp(line -> speaker, "肌肉超人") == 0){
        strcpy(ret, "image/character/bighead.png");
    }else if(strcmp(line -> speaker, "洪suki") == 0){
        strcpy(ret, "image/character/pop.png");
    }
    return ret;
}

char *get_dialogue(sline *line){
    char *ret = (char *)calloc(32, sizeof(char));
    sprintf(ret, "image/dialogue/%s.png", line -> dialogue);
    return ret;
}

void free_sline(sline *line){
    if(line -> scene != NULL){
        free(line -> scene);
    }
    if(line -> speaker != NULL){
        free(line -> speaker);
    }
    if(line -> dialogue != NULL){
        free(line -> dialogue);
    }
    if(line -> choice != NULL){
        free(line -> choice);
    }
    if(line -> event != NULL){
        free(line -> event);
    }
    free(line);
}