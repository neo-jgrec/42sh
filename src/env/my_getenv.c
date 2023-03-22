/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_getenv
*/

#include "my.h"

char *my_getenv(char **env, const char *name)
{
    int i = 0;
    int j = 0;
    int len = my_strlen(name);

    while (env[i] != NULL) {
        while (env[i][j] == name[j] && env[i][j] != '\0' && name[j] != '\0')
            j++;
        if (j == len && env[i][j] == '=')
            return (&env[i][j + 1]);
        j = 0;
        i++;
    }
    return (NULL);
}
