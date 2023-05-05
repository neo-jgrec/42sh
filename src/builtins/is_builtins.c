/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** is_builtins
*/

#include "my.h"

int is_builtins(char **args)
{
    if (args[0] == NULL)
        return 0;
    for (int i = 0; commands[i].name != NULL; i++) {
        if (my_strcmp(args[0], commands[i].name) == 0) {
            return 1;
        }
        if (my_strncmp(args[0], "!", 1) == 0)
            return (1);
    }
    return 0;
}
