/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** print_par_error
*/

#include "my.h"

int print_par_error(int err_id)
{
    if (err_id == 1)
        my_printf("Too many )'s.\n");
    if (err_id == 2)
        my_printf("Too many ('s.\n");
    if (err_id == 3)
        my_printf("Badly placed ()'s");
    if (err_id == 4)
        my_printf("Invalid null command.\n");
    return 1;
}
