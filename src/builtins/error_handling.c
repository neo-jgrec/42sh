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
        write(1, "setenv: Variable name must begin with a letter.\n", 48);
        return (1);
    }
    if (my_str_isalphanum(name) == 0) {
        write(1, "setenv: Variable name must", 26);
        write(1, " contain alphanumeric characters.\n", 34);
        return (1);
    }
    return (0);
}
