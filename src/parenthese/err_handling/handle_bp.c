/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_bp
*/

#include "my.h"

int is_joker(const char *str, const char **jokers);
int print_par_error(int err_id);
const char *bf_jokers[] = {";", "||", "|", "<<", ">>", ">", "<",
"&&", "(", NULL};
const char *af_jokers[] = {";", "||", "|", "<<", ">>", ">", "<",
"&&", ")", NULL};

static int handle_type_err(char *arg)
{
    if (!strcmp(arg, ")") || !strcmp(arg, "("))
        return print_par_error(1);
    else
        return print_par_error(3);
}

static int check_before_pos(char **argv, size_t i)
{
    if (i == 0) {
        return 0;
    } else {
        if (!is_joker(argv[i - 1], bf_jokers))
            return handle_type_err(argv[i - 1]);
    }
    return 0;
}

static int check_after_pos (char **argv, size_t i)
{
    if (argv[i + 1] == NULL) {
        return 0;
    } else {
        if (!is_joker(argv[i + 1], af_jokers))
            return handle_type_err(argv[i + 1]);
    }
    return 0;
}

int handle_bp(char **argv)
{
    int ret;

    for (size_t i = 0; argv[i] != NULL; i++) {
        if (!strcmp(argv[i], "("))
            ret = check_before_pos(argv, i);
        if (!strcmp(argv[i], ")"))
            ret = check_after_pos(argv, i);
        if (ret)
            return 1;
    }
    return 0;
}
