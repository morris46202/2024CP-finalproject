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
            if(strcmp(buff, "#end") == 0){
                line -> kind = END;
                break;
            }
            if(strcmp(buff, "###") == 0){
                line = NULL;
                printf("file terminated\n");
                return line;
            }
            line -> kind = PARA;
            sscanf(buff, "#%d", &(line -> para));
            printf("para: %d\n", line -> para);
            break;
        
        case '@':
            line -> kind = SCENE;
            line -> scene = (char *)calloc(len, sizeof(char));
            sscanf(buff, "@%s", line -> scene);
            // printf("scene: %s\n", line -> scene);
            break;

        case '-':
            line -> kind = DIALOGUE;
            line -> speaker = (char *)calloc(len, sizeof(char));
            line -> dialogue = (char *)calloc(len, sizeof(char));
            sscanf(buff, "- %[^:]:%[^\n]", line -> speaker, line -> dialogue);
            // printf("speaker: %s\n", line -> speaker);
            // printf("dialogue: %s\n", line -> dialogue);
            break;

        case '?':
            line -> kind = CHOICE;
            line -> choice = (char *)calloc(len, sizeof(char));
            sscanf(buff, "? %s ~%d~", line -> choice, &(line->jump_to));
            // printf("choice: %s jump: %d\n", line -> choice, line -> jump_to);
            break;

        case '!':
            line -> kind = EVENT;
            line -> attribute = (char *)calloc(len, sizeof(char));
            sscanf(buff, "! %c %s %c %d", &(line -> event), line -> attribute, &(line -> operation), &(line -> value));
            printf("event: %c\n", line -> event);
            printf("attribute: %s\n", line -> attribute);
            printf("operation: %c\n", line -> operation);
            printf("value: %d\n", line -> value);
            break;
    }
    return line;
}

void mod_data(GameData *data, sline *line){
    switch(line -> event){
        case 'A':
            Love love;
            if(strcmp(line -> attribute, "howard_love") == 0){
                love = LOVE_HOWARD;
            }else if(strcmp(line -> attribute, "jcup_love") == 0){
                love = LOVE_JCUP;
            }else if(strcmp(line -> attribute, "suki_love") == 0){
                love = LOVE_SUKI;
            }else if(strcmp(line -> attribute, "tikili_love") == 0){
                love = LOVE_TIKILI;
            }else if(strcmp(line -> attribute, "shinray_love") == 0){
                love = LOVE_SHINRAY;
            }else{
                printf("Invalid value %s\n", line -> attribute);
                return;
            }
            if(line -> operation == '+'){
                data -> love[love] += line -> value;
            }else if(line -> operation == '-'){
                data -> love[love] -= line -> value;
            }else{
                printf("Invalid operation\n");
                return;
            }
        case 'B':
            Item item;
            if(strcmp(line -> attribute, "太鼓達人會員卡") == 0){
                item = ITEM_CARD;
            }else if(strcmp(line -> attribute, "密室逃脫券") == 0){
                item = ITEM_TICKET;
            }else if(strcmp(line -> attribute, "腳踏車") == 0){
                item = ITEM_BIKE;
            }else if(strcmp(line -> attribute, "毛巾") == 0){
                item = ITEM_TOWEL;
            }else if(strcmp(line -> attribute, "期中考優異證書") == 0){
                item = ITEM_MIDTERM;
            }else if(strcmp(line -> attribute, "期末考優異證書") == 0){
                item = ITEM_FINAL;
            }else if(strcmp(line -> attribute, "異樣的注目") == 0){
                item = ITEM_SPECIAL;
            }else{
                printf("Invalid value\n");
                return;
            }
            if(line -> operation == '+'){
                data -> backpack[item] += line -> value;
            }else if(line -> operation == '-'){
                data -> backpack[item] -= line -> value;
            }else{
                printf("Invalid operation\n");
                return;
            }
        default:
            printf("Invalid event\n");
            return;
        
        return;
    }
}

