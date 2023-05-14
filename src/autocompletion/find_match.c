/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** find_match
*/

#include "my.h"
#include <dirent.h>
#include <glob.h>

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
    glob_t glob_result;
    char *glob_pattern = malloc(strlen(file_word) + 3);
    strcpy(glob_pattern, file_word);
    strcat(glob_pattern, "*");
    if (glob(glob_pattern, GLOB_TILDE, NULL, &glob_result) != 0) {
        globfree(&glob_result);
        free(glob_pattern);
        return NULL;
    }
    char *match = NULL;
    for (size_t i = 0; i < glob_result.gl_pathc; i++) {
        if (strncmp(glob_result.gl_pathv[i], file_word, last_word_len) == 0) {
            match = strdup(glob_result.gl_pathv[i]);
            break;
        }
    }
    globfree(&glob_result);
    free(glob_pattern);
    return match;
}
