/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** envirionement echo "\n$PATH\n\noui"
*/

#include "my.h"

int my_strncmp_tok(char* s1, char* s2, int n);

static size_t calculate_name_var_env_len(char *env_entry)
{
    return my_strlen(env_entry) - my_strlen(my_strchr(env_entry, '='));
}

static char *construct_result(construct_result_params_t *params)
{
    char *result = malloc(sizeof(char) * (\
    params->prefix_len + params->value_len) * 9);
    if (result == NULL)
        return NULL;
    my_strncpy(result, params->name, params->dollar_ptr - params->name);
    my_strncpy(result + (params->dollar_ptr - params->name), params->value, params->value_len);
    my_strncpy(result + (params->dollar_ptr - params->name) + params->value_len,
            params->dollar_ptr + calculate_name_var_env_len(params->dollar_ptr) + 1,
            my_strlen(params->dollar_ptr + calculate_name_var_env_len(\
            params->dollar_ptr) + 1) + 1);
    return result;
}

static char *check(char **env, char *name, size_t prefix_len, size_t value_len)
{
    char *dollar_ptr = my_strchr(name, '$');
    char *var_name;
    char *value;
    char *result;
    size_t name_var_env_len = 0;

    if (dollar_ptr == NULL)
        return name;
    var_name = dollar_ptr + 1;
    for (int i = 0; env[i] != NULL; i++) {
        name_var_env_len = calculate_name_var_env_len(env[i]);
        if (my_strncmp(env[i], var_name, name_var_env_len) == 0) {
            value = my_strchr(env[i], '=') + 1;
            value_len = my_strlen(value);
            construct_result_params_t params = {name, dollar_ptr, value, prefix_len, value_len};
            result = construct_result(&params);
            return result;
        }
    }
    return NULL;
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
