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

char *clean_str_minishell(char *str, const char *to_clean);
char **a_mkstw(char *str, char *sep, int check_quote);

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

char *merge_all_args(char **args)
{
    int total_length = 0;
    int num_args = 0;
    for (int i = 0; args[i] != NULL; i++) {
        total_length += strlen(args[i]);
        num_args++;
    }
    int total_size = total_length + num_args - 1 + 1;
    char *str = malloc(sizeof(char) * total_size);
    if (str == NULL)
        return NULL;
    strcpy(str, args[0]);
    for (int i = 1; args[i] != NULL; i++) {
        strcat(str, " ");
        strcat(str, args[i]);
    }
    return str;
}

void edit_args_with_globbing(char ***args)
{
    char *str = merge_all_args(*args);
    char *new_str = edit_str_with_globbing(str);
    *args = a_mkstw(new_str, " ", 0);
    free(str);
    free(new_str);
}
