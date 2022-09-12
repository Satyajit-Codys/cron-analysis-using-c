#define _GNU_SOURCE
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 256

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

void readCommands(char *line)
{
    // char str1[100];
    char newString[100][100];
    int i, j, ctr;
    char *str1;
    str1 = line;

    // fgets(str1, sizeof str1, str2);

    j = 0;
    ctr = 0;
    for (i = 0; i <= (strlen(str1)); i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if (str1[i] == ' ' || str1[i] == '\0')
        {
            ctr++; // for next word
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
        printf(" %s\n", newString[i]);
}

// for fetching most user command
int mostfrequent()
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char words[1000][1000], word[20];
    int i = 0, j, k, maxCount = 0, count;
    int total_commands;

    // Opens file in read mode
    file = fopen("crontab-file.txt", "r");

    // If file doesn't exist
    if (file == NULL)
    {
        printf("File not found");
        exit(EXIT_FAILURE);
    }

    printf("file opened\n");
    // Since, C doesn't provide in-built function,
    // following code will split content of file into words
    while ((read = getline(&line, &len, file)) != -1)
    {

        if (line[0] == '#') 
        {
            continue;
        }

        printf("%s\n", line);
        readCommands(line);
    }

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
            if (strlen(argv[1]) == 3)
            {
                printf("Entered Month name is: %s\n", argv[1]);
            }
            else
            {
                int month_int = atoi(argv[1]);
                printf("Entered Month is: %d\n", argv[1]);
                if (!isdigit(argv[1][0]) || !isdigit(argv[1][1]) || (month_int > 11))
                {
                    printf("Enter month either an integer 0..11, or a 3-character name format.");
                    exit(0);
                }
            }

            char const *const cronfile = argv[2];
            char const *const estimatesfile = argv[3];
            readestimates(estimatesfile);
            printf("\n");
            readcrontab(cronfile);
            mostfrequent();
            printf("\ndaily-backup 31 1");
        }
    }
    else
    {
        printf("Extra arguments passed. Pass month and two filenames through command line.\n");
    }
}
