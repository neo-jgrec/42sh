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
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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

void process_last_word(char *str, size_t len,
    char **last_word, size_t *last_word_len)
{
    *last_word = strrchr(str, ' ');
    *last_word = *last_word ? *last_word + 1 : str;
    *last_word_len = str + len - *last_word;
}

char* get_file_word(char *last_word, size_t *last_word_len)
{
    char *file_word = last_word;

    if (strncmp(last_word, "./", 2) == 0) {
        file_word += 2;
        *last_word_len -= 2;
    }
    return file_word;
}

char* find_match(const char **suggestions,
    char *last_word, size_t last_word_len)
{
    char *match = NULL;
    int match_count = 0;

    for (int i = 0; suggestions[i] != NULL; i++) {
        if (!strncmp(suggestions[i], last_word, last_word_len)
            && match_count == 0) {
            match = (char *)suggestions[i];
            match_count++;
        }
    }

    return match;
}

char* find_file_match(char *file_word, size_t last_word_len)
{
    DIR *d;
    struct dirent *dir;
    char *match = NULL;
    int match_count = 0;

    d = opendir(".");
    while (d && (dir = readdir(d)) != NULL) {
        if (!strncmp(dir->d_name, file_word, last_word_len) && !match) {
            match = dir->d_name;
            match_count++;
        }
    }
    closedir(d);
    return match;
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
    if (!match) match = find_file_match(file_word, last_word_len);
    if (match) {
        struct stat path_stat;
        stat(match, &path_stat);
        char *suffix = S_ISDIR(path_stat.st_mode) ? "/" : "";
        printf("\033[%zuD\033[K%s%s%s \033[%zuD", last_word_len, match,
            suffix, &str[len], strlen(str) - len + 1);
        fflush(stdout);
        strcpy(last_word, match);
        *index = strlen(str);
        str[*index] = (suffix[0] == '/') ? '/' : ' ';
        (*index) = (suffix[0] == '/') ? *index + 1 : *index;
    }
}
