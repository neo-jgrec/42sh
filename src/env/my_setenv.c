/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** my_setenv
*/

#include "my.h"
#include <stdbool.h>
#include <string.h>

void add_element_tab_tail(char **tab, char *element)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    tab[i] = element;
    tab[i + 1] = NULL;
}

int my_setenv(char *name, char *value, char **env)
{
    int i = 0;
    int j = 0;
    int len = my_strlen(name);
    char *new_env = NULL;

    while (env[i] != NULL) {
        while (env[i][j] == name[j] && env[i][j] != '\0' && name[j] != '\0')
            j++;
        if (j == len && env[i][j] == '=') {
            new_env = my_strcat_inf(3, name, "=", value);
            env[i] = new_env;
            return (0);
        }
        j = 0;
        i++;
    }
    new_env = my_strcat_inf(3, name, "=", value);
    add_element_tab_tail(env, new_env);
    return (0);
}
