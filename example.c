/*
gcc -std=c99 -Wall -Wextra -Wpedantic -Werror -Wvla _task.c -lm -o app.exe

alias g_c='read -p "Введите номер файла (_task.c): " filename; gcc -std=c99 -Wall -Wextra -Wpedantic -Werror -Wvla "${filename}_task.c" -lm -o app.exe'

alias gpush='git add . && git commit -m "no" && git push origin main'

alias gpull='git pull origin main'

nano ~/.bashrc
source ~/.bashrc
*/

#include <stdio.h>

#define MAX_LEN_STR 256
#define MAX_LEN_WORD 16
#define MAX_SIZE 10
#define MAX_NAME_POINT 3
#define MAX_COUNT_WORDS 128

int main(void)
{
    
}