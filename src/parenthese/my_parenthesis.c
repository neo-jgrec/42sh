/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parenthese handing
*/

#include "my.h"

void my_parenthesis(UNUSED exec_t *exec, int *i, term_t *term, char **args)
{
    char **par_input = calloc(100, sizeof(char *));
    size_t nb = 1;
    size_t index = 0;

    for (size_t j = *i + 1; nb != 0; j++) {
        if (!strcmp(args[j], "("))
            nb ++;
        if (!strcmp(args[j], ")"))
            nb --;
        if (nb != 0)
            par_input[index++] = strdup(args[j]);
    }
    exec_parenthesis(par_input, term->env);
    *i += index + 1;
    exec->cmd_start = *i + 1;
    return;
}
