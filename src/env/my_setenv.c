/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_setenv
*/

#include "my.h"
#include <stdbool.h>

static bool my_str_isalphanum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (IS_ALPHANUM(str[i]) == false)
            return (false);
    }
    return (true);
}

static int setenv_error_handling(char *name)
{
    if (IS_ALPHA(name[0]) == false) {
        write(1, "setenv: Variable name must begin with a letter.\n", 48);
        return (1);
    }
    if (my_str_isalphanum(name) == false) {
        write(1, "setenv: Variable name must", 26);
        write(1, " contain alphanumeric characters.\n", 34);
        return (1);
    }
    return (0);
}

static bool is_env_var_present(char *str, char **env)
{
    int i = 0;

    for (; env[i] != NULL; i++) {
        if (my_strncmp(env[i], str, my_strlen(str)) == true)
            return (true);
    }
    return (false);
}

int my_setenv(char *name, char *value, char **env)
{
    char *str = malloc(sizeof(char) * 100);
    int i = 0;

    if (setenv_error_handling(name) == 1)
        return (1);
    value = (value == NULL) ? "" : value;
    if (name == NULL)
        return (1);
    my_strcpy(str, name);
    my_strcat(str, "=");
    my_strcat(str, value);
    if (is_env_var_present(name, env) == true) {
        for (; my_strncmp(env[i], name, my_strlen(name)) != 0; i++);
        env[i] = str;
    } else {
        for (; env[i] != NULL; i++);
        env[i] = str;
        env[i + 1] = NULL;
    }
    return (0);
}
