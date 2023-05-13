/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_exit
*/

#include "my.h"
#include <stdbool.h>

bool my_str_isnum(char *str)
{
    if (!str)
        return (false);
    for (size_t i = 0; str[i] != '\0'; i++)
        if (!IS_NUM(str[i]))
            return (false);
    return (true);
}

void my_exit(char **argv, UNUSED char **env, int *exit_status, void *data)
{
    term_t *term = data;

    int status = *exit_status;
    if (len_tab(argv) > 2) {
        dprintf(2, "exit: Expression Syntax.\n");
        *exit_status = 1;
        return;
    }
    if (argv[1] != NULL) {
        if (my_str_isnum(argv[1]) == 0) {
            dprintf(2, "exit: Badly formed number.\n");
            *exit_status = 1;
            return;
        }
        store_history(term->history);
        exit(my_atoi(argv[1]));
    }
    store_history(term->history);
    exit(status);
}
