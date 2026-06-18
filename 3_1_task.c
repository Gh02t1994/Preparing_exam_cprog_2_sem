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


int take_arr_words(char str[], char words[][MAX_LEN_WORD], size_t *count_words)
{
    *count_words = 0;
    char *word = strtok(str, MARKS);

    while (word != NULL && *count_words < MAX_COUNT_WORDS)
    {
        if (strlen(word) >= MAX_LEN_WORD)
            return ERROR;

        strcpy(words[*count_words], word);
        word = strtok(NULL, MARKS);
        (*count_words)++;
    }

    return SUCCESS;
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

void pal_arr(char words[][MAX_LEN_WORD], size_t count_words)
{
    for (size_t i = 0; i < count_words; i++)
    {
        if (check_pal(words[i]) == SUCCESS)
        {
            for (int j = 0; words[i][j] != '\0'; j++)
                words[i][j] = toupper(words[i][j]);
        }
    }
}

void make_new_str(char str[], char new_str[], char words[][MAX_LEN_WORD])
{
    size_t pos = 0, new_pos = 0;
    size_t ind_word = 0;

    new_str[0] = '\0';
    while (str[pos] != '\0')
    {
        while (str[pos] != '\0' && is_marks(str[pos]) == 1)
        {
            new_str[new_pos++] = str[pos++];
        }

        while (str[pos] != '\0' && is_marks(str[pos]) != 1)
            pos++;

        size_t len_word = strlen(words[ind_word]);
        for (size_t i = 0; i < len_word; i++)
            new_str[new_pos++] = words[ind_word][i];

        ind_word++;
    }
}

int main(void)
{
    char str[MAX_LEN_STR], new_str[MAX_LEN_STR], words[MAX_COUNT_WORDS][MAX_LEN_WORD], source[MAX_LEN_STR];
    size_t count_words;
    int rc;

    rc = input(str);
    if (rc != SUCCESS)
        return ERROR;

    strcpy(source, str);

    rc = take_arr_words(str, words, &count_words);
    if (rc != SUCCESS)
        return ERROR;
    
    pal_arr(words, count_words);

    make_new_str(source, new_str, words);

    printf("%s\n", new_str);
}