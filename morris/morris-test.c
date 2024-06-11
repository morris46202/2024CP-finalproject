#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>

#include "story.h"

#define DEBUG 1
#define MORE_DEBUG 0
#define HI if(DEBUG)printf("HI\n");
#define XD if(DEBUG)
#define XDD if(MORE_DEBUG)

int main()
{
    //hard_read_story("test.txt");

    easy_read_story("easy.txt");
    FILE *fp = fopen("test.txt", "r");

    // char c1 = "大";
    // char c2 = "大";
    // char *c3 = "大";
    // printf("c: %c%c\n", c1,c2);
    // printf("c3: %s\n", c3);
    // printf("sizeof c3: %ld\n", sizeof(c3));
    // printf("strlen of c3: %ld\n", strlen(c3));

    // while(!feof(fp))
    // {
    //     char *omg = calloc( 8, sizeof(char));
    //     fread(omg,1, 1, fp);
    //     printf("omg: [%s] \n", omg);
    //     printf("omg[0] = %d\n", (int)(omg[0]));
    //     if( !isdigit(omg[0]) && !isalpha(omg[0]) && (int)(omg[0]) <0)
    //     {
    //         printf("omg[0] = %d\n", (int)(omg[0]));
    //         fread(omg+1,1, 2, fp);
    //     }
    //     printf("[%s]\n", omg);
    //     sleep(1);
    // }



    return 0;
}











