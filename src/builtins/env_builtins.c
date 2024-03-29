/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** env_builtins
*/

#include "my.h"

int setenv_error_handling(char *name, char **args);

static int my_print_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        my_printf("%s\n", env[i]);
    return (0);
}

int my_env(char **args, char **env, int *exit_status,
UNUSED void *data)
{
    if (len_tab(args) > 1) {
        dprintf(2, "env: Too many arguments.\n");
        *exit_status = 1;
        return (1);
    }
    my_print_env(env);
    *exit_status = 0;
    return (0);
}

int my_setenv_builtin(char **args, char **env, int *exit_status,
UNUSED void *data)
{
    if (args[1] == NULL) {
        my_env(args, env, exit_status, data);
        return (0);
    }
    if (setenv_error_handling(args[1], args) == 1) {
        *exit_status = 1;
        return (1);
    }
    if (args[2] == NULL)
        args[2] = "";
    if (my_setenv(args[1], args[2], env) == 1)
        *exit_status = 1;
    else
        *exit_status = 0;

    return *exit_status;
}

int my_unsetenv_builtin(char **args, char **env, int *exit_status,
UNUSED void *data)
{
    if (args[1] == NULL) {
        dprintf(2, "unsetenv: Too few arguments.\n");
        *exit_status = 1;
        return (1);
    }
    if (my_unsetenv(args[1], env) == 1) {
        *exit_status = 1;
        return (1);
    }
    *exit_status = 0;
    return (0);
}
