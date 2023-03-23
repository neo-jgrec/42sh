/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** parsing_error
*/

#include "my.h"

int is_there_only_char(char **args, char *to_find)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], to_find) != 0)
            return (0);
    }
    return (1);
}

int all_char_check(char **args)
{
    if (is_there_only_char(args, ">") || is_there_only_char(args, "<") ||
    is_there_only_char(args, ">>") || is_there_only_char(args, "<<")
    || is_there_only_char(args, "|") || is_there_only_char(args, ";"))
        return (1);
    if ((my_strcmp(args[0], ">") == 0 || my_strcmp(args[0], "<") == 0
    || my_strcmp(args[0], ">>") == 0 || my_strcmp(args[0], "<<") == 0
    || my_strcmp(args[0], ";") == 0)
    && args[1] == NULL)
        return (1);
    if  (my_strcmp(args[0], "|") == 0 && args[1] == NULL) {
        my_printf("Invalid null command.\n");
        return (1);
    }
    return (0);
}

int parsing_error(char **args)
{
    for (int i = 0; args[i + 1] != NULL; i++) {
        if (((my_strcmp(args[i], ">") == 0 || my_strcmp(args[i], "<") == 0) &&
        (my_strcmp(args[i + 1], ">") == 0 || my_strcmp(args[i + 1], "<") == 0))
        || ((my_strcmp(args[i], ">>") == 0 || my_strcmp(args[i], "<<") == 0)
        && (my_strcmp(args[i + 1], ">>") == 0
        || my_strcmp(args[i + 1], "<<") == 0))) {
            my_printf("Missing name for redirect.\n");
            return (1);
        }
        if (my_strcmp(args[i], "|") == 0 && my_strcmp(args[i + 1], "|") == 0) {
            my_printf("Invalid null command.\n");
            return (1);
        }
    }
    if (all_char_check(args) == 1)
        return (1);
    return (0);
}
