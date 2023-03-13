/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_exit
*/

#include "my.h"
#include <stdbool.h>

static bool my_str_isnum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (false);
    }
    return (true);
}

void my_exit(term_t *term)
{
    if (len_tab(term->argv) > 2) {
        my_printf("exit: Expression Syntax.\n");
        return;
    }
    if (term->argv[1] != NULL) {
        if (my_str_isnum(term->argv[1]) == 0) {
            my_printf("exit: Badly formed number.\n");
            return;
        }
        exit(my_atoi(term->argv[1]));
    }
    exit(term->exit_status);
}
