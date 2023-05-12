/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_null
*/

#include "my.h"

int is_joker(char c, const char **jokers);

const char *token[] = {";", "||", "|", "<<", ">>", ">", "<",
"&&", "(", ")", NULL};

static bool is_only_token(char *input)
{
    for (size_t i = 0; input[i] != '\0'; i++) {
        if (!is_joker(input[i], token))
            return false;
    }
    return true;
}

static bool parse_par_command(char *input)
{
    if (is_only_token(input))
        return true;
    return false;
}

int handle_null(char **argv)
{
    bool ret = false;

    for (size_t i = 0; argv[i] != NULL; i++) {
        if (argv[i][0] == '(')
            ret = parse_par_command(argv[i]);
        if (ret)
            return print_par_error(4);
    }
    return 0;
}
