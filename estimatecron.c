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
#define MAX_PROCESSES 20

struct commands
{
    char command[COMMAND_LEN];
    int time;
    int min;
    int hour;
    int day;
    int month;
    int day_of_week;
    int concurrent_processes[20];
    int concurrent_index;
    int total_executions;
};
// Taken from Chris' workshop
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
    int month;
    int end_of_month;
};

struct data calc_time(char month[])
{
    struct data d;
    // the month
    int m;
    // Turning Month string into an Integer
    if (strncmp("jan", month, 3) == 0 || strncmp("0", month, 3) == 0)
    {
        m = 0;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("feb", month, 3) == 0 || strncmp("1", month, 3) == 0)
    {
        m = 1;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("mar", month, 3) == 0 || strncmp("2", month, 3) == 0)
    {
        m = 2;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("apr", month, 3) == 0 || strncmp("3", month, 3) == 0)
    {
        m = 3;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("may", month, 3) == 0 || strncmp("4", month, 3) == 0)
    {
        m = 4;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("jun", month, 3) == 0 || strncmp("5", month, 3) == 0)
    {
        m = 5;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("jul", month, 3) == 0 || strncmp("6", month, 3) == 0)
    {
        m = 6;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("aug", month, 3) == 0 || strncmp("7", month, 3) == 0)
    {
        m = 7;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("sep", month, 3) == 0 || strncmp("8", month, 3) == 0)
    {
        m = 8;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("oct", month, 3) == 0 || strncmp("9", month, 3) == 0)
    {
        m = 9;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("nov", month, 3) == 0 || strncmp("10", month, 3) == 0)
    {
        m = 10;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else if (strncmp("dec", month, 3) == 0 || strncmp("11", month, 3) == 0)
    {
        m = 11;
        d.first_day_of_month = first_day_of_month(m, YEAR);
    }
    else
    {
        printf("enter a month in 3 letter form or a number between 0-11.\n");
        exit(EXIT_FAILURE);
    }
    // Setting end of month minutes
    switch (m)
    {
    case 0:
        d.end_of_month = 31 * 1440;
        break;
    case 1:
        d.end_of_month = 28 * 1440;
        break;
    case 2:
        d.end_of_month = 31 * 1440;
        break;
    case 3:
        d.end_of_month = 30 * 1440;
        break;
    case 4:
        d.end_of_month = 31 * 1440;
        break;
    case 5:
        d.end_of_month = 30 * 1440;
        break;
    case 6:
        d.end_of_month = 31 * 1440;
        break;
    case 7:
        d.end_of_month = 31 * 1440;
        break;
    case 8:
        d.end_of_month = 30 * 1440;
        break;
    case 9:
        d.end_of_month = 31 * 1440;
        break;
    case 10:
        d.end_of_month = 30 * 1440;
        break;
    case 11:
        d.end_of_month = 31 * 1440;
        break;
    }
    d.month = m;
    return d;
}

int line_count;
struct commands commands[COMMAND_LINES];
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
        if (atoi(time) == 0)
        {
            printf("Estimates file must contain valid durations in minutes (numeric form).\n");
            exit(EXIT_FAILURE);
        }

