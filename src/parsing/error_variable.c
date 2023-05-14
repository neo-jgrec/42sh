/*
** EPITECH PROJECT, 2023
** error_variable
** File description:
** error_variable
*/

#include <string.h>
#include "my.h"
#include "parsing.h"

static bool check_var_existance(char *var, term_t *term)
{
    size_t len_var = 0;

    if (strcmp(var, "$") == 0)
        return (true);
    len_var = strlen(&var[1]);
    for (size_t i = 0; term->env && term->env[i]; i++)
        if (strncmp(&var[1], term->env[i], len_var) == 0 &&
        term->env[i][len_var] == '=')
            return (true);
    for (size_t i = 0; term->var && term->var[i]; i++) {
        if (strncmp(&var[1], term->var[i], len_var) == 0 &&
        (term->var[i][len_var] == '\t' || term->var[i][len_var] == '\0'))
            return (true);
    }
    return (false);
}

bool error_variable(char **args, term_t *term)
{
    for (size_t i = 0; args[i]; i++){
        if (IS_VAR(args[i]) && !check_var_existance(args[i], term)) {
            dprintf(2, "%s: Undefined variable.\n", &args[i][1]);
            return (true);
        }
    }
    return (false);
}
