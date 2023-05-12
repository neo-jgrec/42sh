/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parenthese handing
*/

#include "my.h"

int handle_parenthese(term_t *term)
{
    if (handle_tm(term->str))
        return 1;
    if (handle_bp(term->argv))
        return 1;
    if (handle_tm_argv(term->argv))
        return 1;
    if (handle_null(term->argv));
        return 1;
    return 0;
}
