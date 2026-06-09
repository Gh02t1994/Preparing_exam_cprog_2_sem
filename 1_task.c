#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN_STR 256
#define MAX_LEN_WORD 16
#define MAX_SIZE 10
#define MAX_NAME_POINT 3
#define MAX_COUNT_WORDS 128

#define MARKS " .,:;"

#define ERROR 1
#define SUCCESS 0

int take_arr_words(char str[], char words[][MAX_LEN_WORD], size_t *size)
{
    char *word = strtok(str, MARKS);
    size_t i = 0;

    while (word != NULL && i < MAX_COUNT_WORDS)
    {
        if (strlen(word) >= MAX_LEN_WORD)
            return ERROR;

        strcpy(words[i], word);
        word = strtok(NULL, MARKS);

        i++;
    }

    if (i == 0)
        return ERROR;
    *size = i;

    return SUCCESS;
}

int input(char str[])
{
    if (fgets(str, MAX_LEN_STR, stdin) == NULL)
        return ERROR;

    size_t len = strlen(str);

    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';

    return SUCCESS;
}

int is_number(char str[])
{
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++)
    {
        if (isdigit(str[i]) == 0)
            return ERROR;
    }

    return SUCCESS;
}

int check_all_words(char words[][MAX_LEN_WORD], int numbers[], size_t size, size_t *count_numbers)
{
    *count_numbers = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (is_number(words[i]) != ERROR)
        {
            numbers[*count_numbers] = atoi(words[i]);
            (*count_numbers)++;
        }
    }

    if (*count_numbers == 0)
        return ERROR;

    return SUCCESS;
}

int main(void)
{
    char str[MAX_LEN_STR], words[MAX_COUNT_WORDS][MAX_LEN_WORD];
    int numbers[MAX_COUNT_WORDS];
    size_t size, count_numbers;
    int rc;

    rc = input(str);
    if (rc != SUCCESS)
        return ERROR;

    rc = take_arr_words(str, words, &size);
    if (rc != SUCCESS)
        return ERROR;

    for (size_t i = 0; i < size; i++)
        printf("%s ", words[i]);

    printf("\n");

    rc = check_all_words(words, numbers, size, &count_numbers);
    if (rc != SUCCESS)
        return ERROR;

    for (size_t i = 0; i < count_numbers; i++)
        printf("%d ", numbers[i]);

    return SUCCESS;
}
