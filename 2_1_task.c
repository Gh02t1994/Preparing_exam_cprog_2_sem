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

void reverse_number(int number, char str_num[])
{
    char old_str[MAX_LEN_WORD];

    sprintf(old_str, "%d", number);
    size_t len = strlen(old_str);

    for (size_t i = 0; i < len; i++)
        str_num[i] = old_str[len - i - 1];

    str_num[len] = '\0';
}

int is_marks(char sym)
{
    char mark[] = " .,:;";
    
    for (size_t i = 0; mark[i] != '\0'; i++)
    {
        if (sym == mark[i])
            return 1;
    }

    return 0;
}

void make_new_str(char str[], char new_str[], int numbers[])
{
    size_t ind_number = 0, pos = 0, pos_new_str = 0;
    size_t start, len_word;

    new_str[0] = '\0';
    while (str[pos] != '\0')
    {
        while (str[pos] != '\0' && isdigit(str[pos]) == 0)
        {
            new_str[pos_new_str] = str[pos];
            pos_new_str++;
            pos++;
        }
        new_str[pos_new_str] = '\0';

        start = pos;
        while (str[pos] != '\0' && is_marks(str[pos]) != 1)
            pos++;

        char rev_numb[MAX_LEN_WORD];

        len_word = pos - start;
        char temp[MAX_LEN_WORD];
        strncpy(temp, str + start, len_word);
        temp[len_word] = '\0';

        if (is_number(temp) == SUCCESS)
        {
            reverse_number(numbers[ind_number], rev_numb);
            ind_number++;
            strcat(new_str, rev_numb);
            pos_new_str += len_word;
        }
        else
        {
            strcat(new_str, temp);
            pos_new_str += len_word;
            new_str[pos_new_str] = '\0';
        }
    }
}

int main(void)
{
    char str[MAX_LEN_STR], words[MAX_COUNT_WORDS][MAX_LEN_WORD], new_str[MAX_LEN_STR];
    int numbers[MAX_COUNT_WORDS];
    size_t size, count_numbers;
    int rc;

    rc = input(str);
    if (rc != SUCCESS)
        return ERROR;

    char source[MAX_LEN_STR];
    strcpy(source, str);

    rc = take_arr_words(str, words, &size);
    if (rc != SUCCESS)
        return ERROR;

    rc = check_all_words(words, numbers, size, &count_numbers);
    if (rc != SUCCESS)
        return ERROR;

    make_new_str(source, new_str, numbers);

    printf("%s\n", new_str);

    return SUCCESS;
}
