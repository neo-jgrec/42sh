/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** envirionement echo "\n$PATH\n\noui"
*/

#include "my.h"
#include <string.h>
#include <stdlib.h>

static char *check(char **env, char *name,
size_t prefix_len, size_t value_len)
{
    char *dollar_ptr = strchr(name, '$');
    char *var_name, value, result;
    size_t name_var_env_len = 0;

    if (dollar_ptr == NULL) return (name);
    var_name = dollar_ptr + 1;
    for (int i = 0; env[i] != NULL; i++) {
        name_var_env_len = strlen(env[i]) - strlen(strchr(env[i], '='));
        if (strncmp(env[i], var_name, name_var_env_len) == 0) {
            value = strchr(env[i], '=') + 1; value_len = strlen(value);
            result = malloc(sizeof(char) * (prefix_len + value_len) * 2);
            (result == NULL) ? ({return (NULL);}) : (0);
            strncpy(result, name, dollar_ptr - name);
            strncpy(result + (dollar_ptr - name), value, value_len);
            strncpy(result + (dollar_ptr - name) + value_len,
            dollar_ptr + name_var_env_len + 1,
            strlen(dollar_ptr + name_var_env_len + 1) + 1);
            return (result);
        }
    } return (NULL);
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
