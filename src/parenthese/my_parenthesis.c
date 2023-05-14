/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parenthese handing
*/

#include "my.h"

void my_parenthesis(exec_t *exec, int *i, term_t *term, char **args)
{
    char **par_input = malloc(sizeof(char *) * 100);
    size_t nb = 1;

    for (size_t j = *i + 1; args[j] != NULL; j++) {
        printf("%s\n", args[j]);
    }
    return;
}
