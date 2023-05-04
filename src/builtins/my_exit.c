/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_exit
*/

#include "my.h"
#include <stdbool.h>

void my_exit(char **argv, UNUSED char **env, int *exit_status,
UNUSED void *data)
{
    int status = *exit_status;
    if (len_tab(argv) > 2) {
        my_printf("exit: Expression Syntax.\n");
        return;
    }
    if (argv[1] != NULL) {
        if (my_str_isnum(argv[1]) == 0) {
            my_printf("exit: Badly formed number.\n");
            return;
        }
        exit(my_atoi(argv[1]));
    }
    exit(status);
}
