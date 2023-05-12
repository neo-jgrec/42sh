/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parenthese handing
*/

#include "my.h"

int is_joker(char c, const char **jokers);

const char *jokers[] = {";", "||", "|", "<<", ">>", ">", "<", "&&", "(", NULL};

static int is_valid_pos(char **argv, ssize_t i)
{
    if (i == 0 && !is_joker(argv[i + 1][0], jokers))
        return 0;
    if (i != 0 && (!is_joker(argv[i + 1][0], jokers) ||
    !is_joker(argv[i - 1][0], jokers)))
        return 0;
    return 1;
}

static int parse_par_pos(char **argv)
{
    for (ssize_t i = 0; argv[i] != NULL; i++) {
        if (argv[i][0] == '(' && !is_valid_pos(argv, i))
            return print_par_error(3);
    }
    return 0;
}

int handle_parenthese(term_t *term)
{
    if (handle_tm(term->str))
        return 1;
    if (parse_par_pos(term->argv))
        return 1;
    return 0;
}
