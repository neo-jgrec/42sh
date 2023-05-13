/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** error_handling
*/

#include "my.h"

int setenv_error_handling(char *name, char **args)
{
    if (len_tab(args) > 3) {
        my_printf("setenv: Too many arguments.\n");
        return (1);
    }
    if (IS_ALPHA(name[0]) == 0) {
        dprintf(2, "setenv: Variable name must begin with a letter.\n");
        return (1);
    }
    if (my_str_isalphanum(name) == 0) {
        dprintf(2, "setenv: Variable name must contain\
alphanumeric characters.\n");
        return (1);
    }
    return (0);
}
