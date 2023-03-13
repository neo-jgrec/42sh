/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** env_builtins
*/

#include "my.h"

int my_print_env(term_t *term)
{
    for (int i = 0; term->env[i] != NULL; i++)
        my_printf("%s\n", term->env[i]);
    return (0);
}

int my_setenv_builtin(term_t *term)
{
    if (term->argv[1] == NULL) {
        my_print_env(term);
        return (0);
    }
    if (term->argv[2] == NULL)
        term->argv[2] = "";
    if (my_setenv(term->argv[1], term->argv[2], term->env) == 1)
        return (1);
    return (0);
}

int my_unsetenv_builtin(term_t *term)
{
    if (term->argv[1] == NULL) {
        my_printf("unsetenv: Too few arguments.\n");
        return (1);
    }
    if (my_unsetenv(term->argv[1], term->env) == 1)
        return (1);
    return (0);
}
