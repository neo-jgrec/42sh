/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** envirionement
*/

#include "my.h"
#include <string.h>
#include <stdlib.h>

static char *check(char **env, char *name,
size_t prefix_len, size_t value_len)
{
    char *dollar_ptr = my_strchr(name, '$');
    char *var_name;
    char *value;
    char *result;

    if (dollar_ptr == NULL)
        return name;
    var_name = dollar_ptr + 1;
    value = my_getenv(env, var_name);
    if (value == NULL) {
        my_printf("%s: Undefined variable.\n", var_name);
        return NULL;
    }
    prefix_len = dollar_ptr - name;
    value_len = my_strlen(value);
    result = malloc(prefix_len + value_len + 1);
    my_strncpy(result, name, prefix_len);
    my_strncpy(result + prefix_len, value, value_len);
    result[prefix_len + value_len] = '\0';
    return result;
}

char **edit_args_env(char **args, char **env)
{
    char *tmp = NULL;
    if (args == NULL)
        return (NULL);
    for (int i = 0; args[i] != NULL; i++) {
        tmp = check(env, args[i], 0, 0);
        if (tmp != NULL) {
            args[i] = tmp;
        } else {
            return (NULL);
        }
    }
    return (args);
}
