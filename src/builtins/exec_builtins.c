/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** exec
*/

#include "my.h"

int execute_builtin_command(char **args, char **env,
int *exit_status)
{
    for (int i = 0; commands[i].name != NULL; i++) {
        if (my_strcmp(args[0], commands[i].name) == 0) {
            commands[i].func(args, env, exit_status);
        }
    }
    return (0);
}
