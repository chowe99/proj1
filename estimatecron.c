//  CITS2002 Project 1 2022
//  Student1:   22575612   Howe   Cody 
//  Student2:   22700309   Goodridge   Sam 
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COMMAND_LINES   20
#define LINE_LEN        100
#define COMMAND_LEN     40

void trim_line(char line[])
{
    int i = 0;

//  LOOP UNTIL WE REACH THE END OF line
    while(line[i] != '\0') {

//  CHECK FOR CARRIAGE-RETURN OR NEWLINE
        if( line[i] == '\r' || line[i] == '\n'|| line[i] == ' ') {
            line[i] = '\0'; // overwrite with null-byte
            break;          // leave the loop early
        }
        i = i+1;            // iterate through character array
    }
}

struct commands 
{
    char command[COMMAND_LEN];
    int time;
    int min;
    int hour;
    int day;
    int month;
    int day_of_week;
    int frequency;
    int to_minutes;
};

/*
void calc_time(char month[])
{
    // the month represented with an int
    int m;
    if (strncmp("jan", month, 3))
    {
        m = 0;
    }
    if (strncmp("feb", month, 3))
    {
        m = 1;
    }
    if (strncmp("mar", month, 3))
    {
        m = 2;
    }
    if (strncmp("apr", month, 3))
    {
        m = 3;
    }
    if (strncmp("may", month, 3))
    {
        m = 4;
    }
    if (strncmp("jun", month, 3))
    {
        m = 5;
    }
    if (strncmp("jul", month, 3))
    {
        m = 6;
    }
    if (strncmp("aug", month, 3))
    {
        m = 7;
    }
    if (strncmp("sep", month, 3))
    {
        m = 8;
    }
    if (strncmp("oct", month, 3))
    {
        m = 9;
    }
    if (strncmp("nov", month, 3))
    {
        m = 10;
    }
    if (strncmp("dec", month, 3))
    {
        m = 11;
    }
    int minutes;
    int numDays;
    const int YEAR = 2022;
    // mite not need this if we dont use the first day of the month function thing
    switch (m){
        case 0:
          numDays = 31;
          break;
      case 1:
          numDays = 28;
          break;
      case 2:
          numDays = 31;
          break;
      case 3:
          numDays = 30;
          break;
      case 4:
          numDays = 31;
          break;
      case 5:
          numDays = 30;
          break;
      case 6:
          numDays = 31;
          break;
      case 7:
          numDays = 31;
          break;
      case 8:
          numDays = 30;
          break;
      case 9:
          numDays = 31;
          break;
      case 10:
          numDays = 30;
          break;
      case 11:
          numDays = 31;
          break;
    }

}
*/
int line_count;
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
        // 
        while(line[i] != ' ')
        {
            left_word[i] = line[i];
            i++;
        }
        // goto next 'word' (minutes)
        int j = 0;
        while(line[i] != '\0')
        {
            time[j] = line[i];
            i++;
            j++;
        }
        strcpy(c1[line_index].command, left_word);
        c1[line_index].time = atoi(time);
        // printf("%s %d\n", c1[line_index].command, c1[line_index].time);
        line_index++;
    }
    line_count = line_index;
}

void process_cron(char cronf[]) 
{
    FILE *cron = fopen(cronf, "r");
    char line[LINE_LEN];
    // go through each line in the crontab file
    while(fgets(line, sizeof(line), cron) != NULL)
    {
        // skip comments
        if (line[0] == '#')
        {
            continue;
        }
        // increment index based on how many estimate commands are provided
        int i = 0;
        while(i < line_count)
        {
            // if the cron command contains an estimate command save and process
            // the crontab command
            if(strnstr(line, c1[i].command, strlen(line)))
            {

                char *stop = strnstr(line, c1[i].command, strlen(line));
                for (char *start = &line[0]; start < stop; start++) {
                   printf("%c", *start); 
                }
            }
            i++;
        }
    }
}
int main(int argc, char *argv[])
{
     if (argc != 3) {
         printf("enter arguments");
     }
    //for (int i = 0; i < COMMAND_LINES; i++) {
        // c1[i].min; 
    //}

    int minute = 0;
    while(minute < 480960)
    {
         if (0 < minute && minute < 44640)
         {
            // january 
         }
         if (44640 < minute && minute < 84960) {
             // feb
         }
         if (84960 < minute && minute < 129600) {
            // march 
         }
         if (129600 < minute && minute < 172800) {
             // april
         }
         if (172800 < minute && minute < 217440) {
             // may
         }
         if (217440 < minute && minute < 260640) {
             // june
         }
         if (260640 < minute && minute < 305280) {
             // july
         }
         if (305280 < minute && minute < 349920) {
            // aug   
         }
         if (349920 < minute && minute < 393120) {
           // sep  
         }
         if (393120 < minute && minute < 437760) {
           // oct
         }
         if (minute < 437760 && minute < 480960) {
           // nov 
         }
         if (minute < 480960 && minute < 525600) {
           // dec 
         }
         minute++;
    }
    process_estimates(argv[2]);
    process_cron(argv[1]);
    
}
