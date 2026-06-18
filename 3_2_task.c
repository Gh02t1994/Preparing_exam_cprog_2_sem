#include <stdio.h>
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

int check_pal(char str[])
{
    size_t len = strlen(str);

    for (size_t i = 0; i < len / 2; i ++)
    {
        if (tolower(str[i]) != tolower(str[len - 1 - i]))
            return ERROR;
    }

    return SUCCESS;
}

void make_new_str(char str[], char new_str[])
{
    size_t pos = 0, new_pos = 0;
    size_t start;
    size_t len_word;

    new_str[0] = '\0';
    while (str[pos] != '\0')
    {
        while (str[pos] != '\0' && is_marks(str[pos]) == 1)
        {
            new_str[new_pos++] = str[pos++];
        }

        start = pos;
        while (str[pos] != '\0' && is_marks(str[pos]) != 1)
            pos++;

        len_word = pos - start;

        char temp[MAX_LEN_WORD];
        strncpy(temp, str + start, len_word);
        temp[len_word] = '\0';

        if (check_pal(temp) == SUCCESS)
        {
            for (int i = 0; temp[i] != '\0'; i++)
                new_str[new_pos++] = toupper(temp[i]);
        }
        else
        {
            for (int i = 0; temp[i] != '\0'; i++)
                new_str[new_pos++] = temp[i];
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
}