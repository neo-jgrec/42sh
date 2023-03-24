/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** envirionement
*/

#include "my.h"

static char *check(char **env, char *name)
{
    if (name[0] == '$') {
        if (my_getenv(env, name + 1) != NULL)
            name = my_getenv(env, name + 1);
        else {
            return (NULL);
        }
    }
    return (name);
}

char **edit_args_env(char **args, char **env)
{
    if (args == NULL)
        return (NULL);
    for (int i = 0; args[i] != NULL; i++) {
        args[i] = check(env, args[i]);
        if (args[i] == NULL) {
            printf("%s: Undefined variable.\n", args[i - 1]);
            remove_element_at_index(args, i);
        }
    }
    return (args);
}
