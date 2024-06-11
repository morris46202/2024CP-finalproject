#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>

#define DEBUG 0
#define MORE_DEBUG 0
#define HI if(DEBUG)printf("HI\n");
#define XD if(DEBUG)
#define XDD if(MORE_DEBUG)

// struct for return value
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


void hard_read_story(char* filename);
int32_t hard_find_scene(char* line, char* scene);
int32_t hard_find_dialogue(char* line, char* speaker, char* dialogue);
int32_t hard_find_choice(char* line, char* choice, int32_t* jump_to);
int32_t hard_find_event(char* line, char* event, char* attribute, char* operation, int32_t* value);

enum {
    SCENE = 1,
    DIALOGUE = 2,
    CHOICE = 3,
    EVENT = 4,
};

/*
story file rules -easy version:
Begin with #<number>
Scene is indicated by "@ <name>"
Each line of dialogue starts with "- " followed by "[speaker]"
Use #:D to represent events or options
End with #END

*/

void easy_read_story(char* filename);
mo_return *easy_find_scene(char* line);
mo_return *easy_find_dialogue(char* line);
//mo_return *easy_find_special(char* line);
mo_return *init();
int32_t easy_options( int32_t para );


// read story file (testing funciton)
void easy_read_story(char* filename) 
{
    FILE* file = fopen(filename, "r");
    if(file == NULL) 
    {
        printf("Error: File not found.\n");
        return;
    }
    char *line = calloc(2024, sizeof(char));
    int32_t target_paragraph = 1;
    while(!feof(file)) 
    {

        for(int i = 0; i < 2024; i++) 
        {
            fread(line+i, 1, 1, file);
            if(line[i] == '\n') 
            {
                line[i] = '\0';
                break;
            }
        }
        XD printf("[%s]\n", line);

        int32_t paragraph = 0;
        if(line[0] == '#' && isdigit(line[1])) 
        {
            paragraph = atoi(line + 1);
            printf("Paragraph: %d\n", paragraph);
            if(paragraph != target_paragraph) 
            {
                continue;
            }
        }

        while(paragraph == target_paragraph && !feof(file))
        {
            for(int i = 0; i < 2024; i++) 
            {
                fread(line+i, 1, 1, file);
                if(line[i] == '\n') 
                {
                    line[i] = '\0';
                    break;
                }
            }
            XD printf("[%s]\n", line);
            mo_return *result;
            result = easy_find_scene(line);
            if(result->success) 
            {
                printf("Scene: %s\n", result->scene);
            }
            result = easy_find_dialogue(line);
            if(result->success) 
            {
                printf("Dialogue: \n");
                printf("    speaker: %s\n", result->speaker);
                printf("    dialogue: %s\n", result->dialogue);
            }
            // if find #:D
            if(strstr(line, "#:D") != NULL) 
            {   
                target_paragraph = easy_options(paragraph);
            }
            // if find #END
            if(strstr(line, "#END") != NULL) 
            {
                XD printf("The end of the paragraph.\n");
                break;
            }
            free(result);
        }
        //sleep(1);
        if(paragraph != 0 )    fseek(file, 0, SEEK_SET);
        XD printf("Next line\n");
    }
}

mo_return *init()
{
    mo_return *result = malloc(sizeof(mo_return));
    result->success = 0;
    result->kind = 0;
    result->scene = NULL;
    result->speaker = NULL;
    result->dialogue = NULL;
    result->choice = NULL;
    result->event = NULL;
    result->attribute = NULL;
    result->operation = NULL;
    result->value = 0;
    result->jump_to = 0;
    return result;

}

mo_return *easy_find_scene(char* line)
{
    mo_return *result = init();

    if(line[0] == '@' && line[1] == ' ') 
    {
        result->success = 1;
        result->kind = SCENE;
        char *temp = line + 2;
        // remove the '\n' at the end of the line
        char *end = strchr(temp, '\n');
        if(end != NULL) 
        {
            *end = '\0';
        }
        result->scene = temp;
    }
    return result;
}
mo_return *easy_find_dialogue(char* line)
{
    mo_return *result = init();

    if(line[0] == '-' && line[1] == ' ') 
    {
        result->success = 1;
        result->kind = DIALOGUE;
        char *t_speaker = strtok(line + 3, " ");
        char *t_dialogue = strtok(NULL, "\n");
        // remove the ']' at the end of the t_speaker
        char *end = strchr(t_speaker, ']');
        if(end != NULL) 
        {
            *end = '\0';
        }
        // remove the '\n' at the end of the t_dialogue
        end = strchr(t_dialogue, '\n');
        if(end != NULL) 
        {
            *end = '\0';
        }
        result->speaker = t_speaker;
        result->dialogue = t_dialogue;
    }
    return result;

}

