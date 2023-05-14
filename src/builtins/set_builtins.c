/*
** EPITECH PROJECT, 2023
** set_builtins
** File description:
** set_builtins
*/

#include "my.h"

int my_set_builtin(char **args, UNUSED char **env, int *exit_status, void *data)
{
    term_t *term = data;
    size_t nb_args = my_count_array_size((const char **)args);

    (*exit_status) = 0;
    if (nb_args == 1) {
        display_variables(term->var, term->history);
        return (*exit_status);
    }
    for (size_t i = 1; args[i];) {
        if (my_strcmp(args[i + 1], "=") == 0 && args[i + 2]) {
            my_set(args[i], args[i + 2], &term->var);
            i += 3;
        } else {
            my_set(args[i], NULL, &term->var);
            i++;
        }
    }
    return (*exit_status);
}

int my_unset_builtin(char **args, UNUSED char **env, int *exit_status,
void *data)
{
    UNUSED term_t *term = data;

    *exit_status = 0;
    if (args && args[1] == NULL) {
        dprintf(2, "unset: Too few arguments.\n");
        *exit_status = 1;
        return (*exit_status);
    }
    for (size_t i = 1; args && args[i]; i++)
        my_unset(args[i], &term->var);
    return (*exit_status);
}
