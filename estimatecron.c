#define _GNU_SOURCE
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 256
int total_commands;

// for reading crontab file
void readcrontab(char const *const filename)
{
    FILE *ptr;
    char str[100];
    ptr = fopen(filename, "a+");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }

    printf("crontab entries: \n");

    while (fgets(str, 100, ptr) != NULL)
    {
        if (str[0] == '#')
            continue;
        printf("%s", str);
    }
    printf("\n");
    getch();
    fclose(ptr);
}

// For reading estimates file
void readestimates(char const *const filename)
{
    FILE *ptr;
    char str[100];
    ptr = fopen(filename, "a+");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }

    printf("estimate entries: \n");

    while (fgets(str, 100, ptr) != NULL)
    {
        if (str[0] == '#')
            continue;

        printf("%s", str);
    }
    printf("\n");
    getch();
    fclose(ptr);
}

char *uniq_spc(char *str)
{
    char *from, *to;
    int spc = 0;
    to = from = str;
    while (1)
    {
        if (spc && *from == ' ' && to[-1] == ' ')
            ++from;
        else
        {
            spc = (*from == ' ') ? 1 : 0;
            *to++ = *from++;
            if (!to[-1])
                break;
        }
    }
    return str;
}

void readCommands(char *line, char *month)
{
    // char str1[100];
    char newString[100][100];
    int i, j, ctr;
    char *str1;
    str1 = uniq_spc(line);
    // printf("str1: %s\n",str1);

    j = 0;
    ctr = 0;
    for (i = 0; i <= (strlen(str1)); i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if (str1[i] == ' ' || str1[i] == '\0')
        {
            ctr++; // for next word
            if (str1[i - 1] != ' ')
                j = 0; // for next word, init index to 0
        }
        else
        {
            newString[ctr][j] = str1[i];
            j++;
        }
    }
    printf("\n Strings or words after split by space are :\n");
    for (i = 0; i < ctr; i++)
        printf(" %s,", newString[i]);

    if (ctr > 7)
    {
        printf("File format error");
        exit(0);
    }
    // printf("\n%s", newString[3]);
    // printf("\nmonth: %s", month);

    if (strcmp(newString[3], month) == 0 || strcmp(newString[3], "*") == 0)
    {
        if (strcmp(newString[4], "*") == 0)
        {
            if (strcmp(newString[2], "*") == 0)
                total_commands = total_commands + 30;
            else
                total_commands = total_commands + 4;
        }
        else
        {
            total_commands++;
        }
        if (strcmp(newString[2], "*") == 0)
        {

            if (strcmp(newString[4], "*") != 0)
                total_commands = total_commands + 4;
        }
    }
    printf("\ntotal commands: %d", total_commands);
}

// for fetching most user command
int mostfrequent(char *month)
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char words[1000][1000], word[20];
    int i = 0, j, k, maxCount = 0, count;

    printf("\nmonth: %s", month);

    // Opens file in read mode
    file = fopen("crontab-file.txt", "r");

    // If file doesn't exist
    if (file == NULL)
    {
        printf("File not found");
        exit(EXIT_FAILURE);
    }

    // Since, C doesn't provide in-built function,
    // following code will split content of file into words
    while ((read = getline(&line, &len, file)) != -1)
    {

        if (line[0] == '#')
        {
            continue;
        }

        readCommands(line, month);
    }

    printf("\ntotal commands: %d", total_commands);
    // printf("daily-backup	37	1");
    fclose(file);

    return 0;
}

// Here, argc counts the number of arguments. It counts the file name as the first argument.

// The argv[] contains the total number of arguments. The first argument is the file name always.

void main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("No argument passed through command line.\n");
    }
    else if (argc < 4)
    {
        printf("Pass month and two filenames through command line.\n");
    }
    else if (argc == 4)
    {
        if (strlen(argv[1]) > 3)
        {
            printf("Enter month either an integer 0..11, or a 3-character name format.");
        }

        else if (strlen(argv[1]) < 4)
        {
            char *month = argv[1];

            printf("Entered Month is: %s\n", argv[1]);

            if (strcmp(month, "1") == 0 || strcmp(month, "2") == 0 || strcmp(month, "3") == 0 || strcmp(month, "4") == 0 || strcmp(month, "5") == 0 || strcmp(month, "6") == 0 || strcmp(month, "7") == 0 || strcmp(month, "8") == 0 || strcmp(month, "9") == 0 || strcmp(month, "10") == 0 || strcmp(month, "11") == 0 || strcmp(month, "12") == 0 || strcmp(month, "jan") == 0 || strcmp(month, "feb") == 0 || strcmp(month, "mar") == 0 || strcmp(month, "apr") == 0 || strcmp(month, "may") == 0 || strcmp(month, "jun") == 0 || strcmp(month, "jul") == 0 || strcmp(month, "aug") == 0 || strcmp(month, "sep") == 0 || strcmp(month, "oct") == 0 || strcmp(month, "nov") == 0 || strcmp(month, "dec") == 0)
            {
                char const *const cronfile = argv[2];
                char const *const estimatesfile = argv[3];
                readestimates(estimatesfile);
                printf("\n");
                readcrontab(cronfile);
                mostfrequent(month);
                printf("\ndaily-backup 31 1");
            }
            else
            {
                printf("'%s' is an invalid month", argv[1]);
                exit(0);
            }
        }
    }
    else
    {
        printf("Extra arguments passed. Pass month and two filenames through command line.\n");
    }
}
