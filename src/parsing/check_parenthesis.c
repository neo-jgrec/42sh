/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** check_parentesis
*/

#include "my.h"

int handle_tm(char *input);
int handle_bp(char **argv);

int check_parenthesis(term_t *term)
{
    if (handle_tm(term->str))
        return 1;
    else if (handle_bp(term-> argv))
        return 1;
    return 0;
}
