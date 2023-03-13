/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** is_builtins
*/

#include "my.h"

int is_builtins(term_t *term)
{
    for (int i = 0; commands[i].name != NULL; i++) {
        if (my_strcmp(term->argv[0], commands[i].name) == 0) {
            term->action = BUILTINS;
            my_printf("BUILTINS\n");
            commands[i].func(term);
            return (1);
        }
    }
    return (0);
}
