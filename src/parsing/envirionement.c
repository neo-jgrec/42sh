/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** envirionement
*/

#include "my.h"

static char *check(char **env, char *name)
{
    char *tmp = NULL;
    if (name[0] == '$') {
        if (my_getenv(env, name + 1) != NULL) {
            tmp = my_getenv(env, name + 1);
            return (tmp);
        } else {
            return (NULL);
        }
    }
    return (name);
}

char **edit_args_env(char **args, char **env)
{
    char *tmp = NULL;
    if (args == NULL)
        return (NULL);
    for (int i = 0; args[i] != NULL; i++) {
        tmp = check(env, args[i]);
        if (tmp != NULL) {
            args[i] = tmp;
        } else {
            my_printf("%s: Undefined variable.\n", args[i] + 1);
            return (NULL);
        }
    }
    return (args);
}
