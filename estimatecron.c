//  CITS2002 Project 1 2022
//  Student1:   22575612   Howe   Cody 
//  Student2:   STUDENT-NUMBER2   Goodridge   Sam 
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COMMAND_LINES   20
#define LINE_LEN        100
#define COMMAND_LEN     40

struct commands {
    char command[COMMAND_LEN];
    int time;
};

struct commands c1[COMMAND_LINES];

void process_estimates(char estimatef[]) 
{
    FILE *estimates = fopen(estimatef, "r");
    // a string to hold each line while processing them
    char line[LINE_LEN];
    int line_index = 0;
    char time[10];
    while(fgets(line, sizeof(line), estimates) != NULL)
    {
        char left_word[COMMAND_LEN];
        memset(left_word, 0, COMMAND_LEN);
        if (line[0] == '#')
        {
            continue;
        }
        int i = 0;
        while(line[i] != ' ')
        {
            left_word[i] = line[i];
            i++;
        }
        // goto next 'word'
        int j = 0;
        while(line[i] != '\0')
        {
            time[j] = line[i];
            i++;
            j++;
        }
        strcpy(c1[line_index].command, left_word);
        c1[line_index].time = atoi(time);
        printf("%s %d\n", c1[line_index].command, c1[line_index].time);
        line_index++;
    }
}

void process_cron(char cronf[]) 
{
    FILE *cron = fopen(cronf, "r");
    char line[LINE_LEN];
    printf("%s\n", c1[1].command);
    char croncommand[COMMAND_LEN]; 
    while(fgets(line, sizeof(line), cron) != NULL)
    {
        if (line[0] == '#')
        {
            continue;
        }
        printf("%s\n", line);
        int i = strlen(line);


    }
}
int main(int argc, char *argv[])
{
    process_estimates(argv[2]);
    process_cron(argv[1]);
    int k = 0;

}
