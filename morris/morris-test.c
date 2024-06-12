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
    hard_read_story("test.txt");

    //easy_read_story("easy.txt");
    FILE *fp = fopen("test.txt", "r");




    return 0;
}











