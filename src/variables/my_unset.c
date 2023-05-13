/*
** EPITECH PROJECT, 2023
** my_unset
** File description:
** my_unset
*/

#include "my.h"

static void destroy_var_elm(size_t pos, char ***var)
{
    free((*var)[pos]);
    for (; (*var)[pos + 1]; pos++){
        (*var)[pos] = strdup((*var)[pos + 1]);
        free((*var)[pos + 1]);
    }
    (*var)[pos] = NULL;
}

int my_unset(char *name, char ***var)
{
    size_t len = strlen(name);

    if (!(*var))
        return (0);
    for (size_t i = 0; (*var)[i]; i++){
        if (strncmp(name, (*var)[i], len) == 0 &&
        (*var)[i][len] == '\t') {
            destroy_var_elm(i, var);
            break;
        }
    }
    return (0);
}
