/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** parsing_error
*/

#include "my.h"


int parsing_error(char **args)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (((my_strcmp(args[i], ">") == 0 || my_strcmp(args[i], "<") == 0) &&
        (my_strcmp(args[i + 1], ">") == 0 || my_strcmp(args[i + 1], "<") == 0)) ||
        ((my_strcmp(args[i], ">>") == 0 || my_strcmp(args[i], "<<") == 0)
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
    return (0);
}
