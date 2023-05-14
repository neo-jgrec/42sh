/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** globing
*/

#include "my.h"
#include <glob.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void handle_token(char *token, glob_t *glob_result, char *new_str)
{
    if (strchr(token, '*') || strchr(token, '?') || strchr(token, '[')) {
        glob(token, GLOB_TILDE, NULL, glob_result);
        for (size_t i = 0; i < glob_result->gl_pathc; i++) {
            strcat(new_str, glob_result->gl_pathv[i]);
            strcat(new_str, " ");
        }
        globfree(glob_result);
    } else {
        strcat(new_str, token);
        strcat(new_str, " ");
    }
}

char *edit_str_with_globbing(char *str)
{
    glob_t glob_result;
    char *new_str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    *new_str = '\0';
    memset(&glob_result, 0, sizeof(glob_result));

    char *token = strtok(str, " ");
    while (token != NULL) {
        handle_token(token, &glob_result, new_str);
        token = strtok(NULL, " ");
    }
    new_str[strlen(new_str) - 1] = '\0';

    return new_str;
}
