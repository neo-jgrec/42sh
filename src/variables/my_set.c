/*
** EPITECH PROJECT, 2023
** my_set
** File description:
** my_set
*/

#include "my.h"

bool does_var_exist(char *name, char **var)
{
    size_t len = strlen(name);

    for (size_t i = 0; var && var[i]; i++){
        if (strncmp(name, var[i], len) == 0 && var[i][len] == '\t')
            return (true);
    }
    return (false);
}

int my_set(char *name, char *value, char ***var)
{
    size_t len = strlen(name);
    char *new_var = my_strcat_inf(3, name, "\t", value);

    for (size_t i = 0; (*var) && (*var)[i]; i++){
        if (strncmp(name, (*var)[i], len) == 0 && (*var)[i][len] == '\t') {
            free((*var)[i]);
            (*var)[i] = strdup(new_var);
            free(new_var);
            return (0);
        }
    }
    (*var) = my_add_str_to_array((*var), new_var);
    free(new_var);
    return (0);
}
