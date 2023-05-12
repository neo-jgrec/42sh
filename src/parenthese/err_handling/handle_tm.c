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