GameData *load_game(char filename[]){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File not found\n");
        return NULL;
    }

    GameData *data = (GameData *)calloc(1, sizeof(GameData));
    data -> para = 0;
    for(int i = 0; i < 10; i++){
        data -> backpack[i] = 0;
    }
    for(int i = 0; i < 5; i++){
        data -> love[i] = 0;
    }

    char buffer[1024];
    fgets(buffer, 1024, fp);
    sscanf(buffer, "para: %d", &(data -> para));
    fgets(buffer, 1024, fp);
    sscanf(buffer, "love: %d %d %d %d %d", &(data -> love[0]), 
                                           &(data -> love[1]), 
                                           &(data -> love[2]), 
                                           &(data -> love[3]), 
                                           &(data -> love[4]));
    fgets(buffer, 1024, fp);
    sscanf(buffer, "backpack: %d %d %d %d %d %d %d %d %d %d", 
                            &(data -> backpack[0]), 
                            &(data -> backpack[1]), 
                            &(data -> backpack[2]), 
                            &(data -> backpack[3]), 
                            &(data -> backpack[4]), 
                            &(data -> backpack[5]), 
                            &(data -> backpack[6]), 
                            &(data -> backpack[7]), 
                            &(data -> backpack[8]), 
                            &(data -> backpack[9]));

    fclose(fp);
    return data;
}

void save_game(GameData *data, char filename[]){
    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        printf("File not found\n");
        return;
    }

    fprintf(fp, "para: %d\n", data -> para);
    fprintf(fp, "love: %d %d %d %d %d\n", data -> love[0], 
                                         data -> love[1], 
                                         data -> love[2], 
                                         data -> love[3], 
                                         data -> love[4]);
    fprintf(fp, "backpack: %d %d %d %d %d %d %d %d %d %d\n", 
                                data -> backpack[0], 
                                data -> backpack[1], 
                                data -> backpack[2], 
                                data -> backpack[3], 
                                data -> backpack[4], 
                                data -> backpack[5], 
                                data -> backpack[6], 
                                data -> backpack[7], 
                                data -> backpack[8], 
                                data -> backpack[9]);

    fclose(fp);
    return;
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
    }else if(strcmp(line -> speaker, "tikili") == 0){
        strcpy(ret, "image/character/tikili.png");
    }
    return ret;
}

char *get_dialogue(sline *line, int *len){
    char *ret = (char *)calloc(128, sizeof(char));
    // strncat(ret, "image/dialogue/", 16);
    (line -> dialogue)[strlen(line -> dialogue) - 1] = '\0'; // remove '\n' at the end of the string
    *len = strlen(line -> dialogue);
    strncat(ret, line -> dialogue, strlen(line -> dialogue));
    // strncat(ret, ".png", 5);
    return ret;
}

Option *get_choice(sline *line){
    Option *opt = (Option *)calloc(1, sizeof(Option));
    opt -> text = (char *)calloc(32, sizeof(char));
    opt -> filepath = (char *)calloc(32, sizeof(char));
    strcpy(opt -> text, line -> choice);
    opt->jump = line -> jump_to;
    opt->text_len = strlen(line -> choice);
    if(strcmp(line -> choice, "洪suki的口琴") == 0){
        strcpy(opt->filepath, "image/item/harmonica.png");
    }else if(strcmp(line -> choice, "tikili的門票") == 0){
        strcpy(opt->filepath, "image/item/ticket.png");
    }else if(strcmp(line -> choice, "女號千的3000藍芽鍵盤") == 0){
        strcpy(opt->filepath, "image/item/keyboard.png");
    }
    return opt;
}

void jump(FILE *fp, int para){
    // fseek(fp, 0, SEEK_SET);
    while(1){
        char *buff = readline(fp);
        // printf("%s", buff);
        sline *line = parse_line(buff, strlen(buff));
        if(line -> kind == END){
            continue;
        }
        if(line -> kind == PARA){
            printf("-------------------------para: %d-------------------------\n", line -> para);
            if(line -> para == para){
                free(buff);
                free_sline(line);
                break;
            }
            // break;
        }
        free(buff);
        free_sline(line);
    }
    return;
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
    if(line -> attribute != NULL){
        free(line -> attribute);
    }
    free(line);
}