int32_t easy_options( int32_t para )
{
    if(para == 1) 
    {
        printf("which option do you want to choose(1-3)?\n");
        printf("1. 洪suki的物品\n");
        printf("2. tikili的物品\n");
        printf("3. 女號千的物品\n");
        int32_t t;
        while(scanf("%d", &t))
        {
            if(t < 1 || t > 3) 
            {
                printf("Invalid input, please try again.\n");
            }
            else 
            {
                break;
            }
        }
        printf("Result number is %d\n", t+1);
        return t+1;
    }
    else if( para == 2 )
    {
        printf("which option do you want to choose(1-1)?\n");
        printf("1. 回去宿舍\n");
        int32_t t;
        while(scanf("%d", &t))
        {
            if(t != 1) 
            {
                printf("Invalid input, please try again.\n");
            }
            else 
            {
                break;
            }
        }
        printf("Result number is 1\n");
        return 1;
    }
    else if( para == 3 )
    {
        printf("which option do you want to choose(1-1)?\n");
        printf("1. 回去宿舍\n");
        int32_t t;
        while(scanf("%d", &t))
        {
            if(t != 1) 
            {
                printf("Invalid input, please try again.\n");
            }
            else 
            {
                break;
            }
        }
        printf("Result number is 1\n" );
        return 1;
    }
    else if( para == 4 )
    {
        printf("which option do you want to choose(1-1)?\n");
        printf("1. 回去宿舍\n");
        int32_t t;
        while(scanf("%d", &t))
        {
            if(t != 1) 
            {
                printf("Invalid input, please try again.\n");
            }
            else 
            {
                break;
            }
        }
        printf("Result number is 1\n" );
        return 1;
    }
}

/*
story file rules -hard version:
Begin with #<number>
    Numbering starts from 1.
    If possible, illustrate the script as a state machine for better understanding.
End with #END
Scene is indicated by "@ <name>"
Each line of dialogue starts with "- " followed by "[speaker]"
    Use "${attribute_name}" to reference attributes
Each choice begins with "? " and ends with "~<number>~" (the number indicates which script section to jump to)
Each event begins with "! "
    Attribute changes are indicated by " A " followed by <attribute_name> <operation> <value>
    Bag changes are indicated by " B " followed by <item_name> <+/-> <quantity>
*/

// read story file (testing funciton)
void hard_read_story(char* filename) 
{
    FILE* file = fopen(filename, "r");
    if(file == NULL) 
    {
        printf("Error: File not found.\n");
        return;
    }
    char *line = calloc(2024, sizeof(char));
    while(!feof(file)) 
    {

        for(int i = 0; i < 2024; i++) 
        {
            fread(line+i, 1, 1, file);
            if(line[i] == '\n') 
            {
                line[i] = '\0';
                break;
            }
        }
        printf("[%s]\n", line);



        usleep(1000000);
        // functions
        char *scene = calloc(512,sizeof(char));
        char *speaker = calloc(512,sizeof(char));
        char *dialogue = calloc(512,sizeof(char));
        char *choice = calloc(512,sizeof(char));
        char *event = calloc(512,sizeof(char));
        char *attribute = calloc(512,sizeof(char));
        char *operation = calloc(512,sizeof(char));

        int32_t value;
        int32_t jump_to;

        char *temp_line = malloc(2024);
        strcpy(temp_line, line);

        int32_t linecheck_scene = hard_find_scene(line, scene);
        strcpy(line, temp_line);
        int32_t linecheck_dialogue = hard_find_dialogue(line, speaker, dialogue);
        strcpy(line, temp_line);
        int32_t linecheck_choice = hard_find_choice(line, choice, &jump_to);
        strcpy(line, temp_line);
        int32_t linecheck_event = hard_find_event(line, event, attribute, operation, &value);

        //printf("linecheck_scene = %d\n", linecheck_scene);

        if(linecheck_scene) {
            printf("Scene: %s\n", scene);
        }
        else if(linecheck_dialogue) 
        {
            printf("Dialogue: \n");
            printf("    speaker: %s\n", speaker);
            printf("    dialogue: %s\n", dialogue);
        }
        else if(linecheck_choice) 
        {
            printf("Choice: [%s]\n", choice);
            printf("    jump to %d\n", jump_to);
        }
        else if(linecheck_event) {
            printf("Event: \n");
            printf("    event(kind): %s\n", event);
            printf("    attribute: %s\n", attribute);
            printf("    operation: %s\n", operation);
            printf("    value: %d\n", value);
        }
    }
    fclose(file);
}


