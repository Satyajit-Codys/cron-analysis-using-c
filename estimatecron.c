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
    char str[50];
    ptr = fopen(filename, "a+");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }

    printf("crontab entries: \n");

    while (fgets(str, 50, ptr) != NULL)
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
    char str[50];
    ptr = fopen(filename, "a+");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }

    printf("estimate entries: \n");

    while (fgets(str, 50, ptr) != NULL)
    {
        if (str[0] == '#')
            continue;
        printf("%s", str);
    }
    printf("\n");
    getch();
    fclose(ptr);
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
        system(line);
        printf("Commnd Executed");

        printf("%s\n", line);
        // printf("inside while\n");
        for (k = 0; line[k] != '\0'; k++)
        {
            // printf("inside for\n");
            // Here, i represents row and j represents column of two-dimensional array words
            if (line[k] != ' ' && line[k] != '\n' && line[k] != ',' && line[k] != '.')
            {
                words[i][j++] = tolower(line[k]);
                printf("if %c\n", line[k]);
            }
            else
            {
                words[i][j] = '\0';
                // Increment row count to store new word
                i++;
                // Set column count to 0
                j = 0;
                printf("else\n");
            }
        }
    }

    int length = i;
    printf("length :%d\n", length);

    // Determine the most repeated word in a file
    for (i = 0; i < length; i++)
    {
        count = 1;
        // Count each word in the file and store it in variable count
        for (j = i + 1; j < length; j++)
        {
            if (strcmp(words[i], words[j]) == 0 && (strcmp(words[i], " ") != 0))
            {
                count++;
                // printf("%s %s\n", words[i], words[j]);
            }
        }
        // If maxCount is less than count then store value of count in maxCount
        // and corresponding word to variable word
        printf("count : %d\n", count);
        if (count > maxCount)
        {
            maxCount = count;
            strcpy(word, words[i]);
            printf("word: %s\n", words[j]);
        }
    }

    // printf("The Array elements are:\n");
    // for (int i = 0; i < 1000; i++)
    // {
    //     for (int j = 0; j < 1000; j++)
    //     {
    //         printf("%d ", words[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("Most repeated word: %s", word);
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
            readcrontab(cronfile);
            mostfrequent();
        }
    }
    else
    {
        printf("Extra arguments passed. Pass month and two filenames through command line.\n");
    }
}
