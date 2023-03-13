/*
** EPITECH PROJECT, 2023
** project-maker
** File description:
** main
*/

#include "my.h"

int minishell(char **env);

int main(int argc, UNUSED char **argv, char **env)
{
    if (argc != 1)
        return (84);
    if (env[0] == NULL)
        env = malloc(sizeof(char *) * 1000);
    return (minishell(env));
}

