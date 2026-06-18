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

void reverse_number(char number[], char str_num[])
{
    size_t len = strlen(number);

    for (size_t i = 0; i < len; i++)
        str_num[i] = number[len - i - 1];

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

void make_new_str(char str[], char new_str[])
{
    size_t pos = 0, pos_new_str = 0;
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
            reverse_number(temp, rev_numb);
            strcat(new_str, rev_numb);
            pos_new_str += len_word;
        }
        else
        {
            strcat(new_str, temp);
            pos_new_str += len_word;
        }
    }
}

int main(void)
{
    char str[MAX_LEN_STR], new_str[MAX_LEN_STR];
    int rc;

    rc = input(str);
    if (rc != SUCCESS)
        return ERROR;

    make_new_str(str, new_str);

    printf("%s\n", new_str);

    return SUCCESS;
}
