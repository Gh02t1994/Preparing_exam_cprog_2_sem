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

int check_all_words(char str[], int numbers[], size_t *count_numbers)
{
    size_t pos = 0;
    *count_numbers = 0;

    while (str[pos] != '\0')
    {
        size_t start = pos;

        while (str[pos] != '\0' && is_marks(str[pos]) != 1)
        {
            pos++;
        }

        size_t len_word = pos - start;
        
        for (size_t i = 0; i < size; i++)
        {
            if (is_number(words[i]) != ERROR)
            {
                numbers[*count_numbers] = atoi(words[i]);
                (*count_numbers)++;
            }
        }
    }

    if (*count_numbers == 0)
        return ERROR;

    return SUCCESS;
}

void search_min_max(int numbers[], size_t count, int *min, int *max)
{
    *min = numbers[0]; *max = numbers[0];

    for (size_t i = 0; i < count; i++)
    {
        if (numbers[i] < *min)
            *min = numbers[i];
        
        if (numbers[i] > *max)
            *max = numbers[i];
    }
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

void vstabka_sub(char str[], char new_str[], char sub_search[], char sub_in[])
{
    size_t len_sub_se = strlen(sub_search);

    new_str[0] = '\0';
    size_t pos_old = 0;

    while (str[pos_old] != '\0')
    {
        if (is_marks(str[pos_old]) == 1)
        {
            char tmp[2];
            tmp[0] = str[pos_old];
            tmp[1] = '\0';

            strcat(new_str, tmp);
            pos_old++;
        }
        else
        {
            size_t start = pos_old;

            while (str[pos_old] != '\0' && is_marks(str[pos_old]) != 1)
            {
                pos_old++;
            }

            size_t len_word = pos_old - start;

            if (len_word == len_sub_se && strncmp(str + start, sub_search, len_sub_se) == 0)
            {
                strcat(new_str, sub_in);
            }
            else
            {
                char temp[MAX_LEN_WORD];
                strncpy(temp, str + start, len_word);
                temp[len_word] = '\0';
                strcat(new_str, temp);
            }
        }
    }
}

void make_new_str(char str[], int min, int max, char new_str[])
{
    char min_str[MAX_LEN_WORD], max_str[MAX_LEN_WORD];
    sprintf(min_str, "%d", min);
    sprintf(max_str, "%d", max);

    char temp_str_1[MAX_LEN_STR], temp_str_2[MAX_LEN_STR];

    vstabka_sub(str, temp_str_1, min_str, "__TEMP__");

    vstabka_sub(temp_str_1, temp_str_2, max_str, min_str);

    vstabka_sub(temp_str_2, new_str, "__TEMP__", max_str);
}

int main(void)
{
    char str[MAX_LEN_STR], words[MAX_COUNT_WORDS][MAX_LEN_WORD], new_str[MAX_LEN_STR];
    int numbers[MAX_COUNT_WORDS];
    size_t size, count_numbers;
    int min, max;
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
    
    search_min_max(numbers, count_numbers, &min, &max);

    make_new_str(source, min, max, new_str);

    printf("%s\n", new_str);

    return SUCCESS;
}
