/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** find_match
*/

#include "my.h"
#include <dirent.h>

char *find_match(const char **suggestions,
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

char *find_file_match(char *file_word, size_t last_word_len)
{
    DIR *d;
    struct dirent *dir;
    char *match = NULL;
    int match_count = 0;

    if (strchr(file_word, '/')) return NULL;
    d = opendir(".");
    while (d && (dir = readdir(d)) != NULL) {
        if (!strncmp(dir->d_name, file_word, last_word_len) && !match) {
            match = malloc(strlen(dir->d_name) + 1);
            strcpy(match, dir->d_name);
            match_count++;
        }
    }
    closedir(d);
    return match;
}
