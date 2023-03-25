/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** builtin_command
*/

#include "my.h"

void builtin_list(UNUSED char **args, UNUSED char **env,
UNUSED int *exit_status)
{
    for (int i = 0; commands[i].name != NULL; i++) {
        printf("%s\n", commands[i].name);
    }
}
