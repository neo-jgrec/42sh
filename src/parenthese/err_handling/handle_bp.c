/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_bp
*/

#include "my.h"

int is_joker(char c, const char **jokers);

const char *jokers[] = {";", "||", "|", "<<", ">>", ">", "<", "&&", "(", NULL};

static int is_valid_pos(char **argv, ssize_t i)
{
    if (i == 0 && !is_joker(argv[i + 1][0], jokers))
        return 0;
    if (i + 1 != NULL && (!is_joker(argv[i + 1][0], jokers) ||
    !is_joker(argv[i - 1][0], jokers)))
        return 0;
    if (i + 1 == NULL && !is_joker(argv[i - 1][0], jokers))
        return 0;
    return 1;
}

int handle_bp(char **argv)
{
    for (ssize_t i = 0; argv[i] != NULL; i++) {
        if (argv[i][0] == '(' && !is_valid_pos(argv, i))
            return print_par_error(3);
    }
    return 0;
}
