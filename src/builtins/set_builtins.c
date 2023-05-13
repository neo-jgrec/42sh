/*
** EPITECH PROJECT, 2023
** set_builtins
** File description:
** set_builtins
*/

#include "my.h"

static bool str_is_in_lst(char *str, char **lst)
{
    size_t len = strlen(str);

    if (!lst)
        return (false);
    for (size_t i = 0; lst[i]; i++)
        if (strncmp(str, lst[i], len) == 0 && lst[i][len] == '\t')
            return (true);
    return (false);
}

int my_set_builtin(char **args, UNUSED char **env, int *exit_status, void *data)
{
    term_t *term = data;
    size_t nb_args = my_count_array_size((const char **)args);

    (*exit_status) = 0;
    if (nb_args == 1) {
        display_variables(term->var, term->history);
        return (*exit_status);
    }
    if ((nb_args == 4 && strcmp(args[2], "=") == 0) || (nb_args >= 4 &&
    str_is_in_lst(args[1], term->var) && strcmp(args[2], "=") == 0)) {
        my_set(args[1], args[3], &term->var);
    } else
        my_set(args[1], "\n", &term->var);
    return (*exit_status);
}

int my_unset_builtin(char **args, UNUSED char **env, int *exit_status,
void *data)
{
    UNUSED term_t *term = data;

    *exit_status = 0;
    if (args && args[1] == NULL) {
        my_printf("unset: Too few arguments.\n");
        *exit_status = 1;
        return (*exit_status);
    }
    for (size_t i = 1; args && args[i]; i++)
        my_unset(args[i], &term->var);
    return (*exit_status);
}