// find scene in line, it start with '@', success return 1, fail return 0
int32_t hard_find_scene(char* line, char* scene) 
{
    if(line[0] == '@'&& line[1] == ' ') {
        XD printf("(find_scene)   valid format, the name of scene is \"");
        line += 2;
        XD printf("%s\"\n", line);
        strcpy(scene, line);
        return 1;
    }
    else
    {
        XDD printf("(find_scene)   invalid format\n");
        XDD printf("(find_scene)   line[0] = %c, line[1] = %c\n", line[0], line[1]);
        XDD printf("(find_scene)   It should start with \"@ \"\n");
        return 0;
    }
    return 0;
}

// find dialogue in line, it start with '-', success return 1, fail return 0
int32_t hard_find_dialogue(char* line, char* speaker, char* dialogue) 
{
    if(line[0] == '-' && line[1] == ' ') 
    {
        XD printf("(find_dialogue)    valid format, the speaker is \"");
        line += 3;

        char* end = strchr(line, ']');
        if(end == NULL) {
            printf("???\"\n");
            XDD printf("(find_dialogue)    invalid name format\n");
            return 0;
        }
        *end = '\0';
        
        XD printf("%s\", the dialogue is \"", line); //print name
        strcpy(speaker, line);
        line = end + 1;
        
        XD printf("%s\"\n", line); // print dialogue
        strcpy(dialogue, line);

        return 1;
    }
    else
    {
        XDD printf("(find_dialogue)    invalid format\n");
        XDD printf("(find_dialogue)    line[0] = %c, line[1] = %c\n", line[0], line[1]);
        XDD printf("(find_dialogue)    It should start with \"- \"\n");
        return 0;
    }
}

// find choice in line, it start with '?', success return 1, fail return 0
int32_t hard_find_choice(char* line, char* choice, int32_t* jump_to) 
{
    if(line[0] == '?' && line[1] == ' ') {
        XD printf("(find_choice)    valid format, the choice is \"");
        line += 2;
        char* end = strchr(line, '~');
        if(end == NULL) {
            XD printf("???\"\n");
            XDD printf("(find_choice)    invalid choice format\n");
            return 0;
        }
        *end = '\0';
        
        XD printf("%s\"\n", line); // print choice
        strcpy(choice, line);

        line = end + 1;
        XD printf("(find_choice)    jump to %s\n", line);
        *jump_to = atoi(line);


        return 1;
    }
    else
    {
        XDD printf("(find_choice)    invalid format\n");
        XDD printf("(find_choice)    line[0] = %c, line[1] = %c\n", line[0], line[1]);
        XDD printf("(find_choice)    It should start with \"? \"\n");
        return 0;
    }
}

// find event in line, it start with '!', attribute return 1, bag return 2, fail return 0
int32_t hard_find_event(char* line, char* event, char* attribute, char* operation, int32_t* value) 
{
    if(line[0] == '!' && line[1] == ' ') {
        XD printf("(find_event)    valid format, the event is \"");
        line += 2;
        if(line[0] != 'A' || line[0] != 'B' || line[0] != 'C') {
            XD printf("???\"\n");
            XDD printf("(find_event)    invalid event format\n");
            return 0;
        }
        
        if( line[0] == 'A') 
        {
            XD printf("(find_event)    Attribute :");
            line += 2;

            int i = 0;
            while(line[i] != ' ') 
            {
                attribute[i] = line[i];
                i++;
            }
            attribute[i] = '\0';
            XD printf("%s,", attribute);

            line += i + 1;
            i = 0;

            while(line[i] != ' ') 
            {
                operation[i] = line[i];
                i++;
            }
            operation[i] = '\0';
            XD printf(" %s ,", operation);

            line += i + 1;
            *value = atoi(line);
            XD printf(" %d\n", *value);

            return 1;

        }
        else if( line[0] == 'B') 
        {
            XD printf("(find_event)    Bag_item :");
            line += 2;
            int i = 0;
            while(line[i] != ' ') 
            {
                attribute[i] = line[i];
                i++;
            }
            attribute[i] = '\0';
            XD printf("%s,", attribute);

            line += i + 1;
            i = 0;

            while(line[i] != ' ') 
            {
                operation[i] = line[i];
                i++;
            }
            operation[i] = '\0';
            XD printf(" %s ,", operation);

            line += i + 1;
            *value = atoi(line);
            XD printf(" %d\n", *value);

            return 2;

        }
        else if( line[0] == 'C') {
            XD printf("Condition change\"\n");
        }

        

        return 1;
    }
    else
    {
        XDD printf("(find_event)    invalid format\n");
        XDD printf("(find_event)    line[0] = %c, line[1] = %c\n", line[0], line[1]);
        XDD printf("(find_event)    It should start with \"! \"\n");
        return 0;
    }
}










