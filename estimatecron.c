//  CITS2002 Project 1 2022
//  Student1:   22575612   Howe   Cody
//  Student2:   22700309   Goodridge   Sam
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define COMMAND_LINES 20
#define LINE_LEN 100
#define COMMAND_LEN 40
#define YEAR 2022

void trim_line(char line[])
{
    int i = 0;

    //  LOOP UNTIL WE REACH THE END OF line
    while (line[i] != '\0')
    {

        //  CHECK FOR CARRIAGE-RETURN OR NEWLINE
        if (line[i] == '\r' || line[i] == '\n' || line[i] == ' ')
        {
            line[i] = '\0'; // overwrite with null-byte
            break;          // leave the loop early
        }
        i++;
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

int first_day_of_month(int month, int year)
{
    struct tm tm;

    //  SET ALL FIELDS OF tm TO ZERO TO MAKE SOME FIELDS 'UNKNOWN'
    memset(&tm, 0, sizeof(tm));

    //  INITIALIZE THE FILEDS THAT WE ALREADY KNOW
    tm.tm_mday = 1;
    tm.tm_mon = month - 1; // 0=Jan, 1=Feb, ....
    tm.tm_year = year - 1900;

    //  ASK THE POSIX FUNCTION mktime TO DETERMINE THE 'UNKNOWN' FIELDS
    //  See: http://pubs.opengroup.org/onlinepubs/9699919799/
    mktime(&tm);

    //  RETURN THE INTEGER MONTH VALUE
    return tm.tm_wday; // 0=Sun, 1=Mon, .....
}

struct data
{
    int first_day_of_month;
    int monthMinute;
    int month;
    int end_of_month;
};

struct data calc_time(char month[])
{
    struct data d;
    // the month in minutes
    int monthMinute;
    // the month
    int m;
    if (strncmp("jan", month, 3) == 0)
    {
        monthMinute = 0;
        m = 0;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("feb", month, 3) == 0)
    {
        monthMinute = 44640;
        m = 1;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("mar", month, 3) == 0)
    {
        monthMinute = 84960;
        m = 2;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("apr", month, 3) == 0)
    {
        monthMinute = 129600;
        m = 3;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("may", month, 3) == 0)
    {
        monthMinute = 172800;
        m = 4;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("jun", month, 3) == 0)
    {
        monthMinute = 217440;
        m = 5;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("jul", month, 3) == 0)
    {
        monthMinute = 260640;
        m = 6;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("aug", month, 3) == 0)
    {
        monthMinute = 305280;
        m = 7;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("sep", month, 3) == 0)
    {
        monthMinute = 349920;
        m = 8;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("oct", month, 3) == 0)
    {
        monthMinute = 393120;
        m = 9;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("nov", month, 3) == 0)
    {
        monthMinute = 437760;
        m = 10;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("dec", month, 3) == 0)
    {
        monthMinute = 480960;
        m = 11;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else
    {
        printf("enter a month in 3 letter form");
        exit(EXIT_FAILURE);
    }
    switch (m)
    {
    case 0:
        d.end_of_month = monthMinute + 31 * 1440;
        break;
    case 1:
        d.end_of_month = monthMinute + 28 * 1440;
        break;
    case 2:
        d.end_of_month = monthMinute + 31 * 1440;
        break;
    case 3:
        d.end_of_month = monthMinute + 30 * 1440;
        break;
    case 4:
        d.end_of_month = monthMinute + 31 * 1440;
        break;
    case 5:
        d.end_of_month = monthMinute + 30 * 1440;
        break;
    case 6:
        d.end_of_month = monthMinute + 31 * 1440;
        break;
    case 7:
        d.end_of_month = monthMinute + 31 * 1440;
        break;
    case 8:
        d.end_of_month = monthMinute + 30 * 1440;
        break;
    case 9:
        d.end_of_month = monthMinute + 31 * 1440;
        break;
    case 10:
        d.end_of_month = monthMinute + 30 * 1440;
        break;
    case 11:
        d.end_of_month = monthMinute + 31 * 1440;
        break;
    }
    d.month = m;
    d.monthMinute = monthMinute;
    return d;
}

int line_count;
struct commands c1[COMMAND_LINES];
void process_estimates(char estimatef[])
{
    FILE *estimates = fopen(estimatef, "r");
    // a string to hold each line while processing them
    char line[LINE_LEN];
    int line_index = 0;
    char time[11];
    while (fgets(line, sizeof(line), estimates) != NULL)
    {
        char left_word[COMMAND_LEN];
        memset(left_word, 0, COMMAND_LEN);
        if (line[0] == '#')
        {
            continue;
        }
        int i = 0;
        //
        while (line[i] != ' ')
        {
            left_word[i] = line[i];
            i++;
        }
        // goto next 'word' (minutes)
        int j = 0;
        while (line[i] != '\0')
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
    while (fgets(line, sizeof(line), cron) != NULL)
    {
        // skip comments
        if (line[0] == '#')
        {
            continue;
        }
        // increment index based on how many estimate commands are provided
        int i = 0;
        while (i < line_count)
        {
            // if the cron command contains an estimate command save and process
            // the crontab command
            if (strnstr(line, c1[i].command, strlen(line)))
            {
                c1[i].frequency = 0;
                char *stop = strnstr(line, c1[i].command, strlen(line));
                char placeholder[4];
                int index = 0;
                int cmd_num = 0;
                // save each minute, hour, day, month, and day of week to the structure
                // if its an asterisk, save value as 100. Also calculate its frequency
                for (char *start = &line[0]; start < stop; start++)
                {
                    if (*start != ' ')
                    {
                        index++;
                    }
                    else
                    {
                        
                        if (cmd_num == 0)
                        {
                            memset(placeholder, 0, 4);
                            memcpy(placeholder, start - index, index);
                            if (strncmp(placeholder, "*", 1) == 0)
                            {
                                c1[i].frequency = 1;
                                c1[i].min = 100;
                                cmd_num = 2;
                                printf("%s ", placeholder);
                            }
                            else
                            {
                                c1[i].min = atoi(placeholder);
                                c1[i].time += c1[i].min;
                                printf("%i ", c1[i].min);
                            }
                        }
                        else if (cmd_num == 1)
                        {
                            memset(placeholder, 0, 4);
                            memcpy(placeholder, start - index, index);
                            if (strncmp(placeholder, "*", 1) == 0)
                            {
                                c1[i].frequency = 60;
                                c1[i].hour = 100;
                                printf("%s ", placeholder);
                            }
                            else
                            {
                                c1[i].hour = atoi(placeholder);
                                c1[i].time += c1[i].hour * 60;
                                printf("%i ", c1[i].hour);
                            }
                        }
                        else if (cmd_num == 2)
                        {
                            memset(placeholder, 0, 4);
                            memcpy(placeholder, start - index, index);
                            if (strncmp(placeholder, "*", 1) == 0)
                            {
                                c1[i].frequency = 60 * 24;
                                c1[i].day = 100;
                                printf("%s ", placeholder);
                            }
                            else
                            {
                                c1[i].day = atoi(placeholder);
                                c1[i].time += atoi(placeholder) * 24 * 60;
                                printf("%i ", c1[i].day);
                            }
                        }
                        else if (cmd_num == 3)
                        {
                            memset(placeholder, 0, 4);
                            memcpy(placeholder, start - index, index);
                            if (strncmp(placeholder, "*", 1) == 0)
                            {
                                c1[i].month = 100;
                                printf("%s ", placeholder);
                            }
                            else
                            {
                                c1[i].month = atoi(placeholder);
                                printf("%i ", c1[i].month);
                            }
                        }
                        else if (cmd_num == 4)
                        {
                            memset(placeholder, 0, 4);
                            memcpy(placeholder, start - index, index);
                            if (strncmp(placeholder, "*", 1) == 0)
                            {
                                c1[i].day_of_week = 100;
                                printf("%s ", placeholder);
                            }
                            else
                            {
                                if (c1[i].day == 100)
                                {
                                    if (strncmp(placeholder, "mon", 3) == 0)
                                    {
                                        c1[i].day_of_week = 0;
                                    } else if (strncmp(placeholder, "tue", 3) == 0)
                                    {
                                        c1[i].day_of_week = 1;
                                    } else if (strncmp(placeholder, "wed", 3) == 0)
                                    {
                                        c1[i].day_of_week = 2;
                                    } else if (strncmp(placeholder, "thu", 3) == 0)
                                    {
                                        c1[i].day_of_week = 3;
                                    } else if (strncmp(placeholder, "fri", 3) == 0)
                                    {
                                        c1[i].day_of_week = 4;
                                    } else if (strncmp(placeholder, "sat", 3) == 0)
                                    {
                                        c1[i].day_of_week = 5;
                                    } else if (strncmp(placeholder, "sun", 3) == 0)
                                    {
                                        c1[i].day_of_week = 6;
                                    } 
                                    
                                }
                                
                                printf("%i ", c1[i].day_of_week);
                            }
                        }
                        cmd_num++;
                        index = 0;
                    }
                }
            }
            i++;
        }
        printf("\n");
    }
}
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("enter 3 arguments of the form month(3 characters), crontab-file, estimates-fil\n");
        exit(EXIT_FAILURE);
    }
    // calculate the time data of the given month
    struct data timeData = calc_time(argv[1]);
    printf("%i %i %i\n", timeData.month, timeData.monthMinute, timeData.end_of_month);
    int day;
    day = timeData.first_day_of_month;
    int time = timeData.monthMinute;
    while (time < timeData.end_of_month)
    {
        // iterate over command structure array
        for (int i = 0; i < COMMAND_LINES; i++)
        {
            if (c1[i].month == 100 || c1[i].month == timeData.month)
            {
                if (c1[i].day_of_week == day || c1[i].day_of_week == 100)
                {
                    // time might have to be switched to be relative to a month 
                    if (c1[i].time == time)
                    {
                        //number of processes + concurrent processes++
                    }
                    
                }
                
            }
        }
        time++;

    }
    process_estimates(argv[3]);
    process_cron(argv[2]);
}
