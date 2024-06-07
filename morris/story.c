#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#define DEBUG 1
#define MORE_DEBUG 0
#define HI if(DEBUG)printf("HI\n");
#define XD if(DEBUG)
#define XDD if(MORE_DEBUG)

/*
story file rules:
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

// read story file
void read_story(char* filename) {
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        printf("Error: File not found.\n");
        return;
    }
    char line[256];
    while(fgets(line, sizeof(line), file)) {
        printf("%s", line);

        // functions
    }
    fclose(file);
}

// find scene in line, it start with '@', success return 1, fail return 0
int32_t find_scene(char* line, char* scene) 
{
    if(line[0] == '@'&& line[1] == ' ') {
        XD printf("(find_scene)   valid format, the name of scene is \"");
        line += 2;
        printf("%s\"\n", line);
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
}

// find dialogue in line, it start with '-', success return 1, fail return 0
int32_t find_dialogue(char* line, char* speaker, char* dialogue) 
{
    if(line[0] == '-' && line[1] == ' ') {
        XD printf("(find_dialogue)    valid format, the speaker is \"");
        line += 2;

        char* end = strchr(line, ']');
        if(end == NULL) {
            printf("???\"\n");
            XDD printf("(find_dialogue)    invalid name format\n");
            return 0;
        }
        *end = '\0';
        
        printf("%s\", the dialogue is \"", line); //print name
        strcpy(speaker, line);
        line = end + 1;
        
        printf("%s\"\n", line); // print dialogue
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
int32_t find_choice(char* line, char* choice, int32_t* jump_to) 
{
    if(line[0] == '?' && line[1] == ' ') {
        XD printf("(find_choice)    valid format, the choice is \"");
        line += 2;
        char* end = strchr(line, '~');
        if(end == NULL) {
            printf("???\"\n");
            XDD printf("(find_choice)    invalid choice format\n");
            return 0;
        }
        *end = '\0';
        
        printf("%s\"\n", line); // print choice
        strcpy(choice, line);

        line = end + 1;
        printf("(find_choice)    jump to %s\n", line);
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
int32_t find_event(char* line, char* event, char* attribute, char* operation, int32_t* value) 
{
    if(line[0] == '!' && line[1] == ' ') {
        XD printf("(find_event)    valid format, the event is \"");
        line += 2;
        if(line[0] != 'A' || line[0] != 'B' || line[0] != 'C') {
            printf("???\"\n");
            XDD printf("(find_event)    invalid event format\n");
            return 0;
        }
        
        if( line[0] == 'A') 
        {
            printf("(find_event)    Attribute :");
            line += 2;

            int i = 0;
            while(line[i] != ' ') 
            {
                attribute[i] = line[i];
                i++;
            }
            attribute[i] = '\0';
            printf("%s,", attribute);

            line += i + 1;
            i = 0;

            while(line[i] != ' ') 
            {
                operation[i] = line[i];
                i++;
            }
            operation[i] = '\0';
            printf(" %s ,", operation);

            line += i + 1;
            *value = atoi(line);
            printf(" %d\n", *value);

            return 1;

        }
        else if( line[0] == 'B') 
        {
            printf("(find_event)    Bag_item :");
            line += 2;
            int i = 0;
            while(line[i] != ' ') 
            {
                attribute[i] = line[i];
                i++;
            }
            attribute[i] = '\0';
            printf("%s,", attribute);

            line += i + 1;
            i = 0;

            while(line[i] != ' ') 
            {
                operation[i] = line[i];
                i++;
            }
            operation[i] = '\0';
            printf(" %s ,", operation);

            line += i + 1;
            *value = atoi(line);
            printf(" %d\n", *value);

            return 2;

        }
        else if( line[0] == 'C') {
            printf("Condition change\"\n");
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










