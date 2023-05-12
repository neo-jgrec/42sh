/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** auto_completion
*/

#include "my.h"
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char *find_file_match(char *file_word, size_t last_word_len);
char *find_match(const char **suggestions,
    char *last_word, size_t last_word_len);

const char *suggestions[] = {
    "env",
    "setenv",
    "unsetenv",
    "cd",
    "alias",
    "unalias",
    "echo",
    "exit",
    "which",
    "where",
    "history",
    NULL
};

static void process_last_word(char *str, size_t len,
    char **last_word, size_t *last_word_len)
{
    *last_word = strrchr(str, ' ');
    *last_word = *last_word ? *last_word + 1 : str;
    *last_word_len = str + len - *last_word;
}

static char *get_file_word(char *last_word, size_t *last_word_len)
{
    char *file_word = last_word;

    if (strncmp(last_word, "./", 2) == 0) {
        file_word += 2;
        *last_word_len -= 2;
    }
    return file_word;
}

static void update_str_last_word(size_t *index, char *str, char *suffix)
{
    *index = strlen(str);
    if (suffix[0] == '/') {
        str[*index] = '/';
        (*index)++;
    } else {
        str[*index] = ' ';
        (*index)++;
    }
}

void autocomplete(char *str, size_t *index)
{
    size_t len = *index;
    if (len == 0) return;
    char *last_word;
    size_t last_word_len;
    process_last_word(str, len, &last_word, &last_word_len);
    char *file_word = get_file_word(last_word, &last_word_len);
    char *match = find_match(suggestions, last_word, last_word_len);
    char *file_match = find_file_match(file_word, last_word_len);
    if ((!match && !file_match) || (match && file_match)) return;
    match = match ? match : file_match;
    if (match) {
        struct stat path_stat = {0};
        stat(match, &path_stat);
        char *suffix = (S_ISDIR(path_stat.st_mode)) ? "/" : " ";
        printf("\033[%zuD\033[K%s%s%s", last_word_len, match,
            suffix, &str[len]);
        fflush(stdout);
        strcpy(last_word, match);
        update_str_last_word(index, str, suffix);
    }
}
