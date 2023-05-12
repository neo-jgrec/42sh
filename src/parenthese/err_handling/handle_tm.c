/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_tm
*/

#include "my.h"

int handle_tm(char *input)
{
    ssize_t nb = 0;

    for (size_t i = 0; input[i] != '\0'; i++) {
        if (input[i] == '(')
            nb++;
        if (input[i] == ')')
            nb--;
        if (nb < 0)
            return print_par_error(1);
    }
    if (nb > 0)
        return print_par_error(2);
    return 0;
}

int handle_tm_argv(char **argv)
{
    for (size_t i = 0; argv[i] != NULL; i++) {
        if (i + 1 != NULL && (argv[i][0] == '(' && argv[i + 1][0] == '('))
            return print_par_error(1);
    }
    return 0;
}