        commands[line_index].time = atoi(time);
        strcpy(commands[line_index].command, left_word);
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
            if (strnstr(line, commands[i].command, strlen(line)))
            {
                char *stop = strnstr(line, commands[i].command, strlen(line));
                char placeholder[4];
                int index = 0;
                int cmd_num = 0;
                // save each minute, hour, day, month, and day of week to the structure
                // if its an asterisk, save value as 100.
                for (char *start = &line[0]; start < stop; start++)
                {
                    // increment index until the end of word
                    if (*start != ' ')
                    {
                        index++;
                    }
                    else
                    {
                        // then copy the memory (string) between "start" and "index" and save to placeholder
                        if (cmd_num == 0)
                        {
                            memset(placeholder, 0, 4);
                            memcpy(placeholder, start - index, index);
                            if (strncmp(placeholder, "*", 1) == 0)
                            {
                                commands[i].min = 100;
                                printf("%s ", placeholder);
                            }
                            else
                            {
                                if (atoi(placeholder) < 0 || atoi(placeholder) > 59)
                                {
                                    printf("Min must be between 0 and 59.\n");
                                    exit(EXIT_FAILURE);
                                }
                                commands[i].min = atoi(placeholder);
                                printf("%i ", commands[i].min);
                            }
                        }
                        else if (cmd_num == 1)
                        {
                            memset(placeholder, 0, 4);
                            memcpy(placeholder, start - index, index);
                            if (strncmp(placeholder, "*", 1) == 0)
                            {
                                commands[i].hour = 100;
                                printf("%s ", placeholder);
                            }
                            else
                            {
                                if (atoi(placeholder) < 0 || atoi(placeholder) > 23)
                                {
                                    printf("Hour must be between 0 and 23.\n");
                                    exit(EXIT_FAILURE);
                                }
                                commands[i].hour = atoi(placeholder);
                                printf("%i ", commands[i].hour);
                            }
                        }
                        else if (cmd_num == 2)
                        {
                            memset(placeholder, 0, 4);
                            memcpy(placeholder, start - index, index);
                            if (strncmp(placeholder, "*", 1) == 0)
                            {
                                commands[i].day = 100;
                                printf("%s ", placeholder);
                            }
                            else
                            {
                                if (atoi(placeholder) < 1 || atoi(placeholder) > 31)
                                {
                                    printf("Day must be between 1 and 31.\n");
                                    exit(EXIT_FAILURE);
                                }
                                commands[i].day = atoi(placeholder);
                                printf("%i ", commands[i].day);
                            }
                        }
                        else if (cmd_num == 3)
                        {
                            memset(placeholder, 0, 4);
                            memcpy(placeholder, start - index, index);
                            if (strncmp(placeholder, "*", 1) == 0)
                            {
                                commands[i].month = 100;
                                printf("%s ", placeholder);
                            }
                            else
                            {
                                if (atoi(placeholder) < 0 || atoi(placeholder) > 11)
                                {
                                    printf("Month must be between 0 and 11.\n");
                                    exit(EXIT_FAILURE);
                                }
                                commands[i].month = atoi(placeholder);
                                printf("%i ", commands[i].month);
                            }
                        }
                        else if (cmd_num == 4)
                        {
                            memset(placeholder, 0, 4);
                            memcpy(placeholder, start - index, index);
                            if (strncmp(placeholder, "*", 1) == 0)
                            {
                                commands[i].day_of_week = 100;
                                printf("%s ", placeholder);
                            }
                            else
                            {
                                if (commands[i].day == 100)
                                {
                                    if (strnlen(placeholder, 4) != (long)3)
                                    {
                                        printf("\nEnter a valid day.\n");
                                        exit(EXIT_FAILURE);
                                    }
                                    // check the day of week data is valid
                                    if (strncmp(placeholder, "mon", 3) == 0 || strncmp(placeholder, "1", 3) == 0)
                                    {
                                        commands[i].day_of_week = 1;
                                    }
                                    else if (strncmp(placeholder, "tue", 3) == 0 || strncmp(placeholder, "2", 3) == 0)
                                    {
                                        commands[i].day_of_week = 2;
                                    }
                                    else if (strncmp(placeholder, "wed", 3) == 0 || strncmp(placeholder, "3", 3) == 0)
                                    {
                                        commands[i].day_of_week = 3;
                                    }
                                    else if (strncmp(placeholder, "thu", 3) == 0 || strncmp(placeholder, "4", 3) == 0)
                                    {
                                        commands[i].day_of_week = 4;
                                    }
                                    else if (strncmp(placeholder, "fri", 3) == 0 || strncmp(placeholder, "5", 3) == 0)
                                    {
                                        commands[i].day_of_week = 5;
                                    }
                                    else if (strncmp(placeholder, "sat", 3) == 0 || strncmp(placeholder, "6", 3) == 0)
                                    {
                                        commands[i].day_of_week = 6;
                                    }
                                    else if (strncmp(placeholder, "sun", 3) == 0 || strncmp(placeholder, "0", 3) == 0)
                                    {
                                        commands[i].day_of_week = 0;
                                    }
                                    else
                                    {
                                        printf("Enter a valid day in 3 letter form or digit form (0-6).\n");
                                        exit(EXIT_FAILURE);
                                    }
                                }
                                printf("%i ", commands[i].day_of_week);
                            }
                        }
                        cmd_num++;
                        index = 0;
                    }
                }
                if (cmd_num < 6)
                {
                    printf("\nEnter 6 fields for the crontab file.\n");
                    exit(EXIT_FAILURE);
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
        printf("enter 3 arguments of the form: month(3 characters) crontab-file estimates-file\n");
        exit(EXIT_FAILURE);
    }
    // setting default values
    int peak_processes = 0;
    struct data timeData = calc_time(argv[1]);
    int day;
    day = timeData.first_day_of_month;
    int time = 0;
    int concurrent_processes = 0;
    process_estimates(argv[3]);
    process_cron(argv[2]);

    // Decrementing all relevent processes
    while (time < timeData.end_of_month)
    {
        for (int k = 0; k < line_count; k++)
        {
            for (int l = 0; l < MAX_PROCESSES; l++)
            {
                if (time == commands[k].concurrent_processes[l] && time != 0)
                {
                    commands[k].concurrent_processes[l] = 0;
                    concurrent_processes--;
                }
            }
        }
        // iterate over command structure array and if the all data matches then command is added
        for (int i = 0; i < COMMAND_LINES; i++)
        {
            // if the minute matches or minute was inputted was an '*'
            if (commands[i].min == 100 || commands[i].min == time % 60)
            {
                // if the hour matches or was inputted was an '*'
                if (commands[i].hour == 100 || commands[i].hour == time / 60 % 24)
                {
                    // if the day matches or was inputted was an '*'
                    if (commands[i].day == 100 || commands[i].day == time / 60 / 24)
                    {
                        // if the day of week matches or was inputted was an '*'
                        if (commands[i].day_of_week == 100 || commands[i].day_of_week == day)
                        {
                            // if the month matches or was inputted was an '*'
                            if (commands[i].month == 100 || commands[i].month == timeData.month)
                            {
                                // if the max amount of processors hasnt been reached
                                if (concurrent_processes < 20)
                                {
                                    commands[i].concurrent_processes[commands[i].concurrent_index] = time + commands[i].time;
                                    commands[i].concurrent_index = (commands[i].concurrent_index + 1) % 20;
                                    // incrementing
                                    commands[i].total_executions++;
                                    concurrent_processes++;
                                    // if new peak then update peak
                                    if (concurrent_processes > peak_processes)
                                    {
                                        peak_processes = concurrent_processes;
                                    }
                                }
                                // printf("command:%s|min:%d|hour:%d|day:%d|DoW:%d|month:%d|time:%d\n", commands[i].command, commands[i].min, commands[i].hour, commands[i].day, commands[i].day_of_week, commands[i].month, time);
                            }
                        }
                    }
                }
            }
        }
        if (time % 1440 == 0)
        {
            // printf("date: %d\n", time / 60 / 24);
            day = (day + 1) % 7;
        }
        // debugging stuff
        // printf("%d:%d %d/%d %d\n", time / 60 % 24, time % 60, time / 60 / 24, timeData.month, concurrent_processes);
        time++;
    }
    int total_executions = 0;
    int most_executed = 0;
    char most_executions[COMMAND_LEN];
    for (int cmd = 0; cmd < line_count; cmd++)
    {
        printf("command:%s|executions:%d\n", commands[cmd].command, commands[cmd].total_executions);
        // if the commands execution has surpassed the most executed, set as most executed
        if (commands[cmd].total_executions > most_executed)
        {
            memset(most_executions, 0, COMMAND_LEN);
            most_executed = commands[cmd].total_executions;
            strncpy(most_executions, commands[cmd].command, COMMAND_LEN);
        }
        // increment total_executions by the commands total executions
        total_executions += commands[cmd].total_executions;
    }
    printf("%s %d %d\n", most_executions, total_executions, peak_processes);


}
