/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_tm
*/

#include "my.h"

int print_par_error(int err_id);

static int handle_tm_argv(char **argv)
{
    return 0;
}

int handle_tm(char *input, char **argv)
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
    return handle_tm_argv(argv);
}
